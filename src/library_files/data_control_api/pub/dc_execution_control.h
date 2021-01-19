/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCEXECUTIONCONTROL_H_
#define DCEXECUTIONCONTROL_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>
#include <dc_types.h>
#include <system_layer_types.h>
#include <common_rc.h>
#include <dc_rc.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup EC Execution Control
 *
 * @brief Execution Control
 *
 * Methods for controlling the system execution state, application state and
 * HW inputs/output decoupling.
 *
 * @imageSize{state_diagram.png,height:400px;width:808px;}
 * @image html state_diagram.png
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Execute the "Stop Test" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execStopTest(SRTS_ContextPtr aContext);

/**
 * Execute the "Stop Safe" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execStopSafe(SRTS_ContextPtr aContext);

/**
 * Execute the "Run Test" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execRunTest(SRTS_ContextPtr aContext);

/**
 * Execute the "Run Safe" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execRunSafe(SRTS_ContextPtr aContext);

/**
 * Execute the "RunSafe to RunTest" transition.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execRunSafeToRunTest(SRTS_ContextPtr aContext);

/**
 * Execute the "Hold" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execHold(SRTS_ContextPtr aContext);

/**
 * Execute the "Resume" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execResume(SRTS_ContextPtr aContext);

/**
 * Execute the "Init" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execInit(SRTS_ContextPtr aContext);

/**
 * Execute the "SingleCycle" action.
 *
 * @req{SAFE-3470}
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execSingleCycle(SRTS_ContextPtr aContext);

/**
 * Execute the "SingleCommandBlock" action.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_execSingleCommandBlock(SRTS_ContextPtr aContext);

/**
 * Get the handle of the block to be executed by the next "SingleCommandBlock" action.
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aBlockHandle block handle of the next block to be executed.
 * @return Greater than or equal to 0 on success.
 *
 */
DC_Rc DC_getNextCommandBlockHandle(SRTS_ContextPtr aContext, CMN_BlockHandle *aBlockHandle);

/**
 * Retrieve the machine's execution state.
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aExecutionState Execution state.
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_getExecutionState(SRTS_ContextPtr aContext, CMN_ExecutionState* aExecutionState);

/**
 * Verify the application.
 *
 * The interpreter is initialized.
 *
 * @param aContext pointer the SRTS context instance
 * @param aVerifContext pointer the verification context
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_verify(SRTS_ContextPtr aContext, DC_VerificationInProgressContext const* aVerifContext);

/**
 * return whether the application state is DC_ApplicationStateVerified;
 *
 * @param aContext pointer the SRTS context instance
 * @return true if the application state is DC_ApplicationStateVerified
 *         false in all other cases (including in case of error)
 */
bool DC_isVerified(SRTS_ContextPtr const aContext);

/**
 * Switch application state to Edit Mode, i.e. DC_ApplicationStateNotVerified
 *
 * @param aContext pointer the SRTS context instance
 */
DC_Rc DC_edit(SRTS_ContextPtr aContext);

/**
 * Release the application.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_release(SRTS_ContextPtr aContext);

/**
 * return whether the application state is DC_ApplicationStateReleased;
 *
 * @param aContext pointer the SRTS context instance
 * @return true if the application state is DC_ApplicationStateReleased
 *         false in all other cases (including in case of error)
 */
bool DC_isReleased(SRTS_ContextPtr aContext);

/**
 * Retrieve the application state.
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aApplicationState Application state.
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_getApplicationState(SRTS_ContextPtr aContext, DC_ApplicationState* aApplicationState);

/**
 * Connect hardware IOs.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_connectIo(SRTS_ContextPtr aContext);

/**
 * Disconnect hardware IOs.
 *
 * @param aContext pointer the SRTS context instance
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_disconnectIo(SRTS_ContextPtr aContext);

/**
 * Retrieve IO state.
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aIoState Resulting IO state
 * @return error code
 * @retval SSH_OK
 * @retval #CMN_ENULLPTR
 * @retval #CMN_EINVALCTX
 */
DC_Rc DC_getIoState(SRTS_ContextPtr aContext, DC_IoState* aIoState);

/**
 * Retrieve the watch mode.
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aWatchMode Resulting watch mode
 * @return Greater than or equal to 0 on success.
 */
DC_Rc DC_getWatchMode(SRTS_ContextPtr aContext, DC_WatchMode* aWatchMode);

/*@}*//* Execution Control */

/*@}*//* DCA Data Control API */

#endif
