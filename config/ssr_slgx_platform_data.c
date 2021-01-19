/*
+------------------------------------------------------------------------------+
| Molex
| -----------------------------------------------------------------------------
| Copyright 2019 (c) Molex. All rights reserved.
+------------------------------------------------------------------------------+
 */
 /**
 *  @file    ssr_slgx_platform_data.c
 *  @brief
 *  @author  $Author:  $
 *  @version $Revision:  $
 *  @date    $Date:  $
 *---------------------------------------------------------------------------
 *  @details
 *---------------------------------------------------------------------------
 Version     | Date      | Author        | Comments
 */

#include "ssr_slgx_platform_data.h"
#include "ssr_slogix_io.h"
#include "system_layer_types.h"

/* AGENT MACROS */
#define SLGX_MAX_IO_ITEMS 100
#define SLGX_MAX_COPY_ITEMS 16
/* END AGENT MACROS */

/* AGENT ARRAYS */
SSR_SLGX_IO_ELEMENT_STRUCT st_a_slgx_io_element_buffer[SLGX_MAX_IO_ITEMS];
SSR_SLGX_IO_COPY_STRUCT st_a_slgx_copy_element_buffer[SLGX_MAX_COPY_ITEMS];
uint8_t u8_a_slgx_input_io_image_buffer[SLGX_MAX_IO_ITEMS];
uint8_t u8_a_slgx_output_io_image_buffer[SLGX_MAX_IO_ITEMS];
SL_IoDescription st_a_slgx_io_descriptor_buffer[SLGX_MAX_IO_ITEMS];
void* p_a_slgx_io_image_address_buffer[SLGX_MAX_IO_ITEMS];
/* END AGENT ARRAYS */

/*
--------------------------------------------------------------------------------
ssr_slgx_platform_data_default()
--------------------------------------------------------------------------------
*/
/*
* @brief this routine will initialize the slgx platform data
* @param[in]     SLGX_PLATFORM_DATA <slgx platform data structure>
* @return C_SSR_ERR_NONE if no error.Otherwise error code
*/
void ssr_slgx_platform_data_default(SLGX_PLATFORM_DATA* slgx_data)
{
}

/*
--------------------------------------------------------------------------------
ssr_slgx_initialization_data_default()
--------------------------------------------------------------------------------
*/
/*
* @brief this routine will inititalize the slgx initialization data
* @param[in]     SLGX_PLATFORM_DATA <slgx platform data structure>
* @return C_SSR_ERR_NONE if no error.Otherwise error code
*/
void ssr_slgx_initialization_data_default(SLGX_INITIALIZATION_DATA* slgx_data)
{
	slgx_data->u32_partner_bridge_id = 7;
	slgx_data->u32_partner_bridge_ss = 1;
	slgx_data->u32_logic_agent_id = 5;
	slgx_data->u32_logic_agent_ss = 2;
	slgx_data->u32_application_data_nvmem_id = SSR_MEM_ID_LOGIC_AGENT_APP_DATA;
	slgx_data->u32_meta_data_nvmem_id = SSR_MEM_ID_LOGIC_AGENT_META_DATA;
}

/*
--------------------------------------------------------------------------------
ssr_slgx_initialization_buffers_default()
--------------------------------------------------------------------------------
*/
/*
* @brief this routine will initialize the slgx buffers
* @param[in]     SLGX_INITIALIZATION_BUFFERS <slgx initialization buffer data structure>
* @return C_SSR_ERR_NONE if no error.Otherwise error code
*/
void ssr_slgx_initialization_buffers_default(SLGX_INITIALIZATION_BUFFERS*slgx_data)

#ifndef STOP_INITIALIZATION_OF_ARRAYS
	slgx_data->p_u8_io_items_buffer_array = (uint8_t*)st_a_slgx_io_element_buffer;
	slgx_data->u32_io_items_buffer_size = sizeof(st_a_slgx_io_element_buffer);
	slgx_data->p_u8_copy_items_buffer_array = (uint8_t*)st_a_slgx_copy_element_buffer;
	slgx_data->u32_copy_items_buffer_size = sizeof(st_a_slgx_copy_element_buffer);

	slgx_data->p_u8_io_descriptor_array = (uint8_t*)st_a_slgx_io_descriptor_buffer;
	slgx_data->u16_io_descriptor_array_size = sizeof(st_a_slgx_io_descriptor_buffer);
	slgx_data->p_io_image_address_array = (void **)p_a_slgx_io_image_address_buffer;
	slgx_data->u16_io_image_address_aray_size = sizeof(p_a_slgx_io_image_address_buffer);

	slgx_data->p_u8_input_io_image_array = (uint8_t*)u8_a_slgx_input_io_image_buffer;
	slgx_data->u16_input_io_image_size = sizeof(u8_a_slgx_input_io_image_buffer);
	slgx_data->p_u8_output_io_image_array = (uint8_t*)u8_a_slgx_output_io_image_buffer;
	slgx_data->u16_output_io_image_size = sizeof(u8_a_slgx_output_io_image_buffer);
#else
	slgx_data->p_u8_io_items_buffer_array = (uint8_t*)BUFF_STARTING_OFFSET_SLGX;
	slgx_data->u32_io_items_buffer_size = SLGX_MAX_IO_ITEMS * sizeof(SSR_SLGX_IO_ELEMENT_STRUCT);
	slgx_data->p_u8_copy_items_buffer_array = slgx_data->p_u8_io_items_buffer_array + slgx_data->u32_io_items_buffer_size;
	slgx_data->u32_copy_items_buffer_size = SLGX_MAX_COPY_ITEMS * sizeof(SSR_SLGX_IO_COPY_STRUCT);

	slgx_data->p_u8_io_descriptor_array = slgx_data->p_u8_copy_items_buffer_array + slgx_data->u32_copy_items_buffer_size;
	slgx_data->u16_io_descriptor_array_size = SLGX_MAX_IO_ITEMS * sizeof(SL_IoDescription);
	slgx_data->p_io_image_address_array = (void**)slgx_data->p_u8_io_descriptor_array + slgx_data->u16_io_descriptor_array_size;
	slgx_data->u16_io_image_address_aray_size = SLGX_MAX_IO_ITEMS * sizeof(void*);

	slgx_data->p_u8_input_io_image_array = (uint8_t*)slgx_data->p_io_image_address_array + slgx_data->u16_io_image_address_aray_size;
	slgx_data->u16_input_io_image_size = SLGX_MAX_IO_ITEMS * sizeof(uint8_t);
	slgx_data->p_u8_output_io_image_array = slgx_data->p_u8_input_io_image_array + slgx_data->u16_input_io_image_size;
	slgx_data->u16_output_io_image_size = SLGX_MAX_IO_ITEMS * sizeof(uint8_t);
#endif
}