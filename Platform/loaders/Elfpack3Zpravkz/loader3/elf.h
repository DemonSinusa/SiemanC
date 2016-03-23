/*
 * Copyright (c) 1995, 1996, 2001, 2002
 * Erik Theisen.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. The name of the author may not be used to endorse or promote products
 *    derived from this software without specific prior written permission
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * This is the ELF ABI header file
 * formerly known as "elf_abi.h".
 */

#ifndef _ELF_H
#define _ELF_H

//#include "compiler.h"

typedef unsigned long ulong;
typedef unsigned int  uint;


/*
 *  This version doesn't work for 64-bit ABIs - Erik.
 */

/*
 * These typedefs need to be handled better.
 */
typedef unsigned int	Elf32_Addr;	/* Unsigned program address */
typedef unsigned int	Elf32_Off;	/* Unsigned file offset */
typedef int		Elf32_Sword;	/* Signed large integer */
typedef unsigned int	Elf32_Word;	/* Unsigned large integer */
typedef short	        Elf32_Half;	/* Unsigned medium integer */

/* e_ident[] identification indexes */
#define EI_MAG0		0		/* file ID */
#define EI_MAG1		1		/* file ID */
#define EI_MAG2		2		/* file ID */
#define EI_MAG3		3		/* file ID */
#define EI_CLASS	4		/* file class */
#define EI_DATA		5		/* data encoding */
#define EI_VERSION	6		/* ELF header version */
#define EI_OSABI	7		/* OS/ABI specific ELF extensions */
#define EI_ABIVERSION	8		/* ABI target version */
#define EI_PAD		9		/* start of pad bytes */
#define EI_NIDENT	16		/* Size of e_ident[] */

/* e_ident[] magic number */
#define	ELFMAG0		0x7f		/* e_ident[EI_MAG0] */
#define	ELFMAG1		'E'		/* e_ident[EI_MAG1] */
#define	ELFMAG2		'L'		/* e_ident[EI_MAG2] */
#define	ELFMAG3		'F'		/* e_ident[EI_MAG3] */
#define	ELFMAG		"\177ELF"	/* magic */
#define	SELFMAG		4		/* size of magic */

/* e_ident[] file class */
#define	ELFCLASSNONE	0		/* invalid */
#define	ELFCLASS32	1		/* 32-bit objs */
#define	ELFCLASS64	2		/* 64-bit objs */
#define	ELFCLASSNUM	3		/* number of classes */

/* e_ident[] data encoding */
#define ELFDATANONE	0		/* invalid */
#define ELFDATA2LSB	1		/* Little-Endian */
#define ELFDATA2MSB	2		/* Big-Endian */
#define ELFDATANUM	3		/* number of data encode defines */

/* e_ident[] OS/ABI specific ELF extensions */
#define ELFOSABI_NONE		0	/* No extension specified */
#define ELFOSABI_HPUX		1	/* Hewlett-Packard HP-UX */
#define ELFOSABI_NETBSD		2	/* NetBSD */
#define ELFOSABI_LINUX		3	/* Linux */
#define ELFOSABI_SOLARIS	6	/* Sun Solaris */
#define ELFOSABI_AIX		7	/* AIX */
#define ELFOSABI_IRIX		8	/* IRIX */
#define ELFOSABI_FREEBSD	9	/* FreeBSD */
#define ELFOSABI_TRU64		10	/* Compaq TRU64 UNIX */
#define ELFOSABI_MODESTO	11	/* Novell Modesto */
#define ELFOSABI_OPENBSD	12	/* OpenBSD */
/* 64-255 Architecture-specific value range */

/* e_ident[] ABI Version */
#define ELFABIVERSION		0

/* e_ident */
#define IS_ELF(ehdr) ((ehdr)->e_ident[EI_MAG0] == ELFMAG0 && \
		      (ehdr)->e_ident[EI_MAG1] == ELFMAG1 && \
		      (ehdr)->e_ident[EI_MAG2] == ELFMAG2 && \
		      (ehdr)->e_ident[EI_MAG3] == ELFMAG3)

