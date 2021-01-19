/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_PLATFORM_TYPES_H_
#define SYSTEM_LAYER_PLATFORM_TYPES_H_

#include <system_layer.h>
#include <system_layer_mock.h>
#include <system_layer_vt.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */
#define STM_COMPILER
/* Memory */
#define INSTANCE_DATA_SIZE          (11u)//(6u)                             /* kB */
#define LOGISAFE_APP_DATA_SIZE      (27u)//(14u)                             /* kB */

/* Log */
#define SYS_LOG_ENTRY_LIST_SIZE     (32u)                             /**< size of system log entry list */

/* Alarm */
#define SL_MAX_ALARM_TYPES          (256u)                            /**< maximum number of alarm types (uint8_t) */

#define SL_MAX_SYS_CFG_PARTS_COUNT  (0u)                              /**< Maximum number of system configuration parts TODO: should be changed when system configuration is implemented in SystemLayer */


/* -- Typedefs -------------------------------------------------------------- */

typedef struct {
  SL_SystemTimerTicks systemTimerTicks;                               /**< timestamp [system timer ticks] */
  SL_LogEntrySeverity severity;                                       /**< severity */
  SL_EventId          eventId;                                        /**< event classification */
  CMN_Rc              returnCode;                                     /**< if an error occurred: rc of that error, CMN_OK otherwise */
  char                message[SL_MAX_LOG_MSG_LEN];                    /**< message (including terminating \0)*/
} SL_SystemLogEntry;

struct tag_SRTS_Context {
  /* Valid */
  CMN_Bool isValidSystemConfiguration;                                /**< CMN_TRUE, if the system configuration is valid */
  CMN_Bool isValidTimerSystemConfiguration;                           /**< CMN_TRUE, if the timer system configuration is valid */
  CMN_Bool isValidIoSystemConfiguration;                              /**< CMN_TRUE, if the io system configuration is valid */

  /* Verified */
  CMN_Bool            isVerifiedSystemConfiguration;                  /**< CMN_TRUE, if system configuration is verified */
  SL_SysCfgVerifCount sysCfgVerifEntriesListSize;                     /**< size of system config verification entries list */

  /* Alarm */
  CMN_Bool            alarmState[SL_MAX_ALARM_TYPES];                 /**< Alarm state, array index is alarm type */
  SL_SystemTimerTicks alarmSystemTimerTicks[SL_MAX_ALARM_TYPES];      /**< Alarm system tick count of last set/clear operation, array index is alarm type */

  /* Log */
  SL_LogEntryListSize systemLogListSize;                              /**< Number of used entries in system log */
  SL_SystemLogEntry   systemLog[SYS_LOG_ENTRY_LIST_SIZE];             /**< Array of system log entries */

  /* Timer */
  SL_TicksPerSec ticksPerSecond;                                      /**< frequency of timer hardware and PLC application [ticks/s] (<= 1E9) */

  /* Virtual time support */
  CMN_Bool            isVirtualTimeEnabled;                           /**< CMN_TRUE if virtual time is used */
  SL_SystemTimerTicks virtualTime;                                    /**< time to be used as current time, if virtual time is enabled */

  /* I/O */
  SL_IoDescrListSize      ioDescriptionsListSize;
  SL_IoDescription const* ioDescriptions;
  void **                 ioDescriptionsImageAddr;

  /* System configuration */
  SL_SysCfgListSize sysCfgPartsListSize;                              /**< size of system config parts list */
  uint32_t nvmemIDtmp;
  uint32_t nvmemIDAppData;
  uint32_t nvmemIDStatusData;

  /* States */
  SL_IoConnectionState  iosConnected;
  CMN_ExecutionState    execState;                                    /**< Application execution state */

  /* Memory */
  CMN_Byte instanceData[1024 * INSTANCE_DATA_SIZE];
  CMN_Byte applicationData[1024 * LOGISAFE_APP_DATA_SIZE];
};

#endif /* SYSTEM_LAYER_PLATFORM_TYPES_H_ */
