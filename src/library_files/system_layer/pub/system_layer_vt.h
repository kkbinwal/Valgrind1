/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_VT_H_
#define SYSTEM_LAYER_VT_H_

/* -- Include files --------------------------------------------------------- */
#include <system_layer.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** @name System Layer Virtual Time support */
/*@{*/

/** enable virtual time behavior
 *
 * Enabling virtual time behavior disables normal timing operation and allows injecting current time through
 * setVirtualTime function, also clients are expected to call SRTS_runCylce as needed. It's not allowed to change
 * this behavior when system is in running state.
 *
 * @param[in] aCtx
 * @return error code
 * @retval SL_OK
 * @retval SL_EDISABLED
 */
SL_Rc SL_enableVirtualTime(SRTS_ContextPtr aCtx);

/** disable virtual time behavior
 *
 * Restore normal behavior. It's not allowed to change this behavior when system is in running state.
 *
 * @param[in] aCtx
 * @return error code
 * @retval SL_OK
 * @retval SL_EDISABLED
 */
SL_Rc SL_disableVirtualTime(SRTS_ContextPtr aCtx);

/**
 * Query whether virtual time behavior is enabled
 *
 * @param[in] aCtx
 * @param[out] aVirtualTime
 * @return error code
 * @retval SL_OK
 */
SL_Rc SL_isVirtualTime(SRTS_ContextPtr aCtx, CMN_Bool *aVirtualTime);

/** inject virtual time
 *
 * Set the given time as the current time provided to the application. This operation is only allowed
 * if virtual time behavior is enabled.
 *
 * @param[in] aCtx
 * @return error code
 * @retval SL_OK
 * @retval SL_EDISABLED
 */
SL_Rc SL_setVirtualTime(SRTS_ContextPtr aCtx, SL_SystemTimerTicks aCurrentTimerTicks);

/*@}*/

#endif /* SYSTEM_LAYER_VT_H_ */
