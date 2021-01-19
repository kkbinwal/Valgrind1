/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCHWCONFIG_H_
#define DCHWCONFIG_H_

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

/** @defgroup HWCFG Hardware Config & IOs
 *
 * @brief Hardware Config & IOs
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Retrieves information about io variables.
 * Output:
 * - Properties of the iterated element.
 * Description:
 * - Successively constructs a list of all physically available IO-Channels. see: iterate_block().
 *
 * @param aContext pointer the SRTS context instance
 * @param aOffset Iterator variable (0=Start)
 * @param aNameBuffer String buffer descriptor for "name"
 * @param aIoDirection INPUT, OUTPUT
 * @param aDatatype BOOL, INT, WORD
 * @param aNextOffset offset of next element, 0 indicates last item
 * @return Error code
 * @retval EINVAL Invalid Iterator
 * @retval ENOENT There is not a single element to iterate over
 */
DC_Rc DC_iterateIoVariables(
    SRTS_ContextPtr aContext,
    uint16_t aOffset,
    CMN_StringBufferDesc aNameBuffer,
    SL_IoDirection* aIoDirection,
    CMN_DataType* aDatatype,
    uint16_t* aNextOffset);

/*@}*//* HWCFG Hardware Config & IOs */

/*@}*//* DCA Data Control API */

#endif
