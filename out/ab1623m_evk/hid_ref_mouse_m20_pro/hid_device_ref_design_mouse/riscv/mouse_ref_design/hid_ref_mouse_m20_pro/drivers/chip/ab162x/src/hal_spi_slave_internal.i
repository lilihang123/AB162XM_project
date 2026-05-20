# 0 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_spi_slave_internal.c"
# 1 "/workdir/airoha/risc-v//"
# 0 "<built-in>"
# 0 "<command-line>"
# 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_spi_slave_internal.c"
# 35 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_spi_slave_internal.c"
# 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spi_slave.h" 1
# 38 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spi_slave.h"
# 1 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h" 1
# 38 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 1
# 296 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
    typedef enum IRQn{
        SW_IRQn = 3,
        LED_IRQn = 7,
        QDEC_IRQn = 11,
        KEYSCAN_IRQn = 16,
        UART_IRQn = 17,
        SPI_MST1_IRQn = 18,
        RTC_IRQn = 19,
        GPT_IRQn = 20,
        UART_DMA_IRQn = 21,
        PMU_IRQn = 22,
        MCU_DMA_IRQn = 23,
        EINT_IRQn = 24,
        I3C0_IRQn = 25,
        I3C0_DMA_IRQn = 26,
        SPI_MST0_IRQn = 27,
        IRQ_GEN_IRQn = 28,
        USB_IRQn = 29,
        BT_IRQn = 30,
        IRQ_NUMBER_MAX
    } IRQn_Type;

    typedef IRQn_Type hal_nvic_irq_t;
# 381 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h"
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irq_gen.h" 1
# 39 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irq_gen.h"
# 1 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint.h" 1 3 4
# 11 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint.h" 3 4
# 1 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h" 1 3 4
# 34 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h" 3 4

# 34 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint-gcc.h" 3 4
typedef signed char int8_t;


typedef short int int16_t;


typedef long int int32_t;


typedef long long int int64_t;


typedef unsigned char uint8_t;


typedef short unsigned int uint16_t;


typedef long unsigned int uint32_t;


typedef long long unsigned int uint64_t;




typedef signed char int_least8_t;
typedef short int int_least16_t;
typedef long int int_least32_t;
typedef long long int int_least64_t;
typedef unsigned char uint_least8_t;
typedef short unsigned int uint_least16_t;
typedef long unsigned int uint_least32_t;
typedef long long unsigned int uint_least64_t;



typedef int int_fast8_t;
typedef int int_fast16_t;
typedef int int_fast32_t;
typedef long long int int_fast64_t;
typedef unsigned int uint_fast8_t;
typedef unsigned int uint_fast16_t;
typedef unsigned int uint_fast32_t;
typedef long long unsigned int uint_fast64_t;




typedef int intptr_t;


typedef unsigned int uintptr_t;




typedef long long int intmax_t;
typedef long long unsigned int uintmax_t;
# 12 "/workdir/airoha/risc-v/tools/toolchain/xpack-riscv-none-elf-gcc-13.2.0-2/lib/gcc/riscv-none-elf/13.2.0/include/stdint.h" 2 3 4
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irq_gen.h" 2




# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irq_gen.h"
typedef struct {
    volatile uint32_t MASK;
    volatile uint32_t SET;
    volatile uint32_t CLR;
    volatile const uint32_t STATUS;
} CCNI_REGISTER_T;
# 382 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h" 1
# 44 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t rf_hde_delsel_hv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} RF_HDE_DELSEL_HV_T;






