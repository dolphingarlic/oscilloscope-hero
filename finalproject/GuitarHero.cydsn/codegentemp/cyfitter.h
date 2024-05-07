#ifndef INCLUDED_CYFITTER_H
#define INCLUDED_CYFITTER_H
#include "cydevice.h"
#include "cydevice_trm.h"

/* LCD_LCDPort */
#define LCD_LCDPort__0__INTTYPE CYREG_PICU2_INTTYPE0
#define LCD_LCDPort__0__MASK 0x01u
#define LCD_LCDPort__0__PC CYREG_PRT2_PC0
#define LCD_LCDPort__0__PORT 2u
#define LCD_LCDPort__0__SHIFT 0u
#define LCD_LCDPort__1__INTTYPE CYREG_PICU2_INTTYPE1
#define LCD_LCDPort__1__MASK 0x02u
#define LCD_LCDPort__1__PC CYREG_PRT2_PC1
#define LCD_LCDPort__1__PORT 2u
#define LCD_LCDPort__1__SHIFT 1u
#define LCD_LCDPort__2__INTTYPE CYREG_PICU2_INTTYPE2
#define LCD_LCDPort__2__MASK 0x04u
#define LCD_LCDPort__2__PC CYREG_PRT2_PC2
#define LCD_LCDPort__2__PORT 2u
#define LCD_LCDPort__2__SHIFT 2u
#define LCD_LCDPort__3__INTTYPE CYREG_PICU2_INTTYPE3
#define LCD_LCDPort__3__MASK 0x08u
#define LCD_LCDPort__3__PC CYREG_PRT2_PC3
#define LCD_LCDPort__3__PORT 2u
#define LCD_LCDPort__3__SHIFT 3u
#define LCD_LCDPort__4__INTTYPE CYREG_PICU2_INTTYPE4
#define LCD_LCDPort__4__MASK 0x10u
#define LCD_LCDPort__4__PC CYREG_PRT2_PC4
#define LCD_LCDPort__4__PORT 2u
#define LCD_LCDPort__4__SHIFT 4u
#define LCD_LCDPort__5__INTTYPE CYREG_PICU2_INTTYPE5
#define LCD_LCDPort__5__MASK 0x20u
#define LCD_LCDPort__5__PC CYREG_PRT2_PC5
#define LCD_LCDPort__5__PORT 2u
#define LCD_LCDPort__5__SHIFT 5u
#define LCD_LCDPort__6__INTTYPE CYREG_PICU2_INTTYPE6
#define LCD_LCDPort__6__MASK 0x40u
#define LCD_LCDPort__6__PC CYREG_PRT2_PC6
#define LCD_LCDPort__6__PORT 2u
#define LCD_LCDPort__6__SHIFT 6u
#define LCD_LCDPort__AG CYREG_PRT2_AG
#define LCD_LCDPort__AMUX CYREG_PRT2_AMUX
#define LCD_LCDPort__BIE CYREG_PRT2_BIE
#define LCD_LCDPort__BIT_MASK CYREG_PRT2_BIT_MASK
#define LCD_LCDPort__BYP CYREG_PRT2_BYP
#define LCD_LCDPort__CTL CYREG_PRT2_CTL
#define LCD_LCDPort__DM0 CYREG_PRT2_DM0
#define LCD_LCDPort__DM1 CYREG_PRT2_DM1
#define LCD_LCDPort__DM2 CYREG_PRT2_DM2
#define LCD_LCDPort__DR CYREG_PRT2_DR
#define LCD_LCDPort__INP_DIS CYREG_PRT2_INP_DIS
#define LCD_LCDPort__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU2_BASE
#define LCD_LCDPort__LCD_COM_SEG CYREG_PRT2_LCD_COM_SEG
#define LCD_LCDPort__LCD_EN CYREG_PRT2_LCD_EN
#define LCD_LCDPort__MASK 0x7Fu
#define LCD_LCDPort__PORT 2u
#define LCD_LCDPort__PRT CYREG_PRT2_PRT
#define LCD_LCDPort__PRTDSI__CAPS_SEL CYREG_PRT2_CAPS_SEL
#define LCD_LCDPort__PRTDSI__DBL_SYNC_IN CYREG_PRT2_DBL_SYNC_IN
#define LCD_LCDPort__PRTDSI__OE_SEL0 CYREG_PRT2_OE_SEL0
#define LCD_LCDPort__PRTDSI__OE_SEL1 CYREG_PRT2_OE_SEL1
#define LCD_LCDPort__PRTDSI__OUT_SEL0 CYREG_PRT2_OUT_SEL0
#define LCD_LCDPort__PRTDSI__OUT_SEL1 CYREG_PRT2_OUT_SEL1
#define LCD_LCDPort__PRTDSI__SYNC_OUT CYREG_PRT2_SYNC_OUT
#define LCD_LCDPort__PS CYREG_PRT2_PS
#define LCD_LCDPort__SHIFT 0u
#define LCD_LCDPort__SLW CYREG_PRT2_SLW

/* SD_FS_Clock_1 */
#define SD_FS_Clock_1__CFG0 CYREG_CLKDIST_DCFG0_CFG0
#define SD_FS_Clock_1__CFG1 CYREG_CLKDIST_DCFG0_CFG1
#define SD_FS_Clock_1__CFG2 CYREG_CLKDIST_DCFG0_CFG2
#define SD_FS_Clock_1__CFG2_SRC_SEL_MASK 0x07u
#define SD_FS_Clock_1__INDEX 0x00u
#define SD_FS_Clock_1__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define SD_FS_Clock_1__PM_ACT_MSK 0x01u
#define SD_FS_Clock_1__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define SD_FS_Clock_1__PM_STBY_MSK 0x01u

/* SD_FS_miso0 */
#define SD_FS_miso0__0__INTTYPE CYREG_PICU3_INTTYPE4
#define SD_FS_miso0__0__MASK 0x10u
#define SD_FS_miso0__0__PC CYREG_PRT3_PC4
#define SD_FS_miso0__0__PORT 3u
#define SD_FS_miso0__0__SHIFT 4u
#define SD_FS_miso0__AG CYREG_PRT3_AG
#define SD_FS_miso0__AMUX CYREG_PRT3_AMUX
#define SD_FS_miso0__BIE CYREG_PRT3_BIE
#define SD_FS_miso0__BIT_MASK CYREG_PRT3_BIT_MASK
#define SD_FS_miso0__BYP CYREG_PRT3_BYP
#define SD_FS_miso0__CTL CYREG_PRT3_CTL
#define SD_FS_miso0__DM0 CYREG_PRT3_DM0
#define SD_FS_miso0__DM1 CYREG_PRT3_DM1
#define SD_FS_miso0__DM2 CYREG_PRT3_DM2
#define SD_FS_miso0__DR CYREG_PRT3_DR
#define SD_FS_miso0__INP_DIS CYREG_PRT3_INP_DIS
#define SD_FS_miso0__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU3_BASE
#define SD_FS_miso0__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SD_FS_miso0__LCD_EN CYREG_PRT3_LCD_EN
#define SD_FS_miso0__MASK 0x10u
#define SD_FS_miso0__PORT 3u
#define SD_FS_miso0__PRT CYREG_PRT3_PRT
#define SD_FS_miso0__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SD_FS_miso0__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SD_FS_miso0__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SD_FS_miso0__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SD_FS_miso0__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SD_FS_miso0__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SD_FS_miso0__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SD_FS_miso0__PS CYREG_PRT3_PS
#define SD_FS_miso0__SHIFT 4u
#define SD_FS_miso0__SLW CYREG_PRT3_SLW

