/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SAFETY_SHELL_INTERNAL_H_
#define SAFETY_SHELL_INTERNAL_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>
#include <common_rc.h>
#include <interpreter.h>
#include <safety_shell_mock.h>
#include <safety_shell_types.h>
#include <system_layer_types.h>
#include <dc_rc.h>
#include <dc_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define SSH_INTERNAL_ENUM_INT_RANGE(min, value, max) ((min <= value) && (value <= max))

/* -- Typedefs -------------------------------------------------------------- */

typedef int int_errno;

/* -- Prototypes ------------------------------------------------------------ */

CMN_Rc SSH_internalValidateLiteral(SRTS_ContextPtr aSrtsContext, CMN_DataType aDataType, char const* aLiteral);

CMN_Rc SSH_internalValidateLiteralFloat(char const* aLiteral);

CMN_Rc SSH_internalValidateLiteralDouble(char const* aLiteral);

DC_Rc SSH_internalValidateLiteralUint(char const* aLiteral, uintmax_t const aLimit);

DC_Rc SSH_internalValidateLiteralInt(char const* aLiteral, intmax_t aLowerLimit, intmax_t aUpperLimit);

DC_Rc SSH_internalCopyStringToBuffer(char const* aString, CMN_StringBufferDesc aBuffer);

DC_Rc SSH_internalCopyUint8ArrayToBuffer(uint8_t const* aData, CMN_BufferSize aSize, CMN_BinaryBufferDesc aBuffer);

DC_Rc SSH_internalConvertLiteralToString(SRTS_ContextPtr aSrtsContext, CMN_DataType aDataType, APM_Literal const* aLiteral, char* aValueString);

/**
 * Finish the edit transition in the state diagram.
 *
 * The interpreter is freed (state #CMN_ExecutionStateNotInitialized).
 *
 * @see #DC_verify
 */
DC_Rc SSH_internalEdit(SRTS_ContextPtr aCtx);

DC_Rc SSH_internalSetApplicationState(SSH_InstanceInfoPtr aSshInstance, SRTS_ContextPtr aCtx, DC_ApplicationState aNewApplicationState);

DC_Rc SSH_internalInitWatchIterator(SRTS_ContextPtr aCtx);

DC_Rc SSH_internalSendWatch(SRTS_ContextPtr aCtx);

#endif
