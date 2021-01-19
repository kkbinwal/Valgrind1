/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef MEMORY_MANAGER_H_
#define MEMORY_MANAGER_H_

/* -- Include files ---------------------------------------------------------- */
#include <common_rc.h>
#include <common_types.h>
#include <system_layer.h>

/* -- Externals -------------------------------------------------------------- */

/* -- Defines ---------------------------------------------------------------- */
#define MM_RC_OK       CMN_MM_RC_BASE           /**< No error occurred.   */
#define MM_RC_ERROR    (CMN_MM_RC_BASE + 0x1u)  /**< An error occurred.   */
#define MM_RC_NOTIMPL  CMN_ENOTIMPL             /**< Not implemented yet. */

/**
 * @defgroup MM_GROUP Memory Manager Group
 *
 * @{
 */

/** @} */

/* -- Typedefs --------------------------------------------------------------- */
typedef uint8_t MM_ChunkFlags;


/* -- Defines ---------------------------------------------------------------- */
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

/* Returns CMN_TRUE, if the chunk header struct exceeds the whole memory region, and thus cannot
 * be read or written.
 */
#define MM_CHUNK_HEADER_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, aDataBasePtr,                 \
                                      aMemoryBlockSize)                                            \
    ((CMN_CAST(CMN_Byte*, curChunkHdr)                                                             \
      + sizeof(ChunkHdrTypeName))                                                                  \
      > (CMN_CAST(CMN_Byte*, aDataBasePtr) + aMemoryBlockSize))
/* Returns CMN_TRUE, if a memory chunk exceeds the whole memory region, and thus cannot
 * be created (or is invalid).
 */
#define MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, aBufSize, aDataBasePtr,              \
                               aMemoryBlockSize)                                                   \
    ((CMN_CAST(CMN_Byte*, curChunkHdr)                                                             \
      + sizeof(ChunkHdrTypeName) + aBufSize)                                                       \
      > (CMN_CAST(CMN_Byte*, aDataBasePtr) + aMemoryBlockSize))

