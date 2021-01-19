/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SRC_PIL_PRIV_PIL_PRIV_H_
#define SRC_PIL_PRIV_PIL_PRIV_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>
#include <system_layer_types.h>
#include <library_provider_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */
struct tag_PIL_Context
{
  SL_SystemTimerTicks cycleTime;  /*<Cycle time */
  CMN_Count           cycleIterator; /*<Currently executed cycle */
  CMN_VariableHandle  indexVarHandle; /*< The handle of the index variable created during prepare phase */
  CMN_VariableHandle  timeIndexArray; /*< The handle of the 'timeIndex' array */
  CMN_VariableHandle  cycleTicksArray; /*< The handle of the 'cycleTicks' array */
  CMN_Count           numTestSteps; /*< The maximum number of test steps this SRTS instance can handle */
  CMN_Count           actualNumTestSteps; /*< The number of test steps currently executing */
  CMN_Count           fbutArrayIndex; /*< The handle of the function block under test */
  CMN_VariableHandle  enoOutputArrayHandle; /* The handle for the ENO output array */
};

/* -- Prototypes ------------------------------------------------------------ */

#endif /* SRC_PIL_PRIV_PIL_PRIV_H_ */
