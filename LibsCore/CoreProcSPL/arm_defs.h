#ifndef __ARM_DEFS_H__
#define __ARM_DEFS_H__

#define WORD(a)        * ( (unsigned int   *) ( a ) )
#define HWRD(a)        * ( (unsigned short *) ( a ) )
#define BYTE(a)        * ( (unsigned char  *) ( a ) )

#define INS_BIT(i,b)           ( ( i >> b )&1 )
#define I32_FIELD(i,b,e)       ( ( ( i << ( 31 - b ) ) >> 31 - b ) >> ( e ) )
#define I32_FIELD_FAST(i,e,m)  ( ( i >> e ) & m )
#define IARM_COND(i)           ( ( i >> 28 )&0xF )

#define IARM_Rn(i)          ( ( i >> 16 )&0xF )
#define IARM_Rd(i)          ( ( i >> 12 )&0xF )
#define IARM_Rs(i)          ( ( i >>  8 )&0xF )
#define IARM_Rm(i)          ( ( i >>  0 )&0xF )

#define IARM_ImmHi(i)       ( ( i >> 16 )&0xF )
#define IARM_ImmLo(i)       ( ( i >>  0 )&0xF )
#define IARM_Imm12(i)       ( ( i >>  0 )&0xFFF )

#define IARM_ShiftImm(i)    I32_FIELD_FAST(i,7,0x1F)
#define IARM_Shift(i)       I32_FIELD_FAST(i,5,3)

#define IARM_Shift_LSL      0
#define IARM_Shift_LSR      1

#define PC_ALIGN(pc)        (pc & 0xFFFFFFFE)

#define MAX_REGS   17

#define _R0        0
#define _R1        1
#define _R2        2
#define _R3        3
#define _R4        4
#define _R5        5
#define _R6        6
#define _R7        7
#define _R8        8
#define _R9        9
#define _R10       10
#define _R11       11
#define _R12       12
#define _SP        13
#define _LR        14
#define _PC        15
#define _CPSR      16

#define GET_PSR_N(cpsr)    ((cpsr >> 31)&1)
#define GET_PSR_Z(cpsr)    ((cpsr >> 30)&1)
#define GET_PSR_C(cpsr)    ((cpsr >> 29)&1)
#define GET_PSR_V(cpsr)    ((cpsr >> 28)&1)
#define GET_PSR_Q(cpsr)    ((cpsr >> 27)&1)

#define GET_PSR_I(cpsr)    ((cpsr >>  7)&1)
#define GET_PSR_F(cpsr)    ((cpsr >>  6)&1)
#define GET_PSR_T(cpsr)    ((cpsr >>  5)&1)
#define GET_PSR_M(cpsr)    ((cpsr)&0x1F)

#define SET_PSR_T(cpsr, i)  (cpsr |= ( i << 5))

#define MUSR           0x10 // User Mode
#define MFIQ           0x11 // FIQ Mode
#define MIRQ           0x12 // IRQ Mode
#define MSVC           0x13 // Supervisor Mode
#define MABT           0x17 // Abort Mode
#define MUND           0x1B // Undefined Mode
#define MSYS           0x1F // System Mode
#define MMSK           0x1F // Mask Mode

#define CEQ            0 // �����: Z == 1
#define CNE            1 // �� �����: Z == 0
#define CCS            2 // �������: C == 1
#define CHS            2 // ������� ������ ��� �����: C == 1
#define CCC            3 // ��� ��������: C == 0
#define CLO            3 // ����������� ������: C == 0
#define CMI            4 // �����/�������������: N == 1
#define CPL            5 // ����/������������� ��� ����: N == 0
#define CVS            6 // ������������: V == 1
#define CVC            7 // ��� ������������: V == 0
#define CHI            8 // ����������� ������: C == 1 && Z == 0
#define CLS            9 // ����������� ������ ��� �����: C == 0 && Z == 1
#define CGE           10 // ������ ��� �����, �� ������: N == V
#define CLT           11 // ������ ���, �� ������: N != V
#define CGT           12 // ������ ���, �� ������: Z == 0 && N == V
#define CLE           13 // ������ ��� �����, �� ������: Z == 1 && N != V
#define CAL           14 // ����������� ����������
#define CMSK          15 // ����� �������


//LDR / STR
#define IARM_IS_LDR(i)  \
  ( I32_FIELD_FAST(i,26,3)==1 && INS_BIT(i,22)==0 && INS_BIT(i,20)==1 )
#define IARM_IS_STR(i)  \
  ( I32_FIELD_FAST(i,26,3)==1 && INS_BIT(i,22)==0 && INS_BIT(i,20)==0 )

#define IARM_LDR_I(i)       INS_BIT(i,25)
#define IARM_LDR_P(i)       INS_BIT(i,24)
#define IARM_LDR_U(i)       INS_BIT(i,23)
#define IARM_LDR_W(i)       INS_BIT(i,21)



//if Load and Store word or unsigned byte instructions
#define IARM_IS_LDRHS(i)    ( (i >> 25)&7 == 0 && (i >> 7)&1 == 1 && (i >> 4)&1 == 1 )
#define IARM_LDRHS_P(i)     INS_BIT(i,24)
#define IARM_LDRHS_U(i)     INS_BIT(i,23)
#define IARM_LDRHS_I(i)     INS_BIT(i,22) // 
#define IARM_LDRHS_W(i)     INS_BIT(i,21)
#define IARM_LDRHS_L(i)     INS_BIT(i,20)
#define IARM_LDRHS_S(i)     INS_BIT(i, 6)
#define IARM_LDRHS_H(i)     INS_BIT(i, 5)




#endif // __ARM_DEFS_H__


