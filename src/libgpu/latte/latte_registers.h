#pragma once
#include "latte_contextstate.h"
#include "latte_registers_cb.h"
#include "latte_registers_cp.h"
#include "latte_registers_db.h"
#include "latte_registers_pa.h"
#include "latte_registers_spi.h"
#include "latte_registers_sq.h"
#include "latte_registers_sx.h"
#include "latte_registers_ta.h"
#include "latte_registers_td.h"
#include "latte_registers_vgt.h"

#include <cstdint>

namespace latte
{

static const uint32_t MicroTileWidth = 8;
static const uint32_t MicroTileHeight = 8;

namespace Register_
{

enum Value : uint32_t
{
   IH_RB_BASE                       = 0x03E04,
   IH_RB_RPTR                       = 0x03E08,
   IH_RB_WPTR                       = 0x03E0C,
   IH_STATUS                        = 0x03E20,

   // Config Registers
   ConfigRegisterBase               = 0x08000,
   CP_COHER_STATUS                  = 0x085FC,
   CP_BUSY_STAT                     = 0x0867C,
   CP_STAT                          = 0x08680,
   CP_RB_RPTR                       = 0x08700,
   CP_IB1_BASE_LO                   = 0x08730,
   CP_IB1_BASE_HI                   = 0x08734,
   CP_IB1_BASE_SIZE                 = 0x08738,
   CP_IB2_BASE_LO                   = 0x0873C,
   CP_IB2_BASE_HI                   = 0x08740,
   CP_IB2_BASE_SIZE                 = 0x08744,
   CP_PERFMON_CNTL                  = 0x087FC,
   VGT_GS_PER_ES                    = 0x088C8,
   VGT_ES_PER_GS                    = 0x088CC,
   VGT_GS_VERTEX_REUSE              = 0x088D4,
   VGT_GS_PER_VS                    = 0x088E8,
   VGT_PRIMITIVE_TYPE               = 0x08958,
   VGT_NUM_INDICES                  = 0x08970,
   SQ_CONFIG                        = 0x08C00,
   SQ_GPR_RESOURCE_MGMT_1           = 0x08C04,
   SQ_GPR_RESOURCE_MGMT_2           = 0x08C08,
   SQ_THREAD_RESOURCE_MGMT          = 0x08C0C,
   SQ_STACK_RESOURCE_MGMT_1         = 0x08C10,
   SQ_STACK_RESOURCE_MGMT_2         = 0x08C14,
   SQ_ESGS_RING_BASE                = 0x08C40,
   SQ_ESGS_RING_SIZE                = 0x08C44,
   SQ_GSVS_RING_BASE                = 0x08C48,
   SQ_GSVS_RING_SIZE                = 0x08C4C,
   SQ_ESTMP_RING_BASE               = 0x08C50,
   SQ_ESTMP_RING_SIZE               = 0x08C54,
   SQ_GSTMP_RING_BASE               = 0x08C58,
   SQ_GSTMP_RING_SIZE               = 0x08C5C,
   SQ_VSTMP_RING_BASE               = 0x08C60,
   SQ_VSTMP_RING_SIZE               = 0x08C64,
   SQ_PSTMP_RING_BASE               = 0x08C68,
   SQ_PSTMP_RING_SIZE               = 0x08C6C,
   SQ_FBUF_RING_BASE                = 0x08C70,
   SQ_FBUF_RING_SIZE                = 0x08C74,
   SQ_REDUC_RING_BASE               = 0x08C78,
   SQ_REDUC_RING_SIZE               = 0x08C7C,
   SPI_CONFIG_CNTL_1                = 0x0913C,
   TA_CNTL_AUX                      = 0x09508,
   TD_PS_SAMPLER_BORDER0_RED        = 0x0A400,
   TD_PS_SAMPLER_BORDER0_GREEN      = 0x0A404,
   TD_PS_SAMPLER_BORDER0_BLUE       = 0x0A408,
   TD_PS_SAMPLER_BORDER0_ALPHA      = 0x0A40C,
   // ...
   TD_PS_SAMPLER_BORDER17_RED       = 0x0A510,
   TD_PS_SAMPLER_BORDER17_GREEN     = 0x0A514,
   TD_PS_SAMPLER_BORDER17_BLUE      = 0x0A518,
   TD_PS_SAMPLER_BORDER17_ALPHA     = 0x0A51C,
   TD_VS_SAMPLER_BORDER0_RED        = 0x0A600,
   TD_VS_SAMPLER_BORDER0_GREEN      = 0x0A604,
   TD_VS_SAMPLER_BORDER0_BLUE       = 0x0A608,
   TD_VS_SAMPLER_BORDER0_ALPHA      = 0x0A60C,
   // ...
   TD_VS_SAMPLER_BORDER17_RED       = 0x0A710,
   TD_VS_SAMPLER_BORDER17_GREEN     = 0x0A714,
   TD_VS_SAMPLER_BORDER17_BLUE      = 0x0A718,
   TD_VS_SAMPLER_BORDER17_ALPHA     = 0x0A71C,
   TD_GS_SAMPLER_BORDER0_RED        = 0x0A900,
   TD_GS_SAMPLER_BORDER0_GREEN      = 0x0A904,
   TD_GS_SAMPLER_BORDER0_BLUE       = 0x0A908,
   TD_GS_SAMPLER_BORDER0_ALPHA      = 0x0A90C,
   // ...
   TD_GS_SAMPLER_BORDER17_RED       = 0x0AA10,
   TD_GS_SAMPLER_BORDER17_GREEN     = 0x0AA14,
   TD_GS_SAMPLER_BORDER17_BLUE      = 0x0AA18,
   TD_GS_SAMPLER_BORDER17_ALPHA     = 0x0AA1C,
   ConfigRegisterEnd                = 0x0AC00,

