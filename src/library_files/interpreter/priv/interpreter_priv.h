/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef INTERPRETER_PRIV_H
#define INTERPRETER_PRIV_H

/* -- Include files --------------------------------------------------------- */
#include <interpreter.h>
#include <interpreter_types.h>
#include <library_provider_types.h>
#include <common_types.h>
#include <common_types_complex.h>
#include <application_model_types.h>

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  CMN_Offset instanceDataOffset; /**< offset to block instance data, relative to instance data base pointer */
  LP_LibraryBlockIdx libBlockIdx;
} INP_Call_Metadata;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  CMN_Offset instanceDataOffset; /**< offset to variable instance data, relative to instance data base pointer */
} INP_Var_Metadata;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  CMN_Offset instanceDataOffset; /**< offset to literal instance data, relative to instance data base pointer */
} INP_Literal_Metadata;

typedef struct
{
  CMN_Bool enabled; /* CMN_True, if enabled */
  CMN_Offset src; /**< offset to assignment source, relative to instance data base pointer */
  CMN_Offset dst; /**< offset to assignment destination, relative to instance data base pointer */
  CMN_Size size; /**< size in bytes to be copied */
} INP_Assignment_Metadata;

/* -- Typedefs -------------------------------------------------------------- */
struct tag_INP_Context
{
  INP_Call_Metadata metadataCalls[MAX_NUM_OF_BLOCKS]; /**< calls (blocks) metadata array */
  INP_Var_Metadata metadataVars[MAX_NUM_OF_VARIABLES]; /**< variables metadata array */
  INP_Literal_Metadata metadataLiterals[MAX_NUM_OF_BLOCKS]; /**< literals metadata array */
  INP_Assignment_Metadata metadataAssignments[MAX_NUM_OF_CONNECTIONS]; /**< assignments (connections) metadata array */
  CMN_Offset entryPointData; /**< offset to entry point instance, relative to interpreter context pointer */
  CMN_Offset instanceDataBase; /**< offset to instance data of blocks and variables (instance data base offset),
   relative to interpreter context pointer */
  APM_CommandSeqIterator commandIterator; /**< actual program position in the command sequence */
  CMN_SequenceNumber commandBlockSeqNum; /**< Command block sequence number for block stepping */
};

/* -- Functions ------------------------------------------------------------- */

INP_Rc INP_getOperandDataTypeAndOffset(SRTS_ContextPtr aCtx, APM_Operand const* aOperandPtr, CMN_DataType* aDataTypePtr, CMN_Offset* aOffsetPtr);
INP_Rc INP_executeNextCommand(SRTS_ContextPtr aSrtsContext, INP_ContextPtr aInpContext);

/**
 * Calculates the command block sequence number for the current command.
 *
 * @req{SAFE-3575}
 * @param aSrtsContext [in] the SRTS context pointer
 * @param aInpContext [in] the interpreter context pointer
 * @retval #INP_ENULL
 * @retval #INP_EAPM
 * @retval #INP_OK
 */
INP_Rc INP_calcCommandBlockSequenceNumber(SRTS_ContextPtr aSrtsContext, INP_ContextPtr aInpContext);

#endif /* INTERPRETER_PRIV_H */