/* SD_FS_mosi0 */
#define SD_FS_mosi0__0__INTTYPE CYREG_PICU3_INTTYPE5
#define SD_FS_mosi0__0__MASK 0x20u
#define SD_FS_mosi0__0__PC CYREG_PRT3_PC5
#define SD_FS_mosi0__0__PORT 3u
#define SD_FS_mosi0__0__SHIFT 5u
#define SD_FS_mosi0__AG CYREG_PRT3_AG
#define SD_FS_mosi0__AMUX CYREG_PRT3_AMUX
#define SD_FS_mosi0__BIE CYREG_PRT3_BIE
#define SD_FS_mosi0__BIT_MASK CYREG_PRT3_BIT_MASK
#define SD_FS_mosi0__BYP CYREG_PRT3_BYP
#define SD_FS_mosi0__CTL CYREG_PRT3_CTL
#define SD_FS_mosi0__DM0 CYREG_PRT3_DM0
#define SD_FS_mosi0__DM1 CYREG_PRT3_DM1
#define SD_FS_mosi0__DM2 CYREG_PRT3_DM2
#define SD_FS_mosi0__DR CYREG_PRT3_DR
#define SD_FS_mosi0__INP_DIS CYREG_PRT3_INP_DIS
#define SD_FS_mosi0__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU3_BASE
#define SD_FS_mosi0__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SD_FS_mosi0__LCD_EN CYREG_PRT3_LCD_EN
#define SD_FS_mosi0__MASK 0x20u
#define SD_FS_mosi0__PORT 3u
#define SD_FS_mosi0__PRT CYREG_PRT3_PRT
#define SD_FS_mosi0__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SD_FS_mosi0__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SD_FS_mosi0__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SD_FS_mosi0__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SD_FS_mosi0__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SD_FS_mosi0__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SD_FS_mosi0__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SD_FS_mosi0__PS CYREG_PRT3_PS
#define SD_FS_mosi0__SHIFT 5u
#define SD_FS_mosi0__SLW CYREG_PRT3_SLW

/* SD_FS_sclk0 */
#define SD_FS_sclk0__0__INTTYPE CYREG_PICU3_INTTYPE3
#define SD_FS_sclk0__0__MASK 0x08u
#define SD_FS_sclk0__0__PC CYREG_PRT3_PC3
#define SD_FS_sclk0__0__PORT 3u
#define SD_FS_sclk0__0__SHIFT 3u
#define SD_FS_sclk0__AG CYREG_PRT3_AG
#define SD_FS_sclk0__AMUX CYREG_PRT3_AMUX
#define SD_FS_sclk0__BIE CYREG_PRT3_BIE
#define SD_FS_sclk0__BIT_MASK CYREG_PRT3_BIT_MASK
#define SD_FS_sclk0__BYP CYREG_PRT3_BYP
#define SD_FS_sclk0__CTL CYREG_PRT3_CTL
#define SD_FS_sclk0__DM0 CYREG_PRT3_DM0
#define SD_FS_sclk0__DM1 CYREG_PRT3_DM1
#define SD_FS_sclk0__DM2 CYREG_PRT3_DM2
#define SD_FS_sclk0__DR CYREG_PRT3_DR
#define SD_FS_sclk0__INP_DIS CYREG_PRT3_INP_DIS
#define SD_FS_sclk0__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU3_BASE
#define SD_FS_sclk0__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SD_FS_sclk0__LCD_EN CYREG_PRT3_LCD_EN
#define SD_FS_sclk0__MASK 0x08u
#define SD_FS_sclk0__PORT 3u
#define SD_FS_sclk0__PRT CYREG_PRT3_PRT
#define SD_FS_sclk0__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SD_FS_sclk0__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SD_FS_sclk0__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SD_FS_sclk0__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SD_FS_sclk0__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SD_FS_sclk0__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SD_FS_sclk0__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SD_FS_sclk0__PS CYREG_PRT3_PS
#define SD_FS_sclk0__SHIFT 3u
#define SD_FS_sclk0__SLW CYREG_PRT3_SLW

