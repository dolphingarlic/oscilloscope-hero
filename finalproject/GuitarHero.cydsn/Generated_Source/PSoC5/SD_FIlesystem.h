/*******************************************************************************
* File Name: SD_FIlesystem.h
* Version 1.20
*
* Description:
*  This file contains the function prototypes and constants used in the emFile
*  component.
*
* Note:
*
********************************************************************************
* Copyright 2011-2012, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_EM_FILE_SD_FIlesystem_H)
#define CY_EM_FILE_SD_FIlesystem_H

#include <cytypes.h>
#include "cyfitter.h"
#include "MMC_X_HW.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Number of configured SD cards */
#define SD_FIlesystem_NUMBER_SD_CARDS    (1u)

/* Max frequency in KHz */
#define SD_FIlesystem_MAX_SPI_FREQ       (4000u)

/* Enable Write Protect */
#define SD_FIlesystem_WP0_EN             (0u)
#define SD_FIlesystem_WP1_EN             (0u)
#define SD_FIlesystem_WP2_EN             (0u)
#define SD_FIlesystem_WP3_EN             (0u)


/***************************************
*        Function Prototypes
***************************************/

void SD_FIlesystem_SaveConfig(void) ;
void SD_FIlesystem_RestoreConfig(void) ;
void SD_FIlesystem_Sleep(void) ;
void SD_FIlesystem_Wakeup(void) ;


/***************************************
*           API Constants
***************************************/

#define SD_FIlesystem_RET_SUCCCESS       (0x01u)
#define SD_FIlesystem_RET_FAIL           (0x00u)

#endif /* CY_EM_FILE_SD_FIlesystem_H */


/* [] END OF FILE */
