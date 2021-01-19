/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef DC_RC_H_
#define DC_RC_H_

/* -- Include files --------------------------------------------------------- */
#include <common_rc.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define SSH_OK              CMN_SSH_RC_BASE            /**< No Error*/
#define SSH_ENOELMNT        (CMN_SSH_RC_BASE + 0x01u)  /**< Referenced element does not exist*/
#define SSH_ELITFORM        (CMN_SSH_RC_BASE + 0x02u)  /**< Malformed literal*/
#define SSH_ELITRANGE       (CMN_SSH_RC_BASE + 0x03u)  /**< Literal is out of range*/
#define SSH_EINVALDT        (CMN_SSH_RC_BASE + 0x04u)  /**< Invalid datatype*/
#define SSH_EINVALFB        (CMN_SSH_RC_BASE + 0x05u)  /**< Invalid functional block name*/
#define SSH_ERUNNING        (CMN_SSH_RC_BASE + 0x06u)  /**< Application is not in stopped state, editing is disabled*/
#define SSH_EINVALBT        (CMN_SSH_RC_BASE + 0x07u)  /**< Invalid block type*/
#define SSH_EINVALITER      (CMN_SSH_RC_BASE + 0x08u)  /**< Invalid iterator*/
#define SSH_EALREADY        (CMN_SSH_RC_BASE + 0x09u)  /**< Requested operation cannot be executed since application is already in the requested state*/
#define SSH_ESAFE           (CMN_SSH_RC_BASE + 0x0Au)  /**< Operation cannot be executed in safe state*/
#define SSH_ESTATE          (CMN_SSH_RC_BASE + 0x0Bu)  /**< Application is in an illegal state*/
#define SSH_ELP             (CMN_SSH_RC_BASE + 0x0Cu)  /**< Library provider reported an error*/
#define SSH_EITEREND        (CMN_SSH_RC_BASE + 0x0Du)  /**< Iterator has ended*/
#define SSH_EBUFINSU        (CMN_SSH_RC_BASE + 0x0Eu)  /**< Insufficient buffer*/
#define SSH_ENULL           (CMN_SSH_RC_BASE + 0x0Fu)  /**< NULL pointer is not allowed*/
#define SSH_EINVALPIN       (CMN_SSH_RC_BASE + 0x10u)  /**< Invalid Pin*/
#define SSH_ENOTRUNNING     (CMN_SSH_RC_BASE + 0x11u)  /**< Application is not in running state*/
#define SSH_EPIL            (CMN_SSH_RC_BASE + 0x12u)  /**< PIL error occurred*/
#define SSH_ENOTEXECUTABLE  (CMN_SSH_RC_BASE + 0x13u)  /**< Application execution order cannot be determined */
#define SSH_ENOT_FOUND      (CMN_SSH_RC_BASE + 0x14u)  /**< No valid result has been found */
#define SSH_ESEND           (CMN_SSH_RC_BASE + 0x15u)  /**< Message sending failed */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

#endif /* DC_RC_H_ */
