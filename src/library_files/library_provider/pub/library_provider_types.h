/* Copyright (C) logi.cals GmbH. All rights reserved. */

#ifndef LIBRARY_PROVIDER_TYPES_H_
#define LIBRARY_PROVIDER_TYPES_H_

/* -- Include files --------------------------------------------------------- */
#include <common_lp_types.h>

/** @addtogroup LP
 *@{*/

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Return code. (#LP_OK, #LP_ENULLPTR, ...)
 */
typedef CMN_Rc LP_Rc;

/**
 * List size.
 */
typedef uint32_t LP_ListSize;

/**
 * Zero-based list index. No gaps.
 */
typedef uint32_t LP_ListIdx;

/**
 * Zero-based index of a list of blocks. No gaps.
 */
typedef uint16_t LP_BlockListIdx;

/**
 * Public handle for library blocks.
 */
typedef struct
{
  LP_ListIdx libIdx;        /**< index to the function block in the library */
  LP_BlockListIdx blockIdx; /**< index to the library (list of blocks) */
} LP_LibraryBlockIdx;

/**
 * Zero-based index of a list of pins. No gaps.
 */
typedef CMN_PinCount LP_PinListIdx;

/**
 * Forward declaration of tag_LP_Block handle.
 */
typedef struct tag_LP_Block const* LP_BlockHandle;

/**
 * Forward declaration of tag_LP_VersionInfo handle.
 */
typedef struct tag_LP_VersionInfo const* LP_VersionInfoHandle;

/**
 * Forward declaration of tag_LP_Libraries handle.
 */
typedef struct tag_LP_Libraries const* LP_LibrariesHandle;

/**
 * Forward declaration of tag_LP_Library handle.
 */
typedef struct tag_LP_Library const* LP_LibraryHandle;

/**
 * Constant C-string.
 */
typedef char const* LP_ConstCStr;

/**
 * Timestamp.
 */
typedef uint64_t LP_TimeStamp;

/**
 * Frequency
 */
typedef uint64_t LP_Frequency;

/**
 * Version.
 */
typedef uint32_t LP_Version;

/**
 * Fingerprint.
 */
typedef uint32_t LP_Fingerprint;

/**
 * Size of a list of blocks.
 */
typedef uint16_t LP_BlockListSize;

/**
 * Size of a list of pins.
 */
typedef CMN_PinCount LP_PinListSize;

/**
 * Index of IO pin display in visual block.
 * Inputs are on the left side, outputs are
 * on the right side.
 * Pin positions go from top to bottom,
 * starting at index 0.
 * Used indices may have gaps.
 */
typedef CMN_PinDisplayIndex LP_DisplayIndex;

/**
 * Size of data elements (of a struct) in bytes.
 */
typedef uint32_t LP_DataSize;

/**
 * Instance data size of a function block.
 */
typedef uint16_t LP_InstanceDataSize;

/**
 * Memory offset. (to a base pointer)
 */
typedef CMN_Offset LP_MemOffset;

/**
 * Void pointer.
 */
typedef void* LP_VoidPtr;

/**
 * Const void pointer.
 */
typedef void const* LP_ConstVoidPtr;

/**
 * Instance data pointer of a function block.
 */
typedef struct tag_LP_InstanceData* LP_InstanceDataPtr;

/**
 * Entry point data.
 *
 * Passed to functions of a function block.
 *
 * @see #LP_InitFun
 * @see #LP_RunFun
 */
typedef struct tag_LP_EntryPoint* LP_EntryPointPtr;

/**
 * Init function of a function block.
 *
 * Initializes the variables of the block instance data.
 *
 * @param[in] aThisData The block instance data pointer.
 * @return void
 */
typedef void LP_InitFun(LP_InstanceDataPtr aThisData);

/**
 * Init function pointer of a function block.
 */
typedef LP_InitFun* LP_InitFunPtr;

/**
 * Run function of a function block.
 *
 * Performs the function block function. Inputs are written to the block instance
 * data before calling this function. Outputs are placed in block instance data.
 *
 * Memory locations of the input and output pin values (inside the block instance
 * data) and their datatypes can be located via api calls.
 *
 * @param[in] aThisData The block instance data pointer.
 * @param[in] aEntryPoint Entry point data pointer.
 * @return void
 */
typedef void LP_RunFun(LP_InstanceDataPtr aThisData, LP_EntryPointPtr aEntryPoint);

/**
 * Run function pointer of a function block.
 */
typedef LP_RunFun* LP_RunFunPtr;

/**
 * RGB color.
 */
typedef struct
{
  uint8_t red;   /**< value for color red */
  uint8_t green; /**< value for color green */
  uint8_t blue;  /**< value for color blue */
} LP_RgbColor;

/**
 * Geometrical size in raster units.
 */
typedef struct
{
  uint8_t width;  /**< raster width */
  uint8_t height; /**< raster height */
} LP_RasterSize;

/*@}*//* LP */

#endif /* LIBRARY_PROVIDER_TYPES_H_ */