/* SD_FS_SPI0_BSPIM */
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB04_05_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB04_05_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB04_05_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB04_05_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB04_05_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB04_05_MSK
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB04_05_MSK
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB04_05_MSK
#define SD_FS_SPI0_BSPIM_BitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB04_05_MSK
#define SD_FS_SPI0_BSPIM_BitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB04_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter__CONTROL_REG CYREG_B0_UDB04_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__CONTROL_ST_REG CYREG_B0_UDB04_ST_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__COUNT_REG CYREG_B0_UDB04_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__COUNT_ST_REG CYREG_B0_UDB04_ST_CTL
#define SD_FS_SPI0_BSPIM_BitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter__PERIOD_REG CYREG_B0_UDB04_MSK
#define SD_FS_SPI0_BSPIM_BitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB04_05_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB04_05_ST
#define SD_FS_SPI0_BSPIM_BitCounter_ST__MASK_REG CYREG_B0_UDB04_MSK
#define SD_FS_SPI0_BSPIM_BitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB04_MSK_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB04_ACTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB04_ST_CTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB04_ST_CTL
#define SD_FS_SPI0_BSPIM_BitCounter_ST__STATUS_REG CYREG_B0_UDB04_ST
#define SD_FS_SPI0_BSPIM_RxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB06_07_ACTL
#define SD_FS_SPI0_BSPIM_RxStsReg__16BIT_STATUS_REG CYREG_B1_UDB06_07_ST
#define SD_FS_SPI0_BSPIM_RxStsReg__4__MASK 0x10u
#define SD_FS_SPI0_BSPIM_RxStsReg__4__POS 4
#define SD_FS_SPI0_BSPIM_RxStsReg__5__MASK 0x20u
#define SD_FS_SPI0_BSPIM_RxStsReg__5__POS 5
#define SD_FS_SPI0_BSPIM_RxStsReg__6__MASK 0x40u
#define SD_FS_SPI0_BSPIM_RxStsReg__6__POS 6
#define SD_FS_SPI0_BSPIM_RxStsReg__MASK 0x70u
#define SD_FS_SPI0_BSPIM_RxStsReg__MASK_REG CYREG_B1_UDB06_MSK
#define SD_FS_SPI0_BSPIM_RxStsReg__STATUS_AUX_CTL_REG CYREG_B1_UDB06_ACTL
#define SD_FS_SPI0_BSPIM_RxStsReg__STATUS_REG CYREG_B1_UDB06_ST
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_A0_REG CYREG_B0_UDB05_06_A0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_A1_REG CYREG_B0_UDB05_06_A1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_D0_REG CYREG_B0_UDB05_06_D0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_D1_REG CYREG_B0_UDB05_06_D1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB05_06_ACTL
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_F0_REG CYREG_B0_UDB05_06_F0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__16BIT_F1_REG CYREG_B0_UDB05_06_F1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__A0_A1_REG CYREG_B0_UDB05_A0_A1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__A0_REG CYREG_B0_UDB05_A0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__A1_REG CYREG_B0_UDB05_A1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__D0_D1_REG CYREG_B0_UDB05_D0_D1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__D0_REG CYREG_B0_UDB05_D0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__D1_REG CYREG_B0_UDB05_D1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__DP_AUX_CTL_REG CYREG_B0_UDB05_ACTL
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__F0_F1_REG CYREG_B0_UDB05_F0_F1
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__F0_REG CYREG_B0_UDB05_F0
#define SD_FS_SPI0_BSPIM_sR8_Dp_u0__F1_REG CYREG_B0_UDB05_F1
#define SD_FS_SPI0_BSPIM_TxStsReg__0__MASK 0x01u
#define SD_FS_SPI0_BSPIM_TxStsReg__0__POS 0
#define SD_FS_SPI0_BSPIM_TxStsReg__1__MASK 0x02u
#define SD_FS_SPI0_BSPIM_TxStsReg__1__POS 1
#define SD_FS_SPI0_BSPIM_TxStsReg__16BIT_STATUS_AUX_CTL_REG CYREG_B1_UDB07_08_ACTL
#define SD_FS_SPI0_BSPIM_TxStsReg__16BIT_STATUS_REG CYREG_B1_UDB07_08_ST
#define SD_FS_SPI0_BSPIM_TxStsReg__2__MASK 0x04u
#define SD_FS_SPI0_BSPIM_TxStsReg__2__POS 2
#define SD_FS_SPI0_BSPIM_TxStsReg__3__MASK 0x08u
#define SD_FS_SPI0_BSPIM_TxStsReg__3__POS 3
#define SD_FS_SPI0_BSPIM_TxStsReg__4__MASK 0x10u
#define SD_FS_SPI0_BSPIM_TxStsReg__4__POS 4
#define SD_FS_SPI0_BSPIM_TxStsReg__MASK 0x1Fu
#define SD_FS_SPI0_BSPIM_TxStsReg__MASK_REG CYREG_B1_UDB07_MSK
#define SD_FS_SPI0_BSPIM_TxStsReg__STATUS_AUX_CTL_REG CYREG_B1_UDB07_ACTL
#define SD_FS_SPI0_BSPIM_TxStsReg__STATUS_REG CYREG_B1_UDB07_ST

/* SD_FS_SPI0_CS */
#define SD_FS_SPI0_CS__0__INTTYPE CYREG_PICU3_INTTYPE6
#define SD_FS_SPI0_CS__0__MASK 0x40u
#define SD_FS_SPI0_CS__0__PC CYREG_PRT3_PC6
#define SD_FS_SPI0_CS__0__PORT 3u
#define SD_FS_SPI0_CS__0__SHIFT 6u
#define SD_FS_SPI0_CS__AG CYREG_PRT3_AG
#define SD_FS_SPI0_CS__AMUX CYREG_PRT3_AMUX
#define SD_FS_SPI0_CS__BIE CYREG_PRT3_BIE
#define SD_FS_SPI0_CS__BIT_MASK CYREG_PRT3_BIT_MASK
#define SD_FS_SPI0_CS__BYP CYREG_PRT3_BYP
#define SD_FS_SPI0_CS__CTL CYREG_PRT3_CTL
#define SD_FS_SPI0_CS__DM0 CYREG_PRT3_DM0
#define SD_FS_SPI0_CS__DM1 CYREG_PRT3_DM1
#define SD_FS_SPI0_CS__DM2 CYREG_PRT3_DM2
#define SD_FS_SPI0_CS__DR CYREG_PRT3_DR
#define SD_FS_SPI0_CS__INP_DIS CYREG_PRT3_INP_DIS
#define SD_FS_SPI0_CS__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU3_BASE
#define SD_FS_SPI0_CS__LCD_COM_SEG CYREG_PRT3_LCD_COM_SEG
#define SD_FS_SPI0_CS__LCD_EN CYREG_PRT3_LCD_EN
#define SD_FS_SPI0_CS__MASK 0x40u
#define SD_FS_SPI0_CS__PORT 3u
#define SD_FS_SPI0_CS__PRT CYREG_PRT3_PRT
#define SD_FS_SPI0_CS__PRTDSI__CAPS_SEL CYREG_PRT3_CAPS_SEL
#define SD_FS_SPI0_CS__PRTDSI__DBL_SYNC_IN CYREG_PRT3_DBL_SYNC_IN
#define SD_FS_SPI0_CS__PRTDSI__OE_SEL0 CYREG_PRT3_OE_SEL0
#define SD_FS_SPI0_CS__PRTDSI__OE_SEL1 CYREG_PRT3_OE_SEL1
#define SD_FS_SPI0_CS__PRTDSI__OUT_SEL0 CYREG_PRT3_OUT_SEL0
#define SD_FS_SPI0_CS__PRTDSI__OUT_SEL1 CYREG_PRT3_OUT_SEL1
#define SD_FS_SPI0_CS__PRTDSI__SYNC_OUT CYREG_PRT3_SYNC_OUT
#define SD_FS_SPI0_CS__PS CYREG_PRT3_PS
#define SD_FS_SPI0_CS__SHIFT 6u
#define SD_FS_SPI0_CS__SLW CYREG_PRT3_SLW