typedef union {
    struct {
        volatile uint32_t rf_hde_delsel_lv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} RF_HDE_DELSEL_LV_T;






typedef union {
    struct {
        volatile uint32_t rf_uhde_delsel_hv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} RF_UHDE_DELSEL_HV_T;






typedef union {
    struct {
        volatile uint32_t rf_uhde_delsel_lv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} RF_UHDE_DELSEL_LV_T;






typedef union {
    struct {
        volatile uint32_t sram_hde_delsel_hv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} SRAM_HDE_DELSEL_HV_T;






typedef union {
    struct {
        volatile uint32_t sram_hde_delsel_lv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} SRAM_HDE_DELSEL_LV_T;






typedef union {
    struct {
        volatile uint32_t sram_uhde_delsel_hv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} SRAM_UHDE_DELSEL_HV_T;






typedef union {
    struct {
        volatile uint32_t sram_uhde_delsel_lv :19;
        volatile const uint32_t __reserved_00 :13;
    } field;
    volatile uint32_t word;
} SRAM_UHDE_DELSEL_LV_T;






typedef union {
    struct {
        volatile uint32_t sram_delsel_sel :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} SRAM_DELSEL_SEL_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC0_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC1 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC1_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC2 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC2_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC3 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC3_T;






typedef union {
    struct {
        volatile uint32_t SW_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} SW_MISC0_T;






typedef union {
    struct {
        volatile uint32_t BROM_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} BROM_MISC0_T;






typedef union {
    struct {
        volatile const uint32_t SYSTEM_INFO :32;
    } field;
    volatile uint32_t word;
} SYSTEM_INFOD_T;






typedef union {
    struct {
        volatile const uint32_t TOP_DEBUG_MON :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} TOP_DEBUG_MON_T;






typedef union {
    struct {
        volatile uint32_t TOP_DEBUG_CTRL :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} TOP_DEBUG_CTRL_T;






typedef union {
    struct {
        volatile uint32_t TOP_TRAP_REG_CTRL :8;
        volatile uint32_t TOP_NM_TRAP_DUMMY_MASK :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} TOP_TRAP_REG_CTRL_T;
# 293 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t sfc_slt_sel :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} SFC_SLT_SEL_T;






typedef union {
    struct {
        volatile uint32_t exit_slt_mode :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} EXIT_SLT_MODE_T;






typedef union {
    struct {
        volatile uint32_t usb_i2c_mode :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} USB_CTRL_T;






typedef union {
    struct {
        volatile uint32_t tm_ctrl :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} TM_CTRL_T;






typedef union {
    struct {
        volatile uint32_t tm_ctrl_clock_mon :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} TM_CTRL_CK_MON_T;






typedef union {
    struct {
        volatile uint32_t cr_tmbist_jtag_ctrl :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t cr_tmbist_jtag_mode :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} TMBIST_CTRL_T;
# 375 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t SFIO_CFG_WP :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_WP_T;






typedef union {
    struct {
        volatile uint32_t SFIO_CFG_CS :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_CS_T;






typedef union {
    struct {
        volatile uint32_t SFIO_CFG_CK :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_CK_T;






typedef union {
    struct {
        volatile uint32_t SFIO_CFG_IN :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_IN_T;






typedef union {
    struct {
        volatile uint32_t SFIO_CFG_OUT :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_OUT_T;






typedef union {
    struct {
        volatile uint32_t SFIO_CFG_HOLD :32;
    } field;
    volatile uint32_t word;
} SFIO_CFG_HOLD_T;






typedef union {
    struct {
        volatile const uint32_t vbus_detect_staus :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} VBUS_DET_T;






typedef union {
    struct {
        volatile uint32_t hpbuf_chop_clk100k_90deg_div_en :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t hpbuf_chop_clk100k_90deg_div_chg:1;
        volatile const uint32_t __reserved_01 :7;
        volatile uint32_t hpbuf_chop_clk100k_90deg_div_sel:11;
        volatile const uint32_t __reserved_02 :5;
    } field;
    volatile uint32_t word;
} ABB_CLK_GEN_CFG_0_T;
# 481 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t ck100k_div_en :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t ck100k_div_chg :1;
        volatile const uint32_t __reserved_01 :7;
        volatile uint32_t ck100k_div_sel :11;
        volatile const uint32_t __reserved_02 :5;
    } field;
    volatile uint32_t word;
} ABB_CLK_GEN_CFG_1_T;
# 502 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile const uint32_t hpbuf_chop_clk100k_90deg_div_rdy:1;
        volatile const uint32_t __reserved_00 :7;
        volatile const uint32_t ck100k_div_rdy :1;
        volatile const uint32_t __reserved_01 :7;
        volatile uint32_t hpbuf_chop_clk100k_90deg_div_swrst:1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t ck100k_div_swrst :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} ABB_CLK_GEN_CFG_2_T;
# 527 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t aud01adc_test_sel :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t aud23adc_test_sel :1;
        volatile const uint32_t __reserved_01 :7;
        volatile uint32_t dbg_clk_out_en :1;
        volatile const uint32_t __reserved_02 :15;
    } field;
    volatile uint32_t word;
} ABB_CLK_GEN_CFG_3_T;
# 548 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t SPI_BYPASS_EN :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t SPI_BYPASS_MST_SEL :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SPI_BYPASS_CS_EN :4;
        volatile const uint32_t __reserved_02 :4;
        volatile uint32_t SPI_BYPASS_OE :4;
        volatile const uint32_t __reserved_03 :4;
    } field;
    volatile uint32_t word;
} SPI_BYPASS_T;
# 573 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t sw_irq_0_trig :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t sw_irq_0_sta :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SW_IRQ_0_T;
# 590 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t sw_irq_1_trig :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t sw_irq_1_sta :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SW_IRQ_1_T;







typedef struct {
    RF_HDE_DELSEL_HV_T rf_hde_delsel_hv;
    RF_HDE_DELSEL_LV_T rf_hde_delsel_lv;
    RF_UHDE_DELSEL_HV_T rf_uhde_delsel_hv;
    RF_UHDE_DELSEL_LV_T rf_uhde_delsel_lv;
    SRAM_HDE_DELSEL_HV_T sram_hde_delsel_hv;
    SRAM_HDE_DELSEL_LV_T sram_hde_delsel_lv;
    SRAM_UHDE_DELSEL_HV_T sram_uhde_delsel_hv;
    SRAM_UHDE_DELSEL_LV_T sram_uhde_delsel_lv;
    SRAM_DELSEL_SEL_T sram_delsel_sel;
    uint32_t __reserved_00[3];
    HW_MISC0_T hw_misc0;
    HW_MISC1_T hw_misc1;
    HW_MISC2_T hw_misc2;
    HW_MISC3_T hw_misc3;
    SW_MISC0_T sw_misc0;
    BROM_MISC0_T brom_misc0;
    uint32_t __reserved_01[46];
    SYSTEM_INFOD_T system_infod;
    TOP_DEBUG_MON_T top_debug_mon;
    TOP_DEBUG_CTRL_T top_debug_ctrl;
    TOP_TRAP_REG_CTRL_T top_trap_reg_ctrl;
    SFC_SLT_SEL_T sfc_slt_sel;
    EXIT_SLT_MODE_T exit_slt_mode;
    USB_CTRL_T usb_ctrl;
    uint32_t __reserved_02[1];
    TM_CTRL_T tm_ctrl;
    TM_CTRL_CK_MON_T tm_ctrl_ck_mon;
    TMBIST_CTRL_T tmbist_ctrl;
    uint32_t __reserved_03[53];
    SFIO_CFG_WP_T sfio_cfg_wp;
    SFIO_CFG_CS_T sfio_cfg_cs;
    SFIO_CFG_CK_T sfio_cfg_ck;
    SFIO_CFG_IN_T sfio_cfg_in;
    SFIO_CFG_OUT_T sfio_cfg_out;
    SFIO_CFG_HOLD_T sfio_cfg_hold;
    uint32_t __reserved_04[58];
    VBUS_DET_T vbus_det;
    uint32_t __reserved_05[63];
    ABB_CLK_GEN_CFG_0_T abb_clk_gen_cfg_0;
    ABB_CLK_GEN_CFG_1_T abb_clk_gen_cfg_1;
    ABB_CLK_GEN_CFG_2_T abb_clk_gen_cfg_2;
    ABB_CLK_GEN_CFG_3_T abb_clk_gen_cfg_3;
    uint32_t __reserved_06[60];
    SPI_BYPASS_T spi_bypass;
    uint32_t __reserved_07[63];
    SW_IRQ_0_T sw_irq_0;
    SW_IRQ_1_T sw_irq_1;
} TOP_MISC_CFG_REGISTER_T;





typedef union {
    struct {
        volatile uint32_t HW_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC1_0_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC1 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC1_1_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC2 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC1_2_T;






typedef union {
    struct {
        volatile uint32_t HW_MISC3 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} HW_MISC1_3_T;






typedef union {
    struct {
        volatile uint32_t SW_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} SW_MISC1_0_T;






typedef union {
    struct {
        volatile uint32_t BROM_MISC0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} BROM_MISC1_0_T;






typedef union {
    struct {
        volatile uint32_t sw_irq1_0_trig :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t sw_irq1_0_sta :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SW_IRQ1_0_T;
# 755 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t sw_irq1_1_trig :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t sw_irq1_1_sta :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SW_IRQ1_1_T;







typedef struct {
    uint32_t __reserved_00[12];
    HW_MISC1_0_T hw_misc1_0;
    HW_MISC1_1_T hw_misc1_1;
    HW_MISC1_2_T hw_misc1_2;
    HW_MISC1_3_T hw_misc1_3;
    SW_MISC1_0_T sw_misc1_0;
    BROM_MISC1_0_T brom_misc1_0;
    uint32_t __reserved_01[366];
    SW_IRQ1_0_T sw_irq1_0;
    SW_IRQ1_1_T sw_irq1_1;
} TOP_MISC_CFG_1_REGISTER_T;





typedef union {
    struct {
        volatile uint32_t RG_ABB_RSV18 :8;
        volatile uint32_t RG_ABB_RSV33 :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_ABB_TOP_0_T;
# 804 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDPREAMPLON :1;
        volatile uint32_t RG_AUD_ACC_EN :1;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t RG_AUDPREAMPLPGATEST :1;
        volatile uint32_t RG_AUDPREAMP_LP_RSV :2;
        volatile uint32_t RG_AUDPREAMPLINPUTSEL :2;
        volatile uint32_t RG_AUDPREAMPLGAIN :4;
        volatile uint32_t RG_AUDADCLPWRUP :1;
        volatile uint32_t RG_AUDADCLINPUTSEL :2;
        volatile uint32_t RG_AUDPGA_ACC20K_EN :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_0_T;
# 842 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDULHALFBIAS :1;
        volatile uint32_t RG_AUDPREAMPLP1EN :1;
        volatile uint32_t RG_IPB_LP_EN :1;
        volatile uint32_t RG_AUDADC1STSTAGELPEN :1;
        volatile uint32_t RG_AUDADC2NDSTAGELPEN :1;
        volatile uint32_t RG_EN_FLASHLOWLEVEL :1;
        volatile uint32_t RG_AUDPREAMPIDDTEST :2;
        volatile uint32_t RG_AUDADC1STSTAGEIDDTEST :2;
        volatile uint32_t RG_AUDADC2NDSTAGEIDDTEST :2;
        volatile uint32_t RG_AUDADCREFBUFIDDTEST :2;
        volatile uint32_t RG_AUDADCFLASHIDDTEST :2;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_1_T;
# 885 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDADCCLKSEL :2;
        volatile uint32_t RG_AUDADCCLKSOURCE :2;
        volatile uint32_t RG_AUDADC_16MCK_EN :1;
        volatile uint32_t RG_AUDADCDAC0P25FS :1;
        volatile uint32_t RG_AUDPGAL_ACCFS :1;
        volatile uint32_t RG_AUDPREAMP_LOWPEN1 :1;
        volatile uint32_t RG_AUDPREAMP_LOWPEN2 :1;
        volatile uint32_t RG_AUDPREAMP_LOWPEN_ORIGIN :1;
        volatile uint32_t RG_AUDPREAMP_IN_IMP_EN :2;
        volatile uint32_t RG_AUDPREAMP_CM_IMP_EN :2;
        volatile uint32_t RG_AUDADC1STSTAGESDENB :1;
        volatile uint32_t RG_AUDADC2NDSTAGERESET :1;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_2_T;
# 931 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDADC3RDSTAGERESET :1;
        volatile uint32_t RG_AUDADCFSRESET :1;
        volatile uint32_t RG_AUDADCWIDECM :1;
        volatile uint32_t RG_AUDADCNOPATEST :1;
        volatile uint32_t RG_AUD01ADCBYPASS :1;
        volatile uint32_t RG_AUDADCFFBYPASS :1;
        volatile uint32_t RG_AUDADCDACFBCURRENT :1;
        volatile uint32_t RG_AUDADCDACIDDTEST :2;
        volatile uint32_t RG_AUDADCDACNRZ :1;
        volatile uint32_t RG_AUDADCNODEM :1;
        volatile uint32_t RG_AUDADCDACTEST :1;
        volatile uint32_t RG_AUDPREAMP_THD :4;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_3_T;
# 977 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDADCTESTDATA :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_4_T;






typedef union {
    struct {
        volatile uint32_t RG_AUDRCTUNEL :5;
        volatile uint32_t RG_AUDRCTUNELSEL :1;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RG_AUDADCSYNCCLK_INV :1;
        volatile uint32_t RG_AUDADCCLKRATEQUARTER :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_5_T;
# 1013 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDADCCLKHALFRST :1;
        volatile uint32_t RG_AUDADCCLKRATEHALF :1;
        volatile uint32_t RG_EN_VREF0P9 :1;
        volatile uint32_t RG_CM_REFGENSEL :1;
        volatile uint32_t RG_AUDADC_FROM_GPIO :1;
        volatile uint32_t RG_DCCVCMBUFLPMODSEL :1;
        volatile uint32_t RG_DCCVCMBUFLPSWEN :1;
        volatile uint32_t RG_CM01STBENH :1;
        volatile uint32_t RG_AUDSPAREVA25 :4;
        volatile uint32_t RG_AUDSPAREVA12 :4;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_6_T;
# 1053 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AUDENCSPAREVA25 :8;
        volatile uint32_t RG_AUDENCSPAREVA12 :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_7_T;
# 1069 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_LCLDO_ENC_EN :1;
        volatile uint32_t RG_LCLDO_PDDIS_EN :1;
        volatile uint32_t RG_LCLDO_TBST_EN :1;
        volatile uint32_t RG_LCLDO_ENC_REMOTE_SENSE :1;
        volatile uint32_t RG_LCLDO_PDD_TEST :1;
        volatile const uint32_t __reserved_00 :27;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_8_T;
# 1094 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_UL_ATST :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_9_T;






typedef union {
    struct {
        volatile uint32_t RG_AIO_R_MODE_EN :1;
        volatile uint32_t RG_AIO_SC_MODE_EN :1;
        volatile uint32_t RG_MIC_MODE_EN :1;
        volatile uint32_t RG_AIO_DIFF_EN :1;
        volatile uint32_t RG_AIO_RIN_SEL :2;
        volatile uint32_t RG_AIO_RTEMP_SEL :2;
        volatile uint32_t RG_PGA_CHOP_EN :1;
        volatile uint32_t RG_AIO_RTB_SHORT_EN :1;
        volatile uint32_t RG_AIO_MUX_INTERNAL_EN :1;
        volatile uint32_t RG_AIO_SC_C_SEL :5;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_11_T;
# 1147 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AIO_MUX_INTERNAL :4;
        volatile uint32_t RG_AIO_VIN_BUF_EN :1;
        volatile uint32_t RG_AIO_RTB_SEL :7;
        volatile uint32_t RG_AIO_VIN_BUF_RSEL :4;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_12_T;
# 1169 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AIO_SC_CLK_DIV :4;
        volatile uint32_t RG_AIO_RVCMI_EN :1;
        volatile uint32_t RG_AIO_TB_BUF_EN :1;
        volatile uint32_t RG_AIO_SC_CVCMI_EN :1;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t RG_AIO_TB_BUF_RSEL :4;
        volatile uint32_t RG_AIO_VINBUF_ATST_EN :1;
        volatile uint32_t RG_AIO_TBBUF_ATST_EN :1;
        volatile const uint32_t __reserved_01 :18;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_13_T;
# 1201 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_PGA_CM_EN :2;
        volatile uint32_t RG_PGA_RM_EN :2;
        volatile const uint32_t __reserved_00 :28;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_14_T;
# 1217 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_AIO_RSV :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_15_T;






typedef union {
    struct {
        volatile const uint32_t RGS_AUDRCTUNEREAD :5;
        volatile const uint32_t __reserved_00 :27;
    } field;
    volatile uint32_t word;
} RG_AUENC_CON_16_T;






typedef union {
    struct {
        volatile uint32_t RG_TEMP_BGR_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_TEMP_CK200K_BGR_CHOP_EN :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t RG_TEMP_BGR_R1_SEL :3;
        volatile const uint32_t __reserved_02 :1;
        volatile uint32_t RG_TEMP_BGR_RE0_SEL :3;
        volatile const uint32_t __reserved_03 :17;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_0_T;
# 1268 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_TEMP_VREF_AIO_SEL :5;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_TEMP_VBG1P0V_COMP_SEL :5;
        volatile const uint32_t __reserved_01 :19;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_1_T;
# 1285 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_TEMP_VBG0P6V_AUD_SEL :5;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_TEMP_VBG0P8V_AUD_SEL :5;
        volatile const uint32_t __reserved_01 :19;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_2_T;
# 1302 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_TEMP_TS_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_TEMP_TS_PTAT_ONLY :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t RG_TEMP_TS_CTAT_SEL :2;
        volatile const uint32_t __reserved_02 :2;
        volatile uint32_t RG_TEMP_TS_PTAT_SEL :2;
        volatile const uint32_t __reserved_03 :18;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_3_T;
# 1327 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_TEMP_ATST_SEL :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t RG_TEMP_RSV0 :8;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_4_T;
# 1344 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_TEMP_GLBV2I_PWRUP :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_TEMP_GLBV2I_RSEL :3;
        volatile const uint32_t __reserved_01 :1;
        volatile uint32_t RG_TEMP_GLBV2I_SELFBIAS_RSEL :3;
        volatile const uint32_t __reserved_02 :21;
    } field;
    volatile uint32_t word;
} RG_TENSOR_CON_5_T;
# 1365 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CP2_OP_EN :1;
        volatile uint32_t RG_CP2_UGB_EN :1;
        volatile uint32_t RG_CP2_IREF_SEL :1;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t RG_CP2_LP_ISEL :2;
        volatile const uint32_t __reserved_01 :2;
        volatile uint32_t RG_CP2_AT_ISEL :3;
        volatile const uint32_t __reserved_02 :1;
        volatile uint32_t RG_CP2_ACTIVE_MODE_EN :1;
        volatile const uint32_t __reserved_03 :19;
    } field;
    volatile uint32_t word;
} RG_COMP_CON_0_T;
# 1396 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CP2_MODE :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_CP2_EXTREFSEL :4;
        volatile uint32_t RG_CP2_HYST_EN :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t RG_CP2_HYST_SEL :3;
        volatile const uint32_t __reserved_02 :17;
    } field;
    volatile uint32_t word;
} RG_COMP_CON_1_T;
# 1420 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CP2_PSEL :4;
        volatile uint32_t RG_CP2_REFSEL :2;
        volatile const uint32_t __reserved_00 :2;
        volatile uint32_t RG_CP2_RL_REFSEL :2;
        volatile const uint32_t __reserved_01 :22;
    } field;
    volatile uint32_t word;
} RG_COMP_CON_2_T;
# 1440 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CP2_THDOWN :6;
        volatile const uint32_t __reserved_00 :2;
        volatile uint32_t RG_CP2_THUP :6;
        volatile const uint32_t __reserved_01 :18;
    } field;
    volatile uint32_t word;
} RG_COMP_CON_3_T;
# 1457 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CP_ATST_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_CP_ATST_SEL :2;
        volatile const uint32_t __reserved_01 :2;
        volatile uint32_t RG_CP_RSV :8;
        volatile const uint32_t __reserved_02 :16;
    } field;
    volatile uint32_t word;
} RG_COMP_CON_4_T;
# 1478 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_ATST1_BUF_BIAS_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_ATST1_BUF_ISEL :2;
        volatile const uint32_t __reserved_01 :2;
        volatile uint32_t RG_ATST1_EN :1;
        volatile uint32_t RG_ATST1_BUF_NIN_EN :1;
        volatile uint32_t RG_ATST1_BUF_PIN_EN :1;
        volatile const uint32_t __reserved_02 :1;
        volatile uint32_t RG_ATST1_SEL :3;
        volatile const uint32_t __reserved_03 :17;
    } field;
    volatile uint32_t word;
} RG_ATST_CON_0_T;
# 1509 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_ATST2_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_ATST2_SEL :3;
        volatile const uint32_t __reserved_01 :1;
        volatile uint32_t RG_ATST_RSV :2;
        volatile const uint32_t __reserved_02 :22;
    } field;
    volatile uint32_t word;
} RG_ATST_CON_1_T;
# 1530 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CKGEN_AUDADC_CK_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_CKGEN_AUDADC_CKDIV_RSTB :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t RG_CKGEN_AUDADC_CKINV_SEL :1;
        volatile const uint32_t __reserved_02 :3;
        volatile uint32_t RG_CKGEN_AUDADC_CKDIV_SEL :2;
        volatile const uint32_t __reserved_03 :18;
    } field;
    volatile uint32_t word;
} RG_CKGEN_CON_0_T;
# 1555 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef union {
    struct {
        volatile uint32_t RG_CKGEN_LSCK_EN :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t RG_CKGEN_LSCK_DIV_RSTB :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t RG_CKGEN_BGR_CK_EN :1;
        volatile uint32_t RG_CKGEN_BGR_CLK_SEL :1;
        volatile uint32_t RG_CKGEN_BGR_CK_SEL :2;
        volatile uint32_t RG_CKGEN_AIO_CK_EN :1;
        volatile uint32_t RG_CKGEN_AIO_CLK_SEL :1;
        volatile uint32_t RG_CKGEN_AIO_CK_SEL :2;
        volatile const uint32_t __reserved_02 :16;
    } field;
    volatile uint32_t word;
} RG_CKGEN_CON_1_T;
# 1590 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_misc_cfg.h"
typedef struct {
    RG_ABB_TOP_0_T rg_abb_top_0;
    RG_AUENC_CON_0_T rg_auenc_con_0;
    RG_AUENC_CON_1_T rg_auenc_con_1;
    RG_AUENC_CON_2_T rg_auenc_con_2;
    RG_AUENC_CON_3_T rg_auenc_con_3;
    RG_AUENC_CON_4_T rg_auenc_con_4;
    RG_AUENC_CON_5_T rg_auenc_con_5;
    RG_AUENC_CON_6_T rg_auenc_con_6;
    RG_AUENC_CON_7_T rg_auenc_con_7;
    RG_AUENC_CON_8_T rg_auenc_con_8;
    RG_AUENC_CON_9_T rg_auenc_con_9;
    uint32_t __reserved_00[1];
    RG_AUENC_CON_11_T rg_auenc_con_11;
    RG_AUENC_CON_12_T rg_auenc_con_12;
    RG_AUENC_CON_13_T rg_auenc_con_13;
    RG_AUENC_CON_14_T rg_auenc_con_14;
    RG_AUENC_CON_15_T rg_auenc_con_15;
    RG_AUENC_CON_16_T rg_auenc_con_16;
    RG_TENSOR_CON_0_T rg_tensor_con_0;
    RG_TENSOR_CON_1_T rg_tensor_con_1;
    RG_TENSOR_CON_2_T rg_tensor_con_2;
    RG_TENSOR_CON_3_T rg_tensor_con_3;
    RG_TENSOR_CON_4_T rg_tensor_con_4;
    RG_TENSOR_CON_5_T rg_tensor_con_5;
    RG_COMP_CON_0_T rg_comp_con_0;
    RG_COMP_CON_1_T rg_comp_con_1;
    RG_COMP_CON_2_T rg_comp_con_2;
    RG_COMP_CON_3_T rg_comp_con_3;
    RG_COMP_CON_4_T rg_comp_con_4;
    RG_ATST_CON_0_T rg_atst_con_0;
    RG_ATST_CON_1_T rg_atst_con_1;
    RG_CKGEN_CON_0_T rg_ckgen_con_0;
    RG_CKGEN_CON_1_T rg_ckgen_con_1;
} ABB_CFG_REGISTER_T;




typedef union {
    struct {
        volatile uint32_t CM33_BOOT_VECTOR0 :32;
    } field;
    volatile uint32_t word;
} CMCFG_BOOT_VECTOR0_T;






typedef union {
    struct {
        volatile uint32_t CM33_BOOT_VECTOR1 :32;
    } field;
    volatile uint32_t word;
} CMCFG_BOOT_VECTOR1_T;






typedef union {
    struct {
        volatile uint32_t CM33_BOOT_FROM_SLV :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} CMCFG_BOOT_FROM_SLV_T;






typedef union {
    struct {
        volatile uint32_t RISCV_BOOT_VECTOR :32;
    } field;
    volatile uint32_t word;
} RISCV_CFG_BOOT_VECTOR_T;






typedef union {
    struct {
        volatile uint32_t RISCV_BOOT_VECTOR_SELECT :2;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} RISCV_CFG_BOOT_VECTOR_SELECT_T;






typedef union {
    struct {
        volatile const uint32_t RISCV_DEEP_SLEEP :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} RISCV_DEEP_SLEEP_T;






typedef union {
    struct {
        volatile const uint32_t RISCV_PC :32;
    } field;
    volatile uint32_t word;
} RISCV_PC_T;






typedef union {
    struct {
        volatile uint32_t DUMMY_RW :32;
    } field;
    volatile uint32_t word;
} DUMMY_RW_T;






typedef union {
    struct {
        volatile const uint32_t DUMMY_RO :32;
    } field;
    volatile uint32_t word;
} DUMMY_RO_T;





typedef struct {
    CMCFG_BOOT_VECTOR0_T cmcfg_boot_vector0;
    CMCFG_BOOT_VECTOR1_T cmcfg_boot_vector1;
    CMCFG_BOOT_FROM_SLV_T cmcfg_boot_from_slv;
    uint32_t __reserved_00[1];
    RISCV_CFG_BOOT_VECTOR_T riscv_cfg_boot_vector;
    RISCV_CFG_BOOT_VECTOR_SELECT_T riscv_cfg_boot_vector_select;
    RISCV_DEEP_SLEEP_T riscv_deep_sleep;
    RISCV_PC_T riscv_pc;
    DUMMY_RW_T dummy_rw;
    DUMMY_RO_T dummy_ro;
} MCU_CFG_PRI_REGISTER_T;
# 383 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_smph.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_smph.h"
typedef struct {
    volatile uint32_t ch_lock;
    volatile uint32_t ch_release;
    volatile const uint32_t __reserved_00[62];
} SMPH_CH_T;

typedef struct {
    volatile const uint32_t ch_status[3];
    volatile const uint32_t __reserved_00[1];
    volatile const uint32_t global_status;
    volatile const uint32_t __reserved_01[59];
         SMPH_CH_T channels[3];
} SMPH_REGISTER_T;
# 384 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_uart.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_uart.h"
typedef struct {
    union {
        struct {
            volatile uint8_t SW_FLOW_CONT;
            volatile uint8_t HW_FLOW_CONT;
            volatile uint8_t SEND_XOFF;
            volatile uint8_t SEND_XON;
        } EFR_CELLS;
        volatile uint32_t EFR;
    } EFR_UNION;

    union {
        struct {
            volatile uint8_t XOFF;
            volatile uint8_t XON;
            volatile const uint8_t RESERVED[2];
        } XON_XOFF_CELLS;
        volatile uint32_t XON_XOFF;
    } XON_XOFF_UNION;

    union {
        struct {
            volatile uint8_t ESCAPE_CHAR;
            volatile uint8_t ESCAPE_EN;
            volatile const uint8_t RESERVED[2];
        } ESCAPE_REG_CELLS;
        volatile uint32_t ESCAPE_REG;
    } ESCAPE_REG_UNION;

    union {
        struct {
            volatile uint8_t SLEEP_IDLE_FC_EN;
            volatile uint8_t SLEEP_SEND_XOFF_RTS_EN;
            volatile uint8_t SLEEP_FC_EN;
            volatile const uint8_t RESERVED[1];
        } SLEEP_REG_CELLS;
        volatile uint32_t SLEEP_REG;
    } SLEEP_REG_UNION;

    union {
        struct {
            volatile uint8_t AUTOBAUD_EN;
            volatile uint8_t AUTOBAUD_SEL;
            volatile uint8_t AUTOBAUD_SLEEP_ACK;
            volatile const uint8_t RESERVED;
        } AUTOBAUD_CON_CELLS;
        volatile uint32_t AUTOBAUD_CON;
    } AUTOBAUD_CON_UNION;

    union {
        struct {
            volatile uint8_t AUTOBAUD_SAMPLE;
            volatile uint8_t AUTOBAUD_RATEFIX;
            volatile uint8_t RATEFIX;
            volatile const uint8_t RESERVED;
        } RATEFIX_CELLS;
        volatile uint32_t RATEFIX;
    } RATEFIX_UNION;

    union {
        struct {
            volatile const uint8_t AUTOBAUD_RATE;
            volatile const uint8_t AUTOBAUD_STAT;
            volatile const uint8_t RESERVED[2];
        } AUTOBAUD_REG_CELLS;
        volatile const uint32_t AUTOBAUD_REG;
    } AUTOBAUD_REG_UNION;

    volatile uint32_t DLM_DLL;

    union {
        struct {
            volatile uint8_t SPEED;
            volatile const uint8_t RESERVED[1];
            volatile uint8_t SAMPLE_COUNT;
            volatile uint8_t SAMPLE_POINT;
        } SAMPLE_REG_CELLS;
        volatile uint32_t SAMPLE_REG;
    } SAMPLE_REG_UNION;

    volatile uint32_t FRACDIV;

    union {
        struct {
            volatile uint8_t RX_DMA_EN;
            volatile uint8_t TX_DMA_EN;
            volatile uint8_t FIFO_LSR_SEL;
            volatile uint8_t CLR_DMA_MODE_TO;
        } DMA_CON_CELLS;
        volatile uint32_t DMA_CON;
    } DMA_CON_UNION;

    union {
        struct {
            volatile uint8_t FIFOE;
            volatile uint8_t RFTL_TFTL;
            volatile uint8_t CLRR;
            volatile uint8_t CLRT;
        } FCR_CELLS;
        volatile uint32_t FCR;
    } FCR_UNION;

    volatile uint32_t RXTRIG;

    union {
        struct {
            volatile uint8_t PAR_STB_WLS;
            volatile uint8_t SB;
            volatile uint8_t GUARD;
            volatile const uint8_t RESERVED[1];
        } LCR_CELLS;
        volatile uint32_t LCR;
    } LCR_UNION;

    union {
        struct {
            volatile uint8_t RX_TO_MODE;
            volatile uint8_t TO_CNT_AUTORST;
            volatile uint8_t FC_TOC_DIS;
            volatile const uint8_t RESERVED[1];
        } RX_TO_CON_CELLS;
        volatile uint32_t RX_TO_CON;
    } RX_TO_CON_UNION;

    volatile uint32_t RX_TOC_DEST;

    union {
        struct {
            volatile uint8_t ETSEI_ETBEI;
            volatile uint8_t ELSI_ERBFI;
            volatile uint8_t DETCI_XOFFI;
            volatile uint8_t CTSI_RTSI;
        } IER_CELLS;
        volatile uint32_t IER;
    } IER_UNION;

    volatile uint32_t DETC;

    volatile const uint32_t RBR;

    volatile uint32_t THR;

    volatile const uint32_t IIR;

    union {
        struct {
            volatile uint8_t RTS;
            volatile uint8_t LOOP;
            volatile const uint8_t XOFF_STATUS;
            volatile uint8_t XOFF_CLEAR;
        } MCR_CELLS;
        volatile uint32_t MCR;
    } MCR_UNION;

    volatile const uint32_t LSR;

    volatile uint32_t SCR;
# 212 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_uart.h"
} UART_REGISTER_T;
# 385 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_usb.h" 1
# 386 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_sfc.h" 1
# 46 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_sfc.h"
typedef struct {
    volatile uint32_t RW_SF_MAC_CTL;
    volatile uint32_t RW_SF_DIRECT_CTL;
    volatile uint32_t RW_SF_MISC_CTL;
    volatile uint32_t RW_SF_MISC_CTL2;
    volatile uint32_t RW_SF_MAC_OUTL;
    volatile uint32_t RW_SF_MAC_INL;
    volatile uint32_t RW_SF_RESET_CTL;
    volatile uint32_t RW_SF_STA2_CTL;
    volatile uint32_t RW_SF_DLY_CTL1;
    volatile uint32_t RW_SF_DLY_CTL2;
    volatile uint32_t RW_SF_DLY_CTL3;
    volatile uint32_t RW_SF_DUMMY1;
    volatile uint32_t RW_SF_DLY_CTL4;
    volatile uint32_t RW_SF_DLY_CTL5;
    volatile uint32_t RW_SF_DLY_CTL6;
    volatile uint32_t RW_SF_DUMMY2;
    volatile uint32_t RW_SF_DIRECT_CTL2;
    volatile uint32_t RW_SF_MISC_CTL3;
    volatile uint32_t RW_SF_STA3;
    volatile const uint32_t __RESERVED_1[13];
    volatile uint32_t RW_SF_CHECK_PERF;
    volatile const uint32_t __RESERVED_2[44];
    volatile const uint32_t RW_SF_PERF_MONITOR[3];
} SFC_REGISTER_T;

typedef struct {
    volatile uint32_t RW_SF_GPRAM_DATA;
    volatile uint32_t RW_SF_GPRAM_DATA_OF_4;
} SFC_GPRAM_REGISTER_T;
# 387 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_esc.h" 1
# 44 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_esc.h"
typedef struct {
    volatile uint32_t ESC_MAC_CTL;
    volatile uint32_t ESC_DIRECT_CTL;
    volatile uint32_t ESC_MISC_CTL1;
    volatile uint32_t ESC_MISC_CTL2;
    volatile uint32_t ESC_MAC_OUTL;
    volatile uint32_t ESC_MAC_INL;
    volatile uint32_t ESC_STA1_CTL;
    volatile uint32_t ESC_STA2_CTL;
    volatile uint32_t ESC_DLY_CTL1;
    volatile uint32_t ESC_DLY_CTL2;
    volatile uint32_t ESC_DLY_CTL3;
    volatile uint32_t reserve0[1];
    volatile uint32_t ESC_DMY_BYTE;
    volatile uint32_t reserve1[5];
    volatile uint32_t ESC_STA3;
    volatile uint32_t reserve2[5];
    volatile uint32_t ESC_DEBUG_1;
    volatile uint32_t ESC_DEBUG_2;
    volatile uint32_t reserve3[2];
    volatile uint32_t ESC_DEBUG_MUX;
    volatile uint32_t reserve4[3];
    volatile uint32_t ESC_MISC_CTL3;
    volatile uint32_t ESC_MAC_IRQ;
} ESC_REGISTER_T;
# 388 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h" 1
# 48 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef struct {
    volatile const uint32_t GLB_STA;
    volatile const uint32_t GLB_STA2;
    volatile const uint32_t GLB_CPU0_CFG;
    volatile uint32_t GLB_CPU0_SET;
    volatile uint32_t GLB_CPU0_CLR;
    volatile const uint32_t GLB_CPU1_CFG;
    volatile uint32_t GLB_CPU1_SET;
    volatile uint32_t GLB_CPU1_CLR;
    volatile const uint32_t __RESERVED_1[13];
    volatile const uint32_t GLB_CPU2_CFG;
    volatile uint32_t GLB_CPU2_SET;
    volatile uint32_t GLB_CPU2_CLR;
    volatile const uint32_t __RESERVED_2[2];
    volatile const uint32_t GLB_CPU3_CFG;
    volatile uint32_t GLB_CPU3_SET;
    volatile uint32_t GLB_CPU3_CLR;
} GDMA_0_REG_T;

typedef struct {
    volatile const uint32_t RG_GLB_STA;
    volatile uint32_t RESERVE1[1];
    volatile const uint32_t RG_GLB_CPU0_INT_CFG;
    volatile uint32_t RG_GLB_CPU0_INT_SET;
    volatile uint32_t RG_GLB_CPU0_INT_CLR;
    volatile const uint32_t RG_GLB_CPU1_INT_CFG;
    volatile uint32_t RG_GLB_CPU1_INT_SET;
    volatile uint32_t RG_GLB_CPU1_INT_CLR;
    volatile const uint32_t RG_GLB_SWRST;
    volatile uint32_t RESERVE2[1];
    volatile const uint32_t RG_GLB_LIMITER;
    volatile uint32_t RESERVE3[5];
    volatile const uint32_t RG_GLB_BUSY;
    volatile const uint32_t RG_GLB_INTR;
    volatile uint32_t RESERVE4[2];
    volatile const uint32_t RG_GLB_CPU2_INT_CFG;
    volatile uint32_t RG_GLB_CPU2_INT_SET;
    volatile uint32_t RG_GLB_CPU2_INT_CLR;
    volatile uint32_t RESERVE5[1];
    volatile const uint32_t RG_GLB_CPU3_INT_CFG;
    volatile uint32_t RG_GLB_CPU3_INT_SET;
    volatile uint32_t RG_GLB_CPU3_INT_CLR;
    volatile uint32_t RESERVE6[1];
    volatile const uint32_t RG_GLB_CLK_CFG;
    volatile uint32_t RG_GLB_CLK_SET;
    volatile uint32_t RG_GLB_CLK_CLR;
} DMA_REGISTER_GLOABL_T;


typedef struct {
    volatile uint32_t GDMA_SRC;
    volatile uint32_t GDMA_DST;
    volatile uint32_t GDMA_WPPT;
    volatile uint32_t GDMA_WPTO;
    volatile uint32_t GDMA_COUNT;
    union {
        struct {
            volatile uint8_t GDMA_DIRECTION ;
            volatile uint8_t GDMA_SIZE;
            volatile uint8_t GDMA_SETTING;
            volatile uint8_t GDMA_ITEN;
        } GDMA_CON_CELLS;
        volatile uint32_t GDMA_CON;
    } GDMA_CON_UNION;
    volatile uint32_t GDMA_START;
    volatile uint32_t GDMA_INTSTA;
    volatile uint32_t GDMA_ACKINT;
    volatile const uint32_t GDMA_RLCT;
    volatile uint32_t GDMA_LIMITER;
} GDMA_REGISTER_T;
# 169 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU0_CFG_TX :1;
        volatile uint32_t CPU0_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU0_CFG_T;
# 185 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU1_CFG_TX :1;
        volatile uint32_t CPU1_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU1_CFG_T;
# 201 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile const uint32_t CLK_CFG_TX :1;
        volatile const uint32_t CLK_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CLK_CFG_T;
# 217 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t COUNT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} PDMA_COUNT_T;






typedef union {
    struct {
# 249 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
        volatile uint32_t DIRECTION :5;
        volatile const uint32_t __reserved_00 :3;




        volatile uint32_t SIZE :2;
        volatile const uint32_t __reserved_01 :6;
# 269 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
        volatile uint32_t SETTING :4;
        volatile const uint32_t __reserved_02 :4;
        volatile uint32_t ITEN :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} PDMA_CON_T;
# 316 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t PGMADDR :32;
    } field;
    volatile uint32_t word;
} PDMA_PGMADDR_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile uint32_t STR :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} PDMA_START_T;






typedef union {
    struct {
        volatile const uint32_t RUN_TX :1;
        volatile const uint32_t IT_TX :1;
        volatile const uint32_t RUN_RX :1;
        volatile const uint32_t IT_RX :1;
        volatile const uint32_t __reserved_00 :28;
    } field;
    volatile uint32_t word;
} DMA_GLBSTA_T;
# 364 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU0_SET_TX :1;
        volatile uint32_t CPU0_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU0_SET_T;
# 380 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU0_CLR_TX :1;
        volatile uint32_t CPU0_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU0_CLR_T;
# 396 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU1_SET_TX :1;
        volatile uint32_t CPU1_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU1_SET_T;
# 412 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CPU1_CLR_TX :1;
        volatile uint32_t CPU1_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CPU1_CLR_T;
# 428 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile const uint32_t SW_RESET :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} DMA_GLB_SWRST_T;






typedef union {
    struct {
        volatile uint32_t LIMITER :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} DMA_GLBLIMITER_T;






typedef union {
    struct {
        volatile const uint32_t CC :32;
    } field;
    volatile uint32_t word;
} DMA_GLB_DBG_T;






typedef union {
    struct {
        volatile const uint32_t RUN_TX :1;
        volatile const uint32_t RUN_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_BUSY_T;
# 482 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile const uint32_t IT_TX :1;
        volatile const uint32_t IT_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_INTR_T;
# 498 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CLK_SET_TX :1;
        volatile uint32_t CLK_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CLK_SET_T;
# 514 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_dma.h"
typedef union {
    struct {
        volatile uint32_t CLK_CLR_TX :1;
        volatile uint32_t CLK_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} DMA_GLB_CLK_CLR_T;







typedef union {
    struct {
        volatile uint32_t WPPT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} PDMA_WPPT_T;






typedef union {
    struct {
        volatile uint32_t WPTO :32;
    } field;
    volatile uint32_t word;
} PDMA_WPTO_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile const uint32_t INT :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} PDMA_INTSTA_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile uint32_t ACK :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} PDMA_ACKINT_T;






typedef union {
    struct {
        volatile const uint32_t RLCT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} PDMA_RLCT_T;






typedef union {
    struct {
        volatile uint32_t LIMITER :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} PDMA_LIMITER_T;





typedef struct {
    PDMA_WPPT_T pdma_wppt;
    PDMA_WPTO_T pdma_wpto;
    PDMA_COUNT_T pdma_count;
    PDMA_CON_T pdma_con;
    PDMA_PGMADDR_T pdma_pgmaddr;
    PDMA_START_T pdma_start;
} PDMA_CFG_REGISTER_T;

typedef struct {
    PDMA_INTSTA_T pdma_intsta;
    PDMA_ACKINT_T pdma_ackint;
    PDMA_RLCT_T pdma_rlct;
    PDMA_LIMITER_T pdma_limiter;
    uint32_t __reserved_00[60];
} PDMA_STA_REGISTER_T;

typedef struct {
    DMA_GLB_CPU0_CFG_T dma_glb_cpu0_cfg;
    DMA_GLB_CPU1_CFG_T dma_glb_cpu1_cfg;
    DMA_GLB_CLK_CFG_T dma_glb_clk_cfg;

    PDMA_CFG_REGISTER_T dma_config_ch[2];

    DMA_GLBSTA_T dma_glbsta;
    DMA_GLB_CPU0_SET_T dma_glb_cpu0_set;
    DMA_GLB_CPU0_CLR_T dma_glb_cpu0_clr;
    DMA_GLB_CPU1_SET_T dma_glb_cpu1_set;
    DMA_GLB_CPU1_CLR_T dma_glb_cpu1_clr;
    DMA_GLB_SWRST_T dma_glb_swrst;
    DMA_GLBLIMITER_T dma_glblimiter;
    DMA_GLB_DBG_T dma_glb_dbg;
    DMA_GLB_BUSY_T dma_glb_busy;
    DMA_GLB_INTR_T dma_glb_intr;
    DMA_GLB_CLK_SET_T dma_glb_clk_set;
    DMA_GLB_CLK_CLR_T dma_glb_clk_clr;
    uint32_t __reserved_00[44];

    PDMA_STA_REGISTER_T dma_status_ch[2];
} I3C_DMA_REGISTER_T;



typedef struct {
    volatile uint32_t VDMA_COUNT;
    union {
        struct {
            volatile uint8_t VDMA_DIRECTION ;
            volatile uint8_t VDMA_SIZE;
            volatile uint8_t VDMA_SETTING;
            volatile uint8_t VDMA_ITEN;
        } VDMA_CON_CELLS;
        volatile uint32_t VDMA_CON;
    } VDMA_CON_UNION;
    volatile uint32_t VDMA_START;
    volatile uint32_t VDMA_INTSTA;
    volatile uint32_t VDMA_ACKINT;
    volatile uint32_t DUMMY1_OFFSET[1];
    volatile uint32_t VDMA_LIMITER;
    volatile uint32_t VDMA_PGMADDR;
    volatile const uint32_t VDMA_WRPTR;
    volatile const uint32_t VDMA_RDPTR;
    volatile const uint32_t VDMA_FFCNT;
    volatile const uint32_t VDMA_FFSTA;
    volatile uint32_t VDMA_ALTLEN;
    volatile uint32_t VDMA_FFSIZE;
    volatile uint32_t DUMMY2_OFFSET[6];
    volatile uint32_t VDMA_SW_MV_BYTE;
    volatile uint32_t VDMA_BNDRY_ADDR;
    volatile uint32_t VDMA_BYTE_TO_BNDRY;
    volatile uint32_t VDMA_BYTE_AVAIL;
} VDMA_REGISTER_T;
# 389 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h" 1
# 42 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
typedef struct {
    volatile const uint32_t GPT_IRQSTA;
    volatile uint32_t GPT_IRQMSK0;
    volatile uint32_t GPT_IRQMSK1;
    volatile uint32_t GPT_WAKEUPMSK0;
    volatile uint32_t GPT_WAKEUPMSK1;
    volatile const uint32_t GPT_CLRSTA;
    volatile const uint32_t GPT_WCOMPSTA;
} GPT_REGISTER_GLOABL_T;

typedef struct {
    union {
        struct {
            volatile uint8_t EN;
            volatile uint8_t MODE;
            volatile uint8_t SW_CG;
            volatile const uint8_t RESERVED[1];
        } GPT_CON_CELLS;
        volatile uint32_t GPT_CON;
    } GPT_CON_UNION;
    volatile uint32_t GPT_CLR ;
    volatile uint32_t GPT_CLK ;
    volatile uint32_t GPT_IRQ_EN ;
    volatile const uint32_t GPT_IRQ_STA ;
    volatile uint32_t GPT_IRQ_ACK;
    volatile uint32_t GPT_COUNT ;
    volatile uint32_t GPT_COMPARE ;
} GPT_REGISTER_T;
# 86 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpt.h"
typedef struct {
    volatile const uint32_t OS_GPT_IRQSTA;
    volatile uint32_t OS_GPT_IRQMSK;
    volatile uint32_t OS_GPT_WAKEUPMSK;
    volatile const uint32_t OS_GPT_CLRSTA;
    volatile const uint32_t OS_GPT_WCOMPSTA;
} OS_GPT_REGISTER_GLOABL_T;
# 390 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc_timer.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc_timer.h"
typedef union {
    struct {
        volatile uint32_t EN0 :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t MODE0 :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SW_CG0 :1;
        volatile const uint32_t __reserved_02 :15;
    } field;
    volatile uint32_t word;
} RTC_CON_T;
# 61 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc_timer.h"
typedef union {
    struct {
        volatile uint32_t CLR0 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} RTC_CLR_T;






typedef union {
    struct {
        volatile uint32_t CLK0 :5;
        volatile const uint32_t __reserved_00 :27;
    } field;
    volatile uint32_t word;
} RTC_CLK_T;






typedef union {
    struct {
        volatile uint32_t IRQEN0 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} RTC_IRQ_EN_T;






typedef union {
    struct {
        volatile const uint32_t IRQSTA0 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} RTC_IRQ_STA_T;






typedef union {
    struct {
        volatile uint32_t IRQACK0 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} RTC_IRQ_ACK_T;






typedef union {
    struct {
        volatile const uint32_t COUNTER0 :32;
    } field;
    volatile uint32_t word;
} RTC_COUNT_T;






typedef union {
    struct {
        volatile uint32_t COMPARE0 :32;
    } field;
    volatile uint32_t word;
} RTC_COMPARE_T;




typedef struct {
    RTC_CON_T rtc_con;
    RTC_CLR_T rtc_clr;
    RTC_CLK_T rtc_clk;
    RTC_IRQ_EN_T rtc_irq_en;
    RTC_IRQ_STA_T rtc_irq_sta;
    RTC_IRQ_ACK_T rtc_irq_ack;
    RTC_COUNT_T rtc_count;
    RTC_COMPARE_T rtc_compare;
    uint32_t __reserved_00[56];
}RTC_CONFIG_T;


typedef union {
    struct {
        volatile const uint32_t IRQSTA :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_IRQSTA_T;






typedef union {
    struct {
        volatile uint32_t IRQMASK0 :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_IRQMASK0_T;






typedef union {
    struct {
        volatile uint32_t IRQMASK1 :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_IRQMASK1_T;






typedef union {
    struct {
        volatile uint32_t EVENTMASK0 :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_WAKEUPMASK0_T;






typedef union {
    struct {
        volatile uint32_t EVENTMASK1 :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_WAKEUPMASK1_T;






typedef union {
    struct {
        volatile const uint32_t CLRSTA :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_CLRSTA_T;






typedef union {
    struct {
        volatile const uint32_t WCOMPSTA :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} RTC_T_WCOMPSTA_T;





typedef struct {
    RTC_CONFIG_T rtc_config[2];
    uint32_t __reserved_02[320];
    RTC_T_IRQSTA_T rtc_t_irqsta;
    RTC_T_IRQMASK0_T rtc_t_irqmask0;
    RTC_T_IRQMASK1_T rtc_t_irqmask1;
    RTC_T_WAKEUPMASK0_T rtc_t_wakeupmask0;
    RTC_T_WAKEUPMASK1_T rtc_t_wakeupmask1;
    RTC_T_CLRSTA_T rtc_t_clrsta;
    RTC_T_WCOMPSTA_T rtc_t_wcompsta;
    uint32_t __reserved_03[57];
    RTC_CONFIG_T rtc_ao_config;
    uint32_t __reserved_04[384];
    RTC_T_IRQSTA_T rtc_ao_t_irqsta;
    RTC_T_IRQMASK0_T rtc_ao_t_irqmask0;
    RTC_T_IRQMASK1_T rtc_ao_t_irqmask1;
    RTC_T_WAKEUPMASK0_T rtc_ao_t_wakeupmask0;
    RTC_T_WAKEUPMASK1_T rtc_ao_t_wakeupmask1;
    RTC_T_CLRSTA_T rtc_ao_t_clrsta;
    RTC_T_WCOMPSTA_T rtc_ao_t_wcompsta;
} RTC_TIMER_REGISTER_T;
# 391 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_cache.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_cache.h"
typedef union {
    struct {
        uint32_t EN :1;
        uint32_t SIZE :5;
        uint32_t __reserved_00 :3;
        uint32_t SRC_ADDR :23;
    } b;
    uint32_t w;
} CACHE_NCREMAP_ENTRY_N_HIGH_Type;

typedef union {
    struct {
        uint32_t __reserved_00 :9;
        uint32_t DEST_ADDR :23;
    } b;
    uint32_t w;
} CACHE_NCREMAP_ENTRY_N_LOW_Type;

typedef struct {
    CACHE_NCREMAP_ENTRY_N_HIGH_Type high;
    CACHE_NCREMAP_ENTRY_N_LOW_Type low;
} CACHE_NCREMAP_ENTRY_Type;

typedef struct {
    volatile uint32_t CACHE_CON;
    volatile uint32_t CACHE_OP;
    volatile uint32_t CACHE_HCNT0L;
    volatile uint32_t CACHE_HCNT0U;
    volatile uint32_t CACHE_CCNT0L;
    volatile uint32_t CACHE_CCNT0U;
    volatile uint32_t CACHE_HCNT1L;
    volatile uint32_t CACHE_HCNT1U;
    volatile uint32_t CACHE_CCNT1L;
    volatile uint32_t CACHE_CCNT1U;
    volatile const uint32_t __RESERVED_00;
    volatile uint32_t CACHE_REGION_EN;
    volatile const uint32_t __RESERVED_01[1012];
    volatile CACHE_NCREMAP_ENTRY_Type remap[4];
    volatile const uint32_t __RESERVED_02[15352];
    volatile uint32_t CACHE_ENTRY_N[16];
    volatile uint32_t CACHE_END_ENTRY_N[16];
} CACHE_REGISTER_T;
# 392 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_adc.h" 1
# 44 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_adc.h"
typedef struct {
    uint32_t RESERVED0[1];
    volatile uint32_t AUXADC_CON1;
    union {
        struct {
            volatile const uint8_t ADC_STAT;
            volatile uint8_t SOFT_RST;
            volatile uint8_t AUXADC_CON3_RESERVED0;
            volatile uint8_t AUXADC_CON3_RESERVED1;
        } AUXADC_CON3_CELLS;
        volatile uint32_t AUXADC_CON3;
    } AUXADC_CON3_UNION;

    union {
        struct {
            volatile uint8_t AUTO_AVG_EN;
            volatile uint8_t AUTOSET;
            volatile uint8_t AUXADC_CON4_RESERVED0;
            volatile uint8_t AUXADC_CON4_RESERVED1;
        } AUXADC_CON4_CELLS;
        volatile uint32_t AUXADC_CON4;
    } AUXADC_CON4_UNION;

    volatile const uint32_t AUXADC_DATA[32];

    volatile uint32_t AUXADC_SLP_LIST;
    volatile uint32_t AUXADC_SLP_STATE;
    volatile uint32_t AUXADC_CON5;

    union {
        struct {
            volatile uint8_t AUTO_AUXADC_EN;
            volatile uint8_t AUTO_SEL;
            volatile uint8_t AUXADC_CON6_RESERVED0;
            volatile uint8_t AUXADC_CON6_RESERVED1;
        } AUXADC_CON6_CELLS;
        volatile uint32_t AUXADC_CON6;
    } AUXADC_CON6_UNION;

    union {
        struct {
            volatile uint8_t ACD_MODE;
            volatile uint8_t ACD_AUX_PWDB;
            volatile uint8_t ACD_CON_SEL_RESERVED0;
            volatile uint8_t ACD_CON_SEL_RESERVED1;
        } ACD_CON_SEL_CELLS;
        volatile uint32_t ACD_CON_SEL;
    } ACD_CON_SEL_UNION;

    union {
        struct {
            volatile uint8_t EXT_AUX_SEL;
            volatile uint8_t EXT_AUX_EN;
            volatile uint8_t EXT_AUX_SEL_RESERVED0;
            volatile uint8_t EXT_AUX_SEL_RESERVED1;
        } EXT_AUX_SEL_CELLS;
        volatile uint32_t EXT_AUX_SEL;
    } EXT_AUX_SEL_UNION;

    volatile uint32_t AUXADC_DIV_CON;


    union {
        struct {
            volatile uint8_t RG_AUXADC_LDO_EN;
            volatile uint8_t RG_AUXADC_LDO_OUT_EN;
            volatile uint8_t MACRO_CON2_RESERVED0;
            volatile uint8_t MACRO_CON2_RESERVED1;
        } MACRO_CON2_CELLS;
        volatile uint32_t MACRO_CON2;
    } MACRO_CON2_UNION;


    union {
        struct {
            volatile uint8_t AUXADC_EN;
            volatile uint8_t RG_AUXADC_REF_SEL;
            volatile uint8_t ANA_EN_CON_RESERVED0;
            volatile uint8_t ANA_EN_CON_RESERVED1;
        } ANA_EN_CON_CELLS;
        volatile uint32_t ANA_EN_CON;
    } ANA_EN_CON_UNION;

    volatile uint32_t AUXADC_AVG_NUM;

    volatile const uint32_t AUXADC_AVG_READY;

    volatile const uint32_t AUXADC_AVG_DATA;

    volatile uint32_t ACD_FUNC_MODE_CTL;

    volatile uint32_t RG_AUXADC_DEBUG_EN;

    volatile uint32_t AUXADC_SPL_CON;

    union {
        struct {
            volatile uint8_t AUXADC_MSB0_CON;
            volatile uint8_t AUXADC_MSB1_CON;
            volatile uint8_t AUXADC_MSB_CON_RESERVED0;
            volatile uint8_t AUXADC_MSB_CON_RESERVED1;
        } AUXADC_MSB_CON_CELLS;
        volatile uint32_t AUXADC_MSB_CON;
    } AUXADC_MSB_CON_UNION;

    volatile uint32_t RG_D2A_SAR_CLK_EN;

    union {
        struct {
            volatile uint8_t RG_ADC2SRAM_EN;
            volatile uint8_t AUXADC_MSB1_CON;
            volatile uint8_t ADC_SRAM_CON_RESERVED0;
            volatile uint8_t ADC_SRAM_CON_RESERVED1;
        } ADC_SRAM_CON_CELLS;
        volatile uint32_t ADC_SRAM_CON;
    } ADC_SRAM_CON_UNION;

    volatile uint32_t AUXADC_RESERVE;
    volatile uint32_t RESERVED1[9];
    volatile uint32_t AVG_DATA[32];

} ADC_REGISTER_T;
# 393 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_clock.h" 1
# 42 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_clock.h"
typedef struct {
    volatile uint32_t BUS_DCM_CON_0;
    volatile uint32_t BUS_DCM_CON_1;
    volatile uint32_t reserver1[2];
    volatile uint32_t CM4_DCM_CON_0;
    volatile uint32_t CM4_DCM_CON_1;
    volatile uint32_t reserver2[6];
    volatile uint32_t SYS_FREE_DCM_CON;
    volatile uint32_t reserver3[3];
    volatile uint32_t SFC_DCM_CON_0;
    volatile uint32_t SFC_DCM_CON_1;
    volatile uint32_t reserver4[10];
    volatile uint32_t CLK_FREQ_SWCH;
    volatile uint32_t reserver5[99];
    volatile const uint32_t PDN_COND0;
    volatile uint32_t reserver6[3];
    volatile uint32_t PDN_SETD0;
    volatile uint32_t reserver7[3];
    volatile uint32_t PDN_CLRD0;
} CKSYS_BUS_CLK_REGISTER_T;





typedef struct {
    volatile uint32_t CKSYS_TST_SEL_0;
    volatile uint32_t CKSYS_TST_SEL_1;
    volatile uint32_t reserver1[6];
    volatile uint32_t CKSYS_CLK_CFG_0;
    volatile uint32_t CKSYS_CLK_CFG_1;
    volatile uint32_t reserver2[2];
    volatile uint32_t CKSYS_CLK_UPDATE_0;
    volatile uint32_t CKSYS_CLK_UPDATE_1;
    volatile uint32_t reserver3[2];
    volatile const uint32_t CKSYS_CLK_UPDATE_STATUS_0;
    volatile const uint32_t CKSYS_CLK_UPDATE_STATUS_1;
    volatile uint32_t reserver4[2];
    volatile uint32_t CKSYS_CLK_FORCE_ON_0;
    volatile uint32_t CKSYS_CLK_FORCE_ON_1;
    volatile uint32_t reserver5[2];
    volatile uint32_t CKSYS_CLK_DIV_0;
    volatile uint32_t CKSYS_CLK_DIV_1;
    volatile uint32_t CKSYS_CLK_DIV_2;
    volatile uint32_t CKSYS_CLK_DIV_3;
    volatile uint32_t CKSYS_CLK_DIV_4;
    volatile uint32_t CKSYS_CLK_DIV_5;
    volatile uint32_t reserver6[2];
    volatile uint32_t CKSYS_XTAL_FREQ;
    volatile uint32_t CKSYS_REF_CLK_SEL;
    volatile uint32_t reserver7[86];
    volatile uint32_t PLL_ABIST_FQMTR_CON0;
    volatile const uint32_t PLL_ABIST_FQMTR_CON1;
    volatile uint32_t PLL_ABIST_FQMTR_CON2;
    volatile const uint32_t PLL_ABIST_FQMTR_DATA;
} CKSYS_REGISTER_T;




typedef struct {
    volatile const uint32_t XO_PDN_COND0;
    volatile uint32_t reserver1[3];
    volatile uint32_t XO_PDN_SETD0;
    volatile uint32_t reserver2[3];
    volatile uint32_t XO_PDN_CLRD0;
    volatile uint32_t reserver3[55];
    volatile uint32_t XO_DCM_CON_0;
    volatile uint32_t XO_DCM_CON_1;
} CKSYS_XO_CLK_REGISTER_T;
# 394 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_RESUME :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t SPIM_RST :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SPIMST_TRIG_T;
# 57 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile const uint32_t SPIM_INT :2;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} SPIMST_INT_T;






typedef union {
    struct {
        volatile uint32_t SPIM_TX_SRC :32;
    } field;
    volatile uint32_t word;
} SPIMST_TX_SRC_T;






typedef union {
    struct {
        volatile uint32_t SPIM_RX_DST :32;
    } field;
    volatile uint32_t word;
} SPIMST_RX_DST_T;






typedef union {
    struct {
        volatile uint32_t SPIM_CTRL0 :7;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t SPIM_DEASSERT_EN :1;
        volatile const uint32_t __reserved_01 :7;
        volatile uint32_t SPIM_PAUSE_EN :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIM_DEBUG_EN :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} SPIMST_CTRL0_T;
# 119 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_CTRL1 :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t SPIM_GET_DLY :3;
        volatile const uint32_t __reserved_01 :5;
        volatile uint32_t SPIM_TXDMA_EN :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIM_RXDMA_EN :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} SPIMST_CTRL1_T;
# 144 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_CS_HOLD_CNT :16;
        volatile uint32_t SPIM_CS_SETUP_CNT :16;
    } field;
    volatile uint32_t word;
} SPIMST_CFG0_T;
# 159 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_SCK_HIGH_CNT :16;
        volatile uint32_t SPIM_SCK_LOW_CNT :16;
    } field;
    volatile uint32_t word;
} SPIMST_CFG1_T;
# 174 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_CS_IDLE_CNT :8;
        volatile uint32_t SPIM_PACKET_LOOP_CNT :8;
        volatile uint32_t SPIM_PACKET_LENGTH_CNT :16;
    } field;
    volatile uint32_t word;
} SPIMST_CFG2_T;
# 192 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_COMMAND_CNT :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t SPIM_DUMMY_CNT :4;
        volatile const uint32_t __reserved_01 :4;
        volatile uint32_t SPIM_BT_HW_EN :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIM_TX_MOSI_CLR_EN :1;
        volatile uint32_t SPIM_TX_MOSI_CLR_DATA :1;
        volatile const uint32_t __reserved_03 :6;
    } field;
    volatile uint32_t word;
} SPIMST_CFG3_T;
# 220 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_SEL_ADDR :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t SPIM_SEL_WDATA :3;
        volatile const uint32_t __reserved_01 :5;
        volatile const uint32_t SPIM_SEL_RDATA :3;
        volatile const uint32_t __reserved_02 :5;
        volatile uint32_t SPIM_IE :2;
        volatile const uint32_t __reserved_03 :6;
    } field;
    volatile uint32_t word;
} SPIMST_CFG4_T;
# 245 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_B2B_DELAY_CNT :16;
        volatile uint32_t SPIM_SB2NB_CNT :5;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t SPIM_B2B_DELAY_EN :1;
        volatile const uint32_t __reserved_01 :7;
    } field;
    volatile uint32_t word;
} SPIMST_CFG5_T;
# 265 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spim.h"
typedef union {
    struct {
        volatile uint32_t SPIM_CMD_ACT :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} SPIMST_CMD_ACT_T;






typedef union {
    struct {
        volatile const uint32_t SPIM_RX_DATA :32;
    } field;
    volatile uint32_t word;
} SPIMST_RX_DATA_T;






typedef union {
    struct {
        volatile uint32_t SPIM_TX_DATA :32;
    } field;
    volatile uint32_t word;
} SPIMST_TX_DATA_T;






typedef union {
    struct {
        volatile const uint32_t SPIM_BUSY :1;
        volatile const uint32_t __reserved_00 :7;
        volatile const uint32_t SPIM_BT_TRIG_STA :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} SPIMST_STA_T;







typedef struct {
    SPIMST_TX_SRC_T spimst_tx_src;
    SPIMST_RX_DST_T spimst_rx_dst;
    SPIMST_CTRL0_T spimst_ctrl0;
    SPIMST_CTRL1_T spimst_ctrl1;
    SPIMST_CFG0_T spimst_cfg0;
    SPIMST_CFG1_T spimst_cfg1;
    SPIMST_CFG2_T spimst_cfg2;
    SPIMST_CFG3_T spimst_cfg3;
    SPIMST_CFG4_T spimst_cfg4;
    SPIMST_CFG5_T spimst_cfg5;
    SPIMST_CMD_ACT_T spimst_cmd_act;
    SPIMST_RX_DATA_T spimst_rx_data;
    SPIMST_TX_DATA_T spimst_tx_data;
    SPIMST_STA_T spimst_sta;
    SPIMST_TRIG_T spimst_trig;
    SPIMST_INT_T spimst_int;
} SPIM_REGISTER_T;
# 395 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h" 1
# 46 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_DUMMY_CNT :4;
        volatile const uint32_t __reserved_00 :20;
        volatile uint32_t SPIS_PAD_CMD_CT :8;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_CMD_DEF0_T;
# 62 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_CMD_PWOFF :8;
        volatile uint32_t SPIS_PAD_CMD_PWON :8;
        volatile uint32_t SPIS_PAD_CMD_RS :8;
        volatile uint32_t SPIS_PAD_CMD_WS :8;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_CMD_DEF1_T;
# 83 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_CMD_CR :8;
        volatile uint32_t SPIS_PAD_CMD_CW :8;
        volatile uint32_t SPIS_PAD_CMD_RD :8;
        volatile uint32_t SPIS_PAD_CMD_WR :8;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_CMD_DEF2_T;
# 104 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_MOSI0_DLYSEL :3;
        volatile const uint32_t __reserved_00 :5;
        volatile uint32_t SPIS_PAD_MOSI1_DLYSEL :3;
        volatile const uint32_t __reserved_01 :5;
        volatile uint32_t SPIS_PAD_MOSI2_DLYSEL :3;
        volatile const uint32_t __reserved_02 :5;
        volatile uint32_t SPIS_PAD_MOSI3_DLYSEL :3;
        volatile const uint32_t __reserved_03 :5;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_DLYSEL0_T;
# 129 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_MISO0_DLYSEL :3;
        volatile const uint32_t __reserved_00 :5;
        volatile uint32_t SPIS_PAD_MISO1_DLYSEL :3;
        volatile const uint32_t __reserved_01 :5;
        volatile uint32_t SPIS_PAD_MISO2_DLYSEL :3;
        volatile const uint32_t __reserved_02 :5;
        volatile uint32_t SPIS_PAD_MISO3_DLYSEL :3;
        volatile const uint32_t __reserved_03 :5;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_DLYSEL1_T;
# 154 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_PAD_SCK_DLYSEL :3;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_DLYSEL2_T;






typedef union {
    struct {
        volatile uint32_t SPIS_PAD_DEBUG_EN :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t SPIS_PAD_CTRL0 :2;
        volatile const uint32_t __reserved_01 :22;
    } field;
    volatile uint32_t word;
} SPISLV_PAD_DEBUG_EN_T;







typedef struct {
    SPISLV_PAD_CMD_DEF0_T spislv_pad_cmd_def0;
    SPISLV_PAD_CMD_DEF1_T spislv_pad_cmd_def1;
    SPISLV_PAD_CMD_DEF2_T spislv_pad_cmd_def2;
    SPISLV_PAD_DLYSEL0_T spislv_pad_dlysel0;
    SPISLV_PAD_DLYSEL1_T spislv_pad_dlysel1;
    SPISLV_PAD_DLYSEL2_T spislv_pad_dlysel2;
    SPISLV_PAD_DEBUG_EN_T spislv_pad_debug_en;
} SPIS_PAD_REGISTER_T;
# 203 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_TX_FIFO_THRE :6;
        volatile const uint32_t __reserved_00 :2;
        volatile uint32_t SPIS_RX_FIFO_THRE :6;
        volatile const uint32_t __reserved_01 :18;
    } field;
    volatile uint32_t word;
} SPISLV_DIR_MODE_FIFO_CON_T;
# 220 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_RXDMA_STR_ADDR :32;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_START_ADDR_T;






typedef union {
    struct {
        volatile uint32_t SPIS_RXDMA_SIZE :16;
        volatile uint32_t SPIS_RXDMA_THRE :16;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_SIZE_T;
# 247 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_RXDMA_SW_MV_BYTE :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_SW_CON_T;






typedef union {
    struct {
        volatile uint32_t SPIS_TXDMA_STR_ADDR :32;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_START_ADDR_T;






typedef union {
    struct {
        volatile uint32_t SPIS_TXDMA_SIZE :16;
        volatile uint32_t SPIS_TXDMA_THRE :16;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_SIZE_T;
# 287 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_TXDMA_SW_MV_BYTE :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_SW_CON_T;






typedef union {
    struct {
        volatile uint32_t SPIS_CTRL0 :7;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t SPIS_CTRL1 :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SPIS_MISO_EARLY_TRANS :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIS_DIR_MODE :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} SPISLV_CTRL_T;
# 325 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_TMOUT_THR :32;
    } field;
    volatile uint32_t word;
} SPISLV_TMOUT_THR_T;






typedef union {
    struct {
        volatile uint32_t SPIS_BUFFER_BASE_ADDR :32;
    } field;
    volatile uint32_t word;
} SPISLV_BUFFER_BASE_ADDR_T;






typedef union {
    struct {
        volatile uint32_t SPIS_BUFFER_SIZE :32;
    } field;
    volatile uint32_t word;
} SPISLV_BUFFER_SIZE_T;






typedef union {
    struct {
        volatile uint32_t SPIS_IE :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} SPISLV_IE_T;






typedef union {
    struct {
        volatile uint32_t SPIS_SW_ON :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t SPIS_SW_RST :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SPIS_TXDMA_SW_RDY :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIS_RXDMA_SW_RDY :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} SPISLV_TRIG_T;
# 399 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile uint32_t SPIS_TX_DMA_START :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t SPIS_TXDMA_TRANS_TYPE :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SPIS_RX_DMA_START :1;
        volatile const uint32_t __reserved_02 :7;
        volatile uint32_t SPIS_RXDMA_TRANS_TYPE :2;
        volatile const uint32_t __reserved_03 :6;
    } field;
    volatile uint32_t word;
} SPISLV_DIR_MODE_DMA_CON_T;
# 424 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_RX_DATA :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} SPISLV_DIR_MODE_RX_DATA_T;






typedef union {
    struct {
        volatile uint32_t SPIS_TX_DATA :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} SPISLV_DIR_MODE_TX_DATA_T;






typedef union {
    struct {
        volatile uint32_t SPIS_INT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} SPISLV_INT_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_STA :14;
        volatile const uint32_t __reserved_00 :2;
        volatile const uint32_t SPIS_AHB_STA :4;
        volatile const uint32_t __reserved_01 :4;
        volatile const uint32_t SPIS_FIFO_STA :4;
        volatile const uint32_t __reserved_02 :4;
    } field;
    volatile uint32_t word;
} SPISLV_STA_T;
# 484 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_TRANS_LENGTH :32;
    } field;
    volatile uint32_t word;
} SPISLV_TRANS_LENGTH_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_TRANS_ADDR :32;
    } field;
    volatile uint32_t word;
} SPISLV_TRANS_ADDR_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_CMD_RECEIVED :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} SPISLV_CMD_RECEIVED_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_TX_FIFO_CNT :7;
        volatile const uint32_t __reserved_00 :9;
        volatile const uint32_t SPIS_RX_FIFO_CNT :7;
        volatile const uint32_t __reserved_01 :9;
    } field;
    volatile uint32_t word;
} SPISLV_DIR_MODE_FIFO_STA_T;
# 538 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_RXDMA_WPTR :16;
        volatile const uint32_t SPIS_RXDMA_RPTR :16;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_PTR_T;
# 553 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_RXDMA_FIFO_CNT :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_FIFO_CNT_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_RXDMA_BYTE_AVAIL :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_RXDMA_BYTE_AVAIL_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_TXDMA_WPTR :16;
        volatile const uint32_t SPIS_TXDMA_RPTR :16;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_PTR_T;
# 594 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_TXDMA_FIFO_CNT :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_FIFO_CNT_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_TXDMA_BYTE_AVAIL :17;
        volatile const uint32_t __reserved_00 :15;
    } field;
    volatile uint32_t word;
} SPISLV_TXDMA_BYTE_AVAIL_T;






typedef union {
    struct {
        volatile const uint32_t SPIS_TX_FIFO_WPTR_H :6;
        volatile const uint32_t __reserved_00 :2;
        volatile const uint32_t SPIS_TX_FIFO_RPTR_H :6;
        volatile const uint32_t __reserved_01 :2;
        volatile const uint32_t SPIS_RX_FIFO_WPTR_H :6;
        volatile const uint32_t __reserved_02 :2;
        volatile const uint32_t SPIS_RX_FIFO_RPTR_H :6;
        volatile const uint32_t __reserved_03 :2;
    } field;
    volatile uint32_t word;
} SPISLV_DEBUG1_T;
# 645 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef union {
    struct {
        volatile const uint32_t SPIS_TX_FIFO_WPTR_B :6;
        volatile const uint32_t __reserved_00 :2;
        volatile const uint32_t SPIS_TX_FIFO_RPTR_B :6;
        volatile const uint32_t __reserved_01 :2;
        volatile const uint32_t SPIS_RX_FIFO_WPTR_B :6;
        volatile const uint32_t __reserved_02 :2;
        volatile const uint32_t SPIS_RX_FIFO_RPTR_B :6;
        volatile const uint32_t __reserved_03 :2;
    } field;
    volatile uint32_t word;
} SPISLV_DEBUG2_T;
# 669 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spis.h"
typedef struct {
    SPISLV_DIR_MODE_FIFO_CON_T spislv_dir_mode_fifo_con;
    SPISLV_RXDMA_START_ADDR_T spislv_rxdma_start_addr;
    SPISLV_RXDMA_SIZE_T spislv_rxdma_size;
    SPISLV_RXDMA_SW_CON_T spislv_rxdma_sw_con;
    SPISLV_TXDMA_START_ADDR_T spislv_txdma_start_addr;
    SPISLV_TXDMA_SIZE_T spislv_txdma_size;
    SPISLV_TXDMA_SW_CON_T spislv_txdma_sw_con;
    SPISLV_CTRL_T spislv_ctrl;
    SPISLV_TMOUT_THR_T spislv_tmout_thr;
    SPISLV_BUFFER_BASE_ADDR_T spislv_buffer_base_addr;
    SPISLV_BUFFER_SIZE_T spislv_buffer_size;
    SPISLV_IE_T spislv_ie;
    SPISLV_TRIG_T spislv_trig;
    SPISLV_DIR_MODE_DMA_CON_T spislv_dir_mode_dma_con;
    SPISLV_DIR_MODE_RX_DATA_T spislv_dir_mode_rx_data;
    SPISLV_DIR_MODE_TX_DATA_T spislv_dir_mode_tx_data;
    SPISLV_INT_T spislv_int;
    SPISLV_STA_T spislv_sta;
    SPISLV_TRANS_LENGTH_T spislv_trans_length;
    SPISLV_TRANS_ADDR_T spislv_trans_addr;
    SPISLV_CMD_RECEIVED_T spislv_cmd_received;
    SPISLV_DIR_MODE_FIFO_STA_T spislv_dir_mode_fifo_sta;
    SPISLV_RXDMA_PTR_T spislv_rxdma_ptr;
    SPISLV_RXDMA_FIFO_CNT_T spislv_rxdma_fifo_cnt;
    SPISLV_RXDMA_BYTE_AVAIL_T spislv_rxdma_byte_avail;
    SPISLV_TXDMA_PTR_T spislv_txdma_ptr;
    SPISLV_TXDMA_FIFO_CNT_T spislv_txdma_fifo_cnt;
    SPISLV_TXDMA_BYTE_AVAIL_T spislv_txdma_byte_avail;
    uint32_t __reserved_00[12];
    SPISLV_DEBUG1_T spislv_debug1;
    SPISLV_DEBUG2_T spislv_debug2;
} SPIS_REGISTER_T;
# 396 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_eint.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_eint.h"
typedef union
{
    struct
    {
        uint8_t DBC_CON[2];

        uint8_t DBC_EN;
        uint8_t RSTDBC;
    } EINT_CON_CELLS;
    uint32_t EINT_CON;
} EINT_CON_UNION;

typedef struct
{
    volatile uint32_t EINT_SENS[2];
    volatile uint32_t EINT_DUALEDGE[2];
    volatile uint32_t EINT_POL[2];
    volatile EINT_CON_UNION EINT_CON_REGISTER[48];
    volatile uint32_t EINT_TIMER_SEL[10];
    volatile uint32_t EINT_COUNTER_CTRL;
    volatile uint32_t EINT_D0EN[2];
    volatile uint32_t EINT_D1EN[2];
    volatile uint32_t EINT_MASK[2];
    volatile uint32_t EINT_WAKEUP_MASK[2];
    volatile uint32_t EINT_ENABLE[2];
    volatile uint32_t EINT_TOGGLE[2];
    volatile const uint32_t RESERVED0[51];
    volatile uint32_t EINT_INTACK[2];
    volatile uint32_t EINT_EEVTACK[2];
    volatile uint32_t EINT_SOFT[2];
    volatile const uint32_t RESERVED1[58];

    volatile uint32_t EINT_STA[2];
    volatile uint32_t EINT_EEVT[2];
    volatile uint32_t EINT_DBC_OUT[2];
    volatile const uint32_t RESERVED2[58];

    volatile uint32_t EINT_SENS_SET[2];
    volatile uint32_t EINT_SENS_CLR[2];
    volatile uint32_t EINT_DUALEDGE_SET[2];
    volatile uint32_t EINT_DUALEDGE_CLR[2];
    volatile uint32_t EINT_POL_SET[2];
    volatile uint32_t EINT_POL_CLR[2];
    volatile uint32_t EINT_D0EN_SET[2];
    volatile uint32_t EINT_D0EN_CLR[2];
    volatile uint32_t EINT_D1EN_SET[2];
    volatile uint32_t EINT_D1EN_CLR[2];
    volatile uint32_t EINT_MASK_SET[2];
    volatile uint32_t EINT_MASK_CLR[2];
    volatile uint32_t EINT_WAKEUP_MASK_SET[2];
    volatile uint32_t EINT_WAKEUP_MASK_CLR[2];
    volatile uint32_t EINT_SOFT_SET[2];
    volatile uint32_t EINT_SOFT_CLR[2];
    volatile uint32_t EINT_ENABLE_SET[2];
    volatile uint32_t EINT_ENABLE_CLR[2];
    volatile uint32_t EINT_TOGGLE_DIS[2];
    volatile const uint32_t RESERVED3[27];

    volatile uint32_t EINT_COUNTER_OUT;
    volatile const uint32_t RESERVED4[18];

    volatile uint32_t EINT_TIMER_OUT[10];
    volatile const uint32_t RESERVED5[35];
    volatile uint32_t EINT_TRIGGER_STA[14];
    volatile const uint32_t RESERVED6[51];
    volatile uint32_t EINT_DEBUG_SEL;
} EINT_REGISTER_T;
# 397 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc.h" 1
# 45 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rtc.h"
typedef union {
    struct {
        volatile uint32_t EOSC1_CHOP_EN : 1;
        volatile uint32_t EOSC1_CALI : 5;
        volatile uint32_t EOSC1_FST_EN : 2;
        volatile uint32_t EOSC1_LPD_BIAS_RDY : 1;
        volatile uint32_t EOSC1_LPD_EN : 1;
        volatile uint32_t EOSC1_LPD_RST : 1;
        volatile uint32_t EOSC1_STR_ENB : 1;
        volatile uint32_t EOSC1_VCT_EN : 1;
        volatile const uint32_t __RESERVED_00 : 3;
        volatile uint32_t EOSC2_BIAS_CT0 : 1;
        volatile uint32_t EOSC2_BIAS_CT1 : 1;
        volatile uint32_t EOSC2_BIAS_DN : 2;
        volatile uint32_t EOSC2_CALI : 5;
        volatile uint32_t EOSC2_FRWQ_CT0 : 1;
        volatile uint32_t EOSC2_FRWQ_CT1 : 1;
        volatile uint32_t EOSC_EN : 1;
        volatile const uint32_t __RESERVED_01 : 4;
    } field;
    volatile uint32_t word;
} RTC_OSC32CON0_T;

typedef union {
    struct {
        volatile uint32_t XOSC_QI_PWDB : 1;
        volatile uint32_t XOSC_AMP_EN : 1;
        volatile uint32_t XOSC_CALI : 4;
        volatile uint32_t XOSC_CGM_LP_EN : 1;
        volatile uint32_t XOSC_CGM_STR_ENB : 1;
        volatile uint32_t XOSC_LPMODEB : 1;
        volatile uint32_t XOSC_SW_EN : 1;
        volatile uint32_t XOSC_AC_ON : 1;
        volatile uint32_t XOSC_CAP : 3;
        volatile uint32_t XOSC_DMY : 4;
        volatile uint32_t XOSC_DMY_EN : 1;
        volatile uint32_t RFB_BYPASS : 1;
        volatile uint32_t XOSC_ULP_EN : 1;
        volatile const uint32_t __RESERVED_00 : 11;
    } field;
    volatile uint32_t word;
} RTC_OSC32CON1_T;

typedef union {
    struct {
        volatile const uint32_t __RESERVED_00 : 16;
        volatile uint32_t F32K_SEL : 2;
        volatile const uint32_t __RESERVED_01 : 6;
        volatile uint32_t SYS32K_SRC_SEL : 1;
        volatile const uint32_t __RESERVED_02 : 7;
    } field;
    volatile uint32_t word;
} RTC_OSC32CON2_T;

typedef union {
    struct {
        volatile uint32_t DBG_SEL : 3;
        volatile const uint32_t __RESERVED_00 : 4;
        volatile uint32_t DGB_EN : 1;
        volatile const uint32_t __RESERVED_01 : 8;
        volatile const uint32_t OUTPUT : 16;
    } field;
    volatile uint32_t word;
} RTC_DEBUG_CON_T;

typedef union {
    struct {
        volatile const uint32_t __RESERVED_00 : 16;
        volatile uint32_t F32K_SEL : 2;
        volatile const uint32_t __RESERVED_01 : 6;
        volatile uint32_t SYS32K_SEL : 1;
        volatile const uint32_t __RESERVED_02 : 7;
    } field;
    volatile uint32_t word;
} RTC_SYS32K_CG_CON_T;



typedef struct {
    union {
        struct {
            volatile uint32_t RTC_OSC32CON0;
            volatile uint32_t RTC_OSC32CON1;
            volatile uint32_t RTC_OSC32CON2;
        };
        volatile uint32_t RTC_OSC32CON[3];
    };
    volatile uint32_t RTC_DEBUG_CON;
    volatile uint32_t RTC_SPAR_REG;
    union {
        struct {
            volatile uint32_t RTC_SPAR0;
            volatile uint32_t RTC_SPAR1;
            volatile uint32_t RTC_SPAR2;
        };
        volatile uint32_t RTC_SPAR[3];
    };

    volatile uint32_t RTC_SYS32K_CG_CON;
} RTC_32K_REGISTER_T;
# 398 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_crypto.h" 1
# 399 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_trng.h" 1
# 44 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_trng.h"
typedef struct {
    volatile uint32_t TRNG_CTRL;
    volatile uint32_t TRNG_TIME;
    volatile const uint32_t TRNG_DATA;
    volatile uint32_t TRNG_CONF;
    volatile const uint32_t TRNG_INT_SET;
    volatile uint32_t TRNG_INT_CLR;
} TRNG_REGISTER_T;
# 400 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY0 :8;
        volatile uint32_t WDT_EN :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t KEY1 :8;
        volatile uint32_t WDT_EN_TEST :1;
        volatile const uint32_t __reserved_01 :7;
    } field;
    volatile uint32_t word;
} WDT_EN_T;
# 63 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t WDT_LENGTH :16;
    } field;
    volatile uint32_t word;
} WDT_LENGTH_T;
# 79 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t WDT_INTERVAL :16;
    } field;
    volatile uint32_t word;
} WDT_INTERVAL_T;
# 95 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :32;
    } field;
    volatile uint32_t word;
} WDT_SW_RESTART_T;






typedef union {
    struct {
        volatile uint32_t KEY :32;
    } field;
    volatile uint32_t word;
} WDT_SW_RST_T;






typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile uint32_t WDT_AUTO_RESTART_EN :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} WDT_AUTO_RESTART_EN_T;
# 135 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT_STA :2;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} WDT_STA_T;
# 152 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY_NMI :8;
        volatile uint32_t WDT_NMI_IE :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t KEY_IRQ :8;
        volatile uint32_t WDT_IRQ_IE :1;
        volatile const uint32_t __reserved_01 :7;
    } field;
    volatile uint32_t word;
} WDT_IE_T;
# 175 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT_INT :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} WDT_INT_T;






typedef union {
    struct {
        volatile uint32_t KEY_WAKEUP_EN :8;
        volatile uint32_t WDT_WAKEUP_EN :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} WDT_WAKEUP_EN_T;
# 204 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT_WAKEUP :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} WDT_WAKEUP_T;






typedef union {
    struct {
        volatile const uint32_t WDT_COUNTER_STA :25;
        volatile const uint32_t __reserved_00 :7;
    } field;
    volatile uint32_t word;
} WDT_COUNTER_STA_T;






typedef union {
    struct {
        volatile uint32_t KEY0 :8;
        volatile uint32_t WDT1_EN :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t KEY1 :8;
        volatile uint32_t WDT1_EN_TEST :1;
        volatile const uint32_t __reserved_01 :7;
    } field;
    volatile uint32_t word;
} WDT1_EN_T;
# 253 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t WDT1_LENGTH :16;
    } field;
    volatile uint32_t word;
} WDT1_LENGTH_T;
# 269 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t WDT1_INTERVAL :16;
    } field;
    volatile uint32_t word;
} WDT1_INTERVAL_T;
# 285 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :32;
    } field;
    volatile uint32_t word;
} WDT1_SW_RESTART_T;






typedef union {
    struct {
        volatile uint32_t KEY :32;
    } field;
    volatile uint32_t word;
} WDT1_SW_RST_T;






typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile uint32_t WDT1_AUTO_RESTART_EN :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} WDT1_AUTO_RESTART_EN_T;
# 325 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT1_STA :2;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} WDT1_STA_T;






typedef union {
    struct {
        volatile uint32_t KEY_NMI :8;
        volatile uint32_t WDT1_NMI_IE :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t KEY_IRQ :8;
        volatile uint32_t WDT1_IRQ_IE :1;
        volatile const uint32_t __reserved_01 :7;
    } field;
    volatile uint32_t word;
} WDT1_IE_T;
# 361 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT1_INT :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} WDT1_INT_T;






typedef union {
    struct {
        volatile uint32_t KEY_WAKEUP_EN :8;
        volatile uint32_t WDT1_WAKEUP_EN :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} WDT1_WAKEUP_EN_T;
# 390 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile const uint32_t WDT1_WAKEUP :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} WDT1_WAKEUP_T;






typedef union {
    struct {
        volatile const uint32_t WDT1_COUNTER_STA :25;
        volatile const uint32_t __reserved_00 :7;
    } field;
    volatile uint32_t word;
} WDT1_COUNTER_STA_T;






typedef union {
    struct {
        volatile uint32_t KEY0 :8;
        volatile uint32_t SYSTEM_SW_RST :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} SW_RSTSYS_T;
# 432 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 442 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t RISCV_SW_RST;
        volatile const uint16_t RESERVED;
    } field;
    volatile uint32_t word;
} SW_RST0_T;
# 459 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 469 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t CONNSYS_SW_RST;
        volatile const uint16_t RESERVED;
    } field;
    volatile uint32_t word;
} SW_RST1_T;
# 486 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 496 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t AUDIOSYS_SW_RST;
        volatile const uint16_t RESERVED;
    } field;
    volatile uint32_t word;
} SW_RST2_T;
# 513 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 523 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t USB_SW_RST;
        volatile uint16_t USBSIF_SW_RST;
    } field;
    volatile uint32_t word;
} SW_RST3_T;
# 540 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 550 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t JTAG_RESET;
        volatile uint16_t AIRCR_RESET;
    } field;
    volatile uint32_t word;
} RST_MASK0_T;
# 567 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 577 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t PCM_RESET;
        volatile uint16_t PMU_RESET;
    } field;
    volatile uint32_t word;
} RST_MASK1_T;
# 594 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY0 :8;
        volatile uint32_t CM4_RST_INTERVAL :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} RST_FUNC_CONT0_T;
