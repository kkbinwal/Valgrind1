/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef COMMON_RC_H_
#define COMMON_RC_H_

/* -- Include files --------------------------------------------------------- */
#include <common_types.h>
#include <stdint.h>

/** @defgroup CMN_RC_BASE Common base return codes
 *
 *  Base values for the return/error codes of all modules/groups.
 *
 *@{*/

/* -- Defines --------------------------------------------------------------- */
#define CMN_APM_RC_BASE     0x10000u    /**< base return code of APM   module, lower 12 bits contain error code */
#define CMN_CMN_RC_BASE     0x11000u    /**< base return code of CMN   module, lower 12 bits contain error code */
#define CMN_DPM_RC_BASE     0x13000u    /**< base return code of DPM   module, lower 12 bits contain error code */
#define CMN_INP_RC_BASE     0x14000u    /**< base return code of INP   module, lower 12 bits contain error code */
#define CMN_IO_RC_BASE      0x15000u    /**< base return code of IO    module, lower 12 bits contain error code */
#define CMN_LP_RC_BASE      0x16000u    /**< base return code of LP    module, lower 12 bits contain error code */
#define CMN_MM_RC_BASE      0x17000u    /**< base return code of MM    module, lower 12 bits contain error code */
#define CMN_SL_RC_BASE      0x18000u    /**< base return code of SL    module, lower 12 bits contain error code */
#define CMN_SSH_RC_BASE     0x19000u    /**< base return code of SSH   module, lower 12 bits contain error code */
#define CMN_ENTRY_RC_BASE   0x1a000u    /**< base return code of ENTRY module, lower 12 bits contain error code */
#define CMN_PIL_RC_BASE     0x1b000u    /**< base return code of PIL   module, lower 12 bits contain error code */

/*@}*//* CMN_RC_BASE */

/** @defgroup CMN_RC Common error codes
 *
 *  Common error codes which are the same in all modules/groups.
 *
 *@{*/

/* -- Defines --------------------------------------------------------------- */
#define CMN_OK              CMN_CMN_RC_BASE             /**< No error occurred. */
#define CMN_EPERM           (CMN_CMN_RC_BASE +   0x1u)  /**< The Operation is not permitted. */
#define CMN_ENOTIMPL        (CMN_CMN_RC_BASE +  0x21u)  /**< Not implemented. */
#define CMN_EINVAL          (CMN_CMN_RC_BASE +  0x22u)  /**< An argument is invalid. */
#define CMN_ERANGE          (CMN_CMN_RC_BASE +  0x34u)  /**< The result is too large. */
#define CMN_EFOO            (CMN_CMN_RC_BASE +  0x42u)  /**< To be defined error */
#define CMN_ENOBUFS         (CMN_CMN_RC_BASE + 0x105u)  /**< No buffer space is available. */
#define CMN_ECLASS          (CMN_CMN_RC_BASE + 0x106u)  /**< the class is unknown. */
#define CMN_EBADHNDL        (CMN_CMN_RC_BASE + 0x200u)  /**< The handle is invalid. */
#define CMN_ENOIOIDX        (CMN_CMN_RC_BASE + 0x201u)  /**< No index for the IO could be found. */
#define CMN_ENOVARIDX       (CMN_CMN_RC_BASE + 0x202u)  /**< No index for the variable could be found. */
#define CMN_ENOBLOCKIDX     (CMN_CMN_RC_BASE + 0x203u)  /**< No index for the block could be found. */
#define CMN_ENOCONIDX       (CMN_CMN_RC_BASE + 0x204u)  /**< No index for the connection could be found. */
#define CMN_EOUTPNOIN       (CMN_CMN_RC_BASE + 0x205u)  /**< An output may not be used as an input. */
#define CMN_ESEQ            (CMN_CMN_RC_BASE + 0x206u)  /**< There is a problem with the sequence numbers */
#define CMN_EBLOCKTYPE      (CMN_CMN_RC_BASE + 0x207u)  /**< The block type is not handled */
#define CMN_ENOFBIDX        (CMN_CMN_RC_BASE + 0x208u)  /**< No index for the FB could be found. */
#define CMN_EUNKNOWN        (CMN_CMN_RC_BASE + 0x209u)  /**< An Unknown error code was returned. */
#define CMN_EIDXBOUNDS      (CMN_CMN_RC_BASE + 0x20au)  /**< The list index is out of bounds. */
#define CMN_ENULLPTR        (CMN_CMN_RC_BASE + 0x20bu)  /**< A pointer should be non-NULL, but is NULL. */
#define CMN_EINVALCTX       (CMN_CMN_RC_BASE + 0x20cu)  /**< Invalid context handle. */
#define CMN_ENOTAVAIL       (CMN_CMN_RC_BASE + 0x20du)  /**< Not available. */
#define CMN_ESYSTEM         (CMN_CMN_RC_BASE + 0x20eu)  /**< System error. */
#define CMN_EALIGNMENT      (CMN_CMN_RC_BASE + 0x20fu)  /**< Alignment computation error. */
#define CMN_ESTRCPY         (CMN_CMN_RC_BASE + 0x301u)  /**< An error occurred during strcpy operation */
#define CMN_ESTRCAT         (CMN_CMN_RC_BASE + 0x302u)  /**< An error occurred during strcat operation */
#define CMN_ESPRINTF        (CMN_CMN_RC_BASE + 0x303u)  /**< An error occurred during sprintf operation */
#define CMN_ESTRTOK         (CMN_CMN_RC_BASE + 0x304u)  /**< An error occurred during strtok operation */
#define CMN_ESTRLEN         (CMN_CMN_RC_BASE + 0x305u)  /**< An error occurred during strlen operation */
#define CMN_ESL             (CMN_CMN_RC_BASE + 0x306u)  /**< A system layer error occurred */
#define CMN_EMEMCPY         (CMN_CMN_RC_BASE + 0x307u)  /**< An error occurred during memcpy operation */
#define CMN_EENO            (CMN_CMN_RC_BASE + 0x308u)  /**< ENO of any function block is set to false. */
#define CMNSM_ETRAN         (CMN_CMN_RC_BASE + 0x401u)  /**< Transition is in progress. */
#define CMNSM_ENOTRAN       (CMN_CMN_RC_BASE + 0x402u)  /**< Transition not in progress */
#define CMNSM_ESTAT         (CMN_CMN_RC_BASE + 0x403u)  /**< Transition is not allowed in this state (or guard function failed) */
#define CMN_ESTRRCHR        (CMN_CMN_RC_BASE + 0x404u)  /**< An error occured during strrchar operation */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/**
 * Check if return code is an error.
 *
 * @param[in] rc The return code to check.
 * @return 0..rc is ok, !=0..rc is an error
 */
CMN_Bool isRcError(CMN_Rc rc);

/**
 * Check if return code is ok / no error.
 *
 * @param[in] rc The return code to check.
 * @return 0..rc is an error, !=0..rc is ok
 */
CMN_Bool isRcOk(CMN_Rc rc);

#ifdef __cplusplus
}
#endif /* __cplusplus */

/*@}*//* CMN_RC */

#endif /* COMMON_RC_H_ */
