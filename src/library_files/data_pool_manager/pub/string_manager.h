/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef STRING_MANAGER_H
#define STRING_MANAGER_H

/* -- Include files ---------------------------------------------------------- */
#include <common_types.h>
#include <system_layer_types.h>

typedef uint16_t DPM_StringsCount;
typedef CMN_Offset DPM_StringHandle;
/**
 * string length data type
 * @see #DPM_SM_MAX_STRING_BUFFER_SIZE
 */
typedef uint8_t DPM_StringLength;
/**
 * maximum string buffer size (including terminating \0 character)
 * @see #DPM_StringLength
 */
#define DPM_SM_MAX_STRING_BUFFER_SIZE 255u

/* -- Prototypes ------------------------------------------------------------- */

CMN_Rc DPM_StringManager_allocate(SRTS_ContextPtr aCtx, char const* string, DPM_StringHandle* aHandle);
CMN_Rc DPM_StringManager_get(SRTS_ContextPtr aCtx, DPM_StringHandle aHandle, char const** string);
CMN_Rc DPM_StringManager_free(SRTS_ContextPtr aCtx, DPM_StringHandle aHandle);

#endif /* STRING_MANAGER_H */
