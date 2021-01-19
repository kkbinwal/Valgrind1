/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef INTERPRETER_H
#define INTERPRETER_H

/* -- Include files --------------------------------------------------------- */
#include <interpreter_types.h>
#include <system_layer_types.h>
#include <application_model_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define INP_OK                    CMN_INP_RC_BASE           /**< successful function execution. */
#define INP_ENOTRUNNING           (CMN_INP_RC_BASE + 0x1u)  /**< The interpreter is not in running state. */
#define INP_EAPM                  (CMN_INP_RC_BASE + 0x2u)  /**< Error from application model. */
#define INP_ELP                   (CMN_INP_RC_BASE + 0x3u)  /**< Error from library provider. */
#define INP_EMEM                  (CMN_INP_RC_BASE + 0x4u)  /**< Error from data pool manager or memory manager. */
#define INP_EIO                   (CMN_INP_RC_BASE + 0x5u)  /**< Error from IO provider. */
#define INP_ENOEMNT               (CMN_INP_RC_BASE + 0x6u)  /**< No such element */
#define INP_EDATATYPES_NOT_EQUAL  (CMN_INP_RC_BASE + 0x7u)  /**< Assignment datatypes not equal. */
#define INP_ENOTSUPPORTED         (CMN_INP_RC_BASE + 0x8u)  /**< Not supported */
#define INP_ENULL                 (CMN_INP_RC_BASE + 0x9u)  /**< NULL pointer is not allowed*/
#define INP_EARRAYINDEX           (CMN_INP_RC_BASE + 0xAu)  /**< Array index exceeds array size */
#define INP_ETIMERFREQUENCY       (CMN_INP_RC_BASE + 0xBu)  /**< Library timer frequency does not match system timer frequency */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * State of the interpreter module.
 * This Enumeration represents the state of the interpreter module.
 */
typedef enum {
  INP_ExecutionStateNone = 0,           /**< The interpreter module is not allocated and initialized. */
  INP_ExecutionStateStopped = 1,        /**< The interpreter module is stopped. */
  INP_ExecutionStateRunning = 2,        /**< The interpreter module is running. */
  INP_ExecutionStatePaused = 3          /**< The interpreter module is paused. */
} INP_ExecutionState;

/* -- Prototypes ------------------------------------------------------------ */

/** @name SRTS interpreter */
/*@{*/

/**
 * This function is the constructor of the interpreter module.
 *
 * The initialization steps of the interpreter are handled in this function.
 *
 * The resulting state of the interpreter is #INP_ExecutionStateStopped.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aInpContextPtrPtr [in,out] pointer to the interpreter context pointer
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_EMEM
 * @retval #INP_ELP
 * @retval #INP_EAPM
 * @retval #INP_EIO
 * @retval #INP_EEMPTY
 */
INP_Rc INP_create(SRTS_ContextPtr aContext, INP_ContextPtr* aInpContextPtrPtr);

/**
 * This function gets the interpreter context from the srts context.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aInpContextPtrPtr [in,out] pointer to the interpreter context pointer
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_EMEM
 */
INP_Rc INP_get(SRTS_ContextPtr aContext, INP_ContextPtr* aInpContextPtrPtr);

/**
 * Initializes the function blocks and variables.
 *
 * Initialize function blocks: call init function for each block.
 * Initialze variables: for each variable copy init value to variable instance data.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aInpContextPtr [in] pointer to the interpreter context
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_EAPM
 * @retval #INP_ELP
 * @retval #INP_EMEM
 */
INP_Rc INP_initApplication(SRTS_ContextPtr aContext, INP_ContextPtr aInpContextPtr);

/**
 * Destructor of INP.
 *
 * Frees all memory resources of INP.
 *
 * The resulting state of the interpreter is #INP_ExecutionStateNone.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aInpContextPtrPtr [in] pointer to interpreter context pointer. interpreter context pointer will be reset to 0.
 * @return #INP_Rc return code
 * @retval #CMN_ENULLPTR
 * @retval #INP_EMEM
 */
INP_Rc INP_destroy(SRTS_ContextPtr aContext, INP_ContextPtr* aInpContextPtrPtr);

/** This function starts the execution of the interpreter
 *
 * In this function the the application program ('IEC-61331-code') is initialized,
 * checked, and execution is started.
 *
 * @param aContext [in] the SRTS context pointer
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_EAPM
 * @retval #INP_ELP
 * @retval #INP_EMEM
 */
INP_Rc INP_start(SRTS_ContextPtr aContext);

