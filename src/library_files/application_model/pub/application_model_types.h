/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_TYPES_H_
#define APPLICATION_MODEL_TYPES_H_

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>
#include <common_types.h>
#include <library_provider.h>
#include <string_manager.h>
#include <literal_manager.h>

#include <stdint.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define APM_MAX_NUM_OF_NETWORK_ITEMS MAX_NUM_OF_BLOCKS + MAX_NUM_OF_CONNECTIONS

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Return code for application manager API functions.
 * Return codes greater or equal to 0 are success codes, codes less than 0 indicate that an error has occurred.
 */
typedef CMN_Rc APM_Rc;

typedef uint32_t APM_CommandSeqIterator;
typedef uint8_t APM_OperandType;
#define APM_OPERAND_TYPE_INVALID                  0u
#define APM_OPERAND_TYPE_VAR                      1u
#define APM_OPERAND_TYPE_BLOCK_INPUT              2u
#define APM_OPERAND_TYPE_BLOCK_OUTPUT             3u
#define APM_OPERAND_TYPE_OUTPUT_PIN_OF_INPUT_IO   4u
#define APM_OPERAND_TYPE_INPUT_PIN_OF_OUTPUT_IO   5u
#define APM_OPERAND_TYPE_LITERAL                  6u
#define APM_OPERAND_TYPE_ARRAY_IDXBY_LITERAL      7u
#define APM_OPERAND_TYPE_ARRAY_IDXBY_VARIABLE     8u
#define APM_OPERAND_TYPE_OUTPUT_PIN_OF_OUTPUT_IO  9u

#define APM_CMD_TYPE_INVALID             0u
#define APM_CMD_TYPE_CALL                1u
#define APM_CMD_TYPE_ASSIGNEMNT          2u
typedef uint8_t APM_CommandType;

typedef union
{
  CMN_Bool vbool;
  CMN_SafeBool vsafebool;
  uint8_t vuint8;
  int8_t vint8;
  uint16_t vuint16;
  int16_t vint16;
  uint32_t vuint32;
  int32_t vint32;
  uint64_t vuint64;
  int64_t vint64;
  CMN_Real32 vfloat;
  CMN_Real64 vdouble;
} APM_Literal;

typedef APM_Literal* APM_LiteralPtr;

typedef struct
{
  CMN_DataType datatype;
  APM_Literal value;
  DPM_StringHandle literalString;
} APM_LiteralData;

typedef APM_LiteralData* APM_LiteralDataPtr;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  LP_LibraryBlockIdx libBlockIdx;
} APM_BlockCodeInfos;

typedef APM_BlockCodeInfos* APM_BlockCodeInfosPtr;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  CMN_DataType dataType; /**< data type of variable */
  APM_LiteralPtr initValue; /**<  pointer to init value of variable. */
  CMN_Size arraySize; /**< Array size (for arrays: arraySize > 1) */
} APM_VariableCodeInfos;

typedef APM_VariableCodeInfos* APM_VariableCodeInfosPtr;

typedef struct
{
  CMN_Count varIndex;
} APM_VarIdentifier;

typedef struct
{
  CMN_Count blockIndex;
  LP_PinListIdx pin; /**< zero-based for each operandType (block inputs and block outputs) */
} APM_PinIdentifier;

typedef struct
{
  CMN_IoDescrListIdx ioIndex; /**< index of the IO */
} APM_IOIdentifier;

typedef CMN_Count APM_LiteralIndex;

typedef struct
{
  APM_VarIdentifier arrayIdentifier;  /**< identifier of the array variable */
  DPM_LiteralHandle literalHandle; /**< handle for the literal value used to index the array */
} APM_ArrayIdxByLiteralIdentifier;

typedef struct
{
  APM_VarIdentifier arrayIdentifier;  /**< identifier of the array variable */
  APM_VarIdentifier varIdentifier;  /**< identifier of the variable used to index the array */
} APM_ArrayIdxByVariableIdentifier;

typedef struct
{
  APM_OperandType operandType;
  union
  {
    APM_VarIdentifier varIdentifier;
    APM_PinIdentifier pinIdentifier;
    APM_IOIdentifier ioIdentifier;
    APM_LiteralIndex literalIdentifier;
    APM_ArrayIdxByLiteralIdentifier arrayIdxByLiteralIdentifier;
    APM_ArrayIdxByVariableIdentifier arrayIdxByVariableIdentifier;
  } operandIdentifier;
} APM_Operand;
typedef APM_Operand* APM_OperandPtr;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  APM_Operand src;
  APM_Operand dst;
} APM_ConnectionCodeInfos;

typedef APM_ConnectionCodeInfos* APM_ConnectionCodeInfosPtr;

typedef struct
{
  APM_CommandType cmdType;
  CMN_Count index; /* to be used with APM_getBlock or APM_getConnection depending on type */
  CMN_SequenceNumber seqNumber;   /* Command sequence number; used by the interpreter to be able to execute block steps */
} APM_Command;

typedef APM_Command const* APM_CommandPtr;

/* -- Prototypes ------------------------------------------------------------ */

#endif /* APPLICATION_MODEL_TYPES_H_ */