# 610 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
# 620 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
        volatile uint16_t PMU_RST_INV_EN;
        volatile uint16_t PMIC_IO_RST_INV_EN;
    } field;
    volatile uint32_t word;
} RST_FUNC_CONT1_T;
# 637 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG0 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG0_T;
# 653 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG1 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG1_T;
# 669 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG2 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG2_T;
# 685 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG3 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG3_T;
# 701 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG4 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG4_T;
# 717 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t RETN_FLAG5 :16;
    } field;
    volatile uint32_t word;
} RETN_FLAG5_T;
# 733 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t RETN_DAT0 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT0_T;






typedef union {
    struct {
        volatile uint32_t RETN_DAT1 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT1_T;






typedef union {
    struct {
        volatile uint32_t RETN_DAT2 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT2_T;






typedef union {
    struct {
        volatile uint32_t RETN_DAT3 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT3_T;






typedef union {
    struct {
        volatile uint32_t RETN_DAT4 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT4_T;






typedef union {
    struct {
        volatile uint32_t RETN_DAT5 :32;
    } field;
    volatile uint32_t word;
} RETN_DAT5_T;






typedef union {
    struct {
        volatile uint32_t KEY :8;
        volatile uint32_t PMU_TEST_SW_RST :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} PMU_TEST_SW_RST_T;
# 821 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t KEY0 :8;
        volatile uint32_t RF_SW_RST :1;
        volatile const uint32_t __reserved_00 :23;
    } field;
    volatile uint32_t word;
} SW_RF_RST_T;
# 837 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_rgu.h"
typedef union {
    struct {
        volatile uint32_t DEBUG_SEL :32;
    } field;
    volatile uint32_t word;
} RGU_DEBUG_SEL_T;





typedef struct {
    WDT_EN_T wdt_en;
    WDT_LENGTH_T wdt_length;
    WDT_INTERVAL_T wdt_interval;
    WDT_SW_RESTART_T wdt_sw_restart;
    WDT_SW_RST_T wdt_sw_rst;
    WDT_AUTO_RESTART_EN_T wdt_auto_restart_en;
    WDT_STA_T wdt_sta;
    WDT_IE_T wdt_ie;
    WDT_INT_T wdt_int;
    WDT_WAKEUP_EN_T wdt_wakeup_en;
    WDT_WAKEUP_T wdt_wakeup;
    WDT_COUNTER_STA_T wdt_counter_sta;
} RGU_REGISTER_T;


typedef struct {
    SW_RSTSYS_T sw_rstsys;
    SW_RST0_T sw_rst0;
    SW_RST1_T sw_rst1;
    SW_RST2_T sw_rst2;
    SW_RST3_T sw_rst3;
    uint32_t __reserved_00[3];
    RST_MASK0_T rst_mask0;
    RST_MASK1_T rst_mask1;
    uint32_t __reserved_01[2];
    RST_FUNC_CONT0_T rst_func_cont0;
    RST_FUNC_CONT1_T rst_func_cont1;
    uint32_t __reserved_02[2];
    RETN_FLAG0_T retn_flag0;
    RETN_FLAG1_T retn_flag1;
    RETN_FLAG2_T retn_flag2;
    RETN_FLAG3_T retn_flag3;
    RETN_FLAG4_T retn_flag4;
    RETN_FLAG5_T retn_flag5;
    uint32_t __reserved_03[2];
    RETN_DAT0_T retn_dat0;
    RETN_DAT1_T retn_dat1;
    RETN_DAT2_T retn_dat2;
    RETN_DAT3_T retn_dat3;
    RETN_DAT4_T retn_dat4;
    RETN_DAT5_T retn_dat5;
    uint32_t __reserved_04[2];
    PMU_TEST_SW_RST_T pmu_test_sw_rst;
    uint32_t __reserved_05[3];
    SW_RF_RST_T sw_rf_rst;
    uint32_t __reserved_06[3];
    RGU_DEBUG_SEL_T debug_sel;
} RGU_MISC_REGISTER_T;
# 401 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm.h"
typedef struct {
    volatile uint32_t PWM_CTRL;
    volatile uint32_t PWM_COUNT;
    volatile uint32_t PWM_THRESH;
    volatile uint32_t PWM_THRESH_DOWN;
    volatile uint32_t PWM_POL;
} PWM_REGISTER_T;
# 402 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t MR0 :1;
        volatile uint32_t MR1 :1;
        volatile uint32_t MR2 :1;
        volatile uint32_t MR3 :1;
        volatile uint32_t MR0_2 :1;
        volatile uint32_t MR1_2 :1;
        volatile uint32_t MR2_2 :1;
        volatile uint32_t MR3_2 :1;
        volatile uint32_t DMA_DONE :1;
        volatile uint32_t DMA_BUFA_DONE :1;
        volatile uint32_t DMA_BUFB_DONE :1;
        volatile uint32_t DMA_BUFA_OV :1;
        volatile uint32_t DMA_BUFB_OV :1;
        volatile const uint32_t __reserved_00 :19;
    } field;
    volatile uint32_t word;
} INTR_STS_T;
# 89 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t CEN :1;
        volatile uint32_t CRST :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} TIME_CTRL_REG_T;
# 105 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile const uint32_t TC :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} TIME_CNT_T;






typedef union {
    struct {
        volatile uint32_t PR :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} PSCALE_REG_T;






typedef union {
    struct {
        volatile const uint32_t PC :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} PSCALE_CNT_T;






typedef union {
    struct {
        volatile uint32_t MR0I :1;
        volatile uint32_t MR0R :1;
        volatile uint32_t MR0S :1;
        volatile uint32_t MR1I :1;
        volatile uint32_t MR1R :1;
        volatile uint32_t MR1S :1;
        volatile uint32_t MR2I :1;
        volatile uint32_t MR2R :1;
        volatile uint32_t MR2S :1;
        volatile uint32_t MR3I :1;
        volatile uint32_t MR3R :1;
        volatile uint32_t MR3S :1;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t MR0I_2 :1;
        volatile uint32_t MR0R_2 :1;
        volatile uint32_t MR0S_2 :1;
        volatile uint32_t MR1I_2 :1;
        volatile uint32_t MR1R_2 :1;
        volatile uint32_t MR1S_2 :1;
        volatile uint32_t MR2I_2 :1;
        volatile uint32_t MR2R_2 :1;
        volatile uint32_t MR2S_2 :1;
        volatile uint32_t MR3I_2 :1;
        volatile uint32_t MR3R_2 :1;
        volatile uint32_t MR3S_2 :1;
        volatile const uint32_t __reserved_01 :4;
    } field;
    volatile uint32_t word;
} MATCH_CTRL_REG_T;
# 227 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t MR :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} MATCH_REG_T;






typedef union {
    struct {
        volatile uint32_t MR0_WAKEUP :1;
        volatile uint32_t MR1_WAKEUP :1;
        volatile uint32_t MR2_WAKEUP :1;
        volatile uint32_t MR3_WAKEUP :1;
        volatile uint32_t MR0_2_WAKEUP :1;
        volatile uint32_t MR1_2_WAKEUP :1;
        volatile uint32_t MR2_2_WAKEUP :1;
        volatile uint32_t MR3_2_WAKEUP :1;
        volatile uint32_t DMA_DONE_WAKEUP :1;
        volatile uint32_t DMA_BUFA_DONE_WAKEUP :1;
        volatile uint32_t DMA_BUFB_DONE_WAKEUP :1;
        volatile uint32_t DMA_BUFA_OV_WAKEUP :1;
        volatile uint32_t DMA_BUFB_OV_WAKEUP :1;
        volatile const uint32_t __reserved_00 :19;
    } field;
    volatile uint32_t word;
} WAKEUP_MASK_T;


typedef union {
    struct {
        volatile const uint32_t EM0 :1;
        volatile const uint32_t EM1 :1;
        volatile const uint32_t EM2 :1;
        volatile const uint32_t EM3 :1;
        volatile uint32_t EMC0 :2;
        volatile uint32_t EMC1 :2;
        volatile uint32_t EMC2 :2;
        volatile uint32_t EMC3 :2;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t EMC0_2 :2;
        volatile uint32_t EMC1_2 :2;
        volatile uint32_t EMC2_2 :2;
        volatile uint32_t EMC3_2 :2;
        volatile uint32_t EM0_INV :1;
        volatile uint32_t EM1_INV :1;
        volatile uint32_t EM2_INV :1;
        volatile uint32_t EM3_INV :1;
        volatile const uint32_t __reserved_01 :4;
    } field;
    volatile uint32_t word;
} EXT_MATCH_CTRL_REG_T;
# 320 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t MR_2 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} MATCH_REG_2_T;






typedef union {
    struct {
        volatile uint32_t DMA_DATA_SCALE :4;
        volatile uint32_t DMA_DATA_GAIN :4;
        volatile uint32_t DMA_DATA_REPEAT :4;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t DMA_CH_NO :2;
        volatile uint32_t DMA_BUF_NONALIGN :1;
        volatile uint32_t DMA_BUF_8B :1;
        volatile uint32_t DMA_BUF_REPEAT_EN :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t DMA_MODE :1;
        volatile const uint32_t __reserved_02 :3;
        volatile uint32_t DMA_DATA_SIGN :1;
        volatile const uint32_t __reserved_03 :3;
    } field;
    volatile uint32_t word;
} DMA_SET_T;
# 373 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t DMA_DONE_INT_EN :1;
        volatile uint32_t DMA_BUFA_DONE_INT_EN :1;
        volatile uint32_t DMA_BUFB_DONE_INT_EN :1;
        volatile uint32_t DMA_BUFA_OV_INT_EN :1;
        volatile uint32_t DMA_BUFB_OV_INT_EN :1;
        volatile const uint32_t __reserved_00 :27;
    } field;
    volatile uint32_t word;
} INTR_EN_T;
# 398 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t DMA_BADDR_A :32;
    } field;
    volatile uint32_t word;
} DMA_BASE_ADDR_A_T;






typedef union {
    struct {
        volatile uint32_t DMA_LEN_A :14;
        volatile const uint32_t __reserved_00 :18;
    } field;
    volatile uint32_t word;
} DMA_LENGTH_A_T;






typedef union {
    struct {
        volatile uint32_t DMA_BADDR_B :32;
    } field;
    volatile uint32_t word;
} DMA_BASE_ADDR_B_T;






typedef union {
    struct {
        volatile uint32_t DMA_LEN_B :14;
        volatile const uint32_t __reserved_00 :18;
    } field;
    volatile uint32_t word;
} DMA_LENGTH_B_T;






typedef union {
    struct {
        volatile uint32_t DMA_START_P :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t DMA_ABORT_P :1;
        volatile const uint32_t __reserved_01 :23;
    } field;
    volatile uint32_t word;
} DMA_CTRL_T;
# 465 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile uint32_t PWM_CLK_FREE_EN :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} CLK_CTRL_T;






typedef union {
    struct {
        volatile const uint32_t DMA_BUSY :1;
        volatile const uint32_t DMA_BUFA_QUEUE :1;
        volatile const uint32_t DMA_BUFB_QUEUE :1;
        volatile const uint32_t DMA_NEXT_BUF :1;
        volatile const uint32_t __reserved_00 :28;
    } field;
    volatile uint32_t word;
} DMA_STS_T;
# 499 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_pwm_dma.h"
typedef union {
    struct {
        volatile const uint32_t DMA_BUF_CNT_PRELOAD :14;
        volatile const uint32_t __reserved_00 :1;
        volatile const uint32_t DMA_BUF_PRELOAD :1;
        volatile const uint32_t DMA_BUF_CNT_CURRENT :14;
        volatile const uint32_t __reserved_01 :1;
        volatile const uint32_t DMA_BUF_CURRENT :1;
    } field;
    volatile uint32_t word;
} DMA_CNT_STS_T;

typedef struct {
    INTR_STS_T intr_sts;
    TIME_CTRL_REG_T time_ctrl_reg;
    TIME_CNT_T time_cnt;
    PSCALE_REG_T pscale_reg;
    PSCALE_CNT_T pscale_cnt;
    MATCH_CTRL_REG_T match_ctrl_reg;
    MATCH_REG_T match_reg[4];
    uint32_t __reserved_00[2];
    WAKEUP_MASK_T wake_up_mask;
    uint32_t __reserved_01[2];
    EXT_MATCH_CTRL_REG_T ext_match_ctrl_reg;
    MATCH_REG_2_T match_reg_2[4];
    DMA_SET_T dma_set;
    INTR_EN_T intr_en;
    DMA_BASE_ADDR_A_T dma_base_addr_a;
    DMA_LENGTH_A_T dma_length_a;
    DMA_BASE_ADDR_B_T dma_base_addr_b;
    DMA_LENGTH_B_T dma_length_b;
    DMA_CTRL_T dma_ctrl;
    CLK_CTRL_T clk_ctrl;
    DMA_STS_T dma_sts;
    DMA_CNT_STS_T dma_cnt_sts;
} PWM_DMA_REGISTER_T;
# 403 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irrx.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irrx.h"
 typedef struct {
    volatile uint32_t PDREG_IRH;
    volatile uint32_t PDREG_IRM;
    volatile uint32_t PDREG_IRL;
    volatile uint32_t PDREG_IRCFGH;
    volatile uint32_t PDREG_IRCFGL;
    volatile uint32_t PDREG_IRTHD;
    volatile uint32_t PDREG_IRRCM_THD;
    volatile uint32_t PDREG_IRRCM_THD_0;
    volatile uint32_t PDREG_IRCLR;
    volatile uint32_t PDREG_IREXP_EN;
    volatile uint32_t PDREG_EXP_BCNT;
    volatile uint32_t PDREG_ENEXP_IRM;
    volatile uint32_t PDREG_ENEXP_IRL;
    volatile uint32_t PDREG_EXP_IRL0;
    volatile uint32_t PDREG_EXP_IRL1;
    volatile uint32_t PDREG_EXP_IRL2;
    volatile uint32_t PDREG_EXP_IRL3;
    volatile uint32_t PDREG_EXP_IRL4;
    volatile uint32_t PDREG_EXP_IRL5;
    volatile uint32_t PDREG_EXP_IRL6;
    volatile uint32_t PDREG_EXP_IRL7;
    volatile uint32_t PDREG_EXP_IRL8;
    volatile uint32_t PDREG_EXP_IRL9;
    volatile uint32_t PDREG_EXP_IRM0;
    volatile uint32_t PDREG_EXP_IRM1;
    volatile uint32_t PDREG_EXP_IRM2;
    volatile uint32_t PDREG_EXP_IRM3;
    volatile uint32_t PDREG_EXP_IRM4;
    volatile uint32_t PDREG_EXP_IRM5;
    volatile uint32_t PDREG_EXP_IRM6;
    volatile uint32_t PDREG_EXP_IRM7;
    volatile uint32_t PDREG_EXP_IRM8;
    volatile uint32_t PDREG_EXP_IRM9;
    volatile uint32_t PDREG_IRINT_EN;
    volatile uint32_t PDREG_IR_INTCLR;
    volatile uint32_t PDREG_WAKEEN;

    volatile uint32_t PDREG_WAKECLR;
    volatile uint32_t RESERVER;
    volatile uint32_t PDREG_SOFTEN;
    volatile uint32_t PDREG_SELECT;

    volatile uint32_t PDREG_CHK_DATA0;
    volatile uint32_t PDREG_CHK_DATA1;
    volatile uint32_t PDREG_CHK_DATA2;
    volatile uint32_t PDREG_CHK_DATA3;
    volatile uint32_t PDREG_CHK_DATA4;
    volatile uint32_t PDREG_CHK_DATA5;
    volatile uint32_t PDREG_CHK_DATA6;
    volatile uint32_t PDREG_CHK_DATA7;
    volatile uint32_t PDREG_CHK_DATA8;
    volatile uint32_t PDREG_CHK_DATA9;
    volatile uint32_t PDREG_CHK_DATA10;
    volatile uint32_t PDREG_CHK_DATA11;
    volatile uint32_t PDREG_CHK_DATA12;
    volatile uint32_t PDREG_CHK_DATA13;
    volatile uint32_t PDREG_CHK_DATA14;
    volatile uint32_t PDREG_CHK_DATA15;
    volatile uint32_t PDREG_CHK_DATA16;
    volatile uint32_t PDREG_CHK_DATA17;
    volatile uint32_t PDREG_CHK_DATA18;
    volatile uint32_t PDREG_CHK_DATA19;
    volatile uint32_t PDREG_CHK_DATA20;
    volatile uint32_t PDREG_CHK_DATA21;
    volatile uint32_t PDREG_CHK_DATA22;
    volatile uint32_t PDREG_CHK_DATA23;
    volatile uint32_t PDREG_CHK_DATA24;
    volatile uint32_t PDREG_CHK_DATA25;
    volatile uint32_t PDREG_CHK_DATA26;
    volatile uint32_t PDREG_CHK_DATA27;
    volatile uint32_t PDREG_CHK_DATA28;
    volatile uint32_t PDREG_CHK_DATA29;
    volatile uint32_t PDREG_CHK_DATA30;
    volatile uint32_t PDREG_CHK_DATA31;
}IRRX_REGISTER_T;
# 404 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h" 1
# 38 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t level1_cnt :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t reg_level1_cnt;
} REG_LEVEL1_CNT_T;

typedef union {
    struct {
        volatile uint32_t level2_cnt :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t reg_level2_cnt;
} REG_LEVEL2_CNT_T;

typedef struct{
    REG_LEVEL1_CNT_T level1_cnt_t;
    REG_LEVEL2_CNT_T level2_cnt_t;
}REG_LEVEL_CNT_T;


typedef union {
    struct {
        volatile uint32_t reg_value_unit00 :2;
        volatile uint32_t reg_value_unit01 :2;
        volatile uint32_t reg_value_unit02 :2;
        volatile uint32_t reg_value_unit03 :2;
        volatile uint32_t reg_value_unit04 :2;
        volatile uint32_t reg_value_unit05 :2;
        volatile uint32_t reg_value_unit06 :2;
        volatile uint32_t reg_value_unit07 :2;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_LEVEL_VALUE0_T;
# 94 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_value_unit08 :2;
        volatile uint32_t reg_value_unit09 :2;
        volatile uint32_t reg_value_unit10 :2;
        volatile uint32_t reg_value_unit11 :2;
        volatile uint32_t reg_value_unit12 :2;
        volatile uint32_t reg_value_unit13 :2;
        volatile const uint32_t __reserved_00 :20;
    } field;
    volatile uint32_t word;
} REG_LEVEL_VALUE1_T;
# 122 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_ir_tx_total_cycle_cnt_1:16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_TOTAL_CNT1_T;


typedef union {
    struct {
        volatile uint32_t reg_ir_tx_total_cycle_cnt_0:16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_TOTAL_CNT0_T;


typedef union {
    struct {
        volatile uint32_t reg_ir_tx_wait_value_0080 :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t reg_ir_tx_ckdiv_num_0080 :8;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} REG_0080_IR_TX_0_T;
# 157 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_ir_tx_carrier_hcnt_0084 :8;
        volatile uint32_t reg_ir_tx_carrier_lcnt_0084 :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_0084_IR_TX_0_T;
# 173 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_ir_tx_en_0088 :1;
        volatile uint32_t reg_ir_tx_rstz_0088 :1;
        volatile uint32_t reg_ir_tx_int_en_0088 :1;
        volatile uint32_t reg_ir_tx_out_inv_baseband_0088 :1;
        volatile uint32_t reg_ir_tx_carrier_en_0088 :1;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t reg_ir_tx_test_sel_0088 :2;
        volatile uint32_t reg_ir_tx_out_inv_0088 :1;
        volatile const uint32_t __reserved_01 :21;
    } field;
    volatile uint32_t word;
} REG_0088_IR_TX_0_T;
# 205 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_ir_tx_trigger_008C :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} REG_008C_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_done_flag_0090 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} REG_0090_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_ir_tx_clr_done_flag_0094 :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} REG_0094_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_reserved00_0098 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_0098_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_reserved01_009C :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_009C_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_reserved02_00A0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00A0_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_reserved03_00A4 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00A4_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_bist_fail_00A8 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00A8_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_dbg_bus_0_00AC :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00AC_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_dbg_bus_1_00B0 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00B0_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_dbg_bus_2_00B4 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00B4_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_ir_tx_dbg_bus_3_00B8 :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_00B8_IR_TX_0_T;






typedef union {
    struct {
        volatile uint32_t reg_ir_tx_xmp_1_en_0100 :1;
        volatile const uint32_t __reserved_00 :7;
        volatile uint32_t reg_ir_tx_xmp_1_start_unit_0100 :4;
        volatile uint32_t reg_ir_tx_xmp_1_data_unit_0100 :4;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} REG_0100_IR_TX_0_T;
# 381 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_ir_tx_xmp_1_packet_size_0104:16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_0104_IR_TX_0_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :8;
        volatile uint32_t reg_addr_auto_inc :1;
        volatile const uint32_t __reserved_01 :3;
        volatile uint32_t reg_key :4;
        volatile const uint32_t __reserved_02 :16;
    } field;
    volatile uint32_t word;
} REG_1004_IR_TX_MEM_0_T;
# 412 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_irtx.h"
typedef union {
    struct {
        volatile uint32_t reg_addr :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_1108_IR_TX_MEM_0_T;






typedef union {
    struct {
        volatile uint32_t reg_sram_wd :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_1118_IR_TX_MEM_0_T;






typedef union {
    struct {
        volatile const uint32_t reg_sram_rd :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} REG_1120_IR_TX_MEM_0_T;





typedef struct {
    REG_LEVEL_CNT_T reg_level_cnt[14];
    REG_LEVEL_VALUE0_T reg_level_value_0;
    REG_LEVEL_VALUE1_T reg_level_value_1;
    REG_TOTAL_CNT1_T reg_total_cnt_1;
    REG_TOTAL_CNT0_T reg_total_cnt_0;
    REG_0080_IR_TX_0_T reg_0080_ir_tx_0;
    REG_0084_IR_TX_0_T reg_0084_ir_tx_0;
    REG_0088_IR_TX_0_T reg_0088_ir_tx_0;
    REG_008C_IR_TX_0_T reg_008c_ir_tx_0;
    REG_0090_IR_TX_0_T reg_0090_ir_tx_0;
    REG_0094_IR_TX_0_T reg_0094_ir_tx_0;
    REG_0098_IR_TX_0_T reg_0098_ir_tx_0;
    REG_009C_IR_TX_0_T reg_009c_ir_tx_0;
    REG_00A0_IR_TX_0_T reg_00a0_ir_tx_0;
    REG_00A4_IR_TX_0_T reg_00a4_ir_tx_0;
    REG_00A8_IR_TX_0_T reg_00a8_ir_tx_0;
    REG_00AC_IR_TX_0_T reg_00ac_ir_tx_0;
    REG_00B0_IR_TX_0_T reg_00b0_ir_tx_0;
    REG_00B4_IR_TX_0_T reg_00b4_ir_tx_0;
    REG_00B8_IR_TX_0_T reg_00b8_ir_tx_0;
    uint32_t __reserved_00[17];
    REG_0100_IR_TX_0_T reg_0100_ir_tx_0;
    REG_0104_IR_TX_0_T reg_0104_ir_tx_0;
    uint32_t __reserved_01[959];
    REG_1004_IR_TX_MEM_0_T reg_1004_ir_tx_mem_0;
    uint32_t __reserved_02[64];
    REG_1108_IR_TX_MEM_0_T reg_1108_ir_tx_mem_0;
    uint32_t __reserved_03[3];
    REG_1118_IR_TX_MEM_0_T reg_1118_ir_tx_mem_0;
    uint32_t __reserved_04[1];
    REG_1120_IR_TX_MEM_0_T reg_1120_ir_tx_mem_0;
} IRTX_REGISTER_T;
# 405 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpio.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_gpio.h"
typedef struct
{
    volatile uint32_t GPIO_DIR[2];
    volatile uint32_t RESERVED0[2];
    volatile uint32_t GPIO_DOUT[2];
    volatile uint32_t RESERVED1[2];
    volatile uint32_t GPIO_DIN[2];
    volatile uint32_t RESERVED2[2];
    volatile uint32_t GPIO_MODE[6];
    volatile uint32_t RESERVED3[2];
    volatile uint32_t GPIO_BACKUP;
    volatile uint32_t RESERVED4[47];

    volatile uint32_t GPIO_DIR_SET[2];
    volatile uint32_t RESERVED5[2];
    volatile uint32_t GPIO_DIR_CLR[2];
    volatile uint32_t RESERVED6[6];
    volatile uint32_t GPIO_DOUT_SET[2];
    volatile uint32_t RESERVED7[2];
    volatile uint32_t GPIO_DOUT_CLR[2];
    volatile uint32_t RESERVED8[42];

    volatile uint32_t GPIO_MODE_SET[6];
    volatile uint32_t RESERVED9[58];

    volatile uint32_t GPIO_MODE_CLR[6];
} GPIO_BASE_REGISTER_T;

typedef struct
{
    volatile uint32_t RW;
    volatile uint32_t SET;
    volatile uint32_t CLR;
    uint32_t RESERVED1;
} GPIO_CFG_REGISTER_T;

typedef struct
{
    GPIO_CFG_REGISTER_T GPIO_DRV[2];
    GPIO_CFG_REGISTER_T GPIO_EH;
    GPIO_CFG_REGISTER_T GPIO_G;
    GPIO_CFG_REGISTER_T GPIO_IES;
    GPIO_CFG_REGISTER_T GPIO_PD;
    GPIO_CFG_REGISTER_T GPIO_PU4P7K;
    GPIO_CFG_REGISTER_T GPIO_PU;
    GPIO_CFG_REGISTER_T GPIO_RSEL;
    GPIO_CFG_REGISTER_T GPIO_SMT;
    GPIO_CFG_REGISTER_T GPIO_SR;
    GPIO_CFG_REGISTER_T GPIO_TDSEL;
    GPIO_CFG_REGISTER_T GPIO_DUMMY;
    volatile uint32_t RESERVED[4];
    GPIO_CFG_REGISTER_T GPIO_RTC_IN_EN;
    GPIO_CFG_REGISTER_T GPIO_RTC_GPIO_MODE[2];
} GPIO_CFG0_REGISTER_T;

typedef struct
{
    GPIO_CFG_REGISTER_T GPIO_DRV[2];
    GPIO_CFG_REGISTER_T GPIO_EH;
    GPIO_CFG_REGISTER_T GPIO_G;
    GPIO_CFG_REGISTER_T GPIO_IES;
    GPIO_CFG_REGISTER_T GPIO_PD;
    GPIO_CFG_REGISTER_T GPIO_PU4P7K;
    GPIO_CFG_REGISTER_T GPIO_PU;
    GPIO_CFG_REGISTER_T GPIO_RSEL;
    GPIO_CFG_REGISTER_T GPIO_SMT;
    GPIO_CFG_REGISTER_T GPIO_SR;
    GPIO_CFG_REGISTER_T GPIO_TDSEL;
    GPIO_CFG_REGISTER_T GPIO_DUMMY;
    volatile uint32_t RESERVED[8];
    GPIO_CFG_REGISTER_T GPIO_RTC_IN_EN;
    GPIO_CFG_REGISTER_T GPIO_RTC_GPIO_MODE[2];
} GPIO_CFG1_REGISTER_T;
# 406 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_i3c.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_i3c.h"
typedef struct {
    volatile uint32_t SOFT_RESET;
    volatile uint32_t IO_CONFIG;
    volatile uint32_t CLOCK_DIV;
    volatile uint32_t H_TIMING;
    volatile uint32_t L_TIMING;
    volatile uint32_t HS;
    volatile uint32_t EXT_CONF;
    volatile uint32_t CONTROL;
    volatile uint32_t MULTIMAS;
    volatile uint32_t TRANSFER_LEN;
    volatile uint32_t TRANSFER_LEN_AUX;
    volatile uint32_t TRANSAC_LEN;
    volatile uint32_t FIFO_THRESH;
    volatile uint32_t DATA_TIMING;
    volatile uint32_t TIMEOUT_DIV;
    volatile uint32_t IBI_TIMING;
    volatile uint32_t SLAVE_ADDR;
    volatile uint32_t DELAY_LEN;
    volatile uint32_t INTR_MASK;
    volatile uint32_t START;
    volatile uint8_t DATA_PORT;
    volatile uint8_t RESERVE_0x[3];
    volatile uint32_t FIFO_ADDR_CLR;
    volatile uint32_t INTR_STA;
    volatile uint32_t DEF_DA;
    volatile uint32_t HFIFO_DATA;
    volatile uint32_t TRAFFIC;
    volatile uint32_t SHAPE;
    volatile uint32_t ERROR;
    volatile uint32_t DEBUG_STAT;
    volatile uint32_t DEBUG_CTRL;
    volatile uint32_t FIFO_STAT;
    volatile uint32_t HFIFO_STAT;
}I3C_MASTER_REGISTER_T;
# 269 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_i3c.h"
enum {
    I3C_HFIFO_DATA_NINTH_BIT_IGNORE = 0,
    I3C_HFIFO_DATA_NINTH_BIT_ACK,
    I3C_HFIFO_DATA_NINTH_BIT_NACK,
    I3C_HFIFO_DATA_NINTH_BIT_PARITY
};
# 305 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_i3c.h"
typedef struct {
    volatile uint32_t GLB_STA;
    volatile uint32_t RESERVE_0004;
    volatile uint32_t GLB_CPU0_CFG;
    volatile uint32_t GLB_CPU0_SET;

    volatile uint32_t GLB_CPU0_CLR;
    volatile uint32_t GLB_CPU1_CFG;
    volatile uint32_t GLB_CPU1_SET;
    volatile uint32_t GLB_CPU1_CLR;

    volatile uint32_t GLB_SWRST;
    volatile uint32_t RESERVE_24;
    volatile uint32_t GLB_LIMITER;
    volatile uint32_t RESERVE_002C;

    volatile uint32_t GLB_DBG;
    volatile uint32_t RESERVE_003X[3];

    volatile uint32_t GLB_BUSY;
    volatile uint32_t GLB_INTR;
    volatile uint32_t RESERVE_004X[2];

    volatile uint32_t GLB_CPU2_CFG;
    volatile uint32_t GLB_CPU2_SET;
    volatile uint32_t GLB_CPU2_CLR;
    volatile uint32_t RESERVE_005C;

    volatile uint32_t GLB_CPU3_CFG;
    volatile uint32_t GLB_CPU3_SET;
    volatile uint32_t GLB_CPU3_CLR;
    volatile uint32_t RESERVE_006C;

    volatile uint32_t GLB_CLK_CFG;
    volatile uint32_t GLB_CLK_SET;
    volatile uint32_t GLB_CLK_CLR;
    volatile uint32_t RESERVE_007C;

    volatile uint32_t RESERVE_008X[4];
    volatile uint32_t RESERVE_009X[4];
    volatile uint32_t RESERVE_00AX[4];
    volatile uint32_t RESERVE_00BX[4];
    volatile uint32_t RESERVE_00CX[4];
    volatile uint32_t RESERVE_00DX[4];
    volatile uint32_t RESERVE_00EX[4];
    volatile uint32_t RESERVE_00FX[4];

    volatile uint32_t RESERVE_010X[2];
    volatile uint32_t PDMA1_WPPT;
    volatile uint32_t PDMA1_WPTO;

    volatile uint32_t PDMA1_COUNT;
    volatile uint32_t PDMA1_CON;
    volatile uint32_t PDMA1_START;
    volatile uint32_t PDMA1_INTSTA;

    volatile uint32_t PDMA1_ACKINT;
    volatile uint32_t PDMA1_RLCT;
    volatile uint32_t PDMA1_LIMITER;
    volatile uint32_t PDMA1_PGMADDR;

    volatile uint32_t RESERVE_01XX[52];

    volatile uint32_t RESERVE_02XX[2];
    volatile uint32_t PDMA2_WPPT;
    volatile uint32_t PDMA2_WPTO;

    volatile uint32_t PDMA2_COUNT;
    volatile uint32_t PDMA2_CON;
    volatile uint32_t PDMA2_START;
    volatile uint32_t PDMA2_INTSTA;

    volatile uint32_t PDMA2_ACKINT;
    volatile uint32_t PDMA2_RLCT;
    volatile uint32_t PDMA2_LIMITER;
    volatile uint32_t PDMA2_PGMADDR;

}I2C_PDMA_REGISTER_T;
# 407 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h" 1
# 44 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED0_EN :1;
        volatile uint32_t LED1_EN :1;
        volatile uint32_t LED2_EN :1;
        volatile uint32_t LED3_EN :1;
        volatile const uint32_t __reserved_00 :4;
        volatile uint32_t LED0_DIS_WHEN_IDLE :1;
        volatile uint32_t LED1_DIS_WHEN_IDLE :1;
        volatile uint32_t LED2_DIS_WHEN_IDLE :1;
        volatile const uint32_t __reserved_01 :13;
        volatile const uint32_t LED0_EN_SYS_SW :1;
        volatile const uint32_t LED1_EN_SYS_SW :1;
        volatile const uint32_t LED2_EN_SYS_SW :1;
        volatile const uint32_t LED3_EN_SYS_SW :1;
        volatile const uint32_t __reserved_02 :4;
    } field;
    volatile uint32_t word;
} LED_EN_CTRL_T;
# 89 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED_LP_EN :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} LED_GBL_CTRL_T;






typedef union {
    struct {
        volatile uint32_t LED_T1T2_REPEAT :4;
        volatile uint32_t LED_REPEAT :1;
        volatile uint32_t LED_INVERT :1;
        volatile const uint32_t __reserved_00 :10;
        volatile uint32_t LED_FW_EN :1;
        volatile uint32_t LED_FW_SEL :2;
        volatile uint32_t LED_FW_RETRIG :1;
        volatile uint32_t LED_FW_T1T2 :1;
        volatile const uint32_t __reserved_01 :11;
    } field;
    volatile uint32_t word;
} LED_CON0_T;
# 134 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED_UNIT :8;
        volatile uint32_t LED_XN :2;
        volatile const uint32_t __reserved_00 :22;
    } field;
    volatile uint32_t word;
} LED_UNIT_T;
# 150 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED_T0 :8;
        volatile uint32_t LED_T1 :8;
        volatile uint32_t LED_T2 :8;
        volatile uint32_t LED_T3 :8;
    } field;
    volatile uint32_t word;
} LED_PERIOD0_T;
# 171 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED_PWM_LOAD_EN :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} LED_PWM0_T;






typedef union {
    struct {
        volatile uint32_t LED_PWM_PERIOD :8;
        volatile uint32_t LED_PWM_DURATION :8;
        volatile uint32_t LED_PWM_DURATION2 :8;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} LED_PWM1_T;
# 203 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED_PWM_ONSTEP :8;
        volatile uint32_t LED_PWM_OFFSTEP :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} LED_PWM2_T;







typedef union {
    struct {
        volatile const uint32_t __reserved_00 :5;
        volatile uint32_t LED3_INVERT :1;
        volatile const uint32_t __reserved_01 :26;
    } field;
    volatile uint32_t word;
} LED3_CON0_T;






typedef union {
    struct {
        volatile uint32_t LED3_PWM_PERIOD :8;
        volatile uint32_t LED3_PWM_DURATION :8;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} LED3_PWM1_T;
# 248 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t RG_LED0_EN_SW_MODE :1;
        volatile uint32_t RG_LED0_EN_SW :1;
        volatile const uint32_t __reserved_00 :6;
        volatile uint32_t RG_LED1_EN_SW_MODE :1;
        volatile uint32_t RG_LED1_EN_SW :1;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t RG_LED2_EN_SW_MODE :1;
        volatile uint32_t RG_LED2_EN_SW :1;
        volatile const uint32_t __reserved_02 :6;
        volatile uint32_t RG_LED3_EN_SW_MODE :1;
        volatile uint32_t RG_LED3_EN_SW :1;
        volatile const uint32_t __reserved_03 :6;
    } field;
    volatile uint32_t word;
} LED_DBG_CTRL_T;
# 285 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile const uint32_t LED0_DONE_INTR :1;
        volatile const uint32_t LED1_DONE_INTR :1;
        volatile const uint32_t LED2_DONE_INTR :1;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} LED_INTR_STS_T;
