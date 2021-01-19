/* Copyright (C) logi.cals GmbH. All rights reserved. */
#ifndef APPLICATION_MODEL_EXECORDER_PRIV_H_
#define APPLICATION_MODEL_EXECORDER_PRIV_H_

/* -- Include files --------------------------------------------------------- */

#include <application_model_priv.h>
#include <application_model_types.h>
#include <common_bitfields.h>
#include <common_types.h>

/* -- Externals ------------------------------------------------------------- */

/* -- Defines --------------------------------------------------------------- */

/* -- Typedefs -------------------------------------------------------------- */

/**
 * Identifier of a network
 */
typedef uint16_t APM_NetworkId;

/**
 * Identifier of a network item
 */
typedef uint16_t APM_NetworkItemId;

typedef uint16_t APM_NetworkCount;

typedef uint16_t APM_NetworkItemCount;

typedef struct
{
  CMN_BlockHandle blockHandle;
  APM_Command command;
  APM_NetworkId networkId;
  CMN_Bool networkHasLoop;
} APM_NetworkItem;

/**
 * A list which assigns all blocks to their network.
 * If a block is not contained by a network, than it has MAX_NUM_OF_BLOCKS value.
 */
typedef APM_NetworkItem APM_NetworkList[MAX_NUM_OF_BLOCKS + MAX_NUM_OF_CONNECTIONS];

typedef APM_NetworkItem APM_CommandList[];

typedef CMN_Bitfield(APM_VariableSet, MAX_NUM_OF_VARIABLES);

typedef CMN_Bitfield(APM_NetworkItemSet, APM_MAX_NUM_OF_NETWORK_ITEMS);

/**
 * An array of APM_MAX_NUM_OF_NETWORK_ITEMS bitfields, each holding
 * APM_MAX_NUM_OF_NETWORK_ITEMS bits.
 */
typedef struct {
  size_t numRows;
  size_t bitsPerRow;
  CMN_Bitfield(table[APM_MAX_NUM_OF_NETWORK_ITEMS], APM_MAX_NUM_OF_NETWORK_ITEMS);
} APM_NetworkItemsBitfieldArray;

typedef struct {
  CMN_Coordinate* coordinates;
  CMN_Coordinate* alternativeCoordinates;
  APM_NetworkItem* networkItems;
} APM_ResolveLoopContext;

/**
 * An array of MAX_NUM_OF_BLOCKS bitfields, each holding MAX_NUM_OF_BLOCKS bits.
 */
typedef struct {
  size_t const numRows;
  size_t const bitsPerRow;
  CMN_Bitfield(table[MAX_NUM_OF_BLOCKS], MAX_NUM_OF_BLOCKS);
} BlocksBitfieldArray;

#define INIT_BLOCKS_BITFIELD_ARRAY     \
{                                      \
    .numRows = MAX_NUM_OF_BLOCKS,      \
    .bitsPerRow = MAX_NUM_OF_BLOCKS    \
}

typedef CMN_Rc (*APM_HandleCycle)(APM_Instance const*, APM_NetworkItemCount,\
    APM_NetworkItemsBitfieldArray* aDepTable, APM_NetworkItemId*, APM_ResolveLoopContext* aHandleCycleContext);

typedef struct
{
  APM_NetworkId networkId;
  CMN_Bool networkHasLoop;
} APM_BlockToNetworkItem;

/* -- Prototypes ------------------------------------------------------------ */
void APM_internalAssignNetworks(
    APM_Instance const* aInstance,
    BlocksBitfieldArray* aTable,
    APM_NetworkList aNetworkList,
    APM_NetworkCount* aNumOfNetworks);

/**
 * Fills a bit-table with network-network dependency information
 * @param aInstance The APM instance pointer
 * @param aNetworkList the network list as produced by APM_internalAssignNetworks
 * @param aNumOfNetworks the actual number of networks found in model.
 * @param aTable bitField-based table, where a bit at [i][j] indicates that network i depends on network j
 */
void APM_internalBuildNetworkDependencyTable(
    APM_Instance const* aInstance,
    APM_NetworkList const aNetworkList,
    APM_NetworkCount aNumOfNetworks,
    APM_NetworkItemsBitfieldArray* networkItemTable);

/**
 * @param[in] aNumOfItems number of items to sort
 * @param[in,out] aDepTable
 * @param[in] aHandleCycle function that is called to handle cycles (can be null, in which case a
 *            default cycle handler will be used)
 * @param[in,out] aResult pointer to an array containing aNumOfItems item ids
 */
CMN_Rc APM_internalTopologyOrder(
    APM_Instance const* aInstance,
    APM_NetworkItemCount aNumOfItems,
    APM_NetworkItemsBitfieldArray* aDepTable,
    APM_HandleCycle aHandleCycle,
    APM_ResolveLoopContext* aHandleCycleContext,
    APM_NetworkItemId* aResult);

void APM_internalBuildBlockDependencyTable(APM_Instance const* aInstance, BlocksBitfieldArray* aTable);

APM_Rc APM_internalComputeNetworkOrder(APM_Instance const*, APM_NetworkList aNetworkList, APM_NetworkCount aNumOfNetworks);

void APM_internalBuildCommandDependencyTable(
    APM_Instance const* aInstance,
    APM_CommandList const aCommandList,
    CMN_Count aNumOfCommands,
    APM_NetworkItemsBitfieldArray* aTable);

APM_Rc APM_internalComputeCommandOrder(APM_Instance const* aInstance, APM_NetworkList aNetworkList);

/**
 * Set sequence number of all blocks to INVALID
 *
 * @req{SAFE-3612}
 *
 * @param[in] aInstance The application model instance
 */
void APM_internalClearSequenceNumbers(APM_InstancePtr aInstance);

#endif /* APPLICATION_MODEL_EXECORDER_PRIV_H_ */
