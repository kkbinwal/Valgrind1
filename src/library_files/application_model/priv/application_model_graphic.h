/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_GRAPHIC_H_
#define APPLICATION_MODEL_GRAPHIC_H_

/* -- Include files --------------------------------------------------------- */
#include <data_control_messaging_impl.h>
#include <application_model_priv.h>
#include <application_model_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

APM_Rc APM_internalSendBlockDrawingInstructions(
    SRTS_ContextPtr aContext,
    APM_BlockData* aBlock,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_Bool aDeleteBlock);

APM_Rc APM_internalSendConnectionRelatedDrawingInstructions(
    SRTS_ContextPtr aContext,
    APM_ConnectionData* aConnection,
    CMN_DataType aDataType,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_Bool aConnectionsChanged,
    CMN_Bool aDeleteConnection);

APM_Rc APM_internalSendCommentDrawingInstructions(
    SRTS_ContextPtr aContext,
    APM_CommentData const* aComment,
    DCM_SendDrawingInstructionCtx const* aSendDICtx,
    CMN_Bool aDeleteComment);

CMN_Bool APM_geometryIsOutOfBounds(CMN_Rectangle const* geometry);

#endif /* APPLICATION_MODEL_GRAPHIC_H_ */