# 304 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED0_DONE_INTR_CLR :1;
        volatile uint32_t LED1_DONE_INTR_CLR :1;
        volatile uint32_t LED2_DONE_INTR_CLR :1;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} LED_INTR_CLR_T;
# 323 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED0_DONE_INTR_EN :1;
        volatile uint32_t LED1_DONE_INTR_EN :1;
        volatile uint32_t LED2_DONE_INTR_EN :1;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} LED_INTR_EN_T;
# 342 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef union {
    struct {
        volatile uint32_t LED0_DONE_INTR_MSK :1;
        volatile uint32_t LED1_DONE_INTR_MSK :1;
        volatile uint32_t LED2_DONE_INTR_MSK :1;
        volatile const uint32_t __reserved_00 :29;
    } field;
    volatile uint32_t word;
} LED_INTR_MSK_T;
# 360 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_led_ctrl.h"
typedef struct {
    LED_CON0_T led_con0;
    LED_UNIT_T led_unit;
    LED_PERIOD0_T led_period0;
    uint32_t __reserved_02[1];
    LED_PWM0_T led_pwm0;
    LED_PWM1_T led_pwm1;
    LED_PWM2_T led_pwm2;
    uint32_t __reserved_03[9];
}LED_STRUCT_T;


typedef struct {
    LED_EN_CTRL_T led_en_ctrl;
    uint32_t __reserved_00[15];
    LED_GBL_CTRL_T led_gbl_ctrl;
    uint32_t __reserved_01[47];
    LED_STRUCT_T led_struct[3];
    LED3_CON0_T led3_con0;
    uint32_t __reserved_08[4];
    LED3_PWM1_T led3_pwm1;
    uint32_t __reserved_09[138];
    LED_DBG_CTRL_T led_dbg_ctrl;
    uint32_t __reserved_10[63];
    LED_INTR_STS_T led_intr_sts;
    LED_INTR_CLR_T led_intr_clr;
    LED_INTR_EN_T led_intr_en;
    LED_INTR_MSK_T led_intr_msk;
} LED_CONTROL_REGISTER_T;
# 408 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_hw_keyscan.h" 1
# 36 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_hw_keyscan.h"
typedef struct
{
  union
  {
    struct
    {
      volatile uint8_t SFR_ROW_NUM;
      volatile uint8_t SFR_COL_NUM;
      volatile const uint8_t RESERVED[2];
    } MATRIX_SIZE_CELLS;
    volatile uint32_t MATRIX_SIZE;
  } MATRIX_SIZE_UNION;

  volatile uint32_t SFR_SCAN_MODE;
  volatile uint32_t SFR_IO_SW_TIME_SEL;
  volatile uint32_t SFR_KEYSCAN_RATE_DLY_SEL;
  volatile uint32_t SFR_DEB_EN;
  volatile uint32_t SFR_RLS_DEB_TIME;
  volatile uint32_t SFR_PRS_DEB_TIME;

  volatile uint32_t SFR_COL_MAP[18];
  volatile uint32_t SFR_ROW_MAP[8];

  volatile uint32_t SFR_KB_TYPE;
  volatile uint32_t SFR_COL_IN_SETTING;
  volatile uint32_t SFR_KEYSCAN_IO_EN;
  volatile uint32_t SFR_KEYSCAN_EN;
  volatile uint32_t AFIFO_DOUT;

  union
  {
    struct
    {
      volatile uint8_t AFIFO_DNUM;
      volatile uint8_t AFIFO_EMPTY;
      volatile uint8_t AFIFO_FULL_SYNC;
      volatile uint8_t FIFO_STOP_FLAG;
    } AFIFO_STATUS_CELLS;
    volatile uint32_t AFIFO_STATUS;
  } AFIFO_STATUS_UNION;

  volatile uint32_t RESERVED[25];
  volatile uint32_t GHOST_KEY;
  volatile uint32_t SFR_IRQ_CLEAR;
  volatile uint32_t SOFT_RST;

  union
  {
    struct
    {
      volatile uint8_t DEB_DONE_SYNC;
      volatile uint8_t KEYSCAN_READ_SYNC;
      volatile uint8_t RESERVED[2];
    } STATUS_CELLS;
    volatile uint32_t STATUS;
  } STATUS_UNION;
} HW_KEYSCAN_REGISTER_T;
# 409 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_qdec.h" 1
# 36 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_qdec.h"
typedef struct
{
  union
  {
    struct
    {
      volatile uint8_t LED_POL;
      volatile uint8_t LED_FORCE_OFF;
      volatile const uint8_t RESERVED[2];
    } QDEC_LED_CON_CELLS;
    volatile uint32_t QDEC_LEED_CON;
  } QDEC_LED_CON_UNION;

  union
  {
    struct
    {
      volatile uint16_t Z_SUM_THR;
      volatile uint8_t Z_COUNT_THR;
      volatile uint8_t Z_DIV;
    } QDEC_SAMPLE_THR_CELLS;
    volatile uint32_t QDEC_SAMPLE_THR;
  } QDEC_SAMPLE_THR_UNION;

  union
  {
    struct
    {
      volatile uint16_t SMP_PERIOD_A;
      volatile uint8_t LED_PERIOD_A;
      volatile uint8_t DBC_COUNT_A;
    } QDEC_SAMPLE_CON_A_CELLS;
    volatile uint32_t QDEC_SAMPLE_CON_A;
  } QDEC_SAMPLE_CON_A_UNION;

  union
  {
    struct
    {
      volatile uint16_t SMP_PERIOD_B;
      volatile uint8_t LED_PERIOD_B;
      volatile uint8_t DBC_COUNT_B;
    } QDEC_SAMPLE_CON_B_CELLS;
    volatile uint32_t QDEC_SAMPLE_CON_B;
  } QDEC_SAMPLE_CON_B_UNION;

  union
  {
    struct
    {
      volatile uint8_t SW_RELOAD;
      volatile uint8_t QDEC_ENABLE;
      volatile const uint8_t RESERVED;
      volatile uint8_t SW_RSTB;
    } QDEC_CON_CELLS;
    volatile uint32_t QDEC_CON;
  } QDEC_CON_UNION;

  union
  {
    struct
    {
      volatile uint8_t SEL_GROUP;
      volatile uint8_t HW_SEL_EN;
      volatile uint8_t HW_SEL_GROUP;
      volatile const uint8_t RESERVED;
    } QDEC_SEL_GROUP_CELLS;
    volatile uint32_t QDEC_SEL_GROUP;
  } QDEC_SEL_GROUP_UNION;

  volatile uint32_t RESERVED1[2];

  union
  {
    struct
    {
      volatile uint8_t IRQ_ENABLE_Z_SUM;
      volatile uint8_t IRQ_ENABLE_Z_CNT;
      volatile uint8_t IRQ_ENABLE_DATA_RDY;
      volatile const uint8_t RESERVED;
    } QDEC_IRQ_ENABLE_CELLS;
    volatile uint32_t QDEC_IRQ_ENABLE;
  } QDEC_IRQ_ENABLE_UNION;

  union
  {
    struct
    {
      volatile uint8_t WKUP_ENABLE_Z_SUM;
      volatile uint8_t WKUP_ENABLE_Z_CNT;
      volatile const uint8_t RESERVED[2];
    } QDEC_WKUP_ENABLE_CELLS;
    volatile uint32_t QDEC_WKUP_ENABLE;
  } QDEC_WKUP_ENABLE_UNION;

  union
  {
    struct
    {
      volatile uint8_t LATCH_N_CLR;
      volatile const uint8_t LATCH_STATUS;
      volatile const uint8_t RESERVED[2];
    } QDEC_LATCH_N_CLR_CELLS;
    volatile uint32_t QDEC_LATCH_N_CLR;
  } QDEC_LATCH_N_CLR_UNION;

  union
  {
    struct
    {
      volatile uint8_t IRQ_CLR_Z_THR_NOTIFY;
      volatile uint8_t IRQ_CLR_Z_THR_EVENT;
      volatile uint8_t IRQ_CLR_DATA_RDY;
      volatile const uint8_t RESERVED;
    } QDEC_IRQ_LCR_CELLS;
    volatile uint32_t QDEC_IRQ_LCR;
  } QDEC_IRQ_LCR_UNION;

  union
  {
    struct
    {
      volatile uint8_t WKUP_LCR_Z_THR_NOTIFY;
      volatile uint8_t WKUP_LCR_Z_THR_EVENT;
      volatile const uint8_t RESERVED[2];
    } QDEC_WKUP_LCR_CELLS;
    volatile uint32_t QDEC_WKUP_LCR;
  } QDEC_WKUP_LCR_UNION;

  union
  {
    struct
    {
      volatile const uint16_t Z_SUM;
      volatile const uint16_t Z_CNT;
    } QDEC_Z_INFO_CELLS;
    volatile const uint32_t QDEC_Z_INFO;
  } QDEC_Z_INFO_UNION;

  union
  {
    struct
    {
      volatile const uint16_t SMP_CNT;
      volatile const uint16_t INVALID_CNT;
    } QDEC_SAMPLE_INFO_CELLS;
    volatile const uint32_t QDEC_SAMPLE_INFO;
  } QDEC_SAMPLE_INFO_UNION;

  volatile uint32_t RESERVED2[2];

  union
  {
    struct
    {
      volatile uint8_t SW_RELOAD_CLR;
      volatile const uint8_t SW_RELOAD_STATUS;
      volatile const uint8_t RESERVED[2];
    } QDEC_SW_RELOAD_CLR_CELLS;
    volatile uint32_t QDEC_SW_RELOAD_CLR;
  } QDEC_SW_RELOAD_CLR_UNION;

  union
  {
    struct
    {
      volatile const uint8_t QDEC_STATE;
      volatile const uint8_t QDEC_SEL_GROUP;
      volatile const uint8_t RESERVED[2];
    } QDEC_INFO_CELLS;
    volatile uint32_t QDEC_INFO;
  } QDEC_INFO_UNION;

  union
  {
    struct
    {
      volatile const uint8_t IRQ_STATUS_Z_SUM;
      volatile const uint8_t IRQ_STATUS_Z_CNT;
      volatile const uint8_t IRQ_STATUS_DATA_RDY;
      volatile const uint8_t RESERVED[1];
    } QDEC_IRQ_STATUS_CELLS;
    volatile const uint32_t QDEC_IRQ_STATUS;
  } QDEC_IRQ_STATUS_UNION;

  union
  {
    struct
    {
      volatile const uint8_t WKUP_STATUS_Z_SUM;
      volatile const uint8_t WKUP_STATUS_Z_CNT;
      volatile const uint8_t RESERVED[2];
    } QDEC_WKUP_STATUS_CELLS;
    volatile uint32_t QDEC_WKUP_STATUS;
  } QDEC_WKUP_STATUS_UNION;

  union
  {
    struct
    {
      volatile const uint8_t IRQ_EVENT_STATUS_Z_SUM;
      volatile const uint8_t IRQ_EVENT_STATUS_Z_CNT;
      volatile const uint8_t RESERVED[2];
    } QDEC_IRQ_EVENT_STATUS_CELLS;
    volatile uint32_t QDEC_IRQ_EVENT_STATUS;
  } QDEC_IRQ_EVENT_STATUS_UNION;

  union
  {
    struct
    {
      volatile const uint8_t WKUP_EVENT_STATUS_Z_SUM;
      volatile const uint8_t WKUP_EVENT_STATUS_Z_CNT;
      volatile const uint8_t RESERVED[2];
    } QDEC_WKUP_EVENT_STATUS_CELLS;
    volatile uint32_t QDEC_WKUP_EVENT_STATUS;
  } QDEC_WKUP_EVENT_STATUS_UNION;

  volatile uint32_t RESERVED3;

  volatile uint32_t QDEC_DEBUG_SEL;
  volatile const uint32_t QDEC_DEBUG_ADDR;

} HW_QDEC_REGISTER_T;
# 410 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h" 1
# 40 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t RUN_TX :1;
        volatile const uint32_t IT_TX :1;
        volatile const uint32_t RUN_RX :1;
        volatile const uint32_t IT_RX :1;
        volatile const uint32_t __reserved_00 :28;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLBSTA_T;