/* ELF Header */
typedef struct elfhdr{
	unsigned char	e_ident[EI_NIDENT]; /* ELF Identification */
	Elf32_Half	e_type;		/* object file type */
	Elf32_Half	e_machine;	/* machine */
	Elf32_Word	e_version;	/* object file version */
	Elf32_Addr	e_entry;	/* virtual entry point */
	Elf32_Off	e_phoff;	/* program header table offset */
	Elf32_Off	e_shoff;	/* section header table offset */
	Elf32_Word	e_flags;	/* processor-specific flags */
	Elf32_Half	e_ehsize;	/* ELF header size */
	Elf32_Half	e_phentsize;	/* program header entry size */
	Elf32_Half	e_phnum;	/* number of program header entries */
	Elf32_Half	e_shentsize;	/* section header entry size */
	Elf32_Half	e_shnum;	/* number of section header entries */
	Elf32_Half	e_shstrndx;	/* section header table's "section
					   header string table" entry offset */
} Elf32_Ehdr;

/* e_type */
#define ET_NONE		0		/* No file type */
#define ET_REL		1		/* relocatable file */
#define ET_EXEC		2		/* executable file */
#define ET_DYN		3		/* shared object file */
#define ET_CORE		4		/* core file */
#define ET_NUM		5		/* number of types */
#define ET_LOOS		0xfe00		/* reserved range for operating */
#define ET_HIOS		0xfeff		/*  system specific e_type */
#define ET_LOPROC	0xff00		/* reserved range for processor */
#define ET_HIPROC	0xffff		/*  specific e_type */

/* e_machine */
#define EM_NONE		0		/* No Machine */
#define EM_M32		1		/* AT&T WE 32100 */
#define EM_SPARC	2		/* SPARC */
#define EM_386		3		/* Intel 80386 */
#define EM_68K		4		/* Motorola 68000 */
#define EM_88K		5		/* Motorola 88000 */
#if 0
#define EM_486		6		/* RESERVED - was Intel 80486 */
#endif
#define EM_860		7		/* Intel 80860 */
#define EM_MIPS		8		/* MIPS R3000 Big-Endian only */
#define EM_S370		9		/* IBM System/370 Processor */
#define EM_MIPS_RS4_BE	10		/* MIPS R4000 Big-Endian */
#if 0
#define EM_SPARC64	11		/* RESERVED - was SPARC v9
					     64-bit unoffical */
#endif
/* RESERVED 11-14 for future use */
#define EM_PARISC	15		/* HPPA */
/* RESERVED 16 for future use */
#define EM_VPP500	17		/* Fujitsu VPP500 */
#define EM_SPARC32PLUS	18		/* Enhanced instruction set SPARC */
#define EM_960		19		/* Intel 80960 */
#define EM_PPC		20		/* PowerPC */
#define EM_PPC64	21		/* 64-bit PowerPC */
#define EM_S390		22		/* IBM System/390 Processor */
/* RESERVED 23-35 for future use */
#define EM_V800		36		/* NEC V800 */
#define EM_FR20		37		/* Fujitsu FR20 */
#define EM_RH32		38		/* TRW RH-32 */
#define EM_RCE		39		/* Motorola RCE */
#define EM_ARM		40		/* Advanced Risc Machines ARM */
#define EM_ALPHA	41		/* Digital Alpha */
#define EM_SH		42		/* Hitachi SH */
#define EM_SPARCV9	43		/* SPARC Version 9 */
#define EM_TRICORE	44		/* Siemens TriCore embedded processor */
#define EM_ARC		45		/* Argonaut RISC Core */
#define EM_H8_300	46		/* Hitachi H8/300 */
#define EM_H8_300H	47		/* Hitachi H8/300H */
#define EM_H8S		48		/* Hitachi H8S */
#define EM_H8_500	49		/* Hitachi H8/500 */
#define EM_IA_64	50		/* Intel Merced */
#define EM_MIPS_X	51		/* Stanford MIPS-X */
#define EM_COLDFIRE	52		/* Motorola Coldfire */
#define EM_68HC12	53		/* Motorola M68HC12 */
#define EM_MMA		54		/* Fujitsu MMA Multimedia Accelerator*/
#define EM_PCP		55		/* Siemens PCP */
#define EM_NCPU		56		/* Sony nCPU embeeded RISC */
#define EM_NDR1		57		/* Denso NDR1 microprocessor */
#define EM_STARCORE	58		/* Motorola Start*Core processor */
#define EM_ME16		59		/* Toyota ME16 processor */
#define EM_ST100	60		/* STMicroelectronic ST100 processor */
#define EM_TINYJ	61		/* Advanced Logic Corp. Tinyj emb.fam*/
#define EM_X86_64	62		/* AMD x86-64 */
#define EM_PDSP		63		/* Sony DSP Processor */
/* RESERVED 64,65 for future use */
#define EM_FX66		66		/* Siemens FX66 microcontroller */
#define EM_ST9PLUS	67		/* STMicroelectronics ST9+ 8/16 mc */
#define EM_ST7		68		/* STmicroelectronics ST7 8 bit mc */
#define EM_68HC16	69		/* Motorola MC68HC16 microcontroller */
#define EM_68HC11	70		/* Motorola MC68HC11 microcontroller */
#define EM_68HC08	71		/* Motorola MC68HC08 microcontroller */
#define EM_68HC05	72		/* Motorola MC68HC05 microcontroller */
#define EM_SVX		73		/* Silicon Graphics SVx */
#define EM_ST19		74		/* STMicroelectronics ST19 8 bit mc */
#define EM_VAX		75		/* Digital VAX */
#define EM_CHRIS	76		/* Axis Communications embedded proc. */
#define EM_JAVELIN	77		/* Infineon Technologies emb. proc. */
#define EM_FIREPATH	78		/* Element 14 64-bit DSP Processor */
#define EM_ZSP		79		/* LSI Logic 16-bit DSP Processor */
#define EM_MMIX		80		/* Donald Knuth's edu 64-bit proc. */
#define EM_HUANY	81		/* Harvard University mach-indep objs */
#define EM_PRISM	82		/* SiTera Prism */
#define EM_AVR		83		/* Atmel AVR 8-bit microcontroller */
#define EM_FR30		84		/* Fujitsu FR30 */
#define EM_D10V		85		/* Mitsubishi DV10V */
#define EM_D30V		86		/* Mitsubishi DV30V */
#define EM_V850		87		/* NEC v850 */
#define EM_M32R		88		/* Mitsubishi M32R */
#define EM_MN10300	89		/* Matsushita MN10200 */
#define EM_MN10200	90		/* Matsushita MN10200 */
#define EM_PJ		91		/* picoJava */
#define EM_NUM		92		/* number of machine types */

