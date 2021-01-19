/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_TYPES_H
#define SYSTEM_LAYER_TYPES_H

/* -- Include files --------------------------------------------------------- */
#include <ssr_slgx_platform_data.h>
#include <common_rc.h>
#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SL System Layer Interface
 *
 *  In order to integrate the Safe RTS to a specific platform, this
 *  interfaces have to be implemented by the platform vendor.
 *
 *@{*/

#define SL_OK                   CMN_SL_RC_BASE              /**< Successful function execution */
#define SL_ETIMER               (CMN_SL_RC_BASE + 0x01u)    /**< Base software timer error. */
#define SL_EPERSISTREAD         (CMN_SL_RC_BASE + 0x02u)    /**< Base software persistent storage read error */
#define SL_EPERSISTWRITE        (CMN_SL_RC_BASE + 0x03u)    /**< Base software persistent storage write error */
#define SL_ESETTNOTACC          (CMN_SL_RC_BASE + 0x04u)    /**< Setting was not accepted by the base software. */
#define SL_EINVALRMTYP          (CMN_SL_RC_BASE + 0x05u)    /**< Invalid alarm type. */
#define SL_ESLOTEMPTY           (CMN_SL_RC_BASE + 0x06u)    /**< Persistent storage slot is empty. */
#define SL_ELOGFULL             (CMN_SL_RC_BASE + 0x07u)    /**< The log is full. */
#define SL_ECLIPSMSG            (CMN_SL_RC_BASE + 0x08u)    /**< Message would be clipped / buffer too small */
#define SL_EALARMSET            (CMN_SL_RC_BASE + 0x09u)    /**< Alarm is already set. */
#define SL_EALARMCLR            (CMN_SL_RC_BASE + 0x0au)    /**< Alarm is already cleared. */
#define SL_EINVALSYSCFG         (CMN_SL_RC_BASE + 0x0bu)    /**< Invalid system configuration. */
#define SL_EMAXSYSCFGPARTS      (CMN_SL_RC_BASE + 0x0cu)    /**< Maximum number of system configuration parts exceeded. */
#define SL_EINVALAPM            (CMN_SL_RC_BASE + 0x0du)    /**< Application model file format or checksum invalid. */
#define SL_EDISABLED            (CMN_SL_RC_BASE + 0x0eu)    /**< Operation is not enabled */
#define SL_EADDVERIF            (CMN_SL_RC_BASE + 0x0fu)    /**< Additional verification error */

#define IO_OK                   CMN_IO_RC_BASE              /**< No error occurred. */
#define IO_ENOTAVAIL            (CMN_IO_RC_BASE + 0x01u)    /**< The io is not available on this hardware platform. */
#define IO_ETOOMANY             (CMN_IO_RC_BASE + 0x02u)    /**< The max number of IOs was exceeded */
#define IO_EINVALIOSYSCFG       (CMN_IO_RC_BASE + 0x03u)    /**< Invalid io system configuration. */
#define IO_EDUPLICATE           (CMN_IO_RC_BASE + 0x04u)    /**< Duplicate IO resource id or name */
#define IO_EDATATYPE            (CMN_IO_RC_BASE + 0x05u)    /**< The data type is not possible for that IO */
#define IO_EPINDIR              (CMN_IO_RC_BASE + 0x06u)    /**< The pin direction is not possible for that IO */
#define IO_EIO_DESCR_NOT_FOUND  (CMN_IO_RC_BASE + 0x07u)    /**< The triple (ioName, ioDirection, ioDataType) was not found */

#define SL_PERSISTENCE_DEFAULT_SLOT 0                           /**< Default slot to persist the application model */
#define SL_PERSISTENCE_BACKUP_SLOT  1                           /**< Backup slot to persist the application model */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Return code for system layer functions.
 */
typedef CMN_Rc SL_Rc;                    /**< System layer return code. */
typedef CMN_Rc IO_Rc;                    /**< IO provider return code. */

typedef uint8_t SL_SysCfgPart;           /**< System configuration part (binary, structure is known to
                                              system layer implementation) */

typedef CMN_Bool SL_IoConnectionState;   /**< State of the IO connections, 0=IOs disconnected, 1=IOs connected */

typedef uint64_t SL_SystemTimerTicks;    /**< System timer ticks */
typedef uint32_t SL_TicksPerSec;         /**< System timer ticks per second */
typedef uint16_t SL_IoDescrListSize;     /**< IO description list size */
typedef uint16_t SL_SysCfgPartSize;      /**< Size of system configuration part */
typedef uint16_t SL_SysCfgListSize;      /**< Size of system configuration part list */
typedef uint16_t SL_SysCfgListIdx;       /**< Zero-based index of system configuration part list */
typedef uint16_t SL_SysCfgVerifCount;    /**< System configuration verification entry count */
typedef uint16_t SL_SysCfgVerifIdx;      /**< Zero-based index of system configuration verification entry list */
typedef uint32_t SL_LogEntryListSize;    /**< Size of the log entry list */
typedef uint32_t SL_LogEntryListIdx;     /**< Zero-based index of log entry list */

//BACR - typedef moved to ssr_slgx_platform_data.h
typedef char* SL_CStr;                   /**< \0-terminated string */
typedef uint16_t SL_CStrSize;            /**< Maximum length of C-string (including terminating \0 character) */
typedef CMN_VoidPtr SL_MemoryBlockBasePtr;     /**< Base pointer of large memory block provided by base software */
typedef size_t SL_MemoryBlockSize;    /**< Size of large memory block provided by base software */
typedef uint8_t SL_PersistentSlotIdx;    /**< Persistent memory slot index */

/**
 * IO direction
 */
//BACR - enumeration moved to ssr_slgx_platform_data.h

/**
 * IO description
 */
//BACR - description moved to ssr_slgx_platform_data.h

typedef uint8_t SL_AlarmType;

/**
 * Log Entry Severity
 */
typedef enum
{
  eDebug = 0,
  eFirstLogEntrySeverity = eDebug,
  eInfo = 1,
  eWarning = 2,
  eError = 3,
  eFatal = 4,
  eLastLogEntrySeverity = eFatal
} SL_LogEntrySeverity;

/**
 * Log Event Id
 */
typedef enum
{
  eEdit = 0,
  eFirstEventId = eEdit,
  eGenericTrace = 1,
  eRelease = 2,
  eVerify = 3,
  eRuntime = 4,
  eLastEventId = eRuntime
} SL_EventId;

/**
 * State Change Callback function.
 */
typedef SL_Rc SL_stateChangeCallback(SRTS_ContextPtr aSrtsContext);

/**
 * Verification states of the system layer.
 */
typedef enum
{
  SL_AdditionalVerificationStateUnknown = 0, /**< Unknown system layer verification state. */
  SL_AdditionalVerificationStateVerified = 1, /**< System layer verification successful. */
  SL_AdditionalVerificationStateNotVerified = 2, /**< System layer verification failed. */
  SL_AdditionalVerificationStateDeferred = 3, /**< System layer verification not completed yet. */
} SL_AdditionalVerificationState;

/*@}*/

#endif /* SYSTEM_LAYER_TYPES_H */
