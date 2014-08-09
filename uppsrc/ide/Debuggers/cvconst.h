/*
 * File cvconst.h - MS debug information
 *
 * Copyright (C) 2004, Eric Pouech
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/* information in this file is highly derivated from MSDN DIA information pages */

/* symbols & types enumeration */
enum SymTagEnum
{
   SymTagNull,
   SymTagExe,
   SymTagCompiland,
   SymTagCompilandDetails,
   SymTagCompilandEnv,
   SymTagFunction,
   SymTagBlock,
   SymTagData,
   SymTagAnnotation,
   SymTagLabel,
   SymTagPublicSymbol,
   SymTagUDT,
   SymTagEnum,
   SymTagFunctionType,
   SymTagPointerType,
   SymTagArrayType,
   SymTagBaseType,
   SymTagTypedef,
   SymTagBaseClass,
   SymTagFriend,
   SymTagFunctionArgType,
   SymTagFuncDebugStart,
   SymTagFuncDebugEnd,
   SymTagUsingNamespace,
   SymTagVTableShape,
   SymTagVTable,
   SymTagCustom,
   SymTagThunk,
   SymTagCustomType,
   SymTagManagedType,
   SymTagDimension,
   SymTagMax
};

enum BasicType
{
    btNoType = 0,
    btVoid = 1,
    btChar = 2,
    btWChar = 3,
    btInt = 6,
    btUInt = 7,
    btFloat = 8,
    btBCD = 9,
    btBool = 10,
    btLong = 13,
    btULong = 14,
    btCurrency = 25,
    btDate = 26,
    btVariant = 27,
    btComplex = 28,
    btBit = 29,
    btBSTR = 30,
    btHresult = 31,
};

/* kind of UDT */
enum UdtKind
{
    UdtStruct,
    UdtClass,
    UdtUnion
};

/* where a SymTagData is */
enum LocationType
{
    LocIsNull,
    LocIsStatic,
    LocIsTLS,
    LocIsRegRel,
    LocIsThisRel,
    LocIsEnregistered,
    LocIsBitField,
    LocIsSlot,
    LocIsIlRel,
    LocInMetaData,
    LocIsConstant
};

/* kind of SymTagData */
enum DataKind
{
    DataIsUnknown,
    DataIsLocal,
    DataIsStaticLocal,
    DataIsParam,
    DataIsObjectPtr,
    DataIsFileStatic,
    DataIsGlobal,
    DataIsMember,
    DataIsStaticMember,
    DataIsConstant
};

/* values for registers (on different CPUs) */
enum CV_HREG_e
{
    /* those values are common to all supported CPUs (and CPU independant) */
    CV_ALLREG_ERR       = 30000,
    CV_ALLREG_TEB       = 30001,
    CV_ALLREG_TIMER     = 30002,
    CV_ALLREG_EFAD1     = 30003,
    CV_ALLREG_EFAD2     = 30004,
    CV_ALLREG_EFAD3     = 30005,
    CV_ALLREG_VFRAME    = 30006,
    CV_ALLREG_HANDLE    = 30007,
    CV_ALLREG_PARAMS    = 30008,
    CV_ALLREG_LOCALS    = 30009,

    /* Intel x86 CPU */
    CV_REG_NONE         = 0,
    CV_REG_AL           = 1,
    CV_REG_CL           = 2,
    CV_REG_DL           = 3,
    CV_REG_BL           = 4,
    CV_REG_AH           = 5,
    CV_REG_CH           = 6,
    CV_REG_DH           = 7,
    CV_REG_BH           = 8,
    CV_REG_AX           = 9,
    CV_REG_CX           = 10,
    CV_REG_DX           = 11,
    CV_REG_BX           = 12,
    CV_REG_SP           = 13,
    CV_REG_BP           = 14,
    CV_REG_SI           = 15,
    CV_REG_DI           = 16,
    CV_REG_EAX          = 17,
    CV_REG_ECX          = 18,
    CV_REG_EDX          = 19,
    CV_REG_EBX          = 20,
    CV_REG_ESP          = 21,
    CV_REG_EBP          = 22,
    CV_REG_ESI          = 23,
    CV_REG_EDI          = 24,
    CV_REG_ES           = 25,
    CV_REG_CS           = 26,
    CV_REG_SS           = 27,
    CV_REG_DS           = 28,
    CV_REG_FS           = 29,
    CV_REG_GS           = 30,
    CV_REG_IP           = 31,
    CV_REG_FLAGS        = 32,
    CV_REG_EIP          = 33,
    CV_REG_EFLAGS       = 34,

