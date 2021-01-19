/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DATA_CONTROL_MESSAGING_TRANSFER_APM_IMPL_H
#define DATA_CONTROL_MESSAGING_TRANSFER_APM_IMPL_H


/* -- Include files --------------------------------------------------------- */

#include <data_control_messaging.h>
#include <common_types_complex.h>
#include <common_mem.h>

/** @defgroup DCM Data Control Messaging
 *
 * @brief Data Control Messaging
 *
 *@{*/


/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Block handle map.
 * Implemented as array.
 * The value of the array at index 'Hnondefrag - 1' is 'Hdefrag'.
 * Hnondefrag...fragmented (old) block handle
 * Hdefrag...defragmented (new) block handle
 */
typedef CMN_BlockHandle DCM_BlockHandleMap[MAX_NUM_OF_BLOCKS];

/**
 * Message Header
 */
typedef struct {
  uint16_t messageType; /**< type of message */
  uint16_t messageLength; /**< length of message */
} DCM_MessageHeader;

typedef struct
{
  DCM_String magicNumber;                                /**< Magic number "SRTS APM" at apm begin */
  uint32_t apmVersion;                                   /**< Version of the APM binary stream interface */
  uint16_t variableCount;                                /**< Number of variables in application model */
  uint16_t blockCount;                                   /**< Number of blocks in application model */
  uint16_t connectionCount;                              /**< Number of connections in application model */
  uint16_t commentCount;                                 /**< Number of comments in application model */
} DCM_ApplicationModelStreamHeader;

/**
 * State of the application model stream
 */
typedef struct
{
  uint16_t headerTransferCount;             /**< Header transfer Count */
  uint16_t blockTransferCount;              /**< Block transfer Count */
  uint16_t connectionTransferCount;         /**< Connection transfer Count */
  uint16_t variableTransferCount;           /**< Variable transfer Count */
  uint16_t commentTransferCount;            /**< Comment transfer Count */
  CMN_Bool transferStarted;                 /**< Flag used for detection of first transfer */
  DCM_ApplicationModelStreamHeader header;  /**< Header information */
  /**< Buffer for upload/download apm messages */
  uint8_t buffer[DCM_MESSAGE_HEADER_LENGTH + DCM_MESSAGE_MAX_PAYLOAD_LENGTH];
  uint16_t messagesReadIndex;               /**< Index of next byte to read from upload messages buffer */
  uint16_t messagesWriteIndex;              /**< Index of next byte to write to upload messages buffer */
  uint16_t maximumPacketLength;             /**< Maximum download binary packet length */
} DCM_ApplicationModelStream;

/* -- Prototypes ------------------------------------------------------------ */

uint32_t DCM_internalDownloadApplicationModel(SRTS_ContextPtr aContext, DCM_Connection* aConnection, DCM_Request const* aRequest, uint16_t aMaximumPacketLength);
uint32_t DCM_internalConvertOutputPinIndex(SRTS_ContextPtr srtsContext, CMN_BlockHandle outBlock, CMN_PinHandle* outPin, CMN_Bool aFromClientToSrts);
uint32_t DCM_internalIterateVariables(SRTS_ContextPtr aContext, CMN_VariableIterator* aIterator, CMN_DataInterfaceExtVariable* aItem, DCM_MessageModelVariable* aModelItem);
uint32_t DCM_internalIterateBlocks(SRTS_ContextPtr aContext, CMN_VariableIterator* aIterator, CMN_DataInterfaceExtBlock* aItem, DCM_MessageModelBlock* aModelItem);
uint32_t DCM_internalIterateConnections(SRTS_ContextPtr aContext, CMN_VariableIterator* aIterator, CMN_DataInterfaceExtConnection* aItem, DCM_MessageModelConnection* aModelItem);
uint32_t DCM_internalIterateComments(SRTS_ContextPtr aContext, CMN_VariableIterator* aIterator, CMN_DataInterfaceExtComment* aItem, DCM_MessageModelComment* aModelItem);
uint32_t DCM_internalUploadApplicationModel(SRTS_ContextPtr aContext, DCM_Connection* aConnection, const DCM_Request* aRequest, const uint8_t* aData, size_t aLength);
uint32_t DCM_internalBuildBlockHandleMap(SRTS_ContextPtr aContext, DCM_BlockHandleMap aBlockHandleMap);
uint32_t DCM_internalApplyBlockHandleMap(DCM_BlockHandleMap aBlockHandleMap, CMN_BlockHandle aBlockHandle, CMN_BlockHandle* aMappedBlockHandle);

/**
 * Initializes a DCM_String.
 *
 * In case of an error the DCM String is not modified.
 *
 * @param[in] aString Initial value of the string. The string length must be less than #DPM_SM_MAX_STRING_BUFFER_SIZE.
 * @param[out] aDcmString The DCM String to initialize.
 * @return return code
 * @retval #DCM_STATUS_CODE_ERROR Parameter(s) null.
 * @retval #DCM_STATUS_CODE_ERROR Maximum string length exceeded.
 * @retval #DCM_STATUS_CODE_OK DCM String is successfully initialized.
 */
uint32_t DCM_internalInitDcmString(char const* aString, DCM_String* aDcmString);


/**
 * Initializes a C String from a DCM_String.
 *
 * @param[out] aString The C String to initialize. Buffer length must be at least #DPM_SM_MAX_STRING_BUFFER_SIZE.
 * @param[in] aDcmString The DCM String. The string length must be less than #DPM_SM_MAX_STRING_BUFFER_SIZE.
 * @return return code
 * @retval #DCM_STATUS_CODE_ERROR Parameter(s) null.
 * @retval #DCM_STATUS_CODE_ERROR Maximum string length exceeded.
 * @retval #DCM_STATUS_CODE_OK C String is successfully initialized.
 */
uint32_t DCM_internalInitStringFromDcmString(char* aString, DCM_String const* aDcmString);

/* -- Functions ------------------------------------------------------------- */

/*@}*//* DCM Data Control Messaging */

#endif /* DATA_CONTROL_MESSAGING_TRANSFER_APM_IMPL_H */
