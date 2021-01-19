/* Copyright (C) logi.cals GmbH. All rights reserved. */

#ifndef LIBRARY_PROVIDER_H_
#define LIBRARY_PROVIDER_H_

/* -- Include files --------------------------------------------------------- */
#include <common_rc.h>
#include <common_strops.h>
#include <library_provider_types.h>

/** @defgroup LP Library Provider
 *
 * Provides an interface to one or many libraries. (the library descriptor)
 * A library consists of a number of blocks (function blocks), which have an index.
 * For a block, both code and graphical information can be retrieved.
 * These static interfaces can take an arbitrary library descriptor
 * structure and give access to its meta data elements. So the library
 * provider public interface implementation remains part of srts, and
 * is not generated in lc3.
 */
 
 /** @addtogroup LP
 *@{*/

/* -- Defines --------------------------------------------------------------- */
#define LP_OK             CMN_LP_RC_BASE           /**< successful function execution. */
#define LP_ENOLIBSAVAIL   (CMN_LP_RC_BASE + 0x1u)  /**< No libraries are available. */
#define LP_ENOBLOCKWNAME  (CMN_LP_RC_BASE + 0x2u)  /**< No block with given name found */
#define LP_EINVAL         CMN_EINVAL               /**< An argument is invalid. */
#define LP_ENOBUFS        CMN_ENOBUFS              /**< No buffer space is available. */
#define LP_EBADHNDL       CMN_EBADHNDL             /**< The handle is invalid. */
#define LP_EIDXBOUNDS     CMN_EIDXBOUNDS           /**< The list index is out of bounds. */
#define LP_ENULLPTR       CMN_ENULLPTR             /**< A pointer should be non-NULL, but is NULL. */

#define LP_FOLDER_PATH_MAXIMUM_DEPTH 64u           /**< Maximum depth of library block folder path */
#define LP_FOLDER_PATH_SEPARATOR '\n'              /**< Folder separator of library block folder path */
#define LP_DISPLAY_NAME_BUFFER_SIZE 255u           /**< Maximum number of characters in the display name, including the terminating '\0' character. */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */
LP_Rc LP_getLibraryProviderVersionMajor(LP_Version* aMajorVersion);
LP_Rc LP_getLibraryProviderVersionMinor(LP_Version* aMinorVersion);
LP_Rc LP_getLibraryProviderVersionBuild(LP_Version* aBuildVersion);
LP_Rc LP_getLibraryProviderVersionAdditionalInfo(LP_ConstCStr* aAdditionalInfo);

/**
 * Get the libraries handle.
 *
 * @param[in] aHandle The libraries handle.
 * @param[out] aHandle The libraries handle to be retrieved. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_ENOLIBSAVAIL
 */
LP_Rc LP_getLibraries(LP_LibrariesHandle* aHandle);

/**
 * Get the number of libraries.
 *
 * @param[in] aHandle The libraries handle. //BACR - removed to address Jenkins Pipeline build issue
 * @param[out] aNumLibraries The number of libraries.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibrariesNum(LP_ListSize* aNumLibraries);

/**
 * Get the frequency (in Hz) of the timer tick used for the implementation of
 * the blocks of all libraries.
 *
 * @param[out] aFrequency The frequency (in Hz) of the timer tick.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_ENOLIBSAVAIL
 */
LP_Rc LP_getFrequency(LP_Frequency* aFrequency);

/**
 * Get a library handle.
 *
 * @param[in] aHandle The libraries handle. //BACR - removed to address Jenkins pipeline build issue
 * @param[in] aIdx The zero-based library list index.
 * @param[out] aLibraryHandle The library handle. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibrary(LP_ListIdx aIdx, LP_LibraryHandle* aLibraryHandle);

/**
 * Get a library name.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aName The library name. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryName(LP_LibraryHandle aHandle, LP_ConstCStr* aName);

/**
 * Get a library display name.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aDisplayName The library display name. Possibly NULL.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryBlockDisplayName
 */
