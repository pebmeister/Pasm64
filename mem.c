#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#include "mem.h"


#include "error.h"

#define PROTECTIONBUFFERSZ 4

typedef struct memory_node
{
    size_t size;
    size_t allocated_size;
    void* ptr;
    void* mem;
    struct memory_node* next;
} MemoryNode;

MemoryNode* AllocationTable = NULL;
MemoryNode* FreeAllocationTable = NULL;

int IsValidNode(MemoryNode* node)
{
    const char* module = "IsValidNode";
    int n = 0;
 /*   for (unsigned char* p = node->mem; n < PROTECTIONBUFFERSZ; ++n, ++p)
        if (*p != 0x45)
        {
            FatalError(module, error_memory_corruption_detected);
            return 0;
        }*/

    unsigned char* p = (unsigned char*)node->ptr + node->size;
    for (n = 0; n < PROTECTIONBUFFERSZ; ++n)
        if (*(p + n) != 0x45)
        {
           //  FatalError(module, error_memory_corruption_detected);
            return 0;
        }

    return -1;
}

int IsTreeValid(void)
{
    for (MemoryNode* node = AllocationTable; node; node = node->next)
    {
        if (!IsValidNode(node))
            return 0;
    }
    return 1;
}

void* AllocateMemory(const size_t size)
{
    const char* function = "AllocateMemory";

    MemoryNode* node = (MemoryNode*)malloc(sizeof(MemoryNode));
    if (node == NULL)
    {
        FatalError(function, error_outof_memory);
        return NULL;
    }
   
    memset(node, 0, sizeof(MemoryNode));

    node->size = size;
    node->allocated_size = size + PROTECTIONBUFFERSZ * 2;
    node->mem = malloc(node->allocated_size);
    if (node->mem == NULL)
    {
        FatalError(function, error_outof_memory);
        return NULL;
    }
    memset(node->mem, 0x45, node->allocated_size);
    node->ptr = node->mem;
    if (AllocationTable == NULL)
    {
        AllocationTable = node;
    }
    else
    {
        MemoryNode* tmp = AllocationTable;
        while (tmp->next)
        {
            tmp = tmp->next;
        }
        tmp->next = node;
    }
    return node->ptr;
}

void FreeMemoryNode(MemoryNode* node)
{
    memset(node->mem, 0, node->allocated_size);
    free(node->mem);
    memset(node, 0, sizeof(MemoryNode));
    free(node);
}

void FreeMemory(void* ptr)
{
    const char* function = "FreeMemory";

    if (!IsTreeValid()) return;

    if (ptr == AllocationTable->ptr)
    {
        MemoryNode* temp = AllocationTable->next;
        FreeMemoryNode(AllocationTable);
        AllocationTable = temp;
        return;
    }

    for (MemoryNode* p = AllocationTable; p->next; p = p->next)
    {
        MemoryNode* next = p->next;
        if (ptr == next->ptr)
        {
            p->next = next->next;
            FreeMemoryNode(next);

            IsTreeValid();

            return;
        }
    }

    FatalError(function, error_free_unknown_pointer);
}

void* ReallocateMemory(void* ptr, size_t size)
{
    const char* function = "ReallocateMemory";

    for (MemoryNode* node = AllocationTable; node; node = node->next)
    {
        if (node->ptr == ptr)
        {
            node->size = size;
            node->allocated_size = size + PROTECTIONBUFFERSZ * 2;
            node->mem = realloc(node->mem, node->allocated_size);
            if (!node->mem)
            {
                FatalError(function, error_outof_memory);
                return NULL;
            }
            node->ptr = (unsigned char*)node->mem;
            for (int n = 0; n < PROTECTIONBUFFERSZ; ++n)
                *(((unsigned char*)node->ptr) + size + n) = 0x45;

            return node->ptr;
        }
    }
    FatalError(function, error_free_unknown_pointer);
    return NULL;
}

void PrintMemoryAllocation(void)
{
    unsigned long long total = 0;
    unsigned long long numnodes = 0;
    for (MemoryNode* p = AllocationTable; p; p = p->next)
    {
        total += p->size;
        ++numnodes;
        // printf("%-20s %-5d %u\n", p->file, p->line, p->size);
    }
    printf("    Total %llu nodes    %llu K\n\n", numnodes, total / 1024);
}