    /* <pcode> */
    CV_REG_TEMP         = 40,
    CV_REG_TEMPH        = 41,
    CV_REG_QUOTE        = 42,
    CV_REG_PCDR3        = 43,   /* this includes PCDR4 to PCDR7 */
    CV_REG_CR0          = 80,   /* this includes CR1 to CR4 */
    CV_REG_DR0          = 90,   /* this includes DR1 to DR7 */
    /* </pcode> */

    CV_REG_GDTR         = 110,
    CV_REG_GDTL         = 111,
    CV_REG_IDTR         = 112,
    CV_REG_IDTL         = 113,
    CV_REG_LDTR         = 114,
    CV_REG_TR           = 115,

    CV_REG_PSEUDO1      = 116, /* this includes Pseudo02 to Pseuso09 */
    CV_REG_ST0          = 128, /* this includes ST1 to ST7 */
    CV_REG_CTRL         = 136,
    CV_REG_STAT         = 137,
    CV_REG_TAG          = 138,
    CV_REG_FPIP         = 139,
    CV_REG_FPCS         = 140,
    CV_REG_FPDO         = 141,
    CV_REG_FPDS         = 142,
    CV_REG_ISEM         = 143,
    CV_REG_FPEIP        = 144,
    CV_REG_FPEDO        = 145,
    CV_REG_MM0          = 146, /* this includes MM1 to MM7 */
    CV_REG_XMM0         = 154, /* this includes XMM1 to XMM7 */
    CV_REG_XMM00        = 162,
    CV_REG_XMM0L        = 194, /* this includes XMM1L to XMM7L */
    CV_REG_XMM0H        = 202, /* this includes XMM1H to XMM7H */
    CV_REG_MXCSR        = 211,
    CV_REG_EDXEAX       = 212,
    CV_REG_EMM0L        = 220,
    CV_REG_EMM0H        = 228,
    CV_REG_MM00         = 236,
    CV_REG_MM01         = 237,
    CV_REG_MM10         = 238,
    CV_REG_MM11         = 239,
    CV_REG_MM20         = 240,
    CV_REG_MM21         = 241,
    CV_REG_MM30         = 242,
    CV_REG_MM31         = 243,
    CV_REG_MM40         = 244,
    CV_REG_MM41         = 245,
    CV_REG_MM50         = 246,
    CV_REG_MM51         = 247,
    CV_REG_MM60         = 248,
    CV_REG_MM61         = 249,
    CV_REG_MM70         = 250,
    CV_REG_MM71         = 251,

