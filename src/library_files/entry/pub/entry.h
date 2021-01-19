/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SRTS_DCM_API_H
#define SRTS_DCM_API_H

#include <common_rc.h>
#include <data_control_messaging.h>

#include <stddef.h>
#include <stdint.h>

/** @defgroup SRTS_ENTRY_API SRTS entry API
 *
 * @brief SRTS entry API
 *
 *@{*/

#if defined _WIN32 || defined __CYGWIN__
#define SRTSAPI_DLL_EXPORT __declspec(dllexport)
#define SRTSAPI_DLL_IMPORT __declspec(dllimport)
#elif __GNUC__
#define SRTSAPI_DLL_EXPORT __attribute__((visibility("default")))
#define SRTSAPI_DLL_IMPORT __attribute__((visibility("default")))
#else
#define SRTSAPI_DLL_EXPORT
#define SRTSAPI_DLL_IMPORT
#endif

#if defined(BUILDING_FOR_STATIC_LIBRARY)
#define SRTSAPI_DLL
#elif defined(BUILDING_FOR_SHARED_LIBRARY)
#define SRTSAPI_DLL SRTSAPI_DLL_EXPORT
#else
#define SRTSAPI_DLL SRTSAPI_DLL_IMPORT
#endif /* BUILDING_FOR_STATIC_LIBRARY, BUILDING_FOR_SHARED_LIBRARY */

#define ENTRY_OK        CMN_ENTRY_RC_BASE           /**< no error */
#define ENTRY_ESRTS     (CMN_ENTRY_RC_BASE + 0x1u)  /**< srts error */
#define ENTRY_EMSG      (CMN_ENTRY_RC_BASE + 0x2u)  /**< srts message send error */
#define ENTRY_ESYSTEM   (CMN_ENTRY_RC_BASE + 0x3u)  /**< system error */
#define ENTRY_ENOTIMPL  (CMN_ENTRY_RC_BASE + 0x4u)  /**< not implemented */
#define ENTRY_EINVAL    (CMN_ENTRY_RC_BASE + 0x5u)  /**< invalid value or state */
#define ENTRY_EIO       (CMN_ENTRY_RC_BASE + 0x6u)  /**< IO error */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * return code type of the entry interface
 */
typedef uint32_t ENTRY_Rc;

/**
 * Type of send message callback.
 *
 * Sends a message to the client.
 *
 * @param[in] aCtx User defined connection/session context.
 *                 context field of DCM_Connection is passed here.
 * @param[in] aData DCM Application Data to send.
 * @param[in] aLength Length of the data in bytes.
 * @return return code
 * @retval DCM_STATUS_CODE_OK Message was sent.
 * @retval DCM_STATUS_CODE_ERROR Message could not be sent.
 */
typedef uint32_t DCM_sendMessageCallback(CMN_VoidPtr aCtx, void const* aData, size_t aLength);

typedef uint32_t DCM_sendMessageBroadcastCallback(void const* aData, size_t aLength);

/**
 * Initialize the sRTS runtime system
 *
 * @return error code
 */
typedef ENTRY_Rc ENTRY_init_t(SRTS_ContextPtr aContextPtr);
/**
 * Function instance that initializes the sRTS runtime system.
 */
SRTSAPI_DLL ENTRY_init_t ENTRY_init;

/**
 * Execute a cycle (communication, execution of PLC code, ...)
 * of the sRTS runtime system
 *
 * @return error code
 */
typedef ENTRY_Rc ENTRY_cycle_t(SRTS_ContextPtr aSrtsContext);
/**
 * Function instance that executes one cycle of the sRTS runtime system.
 */
SRTSAPI_DLL ENTRY_cycle_t ENTRY_cycle;

/**
 * A message has been received via a connection.
 *
 * @param aConnection the connection (also containing the context for the DCM_sendMessageCallback
 * call)
 * @param aData raw content
 * @param aLength length of the raw content
 * @return error code
 */
typedef ENTRY_Rc ENTRY_receive_t(SRTS_ContextPtr aContextPtr, DCM_Connection* aConnection, void const* aPtr, size_t aLength);
/**
 * Function instance that triggers the runtime system to process a message
 * which has been received by the engineering system.
 */
SRTSAPI_DLL ENTRY_receive_t ENTRY_receive;

/**
 * Set the send message callback.
 *
 * This callback function is used for sending messages as a response to a received message to the
 * client. The context passed to this callback is the one defined by the call to ENTRY_receive
 * (aConnection->context).
 *
 * This function must be called after calling ENTRY_init and before calling ENTRY_receive.
 *
 * @param aSendMessageCallback callback to register
 * @return error code
 */
typedef ENTRY_Rc ENTRY_setSendCb_t(SRTS_ContextPtr aContextPtr, DCM_sendMessageCallback* aSendMessageCallback);
/**
 * Function instance that allows for setting the send message callback which is
 * invoked by the runtime system when sending an answer back to the engineering
 * system.
 */
SRTSAPI_DLL ENTRY_setSendCb_t ENTRY_setSendCb;

/**
 * Set the send message broadcast callback.
 *
 * This callback function is used for sending messages broadcast to the client.
 *
 * This function must be called after calling ENTRY_init and before calling ENTRY_receive.
 *
 * @param aSendMessageBroadcastCallback callback to register
 * @return error code
 */
typedef ENTRY_Rc ENTRY_setSendBroadcastCb_t(SRTS_ContextPtr aContextPtr,
    DCM_sendMessageBroadcastCallback* aSendMessageBroadcastCallback);

/**
 * Function instance that allows for setting the send message callback which is
 * invoked broadcast by the runtime system for sending ad hoc messages back
 * to the engineering system.
 */
SRTSAPI_DLL ENTRY_setSendBroadcastCb_t ENTRY_setSendBroadcastCb;

/**
 * Retrieve flag whether sRTS is in virtual time mode.
 *
 * @param aVirtualTime pointer to flag memory
 * @return error code
 */
typedef ENTRY_Rc ENTRY_isVirtualTime_t(SRTS_ContextPtr aSrtsContext, CMN_Bool* aVirtualTime);
/**
 * Function instance that allows to determine whether sRTS is in virtual time mode.
 */
SRTSAPI_DLL ENTRY_isVirtualTime_t ENTRY_isVirtualTime;

/**
 * Terminate the sRTS runtime system
 *
 * @return error code
 */
typedef ENTRY_Rc ENTRY_terminate_t(SRTS_ContextPtr aSrtsContext);
/**
 * Function instance that terminates the sRTS runtime system and frees its
 * resources.
 */
SRTSAPI_DLL ENTRY_terminate_t ENTRY_terminate;

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*@}*/ /* SRTS_ENTRY_API SRTS entry API */

#endif /* SRTS_DCM_API_H */
