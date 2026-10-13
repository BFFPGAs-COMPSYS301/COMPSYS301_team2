/*******************************************************************************
* File Name: Timeout_3_PM.c
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

#include "Timeout_3.h"

static Timeout_3_backupStruct Timeout_3_backup;


/*******************************************************************************
* Function Name: Timeout_3_SaveConfig
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
*  Timeout_3_backup:  Variables of this global structure are modified to
*  store the values of non retention configuration registers when Sleep() API is
*  called.
*
*******************************************************************************/
void Timeout_3_SaveConfig(void) 
{
    #if (!Timeout_3_UsingFixedFunction)
        Timeout_3_backup.TimerUdb = Timeout_3_ReadCounter();
        Timeout_3_backup.InterruptMaskValue = Timeout_3_STATUS_MASK;
        #if (Timeout_3_UsingHWCaptureCounter)
            Timeout_3_backup.TimerCaptureCounter = Timeout_3_ReadCaptureCount();
        #endif /* Back Up capture counter register  */

        #if(!Timeout_3_UDB_CONTROL_REG_REMOVED)
            Timeout_3_backup.TimerControlRegister = Timeout_3_ReadControlRegister();
        #endif /* Backup the enable state of the Timer component */
    #endif /* Backup non retention registers in UDB implementation. All fixed function registers are retention */
}


/*******************************************************************************
* Function Name: Timeout_3_RestoreConfig
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
*  Timeout_3_backup:  Variables of this global structure are used to
*  restore the values of non retention registers on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_3_RestoreConfig(void) 
{   
    #if (!Timeout_3_UsingFixedFunction)

        Timeout_3_WriteCounter(Timeout_3_backup.TimerUdb);
        Timeout_3_STATUS_MASK =Timeout_3_backup.InterruptMaskValue;
        #if (Timeout_3_UsingHWCaptureCounter)
            Timeout_3_SetCaptureCount(Timeout_3_backup.TimerCaptureCounter);
        #endif /* Restore Capture counter register*/

        #if(!Timeout_3_UDB_CONTROL_REG_REMOVED)
            Timeout_3_WriteControlRegister(Timeout_3_backup.TimerControlRegister);
        #endif /* Restore the enable state of the Timer component */
    #endif /* Restore non retention registers in the UDB implementation only */
}


/*******************************************************************************
* Function Name: Timeout_3_Sleep
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
*  Timeout_3_backup.TimerEnableState:  Is modified depending on the
*  enable state of the block before entering sleep mode.
*
*******************************************************************************/
void Timeout_3_Sleep(void) 
{
    #if(!Timeout_3_UDB_CONTROL_REG_REMOVED)
        /* Save Counter's enable state */
        if(Timeout_3_CTRL_ENABLE == (Timeout_3_CONTROL & Timeout_3_CTRL_ENABLE))
        {
            /* Timer is enabled */
            Timeout_3_backup.TimerEnableState = 1u;
        }
        else
        {
            /* Timer is disabled */
            Timeout_3_backup.TimerEnableState = 0u;
        }
    #endif /* Back up enable state from the Timer control register */
    Timeout_3_Stop();
    Timeout_3_SaveConfig();
}


/*******************************************************************************
* Function Name: Timeout_3_Wakeup
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
*  Timeout_3_backup.enableState:  Is used to restore the enable state of
*  block on wakeup from sleep mode.
*
*******************************************************************************/
void Timeout_3_Wakeup(void) 
{
    Timeout_3_RestoreConfig();
    #if(!Timeout_3_UDB_CONTROL_REG_REMOVED)
        if(Timeout_3_backup.TimerEnableState == 1u)
        {     /* Enable Timer's operation */
                Timeout_3_Enable();
        } /* Do nothing if Timer was disabled before */
    #endif /* Remove this code section if Control register is removed */
}


/* [] END OF FILE */
