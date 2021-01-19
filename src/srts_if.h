#ifndef SRTS_IF_H_
#define SRTS_IF_H_

#include "ssr/msg/access/ssr_msg_access.h"
#include "ssr/lib/time/ssr_lib_time.h" /* TODO: maybe not needed */
#include "ssr/ssr_core_defines_common.h" /* TODO: maybe not needed */

#define SSR_SLOGIX_PAL_MAX_MSG_SIZE       576           /* Divisible by 4 please */

#include <stdint.h>

void ssr_slogix_main_parse_msg(void);
int32_t ssr_slogix_main_init_srts(void);
void ssr_slogix_main_schedule_srts_cycle(void);
uint16_t ssr_slogix_main_get_agent_id(void);
uint16_t ssr_slogix_main_get_subsystem_id(void);

#endif /* SRTS_IF_H_ */