/**
 * This function executes one cycle in the interpreter module.
 *
 * This function executes one cycle of the program which has to be
 * previously 'started' and is in mode 'Running'.
 *
 * @req{SAFE-3576}
 * @param aContext [in] the SRTS context pointer
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ENOTRUNNING
 * @retval #INP_EAPM
 * @retval #INP_ELP
 * @retval #INP_EMEM
 */
INP_Rc INP_runCycle(SRTS_ContextPtr aContext);

/**
 * This function executes the next command block in the command sequence.
 *
 *  A command block is a group of commands that will be executed together.
 *
 * @req{SAFE-3575}
 * @param aContext [in] the SRTS context pointer
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ENOTRUNNING
 * @retval #INP_EAPM
 * @retval #INP_ELP
 * @retval #INP_EMEM
 */
INP_Rc INP_executeNextCommandBlock(SRTS_ContextPtr aContext);

/**
 * Retrieve current value of the command block sequence number. The command block sequence number
 *  denotes the next executed command block (group of commands that will be executed together) in the sequence.
 *
 * @req{SAFE-3575}
 * @param aContext [in] the SRTS context pointer
 * @param aCommandBlockSeqNum [out] the command block sequence number value
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ENOTRUNNING
 * @retval #INP_EAPM
 * @retval #INP_ELP
 * @retval #INP_EMEM
 */
INP_Rc INP_getCommandBlockSequenceNumber(SRTS_ContextPtr aContext, CMN_SequenceNumber* aCommandBlockSeqNum);

/**
 * This function retrieves the current value of a variable. This can only be called when the
 * application is currently running.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aIndex [in] the index of the variable
 * @param aDatatype [out] the data type of the variable
 * @param aValue [out] actual value of the variable
 * @param aArrayIndex [in] array index in case the variable is an array
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ENOTRUNNING
 * @retval #INP_EARRAYINDEX
 */
INP_Rc INP_getVariableValue(SRTS_ContextPtr aContext, CMN_Count aIndex, CMN_DataType* aDatatype, APM_LiteralPtr aValue, CMN_Count aArrayIndex);

/**
 * This function retrieves the current value of an output pin of a block. This can only be called when the
 * application is currently running.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aPinIdentifier [in] the block pin
 * @param aDatatype [out] the data type of the variable
 * @param aValue [out] actual value of the variable
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ELP
 * @retval #INP_ENOTRUNNING
 */
INP_Rc INP_getBlockOutputPinValue(SRTS_ContextPtr aContext, APM_PinIdentifier aPinIdentifier, CMN_DataType* aDatatype, APM_LiteralPtr aValue);

/**
 * This function sets the value of a variable. This can only be called when the
 * application is currently is in 'Running' or 'Paused' state.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aIndex [in] index of the variable
 * @param aValue [in] actual value of the pin
 * @param aArrayIndex [in] array index in case the variable is an array
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #INP_ENOEMNT
 * @retval #INP_ENOTRUNNING
 * @retval #INP_EARRAYINDEX
 */
INP_Rc INP_setVariableValue(SRTS_ContextPtr aContext, CMN_Count aIndex, APM_Literal aValue, CMN_Count aArrayIndex);

/**
 * This function sets the value of an input pin of a block. This can only be called when the
 * application is currently running.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aPinIdentifier [in] the block pin
 * @param aValue [in] value to be set
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ELP
 * @retval #INP_ENOTRUNNING
 */
INP_Rc INP_setBlockInputPinValue(SRTS_ContextPtr aContext, APM_PinIdentifier aPinIdentifier, APM_Literal aValue);

/**
 * This function sets the value of an output pin of a block. This can only be called when the
 * application is currently running.
 *
 * @param aContext [in] the SRTS context pointer
 * @param aPinIdentifier [in] the block output pin
 * @param aValue [in] value to be set
 * @return #INP_Rc return code
 * @retval #INP_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 * @retval #INP_ELP
 * @retval #INP_ENOTRUNNING
 */
INP_Rc INP_setBlockOutputPinValue(SRTS_ContextPtr aContext, APM_PinIdentifier aPinIdentifier, APM_Literal aValue);

INP_Rc INP_getLibraryBlockEnoValue(SRTS_ContextPtr aContext, CMN_Count aArrayIndex, APM_LiteralPtr aValue);

INP_Rc INP_setLibraryBlockEnoValue(SRTS_ContextPtr aContext, CMN_Count aArrayIndex, APM_Literal const* aValue);

/*@}*//* Text */

#endif /* INTERPRETER_H */