   CP_RB_BASE                       = 0x0C100,
   CP_RB_CNTL                       = 0x0C104,
   CP_INT_CNTL                      = 0x0C124,
   CP_INT_STATUS                    = 0x0C128,

   // Context Registers
   ContextRegisterBase              = 0x28000,
   DB_DEPTH_SIZE                    = 0x28000,
   DB_DEPTH_VIEW                    = 0x28004,
   DB_DEPTH_BASE                    = 0x2800C,
   DB_DEPTH_INFO                    = 0x28010,
   DB_DEPTH_HTILE_DATA_BASE         = 0x28014,
   DB_STENCIL_CLEAR                 = 0x28028,
   DB_DEPTH_CLEAR                   = 0x2802C,
   PA_SC_SCREEN_SCISSOR_TL          = 0x28030,
   PA_SC_SCREEN_SCISSOR_BR          = 0x28034,
   CB_COLOR0_BASE                   = 0x28040,
   CB_COLOR1_BASE                   = 0x28044,
   CB_COLOR2_BASE                   = 0x28048,
   CB_COLOR3_BASE                   = 0x2804C,
   CB_COLOR4_BASE                   = 0x28050,
   CB_COLOR5_BASE                   = 0x28054,
   CB_COLOR6_BASE                   = 0x28058,
   CB_COLOR7_BASE                   = 0x2805C,
   CB_COLOR0_SIZE                   = 0x28060,
   CB_COLOR1_SIZE                   = 0x28064,
   CB_COLOR2_SIZE                   = 0x28068,
   CB_COLOR3_SIZE                   = 0x2806C,
   CB_COLOR4_SIZE                   = 0x28070,
   CB_COLOR5_SIZE                   = 0x28074,
   CB_COLOR6_SIZE                   = 0x28078,
   CB_COLOR7_SIZE                   = 0x2807C,
   CB_COLOR0_VIEW                   = 0x28080,
   CB_COLOR1_VIEW                   = 0x28084,
   CB_COLOR2_VIEW                   = 0x28088,
   CB_COLOR3_VIEW                   = 0x2808C,
   CB_COLOR4_VIEW                   = 0x28090,
   CB_COLOR5_VIEW                   = 0x28094,
   CB_COLOR6_VIEW                   = 0x28098,
   CB_COLOR7_VIEW                   = 0x2809C,
   CB_COLOR0_INFO                   = 0x280A0,
   CB_COLOR1_INFO                   = 0x280A4,
   CB_COLOR2_INFO                   = 0x280A8,
   CB_COLOR3_INFO                   = 0x280AC,
   CB_COLOR4_INFO                   = 0x280B0,
   CB_COLOR5_INFO                   = 0x280B4,
   CB_COLOR6_INFO                   = 0x280B8,
   CB_COLOR7_INFO                   = 0x280BC,
   CB_COLOR0_TILE                   = 0x280C0,
   CB_COLOR1_TILE                   = 0x280C4,
   CB_COLOR2_TILE                   = 0x280C8,
   CB_COLOR3_TILE                   = 0x280CC,
   CB_COLOR4_TILE                   = 0x280D0,
   CB_COLOR5_TILE                   = 0x280D4,
   CB_COLOR6_TILE                   = 0x280D8,
   CB_COLOR7_TILE                   = 0x280DC,
   CB_COLOR0_FRAG                   = 0x280E0,
   CB_COLOR1_FRAG                   = 0x280E4,
   CB_COLOR2_FRAG                   = 0x280E8,
   CB_COLOR3_FRAG                   = 0x280EC,
   CB_COLOR4_FRAG                   = 0x280F0,
   CB_COLOR5_FRAG                   = 0x280F4,
   CB_COLOR6_FRAG                   = 0x280F8,
   CB_COLOR7_FRAG                   = 0x280FC,
   CB_COLOR0_MASK                   = 0x28100,
   CB_COLOR1_MASK                   = 0x28104,
   CB_COLOR2_MASK                   = 0x28108,
   CB_COLOR3_MASK                   = 0x2810C,
   CB_COLOR4_MASK                   = 0x28110,
   CB_COLOR5_MASK                   = 0x28114,
   CB_COLOR6_MASK                   = 0x28118,
   CB_COLOR7_MASK                   = 0x2811C,
   SQ_ALU_CONST_BUFFER_SIZE_PS_0    = 0x28140,
   SQ_ALU_CONST_BUFFER_SIZE_PS_1    = 0x28144,
   SQ_ALU_CONST_BUFFER_SIZE_PS_2    = 0x28148,
   SQ_ALU_CONST_BUFFER_SIZE_PS_3    = 0x2814C,
   SQ_ALU_CONST_BUFFER_SIZE_PS_4    = 0x28150,
   SQ_ALU_CONST_BUFFER_SIZE_PS_5    = 0x28154,
   SQ_ALU_CONST_BUFFER_SIZE_PS_6    = 0x28158,
   SQ_ALU_CONST_BUFFER_SIZE_PS_7    = 0x2815C,
   SQ_ALU_CONST_BUFFER_SIZE_PS_8    = 0x28160,
   SQ_ALU_CONST_BUFFER_SIZE_PS_9    = 0x28164,
   SQ_ALU_CONST_BUFFER_SIZE_PS_10   = 0x28168,
   SQ_ALU_CONST_BUFFER_SIZE_PS_11   = 0x2816C,
   SQ_ALU_CONST_BUFFER_SIZE_PS_12   = 0x28170,
   SQ_ALU_CONST_BUFFER_SIZE_PS_13   = 0x28174,
   SQ_ALU_CONST_BUFFER_SIZE_PS_14   = 0x28178,
   SQ_ALU_CONST_BUFFER_SIZE_PS_15   = 0x2817C,
   SQ_ALU_CONST_BUFFER_SIZE_VS_0    = 0x28180,
   SQ_ALU_CONST_BUFFER_SIZE_VS_1    = 0x28184,
   SQ_ALU_CONST_BUFFER_SIZE_VS_2    = 0x28188,
   SQ_ALU_CONST_BUFFER_SIZE_VS_3    = 0x2818C,
   SQ_ALU_CONST_BUFFER_SIZE_VS_4    = 0x28190,
   SQ_ALU_CONST_BUFFER_SIZE_VS_5    = 0x28194,
   SQ_ALU_CONST_BUFFER_SIZE_VS_6    = 0x28198,
   SQ_ALU_CONST_BUFFER_SIZE_VS_7    = 0x2819C,
   SQ_ALU_CONST_BUFFER_SIZE_VS_8    = 0x281A0,
   SQ_ALU_CONST_BUFFER_SIZE_VS_9    = 0x281A4,
   SQ_ALU_CONST_BUFFER_SIZE_VS_10   = 0x281A8,
   SQ_ALU_CONST_BUFFER_SIZE_VS_11   = 0x281AC,
   SQ_ALU_CONST_BUFFER_SIZE_VS_12   = 0x281B0,
   SQ_ALU_CONST_BUFFER_SIZE_VS_13   = 0x281B4,
   SQ_ALU_CONST_BUFFER_SIZE_VS_14   = 0x281B8,
   SQ_ALU_CONST_BUFFER_SIZE_VS_15   = 0x281BC,
   SQ_ALU_CONST_BUFFER_SIZE_GS_0    = 0x281C0,
   SQ_ALU_CONST_BUFFER_SIZE_GS_1    = 0x281C4,
   SQ_ALU_CONST_BUFFER_SIZE_GS_2    = 0x281C8,
   SQ_ALU_CONST_BUFFER_SIZE_GS_3    = 0x281CC,
   SQ_ALU_CONST_BUFFER_SIZE_GS_4    = 0x281D0,
   SQ_ALU_CONST_BUFFER_SIZE_GS_5    = 0x281D4,
   SQ_ALU_CONST_BUFFER_SIZE_GS_6    = 0x281D8,
   SQ_ALU_CONST_BUFFER_SIZE_GS_7    = 0x281DC,
   SQ_ALU_CONST_BUFFER_SIZE_GS_8    = 0x281E0,
   SQ_ALU_CONST_BUFFER_SIZE_GS_9    = 0x281E4,
   SQ_ALU_CONST_BUFFER_SIZE_GS_10   = 0x281E8,
   SQ_ALU_CONST_BUFFER_SIZE_GS_11   = 0x281EC,
   SQ_ALU_CONST_BUFFER_SIZE_GS_12   = 0x281F0,
   SQ_ALU_CONST_BUFFER_SIZE_GS_13   = 0x281F4,
   SQ_ALU_CONST_BUFFER_SIZE_GS_14   = 0x281F8,
   SQ_ALU_CONST_BUFFER_SIZE_GS_15   = 0x281FC,
   PA_SC_WINDOW_OFFSET              = 0x28200,
   PA_SC_WINDOW_SCISSOR_TL          = 0x28204,
   PA_SC_WINDOW_SCISSOR_BR          = 0x28208,
   PA_SC_CLIPRECT_RULE              = 0x2820C,
   CB_TARGET_MASK                   = 0x28238,
   CB_SHADER_MASK                   = 0x2823C,
   PA_SC_GENERIC_SCISSOR_TL         = 0x28240,
   PA_SC_GENERIC_SCISSOR_BR         = 0x28244,
   PA_SC_VPORT_SCISSOR_0_TL         = 0x28250,
   PA_SC_VPORT_SCISSOR_0_BR         = 0x28254,
   PA_SC_VPORT_ZMIN_0               = 0x282D0,
   PA_SC_VPORT_ZMAX_0               = 0x282D4,
   PA_SC_VPORT_ZMIN_1               = 0x282D8,
   PA_SC_VPORT_ZMAX_1               = 0x282DC,
   PA_SC_VPORT_ZMIN_2               = 0x282E0,
   PA_SC_VPORT_ZMAX_2               = 0x282E4,
   PA_SC_VPORT_ZMIN_3               = 0x282E8,
   PA_SC_VPORT_ZMAX_3               = 0x282EC,
   PA_SC_VPORT_ZMIN_4               = 0x282F0,
   PA_SC_VPORT_ZMAX_4               = 0x282F4,
   PA_SC_VPORT_ZMIN_5               = 0x282F8,
   PA_SC_VPORT_ZMAX_5               = 0x282FC,
   PA_SC_VPORT_ZMIN_6               = 0x28300,
   PA_SC_VPORT_ZMAX_6               = 0x28304,
   PA_SC_VPORT_ZMIN_7               = 0x28308,
   PA_SC_VPORT_ZMAX_7               = 0x2830C,
   PA_SC_VPORT_ZMIN_8               = 0x28310,
   PA_SC_VPORT_ZMAX_8               = 0x28314,
   PA_SC_VPORT_ZMIN_9               = 0x28318,
   PA_SC_VPORT_ZMAX_9               = 0x2831C,
   PA_SC_VPORT_ZMIN_10              = 0x28320,
   PA_SC_VPORT_ZMAX_10              = 0x28324,
   PA_SC_VPORT_ZMIN_11              = 0x28328,
   PA_SC_VPORT_ZMAX_11              = 0x2832C,
   PA_SC_VPORT_ZMIN_12              = 0x28330,
   PA_SC_VPORT_ZMAX_12              = 0x28334,
   PA_SC_VPORT_ZMIN_13              = 0x28338,
   PA_SC_VPORT_ZMAX_13              = 0x2833C,
   PA_SC_VPORT_ZMIN_14              = 0x28340,
   PA_SC_VPORT_ZMAX_14              = 0x28344,
   PA_SC_VPORT_ZMIN_15              = 0x28348,
   PA_SC_VPORT_ZMAX_15              = 0x2834C,
   SQ_VTX_SEMANTIC_0                = 0x28380,
   SQ_VTX_SEMANTIC_1                = 0x28384,
   SQ_VTX_SEMANTIC_2                = 0x28388,
   SQ_VTX_SEMANTIC_3                = 0x2838C,
   SQ_VTX_SEMANTIC_4                = 0x28390,
   SQ_VTX_SEMANTIC_5                = 0x28394,
   SQ_VTX_SEMANTIC_6                = 0x28398,
   SQ_VTX_SEMANTIC_7                = 0x2839C,
   SQ_VTX_SEMANTIC_8                = 0x283A0,
   SQ_VTX_SEMANTIC_9                = 0x283A4,
   SQ_VTX_SEMANTIC_10               = 0x283A8,
   SQ_VTX_SEMANTIC_11               = 0x283AC,
   SQ_VTX_SEMANTIC_12               = 0x283B0,
   SQ_VTX_SEMANTIC_13               = 0x283B4,
   SQ_VTX_SEMANTIC_14               = 0x283B8,
   SQ_VTX_SEMANTIC_15               = 0x283BC,
   SQ_VTX_SEMANTIC_16               = 0x283C0,
   SQ_VTX_SEMANTIC_17               = 0x283C4,
   SQ_VTX_SEMANTIC_18               = 0x283C8,
   SQ_VTX_SEMANTIC_19               = 0x283CC,
   SQ_VTX_SEMANTIC_20               = 0x283D0,
   SQ_VTX_SEMANTIC_21               = 0x283D4,
   SQ_VTX_SEMANTIC_22               = 0x283D8,
   SQ_VTX_SEMANTIC_23               = 0x283DC,
   SQ_VTX_SEMANTIC_24               = 0x283E0,
   SQ_VTX_SEMANTIC_25               = 0x283E4,
   SQ_VTX_SEMANTIC_26               = 0x283E8,
   SQ_VTX_SEMANTIC_27               = 0x283EC,
   SQ_VTX_SEMANTIC_28               = 0x283F0,
   SQ_VTX_SEMANTIC_29               = 0x283F4,
   SQ_VTX_SEMANTIC_30               = 0x283F8,
   SQ_VTX_SEMANTIC_31               = 0x283FC,
   VGT_MAX_VTX_INDX                 = 0x28400,
   VGT_MIN_VTX_INDX                 = 0x28404,
   VGT_INDX_OFFSET                  = 0x28408,
   VGT_MULTI_PRIM_IB_RESET_INDX     = 0x2840C,
   SX_ALPHA_TEST_CONTROL            = 0x28410,
   CB_BLEND_RED                     = 0x28414,
   CB_BLEND_GREEN                   = 0x28418,
   CB_BLEND_BLUE                    = 0x2841C,
   CB_BLEND_ALPHA                   = 0x28420,
   DB_STENCILREFMASK                = 0x28430,
   DB_STENCILREFMASK_BF             = 0x28434,
   SX_ALPHA_REF                     = 0x28438,
   PA_CL_VPORT_XSCALE_0             = 0x2843C,
   PA_CL_VPORT_XOFFSET_0            = 0x28440,
   PA_CL_VPORT_YSCALE_0             = 0x28444,
   PA_CL_VPORT_YOFFSET_0            = 0x28448,
   PA_CL_VPORT_ZSCALE_0             = 0x2844C,
   PA_CL_VPORT_ZOFFSET_0            = 0x28450,
   // ...
   PA_CL_VPORT_XSCALE_15            = 0x285A4,
   PA_CL_VPORT_XOFFSET_15           = 0x285A8,
   PA_CL_VPORT_YSCALE_15            = 0x285AC,
   PA_CL_VPORT_YOFFSET_15           = 0x285B0,
   PA_CL_VPORT_ZSCALE_15            = 0x285B4,
   PA_CL_VPORT_ZOFFSET_15           = 0x285B8,
   SPI_VS_OUT_ID_0                  = 0x28614,
   SPI_VS_OUT_ID_1                  = 0x28618,
   SPI_VS_OUT_ID_2                  = 0x2861C,
   SPI_VS_OUT_ID_3                  = 0x28620,
   SPI_VS_OUT_ID_4                  = 0x28624,
   SPI_VS_OUT_ID_5                  = 0x28628,
   SPI_VS_OUT_ID_6                  = 0x2862C,
   SPI_VS_OUT_ID_7                  = 0x28630,
   SPI_VS_OUT_ID_8                  = 0x28634,
   SPI_VS_OUT_ID_9                  = 0x28638,
   SPI_PS_INPUT_CNTL_0              = 0x28640,
   SPI_PS_INPUT_CNTL_1              = 0x28644,
   SPI_PS_INPUT_CNTL_2              = 0x28648,
   SPI_PS_INPUT_CNTL_3              = 0x2864C,
   SPI_PS_INPUT_CNTL_4              = 0x28650,
   SPI_PS_INPUT_CNTL_5              = 0x28654,
   SPI_PS_INPUT_CNTL_6              = 0x28658,
   SPI_PS_INPUT_CNTL_7              = 0x2865C,
   SPI_PS_INPUT_CNTL_8              = 0x28660,
   SPI_PS_INPUT_CNTL_9              = 0x28664,
   SPI_PS_INPUT_CNTL_10             = 0x28668,
   SPI_PS_INPUT_CNTL_11             = 0x2866C,
   SPI_PS_INPUT_CNTL_12             = 0x28670,
   SPI_PS_INPUT_CNTL_13             = 0x28674,
   SPI_PS_INPUT_CNTL_14             = 0x28678,
   SPI_PS_INPUT_CNTL_15             = 0x2867C,
   SPI_PS_INPUT_CNTL_16             = 0x28680,
   SPI_PS_INPUT_CNTL_17             = 0x28684,
   SPI_PS_INPUT_CNTL_18             = 0x28688,
   SPI_PS_INPUT_CNTL_19             = 0x2868C,
   SPI_PS_INPUT_CNTL_20             = 0x28690,
   SPI_PS_INPUT_CNTL_21             = 0x28694,
   SPI_PS_INPUT_CNTL_22             = 0x28698,
   SPI_PS_INPUT_CNTL_23             = 0x2869C,
   SPI_PS_INPUT_CNTL_24             = 0x286A0,
   SPI_PS_INPUT_CNTL_25             = 0x286A4,
   SPI_PS_INPUT_CNTL_26             = 0x286A8,
   SPI_PS_INPUT_CNTL_27             = 0x286AC,
   SPI_PS_INPUT_CNTL_28             = 0x286B0,
   SPI_PS_INPUT_CNTL_29             = 0x286B4,
   SPI_PS_INPUT_CNTL_30             = 0x286B8,
   SPI_PS_INPUT_CNTL_31             = 0x286BC,
   SPI_VS_OUT_CONFIG                = 0x286C4,
   SPI_PS_IN_CONTROL_0              = 0x286CC,
   SPI_PS_IN_CONTROL_1              = 0x286D0,
   SPI_INTERP_CONTROL_0             = 0x286D4,
   SPI_INPUT_Z                      = 0x286D8,
   SPI_FOG_CNTL                     = 0x286DC,
   SPI_FOG_FUNC_SCALE               = 0x286E0,
   SPI_FOG_FUNC_BIAS                = 0x286E4,
   CB_BLEND0_CONTROL                = 0x28780,
   CB_BLEND1_CONTROL                = 0x28784,
   CB_BLEND2_CONTROL                = 0x28788,
   CB_BLEND3_CONTROL                = 0x2878C,
   CB_BLEND4_CONTROL                = 0x28790,
   CB_BLEND5_CONTROL                = 0x28794,
   CB_BLEND6_CONTROL                = 0x28798,
   CB_BLEND7_CONTROL                = 0x2879C,
   CB_SHADER_CONTROL                = 0x287A0,
   VGT_DRAW_INITIATOR               = 0x287F0,
   VGT_DMA_BASE_HI                  = 0x287E4,
   VGT_DMA_BASE                     = 0x287E8,
   DB_DEPTH_CONTROL                 = 0x28800,
   CB_BLEND_CONTROL                 = 0x28804,
   CB_COLOR_CONTROL                 = 0x28808,
   DB_SHADER_CONTROL                = 0x2880C,
   PA_CL_CLIP_CNTL                  = 0x28810,
   PA_SU_SC_MODE_CNTL               = 0x28814,
   PA_CL_VTE_CNTL                   = 0x28818,
   PA_CL_VS_OUT_CNTL                = 0x2881C,
   PA_CL_NANINF_CNTL                = 0x28820,
   SQ_PGM_START_PS                  = 0x28840,
   SQ_PGM_SIZE_PS                   = 0x28844,
   SQ_PGM_RESOURCES_PS              = 0x28850,
   SQ_PGM_EXPORTS_PS                = 0x28854,
   SQ_PGM_START_VS                  = 0x28858,
   SQ_PGM_SIZE_VS                   = 0x2885C,
   SQ_PGM_RESOURCES_VS              = 0x28868,
   SQ_PGM_START_GS                  = 0x2886C,
   SQ_PGM_SIZE_GS                   = 0x28870,
   SQ_PGM_RESOURCES_GS              = 0x2887C,
   SQ_PGM_START_ES                  = 0x28880,
   SQ_PGM_SIZE_ES                   = 0x28884,
   SQ_PGM_RESOURCES_ES              = 0x28890,
   SQ_PGM_START_FS                  = 0x28894,
   SQ_PGM_SIZE_FS                   = 0x28898,
   SQ_PGM_RESOURCES_FS              = 0x288A4,
   SQ_ESGS_RING_ITEMSIZE            = 0x288A8,
   SQ_GSVS_RING_ITEMSIZE            = 0x288AC,
   SQ_ESTMP_RING_ITEMSIZE           = 0x288B0,
   SQ_GSTMP_RING_ITEMSIZE           = 0x288B4,
   SQ_VSTMP_RING_ITEMSIZE           = 0x288B8,
   SQ_PSTMP_RING_ITEMSIZE           = 0x288BC,
   SQ_FBUF_RING_ITEMSIZE            = 0x288C0,
   SQ_REDUC_RING_ITEMSIZE           = 0x288C4,
   SQ_GS_VERT_ITEMSIZE              = 0x288C8,
   SQ_PGM_CF_OFFSET_PS              = 0x288CC,
   SQ_PGM_CF_OFFSET_VS              = 0x288D0,
   SQ_PGM_CF_OFFSET_GS              = 0x288D4,
   SQ_PGM_CF_OFFSET_ES              = 0x288D8,
   SQ_PGM_CF_OFFSET_FS              = 0x288DC,
   SQ_VTX_SEMANTIC_CLEAR            = 0x288E0,
   SQ_ALU_CONST_CACHE_PS_0          = 0x28940,
   SQ_ALU_CONST_CACHE_PS_1          = 0x28944,
   SQ_ALU_CONST_CACHE_PS_2          = 0x28948,
   SQ_ALU_CONST_CACHE_PS_3          = 0x2894C,
   SQ_ALU_CONST_CACHE_PS_4          = 0x28950,
   SQ_ALU_CONST_CACHE_PS_5          = 0x28954,
   SQ_ALU_CONST_CACHE_PS_6          = 0x28958,
   SQ_ALU_CONST_CACHE_PS_7          = 0x2895C,
   SQ_ALU_CONST_CACHE_PS_8          = 0x28960,
   SQ_ALU_CONST_CACHE_PS_9          = 0x28964,
   SQ_ALU_CONST_CACHE_PS_10         = 0x28968,
   SQ_ALU_CONST_CACHE_PS_11         = 0x2896C,
   SQ_ALU_CONST_CACHE_PS_12         = 0x28970,
   SQ_ALU_CONST_CACHE_PS_13         = 0x28974,
   SQ_ALU_CONST_CACHE_PS_14         = 0x28978,
   SQ_ALU_CONST_CACHE_PS_15         = 0x2897C,
   SQ_ALU_CONST_CACHE_VS_0          = 0x28980,
   SQ_ALU_CONST_CACHE_VS_1          = 0x28984,
   SQ_ALU_CONST_CACHE_VS_2          = 0x28988,
   SQ_ALU_CONST_CACHE_VS_3          = 0x2898C,
   SQ_ALU_CONST_CACHE_VS_4          = 0x28990,
   SQ_ALU_CONST_CACHE_VS_5          = 0x28994,
   SQ_ALU_CONST_CACHE_VS_6          = 0x28998,
   SQ_ALU_CONST_CACHE_VS_7          = 0x2899C,
   SQ_ALU_CONST_CACHE_VS_8          = 0x289A0,
   SQ_ALU_CONST_CACHE_VS_9          = 0x289A4,
   SQ_ALU_CONST_CACHE_VS_10         = 0x289A8,
   SQ_ALU_CONST_CACHE_VS_11         = 0x289AC,
   SQ_ALU_CONST_CACHE_VS_12         = 0x289B0,
   SQ_ALU_CONST_CACHE_VS_13         = 0x289B4,
   SQ_ALU_CONST_CACHE_VS_14         = 0x289B8,
   SQ_ALU_CONST_CACHE_VS_15         = 0x289BC,
   SQ_ALU_CONST_CACHE_GS_0          = 0x289C0,
   SQ_ALU_CONST_CACHE_GS_1          = 0x289C4,
   SQ_ALU_CONST_CACHE_GS_2          = 0x289C8,
   SQ_ALU_CONST_CACHE_GS_3          = 0x289CC,
   SQ_ALU_CONST_CACHE_GS_4          = 0x289D0,
   SQ_ALU_CONST_CACHE_GS_5          = 0x289D4,
   SQ_ALU_CONST_CACHE_GS_6          = 0x289D8,
   SQ_ALU_CONST_CACHE_GS_7          = 0x289DC,
   SQ_ALU_CONST_CACHE_GS_8          = 0x289E0,
   SQ_ALU_CONST_CACHE_GS_9          = 0x289E4,
   SQ_ALU_CONST_CACHE_GS_10         = 0x289E8,
   SQ_ALU_CONST_CACHE_GS_11         = 0x289EC,
   SQ_ALU_CONST_CACHE_GS_12         = 0x289F0,
   SQ_ALU_CONST_CACHE_GS_13         = 0x289F4,
   SQ_ALU_CONST_CACHE_GS_14         = 0x289F8,
   SQ_ALU_CONST_CACHE_GS_15         = 0x289FC,
   PA_SU_POINT_SIZE                 = 0x28A00,
   PA_SU_POINT_MINMAX               = 0x28A04,
   PA_SU_LINE_CNTL                  = 0x28A08,
   PA_SC_LINE_STIPPLE               = 0x28A0C,
   VGT_OUTPUT_PATH_CNTL             = 0x28A10,
   VGT_HOS_MAX_TESS_LEVEL           = 0x28A18,
   VGT_HOS_MIN_TESS_LEVEL           = 0x28A1C,
   VGT_HOS_REUSE_DEPTH              = 0x28A20,
   VGT_GS_MODE                      = 0x28A40,
   PA_SC_MPASS_PS_CNTL              = 0x28A48,
   PA_SC_MODE_CNTL                  = 0x28A4C,
   VGT_GS_OUT_PRIM_TYPE             = 0x28A6C,
   VGT_DMA_SIZE                     = 0x28A74,
   VGT_DMA_MAX_SIZE                 = 0x28A78,
   VGT_DMA_INDEX_TYPE               = 0x28A7C,
   VGT_PRIMITIVEID_EN               = 0x28A84,
   VGT_DMA_NUM_INSTANCES            = 0x28A88,
   VGT_MULTI_PRIM_IB_RESET_EN       = 0x28A94,
   VGT_INSTANCE_STEP_RATE_0         = 0x28AA0,
   VGT_INSTANCE_STEP_RATE_1         = 0x28AA4,
   VGT_STRMOUT_EN                   = 0x28AB0,
   VGT_REUSE_OFF                    = 0x28AB4,
   VGT_VTX_CNT_EN                   = 0x28AB8,
   VGT_STRMOUT_BUFFER_SIZE_0        = 0x28AD0,
   VGT_STRMOUT_VTX_STRIDE_0         = 0x28AD4,
   VGT_STRMOUT_BUFFER_BASE_0        = 0x28AD8,
   VGT_STRMOUT_BUFFER_OFFSET_0      = 0x28ADC,
   VGT_STRMOUT_BUFFER_SIZE_1        = 0x28AE0,
   VGT_STRMOUT_VTX_STRIDE_1         = 0x28AE4,
   VGT_STRMOUT_BUFFER_BASE_1        = 0x28AE8,
   VGT_STRMOUT_BUFFER_OFFSET_1      = 0x28AEC,
   VGT_STRMOUT_BUFFER_SIZE_2        = 0x28AF0,
   VGT_STRMOUT_VTX_STRIDE_2         = 0x28AF4,
   VGT_STRMOUT_BUFFER_BASE_2        = 0x28AF8,
   VGT_STRMOUT_BUFFER_OFFSET_2      = 0x28AFC,
   VGT_STRMOUT_BUFFER_SIZE_3        = 0x28B00,
   VGT_STRMOUT_VTX_STRIDE_3         = 0x28B04,
   VGT_STRMOUT_BUFFER_BASE_3        = 0x28B08,
   VGT_STRMOUT_BUFFER_OFFSET_3      = 0x28B0C,
   VGT_STRMOUT_BASE_OFFSET_0        = 0x28B10,
   VGT_STRMOUT_BASE_OFFSET_1        = 0x28B14,
   VGT_STRMOUT_BASE_OFFSET_2        = 0x28B18,
   VGT_STRMOUT_BASE_OFFSET_3        = 0x28B1C,
   VGT_STRMOUT_BUFFER_EN            = 0x28B20,
   VGT_STRMOUT_DRAW_OPAQUE_OFFSET   = 0x28B28,
   PA_SC_LINE_CNTL                  = 0x28C00,
   PA_SU_VTX_CNTL                   = 0x28C08,
   PA_CL_GB_VERT_CLIP_ADJ           = 0x28C0C,
   PA_CL_GB_VERT_DISC_ADJ           = 0x28C10,
   PA_CL_GB_HORZ_CLIP_ADJ           = 0x28C14,
   PA_CL_GB_HORZ_DISC_ADJ           = 0x28C18,
   CB_CLRCMP_CONTROL                = 0x28C30,
   CB_CLRCMP_SRC                    = 0x28C34,
   CB_CLRCMP_DST                    = 0x28C38,
   CB_CLRCMP_MSK                    = 0x28C3C,
   PA_SC_AA_MASK                    = 0x28C48,
   VGT_VERTEX_REUSE_BLOCK_CNTL      = 0x28C58,
   VGT_OUT_DEALLOC_CNTL             = 0x28C5C,
   DB_RENDER_CONTROL                = 0x28D0C,
   DB_RENDER_OVERRIDE               = 0x28D10,
   DB_HTILE_SURFACE                 = 0x28D24,
   DB_SRESULTS_COMPARE_STATE0       = 0x28D28,
   DB_SRESULTS_COMPARE_STATE1       = 0x28D2C,
   DB_PRELOAD_CONTROL               = 0x28D30,
   DB_PREFETCH_LIMIT                = 0x28D34,
   DB_ALPHA_TO_MASK                 = 0x28D44,
   PA_SU_POLY_OFFSET_DB_FMT_CNTL    = 0x28DF8,
   PA_SU_POLY_OFFSET_CLAMP          = 0x28DFC,
   PA_SU_POLY_OFFSET_FRONT_SCALE    = 0x28E00,
   PA_SU_POLY_OFFSET_FRONT_OFFSET   = 0x28E04,
   PA_SU_POLY_OFFSET_BACK_SCALE     = 0x28E08,
   PA_SU_POLY_OFFSET_BACK_OFFSET    = 0x28E0C,
   PA_CL_POINT_X_RAD                = 0x28E10,
   PA_CL_POINT_Y_RAD                = 0x28E14,
   PA_CL_POINT_POINT_SIZE           = 0x28E18,
   PA_CL_POINT_POINT_CULL_RAD       = 0x28E1C,
   PA_CL_UCP_0_X                    = 0x28E20,
   PA_CL_UCP_0_Y                    = 0x28E24,
   PA_CL_UCP_0_Z                    = 0x28E28,
   PA_CL_UCP_0_W                    = 0x28E2C,
   // ...
   PA_CL_UCP_5_X                    = 0x28E70,
   PA_CL_UCP_5_Y                    = 0x28E74,
   PA_CL_UCP_5_Z                    = 0x28E78,
   PA_CL_UCP_5_W                    = 0x28E7C,
   ContextRegisterEnd               = 0x29000,

