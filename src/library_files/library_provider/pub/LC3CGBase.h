/* Copyright (c) logi.cals. All rights reserved. */

#ifndef LC3CGBASE_H
#define LC3CGBASE_H

#include <stdint.h>

#include <LCAPI.h>

typedef LCoplck_EPDB * LCoplck_EPDB_PTR;
typedef enum {LC_EL_true = 1, LC_EL_false = 0} LC_TD_IEC_BOOLIMPL;

LCoplck_EPDB_PTR LCocc_queryEP(unsigned long idx);
unsigned long LCocc_queryEPCount(void);

#define LCCG_StructAttrib
#define LC_INIT_BOOL(p) (*(p) = 0)
#define RT_TARGET_TIME_FREQU 1000000
#define RT_CC_CONST_LL(val)      val##LL
#define LC_TIME_TO_TICKS(ts,tns)      /*lint --e{845} */( ((LC_TD_LINT)(ts) * RT_TARGET_TIME_FREQU) + ((LC_TD_LINT)(tns) * RT_TARGET_TIME_FREQU / RT_CC_CONST_LL(1000000000)) )
#define LC_TIME_VALUE(ts,tns)         LC_TIME_TO_TICKS(ts,tns)
#define LC_INIT_TIME(p) *(p) = LC_TIME_VALUE(0,0)

#endif /* LC3CGBASE_H */
