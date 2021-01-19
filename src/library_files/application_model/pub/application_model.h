/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_H_
#define APPLICATION_MODEL_H_

/* -- Include files --------------------------------------------------------- */

#include <application_model_types.h>
#include <common_rc.h>
#include <common_types.h>
#include <common_types_complex.h>
#include <data_control_messaging_impl.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Iterate through variables in the model.
 *
 * Fills the buffer and returns meta-data. For the first call, the argument "iterator" must be set to 0. The subsequent iterator value is
 * set to aNextIterator, where 0 value indicates the last element.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIterator iterator
 * @param aItem returned variable
 * @param aNextIterator next iterator value
 * @return error code
 * @retval EINVAL Invalid Iterator
 */
APM_Rc APM_iterateVariable(
    SRTS_ContextPtr aContext,
    CMN_VariableIterator aIterator,
    CMN_DataInterfaceExtVariable* aItem,
    CMN_VariableIterator* aNextIterator);

/**
 * Get code infos of variable.
 *
 * Note that enabled flag of returned variable code infos may be false.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIndex index of variable. Range is zero to (#MAX_NUM_OF_VARIABLES - 1).
 * @param aVariable variable code infos
 * @return return code
 * @retval #CMN_ENULLPTR variable code infos pointer is NULL
 * @retval #CMN_EINVAL index out of range
 * @retval #APM_OK
 */
APM_Rc APM_getVariableCodeInfos(SRTS_ContextPtr aContext, CMN_Count aIndex, APM_VariableCodeInfosPtr aVariable);

/**
 * Iterate through blocks in the model.
 *
 * Fills the buffer and returns Meta-data. For the first call, the argument "iterator" must be set to 0. The subsequent iterator value is
 * set to aNextIterator, where 0 value indicates the last element.
 * If the Data Interface contains pointers, the data is placed in the buffer space defined by "BufferDesc varBuffer" and the pointers point into that
 * buffer space. If there are more than one components to be handled that way, they all share the same buffer.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIterator iterator
 * @param aItem returned block
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param aNextIterator next iterator value
 * @return error code
 * @retval EINVAL Invalid Iterator
 */
APM_Rc APM_iterateBlock(
    SRTS_ContextPtr aContext,
    CMN_BlockIterator aIterator,
    CMN_DataInterfaceExtBlock* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_BlockIterator* aNextIterator);

/**
 * Get code infos of block.
 *
 * Note that enabled flag of returned block code infos may be false.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIndex index of block. Range is zero to (#MAX_NUM_OF_BLOCKS - 1).
 * @param aVariable block code infos
 * @return return code
 * @retval #CMN_ENULLPTR block code infos pointer is NULL
 * @retval #CMN_EINVAL index out of range
 * @retval #APM_OK
 */
APM_Rc APM_getBlockCodeInfos(SRTS_ContextPtr aContext, CMN_Count aIndex, APM_BlockCodeInfosPtr aBlock);

/**
 * Iterate through connections in the model.
 *
 * Fills the buffer and returns meta-data. For the first call, the argument "iterator" must be set to 0. The subsequent iterator value is
 * set to aNextIterator, where 0 value indicates the last element.
 * If the Data Interface contains pointers, the data is placed in the buffer space defined by "BufferDesc varBuffer" and the pointers point into that
 * buffer space. If there are more than one components to be handled that way, they all share the same buffer.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIterator iterator
 * @param aItem returned connection
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param aNextIterator next iterator value
 * @return error code
 * @retval EINVAL Invalid Iterator
 */
APM_Rc APM_iterateConnection(
    SRTS_ContextPtr aContext,
    CMN_ConnectionIterator aIterator,
    CMN_DataInterfaceExtConnection* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_ConnectionIterator* aNextIterator);

/**
 * Get code infos of connection.
 *
 * Note that enabled flag of returned connection code infos may be false.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIndex index of connection. Range is zero to (#MAX_NUM_OF_CONNECTIONS - 1).
 * @param aVariable connection code infos
 * @return return code
 * @retval #CMN_ENULLPTR connection code infos pointer is NULL
 * @retval #CMN_EINVAL index out of range
 * @retval #APM_OK
 */
APM_Rc APM_getConnectionCodeInfos(SRTS_ContextPtr aContext, CMN_Count aIndex, APM_ConnectionCodeInfosPtr aConnection);


/**
 * Iterate through command sequence.
 *
 * Fills a pointer to the next command in the command sequence. For the first call, the argument "iterator" must be set to 0.
 * The subsequent iterator value is set to aNextIterator, where 0 value indicates the last element.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIterator iterator
 * @param aCurCommand returned command
 * @param aNextIterator next iterator value
 * @return return code
 * @retval #CMN_ENULLPTR A parameter was NULL
 * @retval #EINVAL Invalid Iterator
 * @retval #APM_OK
 */