   // Alu Const Registers
   AluConstRegisterBase             = 0x30000,
   SQ_ALU_CONSTANT0_0               = 0x30000,
   SQ_ALU_CONSTANT1_0               = 0x30004,
   SQ_ALU_CONSTANT2_0               = 0x30008,
   SQ_ALU_CONSTANT3_0               = 0x3000C,
   // ...
   SQ_ALU_CONSTANT0_256             = 0x31000,
   SQ_ALU_CONSTANT1_256             = 0x31004,
   SQ_ALU_CONSTANT2_256             = 0x31008,
   SQ_ALU_CONSTANT3_256             = 0x3100C,
   AluConstRegisterEnd              = 0x32000,

   // Resource Registers
   ResourceRegisterBase             = 0x38000,
   SQ_RESOURCE_WORD0_0              = 0x38000,
   SQ_RESOURCE_WORD1_0              = 0x38004,
   SQ_RESOURCE_WORD2_0              = 0x38008,
   SQ_RESOURCE_WORD3_0              = 0x3800C,
   SQ_RESOURCE_WORD4_0              = 0x38010,
   SQ_RESOURCE_WORD5_0              = 0x38014,
   SQ_RESOURCE_WORD6_0              = 0x38018,
   ResourceRegisterEnd              = 0x3B678,

