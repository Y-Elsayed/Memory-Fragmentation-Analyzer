#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
// Define data structures
typedef struct {
    unsigned long start_address_allocated;
    unsigned long allocated_size;
    bool is_used;
} MemoryBlock;

typedef struct {
    unsigned long frame_size;
    MemoryBlock *blocks;
    int count;
} MemoryTable;