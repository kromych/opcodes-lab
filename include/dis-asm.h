/* Interface between the opcode library and its callers.

   Copyright (C) 1999-2023 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 51 Franklin Street - Fifth Floor,
   Boston, MA 02110-1301, USA.

   Written by Cygnus Support, 1993.

   The opcode library (libopcodes.a) provides instruction decoders for
   a large variety of instruction sets, callable with an identical
   interface, for making instruction-processing programs more independent
   of the instruction set being processed.  */

#ifndef DIS_ASM_H
#define DIS_ASM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdio.h>
#include <string.h>
#include "bfd.h"

enum dis_insn_type
{
  dis_noninsn,			/* Not a valid instruction.  */
  dis_nonbranch,		/* Not a branch instruction.  */
  dis_branch,			/* Unconditional branch.  */
  dis_condbranch,		/* Conditional branch.  */
  dis_jsr,			/* Jump to subroutine.  */
  dis_condjsr,			/* Conditional jump to subroutine.  */
  dis_dref,			/* Data reference instruction.  */
  dis_dref2			/* Two data references in instruction.  */
};

/* When printing styled disassembler output, this describes what style
   should be used.  */

enum disassembler_style
{
  /* This is the default style, use this for any additional syntax
     (e.g. commas between operands, brackets, etc), or just as a default if
     no other style seems appropriate.  */
  dis_style_text,

  /* Use this for all instruction mnemonics, or aliases for mnemonics.
     These should be things that correspond to real machine
     instructions.  */
  dis_style_mnemonic,

  /* Some architectures include additional mnemonic like fields within the
     instruction operands, e.g. on aarch64 'add w16, w7, w1, lsl #2' where
     the 'lsl' is an additional piece of text that describes how the
     instruction should behave.  This sub-mnemonic style can be used for
     these pieces of text.  */
  dis_style_sub_mnemonic,

  /* For things that aren't real machine instructions, but rather
     assembler directives, e.g. .byte, etc.  */
  dis_style_assembler_directive,

  /* Use this for any register names.  This may or may-not include any
     register prefix, e.g. '$', '%', at the discretion of the target,
     though within each target the choice to include prefixes for not
     should be kept consistent.  If the prefix is not printed with this
     style, then dis_style_text should be used.  */
  dis_style_register,

  /* Use this for any constant values used within instructions or
     directives, unless the value is an absolute address, or an offset
     that will be added to an address (no matter where the address comes
     from) before use.  This style may, or may-not be used for any
     prefix to the immediate value, e.g. '$', at the discretion of the
     target, though within each target the choice to include these
     prefixes should be kept consistent.  */
  dis_style_immediate,

  /* The style for the numerical representation of an absolute address.
     Anything that is an address offset should use the immediate style.
     This style may, or may-not be used for any prefix to the immediate
     value, e.g. '$', at the discretion of the target, though within
     each target the choice to include these prefixes should be kept
     consistent.  */
  dis_style_address,

  /* The style for any constant value within an instruction or directive
     that represents an offset that will be added to an address before
     use.  This style may, or may-not be used for any prefix to the
     immediate value, e.g. '$', at the discretion of the target, though
     within each target the choice to include these prefixes should be
     kept consistent.  */
  dis_style_address_offset,

  /* The style for a symbol's name.  The numerical address of a symbol
     should use the address style above, this style is reserved for the
     name.  */
  dis_style_symbol,

  /* The start of a comment that runs to the end of the line.  Anything
     printed after a comment start might be styled differently,
     e.g. everything might be styled as a comment, regardless of the
     actual style used.  The disassembler itself should not try to adjust
     the style emitted for comment content, e.g. an address emitted within
     a comment should still be given dis_style_address, in this way it is
     up to the user of the disassembler to decide how comments should be
     styled.  */
  dis_style_comment_start
};


typedef int (*fprintf_ftype) (void *, const char*, ...);
typedef int (*fprintf_styled_ftype) (void *, enum disassembler_style, const char*, ...);

