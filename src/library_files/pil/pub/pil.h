/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef PIL_H_
#define PIL_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>
#include <common_rc.h>
#include <library_provider_types.h>
#include <system_layer_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define PIL_OK            CMN_PIL_RC_BASE            /**< No Error */
#define PIL_ENOPIL        (CMN_PIL_RC_BASE + 0x01u)  /**< PIL module is not available in the current build */
#define PIL_ESL           (CMN_PIL_RC_BASE + 0x02u)  /**< System layer reported an error */
#define PIL_EBLKNFND      (CMN_PIL_RC_BASE + 0x03u)  /**< Block cannot be found in library */
#define PIL_ELP           (CMN_PIL_RC_BASE + 0x04u)  /**< Error reported by library provider */
#define PIL_EAPM          (CMN_PIL_RC_BASE + 0x05u)  /**< Error reported by application model */
#define PIL_ESSH          (CMN_PIL_RC_BASE + 0x06u)  /**< Error reported by safety shell */
#define PIL_EDPM          (CMN_PIL_RC_BASE + 0x07u)  /**< Error reported by the data pool manager */
#define PIL_ENULL         (CMN_PIL_RC_BASE + 0x08u)  /**< NULL pointer is not allowed*/
#define PIL_EVARNFND      (CMN_PIL_RC_BASE + 0x09u)  /**< Variable cannot be found in application model */
#define PIL_EINP          (CMN_PIL_RC_BASE + 0x0Au)  /**< Error reported by interpreter */
#define PIL_EINVALLIT     (CMN_PIL_RC_BASE + 0x0Bu)  /**< Invalid literal format */
#define PIL_ESAFE         (CMN_PIL_RC_BASE + 0x0Cu)  /**< Operation cannot be executed in safe state */
#define PIL_ENOTRUNNING   (CMN_PIL_RC_BASE + 0x0Du)  /**< Application is not in running state */
#define PIL_EVARNAME      (CMN_PIL_RC_BASE + 0x0Eu)  /**< Variable name is too long or had encoding problem */

/* -- Typedefs -------------------------------------------------------------- */

typedef CMN_Rc PIL_Rc;

/* -- Prototypes ------------------------------------------------------------ */

/**
 * Switch the system into PIL Test mode.
 *
 * @param aContext pointer the SRTS context instance
 * @return #PIL_Rc
 * @retval #PIL_OK
 * @retval #PIL_ENOPIL
 */
PIL_Rc PIL_setPILTest(SRTS_ContextPtr aContext);

/**
 * Switch back from PIL Test mode.
 *
 * @param aContext pointer the SRTS context instance
 * @return #PIL_Rc
 * @retval #PIL_OK
 * @retval #PIL_ENOPIL
 */
PIL_Rc PIL_resetPILTest(SRTS_ContextPtr aContext);

/**
 * Prepare PIL application to test the given block
 *
 * @param aContext pointer the SRTS context instance
 * @param[in] aBlockName the block under test
 * @paran[out] aNumTestSteps the number of test steps the generated application can handle in one run
 * @return #PIL_Rc
 * @retval #PIL_OK
 * @retval #CMN_ENULLPTR
 * @retval #PIL_ELP
 * @retval #PIL_ENOPIL
 */
PIL_Rc PIL_prepareTest(SRTS_ContextPtr aContext, char const* aBlockName, CMN_Count *aNumTestSteps);

/**
 * Activate test execution
 *
 * @param aContext pointer the SRTS context instance
 * @param aNumTestSteps the number of test steps to execute
 *
 * @return #PIL_Rc
 * @retval #PIL_OK
 * @retval #CMN_ENULLPTR
 * @retval #PIL_ELP
 * @retval #PIL_ENOPIL
 */
PIL_Rc PIL_activateTest(SRTS_ContextPtr aContext, CMN_Count aNumTestSteps);

PIL_Rc PIL_setCycleTime(SRTS_ContextPtr aContext, SL_SystemTimerTicks aCycleTime);

/**
 * This function is called before each cycle execution allowing the PIL
 * module to execute additional configuration (e.g. setting virtual time)
 */
PIL_Rc PIL_preCycle(SRTS_ContextPtr aContext);

/**
 * This function is called after each cycle execution allowing the PIL
 * module to execute additional configuration (e.g. stopping after last cycle)
 */
PIL_Rc PIL_postCycle(SRTS_ContextPtr aContext);

/**
 * Force byte array of values to the specified array variable from the specified array element index.
 *
 * @param aContext the SRTS context
 * @param aHandle handle of the array variable
 * @param aStartIdx first index of the inserted array element
 * @param aLength the length of the byte array
 * @param aValues byte array representing the value to be forced
 * @return error code
 */
PIL_Rc PIL_forceArrayValues(
    SRTS_ContextPtr aContext,
    CMN_VariableHandle aHandle,
    CMN_Count aStartIdx,
    CMN_Count aLength,
    CMN_Byte const* aValues);

/**
 * Returns with the values of an array variable from the given index in
 *  the given length.
 *
 * @param aContext the SRTS context
 * @param aHandle handle of the array variable
 * @param aStartIdx first index of the watched array elements
 * @param aLength the length of the byte array
 * @param aValues byte array that stores the watched elements
 * @return error code
 */
PIL_Rc PIL_watchArrayValues(SRTS_ContextPtr aContext, CMN_VariableHandle aHandle, CMN_Count aStartIdx, CMN_Count aLength, CMN_BytePtr aValues);

/**
 * Initialises the execution state for PIL testing.
 * After the execution of this function the execution state will be in Paused state.
 *
 * @param aContext the SRTS context
 * @return Error code
 * @retval #PIL_ENULL
 * @retval #PIL_ESSH
 * @retval #PIL_OK
 */
PIL_Rc PIL_initPILTest(SRTS_ContextPtr aContext);

/**
 * Searches a variable by it's name and returns with it's information (data type, handle and size).
 *
 * @param aContext
 * @oaram[in] aVarName
 * @param[out] aDataType
 * @param[out] aHandle
 * @param[out] aSize
 * @return Error code
 * @retval #PIL_ENULL
 * @retval #PIL_ESSH
 * @retval #PIL_EAPM
 * @retval #PIL_EVARNFND
 * @retval #PIL_OK
 */
PIL_Rc PIL_getPilTestVarDescriptor(
    SRTS_ContextPtr aContext,
    char const* aVarName,
    CMN_DataType *aDataType,
    int16_t* aHandle,
    CMN_Size *aSize);

#endif /* PIL_H_ */
