#include "structs.h"
#include "parse_memory_allocation.c"
#include "internal_frag_analyzer.c"
#include "external_frag_analyzer.c"

int main() {
    //MemoryTable table = parse_memory_allocation();
    // Define the test data
    MemoryBlock blocks[] = {
            {0, 100, true},
            {100, 50, true},
            {200, 80, true},
            {410, 80, true},
            {500, 50, true}
    };

    // Create the MemoryTable structure and initialize it with the test data
    MemoryTable table;
    table.frame_size = 100; // Frame size for fixed memory blocks
    table.is_fixed = true;
    table.memory_size = 600; // Total memory size
    table.blocks = blocks; // Assign the test data blocks array
    table.count = 5; // Number of blocks
    if(table.is_fixed == true)
    {
        internal_frag_analyzer(&table);
    }
    else {
        // Perform external fragmentation analysis
        external_frag_analyzer(&table);
    }
    return 0;
}