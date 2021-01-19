#ifndef SSR_SLOGIX_IO_H
#define SSR_SLOGIX_IO_H

/* Copyright (C) logi.cals GmbH. All rights reserved. */
#include <ssr_slgx_platform_data.h>
#include <stdint.h>
#include <stdbool.h>

//#define CONFIGURATION_SIMULATION
#undef CONFIGURATION_SIMULATION
#define NETWORK_CONFIG

//BACR Configuration values defined as per Osprey configuration file definitions
#define MAX_IO_ITEM_LEN 8

#define SSR_COPY_TYPE_INPUT_BIT       0
#define SSR_COPY_TYPE_INPUT_NORMAL    1
#define SSR_COPY_TYPE_OUTPUT_NORMAL   2
#define SSR_COPY_TYPE_OUTPUT_BIT      3

#define DRIVEN_BY_NETWORK 0
#define DRIVEN_BY_LOGIC 1

//BACR name changes for consistency. New Config values added
#define SLGX_DIRECTION_INPUT 0x00
#define SLGX_DIRECTION_OUTPUT 0x01
#define SLGX_DIRECTION_DIABLED 0xFF

#define SLGX_TYPE_BOOL 1
#define SLGX_TYPE_BYTE 2
#define SLGX_TYPE_INT 3
#define SLGX_TYPE_SAFE_BOOL 4
#define SLGX_TYPE_SAFE_INT 5


#define SSR_CFG_HEADER_START         0
#define SSR_CFG_FILE_HEAD_UAID               0
#define SSR_CFG_FILE_HEAD_VER                4
#define SSR_CFG_FILE_HEAD_AID                8
#define SSR_CFG_FILE_HEAD_SSID              10
#define SSR_CFG_FILE_HEAD_CRC               12
#define SSR_CFG_FILE_HEAD_SIZE              16

#define SSR_CFG_MAPPING_START       (SSR_CFG_HEADER_START + 20)//(SSR_CFG_HEADER_START + sizeof(SSR_BETA_ST_HEADER))
#define SSR_CFG_FILE_IO_ITEM                0
#define SSR_CFG_FILE_IO_COPY_ITEM           4
#define SSR_CFG_FILE_IO_OFFSET              8
#define SSR_CFG_FILE_IO_COPY_OFFSET         12

#define SSR_CFG_IO_ITEM_START        (SSR_CFG_MAPPING_START + sizeof(SSR_BETA_IO_MAPPING))
#define SSR_IO_ITEM_OFFSET                 0
#define SSR_IO_ITEM_DIR_APPLY              4
#define SSR_IO_ITEM_DIR_DEFAULT            6
#define SSR_IO_ITEM_TYPE                   8
#define SSR_IO_ITEM_RESERVED               12
#define SSR_IO_ITEM_NAME_SIZE              16
#define SSR_IO_ITEM_DRIVEN_BY              20
#define SSR_IO_ITEM_NAME                   24

#define SSR_CFG_COPY_ITEM_START         (SSR_CFG_IO_ITEM_START + (MAX_IO_ITEMS * sizeof(SSR_BETA_IO_ELEMENT_STRUCT)))
#define SSR_COPY_SSR_ID                     0
#define SSR_COPY_SSR_OFFSET                 4
#define SSR_COPY_SSR_SIZE                   8
#define SSR_COPY_TYPE                       12
#define SSR_COPY_OFFSET                     16
#define SSR_COPY_NETWORK_ID                 20
#define SSR_COPY_NETWORK_OFFSET             24

#define CONFIGURATION_SIMULATION_MEM_ID SSR_MEM_ID_CONFIG_TEMP_1
/* Agent developers are allowed to create their own message types to faciliate agent communication
 As long as it does not interfere with the message types of the core agents*/
#define SSR_MSG_DEMO_PAYLOAD (0x00000500u)

#define IS_NETWORK_DRIVEN(x) (x>0)

// Configuration Structures
typedef struct
{
  uint32_t u32_universal_agent_id; // UAID
  uint32_t u32_config_ver; //0x00000001: Version 1 of Logic Agent
  uint16_t u16_agent_id; //Agent ID (AID).
  uint16_t u16_subsystem_id; //Sub-system ID (SSID).
  uint32_t u32_config_crc; //CRC of this entire section
  uint32_t u32_config_size; //Size in bytes in this entire section
} SSR_SLGX_ST_HEADER;

typedef struct
{
  uint32_t u32_slgx_io_item_number; /*number of ST_LOGIC_AGENT_IO_ITEM*/
  uint32_t u32_slgx_copy_item_number;/*number of ST_LOGIC_AGENT_COPY_ITEM*/
  uint32_t u32_slgx_io_item_offset; /*offset in the Agent config data of first ST_LOGIC_AGENT_IO_ITEM*/
  uint32_t u32_slgx_copy_item_offset;/*offset in the Agent config data of first ST_LOGIC_AGENT_COPY_ITEM*/
} SSR_SLGX_IO_MAPPING;

typedef struct
{
	SSR_SLGX_ST_HEADER st_beta_header;
  SSR_SLGX_IO_MAPPING st_beta_io_mapping;
  SSR_SLGX_IO_ELEMENT_STRUCT* st_a_io_element_table; //SSIM CHANGE MAKE THIS A POINTER
  uint32_t u32_io_element_count;
  SSR_SLGX_IO_COPY_STRUCT* st_a_copy_element_table; //SSIM CHANGE MAKE THIS A POINTER
  uint32_t u32_copy_element_count;
} SSR_SLGX_CONFIGURATION_DATA;



int32_t ssr_slogix_io_main_cycle(void);

int32_t ssr_slogix_io_writeSimultedConfig(void);
int32_t ssr_slogix_io_simulateConfigReqMsg(void);
int32_t ssr_slogix_io_waitForCfgMessage(void);
int32_t ssr_slogix_io_sendValidationMessage(void);
int32_t ssr_slogix_io_waitForStartMessage(void);
int32_t ssr_slogix_io_cfgAddIoItems(void);

bool ssr_slogix_io_isCfgReady(void);
SSR_SLGX_CONFIGURATION_DATA* ssr_slogix_io_getCfg(void);

void ssr_slogix_stop_set_config_stop(uint16_t u16_message_id);
void ssr_slogix_io_setCfgReady(bool state);

int32_t ssr_slogix_io_read(void);
int32_t ssr_slogix_io_write(void);

void ssr_set_slgx_config_buffers(uint8_t* p_u8_io_items_buffer, uint32_t u32_io_items_buffer_size,
		uint8_t* p_u8_copy_items_buffer,uint32_t u32_copy_items_buffer_size);

void ssr_slgx_set_image_buffers(uint8_t* p_u8_input_image_buffer, uint16_t u16_input_image_buffer_size,
		uint8_t* p_u8_output_image_buffer,uint16_t u16_output_image_buffer_size);

void ssr_set_slgx_descriptor_buffers(uint8_t* p_u8_io_descriptor_buffer, uint16_t u32_io_descriptor_buffer_size,
		void** p_u8_io_image_address_buffer, uint16_t u32_io_image_address_buffer_size);

extern uint8_t* u8_a_io_input_item_data;
extern uint8_t* u8_a_io_output_item_data;


#endif /* SSR_SLOGIX_IO_H */
