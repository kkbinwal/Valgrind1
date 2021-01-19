/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_LITERALS_H_
#define APPLICATION_MODEL_LITERALS_H_

/* -- Include files --------------------------------------------------------- */

#include <application_model_rc.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/* -- Prototypes ------------------------------------------------------------ */

APM_Rc APM_validateLiteralUint(char const* aLiteral, uintmax_t const aLimit);

APM_Rc APM_validateLiteralInt(char const* aLiteral, intmax_t aLowerLimit, intmax_t aUpperLimit);

APM_Rc APM_parseLiteralUint(char const* aLiteral, uintmax_t const aLimit, uintmax_t* value);

APM_Rc APM_parseLiteralInt(char const* aLiteral, intmax_t aLowerLimit, intmax_t aUpperLimit, intmax_t* value);

#endif
