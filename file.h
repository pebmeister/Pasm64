#pragma once
#include <stdio.h>
#include "genlist.h"

extern FileLine* ReadFile(const char* fileName);
extern FILE* OpenFile(const char* file, char* mode);
