/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SAFETY_SHELL_TYPES_H_
#define SAFETY_SHELL_TYPES_H_

/* -- Include files --------------------------------------------------------- */
#include <dc_types.h>
#include <common_statemachine.h>


/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define SSH_WATCH_MESSAGES_PER_CYCLE 20

/* -- Typedefs -------------------------------------------------------------- */

typedef enum
{
  SSH_ApplicationModeSafe,
  SSH_ApplicationModeTest
} SSH_ApplicationMode;

struct tag_SSH_InstanceInfo
{
  DC_WatchMode watchMode;
  CMN_UnsignedIndex watchStartIterator;
  CMN_StreamState streamState;
  DC_VerificationInProgressContext verifContext;

  CMNSM_StateMachineInstance executionSM;
};

/* -- Prototypes ------------------------------------------------------------ */

#endif
