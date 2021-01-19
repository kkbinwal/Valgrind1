/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_TYPES_H_
#define COMMON_TYPES_H_

/* -- Include files --------------------------------------------------------- */
#include <common_mem.h>
#include <common_lp_types.h>

#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdlib.h>

/* -- Defines --------------------------------------------------------------- */
#define CMN_ITERATOR_INIT 0u
#define CMN_ITERATOR_END  0u
#define CMN_ITERATOR_IS_LAST(it) ((it) == CMN_ITERATOR_END)
#define CMN_ARRAY_INDEX_TYPE CMN_DataTypeUdint
#define CMN_APM_VERSION 3

#define CMN_TRUE_LITERAL "true"
#define CMN_FALSE_LITERAL "false"
#define CMN_SAFETRUE_LITERAL "safetrue"
#define CMN_SAFEFALSE_LITERAL "safefalse"

/* -- Externals ------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */
typedef int CMN_CompareResult;

typedef bool CMN_Bool;

typedef uint8_t CMN_SafeBool;

typedef float CMN_Real32;

typedef double CMN_Real64;

/** @defgroup CMN Common Types and Structures
 *
 *  Common Types and Structures
 *
 *@{*/

/**
 * safe rts context forward declaration.
 */
typedef struct tag_SRTS_Context SRTS_Context;

/**
 * safe rts context pointer typedef.
 */
typedef SRTS_Context* SRTS_ContextPtr;

/**
 * Index
 */
typedef ptrdiff_t CMN_Index;

/**
 * Unsigned Index (e.g. for zero-based arrays)
 */
typedef size_t CMN_UnsignedIndex;

/**
 * Element count
 */
typedef uint32_t CMN_Count;

/**
 * Class ID.
 */
typedef uint32_t CMN_ClassId;

/**
 * Byte
 */
typedef uint8_t CMN_Byte;

/**
 * Const Byte
 */
typedef CMN_Byte const CMN_ByteConst;

/**
 * Const Byte pointer
 */
typedef CMN_ByteConst* CMN_ByteConstPtr;

/**
 * Byte pointer
 */
typedef CMN_Byte* CMN_BytePtr;

/**
 * Void pointer
 */
typedef void* CMN_VoidPtr;

/**
 * Pointer to const void
 */
typedef void const* CMN_VoidConstPtr;

/**
 * RGBA color.
 */
typedef uint32_t CMN_RGBA_Color;

/**
 * System execution state.
 *
 */
typedef enum
{
  CMN_ExecutionStateExecutionStoppedError = 0,            /**< System is in "Stopped Error" mode. */
  CMN_ExecutionStateExecutionRunningSafe = 1,             /**< System is in "Running Safe" mode. */
  CMN_ExecutionStateExecutionRunningTest = 2,             /**< System is in "Running Test" mode. */
  CMN_ExecutionStateExecutionStoppedSafe = 3,             /**< System is in "Stopped Safe" mode. */
  CMN_ExecutionStateExecutionStoppedTest = 4,             /**< System is in "Stopped Test" mode. */
  CMN_ExecutionStateExecutionHeldTest = 5,                /**< System is in "Held Test" mode. */
  CMN_ExecutionStateExecutionCycleStepTest = 6,           /**< System is in "Cycle Step Test" mode. */
  CMN_ExecutionStateExecutionBlockStepBreakpointTest = 7, /**< System is in "Block Step - Breakpoint (Test)" mode. */
  CMN_ExecutionStateExecutionBlockStepRunningTest = 8     /**< System is in "Block Step - Running (Test)" mode. */
} CMN_ExecutionState;

/**
 * Block type enum.
 *
 * Enumerates block types. Structures and strings are omitted intentionally.
 */
typedef enum {
  CMN_BlockTypeVariable = 0, /**< Block is a variable. */
  CMN_BlockTypeLiteral,      /**< Block is a literal. */
  CMN_BlockTypeFb,           /**< Function Block. */
  CMN_BlockTypeInput,        /**< Block is an input */
  CMN_BlockTypeOutput,       /**< Block is an output */
  CMN_BlockTypeArrayElement  /**< Block is an array element */
} CMN_BlockType;

/**
 * Pin direction.
 *
 * Indicates the flow direction of the pin.
 */
typedef enum {
  CMN_PinDirectionInput = 0, /**< Pin is an input. */
  CMN_PinDirectionOutput     /**< Pin is an output. */
} CMN_PinDirection;

