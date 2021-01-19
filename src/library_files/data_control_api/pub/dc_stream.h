/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DC_STREAM
#define DC_STREAM

/* -- Include files --------------------------------------------------------- */
#include <dc_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

/** @defgroup DCA Data Control API
 *
 * @brief Data Control API
 *
 *@{*/

/** @defgroup STM Streams
 *
 * @brief Streams
 *
 * Functions to open/close/write to streams.
 * Streams are used for upload/download of hardware-config/application-model etc.
 *@{*/

/**
 * Set current stream.
 *
 * If the stream is closed (current stream type is #CMN_StreamTypeNone), the stream can be opened
 * (set to a valid stream type other than #CMN_StreamTypeNone).
 * If the stream is opened (current stream type other than #CMN_StreamTypeNone), it can
 * be closed. (by setting #CMN_StreamTypeNone)
 *
 * @param aContext the SRTS context
 * @param aRequest the dcm request to use for response messages
 * @param aStreamType the stream type to set
 * @param aStreamDirection either upload or download
 * @return error code
 */
DC_Rc DC_setStream(SRTS_ContextPtr aContext, DCM_Request const* aRequest, CMN_StreamType aStreamType, CMN_StreamDirection aStreamDirection);

/*@}*//* STM Streams */

/*@}*//* DCA Data Control API */

#endif /* DC_STREAM */