/* Version */
#define EV_NONE		0		/* Invalid */
#define EV_CURRENT	1		/* Current */
#define EV_NUM		2		/* number of versions */

/* Section Header */
typedef struct {
	Elf32_Word	sh_name;	/* name - index into section header
					   string table section */
	Elf32_Word	sh_type;	/* type */
	Elf32_Word	sh_flags;	/* flags */
	Elf32_Addr	sh_addr;	/* address */
	Elf32_Off	sh_offset;	/* file offset */
	Elf32_Word	sh_size;	/* section size */
	Elf32_Word	sh_link;	/* section header table index link */
	Elf32_Word	sh_info;	/* extra information */
	Elf32_Word	sh_addralign;	/* address alignment */
	Elf32_Word	sh_entsize;	/* section entry size */
} Elf32_Shdr;

/* Special Section Indexes */
#define SHN_UNDEF	0		/* undefined */
#define SHN_LORESERVE	0xff00		/* lower bounds of reserved indexes */
#define SHN_LOPROC	0xff00		/* reserved range for processor */
#define SHN_HIPROC	0xff1f		/*   specific section indexes */
#define SHN_LOOS	0xff20		/* reserved range for operating */
#define SHN_HIOS	0xff3f		/*   specific semantics */
#define SHN_ABS		0xfff1		/* absolute value */
#define SHN_COMMON	0xfff2		/* common symbol */
#define SHN_XINDEX	0xffff		/* Index is an extra table */
#define SHN_HIRESERVE	0xffff		/* upper bounds of reserved indexes */

/* sh_type */
#define SHT_NULL	0		/* inactive */
#define SHT_PROGBITS	1		/* program defined information */
#define SHT_SYMTAB	2		/* symbol table section */
#define SHT_STRTAB	3		/* string table section */
#define SHT_RELA	4		/* relocation section with addends*/
#define SHT_HASH	5		/* symbol hash table section */
#define SHT_DYNAMIC	6		/* dynamic section */
#define SHT_NOTE	7		/* note section */
#define SHT_NOBITS	8		/* no space section */
#define SHT_REL		9		/* relation section without addends */
#define SHT_SHLIB	10		/* reserved - purpose unknown */
#define SHT_DYNSYM	11		/* dynamic symbol table section */
#define SHT_INIT_ARRAY	14		/* Array of constructors */
#define SHT_FINI_ARRAY	15		/* Array of destructors */
#define SHT_PREINIT_ARRAY 16		/* Array of pre-constructors */
#define SHT_GROUP	17		/* Section group */
#define SHT_SYMTAB_SHNDX 18		/* Extended section indeces */
#define SHT_NUM		19		/* number of section types */
#define SHT_LOOS	0x60000000	/* Start OS-specific */
#define SHT_HIOS	0x6fffffff	/* End OS-specific */
#define SHT_LOPROC	0x70000000	/* reserved range for processor */
#define SHT_HIPROC	0x7fffffff	/*  specific section header types */
#define SHT_LOUSER	0x80000000	/* reserved range for application */
#define SHT_HIUSER	0xffffffff	/*  specific indexes */