/* x_DAC_viDAC8 */
#define x_DAC_viDAC8__CR0 CYREG_DAC2_CR0
#define x_DAC_viDAC8__CR1 CYREG_DAC2_CR1
#define x_DAC_viDAC8__D CYREG_DAC2_D
#define x_DAC_viDAC8__PM_ACT_CFG CYREG_PM_ACT_CFG8
#define x_DAC_viDAC8__PM_ACT_MSK 0x04u
#define x_DAC_viDAC8__PM_STBY_CFG CYREG_PM_STBY_CFG8
#define x_DAC_viDAC8__PM_STBY_MSK 0x04u
#define x_DAC_viDAC8__STROBE CYREG_DAC2_STROBE
#define x_DAC_viDAC8__SW0 CYREG_DAC2_SW0
#define x_DAC_viDAC8__SW2 CYREG_DAC2_SW2
#define x_DAC_viDAC8__SW3 CYREG_DAC2_SW3
#define x_DAC_viDAC8__SW4 CYREG_DAC2_SW4
#define x_DAC_viDAC8__TR CYREG_DAC2_TR
#define x_DAC_viDAC8__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DAC2_M1
#define x_DAC_viDAC8__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DAC2_M2
#define x_DAC_viDAC8__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DAC2_M3
#define x_DAC_viDAC8__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DAC2_M4
#define x_DAC_viDAC8__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DAC2_M5
#define x_DAC_viDAC8__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DAC2_M6
#define x_DAC_viDAC8__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DAC2_M7
#define x_DAC_viDAC8__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DAC2_M8
#define x_DAC_viDAC8__TST CYREG_DAC2_TST

/* x_out */
#define x_out__0__INTTYPE CYREG_PICU4_INTTYPE0
#define x_out__0__MASK 0x01u
#define x_out__0__PC CYREG_PRT4_PC0
#define x_out__0__PORT 4u
#define x_out__0__SHIFT 0u
#define x_out__AG CYREG_PRT4_AG
#define x_out__AMUX CYREG_PRT4_AMUX
#define x_out__BIE CYREG_PRT4_BIE
#define x_out__BIT_MASK CYREG_PRT4_BIT_MASK
#define x_out__BYP CYREG_PRT4_BYP
#define x_out__CTL CYREG_PRT4_CTL
#define x_out__DM0 CYREG_PRT4_DM0
#define x_out__DM1 CYREG_PRT4_DM1
#define x_out__DM2 CYREG_PRT4_DM2
#define x_out__DR CYREG_PRT4_DR
#define x_out__INP_DIS CYREG_PRT4_INP_DIS
#define x_out__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU4_BASE
#define x_out__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define x_out__LCD_EN CYREG_PRT4_LCD_EN
#define x_out__MASK 0x01u
#define x_out__PORT 4u
#define x_out__PRT CYREG_PRT4_PRT
#define x_out__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define x_out__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define x_out__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define x_out__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define x_out__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define x_out__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define x_out__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define x_out__PS CYREG_PRT4_PS
#define x_out__SHIFT 0u
#define x_out__SLW CYREG_PRT4_SLW

/* y_DAC_viDAC8 */
#define y_DAC_viDAC8__CR0 CYREG_DAC3_CR0
#define y_DAC_viDAC8__CR1 CYREG_DAC3_CR1
#define y_DAC_viDAC8__D CYREG_DAC3_D
#define y_DAC_viDAC8__PM_ACT_CFG CYREG_PM_ACT_CFG8
#define y_DAC_viDAC8__PM_ACT_MSK 0x08u
#define y_DAC_viDAC8__PM_STBY_CFG CYREG_PM_STBY_CFG8
#define y_DAC_viDAC8__PM_STBY_MSK 0x08u
#define y_DAC_viDAC8__STROBE CYREG_DAC3_STROBE
#define y_DAC_viDAC8__SW0 CYREG_DAC3_SW0
#define y_DAC_viDAC8__SW2 CYREG_DAC3_SW2
#define y_DAC_viDAC8__SW3 CYREG_DAC3_SW3
#define y_DAC_viDAC8__SW4 CYREG_DAC3_SW4
#define y_DAC_viDAC8__TR CYREG_DAC3_TR
#define y_DAC_viDAC8__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DAC3_M1
#define y_DAC_viDAC8__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DAC3_M2
#define y_DAC_viDAC8__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DAC3_M3
#define y_DAC_viDAC8__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DAC3_M4
#define y_DAC_viDAC8__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DAC3_M5
#define y_DAC_viDAC8__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DAC3_M6
#define y_DAC_viDAC8__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DAC3_M7
#define y_DAC_viDAC8__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DAC3_M8
#define y_DAC_viDAC8__TST CYREG_DAC3_TST

/* y_out */
#define y_out__0__INTTYPE CYREG_PICU4_INTTYPE1
#define y_out__0__MASK 0x02u
#define y_out__0__PC CYREG_PRT4_PC1
#define y_out__0__PORT 4u
#define y_out__0__SHIFT 1u
#define y_out__AG CYREG_PRT4_AG
#define y_out__AMUX CYREG_PRT4_AMUX
#define y_out__BIE CYREG_PRT4_BIE
#define y_out__BIT_MASK CYREG_PRT4_BIT_MASK
#define y_out__BYP CYREG_PRT4_BYP
#define y_out__CTL CYREG_PRT4_CTL
#define y_out__DM0 CYREG_PRT4_DM0
#define y_out__DM1 CYREG_PRT4_DM1
#define y_out__DM2 CYREG_PRT4_DM2
#define y_out__DR CYREG_PRT4_DR
#define y_out__INP_DIS CYREG_PRT4_INP_DIS
#define y_out__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU4_BASE
#define y_out__LCD_COM_SEG CYREG_PRT4_LCD_COM_SEG
#define y_out__LCD_EN CYREG_PRT4_LCD_EN
#define y_out__MASK 0x02u
#define y_out__PORT 4u
#define y_out__PRT CYREG_PRT4_PRT
#define y_out__PRTDSI__CAPS_SEL CYREG_PRT4_CAPS_SEL
#define y_out__PRTDSI__DBL_SYNC_IN CYREG_PRT4_DBL_SYNC_IN
#define y_out__PRTDSI__OE_SEL0 CYREG_PRT4_OE_SEL0
#define y_out__PRTDSI__OE_SEL1 CYREG_PRT4_OE_SEL1
#define y_out__PRTDSI__OUT_SEL0 CYREG_PRT4_OUT_SEL0
#define y_out__PRTDSI__OUT_SEL1 CYREG_PRT4_OUT_SEL1
#define y_out__PRTDSI__SYNC_OUT CYREG_PRT4_SYNC_OUT
#define y_out__PS CYREG_PRT4_PS
#define y_out__SHIFT 1u
#define y_out__SLW CYREG_PRT4_SLW