#define MM_ALLOCATE_GEN(FuncNamePrefix, ChunkSizeType, ChunkHdrTypeName)                           \
  typedef struct {                                                                                 \
    ChunkSizeType size;                                                                            \
    MM_ChunkFlags flags;                                                                           \
  } ChunkHdrTypeName;                                                                              \
                                                                                                   \
  static CMN_Rc FuncNamePrefix##_getFree(SL_MemoryBlockBasePtr aDataBasePtr,                       \
                                         SL_MemoryBlockSize aMemoryBlockSize,                      \
                                         SL_MemoryBlockSize* aFreeMemorySize)                      \
  {                                                                                                \
    if (!aDataBasePtr)                                                                             \
    {                                                                                              \
      return CMN_ENULLPTR;                                                                         \
    }                                                                                              \
    if (!aFreeMemorySize)                                                                          \
    {                                                                                              \
      return CMN_ENULLPTR;                                                                         \
    }                                                                                              \
                                                                                                   \
    ChunkHdrTypeName* curChunkHdr = CMN_CAST(ChunkHdrTypeName*, aDataBasePtr);                     \
    do                                                                                             \
    {                                                                                              \
      if (MM_CHUNK_HEADER_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, aDataBasePtr,               \
                                        aMemoryBlockSize))                                         \
      {                                                                                            \
        return CMN_ENOBUFS;                                                                        \
      }                                                                                            \
      if (MM_CHUNK_IS_LAST(curChunkHdr))                                                           \
      {                                                                                            \
        break;                                                                                     \
      }                                                                                            \
      if (MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, curChunkHdr->size, aDataBasePtr,   \
                                 aMemoryBlockSize))                                                \
      {                                                                                            \
        return CMN_ENOBUFS;                                                                        \
      }                                                                                            \
      curChunkHdr = CMN_CAST(ChunkHdrTypeName*, CMN_PTR_ADD_BYTES(curChunkHdr,                     \
          CMN_CAST(ChunkSizeType, sizeof(ChunkHdrTypeName)) + curChunkHdr->size));                 \
    } while(CMN_TRUE);                                                                             \
    CMN_VoidPtr dataEndPtr = CMN_PTR_ADD_BYTES(aDataBasePtr, aMemoryBlockSize);                    \
    CMN_VoidPtr nextAllocationDataPtr = CMN_PTR_ADD_BYTES(curChunkHdr, (sizeof(ChunkHdrTypeName)));\
    if (nextAllocationDataPtr >= dataEndPtr)                                                       \
    {                                                                                              \
      return CMN_ENOBUFS;                                                                          \
    }                                                                                              \
    /* Calculate needed padding after the header */                                                \
    CMN_Offset headerPadding;                                                                      \
    CMN_Rc cmnRc = CMN_getAlignmentPadding((CMN_Offset) nextAllocationDataPtr,                      \
        CMN_MEMORY_ALIGNMENT, &headerPadding);                                                     \
    if (isRcError(cmnRc))                                                                          \
    {                                                                                              \
      return cmnRc;                                                                                \
    }                                                                                              \
    /*                                                                                             \
     * Calculate total remaining space for data (remaining space                                   \
     *  without header and header padding).                                                        \
     */                                                                                            \
    CMN_Offset remainingSpace = CMN_CAST(CMN_Offset, CMN_PTR_SUB(dataEndPtr,                       \
        nextAllocationDataPtr));                                                                   \
    remainingSpace = CMN_CAST(CMN_Offset, CMN_PTR_SUB(remainingSpace, headerPadding));             \
    /*                                                                                             \
     * If the (end of the) remaining space is not aligned, decrease                                \
     *  the size by the needed amount.                                                             \
     */                                                                                            \
    CMN_Offset alignmentDiff = remainingSpace % CMN_MEMORY_ALIGNMENT;                              \
    *aFreeMemorySize = CMN_CAST(SL_MemoryBlockSize,                                                \
          CMN_PTR_SUB(remainingSpace, alignmentDiff));                                             \
    return CMN_OK;                                                                              \
  }                                                                                                \
                                                                                                   \
  static CMN_Rc FuncNamePrefix##_allocate(ChunkSizeType aBufSize, CMN_VoidPtr* aMemHandle,         \
                                          SL_MemoryBlockBasePtr aDataBasePtr,                      \
                                          SL_MemoryBlockSize aMemoryBlockSize)                     \
  {                                                                                                \
    (void) FuncNamePrefix##_getFree;                                                               \
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
    ChunkHdrTypeName* curChunkHdr = CMN_CAST(ChunkHdrTypeName*, aDataBasePtr);                     \
    do                                                                                             \
    {                                                                                              \
      if (MM_CHUNK_HEADER_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, aDataBasePtr,               \
                                        aMemoryBlockSize))                                         \
      {                                                                                            \
        return CMN_ENOBUFS;                                                                        \
      }                                                                                            \
      if (MM_CHUNK_IS_LAST(curChunkHdr))                                                           \
      {                                                                                            \
        break;                                                                                     \
      }                                                                                            \
      if (MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, curChunkHdr->size, aDataBasePtr,   \
                                 aMemoryBlockSize))                                                \
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
      curChunkHdr = CMN_CAST(ChunkHdrTypeName*, CMN_PTR_ADD_BYTES(curChunkHdr,                     \
          CMN_CAST(ChunkSizeType, sizeof(ChunkHdrTypeName)) + curChunkHdr->size));                 \
    } while(CMN_TRUE);                                                                             \
    if (candidateChunkHdr)                                                                         \
    {                                                                                              \
      MM_CHUNK_SET_USED(candidateChunkHdr);                                                        \
      *aMemHandle = CMN_PTR_ADD_BYTES(candidateChunkHdr, sizeof(ChunkHdrTypeName));                \
      return CMN_OK;                                                                            \
    }                                                                                              \
    if (MM_CHUNK_OUT_OF_BOUNDS(curChunkHdr, ChunkHdrTypeName, aBufSize, aDataBasePtr,              \
                               aMemoryBlockSize))                                                  \
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


/* -- Prototypes ------------------------------------------------------------- */
CMN_Rc MM_get_dpm_instanceData_context(SRTS_ContextPtr aCtx, SL_MemoryBlockBasePtr* dpmContext);
CMN_Rc MM_get_dpm_applicationModel_context(SRTS_ContextPtr aCtx,
                                           SL_MemoryBlockBasePtr* dpmContext);
CMN_Rc MM_get_dpm_instanceData_data(SRTS_ContextPtr aCtx, SL_MemoryBlockBasePtr* dpmData,
                                    SL_MemoryBlockSize* blockSize);

CMN_Rc MM_allocate_instanceData(SRTS_ContextPtr aCtx, CMN_BufferSize aBufSize, CMN_VoidPtr* aMemHandle);
/* free a given memory handle */
CMN_Rc MM_free_instanceData(SRTS_ContextPtr aCtx, CMN_VoidPtr aMemHandle);
/* free a given memory handle including its subsequent chunks */
CMN_Rc MM_freeSubsequentChunks_instanceData(SRTS_ContextPtr aCtx, CMN_VoidPtr aMemHandle);

CMN_Rc MM_allocate_applicationModel(SRTS_ContextPtr aCtx, CMN_BufferSize aBufSize, CMN_VoidPtr* aMemHandle);
CMN_Rc MM_free_applicationModel(SRTS_ContextPtr aCtx, CMN_VoidPtr aMemHandle);

CMN_Rc MM_reset(SRTS_ContextPtr aCtx);

size_t MM_getSizeOfMmChunkHeaderDT();
CMN_Rc MM_getFreeMemoryOfInstanceData(SRTS_ContextPtr aCtx, SL_MemoryBlockSize* aFreeMemorySize);
CMN_Rc MM_getFreeMemoryOfApplicationModel(SRTS_ContextPtr aCtx, SL_MemoryBlockSize* aFreeMemorySize);

#endif /* MEMORY_MANAGER_H_ */

