/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCAPPLICATIONMODEL_H_
#define DCAPPLICATIONMODEL_H_

/* -- Include files --------------------------------------------------------- */

#include <common_types_complex.h>
#include <dc_types.h>
#include <system_layer_types.h>
#include <data_control_messaging_impl.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup AM Application Model
 *
 * @brief Application Model
 *
 * A "block" represents an FB or an assignment. When used for FBs, the block represents the instance of the Fb as well as its invocation. When used
 * for variables or IOs, a block represents only the assignment, not the instance. If variables or IOs are used as blocks, the instances have to be
 * declared previously.
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Erases all contents of the application model.
 *
 * Resets the 'Application model' to an initial state.
 *
 * @param aContext pointer the SRTS context instance
 * @return DC_Rc error code
 */
DC_Rc DC_clearApplicationModel(SRTS_ContextPtr aContext);

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
 */
DC_Rc DC_addBlock(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceBlock const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_BlockHandle* aHandle);

/**
 * Removes a block from the model.
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Block handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
DC_Rc DC_deleteBlock(SRTS_ContextPtr aContext, CMN_BlockHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing block of the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Block handle,  the value which was returned from DC_addBlock.
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
 */
DC_Rc DC_modifyBlock(
    SRTS_ContextPtr aContext,
    CMN_BlockHandle aHandle,
    CMN_DataInterfaceBlock const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

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
DC_Rc DC_iterateBlock(
    SRTS_ContextPtr aContext,
    CMN_BlockIterator aIterator,
    CMN_DataInterfaceExtBlock* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_BlockIterator* aNextIterator);

/**
 * Adds a new connection to the model, returns the handle.
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
DC_Rc DC_addConnection(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceConnection const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_ConnectionHandle* aHandle);

/**
 * Removes a connection from the model.
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Connection handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
DC_Rc DC_deleteConnection(SRTS_ContextPtr aContext, CMN_ConnectionHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing connection in the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Connection handle,  the value which was returned from DC_addConnection.
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
DC_Rc DC_modifyConnection(
    SRTS_ContextPtr aContext,
    CMN_ConnectionHandle aHandle,
    CMN_DataInterfaceConnection const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Iterate through connections in the model.
 *
 * Fills the buffer and returns meta-data. For the first call, the argument "iterator" must be set to 0.The subsequent iterator value is
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
DC_Rc DC_iterateConnection(
    SRTS_ContextPtr aContext,
    CMN_ConnectionIterator aIterator,
    CMN_DataInterfaceExtConnection* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_ConnectionIterator* aNextIterator);

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
DC_Rc DC_addComment(
    SRTS_ContextPtr aContext,
    CMN_DataInterfaceComment const* aData,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_CommentHandle* aHandle);

/**
 * Deletes a comment from the model.
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Comment handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
DC_Rc DC_deleteComment(SRTS_ContextPtr aContext, CMN_CommentHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing comment in the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Comment handle,  the value which was returned from DC_addComment.
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
DC_Rc DC_modifyComment(
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
DC_Rc DC_iterateComment(
    SRTS_ContextPtr aContext,
    CMN_CommentIterator aIterator,
    CMN_DataInterfaceExtComment* aItem,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_ConnectionIterator* aNextIterator);

/**
 * Adds a new variable instance to the model. No graphical output.
 * @param aContext pointer the SRTS context instance
 * @param aData
 * @param[out] aHandle Handle of the created variable.
 * @return Error code.
 */
DC_Rc DC_addVariable(SRTS_ContextPtr aContext, CMN_DataInterfaceVariable const* aData, CMN_VariableHandle* aHandle);

/**
 * Deletes a variable from the model.
 *
 * @param aContext pointer the SRTS context instance
 * @param aHandle Variable handle.
 * @param aSendDICtx Context for sending drawing instruction using DCM API.
 * @return Error code.
 * @retval ENOENT The handle does not represent a valid item.
 */
DC_Rc DC_deleteVariable(SRTS_ContextPtr aContext, CMN_VariableHandle aHandle, DCM_SendDrawingInstructionCtx const* aSendDICtx);

/**
 * Modifies an existing variable in the model.
 * @param aContext pointer the SRTS context instance
 * @param aHandle Variable handle, the value which was returned from DC_addVariable.
 * @param aData Structure which contains all input data for the model modification.
 * @return Error code.
 * @retval EDOM The specified literal is not valid for the specified data type.
 * @retval ENOMEM Resource problems.
 * @retval EINVAL Enumeration values beyond definition range.
 * @retval EACCESS The desired data type cannot be handled here.
 * @retval EDOM a literal value does not match the type definition.
 * @retval ENOENT The handle does not represent a valid item.
 */
DC_Rc DC_modifyVariable(SRTS_ContextPtr aContext, CMN_VariableHandle aHandle, CMN_DataInterfaceVariable const* aData);

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
DC_Rc DC_iterateVariable(
    SRTS_ContextPtr aContext,
    CMN_VariableIterator aIterator,
    CMN_DataInterfaceExtVariable* aItem,
    CMN_VariableIterator* aNextIterator);

/**
 * Triggers the computation of the block execution order. After successful execution, sequence number of the
 * blocks can be retrieved through the iterator API.
 *
 * @req{SAFE-3610}
 * @req{SAFE-3597}
 *
 * @param aContext pointer the SRTS context instance
 * @return error code
 * @retval ENULL aContext is NULL
 * @retval ENOTEXECUTABLE sort order cannot be determined (
 */
DC_Rc DC_computeSortOrder(SRTS_ContextPtr aContext);

/**
 * Iterates on the sequence number mapping of the blocks. Each entry consists of a block handle and its assigned
 * sequence number, which denotes the order in which the commands related to that particular block is executed.
 *
 * Note: The entries are returned in the order of the sequence numbers which may differ from the order of the blocks
 * are defined.
 *
 * Note: Empty list is returned if sequence order is not available. (aNextIterator = 0 upon aIterator = 0)
 *
 * @req{SAFE-3611}
 * @req{SAFE-3597}
 * @req{SAFE-3613}
 *
 * @param[in] aContext pointer the SRTS context instance
 * @param[in] aIterator iterator
 * @param[out] aBlockHandle the handle of the assigned block
 * @param[out] aSequenceNumber the assigned sequence number of the block
 * @param[out] aNextIterator next value of the iterator. Zero value denotes end of list, in this case the returned block and sequence numbers are invalid.
 * @return error code
 * @retval ENULL aContext is NULL
 */
DC_Rc DC_iterateSortOrder(
    SRTS_ContextPtr aContext,
    CMN_SequenceNumberIterator aIterator,
    CMN_BlockHandle *aBlockHandle,
    CMN_SequenceNumber *aSequenceNumber,
    CMN_SequenceNumberIterator *aNextIterator);

/*@}*//* Application Model */

/*@}*//* DCA Data Control API */

#endif
