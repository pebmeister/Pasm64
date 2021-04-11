#pragma once

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************

enum 
{
    ErrorOutofMemory = 0,
    ErrorMissingOutputFile,
    ErrorOutputFileSpecifiedMoreThanOnce,
    ErrorMissingSymbolFile,
    ErrorSymbolFileSpecifiedMoreThanOnce,
    ErrorMissingLogFile,
    ErrorLogFileSpecifiedMoreThanOnce,
    ErrorMissingListFile,
    ErrorListFileSpecifiedMoreThanOnce,
    ErrorC64OutputFormatSpecifiedMoreThanOnce,
    ErrorInstructionSetSpecifiedMoreThanOnce,
    ErrorIllegalOpcodesSpecifiedMoreThanOnce,
    ErrorNoInputFileSpecified,
    ErrorOpeningLogFile,
    ErrorOpeningInputFile,
    ErrorOpeningSymbolFile,
    ErrorOpeningOutputFile,
    ErrorOpeningListFile,
    ErrorCreatingListNode,
    ErrorValueOutofRange,
    ErrorMissingParameter,
    ErrorWritingListFile,
    ErrorReadingSourceFile,
    ErrorWritingOutputFile,
    ErrorInvalidOpcodeMode,
    ErrorInvalidOpcodeOrMode,
    ErrorSourceStringNull,
    ErrorUnrecognizedEscapeSequence,
    ErrorInvalidNumberOfOps,
    ErrorInvalidParameters,
    ErrorForRegCantBeNested,
    ErrorEndSectionWithoutSection,
    ErrorOrgSpecifiedMoreThanOnce,
    ErrorAddingSymbol,
    ErrorInitializingVariable,
    ErrorInfiniteLoopDetected,
    ErrorExpectedNext,
    ErrorDivideByZero,
    ErrorUnknownOperatorType,
    ErrorUnknownNodeType,
    ErrorSymbolReassignment,
    ErrorMacroParameterNotFound,
    ErrorMacroParameterUnderFlow,
    ErrorNoWarningSpecifiedMoreThanOnce,
    ErrrorBranchOutofRange,
    ErrorProgramCounterOutOfRange,
    ErrorMissingEndSection,
    ErrorCircularSymbolDefiniions
};

extern void Error(const char* module, int error);
extern void Warning(const char* module, int error);
extern void FatalError(const char* module, int error);
