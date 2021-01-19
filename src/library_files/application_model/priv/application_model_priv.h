/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_PRIV_H_
#define APPLICATION_MODEL_PRIV_H_

/* -- Include files --------------------------------------------------------- */

#include <application_model_types.h>
#include <common_mem.h>
#include <common_types_complex.h>
#include <common_bitfields.h>
#include <string_manager.h>
#include <literal_manager.h>
#include <data_control_messaging_impl.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define INVALID_SEQ_NUMBER 0xFFFFu
#define DEPENDENCY_WORD_BITS (sizeof(APM_BlockDepencenyWord)*8)
#define DEPENDENCY_LENGTH_IN_WORDS (MAX_NUM_OF_BLOCKS / DEPENDENCY_WORD_BITS)
#define INVALID_NETWORK_ID MAX_NUM_OF_BLOCKS

/* -- Typedefs -------------------------------------------------------------- */

typedef uint16_t APM_BlockIndex;
typedef uint16_t APM_CommentIndex;
typedef uint16_t APM_ConnectionIndex;
typedef uint16_t APM_VariableIndex;

typedef uint32_t APM_BlockDepencenyWord;

/**
 * Bitfield containing flags indicating that from which other blocks has this
 * block incoming connection.
 */
typedef APM_BlockDepencenyWord APM_BlockDependency[DEPENDENCY_LENGTH_IN_WORDS];

/**
 * Matrix structure to hold the dependency information of all blocks
 */
typedef APM_BlockDependency APM_BlockDependencyTable[MAX_NUM_OF_BLOCKS];

/**
 * Execution order is a list of commands to be executed by the interpreter
 */
typedef struct
{
  APM_Command commands[APM_MAX_NUM_OF_NETWORK_ITEMS];
} APM_ExecutionOrder;

typedef struct
{
  CMN_DataType dataType;           /**< Data type */
  DPM_LiteralHandle literalHandle; /**< Literal handle */
  DPM_StringHandle stringHandle;   /**< String handle */
} APM_InitValue;

typedef struct
{
  CMN_VariableHandle handle; /**< the handle (='instance-ID' )of the variable (0 indicates an invalid item, added by application model) */
  DPM_StringHandle name;     /**< Name of the Variable */
  APM_InitValue initValue;   /**< Initial value */
  CMN_Size arraySize;        /**< Array size (for arrays: arraySize > 1) */
} APM_VariableData;

typedef struct
{
  CMN_CommentHandle handle; /**< The handle of the item (0 indicates an invalid item, added by application model). */
  DPM_StringHandle text; /** Comment Text. */
  CMN_Rectangle box; /**< Comment canvas. */
} APM_CommentData;

typedef struct
{
  CMN_ConnectionHandle handle; /**< The handle of the item (0 indicates an invalid item, added by application model). */
  CMN_BlockHandle inBlock; /**< Input block handle. */
  CMN_PinHandle inPin; /**< Input pin handle. */
  CMN_BlockHandle outBlock; /**< Output block handle. */
  CMN_PinHandle outPin; /**< Output pin handle. */
  CMN_DimensionDiff lineLengths[CMN_MAX_LINES_PER_CONNECTION]; /**< lengths of the segments (alternating x and y), terminated by zero. */
} APM_ConnectionData;

typedef struct
{
  LP_LibraryBlockIdx blockIdx;
  DPM_StringHandle fbName;
} APM_FbBlock;

typedef struct
{
  CMN_IoDescrListIdx ioIndex;
  DPM_StringHandle ioName;
} APM_IoBlock;

typedef enum
{
  APM_IndexTypeLiteral = 0,   /**< The array index is a literal*/
  APM_IndexTypeVariable   /**< The array index is a variable*/
} APM_ArrayIndexType;

typedef struct
{
  CMN_VariableHandle arrayHandle;       /**< Handle of the array variable*/
  APM_ArrayIndexType indexType;         /**< Type of the array index*/
  union
  {
    DPM_LiteralHandle litIndexHandle;   /**< Handle of the literal in case of literal index type*/
    CMN_VariableHandle varIndexHandle;  /**< Handle of the variable in case of variable index type*/
  } indexHandle;
  DPM_StringHandle arrayElementName;
} APM_ArrayElement;

typedef struct
{
  CMN_BlockHandle handle; /**< The handle of the item (0 indicates an invalid item, added by application model) */
  union
  {
    APM_FbBlock fb;
    CMN_VariableHandle variableHandle;
    APM_LiteralData literalData;
    APM_IoBlock io;
    APM_ArrayElement arrayElement;
  } classId;
  CMN_BlockType blockType; /**< Block type. */
  CMN_DataType dataType; /**< Data type. */
  CMN_Rectangle geometry; /**< Block geometry information. */
} APM_BlockData;

struct tag_APM_Instance
{
  APM_BlockData blocks[MAX_NUM_OF_BLOCKS];
  APM_ConnectionData connections[MAX_NUM_OF_CONNECTIONS];
  APM_VariableData variables[MAX_NUM_OF_VARIABLES];
  APM_CommentData comments[MAX_NUM_OF_COMMENTS];

  APM_ExecutionOrder executionOrder;
};

typedef struct
{
  APM_BlockIndex stack[MAX_NUM_OF_BLOCKS];
  CMN_Size size;
} APM_BlockStack;

/* -- Prototypes ------------------------------------------------------------ */

APM_Rc APM_internalGetLibraryIdxByClassId(CMN_ClassId aClassId, LP_LibraryBlockIdx* aIdx);

APM_Rc APM_internalGetLibraryBlockNameByIdx(LP_LibraryBlockIdx aBlockIdx, char const** aName);

APM_Rc APM_internalGetBlockName(SRTS_ContextPtr aContext, CMN_BlockHandle aHandle, char const** aName);

void APM_internalClearBlockStack(APM_BlockStack *aBlockStack);

void APM_internalPushToBlockStack(APM_BlockStack *aBlockStack, APM_BlockIndex aBlockIdx);

void APM_internalPopFromBlockStack(APM_BlockStack *aBlockStack, APM_BlockIndex *aBlockIdx);

APM_Rc APM_internalGetPinName(
    APM_BlockData const* aBlock,
    CMN_PinHandle aPin,
    LP_ConstCStr* aLibraryPinName,
    CMN_PinDirection aPinDirection
    );

APM_Rc APM_internalCheckPinName(
    APM_BlockData const* aBlock,
    CMN_PinHandle aPin,
    LP_ConstCStr aPinName,
    CMN_PinDirection aPinDirection
    );

APM_Rc APM_internalGetEndpointDataType(
    APM_InstancePtr const aInstance,
    CMN_BlockHandle aBlock,
    CMN_PinHandle aPin,
    CMN_PinDirection aPinDirection,
    CMN_DataType* aDataType);

APM_Rc APM_internalSendBlockRelatedConnectionsDrawingInstructions(
    APM_InstancePtr const aInstance,
    CMN_BlockHandle aHandle,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

APM_Rc APM_internalGetOperandInfo(
    APM_InstancePtr const aInstance,
    CMN_BlockHandle aBlockHandle,
    CMN_Bool aIsInputPin,
    CMN_PinHandle aPin,
    APM_OperandPtr aOperand);

#endif /* APPLICATION_MODEL_PRIV_H_ */