# 62 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t CPU0_CFG_TX :1;
        volatile const uint32_t CPU0_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU0_CFG_T;
# 78 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU0_SET_TX :1;
        volatile uint32_t CPU0_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU0_SET_T;
# 94 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU0_CLR_TX :1;
        volatile uint32_t CPU0_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU0_CLR_T;
# 110 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t CPU1_CFG_TX :1;
        volatile const uint32_t CPU1_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU1_CFG_T;
# 126 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU1_SET_TX :1;
        volatile uint32_t CPU1_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU1_SET_T;
# 142 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU1_CLR_TX :1;
        volatile uint32_t CPU1_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU1_CLR_T;
# 158 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t SW_RESET :1;
        volatile const uint32_t __reserved_00 :31;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_SWRST_T;






typedef union {
    struct {
        volatile uint32_t LIMITER :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLBLIMITER_T;






typedef union {
    struct {
        volatile const uint32_t CC :32;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_DBG_T;






typedef union {
    struct {
        volatile const uint32_t RUN_TX :1;
        volatile const uint32_t RUN_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_BUSY_T;
# 212 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t IT_TX :1;
        volatile const uint32_t IT_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_INTR_T;
# 228 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t CPU2_CFG1 :1;
        volatile const uint32_t CPU2_CFG2 :1;
        volatile const uint32_t CPU2_CFG3 :1;
        volatile const uint32_t CPU2_CFG4 :1;
        volatile const uint32_t CPU2_CFG5 :1;
        volatile const uint32_t CPU2_CFG6 :1;
        volatile const uint32_t CPU2_CFG7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU2_CFG_T;
# 259 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU2_SET1 :1;
        volatile uint32_t CPU2_SET2 :1;
        volatile uint32_t CPU2_SET3 :1;
        volatile uint32_t CPU2_SET4 :1;
        volatile uint32_t CPU2_SET5 :1;
        volatile uint32_t CPU2_SET6 :1;
        volatile uint32_t CPU2_SET7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU2_SET_T;
# 290 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU2_CLR1 :1;
        volatile uint32_t CPU2_CLR2 :1;
        volatile uint32_t CPU2_CLR3 :1;
        volatile uint32_t CPU2_CLR4 :1;
        volatile uint32_t CPU2_CLR5 :1;
        volatile uint32_t CPU2_CLR6 :1;
        volatile uint32_t CPU2_CLR7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU2_CLR_T;
# 321 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t CPU3_CFG1 :1;
        volatile const uint32_t CPU3_CFG2 :1;
        volatile const uint32_t CPU3_CFG3 :1;
        volatile const uint32_t CPU3_CFG4 :1;
        volatile const uint32_t CPU3_CFG5 :1;
        volatile const uint32_t CPU3_CFG6 :1;
        volatile const uint32_t CPU3_CFG7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU3_CFG_T;
# 352 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU3_SET1 :1;
        volatile uint32_t CPU3_SET2 :1;
        volatile uint32_t CPU3_SET3 :1;
        volatile uint32_t CPU3_SET4 :1;
        volatile uint32_t CPU3_SET5 :1;
        volatile uint32_t CPU3_SET6 :1;
        volatile uint32_t CPU3_SET7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU3_SET_T;
# 383 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CPU3_CLR1 :1;
        volatile uint32_t CPU3_CLR2 :1;
        volatile uint32_t CPU3_CLR3 :1;
        volatile uint32_t CPU3_CLR4 :1;
        volatile uint32_t CPU3_CLR5 :1;
        volatile uint32_t CPU3_CLR6 :1;
        volatile uint32_t CPU3_CLR7 :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CPU3_CLR_T;
# 414 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t CLK_CFG_TX :1;
        volatile const uint32_t CLK_CFG_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CLK_CFG_T;
# 430 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CLK_SET_TX :1;
        volatile uint32_t CLK_SET_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CLK_SET_T;
# 446 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t CLK_CLR_TX :1;
        volatile uint32_t CLK_CLR_RX :1;
        volatile const uint32_t __reserved_00 :30;
    } field;
    volatile uint32_t word;
} ARGB_DMA_GLB_CLK_CLR_T;
# 462 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t WPPT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_WPPT_T;






typedef union {
    struct {
        volatile uint32_t WPTO :32;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_WPTO_T;






typedef union {
    struct {
        volatile uint32_t COUNT :16;
        volatile uint32_t PKTCNT :8;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_COUNT_T;
# 503 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t DIRECTION :5;
        volatile const uint32_t __reserved_00 :3;
        volatile uint32_t SIZE :2;
        volatile const uint32_t __reserved_01 :6;
        volatile uint32_t SETTING :4;
        volatile const uint32_t __reserved_02 :4;
        volatile uint32_t ITEN :1;
        volatile const uint32_t __reserved_03 :7;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_CON_T;
# 528 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile uint32_t STR :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_START_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile const uint32_t INT :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_INTSTA_T;






typedef union {
    struct {
        volatile const uint32_t __reserved_00 :15;
        volatile uint32_t ACK :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_ACKINT_T;






typedef union {
    struct {
        volatile const uint32_t RLCT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_RLCT_T;






typedef union {
    struct {
        volatile uint32_t LIMITER :8;
        volatile const uint32_t __reserved_00 :24;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_LIMITER_T;






typedef union {
    struct {
        volatile uint32_t PGMADDR :32;
    } field;
    volatile uint32_t word;
} ARGB_PDMA_TX_PGMADDR_T;






typedef union {
    struct {
        volatile uint32_t ONE_L_VAL :8;
        volatile uint32_t ONE_H_VAL :8;
        volatile uint32_t ZERO_L_VAL :8;
        volatile uint32_t ZERO_H_VAL :8;
    } field;
    volatile uint32_t word;
} ARGB_CTRL0_T;
# 629 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t RST_VAL :16;
        volatile uint32_t PAT_CNT :8;
        volatile const uint32_t __reserved_00 :1;
        volatile uint32_t ED_BIG :1;
        volatile uint32_t NONALIGN :1;
        volatile uint32_t BIT_NONREV :1;
        volatile uint32_t CLK_DIV :2;
        volatile const uint32_t __reserved_01 :1;
        volatile uint32_t EN_ARGB :1;
    } field;
    volatile uint32_t word;
} ARGB_CTRL1_T;
# 661 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t ARGB_STOP_INT_STS :1;
        volatile uint32_t RST_ST_INT_STS :1;
        volatile uint32_t AUTO_RE_ST_INT_STS :1;
        volatile uint32_t PR_WK_INT_STS :1;
        volatile uint32_t ARGB_DMA_ST_INT_STS :1;
        volatile uint32_t AUTO_OFF_INT_STS :1;
        volatile uint32_t ARGB_DMA_LVL_INT_STS :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_INTR_STS_T;
# 691 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t ARGB_STOP_INT_MSK :1;
        volatile uint32_t RST_ST_INT_MSK :1;
        volatile uint32_t AUTO_RE_ST_INT_MSK :1;
        volatile uint32_t PR_WK_INT_MSK :1;
        volatile uint32_t ARGB_DMA_ST_INT_MSK :1;
        volatile uint32_t AUTO_OFF_INT_MSK :1;
        volatile uint32_t ARGB_DMA_LVL_INT_MSK :1;
        volatile const uint32_t __reserved_00 :25;
    } field;
    volatile uint32_t word;
} ARGB_INTR_MSK_T;
# 721 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t FIFO_WR_PORT :24;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} ARGB_PATT_T;






typedef union {
    struct {
        volatile uint32_t AUTO_MODE :1;
        volatile const uint32_t __reserved_00 :15;
        volatile uint32_t STOP_CNT :16;
    } field;
    volatile uint32_t word;
} ARGB_TCTRL_T;
# 750 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile uint32_t AUTO_TIMER_VAL :24;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} ARGB_TIMER_T;






typedef union {
    struct {
        volatile uint32_t PR_WAKE_VAL :24;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} ARGB_PREWK_T;






typedef union {
    struct {
        volatile uint32_t ARGB_DMA_ST_VAL :24;
        volatile const uint32_t __reserved_00 :8;
    } field;
    volatile uint32_t word;
} ARGB_DMAST_T;






typedef union {
    struct {
        volatile uint32_t ARGB_PKT_CNT :16;
        volatile const uint32_t __reserved_00 :16;
    } field;
    volatile uint32_t word;
} ARGB_PKTCNT_T;






typedef union {
    struct {
        volatile const uint32_t FIFO_LEVEL :11;
        volatile const uint32_t __reserved_00 :3;
        volatile const uint32_t FIFO_EMPTY :1;
        volatile const uint32_t FIFO_FULL :1;
        volatile const uint32_t __reserved_01 :16;
    } field;
    volatile uint32_t word;
} ARGB_DBG0_T;
# 822 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_argb.h"
typedef union {
    struct {
        volatile const uint32_t TIMER_STATE :3;
        volatile const uint32_t ARGB_AUTO_MODE_EN :1;
        volatile const uint32_t __reserved_00 :28;
    } field;
    volatile uint32_t word;
} ARGB_DBG1_T;







typedef struct {
    ARGB_DMA_GLBSTA_T dma_glbsta;
    uint32_t __reserved_00[1];
    ARGB_DMA_GLB_CPU0_CFG_T dma_glb_cpu0_cfg;
    ARGB_DMA_GLB_CPU0_SET_T dma_glb_cpu0_set;
    ARGB_DMA_GLB_CPU0_CLR_T dma_glb_cpu0_clr;
    ARGB_DMA_GLB_CPU1_CFG_T dma_glb_cpu1_cfg;
    ARGB_DMA_GLB_CPU1_SET_T dma_glb_cpu1_set;
    ARGB_DMA_GLB_CPU1_CLR_T dma_glb_cpu1_clr;
    ARGB_DMA_GLB_SWRST_T dma_glb_swrst;
    uint32_t __reserved_01[1];
    ARGB_DMA_GLBLIMITER_T dma_glblimiter;
    uint32_t __reserved_02[1];
    ARGB_DMA_GLB_DBG_T dma_glb_dbg;
    uint32_t __reserved_03[3];
    ARGB_DMA_GLB_BUSY_T dma_glb_busy;
    ARGB_DMA_GLB_INTR_T dma_glb_intr;
    uint32_t __reserved_04[2];
    ARGB_DMA_GLB_CPU2_CFG_T dma_glb_cpu2_cfg;
    ARGB_DMA_GLB_CPU2_SET_T dma_glb_cpu2_set;
    ARGB_DMA_GLB_CPU2_CLR_T dma_glb_cpu2_clr;
    uint32_t __reserved_05[1];
    ARGB_DMA_GLB_CPU3_CFG_T dma_glb_cpu3_cfg;
    ARGB_DMA_GLB_CPU3_SET_T dma_glb_cpu3_set;
    ARGB_DMA_GLB_CPU3_CLR_T dma_glb_cpu3_clr;
    uint32_t __reserved_06[1];
    ARGB_DMA_GLB_CLK_CFG_T dma_glb_clk_cfg;
    ARGB_DMA_GLB_CLK_SET_T dma_glb_clk_set;
    ARGB_DMA_GLB_CLK_CLR_T dma_glb_clk_clr;
    uint32_t __reserved_07[35];
    ARGB_PDMA_TX_WPPT_T pdma_tx_wppt;
    ARGB_PDMA_TX_WPTO_T pdma_tx_wpto;
    ARGB_PDMA_TX_COUNT_T pdma_tx_count;
    ARGB_PDMA_TX_CON_T pdma_tx_con;
    ARGB_PDMA_TX_START_T pdma_tx_start;
    ARGB_PDMA_TX_INTSTA_T pdma_tx_intsta;
    ARGB_PDMA_TX_ACKINT_T pdma_tx_ackint;
    ARGB_PDMA_TX_RLCT_T pdma_tx_rlct;
    ARGB_PDMA_TX_LIMITER_T pdma_tx_limiter;
    ARGB_PDMA_TX_PGMADDR_T pdma_tx_pgmaddr;
    uint32_t __reserved_08[54];
    ARGB_CTRL0_T ctrl0;
    ARGB_CTRL1_T ctrl1;
    ARGB_INTR_STS_T intr_sts;
    ARGB_INTR_MSK_T intr_msk;
    ARGB_PATT_T patt;
    uint32_t __reserved_09[1];
    ARGB_TCTRL_T tctrl;
    ARGB_TIMER_T timer;
    ARGB_PREWK_T prewk;
    ARGB_DMAST_T dmast;
    ARGB_PKTCNT_T pktcnt;
    uint32_t __reserved_10[11];
    ARGB_DBG0_T dbg0;
    ARGB_DBG1_T dbg1;
} ARGB_REGISTER_T;
# 411 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_ramboz.h" 1
# 36 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_ramboz.h"
typedef struct
{
  union
  {
    struct
    {
      volatile uint8_t RAMBOZ_DIRECTION;
      volatile uint8_t RAMBOZ_5CNT_MODE;
      volatile uint8_t IRQ_ENABLE;
      volatile uint8_t WKUP_ENABLE;
    } RAMBOZ_CFG_CELLS;
    volatile uint32_t RAMBOZ_CFG;
  } RAMBOZ_CFG_UNION;

  volatile uint32_t FILTER_PERIOD;
  volatile uint32_t FAST_SAMPLE_PERIOD;
  volatile uint32_t SLOW_SAMPLE_PERIOD;
  volatile uint32_t FAST_ROLL_PERIOD;

  union
  {
    struct
    {
      volatile uint8_t SW_FORCE_FAST_SAMPLE;
      volatile uint8_t SW_FORCE_SLOW_SAMPLE;
      volatile uint8_t SAMPLE_RATE_CHANGE;
      volatile const uint8_t RESERVE;
    } SAMPLE_RATE_CONTROL_CELLS;
    volatile uint32_t SAMPLE_RATE_CONTROL;
  } SAMPLE_RATE_CONTROL_UNION;

  volatile const uint32_t RESERVE1[2];

  volatile uint32_t RAMBOZ_IRQ_MASK;

  union
  {
    struct
    {
      volatile uint8_t IRQ_NOTIFY_CLR;
      volatile uint8_t IRQ_EVENT_CLR;
      volatile const uint8_t RESERVE[2];
    } RAMBOZ_IRQ_CLR_CELLS;
    volatile uint32_t RAMBOZ_IRQ_CLR;
  } RAMBOZ_IRQ_CLR_UNION;

  volatile uint32_t RAMBOZ_WKUP_MASK;

  union
  {
    struct
    {
      volatile uint8_t WKUP_NOTIFY_CLR;
      volatile uint8_t WKUP_EVENT_CLR;
      volatile const uint8_t RESERVE[2];
    } RAMBOZ_WKUP_CLR_CELLS;
    volatile uint32_t RAMBOZ_WKUP_CLR;
  } RAMBOZ_WKUP_CLR_UNION;

  volatile uint32_t RAMBOZ_ENABLE;
  volatile const uint32_t RESERVE2[3];

  volatile uint32_t RAMBOZ_CNT;

  union
  {
    struct
    {
      volatile const uint8_t Z_CNT;
      volatile const uint8_t RESERVE1;
      volatile uint8_t Z_CNT_LATCH_N_CLR;
      volatile const uint8_t RESERVE2;
    } RAMBOZ_Z_CNT_CELLS;
    volatile uint32_t RAMBOZ_Z_CNT;
  } RAMBOZ_Z_CNT_UNION;

  volatile const uint32_t RAMBOZ_IRQ_STATE;

  volatile const uint32_t RAMBOZ_WKUP_STATE;

  union
  {
    struct
    {
      volatile const uint8_t DEBUG_MON;
      volatile const uint8_t RESERVE1;
      volatile uint8_t DEBUG_SEL;
      volatile const uint8_t RESERVE2;
    } RAMBOZ_DEBUG_MON_CELLS;
    volatile uint32_t RAMBOZ_DEBUG_MON;
  } RAMBOZ_DEBUG_MON_UNION;

  union
  {
    struct
    {
      volatile const uint8_t LED_STATE;
      volatile const uint8_t SLEEP_STATE;
      volatile const uint16_t LEDOFF_PERIOD_MUX;
    } RAMBOZ_DEBUG_INFO_0_CELLS;
    volatile const uint32_t RAMBOZ_DEBUG_INFO_0;
  } RAMBOZ_DEBUG_INFO_0_UNION;

  union
  {
    struct
    {
      volatile const uint8_t IRQ_CLR_LEVEL_32K;
      volatile const uint8_t WKUP_CLR_LEVEL_32K;
      volatile const uint8_t FORCE_FAST_LEVEL_32K;
      volatile const uint8_t FORCE_SLOW_LEVEL_32K;
    } RAMBOZ_DEBUG_INFO_1_CELLS;
    volatile const uint32_t RAMBOZ_DEBUG_INFO_1;
  } RAMBOZ_DEBUG_INFO_1_UNION;

} HW_RAMBZ_REGISTER_T;
# 412 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spmcfg.h" 1
# 413 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_spmtop.h" 1
# 414 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2
# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_srampwrctrl.h" 1
# 415 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2

# 1 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_aioadc.h" 1
# 43 "/workdir/airoha/common/drivers/chip/ab162x/inc/reg_def/reg_def_of_aioadc.h"
typedef struct {
    volatile uint32_t AIO_ADC_DATA[10];
    volatile uint32_t AIO_ADC_RESERVED0[22];

    union {
        struct {
            volatile uint8_t aio_adc_en_pluse;
            volatile uint8_t aio_adc_busy;
            volatile uint8_t AIO_ADC_EN_RESERVED0;
            volatile uint8_t AIO_ADC_EN_RESERVED1;
        } AIO_ADC_EN_CELLS;
        volatile uint32_t AIO_ADC_EN;
    } AIO_ADC_EN_UNION;

    union {
        struct {
            volatile uint8_t aio_adc_avg_sel;
            volatile uint8_t aio_adc_avg_shift_sel;
            volatile uint8_t aio_adc_rst_dly;
            volatile uint8_t aio_adc_sw_ch_dly;
        } AIO_ADC_CON0_CELLS;
        volatile uint32_t AIO_ADC_CON0;
    } AIO_ADC_CON0_UNION;

    volatile uint32_t AIO_ADC_CON1;
    volatile uint32_t AIO_ADC_CON2;
    volatile uint32_t AIO_ADC_CON3;

    union {
        struct {
            volatile uint8_t aio_clk_dig_en;
            volatile uint8_t aio_clk_ana_en;
            volatile uint8_t AIO_ADC_CON4_RESERVED0;
            volatile uint8_t AIO_ADC_CON4_RESERVED1;
        } AIO_ADC_CON4_CELLS;
        volatile uint32_t AIO_ADC_CON4;
    } AIO_ADC_CON4_UNION;

    volatile uint32_t AIO_ADC_CON5;

    union {
        struct {
            volatile uint8_t aio_debug_en;
            volatile uint8_t aio_debug_sel;
            volatile uint8_t AIO_ADC_DEBUG_RESERVED0;
            volatile uint8_t AIO_ADC_DEBUG_RESERVED1;
        } AIO_ADC_DEBUG_CELLS;
        volatile uint32_t AIO_ADC_DEBUG;
    } AIO_ADC_DEBUG_UNION;

    union {
        struct {
            volatile uint8_t aio_adc_force_on;
            volatile uint8_t aio_adc_clk_inv_en;
            volatile uint8_t AIO_ADC_CON6_RESERVED0;
            volatile uint8_t AIO_ADC_CON6_RESERVED1;
        } AIO_ADC_CON6_CELLS;
        volatile uint32_t AIO_ADC_CON6;
    } AIO_ADC_CON6_UNION;

    union {
        struct {
            volatile uint8_t da_sel_mode_aio_man;
            volatile uint8_t da_rstn_aio_man;
            volatile uint8_t da_en_aio_man;
            volatile uint8_t AIO_ADC_MAN0_RESERVED0;
        } AIO_ADC_MAN0_CELLS;
        volatile uint32_t AIO_ADC_MAN0;
    } AIO_ADC_MAN0_UNION;

    volatile uint32_t AIO_ADC_MAN1;

    union {
        struct {
            volatile uint8_t da_sel_mode_aio_man_sel;
            volatile uint8_t da_rstn_aio_man_sel;
            volatile uint8_t da_en_aio_man_sel;
            volatile uint8_t da_sel_ch_aio_man_sel;
        } AIO_ADC_MAN_SEL_CELLS;
        volatile uint32_t AIO_ADC_MAN_SEL;
    } AIO_ADC_MAN_SEL_UNION;
} AIOADC_REGISTER_T;
# 417 "/workdir/airoha/common/drivers/chip/ab162x/inc/air_chip.h" 2



typedef struct {
    volatile uint32_t MISC1;
    volatile uint32_t STCALIB;
    volatile uint32_t AHB_SLAVE_WAY_EN;
    volatile uint32_t AHB_DEC_ERR_EN;
    volatile uint32_t AHB_SIDEBAND;
    volatile uint32_t AHB_BUFFERALBE;
    volatile uint32_t AHB_FIFO_TH;
    volatile uint32_t FORCE_IDLE_OFF;
    uint32_t RESERVED0[1];
    volatile uint32_t CG_FREERUN_EN;
    volatile uint32_t CG_GATE_EN;
    uint32_t RESERVED1[1];
    volatile uint32_t TCM_BUS_CTRL;
    volatile uint32_t INT_ACTIVE_HL0;
    volatile uint32_t INT_ACTIVE_HL1;
    uint32_t RESERVED2[1];
    volatile uint32_t DCM_CTRL_REG;
} CMSYS_CFG_REGISTER_T;





typedef struct {
    volatile uint32_t CG_EN;
    volatile uint32_t DCM_EN;
} CMSYS_CFG_EXT_REGISTER_T;
# 39 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h" 2
# 200 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_SLEEP_MODE_NONE = 0,
    HAL_SLEEP_MODE_IDLE,
    HAL_SLEEP_MODE_SLEEP,
    HAL_SLEEP_MODE_NUMBER
}
hal_sleep_mode_t;

typedef enum {
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_GPT = 0,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_EINT = 1,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_IRQGEN = 2,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_I3C0 = 3,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_USB_32K_RES = 4,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_KEY_SCAN = 5,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RAMBOZ = 6,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_QDEC = 7,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_RTC_TIMER = 8,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_LED_CON = 9,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_PMU = 10,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_TIMER = 11,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_BT_IRQ = 12,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_SPM_SW_WAKEUP = 31,
    HAL_SLEEP_MANAGER_WAKEUP_SOURCE_ALL = 32,
} hal_sleep_manager_wakeup_source_t;
# 253 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_UART_0 = 0,
    HAL_UART_1 = 1,
    HAL_UART_2 = 2,
    HAL_UART_MAX
} hal_uart_port_t;
# 388 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_I2C_MASTER_0 = 1,
    HAL_I2C_MASTER_MAX
} hal_i2c_port_t;
# 461 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_GPIO_0 = 0,
    HAL_GPIO_1 = 1,
    HAL_GPIO_2 = 2,
    HAL_GPIO_3 = 3,
    HAL_GPIO_4 = 4,
    HAL_GPIO_5 = 5,
    HAL_GPIO_6 = 6,
    HAL_GPIO_7 = 7,
    HAL_GPIO_8 = 8,
    HAL_GPIO_9 = 9,
    HAL_GPIO_10 = 10,
    HAL_GPIO_11 = 11,
    HAL_GPIO_12 = 12,
    HAL_GPIO_13 = 13,
    HAL_GPIO_14 = 14,
    HAL_GPIO_15 = 15,
    HAL_GPIO_16 = 16,
    HAL_GPIO_17 = 17,
    HAL_GPIO_18 = 18,
    HAL_GPIO_19 = 19,
    HAL_GPIO_20 = 20,
    HAL_GPIO_21 = 21,
    HAL_GPIO_22 = 22,
    HAL_GPIO_23 = 23,
    HAL_GPIO_24 = 24,
    HAL_GPIO_25 = 25,
    HAL_GPIO_26 = 26,
    HAL_GPIO_27 = 27,
    HAL_GPIO_28 = 28,
    HAL_GPIO_29 = 29,
    HAL_GPIO_30 = 30,
    HAL_GPIO_31 = 31,
    HAL_GPIO_32 = 32,
    HAL_GPIO_33 = 33,
    HAL_GPIO_34 = 34,
    HAL_GPIO_35 = 35,
    HAL_GPIO_36 = 36,
    HAL_GPIO_37 = 37,
    HAL_GPIO_38 = 38,
    HAL_GPIO_39 = 39,
    HAL_GPIO_40 = 40,
    HAL_GPIO_41 = 41,
    HAL_GPIO_42 = 42,
    HAL_GPIO_43 = 43,
    HAL_GPIO_44 = 44,
    HAL_GPIO_45 = 45,
    HAL_GPIO_46 = 46,
    HAL_GPIO_47 = 47,
    HAL_GPIO_MAX
} hal_gpio_pin_t;
# 573 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_GPIO_DRIVING_CURRENT_4MA = 0,
    HAL_GPIO_DRIVING_CURRENT_8MA = 1,
    HAL_GPIO_DRIVING_CURRENT_12MA = 2,
    HAL_GPIO_DRIVING_CURRENT_16MA = 3,
    HAL_GPIO_DRIVING_CURRENT_MAX = 4,
} hal_gpio_driving_current_t;
# 601 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_GPIO_CAPACITANCE_0,
    HAL_GPIO_CAPACITANCE_1,
    HAL_GPIO_CAPACITANCE_2,
    HAL_GPIO_CAPACITANCE_3,
    HAL_GPIO_CAPACITANCE_MAX,
} hal_gpio_capacitance_t;
# 636 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_SARADC_CHANNEL_0 = 0,
    HAL_SARADC_CHANNEL_1 = 1,
    HAL_SARADC_CHANNEL_2 = 2,
    HAL_SARADC_CHANNEL_3 = 3,
    HAL_SARADC_CHANNEL_4 = 4,
    HAL_SARADC_CHANNEL_5 = 5,
    HAL_SARADC_CHANNEL_6 = 6,
    HAL_SARADC_CHANNEL_7 = 7,
    HAL_SARADC_CHANNEL_8 = 8,
    HAL_SARADC_CHANNEL_9 = 9,
    HAL_SARADC_CHANNEL_10 = 10,
    HAL_SARADC_CHANNEL_11 = 11,
    HAL_SARADC_CHANNEL_12 = 12,
    HAL_SARADC_CHANNEL_13 = 13,
    HAL_SARADC_CHANNEL_14 = 14,
    HAL_SARADC_CHANNEL_15 = 15,
    HAL_SARADC_CHANNEL_GPIO_MAX = 16,
    HAL_SARADC_CHANNEL_16 = 16,
    HAL_SARADC_CHANNEL_17 = 17,
    HAL_SARADC_CHANNEL_18 = 18,
    HAL_SARADC_CHANNEL_19 = 19,
    HAL_SARADC_CHANNEL_20 = 20,
    HAL_SARADC_CHANNEL_21 = 21,
    HAL_SARADC_CHANNEL_22 = 22,
    HAL_SARADC_CHANNEL_23 = 23,
    HAL_SARADC_CHANNEL_24 = 24,
    HAL_SARADC_CHANNEL_25 = 25,
    HAL_SARADC_CHANNEL_26 = 26,
    HAL_SARADC_CHANNEL_27 = 27,
    HAL_SARADC_CHANNEL_28 = 28,
    HAL_SARADC_CHANNEL_29 = 29,
    HAL_SARADC_CHANNEL_30 = 30,
    HAL_SARADC_CHANNEL_31 = 31,
    HAL_SARADC_CHANNEL_MAX = 32
} hal_saradc_channel_t;
# 883 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_SPI_MASTER_0 = 0,
    HAL_SPI_MASTER_1 = 1,
    HAL_SPI_MASTER_MAX
} hal_spi_master_port_t;


typedef enum {
    HAL_SPI_MASTER_SLAVE_0 = 0,
    HAL_SPI_MASTER_SLAVE_1 = 1,
    HAL_SPI_MASTER_SLAVE_2 = 2,
    HAL_SPI_MASTER_SLAVE_3 = 3,
    HAL_SPI_MASTER_SLAVE_MAX
} hal_spi_master_slave_port_t;


typedef enum {
    HAL_SPI_MASTER_LSB_FIRST = 0,
    HAL_SPI_MASTER_MSB_FIRST = 1
} hal_spi_master_bit_order_t;


typedef enum {
    HAL_SPI_MASTER_CLOCK_POLARITY0 = 0,
    HAL_SPI_MASTER_CLOCK_POLARITY1 = 1
} hal_spi_master_clock_polarity_t;


typedef enum {
    HAL_SPI_MASTER_CLOCK_PHASE0 = 0,
    HAL_SPI_MASTER_CLOCK_PHASE1 = 1
} hal_spi_master_clock_phase_t;


typedef enum {
    HAL_SPI_MASTER_SINGLE_MODE = 0,
    HAL_SPI_MASTER_3_WIRE_MODE = 1,
    HAL_SPI_MASTER_DUAL_MODE = 2,
    HAL_SPI_MASTER_QUAD_MODE = 3,
} hal_spi_master_mode_t;
# 962 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_RTC_TIMER_0 = 0,
    HAL_RTC_TIMER_1 = 1,
    HAL_RTC_TIMER_2 = 2,
    HAL_RTC_TIMER_MAX = 3
} hal_rtc_timer_port_t;



typedef enum {
    HAL_RTC_TIME_NOTIFICATION_NONE = 0,
    HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND = 1,
    HAL_RTC_TIME_NOTIFICATION_EVERY_MINUTE = 2,
    HAL_RTC_TIME_NOTIFICATION_EVERY_HOUR = 3,
    HAL_RTC_TIME_NOTIFICATION_EVERY_DAY = 4,
    HAL_RTC_TIME_NOTIFICATION_EVERY_MONTH = 5,
    HAL_RTC_TIME_NOTIFICATION_EVERY_YEAR = 6,
    HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_2 = 7,
    HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_4 = 8,
    HAL_RTC_TIME_NOTIFICATION_EVERY_SECOND_1_8 = 9,
    HAL_RTC_TIME_NOTIFICATION_MAX,
} hal_rtc_time_notification_period_t;
# 995 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef struct {
    uint8_t rtc_sec;
    uint8_t rtc_min;
    uint8_t rtc_hour;
    uint8_t rtc_day;
    uint8_t rtc_mon;
    uint8_t rtc_week;
    uint16_t rtc_year;
    uint16_t rtc_milli_sec;
} hal_rtc_time_t;
# 1031 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_EINT_NUMBER_0 = 0,
    HAL_EINT_NUMBER_1 = 1,
    HAL_EINT_NUMBER_2 = 2,
    HAL_EINT_NUMBER_3 = 3,
    HAL_EINT_NUMBER_4 = 4,
    HAL_EINT_NUMBER_5 = 5,
    HAL_EINT_NUMBER_6 = 6,
    HAL_EINT_NUMBER_7 = 7,
    HAL_EINT_NUMBER_8 = 8,
    HAL_EINT_NUMBER_9 = 9,
    HAL_EINT_NUMBER_10 = 10,
    HAL_EINT_NUMBER_11 = 11,
    HAL_EINT_NUMBER_12 = 12,
    HAL_EINT_NUMBER_13 = 13,
    HAL_EINT_NUMBER_14 = 14,
    HAL_EINT_NUMBER_15 = 15,
    HAL_EINT_NUMBER_16 = 16,
    HAL_EINT_NUMBER_17 = 17,
    HAL_EINT_NUMBER_18 = 18,
    HAL_EINT_NUMBER_19 = 19,
    HAL_EINT_NUMBER_20 = 20,
    HAL_EINT_NUMBER_21 = 21,
    HAL_EINT_NUMBER_22 = 22,
    HAL_EINT_NUMBER_23 = 23,
    HAL_EINT_NUMBER_24 = 24,
    HAL_EINT_NUMBER_25 = 25,
    HAL_EINT_NUMBER_26 = 26,
    HAL_EINT_NUMBER_27 = 27,
    HAL_EINT_NUMBER_28 = 28,
    HAL_EINT_NUMBER_29 = 29,
    HAL_EINT_NUMBER_30 = 30,
    HAL_EINT_NUMBER_31 = 31,
    HAL_EINT_NUMBER_32 = 32,
    HAL_EINT_NUMBER_33 = 33,
    HAL_EINT_NUMBER_34 = 34,
    HAL_EINT_NUMBER_35 = 35,
    HAL_EINT_NUMBER_36 = 36,
    HAL_EINT_NUMBER_37 = 37,
    HAL_EINT_NUMBER_38 = 38,
    HAL_EINT_NUMBER_39 = 39,
    HAL_EINT_NUMBER_40 = 40,
    HAL_EINT_NUMBER_41 = 41,
    HAL_EINT_NUMBER_42 = 42,
    HAL_EINT_NUMBER_43 = 43,
    HAL_EINT_NUMBER_44 = 44,
    HAL_EINT_NUMBER_45 = 45,
    HAL_EINT_NUMBER_46 = 46,
    HAL_EINT_NUMBER_47 = 47,
    HAL_EINT_UART_0_RX = 48,
    HAL_EINT_UART_1_RX = 49,
    HAL_EINT_UART_2_RX = 50,
    HAL_EINT_USB0 = 51,
    HAL_EINT_USB1 = 52,
    HAL_EINT_USB2 = 53,
    HAL_EINT_LPCOMP = 54,
    HAL_EINT_RESERVED = 55,
    HAL_EINT_NUMBER_MAX
} hal_eint_number_t;
# 1113 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_GPT_0 = 0,
    HAL_GPT_1 = 1,
    HAL_GPT_2 = 2,
    HAL_GPT_3 = 3,
    HAL_GPT_4 = 4,
    HAL_GPT_5 = 5,
    HAL_GPT_6 = 6,
    HAL_GPT_MAX_PORT = 7,
    HAL_GPT_MAX = 7
} hal_gpt_port_t;


