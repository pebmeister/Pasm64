#pragma once

#ifdef MEM_DEBUG
#include <stdlib.h>
#endif

#include "pasm64.h"
#ifdef MEM_DEBUG
#include "node.h"
#include "str.h"
#endif

extern void* AllocateMemory(size_t size, char* file, int line);
extern void* ReallocateMemory(void* ptr, size_t size, char* file, int line);
extern void FreeMemory(void* ptr);
extern int IsTreeValid(void);
extern void PrintMemoryAllocation(void);
extern void PrintMemoryAllocationSummary(void);
extern void FreeAllocatedMemory(void);
extern void FreeMemoryInternal(void* p, size_t size);
extern void FreeStrInternal(char* str);

#ifdef MEM_DEBUG
#define ALLOCATE(n) AllocateMemory((n),__FILE__, __LINE__)
#define REALLOCATE(p,n) ReallocateMemory((p),(n),__FILE__, __LINE__)
#define FREE(p)  FreeMemory((p))

#define VALIDATE_TREE   if (!IsTreeValid() || !IsValidParseTree()) \
    { \
        FILE* tmp = LogFile; LogFile = stdout; PrintNode(CurrentNode); LogFile = tmp; PrintMemoryAllocation(); \
    }

#else
#define ALLOCATE(n) malloc((n))
#define REALLOCATE(p,n) realloc((p),(n))
// DO NOT REMOVE *(char*)(p) = 0x00.
// IT IS USED TO FLAG THAT IT HAS BEEN DEALLOCATED
#define FREE(p)  { *(char*)(p) = 0x00; free((p)); }
#define VALIDATE_TREE

#endif
