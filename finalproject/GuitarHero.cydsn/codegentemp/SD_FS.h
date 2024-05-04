/*******************************************************************************
* File Name: SD_FS.h
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

#if !defined(CY_EM_FILE_SD_FS_H)
#define CY_EM_FILE_SD_FS_H

#include <cytypes.h>
#include "cyfitter.h"
#include "MMC_X_HW.h"


/***************************************
*   Conditional Compilation Parameters
***************************************/

/* Number of configured SD cards */
#define SD_FS_NUMBER_SD_CARDS    (1u)

/* Max frequency in KHz */
#define SD_FS_MAX_SPI_FREQ       (12000u)

/* Enable Write Protect */
#define SD_FS_WP0_EN             (0u)
#define SD_FS_WP1_EN             (0u)
#define SD_FS_WP2_EN             (0u)
#define SD_FS_WP3_EN             (0u)


/***************************************
*        Function Prototypes
***************************************/

void SD_FS_SaveConfig(void) ;
void SD_FS_RestoreConfig(void) ;
void SD_FS_Sleep(void) ;
void SD_FS_Wakeup(void) ;


/***************************************
*           API Constants
***************************************/

#define SD_FS_RET_SUCCCESS       (0x01u)
#define SD_FS_RET_FAIL           (0x00u)

#endif /* CY_EM_FILE_SD_FS_H */


/* [] END OF FILE */