/* Section names */
#define ELF_BSS         ".bss"		/* uninitialized data */
#define ELF_COMMENT	".comment"	/* version control information */
#define ELF_DATA        ".data"		/* initialized data */
#define ELF_DATA1       ".data1"	/* initialized data */
#define ELF_DEBUG       ".debug"	/* debug */
#define ELF_DYNAMIC     ".dynamic"	/* dynamic linking information */
#define ELF_DYNSTR      ".dynstr"	/* dynamic string table */
#define ELF_DYNSYM      ".dynsym"	/* dynamic symbol table */
#define ELF_FINI        ".fini"		/* termination code */
#define ELF_FINI_ARRAY	".fini_array"	/* Array of destructors */
#define ELF_GOT         ".got"		/* global offset table */
#define ELF_HASH        ".hash"		/* symbol hash table */
#define ELF_INIT        ".init"		/* initialization code */
#define ELF_INIT_ARRAY	".init_array"	/* Array of constuctors */
#define ELF_INTERP	".interp"	/* Pathname of program interpreter */
#define ELF_LINE	".line"		/* Symbolic line numnber information */
#define ELF_NOTE	".note"		/* Contains note section */
#define ELF_PLT		".plt"		/* Procedure linkage table */
#define ELF_PREINIT_ARRAY ".preinit_array" /* Array of pre-constructors */
#define ELF_REL_DATA    ".rel.data"	/* relocation data */
#define ELF_REL_FINI    ".rel.fini"	/* relocation termination code */
#define ELF_REL_INIT    ".rel.init"	/* relocation initialization code */
#define ELF_REL_DYN     ".rel.dyn"	/* relocaltion dynamic link info */
#define ELF_REL_RODATA  ".rel.rodata"	/* relocation read-only data */
#define ELF_REL_TEXT    ".rel.text"	/* relocation code */
#define ELF_RODATA      ".rodata"	/* read-only data */
#define ELF_RODATA1     ".rodata1"	/* read-only data */
#define ELF_SHSTRTAB    ".shstrtab"	/* section header string table */
#define ELF_STRTAB      ".strtab"	/* string table */
#define ELF_SYMTAB      ".symtab"	/* symbol table */
#define ELF_SYMTAB_SHNDX ".symtab_shndx"/* symbol table section index */
#define ELF_TBSS	".tbss"		/* thread local uninit data */
#define ELF_TDATA	".tdata"	/* thread local init data */
#define ELF_TDATA1	".tdata1"	/* thread local init data */
#define ELF_TEXT        ".text"		/* code */

/* Section Attribute Flags - sh_flags */
#define SHF_WRITE	0x1		/* Writable */
#define SHF_ALLOC	0x2		/* occupies memory */
#define SHF_EXECINSTR	0x4		/* executable */
#define SHF_MERGE	0x10		/* Might be merged */
#define SHF_STRINGS	0x20		/* Contains NULL terminated strings */
#define SHF_INFO_LINK	0x40		/* sh_info contains SHT index */
#define SHF_LINK_ORDER	0x80		/* Preserve order after combining*/
#define SHF_OS_NONCONFORMING 0x100	/* Non-standard OS specific handling */
#define SHF_GROUP	0x200		/* Member of section group */
#define SHF_TLS		0x400		/* Thread local storage */
#define SHF_MASKOS	0x0ff00000	/* OS specific */
#define SHF_MASKPROC	0xf0000000	/* reserved bits for processor */
					/*  specific section attributes */

/* Section Group Flags */
#define GRP_COMDAT	0x1		/* COMDAT group */
#define GRP_MASKOS	0x0ff00000	/* Mask OS specific flags */
#define GRP_MASKPROC	0xf0000000	/* Mask processor specific flags */

