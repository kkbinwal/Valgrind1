#ifndef CONFIG_MEM_H_
#define CONFIG_MEM_H_

#define MAX_NUM_OF_BLOCKS 2048
#define MAX_NUM_OF_CONNECTIONS 3072
#define MAX_NUM_OF_VARIABLES 512
#define MAX_NUM_OF_COMMENTS 512
#define CMN_MAX_LINES_PER_CONNECTION 20


/*
 Memory alignment for regions that may contain data of arbitrary types.
 Set this to the maximum value of all datatype alignments.
*/
#define CMN_MEMORY_ALIGNMENT 4

/* Necessary memory alignment for each data type: */
#define CMN_MEMORY_ALIGNMENT_UINT8 1
#define CMN_MEMORY_ALIGNMENT_UINT16 2
#define CMN_MEMORY_ALIGNMENT_UINT32 4
#define CMN_MEMORY_ALIGNMENT_UINT64 4
#define CMN_MEMORY_ALIGNMENT_FLOAT 4
#define CMN_MEMORY_ALIGNMENT_DOUBLE 4

#endif /* CONFIG_MEM_H_ */
