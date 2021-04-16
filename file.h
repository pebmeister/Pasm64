#pragma once
#include <stdio.h>
#include "genlist.h"

extern FileLine* ReadFileLines(const char* fileName);
extern FILE* OpenFile(const char* file, char* mode);
