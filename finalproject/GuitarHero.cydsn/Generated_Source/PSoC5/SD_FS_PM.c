/*******************************************************************************
* File Name: SD_FS_PM.c
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
#include "SD_FS.h"


/*******************************************************************************
* Function Name: SD_FS_SaveConfig
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
void SD_FS_SaveConfig(void) 
{
    #if(SD_FS_NUMBER_SD_CARDS == 4u)
        SD_FS_SPI0_SaveConfig();
        SD_FS_SPI1_SaveConfig();
        SD_FS_SPI2_SaveConfig();
        SD_FS_SPI3_SaveConfig();
    #elif(SD_FS_NUMBER_SD_CARDS == 3u)
        SD_FS_SPI0_SaveConfig();
        SD_FS_SPI1_SaveConfig();
        SD_FS_SPI2_SaveConfig();
    #elif(SD_FS_NUMBER_SD_CARDS == 2u)
        SD_FS_SPI0_SaveConfig();
        SD_FS_SPI1_SaveConfig();
    #else
        SD_FS_SPI0_SaveConfig();
    #endif /* (SD_FS_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FS_RestoreConfig
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
void SD_FS_RestoreConfig(void) 
{
    #if(SD_FS_NUMBER_SD_CARDS == 4u)
        SD_FS_SPI0_RestoreConfig();
        SD_FS_SPI1_RestoreConfig();
        SD_FS_SPI2_RestoreConfig();
        SD_FS_SPI3_RestoreConfig();
    #elif(SD_FS_NUMBER_SD_CARDS == 3u)
        SD_FS_SPI0_SaveConfig();
        SD_FS_SPI1_SaveConfig();
        SD_FS_SPI2_SaveConfig();
    #elif(SD_FS_NUMBER_SD_CARDS == 2u)
        SD_FS_SPI0_SaveConfig();
        SD_FS_SPI1_SaveConfig();
    #else
        SD_FS_SPI0_SaveConfig();
    #endif /* (SD_FS_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FS_Sleep
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
void SD_FS_Sleep(void) 
{
    #if(SD_FS_NUMBER_SD_CARDS == 4u)
        SD_FS_SPI0_Sleep();
        SD_FS_SPI1_Sleep();
        SD_FS_SPI2_Sleep();
        SD_FS_SPI3_Sleep();
    #elif(SD_FS_NUMBER_SD_CARDS == 3u)
        SD_FS_SPI0_Sleep();
        SD_FS_SPI1_Sleep();
        SD_FS_SPI2_Sleep();
    #elif(SD_FS_NUMBER_SD_CARDS == 2u)
        SD_FS_SPI0_Sleep();
        SD_FS_SPI1_Sleep();
    #else
        SD_FS_SPI0_Sleep();
    #endif /* (SD_FS_NUMBER_SD_CARDS == 4u) */
}


/*******************************************************************************
* Function Name: SD_FS_Wakeup
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
void SD_FS_Wakeup(void) 
{
    #if(SD_FS_NUMBER_SD_CARDS == 4u)
        SD_FS_SPI0_Wakeup();
        SD_FS_SPI1_Wakeup();
        SD_FS_SPI2_Wakeup();
        SD_FS_SPI3_Wakeup();
    #elif(SD_FS_NUMBER_SD_CARDS == 3u)
        SD_FS_SPI0_Wakeup();
        SD_FS_SPI1_Wakeup();
        SD_FS_SPI2_Wakeup();
    #elif(SD_FS_NUMBER_SD_CARDS == 2u)
        SD_FS_SPI0_Wakeup();
        SD_FS_SPI1_Wakeup();
    #else
        SD_FS_SPI0_Wakeup();
    #endif /* (SD_FS_NUMBER_SD_CARDS == 4u) */
}


/* [] END OF FILE */
