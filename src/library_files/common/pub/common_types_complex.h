#ifndef COMMON_TYPES_COMPLEX_H_
#define COMMON_TYPES_COMPLEX_H_

#include <config_mem.h>
#include <common_types.h>

/**
 * Data Interface Connection.
 *
 * Structure which contains all input data for the model.
 */
typedef struct {
  CMN_BlockHandle inBlock;                                 /**< Input block handle. */
  CMN_PinHandle inPin;                                     /**< Input pin handle. */
  CMN_BlockHandle outBlock;                                /**< Output block handle. */
  CMN_PinHandle outPin;                                    /**< Output pin handle. */
  CMN_DimensionDiff lineLengths[CMN_MAX_LINES_PER_CONNECTION]; /**< lengths of the segments
                                                          (alternating x and y),
                                                          terminated by zero. */
  char const* inputPinName;                                /**< Input pin name, 0 terminated */
  char const* outputPinName;                               /**< Output pin name, 0 terminated */
} CMN_DataInterfaceConnection;

/**
 * Data Interface Connection Extended.
 *
 * Same as @ref CMN_DataInterfaceConnection but additional components.
 */
typedef struct {
  CMN_ConnectionHandle handle;  /**< The handle of the item (0 indicates an
                                   invalid item, added by application model). */
  CMN_BlockHandle inBlock;      /**< Input block handle. */
  CMN_PinHandle inPin;          /**< Input pin handle. */
  CMN_BlockHandle outBlock;     /**< Output block handle. */
  CMN_PinHandle outPin;         /**< Output pin handle. */
  CMN_DimensionDiff lineLengths[CMN_MAX_LINES_PER_CONNECTION]; /**< lengths of the segments
                                                          (alternating x and y),
                                                          terminated by zero. */
  char const* inputPinName;     /**< Input pin name, 0 terminated */
  char const* outputPinName;    /**< Output pin name, 0 terminated */
} CMN_DataInterfaceExtConnection;


#endif /* COMMON_TYPES_COMPLEX_H_ */
