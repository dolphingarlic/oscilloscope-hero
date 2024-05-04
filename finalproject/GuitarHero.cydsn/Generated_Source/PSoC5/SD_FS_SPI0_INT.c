/*******************************************************************************
* File Name: SD_FS_SPI0_INT.c
* Version 2.40
*
* Description:
*  This file provides all Interrupt Service Routine (ISR) for the SPI Master
*  component.
*
* Note:
*  None.
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "SD_FS_SPI0_PVT.h"

/* User code required at start of ISR */
/* `#START SD_FS_SPI0_ISR_START_DEF` */

/* `#END` */


/*******************************************************************************
* Function Name: SD_FS_SPI0_TX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for TX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SD_FS_SPI0_txBufferWrite - used for the account of the bytes which
*  have been written down in the TX software buffer.
*  SD_FS_SPI0_txBufferRead - used for the account of the bytes which
*  have been read from the TX software buffer, modified when exist data to
*  sending and FIFO Not Full.
*  SD_FS_SPI0_txBuffer[SD_FS_SPI0_TX_BUFFER_SIZE] - used to store
*  data to sending.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SD_FS_SPI0_TX_ISR)
{
    #if(SD_FS_SPI0_TX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
    #endif /* (SD_FS_SPI0_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START SD_FS_SPI0_TX_ISR_START` */

    /* `#END` */

    #if(SD_FS_SPI0_TX_SOFTWARE_BUF_ENABLED)
        /* Check if TX data buffer is not empty and there is space in TX FIFO */
        while(SD_FS_SPI0_txBufferRead != SD_FS_SPI0_txBufferWrite)
        {
            tmpStatus = SD_FS_SPI0_GET_STATUS_TX(SD_FS_SPI0_swStatusTx);
            SD_FS_SPI0_swStatusTx = tmpStatus;

            if(0u != (SD_FS_SPI0_swStatusTx & SD_FS_SPI0_STS_TX_FIFO_NOT_FULL))
            {
                if(0u == SD_FS_SPI0_txBufferFull)
                {
                   SD_FS_SPI0_txBufferRead++;

                    if(SD_FS_SPI0_txBufferRead >= SD_FS_SPI0_TX_BUFFER_SIZE)
                    {
                        SD_FS_SPI0_txBufferRead = 0u;
                    }
                }
                else
                {
                    SD_FS_SPI0_txBufferFull = 0u;
                }

                /* Move data from the Buffer to the FIFO */
                CY_SET_REG8(SD_FS_SPI0_TXDATA_PTR,
                    SD_FS_SPI0_txBuffer[SD_FS_SPI0_txBufferRead]);
            }
            else
            {
                break;
            }
        }

        if(SD_FS_SPI0_txBufferRead == SD_FS_SPI0_txBufferWrite)
        {
            /* TX Buffer is EMPTY: disable interrupt on TX NOT FULL */
            SD_FS_SPI0_TX_STATUS_MASK_REG &= ((uint8) ~SD_FS_SPI0_STS_TX_FIFO_NOT_FULL);
        }

    #endif /* (SD_FS_SPI0_TX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SD_FS_SPI0_TX_ISR_END` */

    /* `#END` */
}


/*******************************************************************************
* Function Name: SD_FS_SPI0_RX_ISR
********************************************************************************
*
* Summary:
*  Interrupt Service Routine for RX portion of the SPI Master.
*
* Parameters:
*  None.
*
* Return:
*  None.
*
* Global variables:
*  SD_FS_SPI0_rxBufferWrite - used for the account of the bytes which
*  have been written down in the RX software buffer modified when FIFO contains
*  new data.
*  SD_FS_SPI0_rxBufferRead - used for the account of the bytes which
*  have been read from the RX software buffer, modified when overflow occurred.
*  SD_FS_SPI0_rxBuffer[SD_FS_SPI0_RX_BUFFER_SIZE] - used to store
*  received data, modified when FIFO contains new data.
*  All described above Global variables are used when Software Buffer is used.
*
*******************************************************************************/
CY_ISR(SD_FS_SPI0_RX_ISR)
{
    #if(SD_FS_SPI0_RX_SOFTWARE_BUF_ENABLED)
        uint8 tmpStatus;
        uint8 rxData;
    #endif /* (SD_FS_SPI0_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at start of ISR */
    /* `#START SD_FS_SPI0_RX_ISR_START` */

    /* `#END` */

    #if(SD_FS_SPI0_RX_SOFTWARE_BUF_ENABLED)

        tmpStatus = SD_FS_SPI0_GET_STATUS_RX(SD_FS_SPI0_swStatusRx);
        SD_FS_SPI0_swStatusRx = tmpStatus;

        /* Check if RX data FIFO has some data to be moved into the RX Buffer */
        while(0u != (SD_FS_SPI0_swStatusRx & SD_FS_SPI0_STS_RX_FIFO_NOT_EMPTY))
        {
            rxData = CY_GET_REG8(SD_FS_SPI0_RXDATA_PTR);

            /* Set next pointer. */
            SD_FS_SPI0_rxBufferWrite++;
            if(SD_FS_SPI0_rxBufferWrite >= SD_FS_SPI0_RX_BUFFER_SIZE)
            {
                SD_FS_SPI0_rxBufferWrite = 0u;
            }

            if(SD_FS_SPI0_rxBufferWrite == SD_FS_SPI0_rxBufferRead)
            {
                SD_FS_SPI0_rxBufferRead++;
                if(SD_FS_SPI0_rxBufferRead >= SD_FS_SPI0_RX_BUFFER_SIZE)
                {
                    SD_FS_SPI0_rxBufferRead = 0u;
                }

                SD_FS_SPI0_rxBufferFull = 1u;
            }

            /* Move data from the FIFO to the Buffer */
            SD_FS_SPI0_rxBuffer[SD_FS_SPI0_rxBufferWrite] = rxData;

            tmpStatus = SD_FS_SPI0_GET_STATUS_RX(SD_FS_SPI0_swStatusRx);
            SD_FS_SPI0_swStatusRx = tmpStatus;
        }

    #endif /* (SD_FS_SPI0_RX_SOFTWARE_BUF_ENABLED) */

    /* User code required at end of ISR (Optional) */
    /* `#START SD_FS_SPI0_RX_ISR_END` */

    /* `#END` */
}

/* [] END OF FILE */