LP_Rc LP_getLibraryDisplayName(LP_LibraryHandle aHandle, LP_ConstCStr* aDisplayName);

/**
 * Get the library fingerprint.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aFingerprint The library fingerprint. An error implies a fingerprint value of zero.
 *                          (But there could possibly also be a successfully returned fingerprint value of zero)
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryFingerprint(LP_LibraryHandle aHandle, LP_Fingerprint* aFingerprint);

/**
 * Get the library version info handle.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aVersionInfoHandle The library version info handle. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryFingerprint
 * @see #LP_getLibraryVersionMajor
 * @see #LP_getLibraryVersionMinor
 * @see #LP_getLibraryVersionBuild
 * @see #LP_getLibraryVersionAdditionalInfo
 */

LP_Rc LP_getLibraryVersionInfo(LP_LibraryHandle aHandle, LP_VersionInfoHandle* aVersionInfoHandle);

/**
 * Get the library major version.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aMajorVersion The library major version. An error implies a version value of zero.
 *                           (But there could also be a successful version value of zero)
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryVersionInfo
 */
LP_Rc LP_getLibraryVersionMajor(LP_VersionInfoHandle aHandle, LP_Version* aMajorVersion);

/**
 * Get the library minor version.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aMinorVersion The library minor version. An error implies a version value of zero.
 *                           (But there could also be a successful return code and a version value of zero)
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryVersionInfo
 */
LP_Rc LP_getLibraryVersionMinor(LP_VersionInfoHandle aHandle, LP_Version* aMinorVersion);

/**
 * Get the library build version.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aBuildVersion The library build version. An error implies a version value of zero.
 *                           (But there could also be a successful return code and a version value of zero)
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryVersionInfo
 */
LP_Rc LP_getLibraryVersionBuild(LP_VersionInfoHandle aHandle, LP_Version* aBuildVersion);

/**
 * Get the library version additional info string.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aAdditionalInfo The library version additional info string. Possibly NULL with successful
 *                             return code #LP_OK.
 *                             In case of an error, this is also set to NULL.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryVersionInfo
 */
LP_Rc LP_getLibraryVersionAdditionalInfo(LP_VersionInfoHandle aHandle, LP_ConstCStr* aAdditionalInfo);

/**
 * Get the number of library blocks.
 *
 * @param[in] aHandle The library handle.
 * @param[out] aNumBlocks The number of library blocks. Zero if an error occurred. (But it can also be zero
 *                        with a successful return code, if the library is empty)
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlocksNum(LP_LibraryHandle aHandle, LP_BlockListSize *aNumBlocks);

/**
 * Get a library block handle.
 *
 * Get a library block handle, where the block is identified by the block index.
 *
 * Note, that block indices may change after library changes.
 *
 * @param[in] aHandle The library handle.
 * @param[in] aBlockIdx The zero-based library block index. The maximum bock index is
 *                      the number of library blocks (returned by \ref LP_getLibrariesNum)
 *                      minus one.
 * @param[out] aBlockHandle The library block handle. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 * @see #LP_getLibraryBlockName
 */
LP_Rc LP_getLibraryBlock(LP_LibraryHandle aHandle, LP_BlockListIdx aBlockIdx, LP_BlockHandle* aBlockHandle);

/**
 * Get the library block display name.
 * The display name consists of the folder path, and the block name (without namespaces).
 *
 * Example: "Test Library\nfolder1\nfolder2\nAND"
 *
 * The library definition can contain nested folders (keyword FOLDER).
 * The folder path is the path to the folder, where the library block is defined.
 *
 * Optionally, the library generator adds the library name as root folder.
 *
 * If the library display name is null, the library name is added as root folder.
 * If the library display name is a non-empty string, the library display name is added as root folder.
 * If the library display name is an empty string, the library name is not part of the
 * folder path. This is useful, if multiple libraries with common namespaces are developed.
 *
 * The path separator is #LP_FOLDER_PATH_SEPARATOR.
 * The maximum folder depth is #LP_FOLDER_PATH_MAXIMUM_DEPTH.
 *
 * @param[in] aLibraryHandle The library handle.
 * @param[in] aHandle The library block handle.
 * @param[in] aDisplayNameBuffer string buffer for display name. aDisplayNameBuffer.len must be #LP_DISPLAY_NAME_BUFFER_SIZE.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_EBADHNDL
 * @retval #LP_ENULLPTR
 * @retval #LP_ENOBUFS
 */
