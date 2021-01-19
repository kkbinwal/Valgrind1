/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef MEMORY_MANAGER_MOCK_H_
#define MEMORY_MANAGER_MOCK_H_

/* -- Include files --------------------------------------------------------- */
#include <memory_manager.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */
#define MM_ALLOCATE_INSTANCEDATA_MOCK(aCtx, aBufSize, aMemhandle)
#define MM_ALLOCATE_APPLICATIONMODEL_MOCK(aCtx, aBufSize, aMemhandle)
#define MM_FREE_INSTANCEDATA_MOCK(aCtx, aMemHandle)
#define MM_FREE_APPLICATIONMODEL_MOCK(aCtx, aMemHandle)
#define MM_RESET_MOCK(aCtx)
#define MM_GET_DPM_INSTANCEDATA_DATA(aCtx, dpmData, blockSize)

/* -- Prototypes ------------------------------------------------------------ */

#endif /* MEMORY_MANAGER_MOCK_H_ */

