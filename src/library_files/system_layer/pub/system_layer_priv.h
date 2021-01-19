#ifndef SYSTEM_LAYER_PRIV_H_
#define SYSTEM_LAYER_PRIV_H_

/* Copyright (C) logi.cals GmbH. All rights reserved. */
#include <system_layer_types.h>
#include <common_types.h>

SL_Rc SL_resetSystemConfiguration(SRTS_ContextPtr aCtx);

void SL_resetIoDescriptors(SRTS_ContextPtr aCtx);


#endif /* SYSTEM_LAYER_PRIV_H_ */
