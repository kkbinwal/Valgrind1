/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DC_OLT_H_
#define DC_OLT_H_

/* -- Include files --------------------------------------------------------- */
#include <dc_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup OLT Online Test
 *
 * @brief Online Test
 *
 * Online test interface provides the ability to watch and force values of specific variables and FB pins.
 *@{*/

/**
 * Enables watching variable and FB output pin values. If enabled, safe RTS will send value updates of these values periodically using DCM_sendWatch.
 *
 * * Can only be enabled if application is already started in TEST mode.
 * * It is disabled upon starting the application
 * * If watch is enabled already, this operation will do nothing and return OK
 *
 * @param aCtx the SRTS context
 * @return error code
 */
DC_Rc DC_enableWatch(SRTS_ContextPtr aCtx);

/**
 * Disables watch functionality.
 *
 * @param aCtx the SRTS context
 * @return error code
 */
DC_Rc DC_disableWatch(SRTS_ContextPtr aCtx);

/**
 * Force a value to the specified variable or FB input pin.
 *
 * @param aCtx the SRTS context
 * @param aBlockHandle handle for the block
 * @param aPin input pin (in case of FB block)
 * @param aValueLiteral string literal representing the value to be forced
 * @return error code
 */
DC_Rc DC_force(SRTS_ContextPtr aCtx, CMN_BlockHandle aBlockHandle, CMN_PinCount aPin, char const* aValueLiteral);

/**
 * Force a value to the specified FB output pin.
 *
 * @param aCtx the SRTS context
 * @param aBlockHandle handle for the block
 * @param aPin output pin of the function block
 * @param aValueLiteral string literal representing the value to be forced
 * @return error code
 */
DC_Rc DC_forceOutput(SRTS_ContextPtr aCtx, CMN_BlockHandle aBlockHandle, CMN_PinCount aPin, char const* aValueLiteral);

/**
 * Read a value from the specified FB output pin.
 *
 * @param aCtx the SRTS context
 * @param aBlockHandle handle for the block
 * @param aPin output pin of the function block
 * @param aValueLiteral string literal representing the read value
 * @return error code
 */
DC_Rc DC_readOutput(SRTS_ContextPtr aCtx, CMN_BlockHandle aBlockHandle, CMN_PinCount aPin, char* aValueLiteral);

/*@}*//* Online Test */

/*@}*//* DCA Data Control API */

#endif /* DC_OLT_H_ */
