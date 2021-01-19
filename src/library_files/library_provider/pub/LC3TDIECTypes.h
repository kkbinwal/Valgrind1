/* Copyright (c) logi.cals. All rights reserved. */

#ifndef LC3TDIECTYPES_H
#define LC3TDIECTYPES_H

#include <LC3CGBase.h>

typedef unsigned char LcCgChar;

typedef uint8_t  RT_TD_IEC_BOOL;

typedef int8_t   RT_TD_IEC_SINT;
typedef int16_t  RT_TD_IEC_INT;
typedef int32_t  RT_TD_IEC_DINT;
typedef int64_t  RT_TD_IEC_LINT;

typedef uint8_t  RT_TD_IEC_USINT;
typedef uint16_t RT_TD_IEC_UINT;
typedef uint32_t RT_TD_IEC_UDINT;
typedef uint64_t RT_TD_IEC_ULINT;

typedef uint8_t  RT_TD_IEC_BYTE;
typedef uint16_t RT_TD_IEC_WORD;
typedef uint32_t RT_TD_IEC_DWORD;
typedef uint64_t RT_TD_IEC_LWORD;

typedef float    RT_TD_IEC_REAL;
typedef double   RT_TD_IEC_LREAL;

typedef int64_t  RT_TD_IEC_TIME;
typedef int64_t  RT_TD_IEC_DATE;
typedef int64_t  RT_TD_IEC_TOD;
typedef int64_t  RT_TD_IEC_DT;

typedef RT_TD_IEC_BOOL      LC_TD_BOOL;

typedef RT_TD_IEC_SINT      LC_TD_SINT;
typedef RT_TD_IEC_INT       LC_TD_INT;
typedef RT_TD_IEC_DINT      LC_TD_DINT;
typedef RT_TD_IEC_LINT      LC_TD_LINT;

typedef RT_TD_IEC_USINT     LC_TD_USINT;
typedef RT_TD_IEC_UINT      LC_TD_UINT;
typedef RT_TD_IEC_UDINT     LC_TD_UDINT;
typedef RT_TD_IEC_ULINT     LC_TD_ULINT;

typedef RT_TD_IEC_BYTE      LC_TD_BYTE;
typedef RT_TD_IEC_WORD      LC_TD_WORD;
typedef RT_TD_IEC_DWORD     LC_TD_DWORD;
typedef RT_TD_IEC_LWORD     LC_TD_LWORD;

typedef RT_TD_IEC_REAL      LC_TD_REAL;
typedef RT_TD_IEC_LREAL     LC_TD_LREAL;

typedef RT_TD_IEC_TIME      LC_TD_TIME;      /* RTS specific - 64bit, Tick based */
typedef RT_TD_IEC_DATE      LC_TD_DATE;
typedef RT_TD_IEC_TOD       LC_TD_TOD;
typedef RT_TD_IEC_DT        LC_TD_DT;

#endif /* LC3TDIECTYPES_H */
