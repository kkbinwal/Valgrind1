/*
+------------------------------------------------------------------------------+
| Molex
| -----------------------------------------------------------------------------
| Copyright 2019 (c) Molex. All rights reserved.
+------------------------------------------------------------------------------+
 */
 /**
 *  @file    ssr_beta_platform_data.h
 *  @brief
 *  @author  $Author:  $
 *  @version $Revision:  $
 *  @date    $Date:  $
 *---------------------------------------------------------------------------
 *  @details
 *---------------------------------------------------------------------------
 Version     | Date      | Author        | Comments
 */

#ifndef _SSR_SLGX_PLATFORM_DATA_H_ 
#define _SSR_SLGX_PLATFORM_DATA_H_  

/* INCLUDED HEADER FILES */
#include "ssr/ssr_core_header.h"
#include "ssr/ssr_core_types.h"

#define SSR_UAID_SRTS SSR_UAID_SLGX
#define MAX_IO_ITEM_NAME_SIZE 64

#pragma pack(1)
typedef enum {
	CMN_DataTypeNone = 0, /**< No data type (e.g. for block type "FB"). */
	CMN_DataTypeBool,     /**< Boolean. */
	CMN_DataTypeSafebool, /**< Safebool. */
	CMN_DataTypeByte,     /**< Byte. */
	CMN_DataTypeUsint,    /**< Unsigned short integer. */
	CMN_DataTypeSint,     /**< Short integer. */
	CMN_DataTypeWord,     /**< Word. */
	CMN_DataTypeUint,     /**< Unsigned integer. */
	CMN_DataTypeInt,      /**< Integer. */
	CMN_DataTypeDword,    /**< Double word. */
	CMN_DataTypeUdint,    /**< Unsigned double integer. */
	CMN_DataTypeDint,     /**< Double integer. */
	CMN_DataTypeLword,    /**< Long word. */
	CMN_DataTypeUlint,    /**< Unsigned long integer. */
	CMN_DataTypeLint,     /**< Long integer. */
	CMN_DataTypeReal,     /**< Single precision real. */
	CMN_DataTypeLreal,    /**< Double precision real. */
	CMN_DataTypeTime,     /**< Time. */
	CMN_DataTypeLtime,    /**< Long time. */
	CMN_DataTypeDate,     /**< Date. */
	CMN_DataTypeLdate,    /**< Long date. */
	CMN_DataTypeTod,      /**< Time of day. */
	CMN_DataTypeLtod,     /**< Long time of day. */
	CMN_DataTypeDt,       /**< Time and date. */
	CMN_DataTypeLdt,      /**< Long time and date. */
	CMN_DataTypeSafeint   /**< Safeint. */
} CMN_DataType;
#pragma pack()

#pragma pack(1)
typedef char const* SL_ConstCStr;        /**< \0-terminated string, which is constant */
#pragma pack()

#pragma pack(1)
typedef enum {
	SL_IoDirectionInput = 0,  /**< Input IO. */
	SL_IoDirectionOutput = 1   /**< Output IO. */
} SL_IoDirection;
#pragma pack()

#pragma pack(1)
typedef struct
{
	SL_ConstCStr name; /**< name of the IO-Resource */
	SL_IoDirection ioDirection; /**< INPUT or OUTPUT */
	CMN_DataType dataType; /**< data type and implicitly the size */
} SL_IoDescription;
#pragma pack()

#pragma pack(1)
typedef struct
{
	uint32_t u32_io_item_offset; /* Item offset. Into Logic Agent IO buffer (inputImage or outputImage) */
	uint16_t u16_io_item_dir_apply; /* Item Direction.  Can be: SL_IoDirectionInput, SL_IoDirectionOutput */
	uint16_t u16_io_item_dir_default; /* Item Direction.  Can be: u16_io_item_dir_apply or SLGX_DIRECTION_DISABLED */
	uint32_t u32_io_item_type; /* Item type.       Can be: CMN_DataTypeBool, CMN_DataTypeSafebool, CMN_DataTypeByte, etc*/
	uint32_t u32_reserved; /*Reserve for future configuration values*/
	uint32_t u32_io_item_name_size;/* Item Name size. */
	uint32_t  u32_io_Driven_by;     /* DRIVEN_BY_NETWORK or DRIVEN_BY_LOGIC */
	uint8_t u8_a_io_element_name[MAX_IO_ITEM_NAME_SIZE];
} SSR_SLGX_IO_ELEMENT_STRUCT;
#pragma pack()

#pragma pack(1)
typedef struct
{
	uint32_t u32_ssr_io_item_id; /* SSR IO item to read (for input) or write (for output) via ssr_io_read and ssr_io_write */
	uint32_t u32_ssr_io_item_offset; /* u32_item_offset argument for ssr_io_read and ssr_io_write */
	uint32_t u32_ssr_io_item_size; /* u32_data_size argument for ssr_io_read and ssr_io_write */
	uint32_t u32_ssr_io_copy_type; /* Item type.   Can be: SSR_COPY_TYPE_NORMAL, SSR_COPY_TYPE_BIT  */
	uint32_t u32_io_item_offset; /* Item offset. Into Logic Agent IO buffer (inputImage or outputImage) */
	uint32_t	u32_ssr_io_item_id_network;/* the SSR IO Item ID that the Logic Agent can use to get the ‘driven by network’ values */
	uint32_t	u32_ssr_io_item_offset_network; /* the SSR IO Item offset that the Logic Agent can use to get the ‘driven by network’ values */
} SSR_SLGX_IO_COPY_STRUCT;
#pragma pack()

#pragma pack(1)
typedef struct SLGX_PLATFORM_DATA_Data
{
	uint8_t  dummy;
} SLGX_PLATFORM_DATA;
#pragma pack()

#pragma pack(1)
typedef struct SLGX_INITIALIZATION_DATA_Data
{
  uint32_t u32_partner_bridge_id;
  uint32_t u32_partner_bridge_ss;
  uint32_t u32_logic_agent_id;
  uint32_t u32_logic_agent_ss;
  uint32_t u32_application_data_nvmem_id;
  uint32_t u32_meta_data_nvmem_id;
} SLGX_INITIALIZATION_DATA;
#pragma pack()

#pragma pack(1)
typedef struct SLGX_INITIALIZATION_BUFFERS_Data
{
  uint8_t* p_u8_input_io_image_array;
  uint16_t u16_input_io_image_size;
  uint8_t* p_u8_output_io_image_array;
  uint16_t u16_output_io_image_size;

  uint8_t* p_u8_io_descriptor_array;
  uint16_t u16_io_descriptor_array_size;
  void** p_io_image_address_array;
  uint16_t u16_io_image_address_aray_size;

  uint8_t* p_u8_io_items_buffer_array;
  uint32_t u32_io_items_buffer_size;
  uint8_t* p_u8_copy_items_buffer_array;
  uint32_t u32_copy_items_buffer_size;
} SLGX_INITIALIZATION_BUFFERS;
#pragma pack()

SSR_AGENT_ENTRY * slogix(void);



#endif