/* Symbol Table Entry */
typedef struct elf32_sym {
	Elf32_Word	st_name;	/* name - index into string table */
	Elf32_Addr	st_value;	/* symbol value */
	Elf32_Word	st_size;	/* symbol size */
	unsigned char	st_info;	/* type and binding */
	unsigned char	st_other;	/* 0 - no defined meaning */
	Elf32_Half	st_shndx;	/* section header index */
} Elf32_Sym;

/* Symbol table index */
#define STN_UNDEF	0		/* undefined */

/* Extract symbol info - st_info */
#define ELF32_ST_BIND(x)	((x) >> 4)
#define ELF32_ST_TYPE(x)	(((unsigned int) x) & 0xf)
#define ELF32_ST_INFO(b,t)	(((b) << 4) + ((t) & 0xf))
#define ELF32_ST_VISIBILITY(x)	((x) & 0x3)

/* Symbol Binding - ELF32_ST_BIND - st_info */
#define STB_LOCAL	0		/* Local symbol */
#define STB_GLOBAL	1		/* Global symbol */
#define STB_WEAK	2		/* like global - lower precedence */
#define STB_NUM		3		/* number of symbol bindings */
#define STB_LOOS	10		/* reserved range for operating */
#define STB_HIOS	12		/*   system specific symbol bindings */
#define STB_LOPROC	13		/* reserved range for processor */
#define STB_HIPROC	15		/*  specific symbol bindings */

/* Symbol type - ELF32_ST_TYPE - st_info */
#define STT_NOTYPE	0		/* not specified */
#define STT_OBJECT	1		/* data object */
#define STT_FUNC	2		/* function */
#define STT_SECTION	3		/* section */
#define STT_FILE	4		/* file */
#define STT_NUM		5		/* number of symbol types */
#define STT_TLS		6		/* Thread local storage symbol */
#define STT_LOOS	10		/* reserved range for operating */
#define STT_HIOS	12		/*  system specific symbol types */
#define STT_LOPROC	13		/* reserved range for processor */
#define STT_HIPROC	15		/*  specific symbol types */

/* Symbol visibility - ELF32_ST_VISIBILITY - st_other */
#define STV_DEFAULT	0		/* Normal visibility rules */
#define STV_INTERNAL	1		/* Processor specific hidden class */
#define STV_HIDDEN	2		/* Symbol unavailable in other mods */
#define STV_PROTECTED	3		/* Not preemptible, not exported */


/* Relocation entry with implicit addend */
typedef struct
{
	Elf32_Addr	r_offset;	/* offset of relocation */
	Elf32_Word	r_info;		/* symbol table index and type */
} Elf32_Rel;

/* Relocation entry with explicit addend */
typedef struct
{
	Elf32_Addr	r_offset;	/* offset of relocation */
	Elf32_Word	r_info;		/* symbol table index and type */
	Elf32_Sword	r_addend;
} Elf32_Rela;

/* Extract relocation info - r_info */
#define ELF32_R_SYM(i)		((i) >> 8)
#define ELF32_R_TYPE(i)		((unsigned char) (i))
#define ELF32_R_INFO(s,t)	(((s) << 8) + (unsigned char)(t))

/* Program Header */
typedef struct {
	Elf32_Word	p_type;		/* segment type */
	Elf32_Off	p_offset;	/* segment offset */
	Elf32_Addr	p_vaddr;	/* virtual address of segment */
	Elf32_Addr	p_paddr;	/* physical address - ignored? */
	Elf32_Word	p_filesz;	/* number of bytes in file for seg. */
	Elf32_Word	p_memsz;	/* number of bytes in mem. for seg. */
	Elf32_Word	p_flags;	/* flags */
	Elf32_Word	p_align;	/* memory alignment */
} Elf32_Phdr;

/* Segment types - p_type */
#define PT_NULL		0		/* unused */
#define PT_LOAD		1		/* loadable segment */
#define PT_DYNAMIC	2		/* dynamic linking section */
#define PT_INTERP	3		/* the RTLD */
#define PT_NOTE		4		/* auxiliary information */
#define PT_SHLIB	5		/* reserved - purpose undefined */
#define PT_PHDR		6		/* program header */
#define PT_TLS		7		/* Thread local storage template */
#define PT_NUM		8		/* Number of segment types */
#define PT_LOOS		0x60000000	/* reserved range for operating */
#define PT_HIOS		0x6fffffff	/*   system specific segment types */
#define PT_LOPROC	0x70000000	/* reserved range for processor */
#define PT_HIPROC	0x7fffffff	/*  specific segment types */