    /* Motorola 68K CPU */
    CV_R68_D0           = 0, /* this includes D1 to D7 too */
    CV_R68_A0           = 8, /* this includes A1 to A7 too */
    CV_R68_CCR          = 16,
    CV_R68_SR           = 17,
    CV_R68_USP          = 18,
    CV_R68_MSP          = 19,
    CV_R68_SFC          = 20,
    CV_R68_DFC          = 21,
    CV_R68_CACR         = 22,
    CV_R68_VBR          = 23,
    CV_R68_CAAR         = 24,
    CV_R68_ISP          = 25,
    CV_R68_PC           = 26,
    CV_R68_FPCR         = 28,
    CV_R68_FPSR         = 29,
    CV_R68_FPIAR        = 30,
    CV_R68_FP0          = 32, /* this includes FP1 to FP7 */
    CV_R68_MMUSR030     = 41,
    CV_R68_MMUSR        = 42,
    CV_R68_URP          = 43,
    CV_R68_DTT0         = 44,
    CV_R68_DTT1         = 45,
    CV_R68_ITT0         = 46,
    CV_R68_ITT1         = 47,
    CV_R68_PSR          = 51,
    CV_R68_PCSR         = 52,
    CV_R68_VAL          = 53,
    CV_R68_CRP          = 54,
    CV_R68_SRP          = 55,
    CV_R68_DRP          = 56,
    CV_R68_TC           = 57,
    CV_R68_AC           = 58,
    CV_R68_SCC          = 59,
    CV_R68_CAL          = 60,
    CV_R68_TT0          = 61,
    CV_R68_TT1          = 62,
    CV_R68_BAD0         = 64, /* this includes BAD1 to BAD7 */
    CV_R68_BAC0         = 72, /* this includes BAC1 to BAC7 */

    /* MIPS 4000 CPU */
    CV_M4_NOREG         = CV_REG_NONE,
    CV_M4_IntZERO       = 10,
    CV_M4_IntAT         = 11,
    CV_M4_IntV0         = 12,
    CV_M4_IntV1         = 13,
    CV_M4_IntA0         = 14, /* this includes IntA1 to IntA3 */
    CV_M4_IntT0         = 18, /* this includes IntT1 to IntT7 */
    CV_M4_IntS0         = 26, /* this includes IntS1 to IntS7 */
    CV_M4_IntT8         = 34,
    CV_M4_IntT9         = 35,
    CV_M4_IntKT0        = 36,
    CV_M4_IntKT1        = 37,
    CV_M4_IntGP         = 38,
    CV_M4_IntSP         = 39,
    CV_M4_IntS8         = 40,
    CV_M4_IntRA         = 41,
    CV_M4_IntLO         = 42,
    CV_M4_IntHI         = 43,
    CV_M4_Fir           = 50,
    CV_M4_Psr           = 51,
    CV_M4_FltF0         = 60, /* this includes FltF1 to Flt31 */
    CV_M4_FltFsr        = 92,

    /* Alpha AXP CPU */
    CV_ALPHA_NOREG      = CV_REG_NONE,
    CV_ALPHA_FltF0      = 10, /* this includes FltF1 to FltF31 */
    CV_ALPHA_IntV0      = 42,
    CV_ALPHA_IntT0      = 43, /* this includes T1 to T7 */
    CV_ALPHA_IntS0      = 51, /* this includes S1 to S5 */
    CV_ALPHA_IntFP      = 57,
    CV_ALPHA_IntA0      = 58, /* this includes A1 to A5 */
    CV_ALPHA_IntT8      = 64,
    CV_ALPHA_IntT9      = 65,
    CV_ALPHA_IntT10     = 66,
    CV_ALPHA_IntT11     = 67,
    CV_ALPHA_IntRA      = 68,
    CV_ALPHA_IntT12     = 69,
    CV_ALPHA_IntAT      = 70,
    CV_ALPHA_IntGP      = 71,
    CV_ALPHA_IntSP      = 72,
    CV_ALPHA_IntZERO    = 73,
    CV_ALPHA_Fpcr       = 74,
    CV_ALPHA_Fir        = 75,
    CV_ALPHA_Psr        = 76,
    CV_ALPHA_FltFsr     = 77,
    CV_ALPHA_SoftFpcr   = 78,

    /* Motorola & IBM PowerPC CPU */
    CV_PPC_GPR0         = 1, /* this includes GPR1 to GPR31 */
    CV_PPC_CR           = 33,
    CV_PPC_CR0          = 34, /* this includes CR1 to CR7 */
    CV_PPC_FPR0         = 42, /* this includes FPR1 to FPR31 */

