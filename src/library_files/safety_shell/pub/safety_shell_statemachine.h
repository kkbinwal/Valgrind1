/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SAFETY_SHELL_STATEMACHINE_H_
#define SAFETY_SHELL_STATEMACHINE_H_

/* -- Include files --------------------------------------------------------- */

#include <common_statemachine.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define SSHSM_State_NotVerified 1
#define SSHSM_State_VerificationInternal 2
#define SSHSM_State_VerificationSLConfiguration 3
#define SSHSM_State_VerificationSLAdditional 4
#define SSHSM_State_Verified_Stopped 5
#define SSHSM_State_Verified_Running_Test 6
#define SSHSM_State_Verified_CycleStepMode_Test 7
#define SSHSM_State_Verified_BlockStepMode_Breakpoint_Test 8
#define SSHSM_State_Verified_BlockStepMode_Running_Test 9
#define SSHSM_State_Verified_Paused_Test 10
#define SSHSM_State_Released_Stopped_Safe 11
#define SSHSM_State_Released_Stopped_Test 12
#define SSHSM_State_Released_Running_Safe 13
#define SSHSM_State_Released_Running_Test 14
#define SSHSM_State_Released_CycleStepMode_Test 15
#define SSHSM_State_Released_BlockStepMode_Breakpoint_Test 16
#define SSHSM_State_Released_BlockStepMode_Running_Test 17
#define SSHSM_State_Released_Paused_Test 18
#define SSHSM_State_Stopped_Error 19

#define SSHSM_Transition_verify 1
#define SSHSM_Transition_release 2
#define SSHSM_Transition_edit 3
#define SSHSM_Transition_runTest 4
#define SSHSM_Transition_runSafe 5
#define SSHSM_Transition_execInit 6
#define SSHSM_Transition_hold 7
#define SSHSM_Transition_resume 8
#define SSHSM_Transition_stopTest 9
#define SSHSM_Transition_stopSafe 10
#define SSHSM_Transition_connectIO 11
#define SSHSM_Transition_disconnectIO 12
#define SSHSM_Transition_cycle 13
#define SSHSM_Transition_execSingleCycle 14
#define SSHSM_Transition_runSafeToRunTest 15
#define SSHSM_Transition_force 16
#define SSHSM_Transition_shutdown 17
#define SSHSM_Transition_watchArray 18
#define SSHSM_Transition_failsafe 19
#define SSHSM_Transition_computeExecutionOrder 20
#define SSHSM_Transition_execSingleCommandBlock 21

#define SSHSM_TRANSITION(transition, targetState, guard, operation) CMNSM_TRANSITION(SSHSM_Transition_ ## transition, SSHSM_State_ ## targetState, guard, operation)
#define SSHSM_TRANSITIONEX(transition, targetState, guard, operation, exceptionState) CMNSM_TRANSITIONEX(SSHSM_Transition_ ## transition, SSHSM_State_ ## targetState, guard, operation, SSHSM_State_ ## exceptionState)
#define SSHSM_SIMPLE(transition, targetState) SSHSM_TRANSITION(transition, targetState, NULL, NULL)

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

CMN_Rc SSHSM_executeTransition(SRTS_ContextPtr aContext, CMNSM_Transition aTransition);

CMN_Rc SSHSM_startTransition(SRTS_ContextPtr aContext, CMNSM_Transition aTransition);

CMN_Rc SSHSM_finishTransition(SRTS_ContextPtr aContext);

CMN_Rc SSHSM_cancelTransition(SRTS_ContextPtr aContext);

#endif /* SAFETY_SHELL_STATEMACHINE_H_ */
