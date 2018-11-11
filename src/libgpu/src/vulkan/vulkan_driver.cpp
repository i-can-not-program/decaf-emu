#ifdef DECAF_VULKAN
#include "vulkan_driver.h"
#include "gpu_event.h"
#include "gpu_graphicsdriver.h"
#include "gpu_ringbuffer.h"

namespace vulkan
{

Driver::Driver()
{
}

Driver::~Driver()
{
}

gpu::GraphicsDriverType
Driver::type()
{
   return gpu::GraphicsDriverType::Vulkan;
}

void
Driver::notifyCpuFlush(phys_addr address,
                       uint32_t size)
{
}

void
Driver::notifyGpuFlush(phys_addr address,
                       uint32_t size)
{
}

void
Driver::initialise(vk::PhysicalDevice physDevice, vk::Device device, vk::Queue queue, uint32_t queueFamilyIndex)
{
   if (mRunState != RunState::None) {
      return;
   }

   mPhysDevice = physDevice;
   mDevice = device;
   mQueue = queue;
   mRunState = RunState::Running;

   validateDevice();

   // Initialize the dynamic loader we use for extensions
   mVkDynLoader.init(nullptr, mDevice);

   // Allocate a command pool to use
   vk::CommandPoolCreateInfo commandPoolDesc;
   commandPoolDesc.flags = vk::CommandPoolCreateFlagBits::eTransient | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
   commandPoolDesc.queueFamilyIndex = queueFamilyIndex;
   mCommandPool = mDevice.createCommandPool(commandPoolDesc);

   // Start our fence thread
   mFenceThread = std::thread(std::bind(&Driver::fenceWaiterThread, this));

   // Set up the VMA
   VmaAllocatorCreateInfo allocatorDesc = {};
   allocatorDesc.physicalDevice = mPhysDevice;
   allocatorDesc.device = mDevice;
   CHECK_VK_RESULT(vmaCreateAllocator(&allocatorDesc, &mAllocator));

   // Set up our drawing pipeline layout
   auto makeStageSet = [&](int stageIndex)
   {
      vk::ShaderStageFlags stageFlags;
      if (stageIndex == 0) {
         stageFlags = vk::ShaderStageFlagBits::eVertex;
      } else if (stageIndex == 1) {
         stageFlags = vk::ShaderStageFlagBits::eGeometry;
      } else if (stageIndex == 2) {
         stageFlags = vk::ShaderStageFlagBits::eFragment;
      } else {
         decaf_abort("Unexpected shader stage index");
      }

      std::vector<vk::DescriptorSetLayoutBinding> bindings;

      for (auto i = 0u; i < latte::MaxSamplers; ++i) {
         vk::DescriptorSetLayoutBinding sampBindingDesc;
         sampBindingDesc.binding = i;
         sampBindingDesc.descriptorType = vk::DescriptorType::eSampler;
         sampBindingDesc.descriptorCount = 1;
         sampBindingDesc.stageFlags = stageFlags;
         sampBindingDesc.pImmutableSamplers = nullptr;
         bindings.push_back(sampBindingDesc);
      }

      for (auto i = 0u; i < latte::MaxTextures; ++i) {
         vk::DescriptorSetLayoutBinding texBindingDesc;
         texBindingDesc.binding = latte::MaxSamplers + i;
         texBindingDesc.descriptorType = vk::DescriptorType::eSampledImage;
         texBindingDesc.descriptorCount = 1;
         texBindingDesc.stageFlags = stageFlags;
         texBindingDesc.pImmutableSamplers = nullptr;
         bindings.push_back(texBindingDesc);
      }

      for (auto i = 0u; i < latte::MaxUniformBlocks; ++i) {
         if (i >= 15) {
            // Vulkan does not support more than 15 uniform blocks unfortunately,
            // if we ever encounter a game needing all 15, we will need to do block
            // splitting or utilize SSBO's.
            break;
         }

         vk::DescriptorSetLayoutBinding cbufferBindingDesc;
         cbufferBindingDesc.binding = latte::MaxSamplers + latte::MaxTextures + i;
         cbufferBindingDesc.descriptorType = vk::DescriptorType::eUniformBuffer;
         cbufferBindingDesc.descriptorCount = 1;
         cbufferBindingDesc.stageFlags = stageFlags;
         cbufferBindingDesc.pImmutableSamplers = nullptr;
         bindings.push_back(cbufferBindingDesc);
      }

      vk::DescriptorSetLayoutCreateInfo descriptorSetLayoutDesc;
      descriptorSetLayoutDesc.bindingCount = static_cast<uint32_t>(bindings.size());
      descriptorSetLayoutDesc.pBindings = bindings.data();
      return mDevice.createDescriptorSetLayout(descriptorSetLayoutDesc);
   };

   mVertexDescriptorSetLayout = makeStageSet(0);
   mGeometryDescriptorSetLayout = makeStageSet(1);
   mPixelDescriptorSetLayout = makeStageSet(2);

   std::array<vk::DescriptorSetLayout, 3> descriptorLayouts = {
      mVertexDescriptorSetLayout,
      mGeometryDescriptorSetLayout,
      mPixelDescriptorSetLayout };


   std::vector<vk::PushConstantRange> pushConstants;

   vk::PushConstantRange screenSpaceConstants;
   screenSpaceConstants.stageFlags = vk::ShaderStageFlagBits::eVertex | vk::ShaderStageFlagBits::eGeometry;
   screenSpaceConstants.offset = 0;
   screenSpaceConstants.size = 32;
   pushConstants.push_back(screenSpaceConstants);

   vk::PushConstantRange alphaRefConstants;
   alphaRefConstants.stageFlags = vk::ShaderStageFlagBits::eFragment;
   alphaRefConstants.offset = 32;
   alphaRefConstants.size = 12;
   pushConstants.push_back(alphaRefConstants);

   vk::PipelineLayoutCreateInfo pipelineLayoutDesc;
   pipelineLayoutDesc.setLayoutCount = static_cast<uint32_t>(descriptorLayouts.size());
   pipelineLayoutDesc.pSetLayouts = descriptorLayouts.data();
   pipelineLayoutDesc.pushConstantRangeCount = static_cast<uint32_t>(pushConstants.size());
   pipelineLayoutDesc.pPushConstantRanges = pushConstants.data();
   mPipelineLayout = mDevice.createPipelineLayout(pipelineLayoutDesc);

   initialiseBlankSampler();
   initialiseBlankImage();
   initialiseBlankBuffer();

   setupResources();
}

void
Driver::initialiseBlankSampler()
{
   vk::SamplerCreateInfo samplerDesc;
   samplerDesc.magFilter = vk::Filter::eLinear;
   samplerDesc.minFilter = vk::Filter::eLinear;
   samplerDesc.mipmapMode = vk::SamplerMipmapMode::eLinear;
   samplerDesc.addressModeU = vk::SamplerAddressMode::eRepeat;
   samplerDesc.addressModeV = vk::SamplerAddressMode::eRepeat;
   samplerDesc.addressModeW = vk::SamplerAddressMode::eRepeat;
   samplerDesc.mipLodBias = 0.0f;
   samplerDesc.anisotropyEnable = false;
   samplerDesc.maxAnisotropy = 0.0f;
   samplerDesc.compareEnable = false;
   samplerDesc.compareOp = vk::CompareOp::eAlways;
   samplerDesc.minLod = 0.0f;
   samplerDesc.maxLod = 0.0f;
   samplerDesc.borderColor = vk::BorderColor::eFloatTransparentBlack;
   samplerDesc.unnormalizedCoordinates = VK_FALSE;
   auto emptySampler = mDevice.createSampler(samplerDesc);

   setVkObjectName(emptySampler, "PlaceholderSampler");

   mBlankSampler = emptySampler;
}

void
Driver::initialiseBlankImage()
{
   // Create a random image to use for sampling
   vk::ImageCreateInfo createImageDesc;
   createImageDesc.imageType = vk::ImageType::e2D;
   createImageDesc.format = vk::Format::eR8G8B8A8Snorm;
   createImageDesc.extent = vk::Extent3D(1, 1, 1);
   createImageDesc.mipLevels = 1;
   createImageDesc.arrayLayers = 1;
   createImageDesc.samples = vk::SampleCountFlagBits::e1;
   createImageDesc.tiling = vk::ImageTiling::eOptimal;
   createImageDesc.usage = vk::ImageUsageFlagBits::eSampled;
   createImageDesc.sharingMode = vk::SharingMode::eExclusive;
   createImageDesc.initialLayout = vk::ImageLayout::eUndefined;
   auto emptyImage = mDevice.createImage(createImageDesc);

   setVkObjectName(emptyImage, "PlaceholderSurface");

   auto imageMemReqs = mDevice.getImageMemoryRequirements(emptyImage);

   vk::MemoryAllocateInfo allocDesc;
   allocDesc.allocationSize = imageMemReqs.size;
   allocDesc.memoryTypeIndex = findMemoryType(imageMemReqs.memoryTypeBits, vk::MemoryPropertyFlagBits::eDeviceLocal);
   auto imageMem = mDevice.allocateMemory(allocDesc);

   mDevice.bindImageMemory(emptyImage, imageMem, 0);

   vk::ImageViewCreateInfo imageViewDesc;
   imageViewDesc.image = emptyImage;
   imageViewDesc.viewType = vk::ImageViewType::e2D;
   imageViewDesc.format = vk::Format::eR8G8B8A8Snorm;
   imageViewDesc.components = vk::ComponentMapping();
   imageViewDesc.subresourceRange = { vk::ImageAspectFlagBits::eColor, 0, 1, 0, 1 };
   auto emptyImageView = mDevice.createImageView(imageViewDesc);

   setVkObjectName(emptyImageView, "PlaceholderView");

   mBlankImage = emptyImage;
   mBlankImageView = emptyImageView;
}

void
Driver::initialiseBlankBuffer()
{
   vk::BufferCreateInfo bufferDesc;
   bufferDesc.size = 1024;
   bufferDesc.usage =
      vk::BufferUsageFlagBits::eUniformBuffer |
      vk::BufferUsageFlagBits::eTransferDst |
      vk::BufferUsageFlagBits::eTransferSrc;
   bufferDesc.sharingMode = vk::SharingMode::eExclusive;
   bufferDesc.queueFamilyIndexCount = 0;
   bufferDesc.pQueueFamilyIndices = nullptr;

   VmaAllocationCreateInfo allocInfo = {};
   allocInfo.usage = VMA_MEMORY_USAGE_GPU_ONLY;

   VkBuffer emptyBuffer;
   VmaAllocation allocation;
   vmaCreateBuffer(mAllocator,
                   &static_cast<VkBufferCreateInfo>(bufferDesc),
                   &allocInfo,
                   &emptyBuffer,
                   &allocation,
                   nullptr);

   setVkObjectName(emptyBuffer, "PlaceholderBuffer");

   mBlankBuffer = emptyBuffer;
}

void
Driver::setupResources()
{
   vk::CommandBufferAllocateInfo cmdBufferAllocDesc(mCommandPool, vk::CommandBufferLevel::ePrimary, 1);
   auto cmdBuffer = mDevice.allocateCommandBuffers(cmdBufferAllocDesc)[0];

   cmdBuffer.begin(vk::CommandBufferBeginInfo {});

   {
      vk::ImageMemoryBarrier imageBarrier;
      imageBarrier.srcAccessMask = vk::AccessFlags();
      imageBarrier.dstAccessMask = vk::AccessFlags();
      imageBarrier.oldLayout = vk::ImageLayout::eUndefined;
      imageBarrier.newLayout = vk::ImageLayout::eShaderReadOnlyOptimal;
      imageBarrier.srcQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
      imageBarrier.dstQueueFamilyIndex = VK_QUEUE_FAMILY_IGNORED;
      imageBarrier.image = mBlankImage;
      imageBarrier.subresourceRange.aspectMask = vk::ImageAspectFlagBits::eColor;
      imageBarrier.subresourceRange.baseMipLevel = 0;
      imageBarrier.subresourceRange.levelCount = 1;
      imageBarrier.subresourceRange.baseArrayLayer = 0;
      imageBarrier.subresourceRange.layerCount = 1;

      cmdBuffer.pipelineBarrier(
         vk::PipelineStageFlagBits::eAllCommands,
         vk::PipelineStageFlagBits::eAllCommands,
         vk::DependencyFlags(),
         {},
         {},
         { imageBarrier });
   }

   cmdBuffer.end();

   vk::SubmitInfo submitInfo;
   submitInfo.commandBufferCount = 1;
   submitInfo.pCommandBuffers = &cmdBuffer;
   mQueue.submit({ submitInfo }, vk::Fence());
}

vk::DescriptorPool
Driver::allocateDescriptorPool(uint32_t numDraws)
{
   vk::DescriptorPool descriptorPool;

   if (!descriptorPool) {
      if (!mDescriptorPools.empty()) {
         descriptorPool = mDescriptorPools.back();
         mDescriptorPools.pop_back();
      }
   }

   if (!descriptorPool) {
      std::vector<vk::DescriptorPoolSize> descriptorPoolSizes = {
         vk::DescriptorPoolSize(vk::DescriptorType::eSampler, latte::MaxSamplers * numDraws),
         vk::DescriptorPoolSize(vk::DescriptorType::eSampledImage, latte::MaxTextures * numDraws),
         vk::DescriptorPoolSize(vk::DescriptorType::eUniformBuffer, latte::MaxAttribBuffers * numDraws),
      };

      vk::DescriptorPoolCreateInfo descriptorPoolInfo;
      descriptorPoolInfo.poolSizeCount = static_cast<uint32_t>(descriptorPoolSizes.size());
      descriptorPoolInfo.pPoolSizes = descriptorPoolSizes.data();
      descriptorPoolInfo.maxSets = static_cast<uint32_t>(numDraws);
      descriptorPool = mDevice.createDescriptorPool(descriptorPoolInfo);
   }

   mActiveSyncWaiter->descriptorPools.push_back(descriptorPool);

   return descriptorPool;
}

vk::DescriptorSet
Driver::allocateGenericDescriptorSet(vk::DescriptorSetLayout &setLayout)
{
   static const uint32_t maxPoolDraws = 32;

   if (!mActiveDescriptorPool || mActiveDescriptorPoolDrawsLeft == 0) {
      mActiveDescriptorPool = allocateDescriptorPool(maxPoolDraws);
      mActiveDescriptorPoolDrawsLeft = maxPoolDraws;
   }

   vk::DescriptorSetAllocateInfo allocInfo;
   allocInfo.descriptorSetCount = 1;
   allocInfo.pSetLayouts = &setLayout;
   allocInfo.descriptorPool = mActiveDescriptorPool;
   mActiveDescriptorPoolDrawsLeft--;

   return mDevice.allocateDescriptorSets(allocInfo)[0];
}

vk::DescriptorSet
Driver::allocateVertexDescriptorSet()
{
   return allocateGenericDescriptorSet(mVertexDescriptorSetLayout);
}

vk::DescriptorSet
Driver::allocateGeometryDescriptorSet()
{
   return allocateGenericDescriptorSet(mGeometryDescriptorSetLayout);
}

vk::DescriptorSet
Driver::allocatePixelDescriptorSet()
{
   return allocateGenericDescriptorSet(mPixelDescriptorSetLayout);
}

void
Driver::retireDescriptorPool(vk::DescriptorPool descriptorPool)
{
   mDevice.resetDescriptorPool(descriptorPool, vk::DescriptorPoolResetFlags());
   mDescriptorPools.push_back(descriptorPool);
}

vk::QueryPool
Driver::allocateOccQueryPool()
{
   vk::QueryPool occPool;

   if (!occPool) {
      if (!mOccQueryPools.empty()) {
         occPool = mOccQueryPools.back();
         mOccQueryPools.pop_back();
      }
   }

   if (!occPool) {
      vk::QueryPoolCreateInfo queryDesc;
      queryDesc.queryType = vk::QueryType::eOcclusion;
      queryDesc.queryCount = 1;
      occPool  = mDevice.createQueryPool(queryDesc);
   }

   mActiveCommandBuffer.resetQueryPool(occPool, 0, 1);

   mActiveSyncWaiter->occQueryPools.push_back(occPool);

   return occPool;
}

void
Driver::retireOccQueryPool(vk::QueryPool pool)
{
   mOccQueryPools.push_back(pool);
}

void
Driver::shutdown()
{
   mFenceSignal.notify_all();
   mFenceThread.join();
}

void
Driver::getSwapBuffers(vk::Image &tvImage, vk::ImageView &tvView, vk::Image &drcImage, vk::ImageView &drcView)
{
   if (mTvSwapChain && mTvSwapChain->presentable) {
      tvImage = mTvSwapChain->image;
      tvView = mTvSwapChain->imageView;
   } else {
      tvImage = vk::Image();
      tvView = vk::ImageView();
   }

   if (mDrcSwapChain && mDrcSwapChain->presentable) {
      drcImage = mDrcSwapChain->image;
      drcView = mDrcSwapChain->imageView;
   } else {
      drcImage = vk::Image();
      drcView = vk::ImageView();
   }
}

void
Driver::run()
{
   while (mRunState == RunState::Running) {
      // Grab the next buffer
      gpu::ringbuffer::wait();
      auto buffer = gpu::ringbuffer::read();

      // Check for any fences completing
      checkSyncFences();

      // Process the buffer if there is anything new
      if (!buffer.empty()) {
         executeBuffer(buffer);
      }
   }
}

void
Driver::stop()
{
   mRunState = RunState::Stopped;
   gpu::ringbuffer::wake();
}

void
Driver::runUntilFlip()
{
   auto startingSwap = mLastSwap;

   while (mRunState == RunState::Running) {
      // Grab the next item
      gpu::ringbuffer::wait();

      // Check for any fences completing
      checkSyncFences();

      // Process the buffer if there is anything new
      auto buffer = gpu::ringbuffer::read();
      if (!buffer.empty()) {
         executeBuffer(buffer);
      }

      if (mLastSwap > startingSwap) {
         break;
      }
   }
}

void
Driver::beginCommandGroup()
{
   mActiveBatchIndex++;

   mActiveSyncWaiter = allocateSyncWaiter();
   mActiveCommandBuffer = mActiveSyncWaiter->cmdBuffer;
}

void
Driver::endCommandGroup()
{
   // Submit the active waiter to the queue
   submitSyncWaiter(mActiveSyncWaiter);

   // Clear our state in between command buffers for safety
   mActiveCommandBuffer = nullptr;
   mActiveSyncWaiter = nullptr;
   mActivePipeline = nullptr;
   mActiveRenderPass = nullptr;
   mActiveDescriptorPool = vk::DescriptorPool();
}

void
Driver::beginCommandBuffer()
{
   // Begin recording our host command buffer
   mActiveCommandBuffer.begin(vk::CommandBufferBeginInfo(vk::CommandBufferUsageFlagBits::eOneTimeSubmit));
}

void
Driver::endCommandBuffer()
{
   // We have to force our memcache objects to be downloaded at the
   // end of every PM4 buffer.
   downloadPendingMemCache();

   // Stop recording this host command buffer
   mActiveCommandBuffer.end();
}

int32_t
Driver::findMemoryType(uint32_t memTypeBits, vk::MemoryPropertyFlags requestProps)
{
   auto memoryProps = mPhysDevice.getMemoryProperties();

   const uint32_t memoryCount = memoryProps.memoryTypeCount;
   for (uint32_t memoryIndex = 0; memoryIndex < memoryCount; ++memoryIndex) {
      const uint32_t memoryTypeBits = (1 << memoryIndex);
      const bool isRequiredMemoryType = memTypeBits & memoryTypeBits;

      const auto properties = memoryProps.memoryTypes[memoryIndex].propertyFlags;
      const bool hasRequiredProperties = (properties & requestProps) == requestProps;

      if (isRequiredMemoryType && hasRequiredProperties)
         return static_cast<int32_t>(memoryIndex);
   }

   throw std::logic_error("failed to find suitable memory type");
}

ResourceUsageMeta
Driver::getResourceUsageMeta(ResourceUsage usage)
{
   switch (usage) {
   case ResourceUsage::Undefined:
      return { false,
               vk::AccessFlags(),
               vk::PipelineStageFlagBits::eBottomOfPipe,
               vk::ImageLayout::eUndefined };

   case ResourceUsage::VertexTexture:
      return { false,
               vk::AccessFlagBits::eShaderRead,
               vk::PipelineStageFlagBits::eVertexShader,
               vk::ImageLayout::eShaderReadOnlyOptimal };
   case ResourceUsage::GeometryTexture:
      return { false,
               vk::AccessFlagBits::eShaderRead,
               vk::PipelineStageFlagBits::eGeometryShader,
               vk::ImageLayout::eShaderReadOnlyOptimal };
   case ResourceUsage::PixelTexture:
      return { false,
               vk::AccessFlagBits::eShaderRead,
               vk::PipelineStageFlagBits::eFragmentShader,
               vk::ImageLayout::eShaderReadOnlyOptimal };
   case ResourceUsage::IndexBuffer:
      return { false,
               vk::AccessFlagBits::eIndexRead,
               vk::PipelineStageFlagBits::eVertexInput,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::VertexUniforms:
      return { false,
               vk::AccessFlagBits::eUniformRead,
               vk::PipelineStageFlagBits::eVertexShader,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::GeometryUniforms:
      return { false,
               vk::AccessFlagBits::eUniformRead,
               vk::PipelineStageFlagBits::eGeometryShader,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::PixelUniforms:
      return { false,
               vk::AccessFlagBits::eUniformRead,
               vk::PipelineStageFlagBits::eFragmentShader,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::AttributeBuffer:
      return { false,
               vk::AccessFlagBits::eVertexAttributeRead,
               vk::PipelineStageFlagBits::eVertexInput,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::StreamOutCounterRead:
      return { false,
               vk::AccessFlagBits::eTransformFeedbackCounterReadEXT,
               vk::PipelineStageFlagBits::eTransformFeedbackEXT,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::TransferSrc:
      return { false,
               vk::AccessFlagBits::eTransferRead,
               vk::PipelineStageFlagBits::eTransfer,
               vk::ImageLayout::eTransferSrcOptimal };
   case ResourceUsage::HostRead:
      return { false,
               vk::AccessFlagBits::eHostRead,
               vk::PipelineStageFlagBits::eHost,
               vk::ImageLayout::eUndefined };

   case ResourceUsage::ColorAttachment:
      return { true,
               vk::AccessFlagBits::eColorAttachmentWrite,
               vk::PipelineStageFlagBits::eColorAttachmentOutput,
               vk::ImageLayout::eColorAttachmentOptimal };
   case ResourceUsage::DepthStencilAttachment:
      return { true,
               vk::AccessFlagBits::eDepthStencilAttachmentWrite,
               vk::PipelineStageFlagBits::eLateFragmentTests,
               vk::ImageLayout::eDepthStencilAttachmentOptimal };
   case ResourceUsage::StreamOutBuffer:
      return { true,
               vk::AccessFlagBits::eTransformFeedbackWriteEXT,
               vk::PipelineStageFlagBits::eTransformFeedbackEXT,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::StreamOutCounterWrite:
      return { true,
               vk::AccessFlagBits::eTransformFeedbackCounterWriteEXT,
               vk::PipelineStageFlagBits::eTransformFeedbackEXT,
               vk::ImageLayout::eUndefined };
   case ResourceUsage::TransferDst:
      return { true,
               vk::AccessFlagBits::eTransferWrite,
               vk::PipelineStageFlagBits::eTransfer,
               vk::ImageLayout::eTransferDstOptimal };
   case ResourceUsage::HostWrite:
      return { true,
               vk::AccessFlagBits::eHostWrite,
               vk::PipelineStageFlagBits::eHost,
               vk::ImageLayout::eUndefined };
   default:
      decaf_abort("Unexpected resource usage");
   }
}

} // namespace vulkan

#endif // ifdef DECAF_VULKAN
