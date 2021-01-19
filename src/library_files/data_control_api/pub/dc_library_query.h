/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCLIBRARYQUERY_H_
#define DCLIBRARYQUERY_H_

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

/** @defgroup LQ Library Query
 *
 * @brief Library Query
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Retrieves the properties of all FBs in the library.
 *
 * See @ref DC_iterateBlock.
 * Buffers will be filled with the relevant information.
 * Handling by the Safety-Shell:
 * - Emulation by getLibraryBlockCount (), getLibraryBlockName (), et al.
 *
 * @param aContext pointer the SRTS context instance
 * @param aOffset Iterator variable (0=Start)
 * @param aLibraryBlockInfo library block information
 * @param aNextOffset iterator to next block, =0: finished
 * @return DC_Rc Error code
 * @retval EINVAL Invalid iterator
 */
DC_Rc DC_iterateLibrary(SRTS_ContextPtr aContext, uint16_t aOffset, DC_LibraryBlockInfoPtr aLibraryBlockInfo, uint16_t* aNextOffset);

/**
 * Retrieves interface information from an FB which is retrieved by "iterate_library".
 *
 * See @ref DC_iterateBlock.
 * Buffers will be filled with the relevant information.
 * Handling by the Safety-Shell:
 * - Safety-Shell acts as middleware to the Library-Provider.
 *
 * @param aContext pointer the SRTS context instance
 * @param aLibraryOffset Identifier given by the library.
 * @param aPinOffset Iterator variable (0=Start).
 * @param aPinInfo pointer to a structure where the pin information will be stored
 * @param aNextOffset iterator to next block, =0: finished
 * @return DC_Rc Error code
 * @retval EINVAL Invalid iterator
 */
DC_Rc DC_iteratePins(SRTS_ContextPtr aContext, uint16_t aLibraryOffset, uint16_t aPinOffset, DC_PinInfoPtr aPinInfo, uint16_t* aNextOffset);

/**
 * Retrieves the version information of [?]
 *
 * - Constant version information of the sRTS program.
 * - Attention: also version information from the library is needed.
 * Handling by the Safety-Shell:
 *  - Direct implementation
 *
 * @param aContext pointer the SRTS context instance
 * @param aVersionBuffer Buffer descriptor for "version"
 * @return Always OK
 */
DC_Rc DC_getVersionInformation(SRTS_ContextPtr aContext, CMN_StringBufferDesc aVersionBuffer);

/**
 * Retrieves the block handle and the output pin index of a given instance path.
 *
 * Instance path format is libraryBlockName.outputPinName.
 *
 * @param aContext Pointer the SRTS context instance
 * @param aInstancePath Instance path of an output pin of a function block
 * @param aOutputPinIndex Pointer where the output pin index will be stored
 * @param aBlock Pointer where the block handle will be stored
 * @return DC_Rc Error code
 * @retval SSH_ELP Error by library provider
 */
DC_Rc DC_getBlockHandleAndOutputPinIndex(SRTS_ContextPtr aContext, char const* aInstancePath, CMN_PinCount* aOutputPinIndex, CMN_DataInterfaceExtBlock* aBlock);

/*@}*//* Library Query */

/*@}*//* DCA Data Control API */

#endif