/* BLE_Rx */
#define BLE_Rx__0__INTTYPE CYREG_PICU6_INTTYPE6
#define BLE_Rx__0__MASK 0x40u
#define BLE_Rx__0__PC CYREG_PRT6_PC6
#define BLE_Rx__0__PORT 6u
#define BLE_Rx__0__SHIFT 6u
#define BLE_Rx__AG CYREG_PRT6_AG
#define BLE_Rx__AMUX CYREG_PRT6_AMUX
#define BLE_Rx__BIE CYREG_PRT6_BIE
#define BLE_Rx__BIT_MASK CYREG_PRT6_BIT_MASK
#define BLE_Rx__BYP CYREG_PRT6_BYP
#define BLE_Rx__CTL CYREG_PRT6_CTL
#define BLE_Rx__DM0 CYREG_PRT6_DM0
#define BLE_Rx__DM1 CYREG_PRT6_DM1
#define BLE_Rx__DM2 CYREG_PRT6_DM2
#define BLE_Rx__DR CYREG_PRT6_DR
#define BLE_Rx__INP_DIS CYREG_PRT6_INP_DIS
#define BLE_Rx__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU6_BASE
#define BLE_Rx__LCD_COM_SEG CYREG_PRT6_LCD_COM_SEG
#define BLE_Rx__LCD_EN CYREG_PRT6_LCD_EN
#define BLE_Rx__MASK 0x40u
#define BLE_Rx__PORT 6u
#define BLE_Rx__PRT CYREG_PRT6_PRT
#define BLE_Rx__PRTDSI__CAPS_SEL CYREG_PRT6_CAPS_SEL
#define BLE_Rx__PRTDSI__DBL_SYNC_IN CYREG_PRT6_DBL_SYNC_IN
#define BLE_Rx__PRTDSI__OE_SEL0 CYREG_PRT6_OE_SEL0
#define BLE_Rx__PRTDSI__OE_SEL1 CYREG_PRT6_OE_SEL1
#define BLE_Rx__PRTDSI__OUT_SEL0 CYREG_PRT6_OUT_SEL0
#define BLE_Rx__PRTDSI__OUT_SEL1 CYREG_PRT6_OUT_SEL1
#define BLE_Rx__PRTDSI__SYNC_OUT CYREG_PRT6_SYNC_OUT
#define BLE_Rx__PS CYREG_PRT6_PS
#define BLE_Rx__SHIFT 6u
#define BLE_Rx__SLW CYREG_PRT6_SLW

/* BLE_Rx_isr */
#define BLE_Rx_isr__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define BLE_Rx_isr__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define BLE_Rx_isr__INTC_MASK 0x02u
#define BLE_Rx_isr__INTC_NUMBER 1u
#define BLE_Rx_isr__INTC_PRIOR_NUM 1u
#define BLE_Rx_isr__INTC_PRIOR_REG CYREG_NVIC_PRI_1
#define BLE_Rx_isr__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define BLE_Rx_isr__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* FPS_isr */
#define FPS_isr__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define FPS_isr__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define FPS_isr__INTC_MASK 0x04u
#define FPS_isr__INTC_NUMBER 2u
#define FPS_isr__INTC_PRIOR_NUM 7u
#define FPS_isr__INTC_PRIOR_REG CYREG_NVIC_PRI_2
#define FPS_isr__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define FPS_isr__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* BLE_UART_BUART */
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_AUX_CTL_REG CYREG_B0_UDB11_12_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_CONTROL_REG CYREG_B0_UDB11_12_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_CONTROL_COUNT_REG CYREG_B0_UDB11_12_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_COUNT_CONTROL_REG CYREG_B0_UDB11_12_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_COUNT_COUNT_REG CYREG_B0_UDB11_12_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_MASK_MASK_REG CYREG_B0_UDB11_12_MSK
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_MASK_PERIOD_REG CYREG_B0_UDB11_12_MSK
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_MASK_REG CYREG_B0_UDB11_12_MSK
#define BLE_UART_BUART_sRX_RxBitCounter__16BIT_PERIOD_PERIOD_REG CYREG_B0_UDB11_12_MSK
#define BLE_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG CYREG_B0_UDB11_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter__CONTROL_REG CYREG_B0_UDB11_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__CONTROL_ST_REG CYREG_B0_UDB11_ST_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__COUNT_REG CYREG_B0_UDB11_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__COUNT_ST_REG CYREG_B0_UDB11_ST_CTL
#define BLE_UART_BUART_sRX_RxBitCounter__MASK_CTL_AUX_CTL_REG CYREG_B0_UDB11_MSK_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter__PER_CTL_AUX_CTL_REG CYREG_B0_UDB11_MSK_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter__PERIOD_REG CYREG_B0_UDB11_MSK
#define BLE_UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB11_12_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__16BIT_STATUS_REG CYREG_B0_UDB11_12_ST
#define BLE_UART_BUART_sRX_RxBitCounter_ST__MASK_REG CYREG_B0_UDB11_MSK
#define BLE_UART_BUART_sRX_RxBitCounter_ST__MASK_ST_AUX_CTL_REG CYREG_B0_UDB11_MSK_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__PER_ST_AUX_CTL_REG CYREG_B0_UDB11_MSK_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__STATUS_AUX_CTL_REG CYREG_B0_UDB11_ACTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__STATUS_CNT_REG CYREG_B0_UDB11_ST_CTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__STATUS_CONTROL_REG CYREG_B0_UDB11_ST_CTL
#define BLE_UART_BUART_sRX_RxBitCounter_ST__STATUS_REG CYREG_B0_UDB11_ST
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_A0_REG CYREG_B0_UDB13_14_A0
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_A1_REG CYREG_B0_UDB13_14_A1
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_D0_REG CYREG_B0_UDB13_14_D0
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_D1_REG CYREG_B0_UDB13_14_D1
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_DP_AUX_CTL_REG CYREG_B0_UDB13_14_ACTL
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_F0_REG CYREG_B0_UDB13_14_F0
#define BLE_UART_BUART_sRX_RxShifter_u0__16BIT_F1_REG CYREG_B0_UDB13_14_F1
#define BLE_UART_BUART_sRX_RxShifter_u0__A0_A1_REG CYREG_B0_UDB13_A0_A1
#define BLE_UART_BUART_sRX_RxShifter_u0__A0_REG CYREG_B0_UDB13_A0
#define BLE_UART_BUART_sRX_RxShifter_u0__A1_REG CYREG_B0_UDB13_A1
#define BLE_UART_BUART_sRX_RxShifter_u0__D0_D1_REG CYREG_B0_UDB13_D0_D1
#define BLE_UART_BUART_sRX_RxShifter_u0__D0_REG CYREG_B0_UDB13_D0
#define BLE_UART_BUART_sRX_RxShifter_u0__D1_REG CYREG_B0_UDB13_D1
#define BLE_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG CYREG_B0_UDB13_ACTL
#define BLE_UART_BUART_sRX_RxShifter_u0__F0_F1_REG CYREG_B0_UDB13_F0_F1
#define BLE_UART_BUART_sRX_RxShifter_u0__F0_REG CYREG_B0_UDB13_F0
#define BLE_UART_BUART_sRX_RxShifter_u0__F1_REG CYREG_B0_UDB13_F1
#define BLE_UART_BUART_sRX_RxSts__16BIT_STATUS_AUX_CTL_REG CYREG_B0_UDB13_14_ACTL
#define BLE_UART_BUART_sRX_RxSts__16BIT_STATUS_REG CYREG_B0_UDB13_14_ST
#define BLE_UART_BUART_sRX_RxSts__3__MASK 0x08u
#define BLE_UART_BUART_sRX_RxSts__3__POS 3
#define BLE_UART_BUART_sRX_RxSts__4__MASK 0x10u
#define BLE_UART_BUART_sRX_RxSts__4__POS 4
#define BLE_UART_BUART_sRX_RxSts__5__MASK 0x20u
#define BLE_UART_BUART_sRX_RxSts__5__POS 5
#define BLE_UART_BUART_sRX_RxSts__MASK 0x38u
#define BLE_UART_BUART_sRX_RxSts__MASK_REG CYREG_B0_UDB13_MSK
#define BLE_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG CYREG_B0_UDB13_ACTL
#define BLE_UART_BUART_sRX_RxSts__STATUS_REG CYREG_B0_UDB13_ST