APM_Rc APM_iterateCommandSeq(
    SRTS_ContextPtr aContext,
    APM_CommandSeqIterator aIterator,
    APM_CommandPtr* aCurCommand,
    APM_CommandSeqIterator* aNextIterator);

/**
 *
 * Get memory footprint of a variable
 *
 * @param aContext pointer the SRTS context instance
 * @param varIdx index of the variable in the application model
 * @retval aSize The size of the array according to the data type
 * @return CMN_Rc error code
 */
APM_Rc APM_getVariableSize(SRTS_ContextPtr aContext, CMN_Count aVarIdx, CMN_Size* aSize);

/**
 *
 * Get size of data type
 *
 * @param aContext pointer the SRTS context instance
 * @retval aSize The size of a variable of this data type
 * @return APM_Rc error code
 * @retval APM_OK
 * @retval APM_DATA_TYPE_SIZE_ERROR
 */
APM_Rc APM_getDataTypeValueSize(SRTS_ContextPtr aContext, CMN_DataType aType, CMN_Size* aSize);

/**
 * Get the color of a data type.
 *
 * @param aType the data type
 * @return color of the data type or zero for unknown data type
 */
CMN_RGBA_Color APM_getDataTypeColor(CMN_DataType aType);

/**
 * Erases all contents of the application model.
 *
 * Resets the 'Application model' to an initial state.
 *
 * @param aContext pointer the SRTS context instance
 * @return APM_Rc error code
 */
APM_Rc APM_clear(SRTS_ContextPtr aContext);

/**
 * Adds a block to the application model.
 *
 * - Adds a new component to the model and returns a handle to the new component.
 * - A new block with the informations, passed in the DataInterfaceBlock will be created in the application model. Note: no connections are involved
 *   at that time yet.
 * - For IOs, no checks for availability take place at that time. This is performed later.
 * - For FBs, "name" refers to the class name. The instance of the FB is anonymous.
 * - Upon unsuccessful operation, a handle to the created block will be returned.
 * - When an FB is added, additional Information from the Library provider is acquired (e.g. inputs and outputs of the FB) and this combined
 *   information is passed to the Application Model.
 *
 * Note: To include a block into the processing flow, all inputs have to be connected by "connection"-elements
 *
 * Caveats:
 * - String are to be managed in a separate String Manager object.
 * - Memory is to be acquired from the Data Pool Manager. The Data Pool Manager is initially provided with a big block of memory and it administers
 *   that block autonomously..
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aData Structure which contains all input data for the model.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param[out] aHandle Handle of the created block.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENODEV The FB-type does not exist or referenced IO-Name or Variable Name does not exist.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval APM_EINVAL_IO The IO was not found in system layer.
 */
APM_Rc APM_addBlock(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceBlock const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_BlockHandle* aHandle);

/**
 * Removes a block from the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Block handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_deleteBlock(SRTS_ContextPtr aContext, CMN_BlockHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing block of the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Block handle,  the value which was returned from DIM_addBlock.
 * @param aData Structure which contains all input data for the model modification.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENODEV The FB-type does not exist or referenced IO-Name or Variable Name does not exist
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval ENOENT The handle does not represent a valid item.
 * @retval APM_EINVAL_IO The IO was not found in system layer.
 */
