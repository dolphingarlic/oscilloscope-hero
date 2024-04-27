/*******************************************************************************
* File Name: BLE_UART.h
* Version 2.50
*
* Description:
*  Contains the function prototypes and constants available to the UART
*  user module.
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_UART_BLE_UART_H)
#define CY_UART_BLE_UART_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CyLib.h"


/***************************************
* Conditional Compilation Parameters
***************************************/

#define BLE_UART_RX_ENABLED                     (0u)
#define BLE_UART_TX_ENABLED                     (1u)
#define BLE_UART_HD_ENABLED                     (0u)
#define BLE_UART_RX_INTERRUPT_ENABLED           (0u)
#define BLE_UART_TX_INTERRUPT_ENABLED           (0u)
#define BLE_UART_INTERNAL_CLOCK_USED            (1u)
#define BLE_UART_RXHW_ADDRESS_ENABLED           (0u)
#define BLE_UART_OVER_SAMPLE_COUNT              (8u)
#define BLE_UART_PARITY_TYPE                    (0u)
#define BLE_UART_PARITY_TYPE_SW                 (0u)
#define BLE_UART_BREAK_DETECT                   (0u)
#define BLE_UART_BREAK_BITS_TX                  (13u)
#define BLE_UART_BREAK_BITS_RX                  (13u)
#define BLE_UART_TXCLKGEN_DP                    (1u)
#define BLE_UART_USE23POLLING                   (1u)
#define BLE_UART_FLOW_CONTROL                   (0u)
#define BLE_UART_CLK_FREQ                       (0u)
#define BLE_UART_TX_BUFFER_SIZE                 (4u)
#define BLE_UART_RX_BUFFER_SIZE                 (4u)

/* Check to see if required defines such as CY_PSOC5LP are available */
/* They are defined starting with cy_boot v3.0 */
#if !defined (CY_PSOC5LP)
    #error Component UART_v2_50 requires cy_boot v3.0 or later
#endif /* (CY_PSOC5LP) */

#if defined(BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG)
    #define BLE_UART_CONTROL_REG_REMOVED            (0u)
#else
    #define BLE_UART_CONTROL_REG_REMOVED            (1u)
#endif /* End BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */


/***************************************
*      Data Structure Definition
***************************************/

/* Sleep Mode API Support */
typedef struct BLE_UART_backupStruct_
{
    uint8 enableState;

    #if(BLE_UART_CONTROL_REG_REMOVED == 0u)
        uint8 cr;
    #endif /* End BLE_UART_CONTROL_REG_REMOVED */

} BLE_UART_BACKUP_STRUCT;


/***************************************
*       Function Prototypes
***************************************/

void BLE_UART_Start(void) ;
void BLE_UART_Stop(void) ;
uint8 BLE_UART_ReadControlRegister(void) ;
void BLE_UART_WriteControlRegister(uint8 control) ;

void BLE_UART_Init(void) ;
void BLE_UART_Enable(void) ;
void BLE_UART_SaveConfig(void) ;
void BLE_UART_RestoreConfig(void) ;
void BLE_UART_Sleep(void) ;
void BLE_UART_Wakeup(void) ;

/* Only if RX is enabled */
#if( (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) )

    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        #define BLE_UART_EnableRxInt()  CyIntEnable (BLE_UART_RX_VECT_NUM)
        #define BLE_UART_DisableRxInt() CyIntDisable(BLE_UART_RX_VECT_NUM)
        CY_ISR_PROTO(BLE_UART_RXISR);
    #endif /* BLE_UART_RX_INTERRUPT_ENABLED */

    void BLE_UART_SetRxAddressMode(uint8 addressMode)
                                                           ;
    void BLE_UART_SetRxAddress1(uint8 address) ;
    void BLE_UART_SetRxAddress2(uint8 address) ;

    void  BLE_UART_SetRxInterruptMode(uint8 intSrc) ;
    uint8 BLE_UART_ReadRxData(void) ;
    uint8 BLE_UART_ReadRxStatus(void) ;
    uint8 BLE_UART_GetChar(void) ;
    uint16 BLE_UART_GetByte(void) ;
    uint8 BLE_UART_GetRxBufferSize(void)
                                                            ;
    void BLE_UART_ClearRxBuffer(void) ;

    /* Obsolete functions, defines for backward compatible */
    #define BLE_UART_GetRxInterruptSource   BLE_UART_ReadRxStatus

#endif /* End (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) */