    CV_PPC_FPSCR        = 74,
    CV_PPC_MSR          = 75,
    CV_PPC_SR0          = 76, /* this includes SR1 to SR15 */
    /* some PPC registers missing */

    /* Hitachi SH3 CPU */
    CV_SH3_NOREG        = CV_REG_NONE,
    CV_SH3_IntR0        = 10, /* this include R1 to R13 */
    CV_SH3_IntFp        = 24,
    CV_SH3_IntSp        = 25,
    CV_SH3_Gbr          = 38,
    CV_SH3_Pr           = 39,
    CV_SH3_Mach         = 40,
    CV_SH3_Macl         = 41,
    CV_SH3_Pc           = 50,
    CV_SH3_Sr           = 51,
    CV_SH3_BarA         = 60,
    CV_SH3_BasrA        = 61,
    CV_SH3_BamrA        = 62,
    CV_SH3_BbrA         = 63,
    CV_SH3_BarB         = 64,
    CV_SH3_BasrB        = 65,
    CV_SH3_BamrB        = 66,
    CV_SH3_BbrB         = 67,
    CV_SH3_BdrB         = 68,
    CV_SH3_BdmrB        = 69,
    CV_SH3_Brcr         = 70,
    CV_SH_Fpscr         = 75,
    CV_SH_Fpul          = 76,
    CV_SH_FpR0          = 80, /* this includes FpR1 to FpR15 */
    CV_SH_XFpR0         = 96, /* this includes XFpR1 to XXFpR15 */

    /* ARM CPU */
    CV_ARM_NOREG        = CV_REG_NONE,
    CV_ARM_R0           = 10, /* this includes R1 to R12 */
    CV_ARM_SP           = 23,
    CV_ARM_LR           = 24,
    CV_ARM_PC           = 25,
    CV_ARM_CPSR         = 26,

    /* Intel IA64 CPU */
    CV_IA64_NOREG       = CV_REG_NONE,
    CV_IA64_Br0         = 512, /* this includes Br1 to Br7 */
    CV_IA64_P0          = 704, /* this includes P1 to P63 */
    CV_IA64_Preds       = 768,
    CV_IA64_IntH0       = 832, /* this includes H1 to H15 */
    CV_IA64_Ip          = 1016,
    CV_IA64_Umask       = 1017,
    CV_IA64_Cfm         = 1018,
    CV_IA64_Psr         = 1019,
    CV_IA64_Nats        = 1020,
    CV_IA64_Nats2       = 1021,
    CV_IA64_Nats3       = 1022,
    CV_IA64_IntR0       = 1024, /* this includes R1 to R127 */
    CV_IA64_FltF0       = 2048, /* this includes FltF1 to FltF127 */
    /* some IA64 registers missing */

    /* TriCore CPU */
    CV_TRI_NOREG        = CV_REG_NONE,
    CV_TRI_D0           = 10, /* includes D1 to D15 */
    CV_TRI_A0           = 26, /* includes A1 to A15 */
    CV_TRI_E0           = 42,
    CV_TRI_E2           = 43,
    CV_TRI_E4           = 44,
    CV_TRI_E6           = 45,
    CV_TRI_E8           = 46,
    CV_TRI_E10          = 47,
    CV_TRI_E12          = 48,
    CV_TRI_E14          = 49,
    CV_TRI_EA0          = 50,
    CV_TRI_EA2          = 51,
    CV_TRI_EA4          = 52,
    CV_TRI_EA6          = 53,
    CV_TRI_EA8          = 54,
    CV_TRI_EA10         = 55,
    CV_TRI_EA12         = 56,
    CV_TRI_EA14         = 57,
    /* some TriCode registers missing */

