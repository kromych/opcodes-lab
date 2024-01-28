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

#ifdef __cplusplus
}
#endif

#endif /* ! defined (DIS_ASM_H) */
