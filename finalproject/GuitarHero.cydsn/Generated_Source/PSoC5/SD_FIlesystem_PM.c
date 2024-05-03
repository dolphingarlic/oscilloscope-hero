/*******************************************************************************
* File Name: SD_FIlesystem_PM.c
* Version 1.20
*
* Description:
*  This file provides the API source code for Power Management of the emFile
*  component.
*
* Note:
*
*******************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include <project.h>
#include "SD_FIlesystem.h"


/*******************************************************************************
* Function Name: SD_FIlesystem_SaveConfig
********************************************************************************
*
* Summary:
*  Saves SPI Masters configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void SD_FIlesystem_SaveConfig(void) 
{
    #if(SD_FIlesystem_NUMBER_SD_CARDS == 4u)
        SD_FIlesystem_SPI0_SaveConfig();
        SD_FIlesystem_SPI1_SaveConfig();
        SD_FIlesystem_SPI2_SaveConfig();
        SD_FIlesystem_SPI3_SaveConfig();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 3u)
        SD_FIlesystem_SPI0_SaveConfig();
        SD_FIlesystem_SPI1_SaveConfig();
        SD_FIlesystem_SPI2_SaveConfig();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 2u)
        SD_FIlesystem_SPI0_SaveConfig();
        SD_FIlesystem_SPI1_SaveConfig();
    #else
        SD_FIlesystem_SPI0_SaveConfig();
    #endif /* (SD_FIlesystem_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FIlesystem_RestoreConfig
********************************************************************************
*
* Summary:
*  Restores SPI Masters configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  If this API is called without first calling SaveConfig then in the following
*  registers will be default values from Customizer:
*
*******************************************************************************/
void SD_FIlesystem_RestoreConfig(void) 
{
    #if(SD_FIlesystem_NUMBER_SD_CARDS == 4u)
        SD_FIlesystem_SPI0_RestoreConfig();
        SD_FIlesystem_SPI1_RestoreConfig();
        SD_FIlesystem_SPI2_RestoreConfig();
        SD_FIlesystem_SPI3_RestoreConfig();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 3u)
        SD_FIlesystem_SPI0_SaveConfig();
        SD_FIlesystem_SPI1_SaveConfig();
        SD_FIlesystem_SPI2_SaveConfig();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 2u)
        SD_FIlesystem_SPI0_SaveConfig();
        SD_FIlesystem_SPI1_SaveConfig();
    #else
        SD_FIlesystem_SPI0_SaveConfig();
    #endif /* (SD_FIlesystem_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FIlesystem_Sleep
********************************************************************************
*
* Summary:
*  Prepare emFile to go to sleep.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void SD_FIlesystem_Sleep(void) 
{
    #if(SD_FIlesystem_NUMBER_SD_CARDS == 4u)
        SD_FIlesystem_SPI0_Sleep();
        SD_FIlesystem_SPI1_Sleep();
        SD_FIlesystem_SPI2_Sleep();
        SD_FIlesystem_SPI3_Sleep();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 3u)
        SD_FIlesystem_SPI0_Sleep();
        SD_FIlesystem_SPI1_Sleep();
        SD_FIlesystem_SPI2_Sleep();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 2u)
        SD_FIlesystem_SPI0_Sleep();
        SD_FIlesystem_SPI1_Sleep();
    #else
        SD_FIlesystem_SPI0_Sleep();
    #endif /* (SD_FIlesystem_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FIlesystem_Wakeup
********************************************************************************
*
* Summary:
*  Prepare SPIM Components to wake up.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Reentrant:
*  No
*
*******************************************************************************/
void SD_FIlesystem_Wakeup(void) 
{
    #if(SD_FIlesystem_NUMBER_SD_CARDS == 4u)
        SD_FIlesystem_SPI0_Wakeup();
        SD_FIlesystem_SPI1_Wakeup();
        SD_FIlesystem_SPI2_Wakeup();
        SD_FIlesystem_SPI3_Wakeup();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 3u)
        SD_FIlesystem_SPI0_Wakeup();
        SD_FIlesystem_SPI1_Wakeup();
        SD_FIlesystem_SPI2_Wakeup();
    #elif(SD_FIlesystem_NUMBER_SD_CARDS == 2u)
        SD_FIlesystem_SPI0_Wakeup();
        SD_FIlesystem_SPI1_Wakeup();
    #else
        SD_FIlesystem_SPI0_Wakeup();
    #endif /* (SD_FIlesystem_NUMBER_SD_CARDS == 4u) */
}


/* [] END OF FILE */