/**
 * The edge of a block, where a pin is located.
 * 0=top, 1=right, 2=bottom, 3=left.
 */
typedef enum {
  CMN_BlockEdgeTop = 0,   /**< Pin is on top edge of block. */
  CMN_BlockEdgeRight = 1, /**< Pin is on right edge of block. */
  CMN_BlockEdgeBottom = 2, /**< Pin is on bottom edge of block. */
  CMN_BlockEdgeLeft = 3  /**< Pin is on left edge of block. */
} CMN_PinBlockEdge;

/**
 * Binary Buffer Descriptor.
 *
 * If binary data with unspecified size is to be returned, the caller allocates binary
 * buffer space and passes the location and the size of that space to processing
 * function via a binary buffer descriptor.
 */
typedef struct {
  CMN_BufferSize len; /**< Size of the buffer. */
  uint8_t* ptr;       /**< Points to the location of the binary array. */
} CMN_BinaryBufferDesc;

/**
 * Coordinate.
 *
 * Cartesian coordinates are uniformly expressed by a structure containing a
 * Cartesian tuple.
 */
typedef struct {
  CMN_Dimension x; /**< X coordinate. */
  CMN_Dimension y; /**< Y coordinate. */
} CMN_Coordinate;

/**
 * Rectangle.
 */
typedef struct {
  CMN_Coordinate position; /**< Position. */
  CMN_Coordinate size;     /**< Size. */
} CMN_Rectangle;

/**
 * Data Interface Block.
 *
 * Structure which contains all input data for the model.
 */
typedef struct {
  CMN_BlockType blockType;       /**< Block type. */
  CMN_DataType dataType;         /**< Data type. */
  char const* name;              /**< Class name of the FB, Literal value, Variable name, I/O
                                    name. */
  CMN_Rectangle geometry;        /**< Block geometry information */
} CMN_DataInterfaceBlock;

/**
 * Data Interface Block Extended.
 *
 * Same as @ref CMN_DataInterfaceBlock but with additional components.
 */
typedef struct {
  CMN_BlockHandle handle;       /**< The handle of the item (0 indicates an invalid
                                   item, added by application model) */
  CMN_ClassId classId;          /**< ID of the FB Class (as stated in library provider)
                                     or associated variable instance (as returned by
                                   add/iterate/...variable()) or IO index (from io provider) */
  CMN_BlockType blockType;      /**< Block type. */
  CMN_DataType dataType;        /**< Data type. */
  char const* name;             /**< Class name of the FB, Literal value, Variable name,
                                   io-name - Points into memory declared by varBuffer */
  CMN_Rectangle geometry;       /**< Block geometry information. */
} CMN_DataInterfaceExtBlock;

/**
 * Data Interface Comment.
 *
 * Structure which contains all input data for the model.
 */
typedef struct {
  char const* text;  /**< Comment text. */
  CMN_Rectangle box; /**< Comment canvas. */
} CMN_DataInterfaceComment;

/**
 * Data Interface Comment Extended.
 *
 * Same as @ref CMN_DataInterfaceComment but additional components.
 */
typedef struct {
  CMN_CommentHandle handle; /**< The handle of the item (0 indicates an invalid
                               item, added by application model). */
  char const* text;         /** Comment Text. */
  CMN_Rectangle box;        /**< Comment canvas. */
} CMN_DataInterfaceExtComment;

/**
 * Data Interface Variable.
 *
 * Structure which contains all input data for the model.
 */
typedef struct {
  CMN_DataType dataType;    /**< Variable's data type. */
  char const* name;         /**< Name of the variable */
  char const* initialValue; /**< Textual representation of the initial value */
  CMN_Size arraySize;       /**< Array size (for arrays: arraySize > 1) */
} CMN_DataInterfaceVariable;

/**
 * Same date as @ref CMN_DataInterfaceVariable but additional components.
 */
typedef struct {
  CMN_VariableHandle handle; /**< the handle (='instance-ID' )of the variable (0 indicates an
                                invalid item, added by application model) */
  CMN_DataType dataType;     /** Variable's data type. */
  char const* name;          /**< Name of the Variable */
  char const* initialValue;  /**< Textual representation of the initial value */
  CMN_Size arraySize;        /**< Array size (for arrays: arraySize > 1) */
} CMN_DataInterfaceExtVariable;