    /* AM33 (and the likes) CPU */
    CV_AM33_NOREG       = CV_REG_NONE,
    CV_AM33_E0          = 10, /* this includes E1 to E7 */
    CV_AM33_A0          = 20, /* this includes A1 to A3 */
    CV_AM33_D0          = 30, /* this includes D1 to D3 */
    CV_AM33_FS0         = 40, /* this includes FS1 to FS31 */

    /* Mitsubishi M32R CPU */
    CV_M32R_NOREG       = CV_REG_NONE,
    CV_M32R_R0          = 10, /* this includes R1 to R11 */
    CV_M32R_R12         = 22,
    CV_M32R_R13         = 23,
    CV_M32R_R14         = 24,
    CV_M32R_R15         = 25,
    CV_M32R_PSW         = 26,
    CV_M32R_CBR         = 27,
    CV_M32R_SPI         = 28,
    CV_M32R_SPU         = 29,
    CV_M32R_SPO         = 30,
    CV_M32R_BPC         = 31,
    CV_M32R_ACHI        = 32,
    CV_M32R_ACLO        = 33,
    CV_M32R_PC          = 34,
    
    // AMD64
	CV_AMD64_NONE       = CV_REG_NONE,
	CV_AMD64_AL         = CV_REG_AL,
	CV_AMD64_CL         = CV_REG_CL,
	CV_AMD64_DL         = CV_REG_DL,
	CV_AMD64_BL         = CV_REG_BL,
	CV_AMD64_AH         = CV_REG_AH,
	CV_AMD64_CH         = CV_REG_CH,
	CV_AMD64_DH         = CV_REG_DH,
	CV_AMD64_BH         = CV_REG_BH,
	CV_AMD64_AX         = CV_REG_AX,
	CV_AMD64_CX         = CV_REG_CX,
	CV_AMD64_DX         = CV_REG_DX,
	CV_AMD64_BX         = CV_REG_BX,
	CV_AMD64_SP         = CV_REG_SP,
	CV_AMD64_BP         = CV_REG_BP,
	CV_AMD64_SI         = CV_REG_SI,
	CV_AMD64_DI         = CV_REG_DI,
	CV_AMD64_EAX        = CV_REG_EAX,
	CV_AMD64_ECX        = CV_REG_ECX,
	CV_AMD64_EDX        = CV_REG_EDX,
	CV_AMD64_EBX        = CV_REG_EBX,
	CV_AMD64_ESP        = CV_REG_ESP,
	CV_AMD64_EBP        = CV_REG_EBP,
	CV_AMD64_ESI        = CV_REG_ESI,
	CV_AMD64_EDI        = CV_REG_EDI,
	CV_AMD64_ES         = CV_REG_ES,
	CV_AMD64_CS         = CV_REG_CS,
	CV_AMD64_SS         = CV_REG_SS,
	CV_AMD64_DS         = CV_REG_DS,
	CV_AMD64_FS         = CV_REG_FS,
	CV_AMD64_GS         = CV_REG_GS,
	CV_AMD64_FLAGS      = CV_REG_FLAGS,
	CV_AMD64_RIP        = CV_REG_EIP,
	CV_AMD64_EFLAGS     = CV_REG_EFLAGS,
		
	/* <pcode> */
	CV_AMD64_TEMP       = CV_REG_TEMP,
	CV_AMD64_TEMPH      = CV_REG_TEMPH,
	CV_AMD64_QUOTE      = CV_REG_QUOTE,
	CV_AMD64_PCDR3      = CV_REG_PCDR3, /* this includes PCDR4 to PCDR7 */
	CV_AMD64_CR0        = CV_REG_CR0,   /* this includes CR1 to CR4 */
	CV_AMD64_DR0        = CV_REG_DR0,   /* this includes DR1 to DR7 */
	/* </pcode> */
		
	CV_AMD64_GDTR       = CV_REG_GDTR,
	CV_AMD64_GDTL       = CV_REG_GDTL,
	CV_AMD64_IDTR       = CV_REG_IDTR,
	CV_AMD64_IDTL       = CV_REG_IDTL,
	CV_AMD64_LDTR       = CV_REG_LDTR,
	CV_AMD64_TR         = CV_REG_TR,
		
