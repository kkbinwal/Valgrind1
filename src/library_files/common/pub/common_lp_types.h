/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_LP_TYPES_H_
#define COMMON_LP_TYPES_H_

/* -- Include files --------------------------------------------------------- */
#include <ssr_slgx_platform_data.h>
#include <stddef.h>

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/** @defgroup CMN_LP Common Types and Structures (for library provider)
 *
 *  Common Types and Structures (can be used from the library provider and the sRTS integrator).
 */

/** @addtogroup CMN_LP
 *@{*/

/**
 * Return code.
 *
 * bit0  - bit11: 12 bit error code, a value of 0x000 is no error / ok<br>
 * bit12 - bit15:  4 bit module id, see base return codes<br>
 * bit16        :  always 1<br>
 *
 * @see #CMN_APM_RC_BASE
 * @see #CMN_CMN_RC_BASE
 * @see #CMN_DPM_RC_BASE
 * @see #CMN_INP_RC_BASE
 * @see #CMN_IO_RC_BASE
 * @see #CMN_LP_RC_BASE
 * @see #CMN_MM_RC_BASE
 * @see #CMN_SL_RC_BASE
 * @see #CMN_SSH_RC_BASE
 * @see #CMN_ENTRY_RC_BASE
 * @see #CMN_PIL_RC_BASE
 */
typedef uint32_t CMN_Rc;

/**
 * Size
 */
typedef size_t CMN_Size;

/**
 * Offset
 */
typedef ptrdiff_t CMN_Offset;

/**
 * Buffer size.
 */
typedef ptrdiff_t CMN_BufferSize;


/**
 * Data type enum.
 *
 * Enumerates data types. Structures and strings are omitted intentionally.
 */
//BACR - enumeration moved to "ssr_slgx_platform_data.h"

/**
 * String Buffer Descriptor.
 *
 * If string data with unspecified size is to be returned, the caller allocates string
 * buffer space and passes the location and the size of that space to processing
 * function via a string buffer descriptor.
 */
typedef struct {
  CMN_BufferSize len; /**< Size of the buffer. */
  char* ptr;          /**< Points to the location of the string data. */
} CMN_StringBufferDesc;


/* -- Forward decls --------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */


/*@}*/ /* CMN_LP */

#endif
