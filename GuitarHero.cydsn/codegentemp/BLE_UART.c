/*******************************************************************************
* File Name: BLE_UART.c
* Version 2.50
*
* Description:
*  This file provides all API functionality of the UART component
*
* Note:
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "BLE_UART.h"
#if (BLE_UART_INTERNAL_CLOCK_USED)
    #include "BLE_UART_IntClock.h"
#endif /* End BLE_UART_INTERNAL_CLOCK_USED */


/***************************************
* Global data allocation
***************************************/

uint8 BLE_UART_initVar = 0u;

#if (BLE_UART_TX_INTERRUPT_ENABLED && BLE_UART_TX_ENABLED)
    volatile uint8 BLE_UART_txBuffer[BLE_UART_TX_BUFFER_SIZE];
    volatile uint8 BLE_UART_txBufferRead = 0u;
    uint8 BLE_UART_txBufferWrite = 0u;
#endif /* (BLE_UART_TX_INTERRUPT_ENABLED && BLE_UART_TX_ENABLED) */

#if (BLE_UART_RX_INTERRUPT_ENABLED && (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED))
    uint8 BLE_UART_errorStatus = 0u;
    volatile uint8 BLE_UART_rxBuffer[BLE_UART_RX_BUFFER_SIZE];
    volatile uint8 BLE_UART_rxBufferRead  = 0u;
    volatile uint8 BLE_UART_rxBufferWrite = 0u;
    volatile uint8 BLE_UART_rxBufferLoopDetect = 0u;
    volatile uint8 BLE_UART_rxBufferOverflow   = 0u;
    #if (BLE_UART_RXHW_ADDRESS_ENABLED)
        volatile uint8 BLE_UART_rxAddressMode = BLE_UART_RX_ADDRESS_MODE;
        volatile uint8 BLE_UART_rxAddressDetected = 0u;
    #endif /* (BLE_UART_RXHW_ADDRESS_ENABLED) */
#endif /* (BLE_UART_RX_INTERRUPT_ENABLED && (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)) */


/*******************************************************************************
* Function Name: BLE_UART_Start
********************************************************************************
*
* Summary:
*  This is the preferred method to begin component operation.
*  BLE_UART_Start() sets the initVar variable, calls the
*  BLE_UART_Init() function, and then calls the
*  BLE_UART_Enable() function.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  The BLE_UART_intiVar variable is used to indicate initial
*  configuration of this component. The variable is initialized to zero (0u)
*  and set to one (1u) the first time BLE_UART_Start() is called. This
*  allows for component initialization without re-initialization in all
*  subsequent calls to the BLE_UART_Start() routine.
*
* Reentrant:
*  No.
*
*******************************************************************************/
void BLE_UART_Start(void) 
{
    /* If not initialized then initialize all required hardware and software */
    if(BLE_UART_initVar == 0u)
    {
        BLE_UART_Init();
        BLE_UART_initVar = 1u;
    }

    BLE_UART_Enable();
}


/*******************************************************************************
* Function Name: BLE_UART_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure
*  dialog settings. It is not necessary to call BLE_UART_Init() because
*  the BLE_UART_Start() API calls this function and is the preferred
*  method to begin component operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BLE_UART_Init(void) 
{
    #if(BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)

        #if (BLE_UART_RX_INTERRUPT_ENABLED)
            /* Set RX interrupt vector and priority */
            (void) CyIntSetVector(BLE_UART_RX_VECT_NUM, &BLE_UART_RXISR);
            CyIntSetPriority(BLE_UART_RX_VECT_NUM, BLE_UART_RX_PRIOR_NUM);
            BLE_UART_errorStatus = 0u;
        #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        #if (BLE_UART_RXHW_ADDRESS_ENABLED)
            BLE_UART_SetRxAddressMode(BLE_UART_RX_ADDRESS_MODE);
            BLE_UART_SetRxAddress1(BLE_UART_RX_HW_ADDRESS1);
            BLE_UART_SetRxAddress2(BLE_UART_RX_HW_ADDRESS2);
        #endif /* End BLE_UART_RXHW_ADDRESS_ENABLED */

        /* Init Count7 period */
        BLE_UART_RXBITCTR_PERIOD_REG = BLE_UART_RXBITCTR_INIT;
        /* Configure the Initial RX interrupt mask */
        BLE_UART_RXSTATUS_MASK_REG  = BLE_UART_INIT_RX_INTERRUPTS_MASK;
    #endif /* End BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED*/

    #if(BLE_UART_TX_ENABLED)
        #if (BLE_UART_TX_INTERRUPT_ENABLED)
            /* Set TX interrupt vector and priority */
            (void) CyIntSetVector(BLE_UART_TX_VECT_NUM, &BLE_UART_TXISR);
            CyIntSetPriority(BLE_UART_TX_VECT_NUM, BLE_UART_TX_PRIOR_NUM);
        #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */

        /* Write Counter Value for TX Bit Clk Generator*/
        #if (BLE_UART_TXCLKGEN_DP)
            BLE_UART_TXBITCLKGEN_CTR_REG = BLE_UART_BIT_CENTER;
            BLE_UART_TXBITCLKTX_COMPLETE_REG = ((BLE_UART_NUMBER_OF_DATA_BITS +
                        BLE_UART_NUMBER_OF_START_BIT) * BLE_UART_OVER_SAMPLE_COUNT) - 1u;
        #else
            BLE_UART_TXBITCTR_PERIOD_REG = ((BLE_UART_NUMBER_OF_DATA_BITS +
                        BLE_UART_NUMBER_OF_START_BIT) * BLE_UART_OVER_SAMPLE_8) - 1u;
        #endif /* End BLE_UART_TXCLKGEN_DP */

        /* Configure the Initial TX interrupt mask */
        #if (BLE_UART_TX_INTERRUPT_ENABLED)
            BLE_UART_TXSTATUS_MASK_REG = BLE_UART_TX_STS_FIFO_EMPTY;
        #else
            BLE_UART_TXSTATUS_MASK_REG = BLE_UART_INIT_TX_INTERRUPTS_MASK;
        #endif /*End BLE_UART_TX_INTERRUPT_ENABLED*/

    #endif /* End BLE_UART_TX_ENABLED */

    #if(BLE_UART_PARITY_TYPE_SW)  /* Write Parity to Control Register */
        BLE_UART_WriteControlRegister( \
            (BLE_UART_ReadControlRegister() & (uint8)~BLE_UART_CTRL_PARITY_TYPE_MASK) | \
            (uint8)(BLE_UART_PARITY_TYPE << BLE_UART_CTRL_PARITY_TYPE0_SHIFT) );
    #endif /* End BLE_UART_PARITY_TYPE_SW */
}


