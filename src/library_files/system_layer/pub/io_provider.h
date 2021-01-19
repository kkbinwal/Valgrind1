/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_IO_PROVIDER_H
#define SYSTEM_LAYER_IO_PROVIDER_H

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>
#include <common_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SL System Layer Interface
 *
 *  In order to integrate the Safe RTS to a specific platform, this
 *  interfaces have to be implemented by the platform vendor.
 *
 *@{*/

/** @defgroup IO IO Provider Interface
 *
 *  This module is part of the system layer.
 *
 *  The public interface handles IO description iteration, and
 *  determining the memory address of each IO in the IO memory image.
 *
 *  Before the PLC cycle, IO values are read from the
 *  hardware and written to the IO memory image. (if IOs are connected)
 *
 *  After the PLC cycle, values from IO memory image are
 *  written to the hardware. (if IOs are connected)
 *
 *  The changed list of io descriptions can be retrieved after
 *  io system configuration was changed.
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** @name Available IO
 * Provides an iterator interface to retrieve all IOs available for the implementation of the safety application.
 *
 */
/*@{*/

/**
 * Get the memory address and data type of an IO variable in the IO memory image.
 *
 * @param[in] aCtx
 * @param[in] aIoIndex IO index
 * @param[out] aIoAddress memory address of io (in io image)
 * @param[out] aDataType data type of io
 * @return return code
 * @retval #CMN_EINVALCTX
 * @retval #CMN_EIDXBOUNDS
 * @retval #CMN_ENULLPTR
 * @retval #SL_EINVALSYSCFG
 * @retval #IO_OK
 */
IO_Rc SL_getIoAddressAndDataType(SRTS_ContextPtr aCtx, CMN_IoDescrListIdx aIoIndex, CMN_VoidPtr* aIoAddress, CMN_DataType* aDataType);


/**
 * Retrieves the number of IO descriptions.
 *
 * @param[in] aCtx
 * @param[out] aCount
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getIoDescriptionCount(SRTS_ContextPtr aCtx, SL_IoDescrListSize *aCount);

/**
 * Retrieves the IO descriptions structure.
 *
 * @param[in] aCtx
 * @param[in] aIndex zero based index
 * @param[out] aIoDescription IO description
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_EIDXBOUNDS
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getIoDescription(SRTS_ContextPtr aCtx, CMN_IoDescrListIdx aIndex, SL_IoDescription* aIoDescription);

/*@}*/

/*@}*/

/*@}*/

#endif /* SYSTEM_LAYER_IO_PROVIDER_H */
