// structs.h
#ifndef STRUCTS_H
#define STRUCTS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    unsigned long start_address_allocated;
    unsigned long allocated_size;
    bool is_used;
} MemoryBlock;

typedef struct {
    unsigned long frame_size;
    bool is_fixed;
    unsigned long memory_size;
    MemoryBlock *blocks;
    int count;
} MemoryTable;

#endif /* STRUCTS_H */
