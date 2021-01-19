#ifndef LCAPI_H
#define LCAPI_H

#include <stdint.h>

typedef struct _lcoplck_epdb_1_impl LCoplck_EPDB;
typedef struct _lcoplck_task_1_impl LCoplck_TASK;
typedef struct _lcoplck_physicalvaraddress LCoplck_PhysicalVarAddress;
typedef unsigned long LCoosResultCodeImpl;
typedef int64_t LCoosHRCTime;

typedef enum _LCoplck_StartMode
{
   LCoplck_ColdStart,
   LCoplck_WarmStart,
   LCoplck_ReloadStart,
   LCoplck_Continue,
   LCoplck_NOTStarted,
   LCoplck_CycleStart,
   LCoplck_Disable,
   LCoplck_Stop,
   LCoplck_Kill,
   LCoplck_Unload,
   LCoplck_Load,
   LCoplck_SM_InitCycle,
   LCoplck_SM_StopStart,
   LCoplck_SM_StopCycle,
   LCoplck_UnknownSM,
   LCoplck_SM_unused = 0xff
} LCoplck_StartMode;

/* data type declarations */
typedef uint8_t LCoccFT_EntryFunc(LCoplck_EPDB *epdb);

typedef void LCoccFT_PreEntryFunc(LCoplck_EPDB *epdb);

typedef void LCoccFT_PostEntryFunc(LCoplck_EPDB *epdb);
typedef unsigned LCoccFT_InitFunc(LCoplck_EPDB *epdb, LCoplck_StartMode s);

typedef unsigned LCoccFT_ReInitFunc(LCoplck_EPDB *newEP, LCoplck_EPDB *oldEP, unsigned long flags);
typedef unsigned LCoccFT_VendorHookFunc(LCoplck_EPDB *epdb, LCoplck_StartMode s);

typedef unsigned LCoccFT_getData(LCoplck_PhysicalVarAddress const *pA, void *buffer, unsigned long size);
typedef unsigned LCoccFT_setData(LCoplck_PhysicalVarAddress const *pA, void const *buffer, unsigned long size);

typedef unsigned LCoccFT_mapDataAddress(LCoplck_PhysicalVarAddress *addr,LCoplck_EPDB const *newEP);

typedef unsigned LCoccFT_getDataError(LCoplck_PhysicalVarAddress const *pA, unsigned pDataErrorType, LCoosResultCodeImpl *pError);
typedef unsigned LCoccFT_setDataError(LCoplck_PhysicalVarAddress const *pA, unsigned pDataErrorType, LCoosResultCodeImpl pError);

typedef unsigned long LCoccFT_QueryRetainedDataSize(LCoplck_EPDB* pEpdb);
typedef unsigned long LCoccFT_GetRetainedData(LCoplck_EPDB* pEpdb, void* pBuffer);
typedef unsigned long LCoccFT_SetRetainedData(LCoplck_EPDB* pEpdb, void* pBuffer);

struct _lcoplck_task_1_impl
{
   unsigned int sizeOfThis;
   char const * name;
   unsigned long id;
   LCoplck_PhysicalVarAddress * singleVar;
   unsigned char single;
   LCoplck_PhysicalVarAddress * intervalVar;
   LCoosHRCTime interval;
   LCoplck_PhysicalVarAddress * priorityVar;
   unsigned long priority;
   unsigned long version;
   unsigned long flags;
   LCoccFT_getData * getDataFun;
   LCoccFT_setData * setDataFun;
   void * tdb;
   void * reserved1;
   void * reserved2;
};

struct _lcoplck_epdb_1_impl
{
   unsigned int sizeOfThis;
   char const * name;
   unsigned long id;
   LCoccFT_EntryFunc * entry;
   LCoccFT_PreEntryFunc * preEntry;
   LCoccFT_PostEntryFunc * postEntry;
   LCoccFT_InitFunc * init;
   LCoccFT_ReInitFunc * reinit;
   LCoplck_EPDB * owner;
   LCoplck_TASK * task;
   void * thisData;
   unsigned long sizeOfThisData;
   void * ccodeData;
   void * vendorData;
   unsigned long version;
   unsigned long flags;
   LCoccFT_getData * getDataFun;
   LCoccFT_setData * setDataFun;
   LCoccFT_mapDataAddress * mapDataAdrFun;
   void * eepdb;
   LCoccFT_VendorHookFunc * hookFun;
   LCoosHRCTime mEpCycleStartTime;
   unsigned mBPHandleEnabled;
   unsigned long * mHPriorTaskWaiting;
   LCoccFT_getDataError * mGetDataErrorFun;
   LCoccFT_setDataError * mSetDataErrorFun;
   LCoccFT_QueryRetainedDataSize* mQueryRetainedDataSizeFun;
   LCoccFT_GetRetainedData * mGetRetainedDataFun;
   LCoccFT_SetRetainedData * mSetRetainedDataFun;
   void * reserved1;
   void * reserved2;
};

#endif /* LCAPI_H */

