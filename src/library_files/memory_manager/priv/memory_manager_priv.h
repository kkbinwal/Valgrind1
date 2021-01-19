/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef MEMORY_MANAGER_PRIV_H_
#define MEMORY_MANAGER_PRIV_H_

/* -- Include files ----------------------------------------------------------
 */
#include <memory_manager.h>

#include <data_pool_manager_priv.h>

/* -- Externals --------------------------------------------------------------
 */

/* -- Typedefs ---------------------------------------------------------------
 */

typedef uint8_t MM_ChunkFlags;

/* -- Defines ----------------------------------------------------------------
 */

#define MM_CHUNK_FLAG_FREE 0
#define MM_CHUNK_FLAG_USED 1

#define MM_CHUNK_IS_FREE(chunkHdrPtr)                                                              \
  (((chunkHdrPtr)->flags & MM_CHUNK_FLAG_USED) == MM_CHUNK_FLAG_FREE)
#define MM_CHUNK_SET_USED(chunkHdrPtr)                                                             \
  do                                                                                               \
  {                                                                                                \
    ((chunkHdrPtr)->flags |= MM_CHUNK_FLAG_USED);                                                  \
  } while (0)
#define MM_CHUNK_IS_LAST(chunkHdrPtr) (!((chunkHdrPtr)->size))
#define MM_CHUNK_SET_LAST(chunkHdrPtr) (((chunkHdrPtr)->size) = 0)
#define MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, MM_ChunkFlags, aBufSize, aDataBasePtr, aMemoryBlockSize) \
  ((CMN_CAST(CMN_Byte*, curChunkHdr)                                                               \
    + sizeof(ChunkHdrTypeName) + sizeof(MM_ChunkFlags) + aBufSize)                                 \
    > (CMN_CAST(CMN_Byte*, aDataBasePtr) + aMemoryBlockSize))

#define MM_ALLOCATE_GEN(FuncNamePrefix, ChunkSizeType, ChunkHdrTypeName)                           \
  typedef struct {                                                                                 \
    ChunkSizeType size;                                                                            \
    MM_ChunkFlags flags;                                                                           \
  } ChunkHdrTypeName;                                                                              \
                                                                                                   \
  static CMN_Rc FuncNamePrefix##_allocate(ChunkSizeType aBufSize, CMN_VoidPtr* aMemHandle,         \
                                          SL_MemoryBlockBasePtr aDataBasePtr,                      \
                                          SL_MemoryBlockSize aMemoryBlockSize)                     \
  {                                                                                                \
    /* TODO: aMemoryBlockSize has to be considered so that not too much memory                     \
     * can be allocated */                                                                         \
    if (!aBufSize)                                                                                 \
    {                                                                                              \
      return CMN_EINVAL;                                                                           \
    }                                                                                              \
    if (!aMemHandle)                                                                               \
    {                                                                                              \
      return CMN_EBADHNDL;                                                                         \
    }                                                                                              \
    if (!aDataBasePtr)                                                                             \
    {                                                                                              \
      return CMN_ENULLPTR;                                                                         \
    }                                                                                              \
    if (!aMemoryBlockSize)                                                                         \
    {                                                                                              \
      return CMN_EINVAL;                                                                           \
    }                                                                                              \
                                                                                                   \
    ChunkHdrTypeName* candidateChunkHdr = NULL;                                                    \
    ChunkHdrTypeName* curChunkHdr;                                                                 \
    for (curChunkHdr = CMN_CAST(ChunkHdrTypeName*, aDataBasePtr); !MM_CHUNK_IS_LAST(curChunkHdr);  \
         curChunkHdr =                                                                             \
             CMN_CAST(ChunkHdrTypeName*, CMN_PTR_ADD_BYTES(curChunkHdr, sizeof(ChunkHdrTypeName) + \
                                                                            curChunkHdr->size)))   \
    {                                                                                              \
      if (MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, MM_ChunkFlags, aBufSize, aDataBasePtr, aMemoryBlockSize)) \
      {                                                                                            \
        return CMN_ENOBUFS;                                                                        \
      }                                                                                            \
      if (MM_CHUNK_IS_FREE(curChunkHdr) && curChunkHdr->size >= aBufSize)                          \
      {                                                                                            \
        if (!candidateChunkHdr || curChunkHdr->size < candidateChunkHdr->size)                     \
        {                                                                                          \
          candidateChunkHdr = curChunkHdr;                                                         \
        }                                                                                          \
      }                                                                                            \
    }                                                                                              \
    if (candidateChunkHdr)                                                                         \
    {                                                                                              \
      MM_CHUNK_SET_USED(candidateChunkHdr);                                                        \
      *aMemHandle = CMN_PTR_ADD_BYTES(candidateChunkHdr, sizeof(ChunkHdrTypeName));                \
      return CMN_OK;                                                                            \
    }                                                                                              \
    if (MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, MM_ChunkFlags, aBufSize, aDataBasePtr, aMemoryBlockSize)) \
    {                                                                                              \
      return CMN_ENOBUFS;                                                                          \
    }                                                                                              \
    MM_CHUNK_SET_USED(curChunkHdr);                                                                \
    curChunkHdr->size = aBufSize;                                                                  \
    *aMemHandle = CMN_PTR_ADD_BYTES(curChunkHdr, sizeof(ChunkHdrTypeName));                        \
                                                                                                   \
    return CMN_OK;                                                                              \
  }                                                                                                \
                                                                                                   \
  static CMN_Rc FuncNamePrefix##_free(CMN_VoidPtr aMemHandle)                                      \
  {                                                                                                \
    if (!aMemHandle)                                                                               \
    {                                                                                              \
      return CMN_EBADHNDL;                                                                         \
    }                                                                                              \
                                                                                                   \
    CMN_CAST(ChunkHdrTypeName*, CMN_PTR_SUB_BYTES(aMemHandle, sizeof(ChunkHdrTypeName)))->flags =  \
        MM_CHUNK_FLAG_FREE;                                                                        \
                                                                                                   \
    return CMN_OK;                                                                              \
  }

/* -- Prototypes -------------------------------------------------------------
 */

CMN_Rc MM_get_dpm_instanceData_context(SRTS_ContextPtr aCtx, DPM_ContextTransientPtr* dpmContext);
CMN_Rc MM_get_dpm_applicationModel_context(SRTS_ContextPtr aCtx,
                                           DPM_ContextPersistentPtr* dpmContext);
CMN_Rc MM_get_dpm_instanceData_data(SRTS_ContextPtr aCtx, SL_MemoryBlockBasePtr* dpmData,
                                    SL_MemoryBlockSize* blockSize);

#endif /* MEMORY_MANAGER_PRIV_H_ */
