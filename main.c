#include "structs.h"
#include "parse_memory_allocation.c"
#include "internal_frag_analyzer.c"
#include "external_frag_analyzer.c"

int main() {
    // Test data
    MemoryBlock blocks[] = {
            {0, 100, true},
            {100, 50, false},
            {150, 80, true},
            {230, 120, true},
            {350, 70, false},
            {420, 80, true},
            {500, 50, true}
    };

    MemoryTable table = {100, false, 550, blocks, 7};

    // Perform internal fragmentation analysis
    printf("Test Case 1: Internal Fragmentation Analysis\n");
    internal_frag_analyzer(&table);

    // Perform external fragmentation analysis
    printf("\nTest Case 2: External Fragmentation Analysis\n");
    external_frag_analyzer(&table);

    return 0;
}