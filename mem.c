#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "str.h"
#include "mem.h"

#include "error.h"

#pragma warning(disable:4996)
#pragma warning(disable:4477)

#define PROTECTION_BUFFER_SIZE 4

typedef struct memory_node
{
    size_t size;
    size_t allocated_size;
    void* ptr;
    void* mem;
    char* file;
    int line;
    struct memory_node* next;
} MemoryNode;

MemoryNode* AllocationTable = NULL;
MemoryNode* FreeAllocationTable = NULL;

int IsValidNode(MemoryNode* node)
{
    const char* module = "IsValidNode";
    unsigned char* p = node->mem;
    for (int n = 0; n < PROTECTION_BUFFER_SIZE; ++n)
        if (*(p + n) != 0x45)
        {
            FatalError(module, error_memory_corruption_detected);
            return 0;
        }

    p = (unsigned char*)node->ptr + node->size;
    for (int n = 0; n < PROTECTION_BUFFER_SIZE; ++n)
        if (*(p + n) != 0x45)
        {
            FatalError(module, error_memory_corruption_detected);
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

void MarkNode(MemoryNode* node)
{
    node->ptr = (unsigned char*)node->mem + PROTECTION_BUFFER_SIZE;
    unsigned char* p = (unsigned char*)node->mem;
    for (int n = 0; n < PROTECTION_BUFFER_SIZE; ++n)
        *(p + n) = 0x45;

    p = (unsigned char*)node->ptr + node->size;
    for (int n = 0; n < PROTECTION_BUFFER_SIZE; ++n)
        *(p + n) = 0x45;

}

void* AllocateMemory(const size_t size, char* file, const int line)
{
    const char* function = "AllocateMemory";

    MemoryNode* node = (MemoryNode*)malloc(sizeof(MemoryNode));
    if (node == NULL)
    {
        FatalError(function, error_out_of_memory);
        return NULL;
    }
   
    memset(node, 0, sizeof(MemoryNode));
    node->size = size;
    node->allocated_size = size + PROTECTION_BUFFER_SIZE * 2;
    node->mem = malloc(node->allocated_size);
    if (node->mem == NULL)
    {
        FatalError(function, error_out_of_memory);
        return NULL;
    }

    // ReSharper disable once CppDeprecatedEntity
    node->file = strdup(file);  // NOLINT(clang-diagnostic-deprecated-declarations)
    node->line = line;

    MarkNode(node);

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
    FreeMemoryInternal(node->mem, node->size);
    FreeStrInternal(node->file);
    FreeMemoryInternal(node, sizeof(MemoryNode));
}

void FreeMemory(const void* ptr)
{
    const char* function = "FreeMemory";

    if (ptr == NULL)
        return;

    RemoveStringNode(ptr);

    MemoryNode* prev = AllocationTable;

    if (ptr == AllocationTable->ptr)
    {
        MemoryNode* temp = AllocationTable->next;
        FreeMemoryNode(AllocationTable);
        AllocationTable = temp;
        return;
    }

    for (MemoryNode* p = AllocationTable->next; p; p = p->next)
    {
        if (ptr == p->ptr)
        {
            prev->next = p->next;
            FreeMemoryNode(p);
            return;
        }
        prev = p;
    }
    Warning(function, error_free_unknown_pointer);
}

void* ReallocateMemory(void* ptr, const size_t size, char* file, int line)
{
    const char* function = "ReallocateMemory";

    for (MemoryNode* node = AllocationTable; node; node = node->next)
    {
        if (node->ptr == ptr)
        {
            void* copy = AllocateMemory(size, file, (int)size);
            if (copy == NULL)
            {
                FatalError(function, error_out_of_memory);
                return NULL;
            }
            memcpy(copy, node->ptr, size);
            FreeMemory(node->ptr);
            node->ptr = copy;
            return copy;
        }
    }
    FatalError(function, error_free_unknown_pointer);
    return NULL;
}

void FreeAllocatedMemory(void)
{
    VALIDATE_TREE

    MemoryNode* p = AllocationTable;
    while (p != NULL)
    {
        FreeMemory(p->ptr);
        p = AllocationTable;
    }
}

void PrintMemoryAllocationSummary(void)
{
    unsigned long long total = 0;
    unsigned long long numNodes = 0;
    for (MemoryNode* p = AllocationTable; p; p = p->next)
    {
        total += p->size;
        ++numNodes;
    }
    printf("    Total %llu nodes    %llu K allocated.\n", numNodes, total / 1024);
}

void PrintMemoryAllocation(void)
{
    unsigned long long total = 0;
    unsigned long long numNodes = 0;
    for (MemoryNode* p = AllocationTable; p; p = p->next)
    {
        total += p->size;
        ++numNodes;
        printf("%-20s %-5d %lu\n", p->file, p->line, (unsigned long)p->size);
    }
    printf("    Total %llu nodes    %llu K\n", numNodes, total / 1024);
}

void FreeMemoryInternal(void* p, size_t size)
{
    memset(p, 0x54, size);
    free(p);
}

void FreeStrInternal(char* str)
{
    FreeMemoryInternal(str, strlen(str));
}