/* Only if TX is enabled */
#if(BLE_UART_TX_ENABLED || BLE_UART_HD_ENABLED)

    #if(BLE_UART_TX_INTERRUPT_ENABLED)
        #define BLE_UART_EnableTxInt()  CyIntEnable (BLE_UART_TX_VECT_NUM)
        #define BLE_UART_DisableTxInt() CyIntDisable(BLE_UART_TX_VECT_NUM)
        #define BLE_UART_SetPendingTxInt() CyIntSetPending(BLE_UART_TX_VECT_NUM)
        #define BLE_UART_ClearPendingTxInt() CyIntClearPending(BLE_UART_TX_VECT_NUM)
        CY_ISR_PROTO(BLE_UART_TXISR);
    #endif /* BLE_UART_TX_INTERRUPT_ENABLED */

    void BLE_UART_SetTxInterruptMode(uint8 intSrc) ;
    void BLE_UART_WriteTxData(uint8 txDataByte) ;
    uint8 BLE_UART_ReadTxStatus(void) ;
    void BLE_UART_PutChar(uint8 txDataByte) ;
    void BLE_UART_PutString(const char8 string[]) ;
    void BLE_UART_PutArray(const uint8 string[], uint8 byteCount)
                                                            ;
    void BLE_UART_PutCRLF(uint8 txDataByte) ;
    void BLE_UART_ClearTxBuffer(void) ;
    void BLE_UART_SetTxAddressMode(uint8 addressMode) ;
    void BLE_UART_SendBreak(uint8 retMode) ;
    uint8 BLE_UART_GetTxBufferSize(void)
                                                            ;
    /* Obsolete functions, defines for backward compatible */
    #define BLE_UART_PutStringConst         BLE_UART_PutString
    #define BLE_UART_PutArrayConst          BLE_UART_PutArray
    #define BLE_UART_GetTxInterruptSource   BLE_UART_ReadTxStatus

#endif /* End BLE_UART_TX_ENABLED || BLE_UART_HD_ENABLED */

#if(BLE_UART_HD_ENABLED)
    void BLE_UART_LoadRxConfig(void) ;
    void BLE_UART_LoadTxConfig(void) ;
#endif /* End BLE_UART_HD_ENABLED */


