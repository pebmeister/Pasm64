// ***********************************************************************
// Author           : Paul Baxter
// Created          : 02-23-2015
//
// ***********************************************************************

#include <stdio.h>
#include <stdarg.h>

#include "opcodes.h"
#include "pasm64.h"
#include "genoutput.h"
#include "error.h"

// number of byte written to output file
int TotalBytesWritten = 0;
int ByteDelta = 0;
int Origin = 0;

/// <summary>
/// Generate output to the object file
/// based on node
///
/// This should only be called on the FinalPass
/// when all symbols/macros are resolved
/// </summary>
/// <param name="p">The parseNode.</param>
/// <returns>int.</returns>
int GenerateOut(ParseNodePtr p)
{
    size_t bytesWritten;
    int op;
    const int startBytes = TotalBytesWritten;
    unsigned char byte;
    const char* module = "GenerateOut";

    // if there is no output file exit
    if (OutputFile == NULL)
        return 0;

    if (!OriginSpecified)
        return 0;

    if (TotalBytesWritten == 0)
    {
        Origin = PC;
        ByteDelta = 0;
    }

    if (TotalBytesWritten == 0 && OutFileFormat == c64)
    {
        unsigned char hi = (unsigned char)((PC & 0xFF00) >> 8);
        unsigned char lo = (unsigned char)(PC & 0xFF);

        bytesWritten = fwrite(&lo, 1, 1, OutputFile);
        if (bytesWritten < 1)
        {
            Error(module, error_writing_output_file);
            return 0;
        }
        TotalBytesWritten += (int)bytesWritten;

        bytesWritten = fwrite(&hi, 1, 1, OutputFile);
        if (bytesWritten < 1)
        {
            Error(module, error_writing_output_file);
            return 0;
        }
        TotalBytesWritten += (int)bytesWritten;
        ByteDelta = 2;
    }

    const int delta = PC - Origin;

    while (delta + ByteDelta > TotalBytesWritten)
    {
        char ch = 0;
        fwrite(&ch, 1, 1, OutputFile);
        ++TotalBytesWritten;
    }

    // output a string
    if (p->type == type_str)
    {
        char* str = p->str.value;
        const int outlen = p->str.len;
        bytesWritten = fwrite(str, 1, outlen, OutputFile);
        if (bytesWritten < 1)
        {
            Error(module, error_writing_output_file);
            return 0;
        }
        TotalBytesWritten += (int)bytesWritten;

        // if using a string with WORD then pad to a word boundary
        if (DataSize == 2 && outlen % 2)
        {
            op = 0;
            bytesWritten = fwrite((char*)&op, 1, 1, OutputFile);
            if (bytesWritten < 1)
            {
                Error(module, error_writing_output_file);
                return 0;
            }
            TotalBytesWritten += (int)bytesWritten;
        }
        return TotalBytesWritten - startBytes;
    }

    // if it is not an opcode then it
    // must evaluate to an integer value
    // DataSize will contain the max number of bytes 0,1, or 2
    // 0 signifies a string value which is dealt with above
    if (p->type != type_op_code)
    {
        unsigned char hi;
        unsigned char lo;

        // expand the expression
        op = Ex(p);
        const int overflow = (op & ~0xFFFF) != 0;

        // extract the hi and lo bytes
        hi = (unsigned char)((op & 0xFF00) >> 8);
        lo = (unsigned char)(op & 0xFF);

        if ((hi != 0 && DataSize < 2) || overflow)
        {
            Error(module, error_value_out_of_range);
            return 0;
        }
        bytesWritten = fwrite(&lo, 1, 1, OutputFile);
        if (bytesWritten < 1)
        {
            Error(module, error_writing_output_file);
            return 0;
        }
        TotalBytesWritten += (int)bytesWritten;

        if (DataSize > 1)
        {
            bytesWritten = fwrite(&hi, 1, 1, OutputFile);
            if (bytesWritten < 1)
            {
                Error(module, error_writing_output_file);
                return 0;
            }
            TotalBytesWritten += (int)bytesWritten;
        }
        return TotalBytesWritten - startBytes;
    }

    // the node is an opcode
    // get the number of bytes needed
    // based on addressing mode of opcode
    const int bytes = GetOpByteCount(p);

    // write the opcode byte
    byte = (unsigned char) (p->opcode.opcode & 0xFF);
    bytesWritten = fwrite(&byte, 1, 1, OutputFile);
    if (bytesWritten < 1)
    {
        Error(module, error_writing_output_file);
        return 0;
    }
    TotalBytesWritten += (int)bytesWritten;

    if (bytes > 0)
    {
        unsigned char hi;
        unsigned char lo;

        // expand the data bytes
        op = Ex(p->op[0]);

        if (p->opcode.mode == zr)
        {            
            if (p->nops != 2)
            {
                Error(module, error_missing_parameter);
                return 0;
            }
            op = Ex(p->op[1]);
            // make sure a branch is in range
            op -= (p->opcode.pc + 2);               
            if (op > 128 || op < -127)
            {
                Error(module, error_value_out_of_range);
                return 0;
            }
            op &= 0xFF;
            bytesWritten = fwrite(&op, 1, 1, OutputFile);
            if (bytesWritten < 1)
            {
                Error(module, error_writing_output_file);
                return 0;
            }
            TotalBytesWritten += (int)bytesWritten;

            op = Ex(p->op[0]);
            hi = (unsigned char)((op & 0xFF00) >> 8);
            lo = (unsigned char)(op & 0xFF);
            if (hi != 0)
            {
                Error(module, error_value_out_of_range);
                return 0;
            }
            bytesWritten = fwrite(&lo, 1, 1, OutputFile);
            if (bytesWritten < 1)
            {
                Error(module, error_writing_output_file);
                return 0;
            }
            TotalBytesWritten += (int)bytesWritten;

            return TotalBytesWritten - startBytes;
        }
        if (p->opcode.mode == r)
        {
            // make sure a branch is in range
            op -= (p->opcode.pc + 2);               

            if (op > 128 || op < -127)
            {
                Error(module, error_value_out_of_range);
                return 0;
            }
            op &= 0xFF;
        }

        // get the hi and lo bytes
        hi = (unsigned char)((op & 0xFF00) >> 8);
        lo = (unsigned char)(op & 0xFF);

        // write then to the object file 
        bytesWritten = fwrite(&lo, 1, 1, OutputFile);
        if (bytesWritten < 1)
        {
            Error(module, error_writing_output_file);
            return 0;
        }
        TotalBytesWritten += (int)bytesWritten;

        if (bytes > 1)
        {
            bytesWritten = fwrite(&hi, 1, 1, OutputFile);
            if (bytesWritten < 1)
            {
                Error(module, error_writing_output_file);
                return 0;
            }
            TotalBytesWritten += (int)bytesWritten;
        }
    }

    // return the number of actual bytes written
    return TotalBytesWritten - startBytes;
}

/// <summary>
/// Gets the op byte count.
/// </summary>
/// <param name="p">The parseNode.</param>
/// <returns>int.</returns>
int GetOpByteCount(ParseNodePtr p)
{
    int byteCount;
    const char* module = "GetOpByteCount";

    if (p->type != type_op_code)
        return 0;

    switch (p->opcode.mode)
    {
        case A:     /* Accumulator          */
        case i:     /* implied              */
            byteCount = 0;
            break;

        case I:     /* immediate            */
        case r:     /* relative             */
        case zp:    /* zero page            */
        case zr:    /* zero page relative   */
        case zpi:   /* zero page indirect   */
        case zpx:   /* zero page x          */
        case zpy:   /* zero page y          */
        case zpix:  /* zero page indirect x */
        case zpiy:  /* zero page indirect y */
            byteCount = 1;
            break;

        case a:     /* absolute             */
        case ax:    /* absolute x           */
        case ay:    /* absolute y           */
        case aix:   /* absolute indirect x  */
        case ind:   /* absolute indirect    */
            byteCount = 2;
            break;

        default:
            Error(module, error_invalid_opcode_mode);
            return 0;
    }
    return byteCount;
}
