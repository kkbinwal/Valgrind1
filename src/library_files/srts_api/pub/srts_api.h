/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SRTSAPI_H_
#define SRTSAPI_H_

/* -- Include files --------------------------------------------------------- */

#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SRTSAPI sRTS API
 *
 * Main interface for running logi.SAFE on a HW-Platform. Must be called by the HW-Platform's base software to integrate logi.SAFE.
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Return code for sRTS API functions.
 * Return codes >= 0 are success codes, codes < 0 indicate that an error has occurred.
 */
typedef CMN_Rc SRTS_Rc;

/* -- Prototypes ------------------------------------------------------------ */
/**
 * Initializes the sRTS.
 *
 * This function is the first function that will be executed right after booting. It initializes the whole module. The function stops ongoing
 * operations and puts the module unconditionally into the initialization state. During execution, the module checks the integrity of the saved
 * application, so that it will immediately be put in a valid execution state ('Safe-Run','Test-Run','Stopped' or 'Error'). Depending on the state,
 * either the IEC program will be executed or the Shell waits for further calls. If this function is called and the module is recognizably not in a
 * cold boot or shutdown state, but the rest of the integrity check was successful, an EINTR will be returned after the initialization.
 *
 * @param aCtx context
 * @return error code
 * @retval EBADFD Loaded application is not in an integrative state.
 * @retval EINTR The module is not in a shutdown or cold boot state.
 */
SRTS_Rc SRTS_initialize(SRTS_ContextPtr aCtx);

/**
 * Runs a cycle.
 *
 * This function is called cyclically by the scheduler. If the module is in a RUN state, a run-cycle will be executed internally. Otherwise, this
 * function will be ignored and EAGAIN ('Try Again') will be returned.
 *
 * @param aCtx context
 * @return error code
 * @retval EAGAIN Application is not in a RUN state.
 */
SRTS_Rc SRTS_runCycle(SRTS_ContextPtr aCtx);

/**
 * Shutdown sRTS.
 *
 * Shuts down the module and releases all resources.
 *
 * @param aCtx context
 * @return error code
 */
SRTS_Rc SRTS_shutdown(SRTS_ContextPtr aCtx);

/**
 * Move the system into fail-safe mode
 *
 * This call indicates that an unrecoverable, fatal error has been detected.
 * @param aCtx context
 * @return error code
 */
SRTS_Rc SRTS_failsafe(SRTS_ContextPtr aCtx);

/*@}*/

#endif