/**
 * Stream direction (Upload, Download).
 */
typedef enum {
  CMN_StreamDirectionUpload = 0,    /**< Upload from client to sRTS */
  CMN_StreamDirectionDownload = 1   /**< Download from sRTS to client */
} CMN_StreamDirection;

/**
 * Stream type.
 */
typedef enum {
  CMN_StreamTypeNone = 0,           /**< No stream is active */
  CMN_StreamTypeHwConfig = 1,       /**< Hardware configuration stream */
  CMN_StreamTypeApplicationModel= 2 /**< Application model stream */
} CMN_StreamType;

typedef struct
{
  CMN_StreamType streamType;
  CMN_StreamDirection streamDirection;
} CMN_StreamState;

/* -- Forward decls --------------------------------------------------------- */

typedef struct tag_INP_Context INP_Context;
typedef INP_Context* INP_ContextPtr;

typedef struct tag_APM_Instance APM_Instance;
typedef APM_Instance* APM_InstancePtr;

typedef struct tag_SSH_InstanceInfo SSH_InstanceInfo;
typedef SSH_InstanceInfo* SSH_InstanceInfoPtr;

typedef struct tag_DPM_StringManagerContext DPM_StringManager_Context;
typedef DPM_StringManager_Context* DPM_StringManager_ContextPtr;

typedef struct tag_PIL_Context PIL_Context;
typedef PIL_Context* PIL_ContextPtr;

typedef struct tag_DPM_LiteralManagerContext DPM_LiteralManager_Context;
typedef DPM_LiteralManager_Context* DPM_LiteralManager_ContextPtr;

/* -- Defines --------------------------------------------------------------- */
#define CMN_DATATYPE_MAX CMN_DataTypeSafeint

#define CMN_TRUE ((CMN_Bool)1u)
#define CMN_FALSE ((CMN_Bool)0u)

#define CMN_SAFETRUE ((CMN_SafeBool)0xAAu)
#define CMN_SAFEFALSE ((CMN_SafeBool)0u)


#define CMN_CHR_ZERO '\0'

/** Cast to a desired type. */
#define CMN_CAST(desiredType, arg) ((desiredType)(arg))
/** Add a number of bytes to an address */
#define CMN_PTR_ADD_BYTES(ptr1, numBytes) (CMN_CAST(CMN_BytePtr, (ptr1)) + (numBytes))
/** Subtract a number of bytes to an address */
#define CMN_PTR_SUB_BYTES(ptr1, numBytes) (CMN_CAST(CMN_BytePtr, (ptr1)) - (numBytes))
/** Subtract basePtr from ptr to determine an offset in bytes */
#define CMN_PTR_SUB(ptr, basePtr) (CMN_CAST(CMN_BytePtr, (ptr)) - CMN_CAST(CMN_BytePtr, (basePtr)))

#define CMN_DOWNCAST_STRSIZE(tempVariable) (uint8_t) tempVariable

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Create color.
 *
 * @param aRed red component (0-255)
 * @param aGreen green component (0-255)
 * @param aBlue blue component (0-255)
 * @return #CMN_RGBA_Color the combined RGB color code
 */
CMN_RGBA_Color CMN_createColor(CMN_RGBA_Color aRed, CMN_RGBA_Color aGreen, CMN_RGBA_Color aBlue);

/**
 * Get the name of a data type.
 *
 * @param aType the data type for which to get a name
 * @param[out] aDataTypeName the name as c-string (zero terminated)
 * @return return code
 * @retval #CMN_OK
 * @retval #CMN_EINVAL
 */
CMN_Rc CMN_getDataTypeName(CMN_DataType aType, char const** aDataTypeName);

/**
 * Calculates alignment padding.
 *
 * @param[in] aOffset Offset to an aAlignment-byte aligned base address.
 * @param[in] aAlignment Required aAlignment-byte alignment. Must be 1, 2, 4, or 8.
 * @param[out] aPadding The calculated padding. (aOffset+*aPadding) is aAlignment-byte aligned.
 * @return return code
 * @retval #CMN_EINVAL aAlignment is not 1, 2, 4, or 8
 * @retval #CMN_ERANGE (aOffset+*aPadding) caused integer addition overflow
 */
CMN_Rc CMN_getAlignmentPadding(CMN_Offset aOffset, CMN_Offset aAlignment, CMN_Offset* aPadding);


/*@}*/ /* CMN */

#endif