typedef enum {
    HAL_GPT_CLOCK_SOURCE_32K = 0,
    HAL_GPT_CLOCK_SOURCE_1M = 1
} hal_gpt_clock_source_t;
# 1867 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {





    HAL_CLOCK_CG_AUXADC = 17,






    HAL_CLOCK_CG_PWM_DMA_0 = (32 + 0),
    HAL_CLOCK_CG_PWM_DMA_1 = (32 + 1),
    HAL_CLOCK_CG_PWM_2 = (32 + 2),
    HAL_CLOCK_CG_PWM_3 = (32 + 3),
    HAL_CLOCK_CG_PWM_4 = (32 + 4),
    HAL_CLOCK_CG_ARGB_BCLK = (32 + 5),
    HAL_CLOCK_CG_UART1 = (32 + 7),
    HAL_CLOCK_CG_UART2 = (32 + 8),
    HAL_CLOCK_CG_UART_DMA0 = (32 + 9),
    HAL_CLOCK_CG_UART_DMA1 = (32 + 10),
    HAL_CLOCK_CG_UART_DMA2 = (32 + 11),
    HAL_CLOCK_CG_I3C0 = (32 + 12),
    HAL_CLOCK_CG_I3C_DMA0 = (32 + 13),
    HAL_CLOCK_CG_GLB_CON_DEBUG_DIS = (32 + 15),

    HAL_CLOCK_CG_SPM_PCLK = (32 + 16),
    HAL_CLOCK_CG_SPM_BCLK_CM33 = (32 + 17),
    HAL_CLOCK_CG_SPM_DIV = (32 + 19),
    HAL_CLOCK_CG_SPM_SYS = (32 + 21),
    HAL_CLOCK_CG_OSTIMER = (32 + 23),
    HAL_CLOCK_CG_GPTIMER = (32 + 24),
    HAL_CLOCK_CG_GPTIMER_SEC = (32 + 25),
    HAL_CLOCK_CG_SECURITY_AO = (32 + 26),
    HAL_CLOCK_CG_KEY_SCAN_BCLK = (32 + 27),
    HAL_CLOCK_CG_KEY_SCAN_F2M = (32 + 28),
    HAL_CLOCK_CG_UART0 = (32 + 29),
    HAL_CLOCK_CG_PMU_1M = (32 + 30),






    HAL_CLOCK_CG_FAST_DMA_1 = (64 + 0),
    HAL_CLOCK_CG_SPIMST0_BUS = (64 + 1),
    HAL_CLOCK_CG_SPIMST1_BUS = (64 + 2),
    HAL_CLOCK_CG_BUS_ERR_AO = (64 + 14),
    HAL_CLOCK_CG_SEC_MON_AO = (64 + 15),






    HAL_CLOCK_CG_SPIMST0 = (96 + 0),
    HAL_CLOCK_CG_SPIMST1 = (96 + 1),
    HAL_CLOCK_CG_SPIMST2 = (96 + 2),
    HAL_CLOCK_CG_I3C = (96 + 4),
    HAL_CLOCK_CG_BT_HOP = (96 + 5),
    HAL_CLOCK_CG_BT_MAC_CONN = (96 + 6),
    HAL_CLOCK_CG_IRTX = (96 + 10),
    HAL_CLOCK_CG_AUD_TEST = (96 + 12),
    HAL_CLOCK_CG_SEC_MON_TOP = (96 + 13),
    HAL_CLOCK_CG_BUS_ERR_TOP = (96 + 14),
    HAL_CLOCK_CG_CKSYS_DEBUG_DIS = (96 + 15),

    HAL_CLOCK_CG_SFC = (96 + 17),
    HAL_CLOCK_CG_ESC = (96 + 18),
    HAL_CLOCK_CG_SPISLV = (96 + 19),
    HAL_CLOCK_CG_USB = (96 + 20),
    HAL_CLOCK_CG_AUD_INTBUS = (96 + 21),
    HAL_CLOCK_CG_IBEX = (96 + 22),
    HAL_CLOCK_CG_SEJ = (96 + 23),
    HAL_CLOCK_CG_EFUSE = (96 + 25),
    HAL_CLOCK_CG_BT_MAC = (96 + 26),






    HAL_CLOCK_CG_CMSYS_BUS = (128 + 16),
    HAL_CLOCK_CG_MEM_BUS = (128 + 17),
    HAL_CLOCK_CG_CONN_BUS = (128 + 18),
    HAL_CLOCK_CG_AUD_ENGINE = (128 + 24),
    HAL_CLOCK_CG_OSC_LS_D2 = (128 + 29),
    HAL_CLOCK_CG_OSC_HS_D2 = (128 + 30),
    HAL_CLOCK_CG_OSC_HS_D4 = (128 + 31),






    HAL_CLOCK_CG_AUXADC_SRAM = (160 + 0),
    HAL_CLOCK_CG_FAST_DMA_0 = (160 + 1),
    HAL_CLOCK_CG_SPIMST2_BUS = (160 + 4),
    HAL_CLOCK_CG_I3C1 = (160 + 5),
    HAL_CLOCK_CG_I3C_DMA1 = (160 + 6),
    HAL_CLOCK_CG_TRNG = (160 + 9),
    HAL_CLOCK_CG_SPISLV_BUS = (160 + 10),
    HAL_CLOCK_CG_IRRX = (160 + 11),
    HAL_CLOCK_CG_IRRX_BUS = (160 + 12),
    HAL_CLOCK_CG_AIO = (160 + 13),
    HAL_CLOCK_CG_BUS_ERR = (160 + 14),
    HAL_CLOCK_CG_SEC_MON = (160 + 15),

    HAL_CLOCK_CG_AESOTF = (160 + 18),
    HAL_CLOCK_CG_AESOTF_ESC = (160 + 19),
    HAL_CLOCK_CG_CRYPTO = (160 + 20),
    HAL_CLOCK_CG_USB_BUS = (160 + 23),
    HAL_CLOCK_CG_USB_DMA = (160 + 24),
