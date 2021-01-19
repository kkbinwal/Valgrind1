/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_STROPS_H_
#define COMMON_STROPS_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>

/** @defgroup CMN_STROPS Runtime string wrapper functions
 *
 *  Wrapper functions for the C-runtime string functions.
 *  This functions should be used in the implementation of the
 *  library provider interface functions and within the sRTS.
 *
 *@{*/

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Offset of the first difference in a string compare.
 */
typedef int32_t CMN_StrDiff;

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Case insensitive string compare.
 * @param[in] aString1 first string to compare
 * @param[in] aString2 second string to compare
 * @param[out] aStringDiff the difference between the two strings.
 * It is zero if the two strings are the same (with ignoring the case).
 * @return Error code
 * @retval #CMN_EINVAL A parameter is NULL
 * @retval #CMN_OK
 */
CMN_Rc CMN_strcasecmp(char const* aString1, char const* aString2, CMN_StrDiff* aStringDiff);

/**
 * String compare.
 * @param[in] aString1 first string to compare
 * @param[in] aString2 second string to compare
 * @param[out] aStringDiff the difference between the two strings.
 * It is zero if the two strings are the same.
 * @return Error code
 * @retval #CMN_EINVAL A parameter is NULL
 * @retval #CMN_OK
 */
CMN_Rc CMN_strcmp(char const* aString1, char const* aString2, CMN_StrDiff* aStringDiff);

/**
 * Common string copy function.
 * @param[in] aDestString pointer to the string to write to
 * @param[in] aSize maximum number of characters to write (including the null terminator)
 * @param[in] aSrcString pointer to the string to copy from
 * @return Error code
 * @retval #CMN_ESTRCPY
 * @retval #CMN_OK
 */
CMN_Rc CMN_strcpy(char* aDestString, CMN_Size aSize, char const* aSrcString);

/**
 * Common string splitter function.
 * @param[in] aString pointer to the string to tokenize
 * @param[in] aDelim pointer to the string delimeters
 * @param[in] aToken pointer to the beginning of the next token or NULL if there are no more tokens.
 * @param[in] aNextToken used to store position information between calls to the function (not supported for all systems).
 * @return Error code
 * @retval #CMN_ESTRTOK
 * @retval #CMN_OK
 */
CMN_Rc CMN_strtok(char* aString, char const* aDelim, char** aToken, char **aNextToken);

/**
 * Common string concatenating function.
 * @param[in] aDestString pointer to the string to append to
 * @param[in] aDestBufferSize buffer size of aDestString
 * @param[out] aSrcString pointer to the string to copy from
 * @return Error code
 * @retval #CMN_ESTRCAT
 * @retval #CMN_OK
 */
CMN_Rc CMN_strcat(char* aDestString, CMN_Size aDestBufferSize, char const* aSrcString);

/**
 * Common string writer from formatted data.
 * @param[out] aDestString pointer to the string to write
 * @param[in] aSize maximum number of character to write (including the null terminator)
 * @param[in] aTemplate string which contains the data format
 * @param[in] ... argument specifying data to write into string
 * @return Error code
 * @retval #CMN_ESPRINTF
 * @retval #CMN_OK
 */
CMN_Rc CMN_sprintf(char* aDestString, CMN_Size aSize, char const* aTemplate, ...);

/**
 * Common string length calculator. It returns the length of the string if it is smaller
 * than aBufferSize bytes. Otherwise it returns aBufferSize.
 * @param[in] aString pointer to the null-terminated byte string
 * @param[in] aBufferSize maximum number of characters to examine
 * @param[out] aLength the length of the given string
 * @return Error code
 * @retval #CMN_ESTRLEN
 * @retval #CMN_OK
 */
CMN_Rc CMN_strlen(char const* aString, CMN_Size aBufferSize, CMN_Size *aLength);

/**
 * Common memory copy function.
 * @param[out] aDest pointer to the object to copy to
 * @param[in] aDestSize maximum number of bytes to modify in the destination
 * @param[in] aSrc pointer to the object to copy from
 * @param[in] aCount number of bytes to copy
 * @return Error code
 * @retval #CMN_EMEMCPY
 * @retval #CMN_OK
 */
CMN_Rc CMN_memcpy(void* aDest, CMN_Size aDestSize, void const* aSrc, CMN_Size aCount);

/**
 * Locate last occurrence of character in string.
 * @param[out] aResult pointer to the result string
 * @param[in] aString pointer to the string to be searched
 * @param[in] aCharacter the character that should be searched for
 * @return Error code
 * @retval #CMN_ESTRRCHR
 * @retval #CMN_OK
 */
CMN_Rc CMN_strrchr(const char* aString, int aCharacter, char** aResult);

/*@}*//* CMN_STROPS */

#endif /* COMMON_STROPS_H_ */
