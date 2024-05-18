#include "structs.h"
#include "parse_memory_allocation.c"
#include "internal_frag_analyzer.c"
#include "external_frag_analyzer.c"
// Function prototypes for automated input
void automate_fixed_size_input();
void automate_dynamic_size_input();

int main() {
    // Test Case 1: Fixed-Size Memory Allocation
    automate_fixed_size_input();

    // Test Case 2: Dynamic-Size Memory Allocation
    automate_dynamic_size_input();

    return 0;
}

void automate_fixed_size_input() {
    printf("Test Case 1: Fixed-Size Memory Allocation\n");

    // Simulate user input for fixed-size memory allocation
    MemoryTable table1;
    table1.is_fixed = true;
    table1.count = 0;
    table1.blocks = NULL;

    table1.memory_size = 100;
    table1.frame_size = 10;

    insert_in_memory_fixed(&table1, 10, 20);
    insert_in_memory_fixed(&table1, 50, 15);

    // Perform analysis
    internal_frag_analyzer(&table1);
    free(table1.blocks); // Free dynamically allocated memory
}

void automate_dynamic_size_input() {
    printf("Test Case 2: Dynamic-Size Memory Allocation\n");

    // Simulate user input for dynamic-size memory allocation
    MemoryTable table2;
    table2.is_fixed = false;
    table2.count = 0;
    table2.blocks = NULL;

    table2.memory_size = 100;

    insert_in_memory_dynamic(&table2, 10, 20);
    insert_in_memory_dynamic(&table2, 40, 15);

    // Perform analysis
    external_frag_analyzer(&table2);
    free(table2.blocks); // Free dynamically allocated memory
}