/* Segment flags - p_flags */
#define PF_X		0x1		/* Executable */
#define PF_W		0x2		/* Writable */
#define PF_R		0x4		/* Readable */
#define PF_MASKOS	0x0ff00000	/* OS specific segment flags */
#define PF_MASKPROC	0xf0000000	/* reserved bits for processor */
					/*  specific segment flags */
/* Dynamic structure */
typedef struct
{
	Elf32_Sword	d_tag;		/* controls meaning of d_val */
	union
	{
		Elf32_Word	d_val;	/* Multiple meanings - see d_tag */
		Elf32_Addr	d_ptr;	/* program virtual address */
	} d_un;
} Elf32_Dyn;

extern Elf32_Dyn	_DYNAMIC[];

/* Dynamic Array Tags - d_tag */
#define DT_NULL		0		/* marks end of _DYNAMIC array */
#define DT_NEEDED	1		/* string table offset of needed lib */
#define DT_PLTRELSZ	2		/* size of relocation entries in PLT */
#define DT_PLTGOT	3		/* address PLT/GOT */
#define DT_HASH		4		/* address of symbol hash table */
#define DT_STRTAB	5		/* address of string table */
#define DT_SYMTAB	6		/* address of symbol table */
#define DT_RELA		7		/* address of relocation table */
#define DT_RELASZ	8		/* size of relocation table */
#define DT_RELAENT	9		/* size of relocation entry */
#define DT_STRSZ	10		/* size of string table */
#define DT_SYMENT	11		/* size of symbol table entry */
#define DT_INIT		12		/* address of initialization func. */
#define DT_FINI		13		/* address of termination function */
#define DT_SONAME	14		/* string table offset of shared obj */
#define DT_RPATH	15		/* string table offset of library
					   search path */
#define DT_SYMBOLIC	16		/* start sym search in shared obj. */
#define DT_REL		17		/* address of rel. tbl. w addends */
#define DT_RELSZ	18		/* size of DT_REL relocation table */
#define DT_RELENT	19		/* size of DT_REL relocation entry */
#define DT_PLTREL	20		/* PLT referenced relocation entry */
#define DT_DEBUG	21		/* bugger */
#define DT_TEXTREL	22		/* Allow rel. mod. to unwritable seg */
#define DT_JMPREL	23		/* add. of PLT's relocation entries */
#define DT_BIND_NOW	24		/* Process relocations of object */
#define DT_INIT_ARRAY	25		/* Array with addresses of init fct */
#define DT_FINI_ARRAY	26		/* Array with addresses of fini fct */
#define DT_INIT_ARRAYSZ	27		/* Size in bytes of DT_INIT_ARRAY */
#define DT_FINI_ARRAYSZ	28		/* Size in bytes of DT_FINI_ARRAY */
#define DT_RUNPATH	29		/* Library search path */
#define DT_FLAGS	30		/* Flags for the object being loaded */
#define DT_ENCODING	32		/* Start of encoded range */
#define DT_PREINIT_ARRAY 32		/* Array with addresses of preinit fct*/
#define DT_PREINIT_ARRAYSZ 33		/* size in bytes of DT_PREINIT_ARRAY */
#define DT_NUM		34		/* Number used. */
#define DT_LOOS		0x60000000	/* reserved range for OS */
#define DT_HIOS		0x6fffffff	/*   specific dynamic array tags */
#define DT_LOPROC	0x70000000	/* reserved range for processor */
#define DT_HIPROC	0x7fffffff	/*  specific dynamic array tags */


/* DT_ entries which fall between DT_VALRNGLO and DT_VALRNDHI use
   the d_val field of the Elf*_Dyn structure.  I.e. they contain scalars.  */
#define DT_VALRNGLO     0x6ffffd00
#define DT_VALRNGHI     0x6ffffdff

/* DT_ entries which fall between DT_ADDRRNGLO and DT_ADDRRNGHI use
   the d_ptr field of the Elf*_Dyn structure.  I.e. they contain pointers.  */
#define DT_ADDRRNGLO    0x6ffffe00
#define DT_ADDRRNGHI    0x6ffffeff