LP_Rc LP_getLibraryBlockDisplayName(LP_LibraryHandle aLibraryHandle, LP_BlockHandle aHandle, CMN_StringBufferDesc aDisplayNameBuffer);

/**
 * Get the library block name.
 *
 * The block name may contain the namespace. (i.e. "logicals.testnamespace.AND")
 *
 * It identifies the library block. If the library is changed and the application model is
 * loaded again, the block name is used to get the block index.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] aName The library block name. NULL if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryBlockAlternativeName
 */
LP_Rc LP_getLibraryBlockName(LP_BlockHandle aHandle, LP_ConstCStr* aName);

/**
 * Get the library block alternative name.
 *
 * This string is used as visual block label.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] aAlternativeName The alternative library block name. This value is never NULL or empty.
 *
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @see #LP_getLibraryBlockName
 */
LP_Rc LP_getLibraryBlockAlternativeName(LP_BlockHandle aHandle, LP_ConstCStr* aAlternativeName);

/**
 * Get the library block input count.
 *
 * Get the number of input pins for a library block with given handle.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] inputCount The input pin count. Count is set to zero, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockInputCount(LP_BlockHandle aHandle, LP_PinListSize* inputCount);

/**
 * Get the library block IO count.
 *
 * Get the number of input and output pins for a library block with given handle.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] outputCount The output pin count. Count is set to zero, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockOutputCount(LP_BlockHandle aHandle, LP_PinListSize* outputCount);

/**
 * Get the raster size of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] rasterSize The raster size. Raster size is set to all zeros, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockVisualRasterSize(LP_BlockHandle aHandle, LP_RasterSize* rasterSize);

/**
 * Get the background color of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] color The background color. Background color elements are set to zero, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockVisualBackgroundColor(LP_BlockHandle aHandle, LP_RgbColor* color);

/**
 * Get the additional visual info of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] additionalInfo The additional visual info pointer. The pointer is set to NULL, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockVisualAdditionalInfo(LP_BlockHandle aHandle, LP_ConstVoidPtr* additionalInfo);

/**
 * Get the input pin display index (#LP_DisplayIndex) of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinDisplayIndex The input pin display index. The display index is set to zero, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualInputPinDisplayIndex(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, LP_DisplayIndex* aInputPinDisplayIndex);

/**
 * Get the input pin name of a library block.
 *
 * It is used for visual io pin label, if the alternative pin name is NULL.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinName The input pin name. The name string is set to NULL, if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualInputPinName(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, LP_ConstCStr* aInputPinName);

/**
 * Get the input pin alternative name of a library block.
 *
 * If non-NULL, it replaces the visual pin label.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinAlternativeName The input pin alternative name. The name string is set to NULL, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualInputPinAlternativeName(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, LP_ConstCStr* aInputPinAlternativeName);

/**
 * Get the input pin additional visual info of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinAdditionalInfo The input pin additional visual info. It is set to NULL, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualInputPinAdditionalInfo(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, LP_ConstVoidPtr* aInputPinAdditionalInfo);

/**
 * Get the output pin display index (#LP_DisplayIndex) of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinDisplayIndex The output pin display index. The display index is set to zero, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualOutputPinDisplayIndex(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex, LP_DisplayIndex* aOutputPinDisplayIndex);

/**
 * Get the output pin name of a library block.
 *
 * It is used for visual io pin label, if the alternative pin name is NULL.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinName The output pin name. The name string is set to NULL, if and only if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualOutputPinName(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex, LP_ConstCStr* aOutputPinName);

/**
 * Get the output pin alternative name of a library block.
 *
 * If non-NULL, it replaces the visual pin label.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinAlternativeName The output pin alternative name. The name string is set to NULL, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualOutputPinAlternativeName(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex, LP_ConstCStr* aOutputPinAlternativeName);

/**
 * Get the output pin additional visual info of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinAdditionalInfo The output pin additional visual info. It is set to NULL, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockVisualOutputPinAdditionalInfo(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex,
    LP_ConstVoidPtr* aOutputPinAdditionalInfo);

LP_Rc LP_setCodeEntryPointCurrentTime(LP_EntryPointPtr aEntryPointPtr, uint64_t currentTime);

LP_Rc LP_getEntryPointSize(CMN_BufferSize* aBufSize);
LP_Rc LP_initEntryPoint(LP_EntryPointPtr aEntryPointPtr);
LP_Rc LP_getInstanceDataSize(LP_BlockHandle aBlockHandle, CMN_BufferSize* aBufSize);

/**
 * Get the init function (#LP_InitFun) of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] aInitFun The init function. The init function is set to NULL, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockCodeInitFun(LP_BlockHandle aHandle, LP_InitFunPtr* aInitFun);

/**
 * Get the run function (#LP_RunFun) of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[out] aRunFun The run function. The run function is set to zero, if an error occurs.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 */
