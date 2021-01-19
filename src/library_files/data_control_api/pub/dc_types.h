/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DCTYPES_H_
#define DCTYPES_H_

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>
#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup TYPES Types and Structures
 *
 * @brief Types and Structures
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */
/**
 * Return code for data control API functions.
 * Return codes greater or equal to 0 are success codes, codes less than 0 indicate that an error has occurred.
 */
typedef CMN_Rc DC_Rc;

/**
 * Application state.
 *
 */
typedef enum
{
  DC_ApplicationStateError = 0, /**< Application is in an "Error" state. */
  DC_ApplicationStateNotVerified = 1, /**< Application is in "Not Verified" state. */
  DC_ApplicationStateVerified = 2, /**< Application is in "Verified" state. */
  DC_ApplicationStateReleased = 3, /**< Application is in "Released" state. */
  DC_ApplicationStateVerificationInternal = 4, /**< Application is currently internally verified. */
  DC_ApplicationStateVerificationSLConfiguration = 5, /**< SystemLayer configuration is currently verified. */
  DC_ApplicationStateVerificationSLAdditional = 6, /**< Additional SystemLayer verification checks are currently performed. */
} DC_ApplicationState;

/**
 * Hardware IOs connection state
 *
 */
typedef enum
{
  DC_IoStateError = 0, /**< IOs are in error state (unknown). */
  DC_IoStateConnected = 1, /**< HW IOs are connected  */
  DC_IoStateDisconnected = 2 /**< HW IOs are disconnected */
} DC_IoState;

/**
 * Watch mode
 */
typedef enum
{
  DC_WatchModeDisabled, /**< Watch is enabled. */
  DC_WatchModeEnabled /**< Watch is disabled. */
} DC_WatchMode;

/**
 * Pin information provided by DC_iteratePins API
 */
typedef struct
{
  CMN_DataType dataType;
  CMN_PinDirection direction;
  CMN_PinBlockEdge blockEdge;
  CMN_PinDisplayIndex displayIndex;
  CMN_StringBufferDesc nameBuffer;
  CMN_Bool alternativeNameExists;
  CMN_StringBufferDesc alternativeNameBuffer;
} DC_PinInfo;

typedef DC_PinInfo* DC_PinInfoPtr;

/**
 * Library information provided by DC_iterateLibrary API
 */
typedef struct
{
  CMN_StringBufferDesc groupBuffer;
  CMN_StringBufferDesc nameBuffer;
  CMN_StringBufferDesc alternativeNameBuffer;
  CMN_Coordinate size;
  CMN_RGBA_Color backgroundColor;
} DC_LibraryBlockInfo;

typedef DC_LibraryBlockInfo* DC_LibraryBlockInfoPtr;

/**
 * Reasons how a verification has been triggered.
 */
typedef enum
{
  DC_VERIF_REASON_UNKNOWN = 0, /**< Unknown verification reason. */
  DC_VERIF_REASON_COMM = 1, /**< Verification was triggered through communication layer. */
  DC_VERIF_REASON_PREPARE_PIL = 2 /**< Verification was triggered by PIL test preparation. */
} DC_VerificationReason;

typedef struct
{
  DC_VerificationReason verificationReason;
  struct
  {
    CMN_Count numTestSteps;
  } preparePilTestContext;
} DC_VerificationInProgressContext;

/*@}*/ /* Types and Structures */

/*@}*/ /* Data Control API */

#endif
