#include "structs.h"
//We will use this in variable partitioning
//Iterate over the whole table, and as we go find empty holes (external fragmentation).
//We would need to calculate the total fragmentation, and find all the free holes in the memory table.
//Each block is an allocated variable partition of memory

void external_frag_analyzer(MemoryTable *table) {
    if (table->count < 1) {
        printf("Exception: Empty table.\n");
        return;
    }

    unsigned long total_external_fragmentation = 0;
    int num_free_holes = 0;
    unsigned long current_address = 0;
    unsigned long *free_hole_sizes = NULL;

    // Memory Visualization Header
    printf("\nMemory Visualization:\n");
    printf("Address\t\tMemory Contents\n");
    printf("--------\t----------------\n");

    for (int i = 0; i < table->count; i++) {
        // Check if there's a free hole before the current block
        if (table->blocks[i].start_address_allocated > current_address) {
            unsigned long hole_size = table->blocks[i].start_address_allocated - current_address;
            free_hole_sizes = (unsigned long *)realloc(free_hole_sizes, (num_free_holes + 1) * sizeof(unsigned long));
            if (free_hole_sizes == NULL) {
                printf("Memory allocation failed.\n");
                return;
            }
            free_hole_sizes[num_free_holes] = hole_size;
            total_external_fragmentation += hole_size;
            num_free_holes++;

            // Print the free hole
            printf("%-8lu\t", current_address);
            for (unsigned long j = 0; j < hole_size; j++) {
                printf(".");
            }
            printf(" (free hole)\n");
            current_address += hole_size;
        }

        // Print the allocated block
        if (table->blocks[i].is_used) {
            printf("%-8lu\t", table->blocks[i].start_address_allocated);
            for (unsigned long j = 0; j < table->blocks[i].allocated_size; j++) {
                printf("X");
            }
            printf(" (allocated block)\n");
            current_address = table->blocks[i].start_address_allocated + table->blocks[i].allocated_size;
        }
    }

    // Check if there's a free hole after the last block
    if (current_address < table->memory_size) {
        unsigned long hole_size = table->memory_size - current_address;
        free_hole_sizes = (unsigned long *)realloc(free_hole_sizes, (num_free_holes + 1) * sizeof(unsigned long));
        if (free_hole_sizes == NULL) {
            printf("Memory allocation failed.\n");
            return;
        }
        free_hole_sizes[num_free_holes] = hole_size;
        total_external_fragmentation += hole_size;
        num_free_holes++;

        // Print the final free hole
        printf("%-8lu\t", current_address);
        for (unsigned long j = 0; j < hole_size; j++) {
            printf(".");
        }
        printf(" (free hole)\n");
    }

    // Calculate average block size
    unsigned long total_block_size = 0;
    for (int i = 0; i < table->count; i++) {
        total_block_size += table->blocks[i].allocated_size;
    }
    unsigned long avg_block_size = table->count > 0 ? total_block_size / table->count : 0;

    // Calculate average hole size
    unsigned long total_hole_size = 0;
    for (int i = 0; i < num_free_holes; i++) {
        total_hole_size += free_hole_sizes[i];
    }
    unsigned long avg_hole_size = num_free_holes > 0 ? total_hole_size / num_free_holes : 0;

    // Print external fragmentation statistics
    printf("\nExternal Fragmentation Statistics:\n");
    printf("Total External Fragmentation: %lu bytes\n", total_external_fragmentation);
    printf("Number of Free Holes: %d\n", num_free_holes);
    printf("Average Block Size: %lu bytes\n", avg_block_size);
    printf("Average Hole Size: %lu bytes\n", avg_hole_size);
    printf("Free Hole Sizes:\n");
    for (int i = 0; i < num_free_holes; i++) {
        printf("%d. %lu bytes\n", i + 1, free_hole_sizes[i]);
    }

    // Optimization suggestions for external fragmentation
    printf("\nOptimization Suggestions:\n");
    printf("1. Memory Compaction:\n");
    if (total_external_fragmentation > table->memory_size / 2) {
        printf("   Total external fragmentation is high. Compacting memory may be beneficial.\n");
    } else {
        printf("   Total external fragmentation is low. Compacting memory may not be necessary.\n");
    }

    printf("2. Allocation Strategy Adjustment:\n");
    if (avg_hole_size > avg_block_size) {
        printf("   The allocation pattern seems to be lacking. Average hole size is greater than average allocated block size.\n"
               "   Consider using a different allocation strategy, it seems like it uses worst-fit.\n");
    } else {
        printf("   Current allocation strategy seems suitable. Block sizes are larger than hole sizes on average.\n");
    }

    free(free_hole_sizes);
}