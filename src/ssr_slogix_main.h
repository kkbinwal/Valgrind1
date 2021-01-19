#ifndef SSR_SLOGIX_MAIN_H
#define SSR_SLOGIX_MAIN_H

/* Copyright (C) logi.cals GmbH. All rights reserved. */
#include <ssr/ssr_core_types.h>
#include <stdint.h>

SSR_SUP_STATE_ID ssr_agent_slogix_get_state(void);
void ssr_agent_slogix_set_state(SSR_SUP_STATE_ID state);
uint16_t ssr_agent_slogix_get_aid(void);
uint16_t ssr_agent_slogix_get_subsystem_id(void);
uint32_t ssr_agent_slogix_get_bridge_id(void);
uint32_t ssr_agent_slogix_get_bridge_ss(void);
uint32_t ssr_agent_slogix_get_application_nvmem_id(void);
uint32_t ssr_agent_slogix_get_meta_data_nvmem_id(void);
#endif /* SSR_SLOGIX_MAIN_H */