/* BLE_UART_IntClock */
#define BLE_UART_IntClock__CFG0 CYREG_CLKDIST_DCFG2_CFG0
#define BLE_UART_IntClock__CFG1 CYREG_CLKDIST_DCFG2_CFG1
#define BLE_UART_IntClock__CFG2 CYREG_CLKDIST_DCFG2_CFG2
#define BLE_UART_IntClock__CFG2_SRC_SEL_MASK 0x07u
#define BLE_UART_IntClock__INDEX 0x02u
#define BLE_UART_IntClock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define BLE_UART_IntClock__PM_ACT_MSK 0x04u
#define BLE_UART_IntClock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define BLE_UART_IntClock__PM_STBY_MSK 0x04u

/* Audio_DAC_viDAC8 */
#define Audio_DAC_viDAC8__CR0 CYREG_DAC0_CR0
#define Audio_DAC_viDAC8__CR1 CYREG_DAC0_CR1
#define Audio_DAC_viDAC8__D CYREG_DAC0_D
#define Audio_DAC_viDAC8__PM_ACT_CFG CYREG_PM_ACT_CFG8
#define Audio_DAC_viDAC8__PM_ACT_MSK 0x01u
#define Audio_DAC_viDAC8__PM_STBY_CFG CYREG_PM_STBY_CFG8
#define Audio_DAC_viDAC8__PM_STBY_MSK 0x01u
#define Audio_DAC_viDAC8__STROBE CYREG_DAC0_STROBE
#define Audio_DAC_viDAC8__SW0 CYREG_DAC0_SW0
#define Audio_DAC_viDAC8__SW2 CYREG_DAC0_SW2
#define Audio_DAC_viDAC8__SW3 CYREG_DAC0_SW3
#define Audio_DAC_viDAC8__SW4 CYREG_DAC0_SW4
#define Audio_DAC_viDAC8__TR CYREG_DAC0_TR
#define Audio_DAC_viDAC8__TRIM__M1 CYREG_FLSHID_CUST_TABLES_DAC0_M1
#define Audio_DAC_viDAC8__TRIM__M2 CYREG_FLSHID_CUST_TABLES_DAC0_M2
#define Audio_DAC_viDAC8__TRIM__M3 CYREG_FLSHID_CUST_TABLES_DAC0_M3
#define Audio_DAC_viDAC8__TRIM__M4 CYREG_FLSHID_CUST_TABLES_DAC0_M4
#define Audio_DAC_viDAC8__TRIM__M5 CYREG_FLSHID_CUST_TABLES_DAC0_M5
#define Audio_DAC_viDAC8__TRIM__M6 CYREG_FLSHID_CUST_TABLES_DAC0_M6
#define Audio_DAC_viDAC8__TRIM__M7 CYREG_FLSHID_CUST_TABLES_DAC0_M7
#define Audio_DAC_viDAC8__TRIM__M8 CYREG_FLSHID_CUST_TABLES_DAC0_M8
#define Audio_DAC_viDAC8__TST CYREG_DAC0_TST

/* Audio_isr */
#define Audio_isr__INTC_CLR_EN_REG CYREG_NVIC_CLRENA0
#define Audio_isr__INTC_CLR_PD_REG CYREG_NVIC_CLRPEND0
#define Audio_isr__INTC_MASK 0x01u
#define Audio_isr__INTC_NUMBER 0u
#define Audio_isr__INTC_PRIOR_NUM 0u
#define Audio_isr__INTC_PRIOR_REG CYREG_NVIC_PRI_0
#define Audio_isr__INTC_SET_EN_REG CYREG_NVIC_SETENA0
#define Audio_isr__INTC_SET_PD_REG CYREG_NVIC_SETPEND0

/* Audio_out */
#define Audio_out__0__INTTYPE CYREG_PICU0_INTTYPE7
#define Audio_out__0__MASK 0x80u
#define Audio_out__0__PC CYREG_PRT0_PC7
#define Audio_out__0__PORT 0u
#define Audio_out__0__SHIFT 7u
#define Audio_out__AG CYREG_PRT0_AG
#define Audio_out__AMUX CYREG_PRT0_AMUX
#define Audio_out__BIE CYREG_PRT0_BIE
#define Audio_out__BIT_MASK CYREG_PRT0_BIT_MASK
#define Audio_out__BYP CYREG_PRT0_BYP
#define Audio_out__CTL CYREG_PRT0_CTL
#define Audio_out__DM0 CYREG_PRT0_DM0
#define Audio_out__DM1 CYREG_PRT0_DM1
#define Audio_out__DM2 CYREG_PRT0_DM2
#define Audio_out__DR CYREG_PRT0_DR
#define Audio_out__INP_DIS CYREG_PRT0_INP_DIS
#define Audio_out__INTTYPE_BASE CYDEV_PICU_INTTYPE_PICU0_BASE
#define Audio_out__LCD_COM_SEG CYREG_PRT0_LCD_COM_SEG
#define Audio_out__LCD_EN CYREG_PRT0_LCD_EN
#define Audio_out__MASK 0x80u
#define Audio_out__PORT 0u
#define Audio_out__PRT CYREG_PRT0_PRT
#define Audio_out__PRTDSI__CAPS_SEL CYREG_PRT0_CAPS_SEL
#define Audio_out__PRTDSI__DBL_SYNC_IN CYREG_PRT0_DBL_SYNC_IN
#define Audio_out__PRTDSI__OE_SEL0 CYREG_PRT0_OE_SEL0
#define Audio_out__PRTDSI__OE_SEL1 CYREG_PRT0_OE_SEL1
#define Audio_out__PRTDSI__OUT_SEL0 CYREG_PRT0_OUT_SEL0
#define Audio_out__PRTDSI__OUT_SEL1 CYREG_PRT0_OUT_SEL1
#define Audio_out__PRTDSI__SYNC_OUT CYREG_PRT0_SYNC_OUT
#define Audio_out__PS CYREG_PRT0_PS
#define Audio_out__SHIFT 7u
#define Audio_out__SLW CYREG_PRT0_SLW

