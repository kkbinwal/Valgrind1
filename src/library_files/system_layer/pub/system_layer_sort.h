/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_SORT_H
#define SYSTEM_LAYER_SORT_H

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SL System Layer Interface
 *
 *  In order to integrate the Safe RTS to a specific platform, this
 *  interfaces have to be implemented by the platform vendor.
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Comparison function which returns ​a negative integer value if the first
 * argument is less than the second, a positive integer value if the first
 * argument is greater than the second and zero if the arguments are equal.
 * The function must not modify the objects passed to it and must return
 * consistent results when called for the same objects, regardless of their
 * positions in the array.
 */
typedef int (*SL_CtxCompareFn)(CMN_VoidConstPtr, CMN_VoidConstPtr, CMN_VoidPtr );

/* -- Prototypes ------------------------------------------------------------ */

/** @name Sorting
  */
/*@{*/



/**
 * Sorting function. (used in the command sequence ordering algorithm)
 *
 * Currently, this function implementation is possibly NOT reentrant
 * (because it uses global variables).
 * This is okay, as long as sRTS is cooperatively scheduled/not multi-threaded.
 *
 * See also the qsort and qsort_s libc function documentation.
 *
 * @param aArray Pointer to the array to sort
 * @param aCount Number of element in the array
 * @param aSize Size of each element in the array in bytes
 * @param aCompareFunction
 *   The compare function is used to perform the comparison on the array
 *   elements. This function is called with two pointer arguments and should
 *   return an integer less than, equal to, or greater than zero corresponding
 *   to whether its first argument is considered less than, equal to, or
 *   greater than its second argument.
 * @param aSortContext Additional parameter passed to aCompareFunction as third
 *                     parameter. Possibly NULL.
 * @return return code
 * @retval #SL_OK
 * @retval #CMN_ENULLPTR aArray or aCompareFunction are NULL
 * @retval #CMN_EINVAL
 */
SL_Rc SL_safeCtxSort(CMN_VoidPtr aArray, size_t aCount, size_t aSize, SL_CtxCompareFn aCompareFunction, CMN_VoidPtr aSortContext);

/*@}*/

/*@}*/

#endif /* SYSTEM_LAYER_SORTING_H */
