/**
 * @file
 * Functions and types for CRC checks.
 *
 * Generated on Tue Oct  8 14:30:24 2019
 * by pycrc v0.9.2, pycrc.org
 * using the configuration (CRC32/AUTOSAR):
 *  - Width         = 32
 *  - Poly          = 0xf4acfb13
 *  - XorIn         = 0xffffffff
 *  - ReflectIn     = True
 *  - XorOut        = 0xffffffff
 *  - ReflectOut    = True
 *  - Algorithm     = table-driven
 *
 * This file defines the functions SL_crc32_init(), SL_crc32_update() and SL_crc32_finalize().
 *
 * The SL_crc32_init() function returns the inital crc value and must be called
 * before the first call to SL_crc32_update().
 * Similarly, the SL_crc32_finalize() function must be called after the last call
 * to SL_crc32_update(), before the crc is being used.
 * is being used.
 *
 * The SL_crc32_update() function can be called any number of times (including zero
 * times) in between the SL_crc32_init() and SL_crc32_finalize() calls.
 *
 * This pseudo-code shows an example usage of the API:
 * @code{.c}
 * SL_crc32_t crc;
 * unsigned char data[MAX_DATA_LEN];
 * size_t data_len;
 *
 * crc = SL_crc32_init();
 * while ((data_len = read_data(data, MAX_DATA_LEN)) > 0) {
 *     crc = SL_crc32_update(crc, data, data_len);
 * }
 * crc = SL_crc32_finalize(crc);
 * @endcode
 *
 * If the update function needs to be called only once,
 * the SL_crc32() can be used.
 */
#ifndef SYSTEM_LAYER_CRC32_H
#define SYSTEM_LAYER_CRC32_H

#include <stdlib.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif


/**
 * The definition of the used algorithm.
 *
 * This is not used anywhere in the generated code, but it may be used by the
 * application code to call algorithm-specific code, if desired.
 */
#define CRC_ALGO_TABLE_DRIVEN 1


/**
 * The type of the CRC values.
 *
 * This type must be big enough to contain at least 32 bits.
 */
typedef uint_fast32_t SL_crc32_t;


/**
 * Calculate the initial crc value.
 *
 * @return     The initial crc value.
 */
static inline SL_crc32_t SL_crc32_init(void)
{
    return 0xffffffffU;
}


/**
 * Update the crc value with new data.
 *
 * @param[in] aCrc      The current crc value.
 * @param[in] aData     Pointer to a buffer of aDataLen bytes.
 * @param[in] aDataLen  Number of bytes in the aData buffer.
 * @return              The updated crc value.
 */
SL_crc32_t SL_crc32_update(SL_crc32_t aCrc, uint8_t const* aData, size_t aDataLen);


/**
 * Calculate the final crc value.
 *
 * @param[in] crc  The current crc value.
 * @return     The final crc value.
 */
static inline SL_crc32_t SL_crc32_finalize(SL_crc32_t aCrc)
{
    return aCrc ^ 0xffffffffU;
}

/**
 * Calculate the final crc value.
 *
 * @param[in] aData     Pointer to a buffer of aDataLen bytes.
 * @param[in] aDataLen  Number of bytes in the aData buffer.
 */
SL_crc32_t SL_crc32(uint8_t const* aData, size_t aDataLen);


#ifdef __cplusplus
}           /* closing brace for extern "C" */
#endif

#endif      /* SYSTEM_LAYER_CRC32_H */
