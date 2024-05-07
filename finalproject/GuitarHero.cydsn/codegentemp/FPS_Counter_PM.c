/*******************************************************************************
* File Name: FPS_Counter_PM.c  
* Version 3.0
*
*  Description:
*    This file provides the power management source code to API for the
*    Counter.  
*
*   Note:
*     None
*
********************************************************************************
* Copyright 2008-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "FPS_Counter.h"

static FPS_Counter_backupStruct FPS_Counter_backup;


/*******************************************************************************
* Function Name: FPS_Counter_SaveConfig
********************************************************************************
* Summary:
*     Save the current user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FPS_Counter_backup:  Variables of this global structure are modified to 
*  store the values of non retention configuration registers when Sleep() API is 
*  called.
*
*******************************************************************************/
void FPS_Counter_SaveConfig(void) 
{
    #if (!FPS_Counter_UsingFixedFunction)

        FPS_Counter_backup.CounterUdb = FPS_Counter_ReadCounter();

        #if(!FPS_Counter_ControlRegRemoved)
            FPS_Counter_backup.CounterControlRegister = FPS_Counter_ReadControlRegister();
        #endif /* (!FPS_Counter_ControlRegRemoved) */

    #endif /* (!FPS_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FPS_Counter_RestoreConfig
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
* Global variables:
*  FPS_Counter_backup:  Variables of this global structure are used to 
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FPS_Counter_RestoreConfig(void) 
{      
    #if (!FPS_Counter_UsingFixedFunction)

       FPS_Counter_WriteCounter(FPS_Counter_backup.CounterUdb);

        #if(!FPS_Counter_ControlRegRemoved)
            FPS_Counter_WriteControlRegister(FPS_Counter_backup.CounterControlRegister);
        #endif /* (!FPS_Counter_ControlRegRemoved) */

    #endif /* (!FPS_Counter_UsingFixedFunction) */
}


/*******************************************************************************
* Function Name: FPS_Counter_Sleep
********************************************************************************
* Summary:
*     Stop and Save the user configuration
*
* Parameters:  
*  void
*
* Return: 
*  void
*
* Global variables:
*  FPS_Counter_backup.enableState:  Is modified depending on the enable 
*  state of the block before entering sleep mode.
*
*******************************************************************************/
void FPS_Counter_Sleep(void) 
{
    #if(!FPS_Counter_ControlRegRemoved)
        /* Save Counter's enable state */
        if(FPS_Counter_CTRL_ENABLE == (FPS_Counter_CONTROL & FPS_Counter_CTRL_ENABLE))
        {
            /* Counter is enabled */
            FPS_Counter_backup.CounterEnableState = 1u;
        }
        else
        {
            /* Counter is disabled */
            FPS_Counter_backup.CounterEnableState = 0u;
        }
    #else
        FPS_Counter_backup.CounterEnableState = 1u;
        if(FPS_Counter_backup.CounterEnableState != 0u)
        {
            FPS_Counter_backup.CounterEnableState = 0u;
        }
    #endif /* (!FPS_Counter_ControlRegRemoved) */
    
    FPS_Counter_Stop();
    FPS_Counter_SaveConfig();
}


/*******************************************************************************
* Function Name: FPS_Counter_Wakeup
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
*  FPS_Counter_backup.enableState:  Is used to restore the enable state of 
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FPS_Counter_Wakeup(void) 
{
    FPS_Counter_RestoreConfig();
    #if(!FPS_Counter_ControlRegRemoved)
        if(FPS_Counter_backup.CounterEnableState == 1u)
        {
            /* Enable Counter's operation */
            FPS_Counter_Enable();
        } /* Do nothing if Counter was disabled before */    
    #endif /* (!FPS_Counter_ControlRegRemoved) */
    
}


/* [] END OF FILE */
