#include "structs.h"
// Function to visualize memory layout and frame boundaries
void visualize_memory(MemoryTable *table) {
    unsigned long current_address = 0;
    unsigned long current_frame_start = 0;

    printf("Memory Layout Visualization:\n");

    // Iterate through each block and print its graphical representation
    for (int i = 0; i < table->count; i++) {
        if (current_address >= current_frame_start + table->frame_size) {
            // Reached the end of a frame
            printf("|");
            for (unsigned long j = 0; j < table->frame_size; j++) {
                printf("-");
            }
            printf("|\n");
            current_frame_start = current_address;
        }

        // Print block details
        if (table->blocks[i].is_used) {
            printf("|");
            for (unsigned long j = current_address; j < current_address + table->blocks[i].allocated_size; j++) {
                printf("#");
            }
            printf("|\n");
        } else {
            printf("|");
            for (unsigned long j = current_address; j < current_address + table->blocks[i].allocated_size; j++) {
                printf(" ");
            }
            printf("|\n");
        }

        current_address += table->blocks[i].allocated_size;
    }

    // Print the last frame boundary
    printf("|");
    for (unsigned long j = 0; j < table->frame_size; j++) {
        printf("-");
    }
    printf("|\n");
}
// Function to analyze internal fragmentation and suggest improvements
void internal_frag_analyzer(MemoryTable *table) {
    int num_blocks = table->count;
    unsigned long *internal_frag = (unsigned long *)malloc(num_blocks * sizeof(unsigned long));

    // Variables for optimization suggestion
    int blocks_above_threshold = 0;
    unsigned long total_internal_frag = 0;
    unsigned long threshold = table->blocks[0].allocated_size / 2; // Threshold set to half the allocated size of the first block

    // Calculate internal fragmentation for each block and collect statistics
    for (int i = 0; i < num_blocks; i++) {
        if (table->blocks[i].is_used) {
            internal_frag[i] = table->frame_size - table->blocks[i].allocated_size;
            total_internal_frag += internal_frag[i];
            if (internal_frag[i] > threshold) {
                blocks_above_threshold++;
            }
        } else {
            internal_frag[i] = 0;
        }
    }

    visualize_memory(table);
    // Calculate average internal fragmentation
    unsigned long avg_internal_frag = total_internal_frag / num_blocks;

    // Print internal fragmentation statistics and block details
    printf("Internal Fragmentation Statistics:\n");
    printf("Block\tInternal Fragmentation (bytes)\n");
    for (int i = 0; i < num_blocks; i++) {
        printf("%d\t%lu\n", i, internal_frag[i]);
    }
    // Print internal fragmentation statistics
    printf("Total Internal Fragmentation: %lu bytes\n", total_internal_frag);
    printf("Average Internal Fragmentation: %lu bytes\n", avg_internal_frag);
    printf("Blocks with Internal Fragmentation above 50%: %d\n", blocks_above_threshold);

    // Suggest reducing block size if many blocks have high internal fragmentation
    if (blocks_above_threshold > num_blocks / 2) {
        printf("Optimization Suggestions:\n");
        printf("1. Reduce Block Size:\n");
        printf("   Explanation: Internal fragmentation is widespread. Consider reducing the block size.\n");
    } else {
        printf("Optimization Suggestions:\n");
        printf("1. No Immediate Optimizations Needed:\n");
        printf("   Explanation: Internal fragmentation is within acceptable limits.\n");
    }
    // Clean up allocated memory
    free(internal_frag);
}