#include "structs.h"
#include "parse_memory_allocation.c"
#include "internal_frag_analyzer.c"
#include "external_frag_analyzer.c"

int main() {
    MemoryTable table = parse_memory_allocation();
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