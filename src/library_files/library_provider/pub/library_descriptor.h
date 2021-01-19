/* Copyright (C) logi.cals GmbH. All rights reserved. */

#ifndef LIBRARY_DESCRIPTOR_H_
#define LIBRARY_DESCRIPTOR_H_

#include <library_provider.h>

#include <LC3CGBase.h>

/* -- Defines --------------------------------------------------------------- */

/** @defgroup LP Library Provider
 *
 * @brief Library Provider
 *
 * Provides an interface to one or many libraries. (the library descriptor)
 * A library consists of a number of blocks (function blocks), which have an index.
 * For a block, both code and graphical information can be retrieved.
 * These static interfaces can take an arbitrary library descriptor
 * structure and give access to its meta data elements. So the library
 * provider public interface implementation remains part of srts, and
 * is not generated in lc3.
 *
 *@{*/

/** @defgroup LD Library Descriptor
 *
 * @brief Library Descriptor
 *
 * Defines the meta data structures of one or many libraries.
 * A library consists of a number of blocks (function blocks), which have an index.
 * For a block, both code and graphical information are encoded.
 * It also contains access to this data structure tree.
 * The implementation is generated in lc3.
 *
 *@{*/

/**
 * Block IO count.
 *
 * Contains the number of input and output pins of a block.
 */
typedef const struct tag_LP_BlockIoCount
{
  LP_DataSize const sizeOfThis; /**< sizeof this struct */
  LP_PinListSize const inputCount; /**< number of input pins */
  LP_PinListSize const outputCount; /**< number of output pins */
} LP_BlockIoCount;

/**
 * Visual block information structure.
 *
 * Contains infos about how to draw a block.
 */
typedef const struct tag_LP_VisualBlockInfo
{
  LP_DataSize const sizeOfThis; /**< sizeof this struct */
  LP_RasterSize const rasterSize; /**< block size in raster units */
  LP_RgbColor const backgroundRgbColor; /**< block background color */
  LP_ConstVoidPtr const additionalInfo; /**< additional info (e.q. line-style, ....) */
} LP_VisualBlockInfo;

/**
 * Visual IO Info.
 *
 * Visual info of an io pin. Contains infos about the position an label of an
 * io pin.
 */
typedef const struct tag_LP_VisualIoInfo
{
  LP_DataSize const sizeOfThis; /**< sizeof this struct */
  LP_DisplayIndex const displayIndex; /**< Index of IO pin display in visual block. */
  LP_ConstCStr const name; /**< pin name, used for visual io pin label, if alternative name is NULL. */
  LP_ConstCStr const alternativeName; /**< alternative io pin name, if non-NULL, it replaces the visual pin label. */
  LP_ConstVoidPtr const additionalInfo; /**< (e.q. connection-point-style, ....)   */
} LP_VisualIoInfo;

/**
 * Code block info.
 *
 * Code related info of a block. Contains infos about how to initialize and call
 * a block and the input/internal/output data size.
 */
typedef const struct tag_LP_CodeBlockInfo
{
  LP_DataSize const sizeOfThis; /**< sizeof this struct */
  LP_InstanceDataSize const instanceDataSize; /**< size of the block instance data (used for block inputs / outputs /
                                             internal data) in bytes */
  LP_InitFunPtr const initFun; /**< block init function pointer */
  LP_RunFunPtr const runFun; /**< block run function pointer */
  LP_MemOffset const enoOffset; /**< memory offset of the eno value */
} LP_CodeBlockInfo;

/**
 * IO pin code info.
 *
 * Code related info of an IO pin.
 *
 */
typedef const struct tag_LP_CodeIoInfo
{
  LP_DataSize const sizeOfThis; /**< sizeof this struct */
  LP_MemOffset const offset; /**< memory offset of the pin value, base address is the block instance data address. */
  CMN_DataType const dataType; /**< datatype of the pin value */
} LP_CodeIoInfo;

/**
 * Forward declaration of LP_Folder const pointer
 */
typedef struct tag_LP_Folder const* LP_FolderConstPtr;

/**
 * Folder tree node.
 */
typedef const struct tag_LP_Folder
{
  LP_ConstCStr const name; /**< name of the folder */
  LP_FolderConstPtr const parent; /**< address of parent folder or NULL, if this is the root folder */
} LP_Folder;

typedef const struct tag_LP_Block
{
  LP_DataSize const sizeOfThis;
  LP_ConstCStr const name;
  LP_ConstCStr const alternativeName;
  LP_BlockIoCount const blockIoCount;
  LP_VisualBlockInfo const visualBlockInfo;
  LP_CodeBlockInfo const codeBlockInfo;
  LP_VisualIoInfo const* const* const inputVisualIoInfo;
  LP_VisualIoInfo const* const* const outputVisualIoInfo;
  LP_CodeIoInfo const* const* const inputCodeIoInfo;
  LP_CodeIoInfo const* const* const outputCodeIoInfo;
  LP_Folder const* const folder;
} LP_Block;

typedef struct tag_EEPDB_Data
{
  uint64_t currentTime;
} EEPDB_Data;

typedef const struct tag_LP_VersionInfo
{
  LP_DataSize const sizeOfThis;
  LP_Version const majorVersion;
  LP_Version const minorVersion;
  LP_Version const buildVersion;
  LP_ConstCStr const additionalInfo;
} LP_VersionInfo;

typedef const struct tag_LP_Library
{
  LP_DataSize const sizeOfThis;
  LP_VersionInfo const versionInfo;
  LP_ConstCStr const name;
  LP_ConstCStr const displayName;
  LP_Fingerprint const fingerprint;
  LP_Block const* const* blocks;
  LP_BlockListSize const numBlocks;
  LP_Frequency const frequency;
} LP_Library;

LP_LibraryHandle LD_getLibrary(void);
LP_Rc LD_libraryInit(LP_LibraryHandle aLibraryHandle);

/*@}*//* LP Library Descriptor */

/*@}*//* LP Library Provider */

#endif /* LIBRARY_PROVIDER_PRIV_H_ */