/*******************************************************************************
* Function Name: BLE_UART_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins component operation. It is not necessary
*  to call BLE_UART_Enable() because the BLE_UART_Start() API
*  calls this function, which is the preferred method to begin component
*  operation.

* Parameters:
*  None.
*
* Return:
*  None.
*
* Global Variables:
*  BLE_UART_rxAddressDetected - set to initial state (0).
*
*******************************************************************************/
void BLE_UART_Enable(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    #if (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)
        /* RX Counter (Count7) Enable */
        BLE_UART_RXBITCTR_CONTROL_REG |= BLE_UART_CNTR_ENABLE;

        /* Enable the RX Interrupt */
        BLE_UART_RXSTATUS_ACTL_REG  |= BLE_UART_INT_ENABLE;

        #if (BLE_UART_RX_INTERRUPT_ENABLED)
            BLE_UART_EnableRxInt();

            #if (BLE_UART_RXHW_ADDRESS_ENABLED)
                BLE_UART_rxAddressDetected = 0u;
            #endif /* (BLE_UART_RXHW_ADDRESS_ENABLED) */
        #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */
    #endif /* (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED) */

    #if(BLE_UART_TX_ENABLED)
        /* TX Counter (DP/Count7) Enable */
        #if(!BLE_UART_TXCLKGEN_DP)
            BLE_UART_TXBITCTR_CONTROL_REG |= BLE_UART_CNTR_ENABLE;
        #endif /* End BLE_UART_TXCLKGEN_DP */

        /* Enable the TX Interrupt */
        BLE_UART_TXSTATUS_ACTL_REG |= BLE_UART_INT_ENABLE;
        #if (BLE_UART_TX_INTERRUPT_ENABLED)
            BLE_UART_ClearPendingTxInt(); /* Clear history of TX_NOT_EMPTY */
            BLE_UART_EnableTxInt();
        #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */
     #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */

    #if (BLE_UART_INTERNAL_CLOCK_USED)
        BLE_UART_IntClock_Start();  /* Enable the clock */
    #endif /* (BLE_UART_INTERNAL_CLOCK_USED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLE_UART_Stop
********************************************************************************
*
* Summary:
*  Disables the UART operation.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
*******************************************************************************/
void BLE_UART_Stop(void) 
{
    uint8 enableInterrupts;
    enableInterrupts = CyEnterCriticalSection();

    /* Write Bit Counter Disable */
    #if (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)
        BLE_UART_RXBITCTR_CONTROL_REG &= (uint8) ~BLE_UART_CNTR_ENABLE;
    #endif /* (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED) */

    #if (BLE_UART_TX_ENABLED)
        #if(!BLE_UART_TXCLKGEN_DP)
            BLE_UART_TXBITCTR_CONTROL_REG &= (uint8) ~BLE_UART_CNTR_ENABLE;
        #endif /* (!BLE_UART_TXCLKGEN_DP) */
    #endif /* (BLE_UART_TX_ENABLED) */

    #if (BLE_UART_INTERNAL_CLOCK_USED)
        BLE_UART_IntClock_Stop();   /* Disable the clock */
    #endif /* (BLE_UART_INTERNAL_CLOCK_USED) */

    /* Disable internal interrupt component */
    #if (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)
        BLE_UART_RXSTATUS_ACTL_REG  &= (uint8) ~BLE_UART_INT_ENABLE;

        #if (BLE_UART_RX_INTERRUPT_ENABLED)
            BLE_UART_DisableRxInt();
        #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */
    #endif /* (BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED) */

    #if (BLE_UART_TX_ENABLED)
        BLE_UART_TXSTATUS_ACTL_REG &= (uint8) ~BLE_UART_INT_ENABLE;

        #if (BLE_UART_TX_INTERRUPT_ENABLED)
            BLE_UART_DisableTxInt();
        #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */
    #endif /* (BLE_UART_TX_ENABLED) */

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: BLE_UART_ReadControlRegister
********************************************************************************
*
* Summary:
*  Returns the current value of the control register.
*
* Parameters:
*  None.
*
* Return:
*  Contents of the control register.
*
*******************************************************************************/
uint8 BLE_UART_ReadControlRegister(void) 
{
    #if (BLE_UART_CONTROL_REG_REMOVED)
        return(0u);
    #else
        return(BLE_UART_CONTROL_REG);
    #endif /* (BLE_UART_CONTROL_REG_REMOVED) */
}


/*******************************************************************************
* Function Name: BLE_UART_WriteControlRegister
********************************************************************************
*
* Summary:
*  Writes an 8-bit value into the control register
*
* Parameters:
*  control:  control register value
*
* Return:
*  None.
*
*******************************************************************************/
void  BLE_UART_WriteControlRegister(uint8 control) 
{
    #if (BLE_UART_CONTROL_REG_REMOVED)
        if(0u != control)
        {
            /* Suppress compiler warning */
        }
    #else
       BLE_UART_CONTROL_REG = control;
    #endif /* (BLE_UART_CONTROL_REG_REMOVED) */
}


#if(BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED)
    /*******************************************************************************
    * Function Name: BLE_UART_SetRxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the RX interrupt sources enabled.
    *
    * Parameters:
    *  IntSrc:  Bit field containing the RX interrupts to enable. Based on the 
    *  bit-field arrangement of the status register. This value must be a 
    *  combination of status register bit-masks shown below:
    *      BLE_UART_RX_STS_FIFO_NOTEMPTY    Interrupt on byte received.
    *      BLE_UART_RX_STS_PAR_ERROR        Interrupt on parity error.
    *      BLE_UART_RX_STS_STOP_ERROR       Interrupt on stop error.
    *      BLE_UART_RX_STS_BREAK            Interrupt on break.
    *      BLE_UART_RX_STS_OVERRUN          Interrupt on overrun error.
    *      BLE_UART_RX_STS_ADDR_MATCH       Interrupt on address match.
    *      BLE_UART_RX_STS_MRKSPC           Interrupt on address detect.
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BLE_UART_SetRxInterruptMode(uint8 intSrc) 
    {
        BLE_UART_RXSTATUS_MASK_REG  = intSrc;
    }


    /*******************************************************************************
    * Function Name: BLE_UART_ReadRxData
    ********************************************************************************
    *
    * Summary:
    *  Returns the next byte of received data. This function returns data without
    *  checking the status. You must check the status separately.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Received data from RX register
    *
    * Global Variables:
    *  BLE_UART_rxBuffer - RAM buffer pointer for save received data.
    *  BLE_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BLE_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BLE_UART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BLE_UART_ReadRxData(void) 
    {
        uint8 rxData;

    #if (BLE_UART_RX_INTERRUPT_ENABLED)

        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BLE_UART_DisableRxInt();

        locRxBufferRead  = BLE_UART_rxBufferRead;
        locRxBufferWrite = BLE_UART_rxBufferWrite;

        if( (BLE_UART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BLE_UART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;

            if(locRxBufferRead >= BLE_UART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BLE_UART_rxBufferRead = locRxBufferRead;

            if(BLE_UART_rxBufferLoopDetect != 0u)
            {
                BLE_UART_rxBufferLoopDetect = 0u;
                #if ((BLE_UART_RX_INTERRUPT_ENABLED) && (BLE_UART_FLOW_CONTROL != 0u))
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BLE_UART_HD_ENABLED )
                        if((BLE_UART_CONTROL_REG & BLE_UART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only in RX
                            *  configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BLE_UART_RXSTATUS_MASK_REG  |= BLE_UART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BLE_UART_RXSTATUS_MASK_REG  |= BLE_UART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BLE_UART_HD_ENABLED */
                #endif /* ((BLE_UART_RX_INTERRUPT_ENABLED) && (BLE_UART_FLOW_CONTROL != 0u)) */
            }
        }
        else
        {   /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
            rxData = BLE_UART_RXDATA_REG;
        }

        BLE_UART_EnableRxInt();

    #else

        /* Needs to check status for RX_STS_FIFO_NOTEMPTY bit */
        rxData = BLE_UART_RXDATA_REG;

    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_ReadRxStatus
    ********************************************************************************
    *
    * Summary:
    *  Returns the current state of the receiver status register and the software
    *  buffer overflow status.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Current state of the status register.
    *
    * Side Effect:
    *  All status register bits are clear-on-read except
    *  BLE_UART_RX_STS_FIFO_NOTEMPTY.
    *  BLE_UART_RX_STS_FIFO_NOTEMPTY clears immediately after RX data
    *  register read.
    *
    * Global Variables:
    *  BLE_UART_rxBufferOverflow - used to indicate overload condition.
    *   It set to one in RX interrupt when there isn't free space in
    *   BLE_UART_rxBufferRead to write new data. This condition returned
    *   and cleared to zero by this API as an
    *   BLE_UART_RX_STS_SOFT_BUFF_OVER bit along with RX Status register
    *   bits.
    *
    *******************************************************************************/
    uint8 BLE_UART_ReadRxStatus(void) 
    {
        uint8 status;

        status = BLE_UART_RXSTATUS_REG & BLE_UART_RX_HW_MASK;

    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        if(BLE_UART_rxBufferOverflow != 0u)
        {
            status |= BLE_UART_RX_STS_SOFT_BUFF_OVER;
            BLE_UART_rxBufferOverflow = 0u;
        }
    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        return(status);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_GetChar
    ********************************************************************************
    *
    * Summary:
    *  Returns the last received byte of data. BLE_UART_GetChar() is
    *  designed for ASCII characters and returns a uint8 where 1 to 255 are values
    *  for valid characters and 0 indicates an error occurred or no data is present.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Character read from UART RX buffer. ASCII characters from 1 to 255 are valid.
    *  A returned zero signifies an error condition or no data available.
    *
    * Global Variables:
    *  BLE_UART_rxBuffer - RAM buffer pointer for save received data.
    *  BLE_UART_rxBufferWrite - cyclic index for write to rxBuffer,
    *     checked to identify new data.
    *  BLE_UART_rxBufferRead - cyclic index for read from rxBuffer,
    *     incremented after each byte has been read from buffer.
    *  BLE_UART_rxBufferLoopDetect - cleared if loop condition was detected
    *     in RX ISR.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint8 BLE_UART_GetChar(void) 
    {
        uint8 rxData = 0u;
        uint8 rxStatus;

    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        uint8 locRxBufferRead;
        uint8 locRxBufferWrite;

        /* Protect variables that could change on interrupt */
        BLE_UART_DisableRxInt();

        locRxBufferRead  = BLE_UART_rxBufferRead;
        locRxBufferWrite = BLE_UART_rxBufferWrite;

        if( (BLE_UART_rxBufferLoopDetect != 0u) || (locRxBufferRead != locRxBufferWrite) )
        {
            rxData = BLE_UART_rxBuffer[locRxBufferRead];
            locRxBufferRead++;
            if(locRxBufferRead >= BLE_UART_RX_BUFFER_SIZE)
            {
                locRxBufferRead = 0u;
            }
            /* Update the real pointer */
            BLE_UART_rxBufferRead = locRxBufferRead;

            if(BLE_UART_rxBufferLoopDetect != 0u)
            {
                BLE_UART_rxBufferLoopDetect = 0u;
                #if( (BLE_UART_RX_INTERRUPT_ENABLED) && (BLE_UART_FLOW_CONTROL != 0u) )
                    /* When Hardware Flow Control selected - return RX mask */
                    #if( BLE_UART_HD_ENABLED )
                        if((BLE_UART_CONTROL_REG & BLE_UART_CTRL_HD_SEND) == 0u)
                        {   /* In Half duplex mode return RX mask only if
                            *  RX configuration set, otherwise
                            *  mask will be returned in LoadRxConfig() API.
                            */
                            BLE_UART_RXSTATUS_MASK_REG |= BLE_UART_RX_STS_FIFO_NOTEMPTY;
                        }
                    #else
                        BLE_UART_RXSTATUS_MASK_REG |= BLE_UART_RX_STS_FIFO_NOTEMPTY;
                    #endif /* end BLE_UART_HD_ENABLED */
                #endif /* BLE_UART_RX_INTERRUPT_ENABLED and Hardware flow control*/
            }

        }
        else
        {   rxStatus = BLE_UART_RXSTATUS_REG;
            if((rxStatus & BLE_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
            {   /* Read received data from FIFO */
                rxData = BLE_UART_RXDATA_REG;
                /*Check status on error*/
                if((rxStatus & (BLE_UART_RX_STS_BREAK | BLE_UART_RX_STS_PAR_ERROR |
                                BLE_UART_RX_STS_STOP_ERROR | BLE_UART_RX_STS_OVERRUN)) != 0u)
                {
                    rxData = 0u;
                }
            }
        }

        BLE_UART_EnableRxInt();

    #else

        rxStatus =BLE_UART_RXSTATUS_REG;
        if((rxStatus & BLE_UART_RX_STS_FIFO_NOTEMPTY) != 0u)
        {
            /* Read received data from FIFO */
            rxData = BLE_UART_RXDATA_REG;

            /*Check status on error*/
            if((rxStatus & (BLE_UART_RX_STS_BREAK | BLE_UART_RX_STS_PAR_ERROR |
                            BLE_UART_RX_STS_STOP_ERROR | BLE_UART_RX_STS_OVERRUN)) != 0u)
            {
                rxData = 0u;
            }
        }
    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        return(rxData);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_GetByte
    ********************************************************************************
    *
    * Summary:
    *  Reads UART RX buffer immediately, returns received character and error
    *  condition.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  MSB contains status and LSB contains UART RX data. If the MSB is nonzero,
    *  an error has occurred.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    uint16 BLE_UART_GetByte(void) 
    {
        
    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        uint16 locErrorStatus;
        /* Protect variables that could change on interrupt */
        BLE_UART_DisableRxInt();
        locErrorStatus = (uint16)BLE_UART_errorStatus;
        BLE_UART_errorStatus = 0u;
        BLE_UART_EnableRxInt();
        return ( (uint16)(locErrorStatus << 8u) | BLE_UART_ReadRxData() );
    #else
        return ( ((uint16)BLE_UART_ReadRxStatus() << 8u) | BLE_UART_ReadRxData() );
    #endif /* BLE_UART_RX_INTERRUPT_ENABLED */
        
    }


    /*******************************************************************************
    * Function Name: BLE_UART_GetRxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of received bytes available in the RX buffer.
    *  * RX software buffer is disabled (RX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty RX FIFO or 1 for not empty RX FIFO.
    *  * RX software buffer is enabled: returns the number of bytes available in 
    *    the RX software buffer. Bytes available in the RX FIFO do not take to 
    *    account.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  uint8: Number of bytes in the RX buffer. 
    *    Return value type depends on RX Buffer Size parameter.
    *
    * Global Variables:
    *  BLE_UART_rxBufferWrite - used to calculate left bytes.
    *  BLE_UART_rxBufferRead - used to calculate left bytes.
    *  BLE_UART_rxBufferLoopDetect - checked to decide left bytes amount.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the RX Buffer is.
    *
    *******************************************************************************/
    uint8 BLE_UART_GetRxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BLE_UART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt */
        BLE_UART_DisableRxInt();

        if(BLE_UART_rxBufferRead == BLE_UART_rxBufferWrite)
        {
            if(BLE_UART_rxBufferLoopDetect != 0u)
            {
                size = BLE_UART_RX_BUFFER_SIZE;
            }
            else
            {
                size = 0u;
            }
        }
        else if(BLE_UART_rxBufferRead < BLE_UART_rxBufferWrite)
        {
            size = (BLE_UART_rxBufferWrite - BLE_UART_rxBufferRead);
        }
        else
        {
            size = (BLE_UART_RX_BUFFER_SIZE - BLE_UART_rxBufferRead) + BLE_UART_rxBufferWrite;
        }

        BLE_UART_EnableRxInt();

    #else

        /* We can only know if there is data in the fifo. */
        size = ((BLE_UART_RXSTATUS_REG & BLE_UART_RX_STS_FIFO_NOTEMPTY) != 0u) ? 1u : 0u;

    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        return(size);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_ClearRxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears the receiver memory buffer and hardware RX FIFO of all received data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_rxBufferWrite - cleared to zero.
    *  BLE_UART_rxBufferRead - cleared to zero.
    *  BLE_UART_rxBufferLoopDetect - cleared to zero.
    *  BLE_UART_rxBufferOverflow - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may
    *  have remained in the RAM.
    *
    * Side Effects:
    *  Any received data not read from the RAM or FIFO buffer will be lost.
    *
    *******************************************************************************/
    void BLE_UART_ClearRxBuffer(void) 
    {
        uint8 enableInterrupts;

        /* Clear the HW FIFO */
        enableInterrupts = CyEnterCriticalSection();
        BLE_UART_RXDATA_AUX_CTL_REG |= (uint8)  BLE_UART_RX_FIFO_CLR;
        BLE_UART_RXDATA_AUX_CTL_REG &= (uint8) ~BLE_UART_RX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BLE_UART_RX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BLE_UART_DisableRxInt();

        BLE_UART_rxBufferRead = 0u;
        BLE_UART_rxBufferWrite = 0u;
        BLE_UART_rxBufferLoopDetect = 0u;
        BLE_UART_rxBufferOverflow = 0u;

        BLE_UART_EnableRxInt();

    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

    }


    /*******************************************************************************
    * Function Name: BLE_UART_SetRxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Sets the software controlled Addressing mode used by the RX portion of the
    *  UART.
    *
    * Parameters:
    *  addressMode: Enumerated value indicating the mode of RX addressing
    *  BLE_UART__B_UART__AM_SW_BYTE_BYTE -  Software Byte-by-Byte address
    *                                               detection
    *  BLE_UART__B_UART__AM_SW_DETECT_TO_BUFFER - Software Detect to Buffer
    *                                               address detection
    *  BLE_UART__B_UART__AM_HW_BYTE_BY_BYTE - Hardware Byte-by-Byte address
    *                                               detection
    *  BLE_UART__B_UART__AM_HW_DETECT_TO_BUFFER - Hardware Detect to Buffer
    *                                               address detection
    *  BLE_UART__B_UART__AM_NONE - No address detection
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_rxAddressMode - the parameter stored in this variable for
    *   the farther usage in RX ISR.
    *  BLE_UART_rxAddressDetected - set to initial state (0).
    *
    *******************************************************************************/
    void BLE_UART_SetRxAddressMode(uint8 addressMode)
                                                        
    {
        #if(BLE_UART_RXHW_ADDRESS_ENABLED)
            #if(BLE_UART_CONTROL_REG_REMOVED)
                if(0u != addressMode)
                {
                    /* Suppress compiler warning */
                }
            #else /* BLE_UART_CONTROL_REG_REMOVED */
                uint8 tmpCtrl;
                tmpCtrl = BLE_UART_CONTROL_REG & (uint8)~BLE_UART_CTRL_RXADDR_MODE_MASK;
                tmpCtrl |= (uint8)(addressMode << BLE_UART_CTRL_RXADDR_MODE0_SHIFT);
                BLE_UART_CONTROL_REG = tmpCtrl;

                #if(BLE_UART_RX_INTERRUPT_ENABLED && \
                   (BLE_UART_RXBUFFERSIZE > BLE_UART_FIFO_LENGTH) )
                    BLE_UART_rxAddressMode = addressMode;
                    BLE_UART_rxAddressDetected = 0u;
                #endif /* End BLE_UART_RXBUFFERSIZE > BLE_UART_FIFO_LENGTH*/
            #endif /* End BLE_UART_CONTROL_REG_REMOVED */
        #else /* BLE_UART_RXHW_ADDRESS_ENABLED */
            if(0u != addressMode)
            {
                /* Suppress compiler warning */
            }
        #endif /* End BLE_UART_RXHW_ADDRESS_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BLE_UART_SetRxAddress1
    ********************************************************************************
    *
    * Summary:
    *  Sets the first of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #1 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BLE_UART_SetRxAddress1(uint8 address) 
    {
        BLE_UART_RXADDRESS1_REG = address;
    }


    /*******************************************************************************
    * Function Name: BLE_UART_SetRxAddress2
    ********************************************************************************
    *
    * Summary:
    *  Sets the second of two hardware-detectable receiver addresses.
    *
    * Parameters:
    *  address: Address #2 for hardware address detection.
    *
    * Return:
    *  None.
    *
    *******************************************************************************/
    void BLE_UART_SetRxAddress2(uint8 address) 
    {
        BLE_UART_RXADDRESS2_REG = address;
    }

#endif  /* BLE_UART_RX_ENABLED || BLE_UART_HD_ENABLED*/


#if( (BLE_UART_TX_ENABLED) || (BLE_UART_HD_ENABLED) )
    /*******************************************************************************
    * Function Name: BLE_UART_SetTxInterruptMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the TX interrupt sources to be enabled, but does not enable the
    *  interrupt.
    *
    * Parameters:
    *  intSrc: Bit field containing the TX interrupt sources to enable
    *   BLE_UART_TX_STS_COMPLETE        Interrupt on TX byte complete
    *   BLE_UART_TX_STS_FIFO_EMPTY      Interrupt when TX FIFO is empty
    *   BLE_UART_TX_STS_FIFO_FULL       Interrupt when TX FIFO is full
    *   BLE_UART_TX_STS_FIFO_NOT_FULL   Interrupt when TX FIFO is not full
    *
    * Return:
    *  None.
    *
    * Theory:
    *  Enables the output of specific status bits to the interrupt controller
    *
    *******************************************************************************/
    void BLE_UART_SetTxInterruptMode(uint8 intSrc) 
    {
        BLE_UART_TXSTATUS_MASK_REG = intSrc;
    }


    /*******************************************************************************
    * Function Name: BLE_UART_WriteTxData
    ********************************************************************************
    *
    * Summary:
    *  Places a byte of data into the transmit buffer to be sent when the bus is
    *  available without checking the TX status register. You must check status
    *  separately.
    *
    * Parameters:
    *  txDataByte: data byte
    *
    * Return:
    * None.
    *
    * Global Variables:
    *  BLE_UART_txBuffer - RAM buffer pointer for save data for transmission
    *  BLE_UART_txBufferWrite - cyclic index for write to txBuffer,
    *    incremented after each byte saved to buffer.
    *  BLE_UART_txBufferRead - cyclic index for read from txBuffer,
    *    checked to identify the condition to write to FIFO directly or to TX buffer
    *  BLE_UART_initVar - checked to identify that the component has been
    *    initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BLE_UART_WriteTxData(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function*/
        if(BLE_UART_initVar != 0u)
        {
        #if (BLE_UART_TX_INTERRUPT_ENABLED)

            /* Protect variables that could change on interrupt. */
            BLE_UART_DisableTxInt();

            if( (BLE_UART_txBufferRead == BLE_UART_txBufferWrite) &&
                ((BLE_UART_TXSTATUS_REG & BLE_UART_TX_STS_FIFO_FULL) == 0u) )
            {
                /* Add directly to the FIFO. */
                BLE_UART_TXDATA_REG = txDataByte;
            }
            else
            {
                if(BLE_UART_txBufferWrite >= BLE_UART_TX_BUFFER_SIZE)
                {
                    BLE_UART_txBufferWrite = 0u;
                }

                BLE_UART_txBuffer[BLE_UART_txBufferWrite] = txDataByte;

                /* Add to the software buffer. */
                BLE_UART_txBufferWrite++;
            }

            BLE_UART_EnableTxInt();

        #else

            /* Add directly to the FIFO. */
            BLE_UART_TXDATA_REG = txDataByte;

        #endif /*(BLE_UART_TX_INTERRUPT_ENABLED) */
        }
    }


    /*******************************************************************************
    * Function Name: BLE_UART_ReadTxStatus
    ********************************************************************************
    *
    * Summary:
    *  Reads the status register for the TX portion of the UART.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Contents of the status register
    *
    * Theory:
    *  This function reads the TX status register, which is cleared on read.
    *  It is up to the user to handle all bits in this return value accordingly,
    *  even if the bit was not enabled as an interrupt source the event happened
    *  and must be handled accordingly.
    *
    *******************************************************************************/
    uint8 BLE_UART_ReadTxStatus(void) 
    {
        return(BLE_UART_TXSTATUS_REG);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_PutChar
    ********************************************************************************
    *
    * Summary:
    *  Puts a byte of data into the transmit buffer to be sent when the bus is
    *  available. This is a blocking API that waits until the TX buffer has room to
    *  hold the data.
    *
    * Parameters:
    *  txDataByte: Byte containing the data to transmit
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_txBuffer - RAM buffer pointer for save data for transmission
    *  BLE_UART_txBufferWrite - cyclic index for write to txBuffer,
    *     checked to identify free space in txBuffer and incremented after each byte
    *     saved to buffer.
    *  BLE_UART_txBufferRead - cyclic index for read from txBuffer,
    *     checked to identify free space in txBuffer.
    *  BLE_UART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to transmit any byte of data in a single transfer
    *
    *******************************************************************************/
    void BLE_UART_PutChar(uint8 txDataByte) 
    {
    #if (BLE_UART_TX_INTERRUPT_ENABLED)
        /* The temporary output pointer is used since it takes two instructions
        *  to increment with a wrap, and we can't risk doing that with the real
        *  pointer and getting an interrupt in between instructions.
        */
        uint8 locTxBufferWrite;
        uint8 locTxBufferRead;

        do
        { /* Block if software buffer is full, so we don't overwrite. */

        #if ((BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Disable TX interrupt to protect variables from modification */
            BLE_UART_DisableTxInt();
        #endif /* (BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            locTxBufferWrite = BLE_UART_txBufferWrite;
            locTxBufferRead  = BLE_UART_txBufferRead;

        #if ((BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3))
            /* Enable interrupt to continue transmission */
            BLE_UART_EnableTxInt();
        #endif /* (BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3) */
        }
        while( (locTxBufferWrite < locTxBufferRead) ? (locTxBufferWrite == (locTxBufferRead - 1u)) :
                                ((locTxBufferWrite - locTxBufferRead) ==
                                (uint8)(BLE_UART_TX_BUFFER_SIZE - 1u)) );

        if( (locTxBufferRead == locTxBufferWrite) &&
            ((BLE_UART_TXSTATUS_REG & BLE_UART_TX_STS_FIFO_FULL) == 0u) )
        {
            /* Add directly to the FIFO */
            BLE_UART_TXDATA_REG = txDataByte;
        }
        else
        {
            if(locTxBufferWrite >= BLE_UART_TX_BUFFER_SIZE)
            {
                locTxBufferWrite = 0u;
            }
            /* Add to the software buffer. */
            BLE_UART_txBuffer[locTxBufferWrite] = txDataByte;
            locTxBufferWrite++;

            /* Finally, update the real output pointer */
        #if ((BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3))
            BLE_UART_DisableTxInt();
        #endif /* (BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            BLE_UART_txBufferWrite = locTxBufferWrite;

        #if ((BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3))
            BLE_UART_EnableTxInt();
        #endif /* (BLE_UART_TX_BUFFER_SIZE > BLE_UART_MAX_BYTE_VALUE) && (CY_PSOC3) */

            if(0u != (BLE_UART_TXSTATUS_REG & BLE_UART_TX_STS_FIFO_EMPTY))
            {
                /* Trigger TX interrupt to send software buffer */
                BLE_UART_SetPendingTxInt();
            }
        }

    #else

        while((BLE_UART_TXSTATUS_REG & BLE_UART_TX_STS_FIFO_FULL) != 0u)
        {
            /* Wait for room in the FIFO */
        }

        /* Add directly to the FIFO */
        BLE_UART_TXDATA_REG = txDataByte;

    #endif /* BLE_UART_TX_INTERRUPT_ENABLED */
    }


    /*******************************************************************************
    * Function Name: BLE_UART_PutString
    ********************************************************************************
    *
    * Summary:
    *  Sends a NULL terminated string to the TX buffer for transmission.
    *
    * Parameters:
    *  string[]: Pointer to the null terminated string array residing in RAM or ROM
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BLE_UART_PutString(const char8 string[]) 
    {
        uint16 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BLE_UART_initVar != 0u)
        {
            /* This is a blocking function, it will not exit until all data is sent */
            while(string[bufIndex] != (char8) 0)
            {
                BLE_UART_PutChar((uint8)string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BLE_UART_PutArray
    ********************************************************************************
    *
    * Summary:
    *  Places N bytes of data from a memory array into the TX buffer for
    *  transmission.
    *
    * Parameters:
    *  string[]: Address of the memory array residing in RAM or ROM.
    *  byteCount: Number of bytes to be transmitted. The type depends on TX Buffer
    *             Size parameter.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  If there is not enough memory in the TX buffer for the entire string, this
    *  function blocks until the last character of the string is loaded into the
    *  TX buffer.
    *
    *******************************************************************************/
    void BLE_UART_PutArray(const uint8 string[], uint8 byteCount)
                                                                    
    {
        uint8 bufIndex = 0u;

        /* If not Initialized then skip this function */
        if(BLE_UART_initVar != 0u)
        {
            while(bufIndex < byteCount)
            {
                BLE_UART_PutChar(string[bufIndex]);
                bufIndex++;
            }
        }
    }


    /*******************************************************************************
    * Function Name: BLE_UART_PutCRLF
    ********************************************************************************
    *
    * Summary:
    *  Writes a byte of data followed by a carriage return (0x0D) and line feed
    *  (0x0A) to the transmit buffer.
    *
    * Parameters:
    *  txDataByte: Data byte to transmit before the carriage return and line feed.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_initVar - checked to identify that the component has been
    *     initialized.
    *
    * Reentrant:
    *  No.
    *
    *******************************************************************************/
    void BLE_UART_PutCRLF(uint8 txDataByte) 
    {
        /* If not Initialized then skip this function */
        if(BLE_UART_initVar != 0u)
        {
            BLE_UART_PutChar(txDataByte);
            BLE_UART_PutChar(0x0Du);
            BLE_UART_PutChar(0x0Au);
        }
    }


    /*******************************************************************************
    * Function Name: BLE_UART_GetTxBufferSize
    ********************************************************************************
    *
    * Summary:
    *  Returns the number of bytes in the TX buffer which are waiting to be 
    *  transmitted.
    *  * TX software buffer is disabled (TX Buffer Size parameter is equal to 4): 
    *    returns 0 for empty TX FIFO, 1 for not full TX FIFO or 4 for full TX FIFO.
    *  * TX software buffer is enabled: returns the number of bytes in the TX 
    *    software buffer which are waiting to be transmitted. Bytes available in the
    *    TX FIFO do not count.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  Number of bytes used in the TX buffer. Return value type depends on the TX 
    *  Buffer Size parameter.
    *
    * Global Variables:
    *  BLE_UART_txBufferWrite - used to calculate left space.
    *  BLE_UART_txBufferRead - used to calculate left space.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Allows the user to find out how full the TX Buffer is.
    *
    *******************************************************************************/
    uint8 BLE_UART_GetTxBufferSize(void)
                                                            
    {
        uint8 size;

    #if (BLE_UART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BLE_UART_DisableTxInt();

        if(BLE_UART_txBufferRead == BLE_UART_txBufferWrite)
        {
            size = 0u;
        }
        else if(BLE_UART_txBufferRead < BLE_UART_txBufferWrite)
        {
            size = (BLE_UART_txBufferWrite - BLE_UART_txBufferRead);
        }
        else
        {
            size = (BLE_UART_TX_BUFFER_SIZE - BLE_UART_txBufferRead) +
                    BLE_UART_txBufferWrite;
        }

        BLE_UART_EnableTxInt();

    #else

        size = BLE_UART_TXSTATUS_REG;

        /* Is the fifo is full. */
        if((size & BLE_UART_TX_STS_FIFO_FULL) != 0u)
        {
            size = BLE_UART_FIFO_LENGTH;
        }
        else if((size & BLE_UART_TX_STS_FIFO_EMPTY) != 0u)
        {
            size = 0u;
        }
        else
        {
            /* We only know there is data in the fifo. */
            size = 1u;
        }

    #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */

    return(size);
    }


    /*******************************************************************************
    * Function Name: BLE_UART_ClearTxBuffer
    ********************************************************************************
    *
    * Summary:
    *  Clears all data from the TX buffer and hardware TX FIFO.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_txBufferWrite - cleared to zero.
    *  BLE_UART_txBufferRead - cleared to zero.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  Setting the pointers to zero makes the system believe there is no data to
    *  read and writing will resume at address 0 overwriting any data that may have
    *  remained in the RAM.
    *
    * Side Effects:
    *  Data waiting in the transmit buffer is not sent; a byte that is currently
    *  transmitting finishes transmitting.
    *
    *******************************************************************************/
    void BLE_UART_ClearTxBuffer(void) 
    {
        uint8 enableInterrupts;

        enableInterrupts = CyEnterCriticalSection();
        /* Clear the HW FIFO */
        BLE_UART_TXDATA_AUX_CTL_REG |= (uint8)  BLE_UART_TX_FIFO_CLR;
        BLE_UART_TXDATA_AUX_CTL_REG &= (uint8) ~BLE_UART_TX_FIFO_CLR;
        CyExitCriticalSection(enableInterrupts);

    #if (BLE_UART_TX_INTERRUPT_ENABLED)

        /* Protect variables that could change on interrupt. */
        BLE_UART_DisableTxInt();

        BLE_UART_txBufferRead = 0u;
        BLE_UART_txBufferWrite = 0u;

        /* Enable Tx interrupt. */
        BLE_UART_EnableTxInt();

    #endif /* (BLE_UART_TX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BLE_UART_SendBreak
    ********************************************************************************
    *
    * Summary:
    *  Transmits a break signal on the bus.
    *
    * Parameters:
    *  uint8 retMode:  Send Break return mode. See the following table for options.
    *   BLE_UART_SEND_BREAK - Initialize registers for break, send the Break
    *       signal and return immediately.
    *   BLE_UART_WAIT_FOR_COMPLETE_REINIT - Wait until break transmission is
    *       complete, reinitialize registers to normal transmission mode then return
    *   BLE_UART_REINIT - Reinitialize registers to normal transmission mode
    *       then return.
    *   BLE_UART_SEND_WAIT_REINIT - Performs both options: 
    *      BLE_UART_SEND_BREAK and BLE_UART_WAIT_FOR_COMPLETE_REINIT.
    *      This option is recommended for most cases.
    *
    * Return:
    *  None.
    *
    * Global Variables:
    *  BLE_UART_initVar - checked to identify that the component has been
    *     initialized.
    *  txPeriod - static variable, used for keeping TX period configuration.
    *
    * Reentrant:
    *  No.
    *
    * Theory:
    *  SendBreak function initializes registers to send 13-bit break signal. It is
    *  important to return the registers configuration to normal for continue 8-bit
    *  operation.
    *  There are 3 variants for this API usage:
    *  1) SendBreak(3) - function will send the Break signal and take care on the
    *     configuration returning. Function will block CPU until transmission
    *     complete.
    *  2) User may want to use blocking time if UART configured to the low speed
    *     operation
    *     Example for this case:
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     SendBreak(1);     - complete Break operation
    *  3) Same to 2) but user may want to initialize and use the interrupt to
    *     complete break operation.
    *     Example for this case:
    *     Initialize TX interrupt with "TX - On TX Complete" parameter
    *     SendBreak(0);     - initialize Break signal transmission
    *         Add your code here to use CPU time
    *     When interrupt appear with BLE_UART_TX_STS_COMPLETE status:
    *     SendBreak(2);     - complete Break operation
    *
    * Side Effects:
    *  The BLE_UART_SendBreak() function initializes registers to send a
    *  break signal.
    *  Break signal length depends on the break signal bits configuration.
    *  The register configuration should be reinitialized before normal 8-bit
    *  communication can continue.
    *
    *******************************************************************************/
    void BLE_UART_SendBreak(uint8 retMode) 
    {

        /* If not Initialized then skip this function*/
        if(BLE_UART_initVar != 0u)
        {
            /* Set the Counter to 13-bits and transmit a 00 byte */
            /* When that is done then reset the counter value back */
            uint8 tmpStat;

        #if(BLE_UART_HD_ENABLED) /* Half Duplex mode*/

            if( (retMode == BLE_UART_SEND_BREAK) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT ) )
            {
                /* CTRL_HD_SEND_BREAK - sends break bits in HD mode */
                BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() |
                                                      BLE_UART_CTRL_HD_SEND_BREAK);
                /* Send zeros */
                BLE_UART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BLE_UART_TXSTATUS_REG;
                }
                while((tmpStat & BLE_UART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BLE_UART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BLE_UART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BLE_UART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BLE_UART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BLE_UART_REINIT) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT) )
            {
                BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() &
                                              (uint8)~BLE_UART_CTRL_HD_SEND_BREAK);
            }

        #else /* BLE_UART_HD_ENABLED Full Duplex mode */

            static uint8 txPeriod;

            if( (retMode == BLE_UART_SEND_BREAK) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT) )
            {
                /* CTRL_HD_SEND_BREAK - skip to send parity bit at Break signal in Full Duplex mode */
                #if( (BLE_UART_PARITY_TYPE != BLE_UART__B_UART__NONE_REVB) || \
                                    (BLE_UART_PARITY_TYPE_SW != 0u) )
                    BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() |
                                                          BLE_UART_CTRL_HD_SEND_BREAK);
                #endif /* End BLE_UART_PARITY_TYPE != BLE_UART__B_UART__NONE_REVB  */

                #if(BLE_UART_TXCLKGEN_DP)
                    txPeriod = BLE_UART_TXBITCLKTX_COMPLETE_REG;
                    BLE_UART_TXBITCLKTX_COMPLETE_REG = BLE_UART_TXBITCTR_BREAKBITS;
                #else
                    txPeriod = BLE_UART_TXBITCTR_PERIOD_REG;
                    BLE_UART_TXBITCTR_PERIOD_REG = BLE_UART_TXBITCTR_BREAKBITS8X;
                #endif /* End BLE_UART_TXCLKGEN_DP */

                /* Send zeros */
                BLE_UART_TXDATA_REG = 0u;

                do /* Wait until transmit starts */
                {
                    tmpStat = BLE_UART_TXSTATUS_REG;
                }
                while((tmpStat & BLE_UART_TX_STS_FIFO_EMPTY) != 0u);
            }

            if( (retMode == BLE_UART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT) )
            {
                do /* Wait until transmit complete */
                {
                    tmpStat = BLE_UART_TXSTATUS_REG;
                }
                while(((uint8)~tmpStat & BLE_UART_TX_STS_COMPLETE) != 0u);
            }

            if( (retMode == BLE_UART_WAIT_FOR_COMPLETE_REINIT) ||
                (retMode == BLE_UART_REINIT) ||
                (retMode == BLE_UART_SEND_WAIT_REINIT) )
            {

            #if(BLE_UART_TXCLKGEN_DP)
                BLE_UART_TXBITCLKTX_COMPLETE_REG = txPeriod;
            #else
                BLE_UART_TXBITCTR_PERIOD_REG = txPeriod;
            #endif /* End BLE_UART_TXCLKGEN_DP */

            #if( (BLE_UART_PARITY_TYPE != BLE_UART__B_UART__NONE_REVB) || \
                 (BLE_UART_PARITY_TYPE_SW != 0u) )
                BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() &
                                                      (uint8) ~BLE_UART_CTRL_HD_SEND_BREAK);
            #endif /* End BLE_UART_PARITY_TYPE != NONE */
            }
        #endif    /* End BLE_UART_HD_ENABLED */
        }
    }


    /*******************************************************************************
    * Function Name: BLE_UART_SetTxAddressMode
    ********************************************************************************
    *
    * Summary:
    *  Configures the transmitter to signal the next bytes is address or data.
    *
    * Parameters:
    *  addressMode: 
    *       BLE_UART_SET_SPACE - Configure the transmitter to send the next
    *                                    byte as a data.
    *       BLE_UART_SET_MARK  - Configure the transmitter to send the next
    *                                    byte as an address.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  This function sets and clears BLE_UART_CTRL_MARK bit in the Control
    *  register.
    *
    *******************************************************************************/
    void BLE_UART_SetTxAddressMode(uint8 addressMode) 
    {
        /* Mark/Space sending enable */
        if(addressMode != 0u)
        {
        #if( BLE_UART_CONTROL_REG_REMOVED == 0u )
            BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() |
                                                  BLE_UART_CTRL_MARK);
        #endif /* End BLE_UART_CONTROL_REG_REMOVED == 0u */
        }
        else
        {
        #if( BLE_UART_CONTROL_REG_REMOVED == 0u )
            BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() &
                                                  (uint8) ~BLE_UART_CTRL_MARK);
        #endif /* End BLE_UART_CONTROL_REG_REMOVED == 0u */
        }
    }

