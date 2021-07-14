// ReSharper disable CppClangTidyBugproneBranchClone
// ReSharper disable CppClangTidyClangDiagnosticCoveredSwitchDefault
// ReSharper disable CppClangTidyBugproneExceptionEscape
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

typedef enum
{
    i = 0,  /* implied              */
    im,     /* immediate            */
    zp,     /* zero page            */
    zpi,    /* zero page indirect   */
    zpx,    /* zero page x          */
    zpy,    /* zero page y          */

    zpix,   /* zero page indirect x */
    zpiy,   /* zero page indirect y */
    a,      /* absolute             */
    aix,    /* absolute indirect x  */
    ax,     /* absolute x           */
    ay,     /* absolute y           */
    ind,    /* absolute indirect    */

    r,      /* relative             */
    zr,     /* zero page relative   */
    ac,     /* Accumulator          */
    max_addressing_mode
} AddressingModes;

typedef struct op
{
    std::string opcode;
    AddressingModes mode;
} Op;

int ModeSizes[max_addressing_mode] =
{
    1, 2, 2, 2, 2, 2, 2, 2,
    3, 3, 3, 3, 3, 2, 2, 1    
};

Op* Ops[] =
{
    new Op {"brk", AddressingModes::i},
    new Op {"ora", zpix},
    nullptr,
    nullptr,
    nullptr,
    new Op {"ora", zp},
    new Op {"asl", zp},
    nullptr,
    new Op {"php", i},
    new Op {"ora", im},
    new Op {"asl", i},
    nullptr,
    nullptr,
    new Op {"ora", a},
    new Op {"asl", a},
    nullptr,
    new Op {"bpl", r},
    new Op {"ora", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"ora", zpx},
    new Op {"asl", zpx},
    nullptr,
    new Op {"clc", i},
    new Op {"ora", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"ora", ax},
    new Op {"asl", ax},
    nullptr,
    new Op {"jsr", a},
    new Op {"and", zpix},
    nullptr,
    nullptr,
    new Op {"bit", zp},
    new Op {"and", zp},
    new Op {"rol", zp},
    nullptr,
    new Op {"plp", i},
    new Op {"and", im},
    new Op {"rol", i},
    nullptr,
    new Op {"bit", a},
    new Op {"and", a},
    new Op {"rol", a},
    nullptr,
    new Op {"bmi", r},
    new Op {"and", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"and", zpx},
    new Op {"rol", zpx},
    nullptr,
    new Op {"sec", i},
    new Op {"and", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"and", ax},
    new Op {"rol", ax},
    nullptr,
    new Op {"rti", i},
    new Op {"eor", zpix},
    nullptr,
    nullptr,
    nullptr,
    new Op {"eor", zp},
    new Op {"lsr", zp},
    nullptr,
    new Op {"pha", i},
    new Op {"eor", im},
    new Op {"lsr", i},
    nullptr,
    new Op {"jmp", a},
    new Op {"eor", a},
    new Op {"lsr", a},
    nullptr,
    new Op {"bvc", r},
    new Op {"eor", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"eor", zpx},
    new Op {"lsr", zpx},
    nullptr,
    new Op {"cli", i},
    new Op {"eor", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"eor", ax},
    new Op {"lsr", ax},
    nullptr,
    new Op {"rts", i},
    new Op {"adc", zpix},
    nullptr,
    nullptr,
    nullptr,
    new Op {"adc", zp},
    new Op {"ror", zp},
    nullptr,
    new Op {"pla", i},
    new Op {"adc", im},
    new Op {"ror", i},
    nullptr,
    new Op {"jmp", ind},
    new Op {"adc", a},
    new Op {"ror", a},
    nullptr,
    new Op {"bvs", r},
    new Op {"adc", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"adc", zpx},
    new Op {"ror", zpx},
    nullptr,
    new Op {"sei", i},
    new Op {"adc", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"adc", ax},
    new Op {"ror", ax},
    nullptr,
    nullptr,
    new Op {"sta", zpix},
    nullptr,
    nullptr,
    new Op {"sty", zp},
    new Op {"sta", zp},
    new Op {"stx", zp},
    nullptr,
    new Op {"dey", i},
    nullptr,
    new Op {"txa", i},
    nullptr,
    new Op {"sty", a},
    new Op {"sta", a},
    new Op {"stx", a},
    nullptr,
    new Op {"bcc", r},
    new Op {"sta", zpiy},
    nullptr,
    nullptr,
    new Op {"sty", zpx},
    new Op {"sta", zpx},
    new Op {"stx", zpy},
    nullptr,
    new Op {"tya", i},
    new Op {"sta", ay},
    new Op {"txs", i},
    nullptr,
    nullptr,
    new Op {"sta", ax},
    nullptr,
    nullptr,
    new Op {"ldy", im},
    new Op {"lda", zpix},
    new Op {"ldx", im},
    nullptr,
    new Op {"ldy", zp},
    new Op {"lda", zp},
    new Op {"ldx", zp},
    nullptr,
    new Op {"tay", i},
    new Op {"lda", im},
    new Op {"tax", i},
    nullptr,
    new Op {"ldy", a},
    new Op {"lda", a},
    new Op {"ldx", a},
    nullptr,
    new Op {"bcs", r},
    new Op {"lda", zpiy},
    nullptr,
    nullptr,
    new Op {"ldy", zpx},
    new Op {"lda", zpx},
    new Op {"ldx", zpy},
    nullptr,
    new Op {"clv", i},
    new Op {"lda", ay},
    new Op {"tsx", i},
    nullptr,
    new Op {"ldy", ax},
    new Op {"lda", ax},
    new Op {"ldx", ay},
    nullptr,
    new Op {"cpy", im},
    new Op {"cmp", zpix},
    nullptr,
    nullptr,
    new Op {"cpy", zp},
    new Op {"cmp", zp},
    new Op {"dec", zp},
    nullptr,
    new Op {"iny", i},
    new Op {"cmp", im},
    new Op {"dex", i},
    nullptr,
    new Op {"cpy", a},
    new Op {"cmp", a},
    new Op {"dec", a},
    nullptr,
    new Op {"bne", r},
    new Op {"cmp", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"cmp", zpx},
    new Op {"dec", zpx},
    nullptr,
    new Op {"cld", i},
    new Op {"cmp", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"cmp", ax},
    new Op {"dec", ax},
    nullptr,
    new Op {"cpx", im},
    new Op {"sbc", zpix},
    nullptr,
    nullptr,
    new Op {"cpx", zp},
    new Op {"sbc", zp},
    new Op {"inc", zp},
    nullptr,
    new Op {"inx", i},
    new Op {"sbc", im},
    new Op {"nop", i},
    nullptr,
    new Op {"cpx", a},
    new Op {"sbc", a},
    new Op {"inc", a},
    nullptr,
    new Op {"beq", r},
    new Op {"sbc", zpiy},
    nullptr,
    nullptr,
    nullptr,
    new Op {"sbc", zpx},
    new Op {"inc", zpx},
    nullptr,
    new Op {"sed", i},
    new Op {"sbc", ay},
    nullptr,
    nullptr,
    nullptr,
    new Op {"sbc", ax},
    new Op {"inc", ax},
    nullptr,
};