   // Sampler Registers
   SamplerRegisterBase              = 0x3C000,
   SQ_TEX_SAMPLER_WORD0_0           = 0x3C000,
   SQ_TEX_SAMPLER_WORD1_0           = 0x3C004,
   SQ_TEX_SAMPLER_WORD2_0           = 0x3C008,
   SamplerRegisterEnd               = 0x3C288,

   // Control Registers
   ControlRegisterBase              = 0x3CFF0,
   SQ_VTX_BASE_VTX_LOC              = 0x3CFF0,
   SQ_VTX_START_INST_LOC            = 0x3CFF4,
   ControlRegisterEnd               = 0x3CFF4, // TODO: Find real ControlRegisterEnd

   // Loop Const Registers
   LoopConstRegisterBase            = 0x3E200,
   SQ_LOOP_CONST_PS_0               = 0x3E200,
   // ...
   SQ_LOOP_CONST_PS_31              = 0x3E27C,
   SQ_LOOP_CONST_VS_0               = 0x3E280,
   // ...
   SQ_LOOP_CONST_VS_31              = 0x3E2FC,
   SQ_LOOP_CONST_GS_0               = 0x3E300,
   // ...
   SQ_LOOP_CONST_GS_31              = 0x3E37C,
   LoopConstRegisterEnd             = 0x3E380,

   // Bool Const Registers
   BoolConstRegisterBase            = 0x3E380,
   BoolConstRegisterEnd             = 0x3E380, // TODO: Find real BoolConstRegisterEnd
};
}

using Register = Register_::Value;

} // namespace latte
