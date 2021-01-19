/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCERRORLOG_H_
#define DCERRORLOG_H_

/* -- Include files --------------------------------------------------------- */
#include <dc_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup EL Error Log
 *
 * @brief Error Log
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Retrieves error log entries.
 *
 * Output:
 *
 * String buffer is filled with the relevant information.
 *
 * Description:
 * - [...] The sRTS manages the error log.
 * - There must also be a set () and a clear ().
 * - Details are still unclear at the moment.
 *
 * Handling by the safety shell:
 * - Still unclear
 *
 * @param aContext pointer the SRTS context instance
 * @param aOffset Iterator variable (0=Start)
 * @param aBuffer String buffer descriptor for "name"
 * @param aNextOffset offset of next element, 0 indicates last item
 * @return error code
 */
DC_Rc DC_iterateErrorLog(SRTS_ContextPtr aContext, uint16_t aOffset, CMN_StringBufferDesc aBuffer, uint16_t *aNextOffset);

/**
 * Clears all  error log entries.
 *
 * Rationale:
 *
 * This function is not foreseen in the original scope. But if an error log needs to be managed and read out, it is very probable and also
 * desirable to delete it sometime again. (source: TELCON Jan 12th 2018).
 *
 * Remarks:
 * - [...] The sRTS manages the error log.
 * - There must also be a set () and a clear ().
 * - Details are still unclear.
 *
 * Handling by the safety shell:
 * - Still unclear
 *
 * @param aContext pointer the SRTS context instance
 * @return 0 on success.
 */
DC_Rc DC_clearErrorLog(SRTS_ContextPtr aContext);

/*@}*//* Error log */

/*@}*//* DCA Data Control API */

#endif