/* FPS_Clock */
#define FPS_Clock__CFG0 CYREG_CLKDIST_DCFG1_CFG0
#define FPS_Clock__CFG1 CYREG_CLKDIST_DCFG1_CFG1
#define FPS_Clock__CFG2 CYREG_CLKDIST_DCFG1_CFG2
#define FPS_Clock__CFG2_SRC_SEL_MASK 0x07u
#define FPS_Clock__INDEX 0x01u
#define FPS_Clock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define FPS_Clock__PM_ACT_MSK 0x02u
#define FPS_Clock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define FPS_Clock__PM_STBY_MSK 0x02u

/* Audio_Clock */
#define Audio_Clock__CFG0 CYREG_CLKDIST_DCFG3_CFG0
#define Audio_Clock__CFG1 CYREG_CLKDIST_DCFG3_CFG1
#define Audio_Clock__CFG2 CYREG_CLKDIST_DCFG3_CFG2
#define Audio_Clock__CFG2_SRC_SEL_MASK 0x07u
#define Audio_Clock__INDEX 0x03u
#define Audio_Clock__PM_ACT_CFG CYREG_PM_ACT_CFG2
#define Audio_Clock__PM_ACT_MSK 0x08u
#define Audio_Clock__PM_STBY_CFG CYREG_PM_STBY_CFG2
#define Audio_Clock__PM_STBY_MSK 0x08u

/* FPS_Counter_CounterHW */
#define FPS_Counter_CounterHW__CAP0 CYREG_TMR0_CAP0
#define FPS_Counter_CounterHW__CAP1 CYREG_TMR0_CAP1
#define FPS_Counter_CounterHW__CFG0 CYREG_TMR0_CFG0
#define FPS_Counter_CounterHW__CFG1 CYREG_TMR0_CFG1
#define FPS_Counter_CounterHW__CFG2 CYREG_TMR0_CFG2
#define FPS_Counter_CounterHW__CNT_CMP0 CYREG_TMR0_CNT_CMP0
#define FPS_Counter_CounterHW__CNT_CMP1 CYREG_TMR0_CNT_CMP1
#define FPS_Counter_CounterHW__PER0 CYREG_TMR0_PER0
#define FPS_Counter_CounterHW__PER1 CYREG_TMR0_PER1
#define FPS_Counter_CounterHW__PM_ACT_CFG CYREG_PM_ACT_CFG3
#define FPS_Counter_CounterHW__PM_ACT_MSK 0x01u
#define FPS_Counter_CounterHW__PM_STBY_CFG CYREG_PM_STBY_CFG3
#define FPS_Counter_CounterHW__PM_STBY_MSK 0x01u
#define FPS_Counter_CounterHW__RT0 CYREG_TMR0_RT0
#define FPS_Counter_CounterHW__RT1 CYREG_TMR0_RT1
#define FPS_Counter_CounterHW__SR0 CYREG_TMR0_SR0