/* Communication bootloader APIs */
#if defined(CYDEV_BOOTLOADER_IO_COMP) && ((CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLE_UART) || \
                                          (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_Custom_Interface))
    /* Physical layer functions */
    void    BLE_UART_CyBtldrCommStart(void) CYSMALL ;
    void    BLE_UART_CyBtldrCommStop(void) CYSMALL ;
    void    BLE_UART_CyBtldrCommReset(void) CYSMALL ;
    cystatus BLE_UART_CyBtldrCommWrite(const uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;
    cystatus BLE_UART_CyBtldrCommRead(uint8 pData[], uint16 size, uint16 * count, uint8 timeOut) CYSMALL
             ;

    #if (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLE_UART)
        #define CyBtldrCommStart    BLE_UART_CyBtldrCommStart
        #define CyBtldrCommStop     BLE_UART_CyBtldrCommStop
        #define CyBtldrCommReset    BLE_UART_CyBtldrCommReset
        #define CyBtldrCommWrite    BLE_UART_CyBtldrCommWrite
        #define CyBtldrCommRead     BLE_UART_CyBtldrCommRead
    #endif  /* (CYDEV_BOOTLOADER_IO_COMP == CyBtldr_BLE_UART) */

    /* Byte to Byte time out for detecting end of block data from host */
    #define BLE_UART_BYTE2BYTE_TIME_OUT (25u)
    #define BLE_UART_PACKET_EOP         (0x17u) /* End of packet defined by bootloader */
    #define BLE_UART_WAIT_EOP_DELAY     (5u)    /* Additional 5ms to wait for End of packet */
    #define BLE_UART_BL_CHK_DELAY_MS    (1u)    /* Time Out quantity equal 1mS */

#endif /* CYDEV_BOOTLOADER_IO_COMP */


/***************************************
*          API Constants
***************************************/
/* Parameters for SetTxAddressMode API*/
#define BLE_UART_SET_SPACE      (0x00u)
#define BLE_UART_SET_MARK       (0x01u)

/* Status Register definitions */
#if( (BLE_UART_TX_ENABLED) || (BLE_UART_HD_ENABLED) )
    #if(BLE_UART_TX_INTERRUPT_ENABLED)
        #define BLE_UART_TX_VECT_NUM            (uint8)BLE_UART_TXInternalInterrupt__INTC_NUMBER
        #define BLE_UART_TX_PRIOR_NUM           (uint8)BLE_UART_TXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BLE_UART_TX_INTERRUPT_ENABLED */

    #define BLE_UART_TX_STS_COMPLETE_SHIFT          (0x00u)
    #define BLE_UART_TX_STS_FIFO_EMPTY_SHIFT        (0x01u)
    #define BLE_UART_TX_STS_FIFO_NOT_FULL_SHIFT     (0x03u)
    #if(BLE_UART_TX_ENABLED)
        #define BLE_UART_TX_STS_FIFO_FULL_SHIFT     (0x02u)
    #else /* (BLE_UART_HD_ENABLED) */
        #define BLE_UART_TX_STS_FIFO_FULL_SHIFT     (0x05u)  /* Needs MD=0 */
    #endif /* (BLE_UART_TX_ENABLED) */

    #define BLE_UART_TX_STS_COMPLETE            (uint8)(0x01u << BLE_UART_TX_STS_COMPLETE_SHIFT)
    #define BLE_UART_TX_STS_FIFO_EMPTY          (uint8)(0x01u << BLE_UART_TX_STS_FIFO_EMPTY_SHIFT)
    #define BLE_UART_TX_STS_FIFO_FULL           (uint8)(0x01u << BLE_UART_TX_STS_FIFO_FULL_SHIFT)
    #define BLE_UART_TX_STS_FIFO_NOT_FULL       (uint8)(0x01u << BLE_UART_TX_STS_FIFO_NOT_FULL_SHIFT)
#endif /* End (BLE_UART_TX_ENABLED) || (BLE_UART_HD_ENABLED)*/

#if( (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) )
    #if(BLE_UART_RX_INTERRUPT_ENABLED)
        #define BLE_UART_RX_VECT_NUM            (uint8)BLE_UART_RXInternalInterrupt__INTC_NUMBER
        #define BLE_UART_RX_PRIOR_NUM           (uint8)BLE_UART_RXInternalInterrupt__INTC_PRIOR_NUM
    #endif /* BLE_UART_RX_INTERRUPT_ENABLED */
    #define BLE_UART_RX_STS_MRKSPC_SHIFT            (0x00u)
    #define BLE_UART_RX_STS_BREAK_SHIFT             (0x01u)
    #define BLE_UART_RX_STS_PAR_ERROR_SHIFT         (0x02u)
    #define BLE_UART_RX_STS_STOP_ERROR_SHIFT        (0x03u)
    #define BLE_UART_RX_STS_OVERRUN_SHIFT           (0x04u)
    #define BLE_UART_RX_STS_FIFO_NOTEMPTY_SHIFT     (0x05u)
    #define BLE_UART_RX_STS_ADDR_MATCH_SHIFT        (0x06u)
    #define BLE_UART_RX_STS_SOFT_BUFF_OVER_SHIFT    (0x07u)

    #define BLE_UART_RX_STS_MRKSPC           (uint8)(0x01u << BLE_UART_RX_STS_MRKSPC_SHIFT)
    #define BLE_UART_RX_STS_BREAK            (uint8)(0x01u << BLE_UART_RX_STS_BREAK_SHIFT)
    #define BLE_UART_RX_STS_PAR_ERROR        (uint8)(0x01u << BLE_UART_RX_STS_PAR_ERROR_SHIFT)
    #define BLE_UART_RX_STS_STOP_ERROR       (uint8)(0x01u << BLE_UART_RX_STS_STOP_ERROR_SHIFT)
    #define BLE_UART_RX_STS_OVERRUN          (uint8)(0x01u << BLE_UART_RX_STS_OVERRUN_SHIFT)
    #define BLE_UART_RX_STS_FIFO_NOTEMPTY    (uint8)(0x01u << BLE_UART_RX_STS_FIFO_NOTEMPTY_SHIFT)
    #define BLE_UART_RX_STS_ADDR_MATCH       (uint8)(0x01u << BLE_UART_RX_STS_ADDR_MATCH_SHIFT)
    #define BLE_UART_RX_STS_SOFT_BUFF_OVER   (uint8)(0x01u << BLE_UART_RX_STS_SOFT_BUFF_OVER_SHIFT)
    #define BLE_UART_RX_HW_MASK                     (0x7Fu)
#endif /* End (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) */

/* Control Register definitions */
#define BLE_UART_CTRL_HD_SEND_SHIFT                 (0x00u) /* 1 enable TX part in Half Duplex mode */
#define BLE_UART_CTRL_HD_SEND_BREAK_SHIFT           (0x01u) /* 1 send BREAK signal in Half Duplez mode */
#define BLE_UART_CTRL_MARK_SHIFT                    (0x02u) /* 1 sets mark, 0 sets space */
#define BLE_UART_CTRL_PARITY_TYPE0_SHIFT            (0x03u) /* Defines the type of parity implemented */
#define BLE_UART_CTRL_PARITY_TYPE1_SHIFT            (0x04u) /* Defines the type of parity implemented */
#define BLE_UART_CTRL_RXADDR_MODE0_SHIFT            (0x05u)
#define BLE_UART_CTRL_RXADDR_MODE1_SHIFT            (0x06u)
#define BLE_UART_CTRL_RXADDR_MODE2_SHIFT            (0x07u)

#define BLE_UART_CTRL_HD_SEND               (uint8)(0x01u << BLE_UART_CTRL_HD_SEND_SHIFT)
#define BLE_UART_CTRL_HD_SEND_BREAK         (uint8)(0x01u << BLE_UART_CTRL_HD_SEND_BREAK_SHIFT)
#define BLE_UART_CTRL_MARK                  (uint8)(0x01u << BLE_UART_CTRL_MARK_SHIFT)
#define BLE_UART_CTRL_PARITY_TYPE_MASK      (uint8)(0x03u << BLE_UART_CTRL_PARITY_TYPE0_SHIFT)
#define BLE_UART_CTRL_RXADDR_MODE_MASK      (uint8)(0x07u << BLE_UART_CTRL_RXADDR_MODE0_SHIFT)

/* StatusI Register Interrupt Enable Control Bits. As defined by the Register map for the AUX Control Register */
#define BLE_UART_INT_ENABLE                         (0x10u)

/* Bit Counter (7-bit) Control Register Bit Definitions. As defined by the Register map for the AUX Control Register */
#define BLE_UART_CNTR_ENABLE                        (0x20u)

/*   Constants for SendBreak() "retMode" parameter  */
#define BLE_UART_SEND_BREAK                         (0x00u)
#define BLE_UART_WAIT_FOR_COMPLETE_REINIT           (0x01u)
#define BLE_UART_REINIT                             (0x02u)
#define BLE_UART_SEND_WAIT_REINIT                   (0x03u)

#define BLE_UART_OVER_SAMPLE_8                      (8u)
#define BLE_UART_OVER_SAMPLE_16                     (16u)

#define BLE_UART_BIT_CENTER                         (BLE_UART_OVER_SAMPLE_COUNT - 2u)

#define BLE_UART_FIFO_LENGTH                        (4u)
#define BLE_UART_NUMBER_OF_START_BIT                (1u)
#define BLE_UART_MAX_BYTE_VALUE                     (0xFFu)

/* 8X always for count7 implementation */
#define BLE_UART_TXBITCTR_BREAKBITS8X   ((BLE_UART_BREAK_BITS_TX * BLE_UART_OVER_SAMPLE_8) - 1u)
/* 8X or 16X for DP implementation */
#define BLE_UART_TXBITCTR_BREAKBITS ((BLE_UART_BREAK_BITS_TX * BLE_UART_OVER_SAMPLE_COUNT) - 1u)

#define BLE_UART_HALF_BIT_COUNT   \
                            (((BLE_UART_OVER_SAMPLE_COUNT / 2u) + (BLE_UART_USE23POLLING * 1u)) - 2u)
#if (BLE_UART_OVER_SAMPLE_COUNT == BLE_UART_OVER_SAMPLE_8)
    #define BLE_UART_HD_TXBITCTR_INIT   (((BLE_UART_BREAK_BITS_TX + \
                            BLE_UART_NUMBER_OF_START_BIT) * BLE_UART_OVER_SAMPLE_COUNT) - 1u)

    /* This parameter is increased on the 2 in 2 out of 3 mode to sample voting in the middle */
    #define BLE_UART_RXBITCTR_INIT  ((((BLE_UART_BREAK_BITS_RX + BLE_UART_NUMBER_OF_START_BIT) \
                            * BLE_UART_OVER_SAMPLE_COUNT) + BLE_UART_HALF_BIT_COUNT) - 1u)

