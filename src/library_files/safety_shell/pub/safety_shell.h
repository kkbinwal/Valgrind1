/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SAFETY_SHELL_H_
#define SAFETY_SHELL_H_

/* -- Include files --------------------------------------------------------- */

#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Checks the application state is safe.
 *
 * @param aContext pointer the SRTS context instance
 * @param aBool true if the application state is safe, otherwise false
 * @return Error code
 */
CMN_Rc SSH_isApplicationModeSafe(SRTS_ContextPtr aContext, CMN_Bool* aBool);

/**
 * Returns the command block sequence number of the next executed command.
 *
 * @req{SAFE-3582}
 *
 * @param aContext pointer the SRTS context instance
 * @param[out] aCommandBlockSeqNum command block sequence number of the next executed command
 * @return Error code
 */
CMN_Rc SSH_getCommandBlockSequenceNumber(SRTS_ContextPtr aContext, CMN_SequenceNumber* aCommandBlockSeqNum);

#endif /* SAFETY_SHELL_H_ */
