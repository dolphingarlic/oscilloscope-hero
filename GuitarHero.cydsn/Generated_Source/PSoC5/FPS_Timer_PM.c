/*******************************************************************************
* File Name: FPS_Timer_PM.c
* Version 2.70
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "FPS_Timer.h"

static FPS_Timer_backupStruct FPS_Timer_backup;


/*******************************************************************************
* Function Name: FPS_Timer_SaveConfig
********************************************************************************
*
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
*  FPS_Timer_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void FPS_Timer_SaveConfig(void) 
{
    #if (!FPS_Timer_UsingFixedFunction)
        FPS_Timer_backup.TimerUdb = FPS_Timer_ReadCounter();
        FPS_Timer_backup.InterruptMaskValue = FPS_Timer_STATUS_MASK;
        #if (FPS_Timer_UsingHWCaptureCounter)
            FPS_Timer_backup.TimerCaptureCounter = FPS_Timer_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!FPS_Timer_UDB_CONTROL_REG_REMOVED)
            FPS_Timer_backup.TimerControlRegister = FPS_Timer_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: FPS_Timer_RestoreConfig
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
*  FPS_Timer_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void FPS_Timer_RestoreConfig(void) 
{   
    #if (!FPS_Timer_UsingFixedFunction)

        FPS_Timer_WriteCounter(FPS_Timer_backup.TimerUdb);
        FPS_Timer_STATUS_MASK =FPS_Timer_backup.InterruptMaskValue;
        #if (FPS_Timer_UsingHWCaptureCounter)
            FPS_Timer_SetCaptureCount(FPS_Timer_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!FPS_Timer_UDB_CONTROL_REG_REMOVED)
            FPS_Timer_WriteControlRegister(FPS_Timer_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: FPS_Timer_Sleep
********************************************************************************
*
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
*  FPS_Timer_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void FPS_Timer_Sleep(void) 
{
    #if(!FPS_Timer_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(FPS_Timer_CTRL_ENABLE == (FPS_Timer_CONTROL & FPS_Timer_CTRL_ENABLE))
        {
            /* Timer is enabled */
            FPS_Timer_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            FPS_Timer_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    FPS_Timer_Stop();
    FPS_Timer_SaveConfig();
}


/*******************************************************************************
* Function Name: FPS_Timer_Wakeup
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
*  FPS_Timer_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void FPS_Timer_Wakeup(void) 
{
    FPS_Timer_RestoreConfig();
    #if(!FPS_Timer_UDB_CONTROL_REG_REMOVED)
        if(FPS_Timer_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                FPS_Timer_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
