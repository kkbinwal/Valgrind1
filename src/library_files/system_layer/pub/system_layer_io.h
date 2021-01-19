#ifndef SYSTEM_LAYER_IO_H_
#define SYSTEM_LAYER_IO_H_

/* Copyright (C) logi.cals GmbH. All rights reserved. */
#include <system_layer_types.h>
#include <common_types.h>

IO_Rc IO_getIoStates(SRTS_ContextPtr aCtx);
IO_Rc IO_setIoStates(SRTS_ContextPtr aCtx);

#endif /* SYSTEM_LAYER_IO_H_ */
