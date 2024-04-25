/*******************************************************************************
* File Name: x_DAC_PM.c  
* Version 1.90
*
* Description:
*  This file provides the power management source code to API for the
*  VDAC8.  
*
* Note:
*  None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "x_DAC.h"

static x_DAC_backupStruct x_DAC_backup;


/*******************************************************************************
* Function Name: x_DAC_SaveConfig
********************************************************************************
* Summary:
*  Save the current user configuration
*
* Parameters:  
*  void  
*
* Return: 
*  void
*
*******************************************************************************/
void x_DAC_SaveConfig(void) 
{
    if (!((x_DAC_CR1 & x_DAC_SRC_MASK) == x_DAC_SRC_UDB))
    {
        x_DAC_backup.data_value = x_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: x_DAC_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores the current user configuration.
*
* Parameters:  
*  void
*
* Return: 
*  void
*
*******************************************************************************/
void x_DAC_RestoreConfig(void) 
{
    if (!((x_DAC_CR1 & x_DAC_SRC_MASK) == x_DAC_SRC_UDB))
    {
        if((x_DAC_Strobe & x_DAC_STRB_MASK) == x_DAC_STRB_EN)
        {
            x_DAC_Strobe &= (uint8)(~x_DAC_STRB_MASK);
            x_DAC_Data = x_DAC_backup.data_value;
            x_DAC_Strobe |= x_DAC_STRB_EN;
        }
        else
        {
            x_DAC_Data = x_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: x_DAC_Sleep
********************************************************************************
* Summary:
*  Stop and Save the user configuration
*
* Parameters:  
*  void:  
*
* Return: 
*  void
*
* Global variables:
*  x_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void x_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(x_DAC_ACT_PWR_EN == (x_DAC_PWRMGR & x_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        x_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        x_DAC_backup.enableState = 0u;
    }
    
    x_DAC_Stop();
    x_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: x_DAC_Wakeup
********************************************************************************
*
* Summary:
*  Restores and enables the user configuration
*  
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  x_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void x_DAC_Wakeup(void) 
{
    x_DAC_RestoreConfig();
    
    if(x_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        x_DAC_Enable();

        /* Restore the data register */
        x_DAC_SetValue(x_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