typedef struct disassemble_info {
    fprintf_ftype fprintf_func;
    fprintf_styled_ftype fprintf_styled_func;
    void *stream;
    void *application_data;

    unsigned long mach;

    /* Function used to get bytes to disassemble.  MEMADDR is the
   address of the stuff to be disassembled, MYADDR is the address to
   put the bytes in, and LENGTH is the number of bytes to read.
   INFO is a pointer to this struct.
   Returns an errno value or 0 for success.  */
    int (*read_memory_func)
        (bfd_vma memaddr, bfd_byte *myaddr, unsigned int length,
         struct disassemble_info *dinfo);

    /* Function which should be called if we get an error that we can't
       recover from.  STATUS is the errno value from read_memory_func and
       MEMADDR is the address that we were trying to read.  INFO is a
       pointer to this struct.  */
    void (*memory_error_func)
        (int status, bfd_vma memaddr, struct disassemble_info *dinfo);

    /* Function called to print ADDR.  */
    void (*print_address_func)
        (bfd_vma addr, struct disassemble_info *dinfo);

    /* For use by the disassembler.
       The top 16 bits are reserved for public use (and are documented here).
       The bottom 16 bits are for the internal use of the disassembler.  */
    unsigned long flags;
    /* Set if the disassembler has determined that there are one or more
       relocations associated with the instruction being disassembled.  */
#define INSN_HAS_RELOC	 (1u << 31)
    /* Set if the user has requested the disassembly of data as well as code.  */
#define DISASSEMBLE_DATA (1u << 30)
    /* Set if the user has specifically set the machine type encoded in the
       mach field of this structure.  */
#define USER_SPECIFIED_MACHINE_TYPE (1u << 29)
    /* Set if the user has requested wide output.  */
#define WIDE_OUTPUT (1u << 28)

    /* Use internally by the target specific disassembly code.  */
    void *private_data;

    /* This variable may be set by the instruction decoder.  It suggests
        the number of bytes objdump should display on a single line.  If
        the instruction decoder sets this, it should always set it to
        the same value in order to get reasonable looking output.  */
    int bytes_per_line;

    /* The next two variables control the way objdump displays the raw data.  */
    /* For example, if bytes_per_line is 8 and bytes_per_chunk is 4, the */
    /* output will look like this:
       00:   00000000 00000000
       with the chunks displayed according to "display_endian". */
    int bytes_per_chunk;

    /* Number of octets per incremented target address
       Normally one, but some DSPs have byte sizes of 16 or 32 bits.  */
    unsigned int octets_per_byte;

    /* The number of zeroes we want to see at the end of a section before we
       start skipping them.  */
    unsigned int skip_zeroes;

    /* The number of zeroes to skip at the end of a section.  If the number
       of zeroes at the end is between SKIP_ZEROES_AT_END and SKIP_ZEROES,
       they will be disassembled.  If there are fewer than
       SKIP_ZEROES_AT_END, they will be skipped.  This is a heuristic
       attempt to avoid disassembling zeroes inserted by section
       alignment.  */
    unsigned int skip_zeroes_at_end;

    /* Whether the disassembler always needs the relocations.  */
    bool disassembler_needs_relocs;
    bfd_vma target;		/* Target address of branch or dref, if known;
                        zero if unknown.  */
    bfd_vma target2;		/* Second target address for dref2 */

    /* Results from instruction decoders.  Not all decoders yet support
       this information.  This info is set each time an instruction is
       decoded, and is only valid for the last such instruction.

       To determine whether this decoder supports this information, set
       insn_info_valid to 0, decode an instruction, then check it.  */

    char insn_info_valid;		/* Branch info has been set. */
    char branch_delay_insns;	/* How many sequential insn's will run before
                                     a branch takes effect.  (0 = normal) */
    char data_size;		/* Size of data reference in insn, in bytes */
    enum dis_insn_type insn_type;	/* Type of instruction */

    /* Command line options specific to the target disassembler.  */
    const char *disassembler_options;

    /* Set to true if the disassembler applied styling to the output,
       otherwise, set to false.  */
    bool created_styled_output;
} disassemble_info;

typedef int (*disassembler_ftype) (bfd_vma, disassemble_info *);
typedef void* asymbol;

static inline char* bfd_asymbol_name (asymbol sym) {
    return NULL;
}


#ifdef __cplusplus
}
#endif

#endif /* ! defined (DIS_ASM_H) */
