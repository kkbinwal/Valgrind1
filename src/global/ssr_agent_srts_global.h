/*
+------------------------------------------------------------------------------+
| Molex Industrial Communications
| --------------------
| Copyright 2018 (c) Molex. All rights reserved.
|+------------------------------------------------------------------------------+
| Project SSR
+------------------------------------------------------------------------------+
*/
/**
*  @file    ssr_agent_srts_global
*  @brief   
*  @author  $Author:  $
*  @version $Revision:  $
*  @date    $Date:  $
*---------------------------------------------------------------------------
*  @details 
*---------------------------------------------------------------------------
*/

#ifndef _SSR_AGENT_SRTS_GLOBAL_H_ 
#define _SSR_AGENT_SRTS_GLOBAL_H_ 

#include "ssr/ssr_core_header.h"


/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_get_uaid() - Agent get UAID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Get UAID for this agent
*
* @param[in]     void
*
* @return        uint32_t
*/
uint32_t ssr_agent_srts_global_get_uaid(
    void 
);  

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_get_state() - Agent get state function
--------------------------------------------------------------------------------
*/
/**
* @brief         Get state for this agent
*
* @param[in]     void
*
* @return        uint32_t
*/
uint32_t ssr_agent_srts_global_get_state(
    void 
);


/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_set_state() - Agent set state function
--------------------------------------------------------------------------------
*/
/**
* @brief         Set state for this agent
*
* @param[in]     u32_agent_state
*
* @return        void
*/
void ssr_agent_srts_global_set_state(
    uint32_t u32_agent_state
);

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_get_aid() - Agent get AID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Get AID for this agent
*
* @param[in]     void
*
* @return        uint16_t
*/
uint16_t ssr_agent_srts_global_get_aid(
    void 
);

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_set_aid() - Agent set AID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Set AID for this agent
*
* @param[in]     u16_agent_id
*
* @return        void
*/
void     ssr_agent_srts_global_set_aid(
    uint16_t u16_agent_id 
);


/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_get_ssid() - Agent get SSID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Get SSID for this agent
*
* @param[in]     void
*
* @return        uint16_t
*/
uint16_t ssr_agent_srts_global_get_ssid(
    void 
);

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_set_ssid() - Agent set SSID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Set SSID for this agent
*
* @param[in]     u16_subsystem_id
*
* @return        void
*/
void ssr_agent_srts_global_set_ssid( 
    uint16_t u16_subsystem_id 
);

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_set_partner() - Agent set Partner Agent ID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Set ID info for partner agent
*
* @param[in]     u16_subsystem_id
* @param[in]     uint16_t
*
* @return        void
*/
void ssr_agent_srts_global_set_partner(
    uint16_t u16_subsystem_id, 
    uint16_t u16_agent_id 
);

/*
--------------------------------------------------------------------------------
ssr_agent_srts_global_get_partner() - Agent get Partner Agent ID function
--------------------------------------------------------------------------------
*/
/**
* @brief         Get ID info for partner agent
*
* @param[out]    p_u16_subsystem_id
* @param[out]    p_u16_agent_id
*
* @return        void
*/
void ssr_agent_srts_global_get_partner(
    uint16_t * p_u16_subsystem_id, 
    uint16_t * p_u16_agent_id 
);


#endif

