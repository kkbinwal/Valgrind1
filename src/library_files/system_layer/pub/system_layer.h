/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef SYSTEM_LAYER_H
#define SYSTEM_LAYER_H

/* -- Include files --------------------------------------------------------- */
#include <system_layer_types.h>
#include <system_layer_tracing.h>
#include <io_provider.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/** @defgroup SL System Layer Interface
 *
 *  In order to integrate the Safe RTS to a specific platform, this
 *  interfaces have to be implemented by the platform vendor.
 *
 *@{*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

SL_Rc SL_initContext(SRTS_ContextPtr aContext);
SL_Rc SL_destroyContext(SRTS_ContextPtr aContext);

/** @name Timer Interface
 * The functions of this interface return the current time required by the timer modules in the safety library
  */
/*@{*/

/**
 * provides the current time in system timer ticks.
 *
 * The time returned by this function is passed to the entry point data structure,
 * which is passed to the run functions of each function block.
 *
 * If the duration of a system timer tick is not equal to the duration of
 * a "libary timer tick" then the timer tick value must be rescaled.
 *
 * The time represents the number of system timer ticks elapsed since last
 * reboot. (or last tick wrap-around. In the worst case of a system timer tick
 * duration of 1ns the wrap-around happens only every 585 years)
 *
 * @param[in] aCtx
 * @param[out] aCurrentTimerTicks current time in system timer ticks.
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #SL_EINVALSYSCFG
 * @retval #CMN_ENULLPTR
 * @retval #SL_ETIMER
 */
SL_Rc SL_getCurrentTime(SRTS_ContextPtr aCtx, SL_SystemTimerTicks* aCurrentTimerTicks);

/**
 * retrieves the time/tick conversion factor.
 *
 * @param[in] aCtx
 * @param[out] aConversionFactor conversion factor [ticks/s]
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #SL_EINVALSYSCFG
 * @retval #CMN_ENULLPTR
 * @retval #SL_ETIMER
 */
SL_Rc SL_getFrequency(SRTS_ContextPtr aCtx, SL_TicksPerSec* aConversionFactor);

/*@}*/


/** @name Set/Get System Configuration
 *
 * A system configuration part is a binary configuration, which is validated by the
 * system layer.
 *
 * A configuration part validation error may occur, if the configuration
 * is not supported by the actual target hardware etc.
 */
/*@{*/

/**
 * Retrieves the additional verification state.
 *
 * For dual-channel architecture, this method can be used to return the
 * state of application cross-comparison.
 *
 * @param[in] aCtx context
 * @param[out] aAdditionalVerificationState the additional verification state
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getAdditionalVerificationState(SRTS_ContextPtr aCtx, SL_AdditionalVerificationState* aAdditionalVerificationState);

/**
 * Starts the additional verification process.
 *
 * Called, when the additional verification (e.g. in case of dual-channel architecture) has
 *  to be started.
 *
 * @param[in] aCtx context
 * @return error code
 * @retval #SL_OK
 * @retval #SL_EADDVERIF
 * @retval #CMN_EINVALCTX
 */
SL_Rc SL_startAdditionalVerification(SRTS_ContextPtr aCtx);

/*@}*/

/** @name Application Instance Data
 */
/*@{*/
/**
 * Retrieves the instance data memory block. ("transient" memory)
 *
 * This memory is used for transient data, i.e. the interpreter context,
 * and function block instance data.
 *
 * The base software retrieves the base address and size of the application
 * model memory from its internal srts context data structure.
 *
 * @param[in] aCtx context
 * @param[out] aInstanceDataBasePtr instance data memory block base address
 * @param[out] aSize memory block size
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getInstanceData(SRTS_ContextPtr aCtx, SL_MemoryBlockBasePtr* aInstanceDataBasePtr, SL_MemoryBlockSize* aSize);
/*@}*/


/** @name Application Model
 */
/*@{*/

/**
 * Retrieves the application model from RAM. ("persistent" memory)
 *
 * This memory is used for persistent data, i.e. the persistent contexts
 * of modules (application model context,..) and the application model data.
 *
 * The base software retrieves the base address and size of the application
 * model memory from its internal srts context data structure.
 *
 * @param[in] aCtx context
 * @param[out] aApplicationModelBasePtr application model memory block base address
 * @param[out] aSize memory block size
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getApplicationModel(SRTS_ContextPtr aCtx, SL_MemoryBlockBasePtr* aApplicationModelBasePtr, SL_MemoryBlockSize* aSize);

/**
 * Save application model to a "persistent" slot.
 *
 * There are two slots:
 * slotIdx=0...default slot (#SL_PERSISTENCE_DEFAULT_SLOT)
 * slotIdx=1...backup slot (#SL_PERSISTENCE_BACKUP_SLOT)
 *
 * @param[in] aCtx context
 * @param[in] aSlotIdx zero based slot index
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_EIDXBOUNDS
 * @retval #SL_EPERSISTWRITE
 */
SL_Rc SL_saveApplicationModel(SRTS_ContextPtr aCtx, SL_PersistentSlotIdx aSlotIdx);

/**
 * Loads the application model from the "persistent" slot onto RAM.
 *
 * There are two slots:
 * slotIdx=0...default slot (#SL_PERSISTENCE_DEFAULT_SLOT)
 * slotIdx=1...backup slot (#SL_PERSISTENCE_BACKUP_SLOT)
 *
 * @param[in] aCtx context
 * @param[in] aSlotIdx zero bazed slot index
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_EIDXBOUNDS
 * @retval #SL_EPERSISTREAD
 * @retval #SL_EINVALAPM
 * @retval #SL_ESLOTEMPTY
 */
SL_Rc SL_loadApplicationModel(SRTS_ContextPtr aCtx, SL_PersistentSlotIdx aSlotIdx);
/*@}*/


/** @name Application Processing States
 */
/*@{*/

/**
 * Sets the execution state of the interpreter.
 *
 * The base software decides, if this execution state is accepted and returned
 * in further calls of #SL_getExecutionState.
 *
 * @param[in] aCtx context
 * @param[in] aState execution state
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #SL_ESETTNOTACC
 */
SL_Rc SL_setExecutionState(SRTS_ContextPtr aCtx, CMN_ExecutionState aState);

/**
 * Retrieves the execution state of the interpreter.
 *
 * @param[in] aCtx context
 * @param[out] aState execution state
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getExecutionState(SRTS_ContextPtr aCtx, CMN_ExecutionState* aState);

/**
 * Registers a state change callback function.
 *
 * The callback function is called, if IO connection state or execution
 * state changes.
 *
 * @param[in] aCtx context
 * @param[in] aStateChangeCallback callback function, NULL is disabled
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_registerStateChangeCallback(SRTS_ContextPtr aCtx, SL_stateChangeCallback* aStateChangeCallback);

/**
 * Set the physical IO connection state.
 *
 * @param[in] aCtx context
 * @param[in] aState true == IOs connected, false == IOs disconnected
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 */
SL_Rc SL_setIoConnectionState(SRTS_ContextPtr aCtx, SL_IoConnectionState aState);

/**
 * Retrieve the physical IO connection state.
 *
 * @param[in] aCtx context
 * @param[out] aState true == IOs connected, false == IOs disconnected
 * @return error code
 * @retval #SL_OK
 * @retval #CMN_EINVALCTX
 * @retval #CMN_ENULLPTR
 */
SL_Rc SL_getIoConnectionState(SRTS_ContextPtr aCtx, SL_IoConnectionState* aState);

/*@}*/


/*@}*/

#endif /* SYSTEM_LAYER_H */
