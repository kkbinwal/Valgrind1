/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef IMPL_MAIN_SSR_STM32_COMMON_SRTS_SAFETY_LAYER_SRTS_SAFETY_LAYER_H_
#define IMPL_MAIN_SSR_STM32_COMMON_SRTS_SAFETY_LAYER_SRTS_SAFETY_LAYER_H_

/* -- Include files --------------------------------------------------------- */
#include <stdint.h>
#include <common_types.h>
#include <common_statemachine.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */
#define SRTSSL_STATE__S0_NOT_INITED             0u
#define SRTSSL_STATE__S1_INITIALIZED            1u
#define SRTSSL_STATE__S2_WAITING_FOR_CHECKSUM   2u
#define SRTSSL_STATE__S3_WAITING_FOR_VERIF_REQ  3u
#define SRTSSL_STATE__S4_COMP_CHECKSUM          4u
#define SRTSSL_STATE__S5_VERIFIED               5u
#define SRTSSL_STATE__S6_VERIF_ERROR            6u

#define SRTSSL_EOK                              0u        //OK
#define SRTSSL_ENULL                            1u        //NULL
#define SRTSSL_ENOTINITED                       2u        //Safety layer is not initialized
#define SRTSSL_EINVALMSG                        3u        //Invalid message
#define SRTSSL_EMSGTYPENOTSUPPORTED             4u        //The given message type is not supported
#define SRTSSL_ESENDCHECKSUM                    5u        //Communication error: compare checksum message can not be sent to the other subsystem
#define SRTSSL_ECHECKSUMCALC                    6u        //Checksum calculation error
#define SRTSSL_ETIMEOUT                         7u        //Timeout
#define SRTSSL_EDIFFERENTCHECKSUMS              8u        //Checksums are different
#define SRTSSL_ETIMESTAMPREAD                   9u        //Reading of the current timestamp value using SSR API failed
#define SRTSSL_ECMNSM                           10u       //Common state machine error

#define SRTSSL_TRANS__ADDITIONAL_VERIF_CYCLE    1u
#define SRTSSL_TRANS__MAIN_CYCLE                2u
#define SRTSSL_TRANS__RECEIVE_CHECKSUM          3u
#define SRTSSL_TRANS__RESET                     4u

#define SRTSSL_MSG__REMOTE_CHECKSUM             0xFFFEu   //Remote checksum message ID

/* -- Typedefs -------------------------------------------------------------- */
typedef uint8_t SRTSSL_Rc;

typedef struct
{
  SRTS_ContextPtr             srtsCtxPtr;
  uint32_t                    localChecksum;
  uint32_t                    remoteChecksum;
  uint16_t                    dstAgentId;
  uint16_t                    dstSubsystemId;
  uint32_t                    stateTransitionTS;
  SRTSSL_Rc                   errorCode;
  CMNSM_StateMachineInstance  smInstance;
} SRTSSL_Context;

/* -- Prototypes ------------------------------------------------------------ */
SRTSSL_Rc SRTSSL_init(SRTS_ContextPtr srtsCtxPtr, uint16_t dstSubsystemId, uint16_t dstAgentId);

SRTSSL_Rc SRTSSL_additionalVerifCycle(void);

SRTSSL_Rc SRTSSL_mainCycle(void);

SL_AdditionalVerificationState SRTSSL_getAdditionalVerificationState(void);

SRTSSL_Rc SRTSSL_isMessageSupportedBySafetyLayer(uint8_t *data, uint32_t length, CMN_Bool *result);

SRTSSL_Rc SRTSSL_onReceiveMessage(uint8_t *data, uint32_t length);

SRTSSL_Rc SRTSSL_reset(void);

#endif /* IMPL_MAIN_SSR_STM32_COMMON_SRTS_SAFETY_LAYER_SRTS_SAFETY_LAYER_H_ */
