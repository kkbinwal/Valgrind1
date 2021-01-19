/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_STATEMACHINE_H_
#define COMMON_STATEMACHINE_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/**
 * Convenience macro to define a transition row initializer.
 */
#define CMNSM_TRANSITION(transition, targetState, guard, operation) {(transition), (targetState), (guard), (operation), CMNSM_State_Uninitialized},

/**
 * Convenience macro to define a transition row initializer with exception handling.
 */
#define CMNSM_TRANSITIONEX(transition, targetState, guard, operation, exceptionState) {(transition), (targetState), (guard), (operation), (exceptionState)},

/**
 * Shorthand for empty transition row.
 */
#define CMNSM_EMPTY {CMNSM_Transition_invalid, CMNSM_State_Uninitialized, NULL, NULL, CMNSM_State_Uninitialized},

/**
 * Defines a transition row without guard and operation.
 */
#define CMNSM_SIMPLE(transition, targetState) CMNSM_TRANSITION(transition, targetState, NULL, NULL)

#define CMNSM_INVALIDTRANSITIONROW ((CMNSM_TransitionIndex)UINT8_MAX)

#define CMNSM_State_Uninitialized ((CMNSM_State)0u)
#define CMNSM_Transition_invalid ((CMNSM_Transition)0u)

#define CMNSM_DEFINITION(smName, numOfStates, numOfTransitions, postT, ...)  \
  typedef CMNSM_TransitionRow tabletype_ ## smName[(numOfStates)][(numOfTransitions)];\
  static const tabletype_ ## smName table_ ## smName = {__VA_ARGS__};\
  static const CMNSM_Definition data_ ## smName =  {.numberOfStates = (numOfStates), .numberOfTransitions = (numOfTransitions), .postTransition=(postT), .transitions = (CMNSM_TransitionRowPtr)table_ ## smName};\
  static const CMNSM_DefinitionPtr smName = &data_ ## smName

#define CMNSM_TRANSREF(smName, state, transition) &((smName)->transitions[((state)*((smName)->numberOfTransitions)) + (transition)])

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Type of transition guard function. If present, the transition is only executed
 * if the guard function returns True.
 */
typedef CMN_Bool CMNSM_TransitionGuard(SRTS_ContextPtr aContext);

/**
 * Pointer for Guard function
 */
typedef CMNSM_TransitionGuard* CMNSM_TransitionGuardPtr;

/**
 * An operation to be executed in the context of the transition.
 */
typedef CMN_Rc CMNSM_TransitionOperation(SRTS_ContextPtr aContext);

/**
 * Pointer for operation function.
 */
typedef CMNSM_TransitionOperation* CMNSM_TransitionOperationPtr;

typedef uint16_t CMNSM_Transition;

typedef uint16_t CMNSM_State;

/**
 * A transition row declares a possible transition originating from a given state.
 */
typedef const struct tag_CMNSM_TransitionRow
{
  CMNSM_Transition transition; /**< Transition. */
  CMNSM_State targetState; /**< This transition can move system state to this state. */
  CMNSM_TransitionGuardPtr guard; /**< Guard function. Transition may only be executed if this function returns true. */
  CMNSM_TransitionOperationPtr operation; /**< Transition operation. It's executed along with the transition. */
  CMNSM_State exceptionState; /**< Move SM into this state if operation fails. If set to UNINITAILIZED, SM won't change state. Only used of operation is not NULL. */
} CMNSM_TransitionRow;

/**
 * Pointer to a transition row.
 */
typedef CMNSM_TransitionRow* CMNSM_TransitionRowPtr;

typedef const struct tag_CMNSM_Definition
{
  uint16_t numberOfStates;
  uint16_t numberOfTransitions;
  CMNSM_TransitionOperationPtr postTransition; /*< Post-transition event handler */
  CMNSM_TransitionRowPtr transitions;
} CMNSM_Definition;

/**
 * Indicates a position in a TransitionList.
 */
typedef uint8_t CMNSM_TransitionIndex;

typedef CMNSM_Definition* CMNSM_DefinitionPtr;

/**
 *
 */
typedef struct tag_CMNSM_StateMachineInstance
{
  CMNSM_State executionState;
  CMNSM_TransitionIndex transitionInProgress;
} CMNSM_StateMachineInstance;

typedef CMNSM_StateMachineInstance* CMNSM_StateMachineInstancePtr;

/* -- Prototypes ------------------------------------------------------------ */

CMN_Rc CMNSM_initialize(CMNSM_StateMachineInstancePtr aSM, CMNSM_State aStartingState);

CMN_Rc CMNSM_executeTransition(CMNSM_StateMachineInstancePtr aSM, CMNSM_DefinitionPtr aStateMachine, SRTS_ContextPtr aContext,
    CMNSM_Transition aTransition);

CMN_Rc CMNSM_startTransition(CMNSM_StateMachineInstancePtr aSM, CMNSM_DefinitionPtr aStateMachine, SRTS_ContextPtr aContext,
    CMNSM_Transition aTransition);

CMN_Rc CMNSM_finishTransition(CMNSM_StateMachineInstancePtr aSM, CMNSM_DefinitionPtr aStateMachine, SRTS_ContextPtr aContext);

CMN_Rc CMNSM_cancelTransition(CMNSM_StateMachineInstancePtr aSM);

#endif /* COMMON_STATEMACHINE_H_ */