	CV_AMD64_PSEUDO1    = CV_REG_PSEUDO1, /* this includes Pseudo02 to Pseuso09 */
	CV_AMD64_ST0        = CV_REG_ST0,     /* this includes ST1 to ST7 */
	CV_AMD64_CTRL       = CV_REG_CTRL,
	CV_AMD64_STAT       = CV_REG_STAT,
	CV_AMD64_TAG        = CV_REG_TAG,
	CV_AMD64_FPIP       = CV_REG_FPIP,
	CV_AMD64_FPCS       = CV_REG_FPCS,
	CV_AMD64_FPDO       = CV_REG_FPDO,
	CV_AMD64_FPDS       = CV_REG_FPDS,
	CV_AMD64_ISEM       = CV_REG_ISEM,
	CV_AMD64_FPEIP      = CV_REG_FPEIP,
	CV_AMD64_FPEDO      = CV_REG_FPEDO,
	CV_AMD64_MM0        = CV_REG_MM0,     /* this includes MM1 to MM7 */
	CV_AMD64_XMM0       = CV_REG_XMM0,    /* this includes XMM1 to XMM7 */
	CV_AMD64_XMM00      = CV_REG_XMM00,
	CV_AMD64_XMM0L      = CV_REG_XMM0L,   /* this includes XMM1L to XMM7L */
	CV_AMD64_XMM0H      = CV_REG_XMM0H,   /* this includes XMM1H to XMM7H */
	CV_AMD64_MXCSR      = CV_REG_MXCSR,
	CV_AMD64_EDXEAX     = CV_REG_EDXEAX,
	CV_AMD64_EMM0L      = CV_REG_EMM0L,
	CV_AMD64_EMM0H      = CV_REG_EMM0H,
	CV_AMD64_MM00       = CV_REG_MM00,
	CV_AMD64_MM01       = CV_REG_MM01,
	CV_AMD64_MM10       = CV_REG_MM10,
	CV_AMD64_MM11       = CV_REG_MM11,
	CV_AMD64_MM20       = CV_REG_MM20,
	CV_AMD64_MM21       = CV_REG_MM21,
	CV_AMD64_MM30       = CV_REG_MM30,
	CV_AMD64_MM31       = CV_REG_MM31,
	CV_AMD64_MM40       = CV_REG_MM40,
	CV_AMD64_MM41       = CV_REG_MM41,
	CV_AMD64_MM50       = CV_REG_MM50,
	CV_AMD64_MM51       = CV_REG_MM51,
	CV_AMD64_MM60       = CV_REG_MM60,
	CV_AMD64_MM61       = CV_REG_MM61,
	CV_AMD64_MM70       = CV_REG_MM70,
	CV_AMD64_MM71       = CV_REG_MM71,
		
	CV_AMD64_RAX        = 328,
	CV_AMD64_RBX        = 329,
	CV_AMD64_RCX        = 330,
	CV_AMD64_RDX        = 331,
	CV_AMD64_RSI        = 332,
	CV_AMD64_RDI        = 333,
	CV_AMD64_RBP        = 334,
	CV_AMD64_RSP        = 335,
		
	CV_AMD64_R8         = 336,
	CV_AMD64_R9         = 337,
	CV_AMD64_R10        = 338,
	CV_AMD64_R11        = 339,
	CV_AMD64_R12        = 340,
	CV_AMD64_R13        = 341,
	CV_AMD64_R14        = 342,
	CV_AMD64_R15        = 343,
};

typedef enum
{
   THUNK_ORDINAL_NOTYPE,
   THUNK_ORDINAL_ADJUSTOR,
   THUNK_ORDINAL_VCALL,
   THUNK_ORDINAL_PCODE,
   THUNK_ORDINAL_LOAD
} THUNK_ORDINAL;
