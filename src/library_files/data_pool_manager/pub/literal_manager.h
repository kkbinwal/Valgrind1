/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef LITERAL_MANAGER_H_
#define LITERAL_MANAGER_H_

/* -- Include files --------------------------------------------------------- */

#include <common_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define DPM_LM_MAX_LITERAL_SIZE INT64_MAX

/* -- Typedefs -------------------------------------------------------------- */

typedef CMN_Offset DPM_LiteralHandle;
typedef uint8_t DPM_LiteralLength;

/* -- Prototypes ------------------------------------------------------------ */

CMN_Rc DPM_LiteralManager_allocate(SRTS_ContextPtr aCtx, CMN_BytePtr const aLiteral, CMN_Size aSize, DPM_LiteralHandle* aHandle);
CMN_Rc DPM_LiteralManager_get(SRTS_ContextPtr aCtx, DPM_LiteralHandle aHandle, CMN_BytePtr* aLiteral);
CMN_Rc DPM_LiteralManager_free(SRTS_ContextPtr aCtx, DPM_LiteralHandle aHandle);

#endif /* LITERAL_MANAGER_H_ */
