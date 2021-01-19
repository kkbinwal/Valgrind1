/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_BITFIELDS_H_
#define COMMON_BITFIELDS_H_

/* -- Include files --------------------------------------------------------- */
#include <common_mem.h>
#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define CMN_BITFIELD_WORD_BITS (sizeof(CMN_BitfieldWord)*8)

#define CMN_BITFIELD_LENGTH_IN_WORDS(length) ( ( (length) + CMN_BITFIELD_WORD_BITS - 1) / CMN_BITFIELD_WORD_BITS)

/**
 * Helper macro to define a bitfield of given length (in bits)
 */
#define CMN_Bitfield(name, length) CMN_BitfieldWord name[CMN_BITFIELD_LENGTH_IN_WORDS(length)]

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Base type for bitfields
 */
typedef uint32_t CMN_BitfieldWord;

/**
 * Index type to be used to address bits in bitfields
 */
typedef uint16_t CMN_BitfieldIndex;

/**
 * Bitfield is represented as an array of unsigned words
 */
typedef CMN_BitfieldWord CMN_BitfieldType[];

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Set the whole bitfield to zero. Length is given in bits
 */
void CMN_bitfieldClearAll(CMN_BitfieldType bitfield, uint16_t length);

/**
 * Set the given bit in the bitfield to 1
 */
void CMN_bitfieldSet(CMN_BitfieldType bitfield, CMN_BitfieldIndex index);

/**
 * Set the given bit in the bitfield to 0
 */
void CMN_bitfieldClear(CMN_BitfieldType bitfield, CMN_BitfieldIndex index);

/**
 * Get the value of the given bit in the bitfield
 */
CMN_Bool CMN_bitfieldGet(CMN_BitfieldType bitfield, CMN_BitfieldIndex index);

/**
 * Returns with true, if the bitfield has only zeroes
 */
CMN_Bool CMN_bitfieldIsZero(CMN_BitfieldType bitfield, uint16_t length);

#endif /* COMMON_BITFIELDS_H_ */