LP_Rc LP_getLibraryBlockCodeRunFun(LP_BlockHandle aHandle, LP_RunFunPtr* aRunFun);

/**
 * Get an input pin memory offset of a library block.
 *
 * The memory offset is relative to the beginning of the instance data.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinMemoryOffset The input pin memory offset. It is set to zero, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockCodeInputPinMemoryOffset(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, LP_MemOffset* aInputPinMemoryOffset);

/**
 * Get an input pin datatype of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aInputPinIndex The zero-based input pin index.
 * @param[out] aInputPinDataType The input pin datatype. It is set to #CMN_DataTypeNone, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockCodeInputPinDataType(LP_BlockHandle aHandle, LP_PinListIdx aInputPinIndex, CMN_DataType* aInputPinDataType);

/**
 * Get an output pin memory offset of a library block.
 *
 * The memory offset is relative to the beginning of the instance data.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinMemoryOffset The output pin memory offset. It is set to zero, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockCodeOutputPinMemoryOffset(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex, LP_MemOffset* aOutputPinMemoryOffset);

/**
 * Get an output pin datatype of a library block.
 *
 * @param[in] aHandle The library block handle.
 * @param[in] aOutputPinIndex The zero-based output pin index.
 * @param[out] aOutputPinDataType The output pin datatype. It is set to #CMN_DataTypeNone, if an error has occurred.
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 */
LP_Rc LP_getLibraryBlockCodeOutputPinDataType(LP_BlockHandle aHandle, LP_PinListIdx aOutputPinIndex, CMN_DataType* aOutputPinDataType);

/**
 * Retrieve library block indices by name (expensive)
 *
 * @param[in] aName the name of the block
 * @param[out] aLibBlockIdx the public handle of the library block
 * @return #LP_Rc
 * @retval #LP_OK
 * @retval #LP_ENULLPTR
 * @retval #LP_EBADHNDL
 * @retval #LP_EIDXBOUNDS
 * @retval #LP_ENOLIBSAVAIL
 * @retval #LP_ENOBLOCKWNAME
 */
LP_Rc LP_getLibraryBlockIdxByName(char const* aName, LP_LibraryBlockIdx* aLibBlockIdx);

/**
 * Retrieve library block handle by its indices (cheap)
 */
LP_Rc LP_getLibraryBlockByIdx(LP_LibraryBlockIdx aLibBlockIdx, LP_BlockHandle* aBlockHandle);

/**
 * Retrieve ENO value for given block handle
 */
LP_Rc LP_getLibraryBlockEnoMemoryOffset(LP_BlockHandle aHandle, LP_MemOffset* aEnoOffset);

/*@}*//* LP */

#endif /* LIBRARY_PROVIDER_H_ */
