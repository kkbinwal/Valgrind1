/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DATA_POOL_MANAGER_H_
#define DATA_POOL_MANAGER_H_

/* -- Include files ---------------------------------------------------------- */
#include <common_rc.h>
#include <common_types.h>
#include <system_layer.h>
#include <string_manager.h>

/* -- Externals -------------------------------------------------------------- */

/* -- Defines ---------------------------------------------------------------- */
#define DPM_RC_OK       CMN_DPM_RC_BASE           /**< No error occurred.   */
#define DPM_RC_ERROR    (CMN_DPM_RC_BASE + 0x1u)  /**< An error occurred.   */
#define DPM_RC_NOTIMPL  (CMN_DPM_RC_BASE + 0x2u)  /**< Not implemented yet. */
#define DPM_RC_EMM      (CMN_DPM_RC_BASE + 0x3u)  /**< Memory manager error */

/* -- Typedefs --------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------- */

CMN_Rc DPM_init(SRTS_ContextPtr aCtx);
CMN_Rc DPM_destroy(SRTS_ContextPtr aCtx);

/* allocated in transient memory */
CMN_Rc DPM_allocate_safetyshell_context(SRTS_ContextPtr aCtx,
    CMN_BufferSize aBufSize, SSH_InstanceInfoPtr* aSshInstancePtrPtr);
CMN_Rc DPM_get_safetyshell_context(SRTS_ContextPtr aCtx, SSH_InstanceInfoPtr* aSshInstancePtrPtr);

CMN_Rc DPM_allocate_pil_context(SRTS_ContextPtr aCtx, CMN_BufferSize aBufSize, PIL_ContextPtr* aPILContextPtrPtr);
CMN_Rc DPM_get_pil_context(SRTS_ContextPtr aCtx, PIL_ContextPtr* aPILContextPtrPtr);

CMN_Rc DPM_allocate_interpreter_context(SRTS_ContextPtr aCtx,
    CMN_BufferSize aBufSize, INP_ContextPtr* aInpContextPtrPtr);
CMN_Rc DPM_get_interpreter_context(SRTS_ContextPtr aCtx, INP_ContextPtr* aInpContextPtrPtr);
CMN_Rc DPM_free_interpreter_context(SRTS_ContextPtr aCtx);

/* allocated in persistent memory */
CMN_Rc DPM_allocate_applicationmodel_context(SRTS_ContextPtr aCtx,
    CMN_BufferSize aBufSize, APM_InstancePtr* aApmInstancePtrPtr);
CMN_Rc DPM_get_applicationmodel_context(SRTS_ContextPtr aCtx, APM_InstancePtr* aApmInstancePtrPtr);
CMN_Rc DPM_clear_applicationmodel_context(SRTS_ContextPtr aCtx);

CMN_Rc DPM_allocate_stringmanager_context(SRTS_ContextPtr aCtx, CMN_BufferSize aBufSize,
    DPM_StringManager_ContextPtr* aSMContextPtrPtr);
CMN_Rc DPM_get_stringmanager_context(SRTS_ContextPtr aCtx,
    DPM_StringManager_ContextPtr* aSMContextPtrPtr, CMN_BufferSize* aStringBufferSize);
CMN_Rc DPM_clear_stringmanager_context(SRTS_ContextPtr aCtx);

CMN_Rc DPM_allocate_literalmanager_context(SRTS_ContextPtr aCtx,
    CMN_BufferSize aBufSize, DPM_LiteralManager_ContextPtr* aLMContextPtrPtr);
CMN_Rc DPM_get_literalmanager_context(SRTS_ContextPtr aCtx,
    DPM_LiteralManager_ContextPtr* aLMContextPtrPtr, CMN_BufferSize* aBufferSize);
CMN_Rc DPM_clear_literalmanager_context(SRTS_ContextPtr aCtx);

/**
 * Calculates the maximum array size in the transient memory.
 * Note: The output aMaxArraySize value shall be divided with the number of used arrays.
 *
 * @param aCtx pointer the SRTS context instance
 * @param aConstantPartsSize size of the constant elements (ideally the tested function block + the index variable)
 * @param aElementVarSize size of an array element
 * @param[out] aMaxArraySize the maximum array size which is fit to the free transient memory
 * @return Error code.
 */
CMN_Rc DPM_calculateMaxArraySize(SRTS_ContextPtr aCtx, CMN_BufferSize aConstantPartsSize, CMN_BufferSize aElementVarSize, CMN_Count* aMaxArraySize);

#endif /* DATA_POOL_MANAGER_H_ */