#else /* BLE_UART_OVER_SAMPLE_COUNT == BLE_UART_OVER_SAMPLE_16 */
    #define BLE_UART_HD_TXBITCTR_INIT   ((8u * BLE_UART_OVER_SAMPLE_COUNT) - 1u)
    /* 7bit counter need one more bit for OverSampleCount = 16 */
    #define BLE_UART_RXBITCTR_INIT      (((7u * BLE_UART_OVER_SAMPLE_COUNT) - 1u) + \
                                                      BLE_UART_HALF_BIT_COUNT)
#endif /* End BLE_UART_OVER_SAMPLE_COUNT */

#define BLE_UART_HD_RXBITCTR_INIT                   BLE_UART_RXBITCTR_INIT


/***************************************
* Global variables external identifier
***************************************/

extern uint8 BLE_UART_initVar;
#if (BLE_UART_TX_INTERRUPT_ENABLED && BLE_UART_TX_ENABLED)
    extern volatile uint8 BLE_UART_txBuffer[BLE_UART_TX_BUFFER_SIZE];
    extern volatile uint8 BLE_UART_txBufferRead;
    extern uint8 BLE_UART_txBufferWrite;
#endif /* (BLE_UART_TX_INTERRUPT_ENABLED && BLE_UART_TX_ENABLED) */
#if (BLE_UART_RX_INTERRUPT_ENABLED && (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED))
    extern uint8 BLE_UART_errorStatus;
    extern volatile uint8 BLE_UART_rxBuffer[BLE_UART_RX_BUFFER_SIZE];
    extern volatile uint8 BLE_UART_rxBufferRead;
    extern volatile uint8 BLE_UART_rxBufferWrite;
    extern volatile uint8 BLE_UART_rxBufferLoopDetect;
    extern volatile uint8 BLE_UART_rxBufferOverflow;
    #if (BLE_UART_RXHW_ADDRESS_ENABLED)
        extern volatile uint8 BLE_UART_rxAddressMode;
        extern volatile uint8 BLE_UART_rxAddressDetected;
    #endif /* (BLE_UART_RXHW_ADDRESS_ENABLED) */
