#ifndef CONFIG_MEM_H_
#define CONFIG_MEM_H_

#define MAX_NUM_OF_BLOCKS 512u
#define MAX_NUM_OF_CONNECTIONS 512u
#define MAX_NUM_OF_VARIABLES 512u
#define MAX_NUM_OF_COMMENTS 512u
#define CMN_MAX_LINES_PER_CONNECTION 32u
/*
 Memory alignment for regions that may contain data of arbitrary types.
 Set this to the maximum value of all datatype alignments.
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
