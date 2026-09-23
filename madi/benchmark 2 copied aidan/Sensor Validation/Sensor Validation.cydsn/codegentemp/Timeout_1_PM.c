/*******************************************************************************
* File Name: Timeout_1_PM.c
* Version 2.80
*
*  Description:
*     This file provides the power management source code to API for the
*     Timer.
*
*   Note:
*     None
*
*******************************************************************************
* Copyright 2008-2017, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
********************************************************************************/

#include "Timeout_1.h"

static Timeout_1_backupStruct Timeout_1_backup;


/*******************************************************************************
* Function Name: Timeout_1_SaveConfig
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
*  Timeout_1_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timeout_1_SaveConfig(void) 
{
    #if (!Timeout_1_UsingFixedFunction)
        Timeout_1_backup.TimerUdb = Timeout_1_ReadCounter();
        Timeout_1_backup.InterruptMaskValue = Timeout_1_STATUS_MASK;
        #if (Timeout_1_UsingHWCaptureCounter)
            Timeout_1_backup.TimerCaptureCounter = Timeout_1_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timeout_1_UDB_CONTROL_REG_REMOVED)
            Timeout_1_backup.TimerControlRegister = Timeout_1_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timeout_1_RestoreConfig
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
*  Timeout_1_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_1_RestoreConfig(void) 
{   
    #if (!Timeout_1_UsingFixedFunction)

        Timeout_1_WriteCounter(Timeout_1_backup.TimerUdb);
        Timeout_1_STATUS_MASK =Timeout_1_backup.InterruptMaskValue;
        #if (Timeout_1_UsingHWCaptureCounter)
            Timeout_1_SetCaptureCount(Timeout_1_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timeout_1_UDB_CONTROL_REG_REMOVED)
            Timeout_1_WriteControlRegister(Timeout_1_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timeout_1_Sleep
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
*  Timeout_1_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timeout_1_Sleep(void) 
{
    #if(!Timeout_1_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timeout_1_CTRL_ENABLE == (Timeout_1_CONTROL & Timeout_1_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timeout_1_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timeout_1_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timeout_1_Stop();
    Timeout_1_SaveConfig();
}


/*******************************************************************************
* Function Name: Timeout_1_Wakeup
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
*  Timeout_1_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_1_Wakeup(void) 
{
    Timeout_1_RestoreConfig();
    #if(!Timeout_1_UDB_CONTROL_REG_REMOVED)
        if(Timeout_1_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timeout_1_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