std::vector<unsigned char> ReadFile(char* name)
{
    std::ifstream input(name, std::ios::binary);
    if (!input.is_open())
    {
        std::cout << "Unable to open " << name << std::endl;
        exit(1);
    }
    // copies all data into buffer
    std::vector<unsigned char> buffer(std::istreambuf_iterator<char>(input), {});
    input.close();
    return buffer;
}

const int MaxErrors = 25;

char* GetNameBase(char* name)
{
    char* i = name;
    char* dirSep = nullptr;
    while (*i)
    {
        if (*i == '\\' || *i == '/')
            dirSep = i;
        ++i;
    }

    if (dirSep)
        return dirSep + 1;

    return name;
}

void DumpHex(const unsigned char b)
{
    std::cout << std::uppercase << std::hex << std::setfill('0') << std::setw(2) << static_cast<int>(b);
}

int GetSize(const AddressingModes mode)
{
    return ModeSizes[mode];
}

void DumpInstruction(Op* op, const int addr, std::vector<unsigned char>&a, const unsigned i, const int sz)
{
    std::cout << "$" << std::uppercase << std::setfill('0') << std::setw(4) << std::hex << addr + i - 2 << ":  ";

    if (i + sz >= a.size())
    {
        for (auto iii = 0; iii + i < a.size(); ++iii)
        {
            DumpHex(a[i + iii]);
            std::cout << ' ';
        }
        return;
    }

    int col = 0;
    // ReSharper disable once CppTooWideScope
    int target;
    signed char d;
    col += 5;
    for (auto iii = 0; iii < sz; ++iii)
    {
        DumpHex(a[i + iii]);
        std::cout << ' ';
        col += 3;
    }
    while (col < 20)
    {
        std::cout << ' ';
        ++col;
    }

    for (auto ch : op->opcode)
        std::cout << static_cast<char>(toupper(ch));

    std::cout << ' ';

    switch (op->mode)
    {
    case AddressingModes::i:
        break;

    case im:
        std::cout << "#$";
        DumpHex(a[i + 1]);
        break;

    case zp:
        std::cout << "$";
        DumpHex(a[i + 1]);
        break;

    case zpi:
        std::cout << "($";
        DumpHex(a[i + 1]);
        std::cout << ")";
        break;

    case zpx:
        std::cout << "$";
        DumpHex(a[i + 1]);
        std::cout << ",x";
        break;

    case zpy:
        std::cout << "$";
        DumpHex(a[i + 1]);
        std::cout << ",y";
        break;

    case zpix:
        std::cout << "($";
        DumpHex(a[i + 1]);
        std::cout << ",x)";
        break;

    case zpiy:
        std::cout << "($";
        DumpHex(a[i + 1]);
        std::cout << "),y";
        break;

    case AddressingModes::a:
        std::cout << "$";
        DumpHex(a[i + 2]);
        DumpHex(a[i + 1]);
        break;

    case aix:
        std::cout << "($";
        DumpHex(a[i + 2]);
        DumpHex(a[i + 1]);
        std::cout << ",x)";
        break;

    case ax:
        std::cout << "$";
        DumpHex(a[i + 2]);
        DumpHex(a[i + 1]);
        std::cout << ",x";
        break;

    case ay:
        std::cout << "$";
        DumpHex(a[i + 2]);
        DumpHex(a[i + 1]);
        std::cout << ",y";
        break;

    case ind:
        std::cout << "($";
        DumpHex(a[i + 2]);
        DumpHex(a[i + 1]);
        std::cout << ")";
        break;

    case r:
        d = static_cast<signed char>(a[i]);
        target = addr + 2 + d;
        std::cout << "$";
        DumpHex(target & 0x00FF);
        DumpHex(target & 0xFF00 >> 8);
        break;

    case zr: 
        d = static_cast<signed char>(a[i]);
        target = addr + 2 + d;
        std::cout << "$";
        DumpHex(target & 0x00FF);
        DumpHex(target & 0xFF00 >> 8);
        break;

    case ac:
        break;

    case max_addressing_mode:
        break;
    default:;
    }
    std::cout << std::endl;
}