# 1994 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
    HAL_CLOCK_CG_CMSYS_ROM = (192 + 16),


    HAL_CLOCK_CG_PSEUDO_BEGIN,
    HAL_CLOCK_CG_PSUEDO_OSC_26M = HAL_CLOCK_CG_PSEUDO_BEGIN,
    HAL_CLOCK_CG_PSEUDO_DCXO_PWR_CTRL,
    HAL_CLOCK_CG_PSEUDO_DCXO_DIG_MACRO,
    HAL_CLOCK_CG_PSEUDO_RGU_32K,
    HAL_CLOCK_CG_PSEUDO_SLOW_BUS,
    HAL_CLOCK_CG_PSEUDO_END = HAL_CLOCK_CG_PSEUDO_SLOW_BUS,

    HAL_CLOCK_CG_DUMMY_END,


    HAL_CLOCK_CG_PWM_MULTI_CTRL = 0x8000
} hal_clock_cg_id;






typedef enum {
    AD_32M_DBB_1P2 = 1,
    xo_ck = 3,
    PAD_SOC_CK = 4,
    PAD_CK = 5,
    AD_64M_DBB_CK = 7,
    AD_32M_DBB_1P2_ = 8,
    AD_CLKO_UPLL_TEST_DIG = 9,
    AD_CLKO_UPLL_FB = 10,
    AD_CLKO_UPLL_REF = 11,
    PAD_CK_ = 12,
    AD_HFOSC_HS = 15,
    AD_HFOSC_LS = 16,
    AD_HFOSC_D3_CLK = 17,
    AD_HFOSC_SSC_SYNCK = 18,
    rtc_ck = 36,
    hf_fsys_ck = 37,
    hf_fsfc_ck = 38,
    f_fesc_ck = 39,
    f_fibex_ck = 40,
    f_fspimst0_ck = 41,
    f_fspimst1_ck = 42,
    f_fspimst2_ck = 43,
    f_fspislv_ck = 44,
    f_fusb_ck = 45,
    hf_fi3c_ck = 46,
    f_fbt_hop_ck = 47,
    f_faud_intbus_ck = 48,
    hf_firtx_ck = 52,
    f_fslow_bus_ck = 55,
    f_faud_engine_ck = 56,
    f_fosc_26m_ck = 58,
    f_fesc_ck_tmp = 59,
    f_fesc_cg_ck = 60,
    f_chop_ck = 62,
    REF_CLK_ = 63
} hal_src_clock;






