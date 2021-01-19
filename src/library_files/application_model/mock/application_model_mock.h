/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_MOCK_H_
#define APPLICATION_MODEL_MOCK_H_

/* -- Include files --------------------------------------------------------- */
#include <application_model.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */
#define APM_GETVARIABLECODEINFOS_MOCK(aContext, index, aVariable)
#define APM_GETBLOCKCODEINFOS_MOCK(aContext, index, aBlock)
#define APM_GETLITERALCODEINFOS_MOCK(aContext, index, aLiteral, aIsEnabled)
#define APM_GETCONNECTIONCODEINFOS_MOCK(aContext, index, aConnection)
#define APM_ITERATECOMMANDSEQ_MOCK(aContext, aIterator, aCurCommand, aNextIterator)
#define APM_COMPUTEEXECUTIONORDER_MOCK(aContext)
#define APM_INTERNALGETLIBRARYIDXBYCLASSID_MOCK(aClassId, aIdx)
#define APM_INTERNALSENDBLOCKDRAWINGINSTRUCTIONS_MOCK(aContext, aBlock, aSendDICtx, aDeleteBlock)
#define APM_INTERNALSENDCONNECTIONRELATEDDRAWINGINSTRUCTIONS_MOCK(aContext, aConnection, aDataType, \
  aSendDICtx, aConnectionsChanged, aDeleteConnection)
#define APM_INTERNALSENDCOMMENTDRAWINGINSTRUCTIONS_MOCK(aContext, aComment, aSendDICtx, aDeleteComment)
#define APM_DELETEBLOCK_MOCK(aContext, aHandle, aSendDICtx)
#define APM_DELETECONNECTION_MOCK(aContext, aHandle, aSendDICtx)
#define APM_UPDATEANDVERIFYIOBLOCKS_MOCK(aContext)
#define APM_GETVARIABLESIZE_MOCK(aContext, varIdx, aSize)
#define APM_INTERNALCLEARSEQUENCENUMBERS_MOCK(aInstance)
#define APM_INTERNALGETPINNAME_MOCK(aBlock, aPin, aLibraryPinName, aPinDirection)
#define APM_INTERNALGETENDPOINTDATATYPE_MOCK(aInstance, aBlock, aPin, aPinDirection, aDataType)

/* -- Prototypes ------------------------------------------------------------ */

#endif /* APPLICATION_MODEL_MOCK_H_ */