#define DT_VERSYM       0x6ffffff0
#define DT_RELACOUNT    0x6ffffff9
#define DT_RELCOUNT     0x6ffffffa
#define DT_FLAGS_1      0x6ffffffb
#define DT_VERDEF       0x6ffffffc
#define DT_VERDEFNUM    0x6ffffffd
#define DT_VERNEED      0x6ffffffe
#define DT_VERNEEDNUM   0x6fffffff

#define DT_MIPS_RLD_VERSION     0x70000001
#define DT_MIPS_TIME_STAMP      0x70000002
#define DT_MIPS_ICHECKSUM       0x70000003
#define DT_MIPS_IVERSION        0x70000004
#define DT_MIPS_FLAGS           0x70000005
  #define RHF_NONE                0
  #define RHF_HARDWAY             1
  #define RHF_NOTPOT              2
#define DT_MIPS_BASE_ADDRESS    0x70000006
#define DT_MIPS_CONFLICT        0x70000008
#define DT_MIPS_LIBLIST         0x70000009
#define DT_MIPS_LOCAL_GOTNO     0x7000000a
#define DT_MIPS_CONFLICTNO      0x7000000b
#define DT_MIPS_LIBLISTNO       0x70000010
#define DT_MIPS_SYMTABNO        0x70000011
#define DT_MIPS_UNREFEXTNO      0x70000012
#define DT_MIPS_GOTSYM          0x70000013
#define DT_MIPS_HIPAGENO        0x70000014
#define DT_MIPS_RLD_MAP         0x70000016

/* This info is needed when parsing the symbol table */
#define STB_LOCAL  0
#define STB_GLOBAL 1
#define STB_WEAK   2

#define STT_NOTYPE  0
#define STT_OBJECT  1
#define STT_FUNC    2
#define STT_SECTION 3
#define STT_FILE    4
#define STT_COMMON  5

#define ELF_ST_BIND(x)          ((x) >> 4)
#define ELF_ST_TYPE(x)          (((unsigned int) x) & 0xf)
#define ELF32_ST_BIND(x)        ELF_ST_BIND(x)
#define ELF32_ST_TYPE(x)        ELF_ST_TYPE(x)
#define ELF64_ST_BIND(x)        ELF_ST_BIND(x)
#define ELF64_ST_TYPE(x)        ELF_ST_TYPE(x)

/* Dynamic Tag Flags - d_un.d_val */
#define DF_ORIGIN	0x01		/* Object may use DF_ORIGIN */
#define DF_SYMBOLIC	0x02		/* Symbol resolutions starts here */
#define DF_TEXTREL	0x04		/* Object contains text relocations */
#define DF_BIND_NOW	0x08		/* No lazy binding for this object */
#define DF_STATIC_TLS	0x10		/* Static thread local storage */

/* Standard ELF hashing function */
unsigned long elf_hash(const unsigned char *name);

#define ELF_TARG_VER	1	/* The ver for which this code is intended */

/* Processor specific flags for the ELF header e_flags field.  */
#define EF_ARM_RELEXEC     0x01
#define EF_ARM_HASENTRY    0x02
#define EF_ARM_INTERWORK   0x04
#define EF_ARM_APCS_26     0x08
#define EF_ARM_APCS_FLOAT  0x10
#define EF_ARM_PIC         0x20
#define EF_ARM_ALIGN8      0x40         /* 8-bit structure alignment is in use.  */
#define EF_ARM_NEW_ABI     0x80
#define EF_ARM_OLD_ABI     0x100
#define EF_ARM_SOFT_FLOAT  0x200
#define EF_ARM_VFP_FLOAT   0x400
#define EF_ARM_MAVERICK_FLOAT 0x800

/* Other constants defined in the ARM ELF spec. version B-01.  */
#define EF_ARM_SYMSARESORTED 0x04       /* NB conflicts with EF_INTERWORK */
#define EF_ARM_DYNSYMSUSESEGIDX 0x08    /* NB conflicts with EF_APCS26 */
#define EF_ARM_MAPSYMSFIRST 0x10        /* NB conflicts with EF_APCS_FLOAT */
#define EF_ARM_EABIMASK      0xFF000000

#define EF_ARM_EABI_VERSION(flags) ((flags) & EF_ARM_EABIMASK)
#define EF_ARM_EABI_UNKNOWN  0x00000000
#define EF_ARM_EABI_VER1     0x01000000
#define EF_ARM_EABI_VER2     0x02000000

