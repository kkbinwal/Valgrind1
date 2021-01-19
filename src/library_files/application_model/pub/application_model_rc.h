/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_RC_H_
#define APPLICATION_MODEL_RC_H_

/* -- Include files --------------------------------------------------------- */

#include <common_rc.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

#define APM_OK                    CMN_APM_RC_BASE            /**< No Error*/
#define APM_ENULL                 (CMN_APM_RC_BASE + 0x01u)  /**< NULL pointer is not allowed*/
#define APM_DATA_TYPE_SIZE_ERROR  (CMN_APM_RC_BASE + 0x02u)  /**< The size of the data type in bytes cannot be determined. */
#define APM_ENOTDAG               (CMN_APM_RC_BASE + 0x03u)  /**< Application model contains a directed cycle*/
#define APM_ENOMEM                (CMN_APM_RC_BASE + 0x04u)  /**< Resource problems*/
#define APM_ELP                   (CMN_APM_RC_BASE + 0x05u)  /**< Library provider reported an error*/
#define APM_ENOELMNT              (CMN_APM_RC_BASE + 0x06u)  /**< Referenced element does not exist*/
#define APM_EINVALITER            (CMN_APM_RC_BASE + 0x07u)  /**< Invalid iterator value*/
#define APM_EDTMISMATCH           (CMN_APM_RC_BASE + 0x08u)  /**< Connected datatypes are incompatible*/
#define APM_EALREADY              (CMN_APM_RC_BASE + 0x09u)  /**< Data has already added to the instance*/
#define APM_EINVALIDX             (CMN_APM_RC_BASE + 0x0Au)  /**< The given index is not valid*/
#define APM_EINVALOP              (CMN_APM_RC_BASE + 0x0Bu)  /**< The operand has invalid type*/
#define APM_EEMPTY                (CMN_APM_RC_BASE + 0x0Cu)  /**< List is empty*/
#define APM_EINVALBT              (CMN_APM_RC_BASE + 0x0Du)  /**< Invalid block type*/
#define APM_ECHANGEDBT            (CMN_APM_RC_BASE + 0x0Eu)  /**< The block type has changed*/
#define APM_ECHANGEDFBNAME        (CMN_APM_RC_BASE + 0x0Fu)  /**< The function block name has changed*/
#define APM_EINVAL_IO             (CMN_APM_RC_BASE + 0x10u)  /**< The IO was not found in system layer */
#define APM_EDPM                  (CMN_APM_RC_BASE + 0x11u)  /**< Data Pool Manager reported an error */
#define APM_EINVALARRIDX          (CMN_APM_RC_BASE + 0x12u)  /**< Invalid array index */
#define APM_EDCM                  (CMN_APM_RC_BASE + 0x13u)  /**< Data Control Messaging reported an error */
#define APM_EGEOMETRY_BOUNDS      (CMN_APM_RC_BASE + 0x14u)  /**< Block Geometry is outside the bounds of the coordinate range */
#define APM_EINVALIDPINIDX        (CMN_APM_RC_BASE + 0x15u)  /**< Name of PIN(index) does not match expected name */
#define APM_ELITFORM              (CMN_SSH_RC_BASE + 0x16u)  /**< Malformed literal*/
#define APM_ELITRANGE             (CMN_SSH_RC_BASE + 0x17u)  /**< Literal is out of range*/

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

#endif /* APPLICATION_MODEL_RC_H_ */
