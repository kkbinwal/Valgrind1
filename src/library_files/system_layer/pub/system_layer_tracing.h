/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_TRACING_H
#define SYSTEM_LAYER_TRACING_H

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>
#include <common_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SL System Layer Interface
 *
 *  In order to integrate the Safe RTS to a specific platform, this
 *  interfaces have to be implemented by the platform vendor.
 *
 *@{*/

#define SL_MAX_LOG_MSG_LEN 128                             /**< Maximum stored size of log message text.
                                                                (including terminating '\0' character) */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** @name Alarming
 */
/*@{*/

/**
 * Raise an alarm of a certain type.
 *
 * @param[in] aCtx context
 * @param[in] aAlarmType alarm type
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #SL_EINVALRMTYP
 * @retval #SL_EALARMSET
 * @retval #SL_ETIMER
 */
SL_Rc SL_setAlarm(SRTS_ContextPtr aCtx, SL_AlarmType aAlarmType);

/**
 * Get an alarm state.
 *
 * @param[in] aCtx context
 * @param[in] aAlarmType alarm type
 * @param[out] aAlarmState alarm state, 0=cleared, 1=set
 * @param[out] aSystemTimerTicks The timestamp [system timer ticks] of alarm set/cleared
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getAlarmState(SRTS_ContextPtr aCtx,
    SL_AlarmType aAlarmType,
    CMN_Bool* aAlarmState,
    SL_SystemTimerTicks* aSystemTimerTicks);

/**
 * Clear an alarm.
 *
 * @param[in] aCtx context
 * @param[in] aAlarmType alarm type
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #SL_EALARMCLR
 * @retval #SL_ETIMER
 */
SL_Rc SL_clearAlarm(SRTS_ContextPtr aCtx, SL_AlarmType aAlarmType);
/*@}*/

/** @name Logging
 */
/*@{*/
/**
 * Reset the log.
 *
 * @param[in] aCtx context
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 */
SL_Rc SL_resetLog(SRTS_ContextPtr aCtx);

/**
 * Add a log entry.
 *
 * Meta-info is provided, in order to group the log entries later on.
 *
 * Misra does not allow variable length argument lists / printf. Thus up to four
 * messages can be passed. Use type-safe number to string conversions when needed.
 *
 * Only the first #SL_MAX_LOG_MSG_LEN characters of the concatenated messages (including
 * terminating \0 character) are stored.
 *
 * @param[in] aCtx context
 * @param[in] aSeverity severity
 * @param[in] aEventId event classification
 * @param[in] aReturnCode return code to log
 * @param[in] aMessage1 message (no space between message1, message2, ..), possibly NULL
 * @param[in] aMessage2 message (no space between message1, message2, ..), possibly NULL
 * @param[in] aMessage3 message (no space between message1, message2, ..), possibly NULL
 * @param[in] aMessage4 message (no space between message1, message2, ..), possibly NULL
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVAL
 * @retval #CMN_EINVALCTX
 * @retval #SL_ETIMER
 * @retval #SL_ELOGFULL
 */
SL_Rc SL_addLogEntry(
    SRTS_ContextPtr aCtx,
    SL_LogEntrySeverity aSeverity,
    SL_EventId aEventId,
    CMN_Rc aReturnCode,
    SL_ConstCStr aMessage1,
    SL_ConstCStr aMessage2,
    SL_ConstCStr aMessage3,
    SL_ConstCStr aMessage4);

/**
 * Get the number of log entries
 *
 * @param[in] aCtx context
 * @param[out] aCount count
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getLogEntryCount(SRTS_ContextPtr aCtx, SL_LogEntryListSize *aCount);

/**
 * Retrieve a log entry.
 *
 * @param[in] aCtx context
 * @param[in] aLogEntryIdx zero based index of log entry
 * @param[out] aSystemTimerTicks timestamp [system timer ticks].
 * @param[out] aSeverity severity
 * @param[out] aEventId event classification
 * @param[out] aReturnCode return code to log
 * @param[in] aMessage message buffer, message is copied to that buffer, buffer size must be
 *                     at least #SL_MAX_LOG_MSG_LEN characters.
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_EIDXBOUNDS
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getLogEntry(
    SRTS_ContextPtr aCtx,
    SL_LogEntryListIdx aLogEntryIdx,
    SL_SystemTimerTicks* aSystemTimerTicks,
    SL_LogEntrySeverity* aSeverity,
    SL_EventId* aEventId,
    CMN_Rc* aReturnCode,
    SL_CStr aMessage
    );
/*@}*/

/*@}*/

#endif /* SYSTEM_LAYER_TRACING_H */
