/*******************************************************************************
* File Name: Audio_DAC_VDAC8_PM.c  
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

#include "Audio_DAC_VDAC8.h"

static Audio_DAC_VDAC8_backupStruct Audio_DAC_VDAC8_backup;


/*******************************************************************************
* Function Name: Audio_DAC_VDAC8_SaveConfig
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
void Audio_DAC_VDAC8_SaveConfig(void) 
{
    if (!((Audio_DAC_VDAC8_CR1 & Audio_DAC_VDAC8_SRC_MASK) == Audio_DAC_VDAC8_SRC_UDB))
    {
        Audio_DAC_VDAC8_backup.data_value = Audio_DAC_VDAC8_Data;
    }
}


/*******************************************************************************
* Function Name: Audio_DAC_VDAC8_RestoreConfig
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
void Audio_DAC_VDAC8_RestoreConfig(void) 
{
    if (!((Audio_DAC_VDAC8_CR1 & Audio_DAC_VDAC8_SRC_MASK) == Audio_DAC_VDAC8_SRC_UDB))
    {
        if((Audio_DAC_VDAC8_Strobe & Audio_DAC_VDAC8_STRB_MASK) == Audio_DAC_VDAC8_STRB_EN)
        {
            Audio_DAC_VDAC8_Strobe &= (uint8)(~Audio_DAC_VDAC8_STRB_MASK);
            Audio_DAC_VDAC8_Data = Audio_DAC_VDAC8_backup.data_value;
            Audio_DAC_VDAC8_Strobe |= Audio_DAC_VDAC8_STRB_EN;
        }
        else
        {
            Audio_DAC_VDAC8_Data = Audio_DAC_VDAC8_backup.data_value;
        }
    }
}


/*******************************************************************************
* Function Name: Audio_DAC_VDAC8_Sleep
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
*  Audio_DAC_VDAC8_backup.enableState:  Is modified depending on the enable 
*  state  of the block before entering sleep mode.
*
*******************************************************************************/
void Audio_DAC_VDAC8_Sleep(void) 
{
    /* Save VDAC8's enable state */    
    if(Audio_DAC_VDAC8_ACT_PWR_EN == (Audio_DAC_VDAC8_PWRMGR & Audio_DAC_VDAC8_ACT_PWR_EN))
    {
        /* VDAC8 is enabled */
        Audio_DAC_VDAC8_backup.enableState = 1u;
    }
    else
    {
        /* VDAC8 is disabled */
        Audio_DAC_VDAC8_backup.enableState = 0u;
    }
    
    Audio_DAC_VDAC8_Stop();
    Audio_DAC_VDAC8_SaveConfig();
}


/*******************************************************************************
* Function Name: Audio_DAC_VDAC8_Wakeup
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
*  Audio_DAC_VDAC8_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Audio_DAC_VDAC8_Wakeup(void) 
{
    Audio_DAC_VDAC8_RestoreConfig();
    
    if(Audio_DAC_VDAC8_backup.enableState == 1u)
    {
        /* Enable VDAC8's operation */
        Audio_DAC_VDAC8_Enable();

        /* Restore the data register */
        Audio_DAC_VDAC8_SetValue(Audio_DAC_VDAC8_Data);
    } /* Do nothing if VDAC8 was disabled before */    
}


/* [] END OF FILE */