/* Miscellaneous */
#define BCLK__BUS_CLK__HZ 24000000U
#define BCLK__BUS_CLK__KHZ 24000U
#define BCLK__BUS_CLK__MHZ 24U
#define CY_PROJECT_NAME "GuitarHero"
#define CY_VERSION "PSoC Creator  3.3 CP3"
#define CYDEV_CHIP_DIE_LEOPARD 1u
#define CYDEV_CHIP_DIE_PANTHER 19u
#define CYDEV_CHIP_DIE_PSOC4A 11u
#define CYDEV_CHIP_DIE_PSOC5LP 18u
#define CYDEV_CHIP_DIE_TMA4 2u
#define CYDEV_CHIP_DIE_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_PSOC3 1u
#define CYDEV_CHIP_FAMILY_PSOC4 2u
#define CYDEV_CHIP_FAMILY_PSOC5 3u
#define CYDEV_CHIP_FAMILY_UNKNOWN 0u
#define CYDEV_CHIP_FAMILY_USED CYDEV_CHIP_FAMILY_PSOC5
#define CYDEV_CHIP_JTAG_ID 0x2E123069u
#define CYDEV_CHIP_MEMBER_3A 1u
#define CYDEV_CHIP_MEMBER_4A 11u
#define CYDEV_CHIP_MEMBER_4C 16u
#define CYDEV_CHIP_MEMBER_4D 7u
#define CYDEV_CHIP_MEMBER_4E 4u
#define CYDEV_CHIP_MEMBER_4F 12u
#define CYDEV_CHIP_MEMBER_4G 2u
#define CYDEV_CHIP_MEMBER_4H 10u
#define CYDEV_CHIP_MEMBER_4I 15u
#define CYDEV_CHIP_MEMBER_4J 8u
#define CYDEV_CHIP_MEMBER_4K 9u
#define CYDEV_CHIP_MEMBER_4L 14u
#define CYDEV_CHIP_MEMBER_4M 13u
#define CYDEV_CHIP_MEMBER_4N 6u
#define CYDEV_CHIP_MEMBER_4O 5u
#define CYDEV_CHIP_MEMBER_4U 3u
#define CYDEV_CHIP_MEMBER_5A 18u
#define CYDEV_CHIP_MEMBER_5B 17u
#define CYDEV_CHIP_MEMBER_UNKNOWN 0u
#define CYDEV_CHIP_MEMBER_USED CYDEV_CHIP_MEMBER_5B
#define CYDEV_CHIP_DIE_EXPECT CYDEV_CHIP_MEMBER_USED
#define CYDEV_CHIP_DIE_ACTUAL CYDEV_CHIP_DIE_EXPECT
#define CYDEV_CHIP_REV_LEOPARD_ES1 0u
#define CYDEV_CHIP_REV_LEOPARD_ES2 1u
#define CYDEV_CHIP_REV_LEOPARD_ES3 3u
#define CYDEV_CHIP_REV_LEOPARD_PRODUCTION 3u
#define CYDEV_CHIP_REV_PANTHER_ES0 0u
#define CYDEV_CHIP_REV_PANTHER_ES1 1u
#define CYDEV_CHIP_REV_PANTHER_PRODUCTION 1u
#define CYDEV_CHIP_REV_PSOC4A_ES0 17u
#define CYDEV_CHIP_REV_PSOC4A_PRODUCTION 17u
#define CYDEV_CHIP_REV_PSOC5LP_ES0 0u
#define CYDEV_CHIP_REV_PSOC5LP_PRODUCTION 0u
#define CYDEV_CHIP_REV_TMA4_ES 17u
#define CYDEV_CHIP_REV_TMA4_ES2 33u
#define CYDEV_CHIP_REV_TMA4_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_3A_ES1 0u
#define CYDEV_CHIP_REVISION_3A_ES2 1u
#define CYDEV_CHIP_REVISION_3A_ES3 3u
#define CYDEV_CHIP_REVISION_3A_PRODUCTION 3u
#define CYDEV_CHIP_REVISION_4A_ES0 17u
#define CYDEV_CHIP_REVISION_4A_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4C_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4D_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4E_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256DMA 0u
#define CYDEV_CHIP_REVISION_4F_PRODUCTION_256K 0u
#define CYDEV_CHIP_REVISION_4G_ES 17u
#define CYDEV_CHIP_REVISION_4G_ES2 33u
#define CYDEV_CHIP_REVISION_4G_PRODUCTION 17u
#define CYDEV_CHIP_REVISION_4H_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4I_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4J_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4K_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4L_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4M_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4N_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4O_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_4U_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_5A_ES0 0u
#define CYDEV_CHIP_REVISION_5A_ES1 1u
#define CYDEV_CHIP_REVISION_5A_PRODUCTION 1u
#define CYDEV_CHIP_REVISION_5B_ES0 0u
#define CYDEV_CHIP_REVISION_5B_PRODUCTION 0u
#define CYDEV_CHIP_REVISION_USED CYDEV_CHIP_REVISION_5B_PRODUCTION
#define CYDEV_CHIP_REV_EXPECT CYDEV_CHIP_REVISION_USED
#define CYDEV_CONFIG_FASTBOOT_ENABLED 1
#define CYDEV_CONFIG_UNUSED_IO_AllowButWarn 0
#define CYDEV_CONFIG_UNUSED_IO CYDEV_CONFIG_UNUSED_IO_AllowButWarn
#define CYDEV_CONFIG_UNUSED_IO_AllowWithInfo 1
#define CYDEV_CONFIG_UNUSED_IO_Disallowed 2
#define CYDEV_CONFIGURATION_COMPRESSED 1
#define CYDEV_CONFIGURATION_DMA 0
#define CYDEV_CONFIGURATION_ECC 1
#define CYDEV_CONFIGURATION_IMOENABLED CYDEV_CONFIG_FASTBOOT_ENABLED
#define CYDEV_CONFIGURATION_MODE_COMPRESSED 0
#define CYDEV_CONFIGURATION_MODE CYDEV_CONFIGURATION_MODE_COMPRESSED
#define CYDEV_CONFIGURATION_MODE_DMA 2
#define CYDEV_CONFIGURATION_MODE_UNCOMPRESSED 1
#define CYDEV_DEBUG_ENABLE_MASK 0x20u
#define CYDEV_DEBUG_ENABLE_REGISTER CYREG_MLOGIC_DEBUG
#define CYDEV_DEBUGGING_DPS_Disable 3
#define CYDEV_DEBUGGING_DPS_JTAG_4 1
#define CYDEV_DEBUGGING_DPS_JTAG_5 0
#define CYDEV_DEBUGGING_DPS_SWD 2
#define CYDEV_DEBUGGING_DPS_SWD_SWV 6
#define CYDEV_DEBUGGING_DPS CYDEV_DEBUGGING_DPS_SWD_SWV
#define CYDEV_DEBUGGING_ENABLE 1
#define CYDEV_DEBUGGING_XRES 0
#define CYDEV_DMA_CHANNELS_AVAILABLE 24u
#define CYDEV_ECC_ENABLE 0
#define CYDEV_HEAP_SIZE 0x80
#define CYDEV_INSTRUCT_CACHE_ENABLED 1
#define CYDEV_INTR_RISING 0x00000003u
#define CYDEV_IS_EXPORTING_CODE 0
#define CYDEV_IS_IMPORTING_CODE 0
#define CYDEV_PROJ_TYPE 0
#define CYDEV_PROJ_TYPE_BOOTLOADER 1
#define CYDEV_PROJ_TYPE_LAUNCHER 5
#define CYDEV_PROJ_TYPE_LOADABLE 2
#define CYDEV_PROJ_TYPE_LOADABLEANDBOOTLOADER 4
#define CYDEV_PROJ_TYPE_MULTIAPPBOOTLOADER 3
#define CYDEV_PROJ_TYPE_STANDARD 0
#define CYDEV_PROTECTION_ENABLE 0
#define CYDEV_STACK_SIZE 0x0800
#define CYDEV_USE_BUNDLED_CMSIS 1
#define CYDEV_VARIABLE_VDDA 0
#define CYDEV_VDDA 5.0
#define CYDEV_VDDA_MV 5000
#define CYDEV_VDDD 5.0
#define CYDEV_VDDD_MV 5000
#define CYDEV_VDDIO0 5.0
#define CYDEV_VDDIO0_MV 5000
#define CYDEV_VDDIO1 5.0
#define CYDEV_VDDIO1_MV 5000
#define CYDEV_VDDIO2 5.0
#define CYDEV_VDDIO2_MV 5000
#define CYDEV_VDDIO3 5.0
#define CYDEV_VDDIO3_MV 5000
#define CYDEV_VIO0 5.0
#define CYDEV_VIO0_MV 5000
#define CYDEV_VIO1 5.0
#define CYDEV_VIO1_MV 5000
#define CYDEV_VIO2 5.0
#define CYDEV_VIO2_MV 5000
#define CYDEV_VIO3 5.0
#define CYDEV_VIO3_MV 5000
#define CYIPBLOCK_ARM_CM3_VERSION 0
#define CYIPBLOCK_P3_ANAIF_VERSION 0
#define CYIPBLOCK_P3_CAN_VERSION 0
#define CYIPBLOCK_P3_CAPSENSE_VERSION 0
#define CYIPBLOCK_P3_COMP_VERSION 0
#define CYIPBLOCK_P3_DECIMATOR_VERSION 0
#define CYIPBLOCK_P3_DFB_VERSION 0
#define CYIPBLOCK_P3_DMA_VERSION 0
#define CYIPBLOCK_P3_DRQ_VERSION 0
#define CYIPBLOCK_P3_DSM_VERSION 0
#define CYIPBLOCK_P3_EMIF_VERSION 0
#define CYIPBLOCK_P3_I2C_VERSION 0
#define CYIPBLOCK_P3_LCD_VERSION 0
#define CYIPBLOCK_P3_LPF_VERSION 0
#define CYIPBLOCK_P3_OPAMP_VERSION 0
#define CYIPBLOCK_P3_PM_VERSION 0
#define CYIPBLOCK_P3_SCCT_VERSION 0
#define CYIPBLOCK_P3_TIMER_VERSION 0
#define CYIPBLOCK_P3_USB_VERSION 0
#define CYIPBLOCK_P3_VIDAC_VERSION 0
#define CYIPBLOCK_P3_VREF_VERSION 0
#define CYIPBLOCK_S8_GPIO_VERSION 0
#define CYIPBLOCK_S8_IRQ_VERSION 0
#define CYIPBLOCK_S8_SAR_VERSION 0
#define CYIPBLOCK_S8_SIO_VERSION 0
#define CYIPBLOCK_S8_UDB_VERSION 0
#define DMA_CHANNELS_USED__MASK0 0x00000000u
#define CYDEV_BOOTLOADER_ENABLE 0

#endif /* INCLUDED_CYFITTER_H */
