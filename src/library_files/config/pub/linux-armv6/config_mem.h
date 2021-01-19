#ifndef CONFIG_MEM_H_
#define CONFIG_MEM_H_

#define MAX_NUM_OF_BLOCKS 512
#define MAX_NUM_OF_CONNECTIONS 512
#define MAX_NUM_OF_VARIABLES 512
#define MAX_NUM_OF_COMMENTS 512
#define CMN_MAX_LINES_PER_CONNECTION 32
/**
 * Byte-alignment of allocated transient / persistent memory regions
 * and interpreter instance data elements.
 */
#define CMN_MEMORY_ALIGNMENT 1
/* Necessary memory alignment for each data type: */
#define CMN_MEMORY_ALIGNMENT_UINT8 1
#define CMN_MEMORY_ALIGNMENT_UINT16 1
#define CMN_MEMORY_ALIGNMENT_UINT32 1
#define CMN_MEMORY_ALIGNMENT_UINT64 1
#define CMN_MEMORY_ALIGNMENT_FLOAT 1
#define CMN_MEMORY_ALIGNMENT_DOUBLE 1

#endif /* CONFIG_MEM_H_ */
