#pragma once
#include <stddef.h>
#include "pasm64.h"
#include "node.h"

extern void* AllocateMemory(size_t size, char* file, int line);
extern void* ReallocateMemory(void* ptr, size_t size, char* file, int line);
extern void FreeMemory(void* ptr);
extern int IsTreeValid(void);
extern void PrintMemoryAllocation(void);
extern void FreeAllocatedMemory(void);

#ifdef _DEBUG
#define ALLOCATE(n) AllocateMemory((n),__FILE__, __LINE__)
#define REALLOCATE(p,n) ReallocateMemory((p),(n),__FILE__, __LINE__)
#define FREE(p) FreeMemory((p))

#define VALIDATE_TREE   if (!IsTreeValid() || !IsValidParseTree()) \
    { \
        FILE* tmp = LogFile; LogFile = stdout; PrintNode(CurrentNode); LogFile = tmp; PrintMemoryAllocation(); \
    }

#else
#define ALLOCATE(n) malloc((n))
#define REALLOCATE(p,n) realloc((p),(n))
#define FREE(p) free((p))

#define VALIDATE_TREE

#endif