int main(const int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Usage: HexCompare file1 file2" << std::endl;
        exit(1);
    }

    std::vector<unsigned char> a = ReadFile(argv[1]);
    std::vector<unsigned char> b = ReadFile(argv[2]);
    std::cout << 
        "A " << GetNameBase(argv[1]) << std::endl <<
        "B " << GetNameBase(argv[2]) << std::endl;

    const size_t last = std::min(a.size(), b.size());

    int errorCount = 0;

    const auto startA = a[0] + a[1] * 256;
    const auto startB = b[0] + b[1] * 256;

    unsigned ia = 2;
    unsigned ib = 2;
    while (errorCount  < MaxErrors && ia < last && ib < last)
    {
        Op* opa = Ops[a[ia]];
        Op* opb = Ops[b[ib]];

        int sza = opa ? GetSize(opa->mode) : 1;
        int szb = opb ? GetSize(opb->mode) : 1;

        for (auto ii = 0; ii < std::min(sza, szb); ++ii)
        {
            if (a[ia + ii] != b[ib + ii])
            {
                ++errorCount;
                
                if (opa)
                {
                    DumpInstruction(opa, startA, a, ia, sza);
                }
                else if (static_cast<int>(ia) + 1 < sza)
                {
                    std::cout << "$";
                    DumpHex(a[ia + 1]);
                    std::cout << std::endl;
                }

                if (opb)
                {
                    DumpInstruction(opb, startB, b, ib, szb);
                }
                else if (static_cast<int>(ib) + 1 < szb)
                {
                    std::cout << "$";
                    DumpHex(b[ia + 1]);
                    std::cout << std::endl;
                }

                std::cout << std::endl;
                break;
            }
        }
        ia += sza;
        ib += szb;
    }
}