/* Local aliases for some flags to match names used by COFF port.  */
#define F_INTERWORK        EF_ARM_INTERWORK
#define F_APCS26           EF_ARM_APCS_26
#define F_APCS_FLOAT       EF_ARM_APCS_FLOAT
#define F_PIC              EF_ARM_PIC
#define F_SOFT_FLOAT       EF_ARM_SOFT_FLOAT
#define F_VFP_FLOAT        EF_ARM_VFP_FLOAT



/* Additional symbol types for Thumb.  */
#define STT_ARM_TFUNC      STT_LOPROC   /* A Thumb function.  */
#define STT_ARM_16BIT      STT_HIPROC   /* A Thumb label.  */

/* ARM-specific values for sh_flags.  */
#define SHF_ENTRYSECT      0x10000000   /* Section contains an entry point.  */
#define SHF_COMDEF         0x80000000   /* Section may be multiply defined in the input to a link step.  */

/* ARM-specific program header flags.  */
#define PF_ARM_SB          0x10000000   /* Segment contains the location addressed by the static base.  */
#define PF_ARM_PI          0x20000000   /* Segment is position-independent.  */
#define PF_ARM_ABS         0x40000000   /* Segment must be loaded at its base address.  */



/* ARM specific declarations */

/* Processor specific flags for the ELF header e_flags field.  */
#define EF_ARM_RELEXEC     0x01
#define EF_ARM_HASENTRY    0x02
#define EF_ARM_INTERWORK   0x04
#define EF_ARM_APCS_26     0x08
#define EF_ARM_APCS_FLOAT  0x10
#define EF_ARM_PIC         0x20
#define EF_ALIGN8          0x40         /* 8-bit structure alignment is in use */
#define EF_NEW_ABI         0x80
#define EF_OLD_ABI         0x100


/* ARM-specific values for sh_flags */
#define SHF_ARM_ENTRYSECT  0x10000000   /* Section contains an entry point */
#define SHF_ARM_COMDEF     0x80000000   /* Section may be multiply defined
                                           in the input to a link step */

/* ARM-specific program header flags */
#define PF_ARM_SB          0x10000000   /* Segment contains the location
                                           addressed by the static base */




/* ARM relocs.  */
#define R_ARM_NONE              0       /* No reloc */
#define R_ARM_PC24              1       /* PC relative 26 bit branch */
#define R_ARM_ABS32             2       /* Direct 32 bit  */
#define R_ARM_REL32             3       /* PC relative 32 bit */
#define R_ARM_PC13              4
#define R_ARM_ABS16             5       /* Direct 16 bit */
#define R_ARM_ABS12             6       /* Direct 12 bit */
#define R_ARM_THM_ABS5          7
#define R_ARM_ABS8              8       /* Direct 8 bit */
#define R_ARM_SBREL32           9
#define R_ARM_THM_PC22          10
#define R_ARM_THM_PC8           11
#define R_ARM_AMP_VCALL9        12
#define R_ARM_SWI24             13
#define R_ARM_THM_SWI8          14
#define R_ARM_XPC25             15
#define R_ARM_THM_XPC22         16
#define R_ARM_COPY              20      /* Copy symbol at runtime */
#define R_ARM_GLOB_DAT          21      /* Create GOT entry */
#define R_ARM_JUMP_SLOT         22      /* Create PLT entry */
#define R_ARM_RELATIVE          23      /* Adjust by program base */
#define R_ARM_GOTOFF            24      /* 32 bit offset to GOT */
#define R_ARM_GOTPC             25      /* 32 bit PC relative offset to GOT */
#define R_ARM_GOT32             26      /* 32 bit GOT entry */
#define R_ARM_PLT32             27      /* 32 bit PLT address */
#define R_ARM_CALL              28
#define R_ARM_JUMP24            29
#define R_ARM_GNU_VTENTRY       100
#define R_ARM_GNU_VTINHERIT     101
#define R_ARM_THM_PC11          102     /* thumb unconditional branch */
#define R_ARM_THM_PC9           103     /* thumb conditional branch */
#define R_ARM_RXPC25            249
#define R_ARM_RSBREL32          250
#define R_ARM_THM_RPC22         251
#define R_ARM_RREL32            252
#define R_ARM_RABS22            253
#define R_ARM_RPC24             254
#define R_ARM_RBASE             255
/* Keep this the last entry.  */
#define R_ARM_NUM               256



#endif /* _ELF_H */