typedef enum {
    CLK_SYS_SEL = 0,
    CLK_IBEX_SEL = 1,
    CLK_SFC_SEL = 2,
    CLK_ESC_SEL = 3,
    CLK_SPIMST0_SEL = 4,
    CLK_SPIMST1_SEL = 5,
    CLK_SPIMST2_SEL = 6,
    CLK_SPISLV_SEL = 7,
    CLK_I3C_SEL = 8,
    CLK_USB_SEL = 9,
    CLK_AUD_ENGINE_SEL = 10,
    CLK_AUD_BUS_SEL = 11,
    CLK_BT_HOP_SEL = 12,
    CLK_BT_MAC_SEL = 13,
    CLK_UART0_SEL = 14,
    CLK_UART1_SEL = 15,
    CLK_UART2_SEL = 16,
    CLK_GPT_BCLK_SEL = 17,
    CLK_OSGPT_BCLK_SEL = 18,
    CLK_SEC_GPT_BCLK_SEL = 19,
    CLK_DCXO_PWR_CTRL_SEL = 20,
    CLK_DCXO_DIG_MACRO_SEL = 21,
    CLK_IRTX_SEL = 22,
    CLK_IRRX_BCLK_SEL = 23,
    CLK_OSC_26M_SEL = 24,
    CLK_RGU_32K_SEL = 25,



    CLK_SLOW_BUS_SEL = 26,


    CLK_MUX_SEL_PSEUDO_BEGIN,
    CLK_PWM0_SEL = CLK_MUX_SEL_PSEUDO_BEGIN,
    CLK_PWM1_SEL,
    CLK_PWM2_SEL,
    CLK_PWM3_SEL,
    CLK_PWM4_SEL,
    CLK_MUX_SEL_PSEUDO_END = CLK_PWM4_SEL,

    TOTAL_MUX_CNT
} clock_mux_sel_id;
# 2110 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_platform.h"
typedef enum {
    HAL_DVFS_OPP_MID,
    HAL_DVFS_OPP_HIGH,
    HAL_DVFS_OPP_NUM,

    HAL_DVFS_OPP_NV = HAL_DVFS_OPP_MID,
    HAL_DVFS_OPP_HV = HAL_DVFS_OPP_HIGH,




    HAL_DVS_VCORE_HIGH = HAL_DVFS_OPP_NUM,

    HAL_DVFS_OPP_TTL
} dvfs_frequency_t;
# 39 "/workdir/airoha/risc-v/drivers/chip/ab162x/inc/hal_spi_slave.h" 2
# 36 "/workdir/airoha/risc-v/drivers/chip/ab162x/src/hal_spi_slave_internal.c" 2
