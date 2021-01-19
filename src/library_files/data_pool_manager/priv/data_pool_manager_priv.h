/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DATA_POOL_MANAGER_PRIV_H_
#define DATA_POOL_MANAGER_PRIV_H_

/* -- Include files ---------------------------------------------------------- */
#include <data_pool_manager.h>

/* -- Externals -------------------------------------------------------------- */

/* -- Defines ---------------------------------------------------------------- */

/* -- Typedefs --------------------------------------------------------------- */

typedef struct
{
  CMN_Offset offset;
  CMN_BufferSize size;
} MemoryChunk;
typedef MemoryChunk* MemoryChunkPtr;

typedef struct tag_DPM_ContextTransient
{
  MemoryChunk interpreter;
  MemoryChunk safetyShell;
  MemoryChunk pilContext;
} DPM_ContextTransient; /* transient */

typedef DPM_ContextTransient* DPM_ContextTransientPtr;

typedef struct tag_DPM_ContextPersistent
{
  MemoryChunk applicationModel;
  MemoryChunk stringManager;
  MemoryChunk literalManager;
} DPM_ContextPersistent;

typedef DPM_ContextPersistent* DPM_ContextPersistentPtr;

/* -- Prototypes ------------------------------------------------------------- */

#endif /* DATA_POOL_MANAGER_PRIV_H_ */