#endif /* (BLE_UART_RX_INTERRUPT_ENABLED && (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)) */


/***************************************
* Enumerated Types and Parameters
***************************************/

#define BLE_UART__B_UART__AM_SW_BYTE_BYTE 1
#define BLE_UART__B_UART__AM_SW_DETECT_TO_BUFFER 2
#define BLE_UART__B_UART__AM_HW_BYTE_BY_BYTE 3
#define BLE_UART__B_UART__AM_HW_DETECT_TO_BUFFER 4
#define BLE_UART__B_UART__AM_NONE 0

#define BLE_UART__B_UART__NONE_REVB 0
#define BLE_UART__B_UART__EVEN_REVB 1
#define BLE_UART__B_UART__ODD_REVB 2
#define BLE_UART__B_UART__MARK_SPACE_REVB 3



/***************************************
*    Initial Parameter Constants
***************************************/

/* UART shifts max 8 bits, Mark/Space functionality working if 9 selected */
#define BLE_UART_NUMBER_OF_DATA_BITS    ((8u > 8u) ? 8u : 8u)
#define BLE_UART_NUMBER_OF_STOP_BITS    (1u)

#if (BLE_UART_RXHW_ADDRESS_ENABLED)
    #define BLE_UART_RX_ADDRESS_MODE    (0u)
    #define BLE_UART_RX_HW_ADDRESS1     (0u)
    #define BLE_UART_RX_HW_ADDRESS2     (0u)
#endif /* (BLE_UART_RXHW_ADDRESS_ENABLED) */

#define BLE_UART_INIT_RX_INTERRUPTS_MASK \
                                  (uint8)((0 << BLE_UART_RX_STS_FIFO_NOTEMPTY_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_MRKSPC_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_ADDR_MATCH_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_PAR_ERROR_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_STOP_ERROR_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_BREAK_SHIFT) \
                                        | (0 << BLE_UART_RX_STS_OVERRUN_SHIFT))

#define BLE_UART_INIT_TX_INTERRUPTS_MASK \
                                  (uint8)((0 << BLE_UART_TX_STS_COMPLETE_SHIFT) \
                                        | (0 << BLE_UART_TX_STS_FIFO_EMPTY_SHIFT) \
                                        | (0 << BLE_UART_TX_STS_FIFO_FULL_SHIFT) \
                                        | (0 << BLE_UART_TX_STS_FIFO_NOT_FULL_SHIFT))


/***************************************
*              Registers
***************************************/

