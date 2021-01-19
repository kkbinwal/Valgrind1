/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DATA_CONTROL_MESSAGING_IMPL_H
#define DATA_CONTROL_MESSAGING_IMPL_H


/* -- Include files --------------------------------------------------------- */

#include <data_control_messaging.h>
#include <entry.h>
#include <system_layer.h>

/** @defgroup DCM Data Control Messaging
 *
 * @brief Data Control Messaging
 *
 *@{*/

/* -- Externals ------------------------------------------------------------- */

extern DCM_sendMessageCallback* g_SendMessageCallback;
extern DCM_sendMessageBroadcastCallback* g_SendMessageBroadcastCallback;

/* -- Defines --------------------------------------------------------------- */

#define DCM_DRAWING_INSTRUCTION_LIST_LENGTH 128
#define DCM_DRAWING_INSTRUCTION_PIN_FLAG_OUTPUT 0x01
#define DCM_DRAWING_INSTRUCTION_PIN_FLAG_CONNECTED 0x04
#define DCM_DRAWING_INSTRUCTION_BLOCK_SIMPLE_ALIGNMENT_LEFT 0x01
#define DCM_DRAWING_INSTRUCTION_BLOCK_SIMPLE_ALIGNMENT_RIGHT 0x02
#define DCM_DRAWING_INSTRUCTION_BLOCK_SIMPLE_ALIGNMENT_CENTER 0x03
#define DCM_MESSAGE_ID_MODEL_HEADER 255


/* -- Typedefs -------------------------------------------------------------- */

/**
 * Message instruction data union
 */
typedef union {
  DCM_MessageDrawingInstructionEmpty empty;
  DCM_MessageDrawingInstructionBlockSimple blockSimple;
  DCM_MessageDrawingInstructionBlockFunctionBlock blockFunction;
  DCM_MessageDrawingInstructionComment comment;
  DCM_MessageDrawingInstructionLine line;
  DCM_MessageDrawingInstructionPin pin;
} DCM_MessageDrawingInstructionData;

/**
 * Drawing instruction
 */
typedef struct {
  uint8_t type;
  DCM_MessageDrawingInstructionData data;
} DCM_MessageDrawingInstruction;

/**
 * Function pointer type for send drawing instruction callback
 */
typedef uint32_t (*DCM_SendDrawingInstructionFptr)(DCM_Connection* aConnection, DCM_Request const* aRequest, DCM_MessageDrawingInstruction* aMessage);

/**
 * Context that contains all necessary informations for calling
 *  send drawing instruction callback.
 */
typedef struct {
  DCM_Connection* connection;
  DCM_Request const* request;
  DCM_SendDrawingInstructionFptr functionPtr;
} DCM_SendDrawingInstructionCtx;

/* -- Prototypes ------------------------------------------------------------ */

uint32_t DCM_implSendMessageState(DCM_Request const* aRequest, SRTS_ContextPtr aSrtsContext);
SL_Rc DCM_implSendMessageStateCallback(SRTS_ContextPtr aSrtsContext);

uint32_t DCM_sendDrawingInstruction(DCM_Connection* aConnection, DCM_Request const* aRequest, DCM_MessageDrawingInstruction* drawingInstruction);

uint32_t DCM_sendCurrentBreakpointBlock(SRTS_ContextPtr aSrtsContext);

/* -- Functions ------------------------------------------------------------- */

/*@}*//* DCM Data Control Messaging */

#endif /* DATA_CONTROL_MESSAGING_IMPL_H */
