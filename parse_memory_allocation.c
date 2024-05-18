#include <structs.h>

MemoryTable parse_memory_allocation()
{
    MemoryTable table;
    table.is_fixed = true;
    table.count = 0;
    table.blocks = NULL; // Initialize blocks to NULL

    // unsigned long allocated_size;
    char user_ans;
     char user_ans;
    printf("Is your allocated memory blocks fixed or Dynamic Sized:\n (f for fixed | d for dynamic)\n");
    scanf(" %c", &user_ans);

    printf("Memory Total Size in MB\n");
    scanf("%lu", &table.memory_size);

    if (user_ans == 'f' || user_ans == 'F') {
        fixed_size_alloc_table(&table);
    } else if (user_ans == 'd' || user_ans == 'D') {
        table.is_fixed = false;
        dynamic_size_alloc_table(&table);
    } else {
        printf("Invalid input. Defaulting to fixed size allocation.\n");
    }
    return table;
}

void fixed_size_alloc_table(MemoryTable *table)
{
    unsigned long count = table->memory_size / table->frame_size;
    table->count = count;
    unsigned long frame_size;
    scanf("Memory Frame Size in MB: %lu", &frame_size);
    table->frame_size = frame_size;
    MemoryBlock *memory_blocks = table->blocks;
    memory_blocks = malloc(sizeof(MemoryBlock) * count);

    // Initialize the memory table
    for (int i = 0; i < count; count++)
    {
        memory_blocks[i].is_used = false;
        memory_blocks[i].start_address_allocated = i * frame_size;
    }

    char user_ans;
    while (1)
    {
        scanf("Would like to write in the memory?\n=>%c", &user_ans);
        if (user_ans == 'n' || user_ans == 'N')
        {
            break;
        }
        unsigned long start_addr;
        unsigned long size;
        scanf("Starting address of the process (0 - %d)\n=> %lu", table->memory_size - 1, start_addr);
        scanf("Size of the allocation\n=>%lu", &size);
        if (insert_in_memory(memory_blocks, start_addr, size))
        {
            printf("Allocation Successful\n");
        }
        else
        {
            printf("Allocation Not Successful Try again\n");
        }
    }
}

bool insert_in_memory_fixed(MemoryTable *table, unsigned long start_addr, unsigned long size)
{
    unsigned long frame_sz = table->frame_size;
    unsigned long index = start_addr / frame_sz;
    // Check if index is valid
    if (index >= table->count)
    {
        printf("Error: Start address out of range.\n");
        return false;
    }

    // Check if the frame is available
    if (table->blocks[index].is_used)
    {
        printf("Error: Frame at start address %lu is already in use.\n", start_addr);
        return false;
    }

    // Update memory block properties
    table->blocks[index].is_used = true;
    table->blocks[index].allocated_size = size;

    printf("Data successfully inserted into memory at start address %lu.\n", start_addr);
    return true;
}

void dynamic_size_alloc_table(MemoryTable *table)
{
    MemoryBlock *memory_blocks = table->blocks;
    memory_blocks = malloc(sizeof(MemoryBlock) * 100); // 100 is an arbitrary number to initialize memory blocks
    char user_ans;
    while (1)
    {
        scanf("Would like to write in the memory?\n=>%c", &user_ans);
        if (user_ans == 'n' || user_ans == 'N')
        {
            break;
        }
        unsigned long start_addr;
        unsigned long size;
        scanf("Starting address of the process (0 - %d)\n=> %lu", table->memory_size - 1, start_addr);
        scanf("Size of the allocation\n=>%lu", &size);
        if (insert_in_memory_dynamic(memory_blocks, start_addr, size))
        {
            printf("Allocation Successful\n");
        }
        else
        {
            printf("Allocation Not Successful Try again\n");
        }
    }
}

bool insert_in_memory_dynamic(MemoryTable *table, unsigned long start_addr, unsigned long size)
{
    // Check if index is valid
    for (int i = 0; i < table->count; i++)
    {
        if (table->blocks[i].start_address_allocated <= start_addr && table->blocks[i].start_address_allocated + table->blocks[i].allocated_size >= start_addr)
        {
            printf("There is a process in this memory address!\n");
            return false;
        }
    }

    // Update memory block properties
    table->blocks[++table->count].is_used = true;
    table->blocks[table->count].allocated_size = size;
    printf("Data successfully inserted into memory at start address %lu.\n", start_addr);
    return true;
}