#ifdef BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BLE_UART_CONTROL_REG \
                            (* (reg8 *) BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
    #define BLE_UART_CONTROL_PTR \
                            (  (reg8 *) BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG )
#endif /* End BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BLE_UART_TX_ENABLED)
    #define BLE_UART_TXDATA_REG          (* (reg8 *) BLE_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BLE_UART_TXDATA_PTR          (  (reg8 *) BLE_UART_BUART_sTX_TxShifter_u0__F0_REG)
    #define BLE_UART_TXDATA_AUX_CTL_REG  (* (reg8 *) BLE_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BLE_UART_TXDATA_AUX_CTL_PTR  (  (reg8 *) BLE_UART_BUART_sTX_TxShifter_u0__DP_AUX_CTL_REG)
    #define BLE_UART_TXSTATUS_REG        (* (reg8 *) BLE_UART_BUART_sTX_TxSts__STATUS_REG)
    #define BLE_UART_TXSTATUS_PTR        (  (reg8 *) BLE_UART_BUART_sTX_TxSts__STATUS_REG)
    #define BLE_UART_TXSTATUS_MASK_REG   (* (reg8 *) BLE_UART_BUART_sTX_TxSts__MASK_REG)
    #define BLE_UART_TXSTATUS_MASK_PTR   (  (reg8 *) BLE_UART_BUART_sTX_TxSts__MASK_REG)
    #define BLE_UART_TXSTATUS_ACTL_REG   (* (reg8 *) BLE_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)
    #define BLE_UART_TXSTATUS_ACTL_PTR   (  (reg8 *) BLE_UART_BUART_sTX_TxSts__STATUS_AUX_CTL_REG)

    /* DP clock */
    #if(BLE_UART_TXCLKGEN_DP)
        #define BLE_UART_TXBITCLKGEN_CTR_REG        \
                                        (* (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BLE_UART_TXBITCLKGEN_CTR_PTR        \
                                        (  (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitClkGen__D0_REG)
        #define BLE_UART_TXBITCLKTX_COMPLETE_REG    \
                                        (* (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
        #define BLE_UART_TXBITCLKTX_COMPLETE_PTR    \
                                        (  (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitClkGen__D1_REG)
    #else     /* Count7 clock*/
        #define BLE_UART_TXBITCTR_PERIOD_REG    \
                                        (* (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BLE_UART_TXBITCTR_PERIOD_PTR    \
                                        (  (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__PERIOD_REG)
        #define BLE_UART_TXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BLE_UART_TXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__CONTROL_AUX_CTL_REG)
        #define BLE_UART_TXBITCTR_COUNTER_REG   \
                                        (* (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
        #define BLE_UART_TXBITCTR_COUNTER_PTR   \
                                        (  (reg8 *) BLE_UART_BUART_sTX_sCLOCK_TxBitCounter__COUNT_REG)
    #endif /* BLE_UART_TXCLKGEN_DP */

#endif /* End BLE_UART_TX_ENABLED */

#if(BLE_UART_HD_ENABLED)

    #define BLE_UART_TXDATA_REG             (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BLE_UART_TXDATA_PTR             (  (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__F1_REG )
    #define BLE_UART_TXDATA_AUX_CTL_REG     (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)
    #define BLE_UART_TXDATA_AUX_CTL_PTR     (  (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BLE_UART_TXSTATUS_REG           (* (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BLE_UART_TXSTATUS_PTR           (  (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BLE_UART_TXSTATUS_MASK_REG      (* (reg8 *) BLE_UART_BUART_sRX_RxSts__MASK_REG )
    #define BLE_UART_TXSTATUS_MASK_PTR      (  (reg8 *) BLE_UART_BUART_sRX_RxSts__MASK_REG )
    #define BLE_UART_TXSTATUS_ACTL_REG      (* (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BLE_UART_TXSTATUS_ACTL_PTR      (  (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End BLE_UART_HD_ENABLED */

#if( (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) )
    #define BLE_UART_RXDATA_REG             (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BLE_UART_RXDATA_PTR             (  (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__F0_REG )
    #define BLE_UART_RXADDRESS1_REG         (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BLE_UART_RXADDRESS1_PTR         (  (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__D0_REG )
    #define BLE_UART_RXADDRESS2_REG         (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BLE_UART_RXADDRESS2_PTR         (  (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__D1_REG )
    #define BLE_UART_RXDATA_AUX_CTL_REG     (* (reg8 *) BLE_UART_BUART_sRX_RxShifter_u0__DP_AUX_CTL_REG)

    #define BLE_UART_RXBITCTR_PERIOD_REG    (* (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BLE_UART_RXBITCTR_PERIOD_PTR    (  (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__PERIOD_REG )
    #define BLE_UART_RXBITCTR_CONTROL_REG   \
                                        (* (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BLE_UART_RXBITCTR_CONTROL_PTR   \
                                        (  (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__CONTROL_AUX_CTL_REG )
    #define BLE_UART_RXBITCTR_COUNTER_REG   (* (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__COUNT_REG )
    #define BLE_UART_RXBITCTR_COUNTER_PTR   (  (reg8 *) BLE_UART_BUART_sRX_RxBitCounter__COUNT_REG )

    #define BLE_UART_RXSTATUS_REG           (* (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BLE_UART_RXSTATUS_PTR           (  (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_REG )
    #define BLE_UART_RXSTATUS_MASK_REG      (* (reg8 *) BLE_UART_BUART_sRX_RxSts__MASK_REG )
    #define BLE_UART_RXSTATUS_MASK_PTR      (  (reg8 *) BLE_UART_BUART_sRX_RxSts__MASK_REG )
    #define BLE_UART_RXSTATUS_ACTL_REG      (* (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
    #define BLE_UART_RXSTATUS_ACTL_PTR      (  (reg8 *) BLE_UART_BUART_sRX_RxSts__STATUS_AUX_CTL_REG )
#endif /* End  (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) */

#if(BLE_UART_INTERNAL_CLOCK_USED)
    /* Register to enable or disable the digital clocks */
    #define BLE_UART_INTCLOCK_CLKEN_REG     (* (reg8 *) BLE_UART_IntClock__PM_ACT_CFG)
    #define BLE_UART_INTCLOCK_CLKEN_PTR     (  (reg8 *) BLE_UART_IntClock__PM_ACT_CFG)

    /* Clock mask for this clock. */
    #define BLE_UART_INTCLOCK_CLKEN_MASK    BLE_UART_IntClock__PM_ACT_MSK
#endif /* End BLE_UART_INTERNAL_CLOCK_USED */


/***************************************
*       Register Constants
***************************************/

#if(BLE_UART_TX_ENABLED)
    #define BLE_UART_TX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End BLE_UART_TX_ENABLED */

#if(BLE_UART_HD_ENABLED)
    #define BLE_UART_TX_FIFO_CLR            (0x02u) /* FIFO1 CLR */
#endif /* End BLE_UART_HD_ENABLED */

#if( (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) )
    #define BLE_UART_RX_FIFO_CLR            (0x01u) /* FIFO0 CLR */
#endif /* End  (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) */


/***************************************
* The following code is DEPRECATED and
* should not be used in new projects.
***************************************/

/* UART v2_40 obsolete definitions */
#define BLE_UART_WAIT_1_MS      BLE_UART_BL_CHK_DELAY_MS   

#define BLE_UART_TXBUFFERSIZE   BLE_UART_TX_BUFFER_SIZE
#define BLE_UART_RXBUFFERSIZE   BLE_UART_RX_BUFFER_SIZE

#if (BLE_UART_RXHW_ADDRESS_ENABLED)
    #define BLE_UART_RXADDRESSMODE  BLE_UART_RX_ADDRESS_MODE
    #define BLE_UART_RXHWADDRESS1   BLE_UART_RX_HW_ADDRESS1
    #define BLE_UART_RXHWADDRESS2   BLE_UART_RX_HW_ADDRESS2
    /* Backward compatible define */
    #define BLE_UART_RXAddressMode  BLE_UART_RXADDRESSMODE
#endif /* (BLE_UART_RXHW_ADDRESS_ENABLED) */

/* UART v2_30 obsolete definitions */
#define BLE_UART_initvar                    BLE_UART_initVar

#define BLE_UART_RX_Enabled                 BLE_UART_RX_ENABLED
#define BLE_UART_TX_Enabled                 BLE_UART_TX_ENABLED
#define BLE_UART_HD_Enabled                 BLE_UART_HD_ENABLED
#define BLE_UART_RX_IntInterruptEnabled     BLE_UART_RX_INTERRUPT_ENABLED
#define BLE_UART_TX_IntInterruptEnabled     BLE_UART_TX_INTERRUPT_ENABLED
#define BLE_UART_InternalClockUsed          BLE_UART_INTERNAL_CLOCK_USED
#define BLE_UART_RXHW_Address_Enabled       BLE_UART_RXHW_ADDRESS_ENABLED
#define BLE_UART_OverSampleCount            BLE_UART_OVER_SAMPLE_COUNT
#define BLE_UART_ParityType                 BLE_UART_PARITY_TYPE

#if( BLE_UART_TX_ENABLED && (BLE_UART_TXBUFFERSIZE > BLE_UART_FIFO_LENGTH))
    #define BLE_UART_TXBUFFER               BLE_UART_txBuffer
    #define BLE_UART_TXBUFFERREAD           BLE_UART_txBufferRead
    #define BLE_UART_TXBUFFERWRITE          BLE_UART_txBufferWrite
#endif /* End BLE_UART_TX_ENABLED */
#if( ( BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED ) && \
     (BLE_UART_RXBUFFERSIZE > BLE_UART_FIFO_LENGTH) )
    #define BLE_UART_RXBUFFER               BLE_UART_rxBuffer
    #define BLE_UART_RXBUFFERREAD           BLE_UART_rxBufferRead
    #define BLE_UART_RXBUFFERWRITE          BLE_UART_rxBufferWrite
    #define BLE_UART_RXBUFFERLOOPDETECT     BLE_UART_rxBufferLoopDetect
    #define BLE_UART_RXBUFFER_OVERFLOW      BLE_UART_rxBufferOverflow
#endif /* End BLE_UART_RX_ENABLED */

#ifdef BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG
    #define BLE_UART_CONTROL                BLE_UART_CONTROL_REG
#endif /* End BLE_UART_BUART_sCR_SyncCtl_CtrlReg__CONTROL_REG */

#if(BLE_UART_TX_ENABLED)
    #define BLE_UART_TXDATA                 BLE_UART_TXDATA_REG
    #define BLE_UART_TXSTATUS               BLE_UART_TXSTATUS_REG
    #define BLE_UART_TXSTATUS_MASK          BLE_UART_TXSTATUS_MASK_REG
    #define BLE_UART_TXSTATUS_ACTL          BLE_UART_TXSTATUS_ACTL_REG
    /* DP clock */
    #if(BLE_UART_TXCLKGEN_DP)
        #define BLE_UART_TXBITCLKGEN_CTR        BLE_UART_TXBITCLKGEN_CTR_REG
        #define BLE_UART_TXBITCLKTX_COMPLETE    BLE_UART_TXBITCLKTX_COMPLETE_REG
    #else     /* Count7 clock*/
        #define BLE_UART_TXBITCTR_PERIOD        BLE_UART_TXBITCTR_PERIOD_REG
        #define BLE_UART_TXBITCTR_CONTROL       BLE_UART_TXBITCTR_CONTROL_REG
        #define BLE_UART_TXBITCTR_COUNTER       BLE_UART_TXBITCTR_COUNTER_REG
    #endif /* BLE_UART_TXCLKGEN_DP */
#endif /* End BLE_UART_TX_ENABLED */

#if(BLE_UART_HD_ENABLED)
    #define BLE_UART_TXDATA                 BLE_UART_TXDATA_REG
    #define BLE_UART_TXSTATUS               BLE_UART_TXSTATUS_REG
    #define BLE_UART_TXSTATUS_MASK          BLE_UART_TXSTATUS_MASK_REG
    #define BLE_UART_TXSTATUS_ACTL          BLE_UART_TXSTATUS_ACTL_REG
#endif /* End BLE_UART_HD_ENABLED */

#if( (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) )
    #define BLE_UART_RXDATA                 BLE_UART_RXDATA_REG
    #define BLE_UART_RXADDRESS1             BLE_UART_RXADDRESS1_REG
    #define BLE_UART_RXADDRESS2             BLE_UART_RXADDRESS2_REG
    #define BLE_UART_RXBITCTR_PERIOD        BLE_UART_RXBITCTR_PERIOD_REG
    #define BLE_UART_RXBITCTR_CONTROL       BLE_UART_RXBITCTR_CONTROL_REG
    #define BLE_UART_RXBITCTR_COUNTER       BLE_UART_RXBITCTR_COUNTER_REG
    #define BLE_UART_RXSTATUS               BLE_UART_RXSTATUS_REG
    #define BLE_UART_RXSTATUS_MASK          BLE_UART_RXSTATUS_MASK_REG
    #define BLE_UART_RXSTATUS_ACTL          BLE_UART_RXSTATUS_ACTL_REG
#endif /* End  (BLE_UART_RX_ENABLED) || (BLE_UART_HD_ENABLED) */

#if(BLE_UART_INTERNAL_CLOCK_USED)
    #define BLE_UART_INTCLOCK_CLKEN         BLE_UART_INTCLOCK_CLKEN_REG
#endif /* End BLE_UART_INTERNAL_CLOCK_USED */

#define BLE_UART_WAIT_FOR_COMLETE_REINIT    BLE_UART_WAIT_FOR_COMPLETE_REINIT

#endif  /* CY_UART_BLE_UART_H */


/* [] END OF FILE */
