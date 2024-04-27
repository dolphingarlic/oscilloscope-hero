/*******************************************************************************
* File Name: y_DAC_PM.c  
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

#include "y_DAC.h"

static y_DAC_backupStruct y_DAC_backup;


/*******************************************************************************
* Function Name: y_DAC_SaveConfig
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
void y_DAC_SaveConfig(void) 
{
    if (!((y_DAC_CR1 & y_DAC_SRC_MASK) == y_DAC_SRC_UDB))
    {
        y_DAC_backup.data_value = y_DAC_Data;
    }
}


/*******************************************************************************
* Function Name: y_DAC_RestoreConfig
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
void y_DAC_RestoreConfig(void) 
{
    if (!((y_DAC_CR1 & y_DAC_SRC_MASK) == y_DAC_SRC_UDB))
    {
        if((y_DAC_Strobe & y_DAC_STRB_MASK) == y_DAC_STRB_EN)
        {
            y_DAC_Strobe &= (uint8)(~y_DAC_STRB_MASK);
            y_DAC_Data = y_DAC_backup.data_value;
            y_DAC_Strobe |= y_DAC_STRB_EN;
        }
        else
        {
            y_DAC_Data = y_DAC_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: y_DAC_Sleep
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
*  y_DAC_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void y_DAC_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(y_DAC_ACT_PWR_EN == (y_DAC_PWRMGR & y_DAC_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        y_DAC_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        y_DAC_backup.enableState = 0u;
    }
    
    y_DAC_Stop();
    y_DAC_SaveConfig();
}


/*******************************************************************************
* Function Name: y_DAC_Wakeup
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
*  y_DAC_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void y_DAC_Wakeup(void) 
{
    y_DAC_RestoreConfig();
    
    if(y_DAC_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        y_DAC_Enable();

        /* Restore the data register */
        y_DAC_SetValue(y_DAC_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