APM_Rc APM_modifyBlock(
    SRTS_ContextPtr aContext,
    CMN_BlockHandle aHandle,
    CMN_DataInterfaceBlock const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Updates and verifies all IO blocks.
 *
 * Updates the IO indices of all IOs, because the IO indices could have been changed by
 * a changed IO system layer configuration.
 *
 * Verifies, that for each IO block the identical IO exists in system layer.
 * (IO name, data type, and io direction must be equal)
 *
 * @param aContext pointer the SRTS context instance
 * @return Error code.
 * @retval APM_EINVAL_IO An IO could not be found in system layer. (i.e. IO is deleted
 *                       or changed in new system layer IO configuration)
 * @retval APM_ENULL
 */
APM_Rc APM_updateAndVerifyIoBlocks(SRTS_ContextPtr aContext);

/**
 * Adds a new connection to the model, returns the handle.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aData Structure which contains all input data for the model.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param[out] aHandle Handle of the created connection.
 * @return Error code.
 * @retval ENODEV The FB-type does not exist or referenced IO-Name or Variable Name does not exist
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 */
APM_Rc APM_addConnection(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceConnection const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_ConnectionHandle* aHandle);

/**
 * Removes a connection from the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Connection handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_deleteConnection(SRTS_ContextPtr aContext, CMN_ConnectionHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing connection in the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Connection handle,  the value which was returned from DIM_addConnection.
 * @param aData Structure which contains all input data for the model modification.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_modifyConnection(
    SRTS_ContextPtr aContext,
    CMN_ConnectionHandle aHandle,
    CMN_DataInterfaceConnection const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Adds a new comment to the model.
 * @param aContext pointer the SRTS context instance
 * @param aData Structure which contains all input data for the model.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param[out] aHandle Handle of the created comment.
 * @return Error code.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 */
APM_Rc APM_addComment(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceComment const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_CommentHandle* aHandle);

/**
 * Deletes a comment from the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Comment handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_deleteComment(SRTS_ContextPtr aContext, CMN_CommentHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing comment in the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Comment handle,  the value which was returned from DIM_addComment.
 * @param aData Structure which contains all input data for the model modification.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_modifyComment(
    SRTS_ContextPtr aContext,
    CMN_CommentHandle aHandle,
    CMN_DataInterfaceComment const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Iterate through comments in the model.
 *
 * Fills the buffer and returns meta-data. For the first call, the argument "iterator" must be set to 0. The subsequent iterator value is
 * set to aNextIterator, where 0 value indicates the last element.
 * If the Data Interface contains pointers, the data is placed in the buffer space defined by "BufferDesc varBuffer" and the pointers point into that
 * buffer space. If there are more than one components to be handled that way, they all share the same buffer.
 *
 * @param aContext pointer the SRTS context instance
 * @param aIterator iterator
 * @param aItem returned comment
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @param aNextIterator next iterator value
 * @return error code
 * @retval EINVAL Invalid Iterator
 */
APM_Rc APM_iterateComment(
    SRTS_ContextPtr aContext,
    CMN_CommentIterator aIterator,
    CMN_DataInterfaceExtComment* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_CommentIterator* aNextIterator);

/**
 * Adds a new variable instance to the model. No graphical output.
 *
 * @param aContext pointer the SRTS context instance
 * @param aData
 * @param[out] aHandle Handle of the created variable.
 * @return Error code.
 */
APM_Rc APM_addVariable(SRTS_ContextPtr aContext, CMN_DataInterfaceVariable const* aData, CMN_VariableHandle* aHandle);

/**
 * Deletes a variable from the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Variable handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_deleteVariable(SRTS_ContextPtr aContext, CMN_VariableHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing variable in the model.
 *
 * @req{SAFE-3612}
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Variable handle, the value which was returned from DIM_addVariable.
 * @param aData Structure which contains all input data for the model modification.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval ENOENT The handle does not represent a valid item.
 */
APM_Rc APM_modifyVariable(SRTS_ContextPtr aContext, CMN_VariableHandle aHandle, CMN_DataInterfaceVariable const* aData);

/**
 * Get code infos of Literals
 *
 * @param aContext pointer the SRTS context instance
 * @param aIndex index of literal. Range is zero to (#MAX_NUM_OF_BLOCKS - 1).
 * @param aLiteral literal code infos
 * @param aIsEnabled CMN_TRUE, if this block is a literal
 * @return return code
 * @retval #CMN_ENULLPTR literal code infos pointer or aIsEnabled is NULL
 * @retval #CMN_EINVAL index out of range
 * @retval #APM_OK
 */
APM_Rc APM_getLiteralCodeInfos(SRTS_ContextPtr aContext, CMN_Count aIndex, APM_LiteralDataPtr aLiteral, CMN_Bool* aIsEnabled);

/**
 * Find the index of the variable represented by the given block
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle [in] handle of the variable block
 * @param aIndex [out] index of the variable
 * @retval CMN_ENULLPTR if aIndex is NULL
 * @retval CMN_EINVAL if the block handle is invalid or the block is not of type VARIABLE
 * @retval APM_OK
 */
APM_Rc APM_getVariableIndex(SRTS_ContextPtr aContext, CMN_BlockHandle aHandle, CMN_UnsignedIndex* aIndex);

/**
 * Find the index of the block
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle [in] handle of the variable block
 * @param aIndex [out] index of the variable
 * @retval CMN_ENULLPTR if aIndex is NULL
 * @retval CMN_EINVAL if the block handle is invalid or the block is not of type FB
 * @retval APM_OK
 */
APM_Rc APM_getBlockIndex(SRTS_ContextPtr aContext, CMN_BlockHandle aHandle, CMN_UnsignedIndex* aIndex);

/**
 * Parse the string literal in aLiteralStr to aLietarValue according to the given data type. This function
 * does not execute any validation.
 *
 * @param aLiteralStr [in] the string literal
 * @param aDataType [in] the expected datatype
 * @param aLiteralValue [out] the literal value
 */
void APM_parseLiteral(SRTS_ContextPtr aSrtsContext, char const* aLiteralStr, CMN_DataType aDataType, APM_LiteralPtr aLiteralValue);

/**
 * Compute the execution order.
 *
 * @req{SAFE-3575}
 * @param aContext pointer the SRTS context instance
 * @retval APM_ENOTDAG
 * @retval APM_ENULL
 * @retval APM_OK
 */
APM_Rc APM_computeExecutionOrder(SRTS_ContextPtr aContext);

#endif /* APPLICATION_MODEL_H_ */
