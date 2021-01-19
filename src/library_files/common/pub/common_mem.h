/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_MEM_H
#define COMMON_MEM_H

/* -- Include files --------------------------------------------------------- */
#include <stdint.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define INVALID_BLOCK_HANDLE 0u
#define INVALID_COMMENT_HANDLE 0u
#define INVALID_CONNECTION_HANDLE 0u
#define INVALID_VARIABLE_HANDLE 0u
#define CMN_MAX_LITERAL_LEN 128 /**< maximum string length of literal values */
#define CMN_MAX_DCM_MSG_CHUNK_SIZE 1024  /**< maximum dcm message chunk size */
#define CMN_PIN_OFFSET 15u /**< offset from one pin to the next pin */
#define CMN_SIMPLE_BLOCK_HEIGHT 14 /**< height of a simple block */
#define CMN_BLOCK_TOP_OFFSET_FROM_SNAP_POINT -7 /** vertical snap position is first pin **/
#define CMN_MAX_BLOCK_NAME_LENGTH 255 /**< maximum string length of block names */

#define CMN_DRAWING_INST_ELEMENT_ID_BLOCK 0
#define CMN_DRAWING_INST_ELEMENT_ID_INPUT_PIN 1
#define CMN_DRAWING_INST_ELEMENT_ID_OUTPUT_PIN 2
#define CMN_DRAWING_INST_ELEMENT_ID_CONNECTION 3
#define CMN_DRAWING_INST_ELEMENT_ID_COMMENT 4

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Block handle.
 */
typedef uint16_t CMN_BlockHandle;

/**
 * Connection handle.
 */
typedef uint16_t CMN_ConnectionHandle;

/**
 * Comment handle.
 */
typedef uint16_t CMN_CommentHandle;

/**
 * Variable handle.
 */
typedef uint16_t CMN_VariableHandle;

/**
 * Pin iterator.
 */
typedef uint16_t CMN_PinIterator;

/**
 * Block iterator.
 */
typedef uint16_t CMN_BlockIterator;

/**
 * Connection iterator.
 */
typedef uint16_t CMN_ConnectionIterator;

/**
 * Comment iterator.
 */
typedef uint16_t CMN_CommentIterator;

/**
 * Variable iterator.
 */
typedef uint16_t CMN_VariableIterator;

/**
 * Iterator type used for sequence number mapping.
 */
typedef uint16_t CMN_SequenceNumberIterator;

/**
 * Sequence number.
 */
typedef uint16_t CMN_SequenceNumber;

/**
 * Geometric dimension.
 */
typedef uint16_t CMN_Dimension;

/**
 * Geometric dimension difference.
 */
typedef int16_t CMN_DimensionDiff;

/** @ingroup CMN_LP
 * Data type for pin indices and counts.
 */
typedef uint8_t CMN_PinCount;

/** @ingroup CMN_LP
 * Pin handle used for connections.
 * Index, input and output pins starting with index zero.
 */
typedef CMN_PinCount CMN_PinHandle;

/** @ingroup CMN_LP
 * Index of IO pin display in visual block.
 *
 * Input pins can be displayed on the left and top edge of the block.
 * Output pins can be displayed on the right and bottom edge of a block.
 * Pin positions go from top to bottom (left edge, right edge) or
 * from left to right (top edge, bottom edge).
 * Pin indices start at index 0.
 * Used indices may have gaps.
 */
typedef CMN_PinCount CMN_PinDisplayIndex;

/**
 * IO description list index.
 *
 * Minimum lifecycle of index is between changes of system layer
 * io configuration.
 * After io configuration change the model must be verified again.
 * At the verify transition it must be ensured, that the io resource
 * still exists in the new configuration. (for each io index the triple
 * (data type, direction, name) must be identical in both the
 * application model block and the io provider io description)
 */
typedef uint16_t CMN_IoDescrListIdx;

/* -- Prototypes ------------------------------------------------------------ */

/*
 * Creates drawing instruction id.
 *
 * bits 0-7: pin index (input and output pins starting at 0) or 0
 * bits 8-23: block or connection handle
 * bits 24-26: element id CMN_DRAWING_INST_ELEMENT_ID_..
 *
 * @param aElementId drawing instruction element id. @see CMN_DRAWING_INST_ELEMENT_ID_BLOCK etc.
 * @param aElementHandle block/connection/comment handle
 * @param aIndex either:
 *              pin index (input and output pins starting at 0)
 *              line index (for connections)
 *              or 0 (if not a pin or a line)
 * @return The created drawing instruction id.
 */
uint32_t CMN_createDrawingInstId(uint8_t aElementId, uint16_t aElementHandle, uint8_t aIndex);

#endif /* COMMON_MEM_H */
