#include<structs.h>
//We will use this in variable partitioning
//Iterate over the whole table, and as we go find empty holes (external fragmentation).
//We would need to calculate the total fragmentation, and find all the free holes in the memory table.
//Each block is an allocated variable partition of memory

// Function to analyze external fragmentation and suggest improvements
void external_frag_analyzer(MemoryTable *table) {
    // Check if the table is empty
    if (table->count < 1) {
        printf("Exception: Empty table.\n");
        return; // Exit function if table is empty
    }

    unsigned long total_external_fragmentation = 0;
    int num_free_holes = 0;
    unsigned long hole_size = 0;
    unsigned long *free_hole_sizes = NULL; // Array for free hole sizes

    // Calculate external fragmentation and collect statistics
    for (int i = 0; i < table->count - 1; i++) {
        // Calculate the hole between the two allocated blocks in memory
        hole_size = table->blocks[i + 1].start_address_allocated - (table->blocks[i].start_address_allocated + table->blocks[i].allocated_size);
        if (hole_size > 0) {
            // Dynamically reallocate array to include one extra hole
            free_hole_sizes = (unsigned long *)realloc(free_hole_sizes, (num_free_holes + 1) * sizeof(unsigned long));
            if (free_hole_sizes == NULL) {
                printf("Memory allocation failed.\n");
                return; // Exit function if memory allocation fails
            }
            free_hole_sizes[num_free_holes] = hole_size;
            total_external_fragmentation += hole_size;
            num_free_holes++;
        }
    }

    // Visualization for allocated blocks and free holes
    printf("\nMemory Visualization:\n");
    printf("Address\t\tMemory Contents\n");
    unsigned long current_address = 0;
    for (int i = 0; i < table->count; i++) {
        if (table->blocks[i].is_used) {
            // Allocated block
            printf("%lu\t\t", current_address);
            for (unsigned long j = 0; j < table->blocks[i].allocated_size; j++) {
                printf("X"); // Print 'X' for allocated memory cell
            }
            printf("\n");
            current_address += table->blocks[i].allocated_size;
        } else {
            // Free hole
            printf("%lu\t\t", current_address);
            for (unsigned long j = 0; j < free_hole_sizes[i]; j++) {
                printf("."); // Print '.' for free memory cell within the hole
            }
            printf("\n");
            current_address += free_hole_sizes[i];
        }
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
    printf("External Fragmentation Statistics:\n");
    printf("Total External Fragmentation: %lu bytes\n", total_external_fragmentation);
    printf("Number of Free Holes: %d\n", num_free_holes);
    printf("Average Block Size: %lu bytes\n", avg_block_size);
    printf("Average Hole Size: %lu bytes\n", avg_hole_size);
    printf("Free Hole Sizes:\n");
    for (int i = 0; i < num_free_holes; i++) {
        printf("%d. %lu bytes\n", i + 1, free_hole_sizes[i]);
    }

    // Optimization suggestions for external fragmentation
    printf("Optimization Suggestions:\n");
    // Evaluate if memory compaction is worth it
    printf("1. Memory Compaction:\n");
    if (total_external_fragmentation > table->memory_size / 2) {
        printf("   Total external fragmentation is high. Compacting memory may be beneficial.\n");
        // Implementation of memory compaction can go here
    } else {
        printf("   Total external fragmentation is low. Compacting memory may not be necessary.\n");
    }

    // Detect fragmentation pattern and suggest allocation strategy
    printf("2. Allocation Strategy Adjustment:\n");
    // Analyze block size pattern and suggest allocation strategy
    if (avg_hole_size > avg_block_size) {
        printf("   The allocation pattern seems to be lacking. Average hole size is greater than average allocated block size.\n"
               "   Consider using a variable allocation strategy.\n");
    }
    else {
        printf("   Current allocation strategy seems suitable. Block sizes are larger than hole sizes on average.\n");
    }
    // Clean up allocated memory
    free(free_hole_sizes);
}