#endif  /* EndBLE_UART_TX_ENABLED */

#if(BLE_UART_HD_ENABLED)


    /*******************************************************************************
    * Function Name: BLE_UART_LoadRxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the receiver configuration in half duplex mode. After calling this
    *  function, the UART is ready to receive data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the transmitter
    *  configuration.
    *
    *******************************************************************************/
    void BLE_UART_LoadRxConfig(void) 
    {
        BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() &
                                                (uint8)~BLE_UART_CTRL_HD_SEND);
        BLE_UART_RXBITCTR_PERIOD_REG = BLE_UART_HD_RXBITCTR_INIT;

    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        /* Enable RX interrupt after set RX configuration */
        BLE_UART_SetRxInterruptMode(BLE_UART_INIT_RX_INTERRUPTS_MASK);
    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */
    }


    /*******************************************************************************
    * Function Name: BLE_UART_LoadTxConfig
    ********************************************************************************
    *
    * Summary:
    *  Loads the transmitter configuration in half duplex mode. After calling this
    *  function, the UART is ready to transmit data.
    *
    * Parameters:
    *  None.
    *
    * Return:
    *  None.
    *
    * Side Effects:
    *  Valid only in half duplex mode. You must make sure that the previous
    *  transaction is complete and it is safe to unload the receiver configuration.
    *
    *******************************************************************************/
    void BLE_UART_LoadTxConfig(void) 
    {
    #if (BLE_UART_RX_INTERRUPT_ENABLED)
        /* Disable RX interrupts before set TX configuration */
        BLE_UART_SetRxInterruptMode(0u);
    #endif /* (BLE_UART_RX_INTERRUPT_ENABLED) */

        BLE_UART_WriteControlRegister(BLE_UART_ReadControlRegister() | BLE_UART_CTRL_HD_SEND);
        BLE_UART_RXBITCTR_PERIOD_REG = BLE_UART_HD_TXBITCTR_INIT;
    }

#endif  /* BLE_UART_HD_ENABLED */


/* [] END OF FILE */
