//
// Created by krom on 1/28/24.
//

#ifndef OPCODES_AARCH64_INSN_BITS_H
#define OPCODES_AARCH64_INSN_BITS_H

#include "aarch64-opc.h"

/* copied from aarch64-opc.c */

/* Instruction bit-fields.
+   Keep synced with 'enum aarch64_field_kind'.  */
const aarch64_field fields[] =
        {
                {  0,  0 },	/* NIL.  */
                {  8,  4 },	/* CRm: in the system instructions.  */
                { 10,  2 }, /* CRm_dsb_nxs: 2-bit imm. encoded in CRm<3:2>.  */
                { 12,  4 },	/* CRn: in the system instructions.  */
                { 10,  8 }, /* CSSC_imm8.  */
                { 11,  1 },	/* H: in advsimd scalar x indexed element instructions.  */
                { 21,  1 },	/* L: in advsimd scalar x indexed element instructions.  */
                { 20,  1 },	/* M: in advsimd scalar x indexed element instructions.  */
                { 22,  1 },	/* N: in logical (immediate) instructions.  */
                { 30,  1 },	/* Q: in most AdvSIMD instructions.  */
                { 10,  5 },	/* Ra: in fp instructions.  */
                {  0,  5 },	/* Rd: in many integer instructions.  */
                { 16,  5 },	/* Rm: in ld/st reg offset and some integer inst.  */
                {  5,  5 },	/* Rn: in many integer instructions.  */
                { 16,  5 },	/* Rs: in load/store exclusive instructions.  */
                {  0,  5 },	/* Rt: in load/store instructions.  */
                { 10,  5 },	/* Rt2: in load/store pair instructions.  */
                { 12,  1 },	/* S: in load/store reg offset instructions.  */
                { 12,  2 }, /* SM3_imm2: Indexed element SM3 2 bits index immediate.  */
                {  1,  3 }, /* SME_Pdx2: predicate register, multiple of 2, [3:1].  */
                { 13,  3 }, /* SME_Pm: second source scalable predicate register P0-P7.  */
                {  0,  3 }, /* SME_PNd3: PN0-PN7, bits [2:0].  */
                {  5,  3 }, /* SME_PNn3: PN0-PN7, bits [7:5].  */
                { 16,  1 }, /* SME_Q: Q class bit, bit 16.  */
                { 16,  2 }, /* SME_Rm: index base register W12-W15 [17:16].  */
                { 13,  2 }, /* SME_Rv: vector select register W12-W15, bits [14:13].  */
                { 15,  1 }, /* SME_V: (horizontal / vertical tiles), bit 15.  */
                { 10,  1 }, /* SME_VL_10: VLx2 or VLx4, bit [10].  */
                { 13,  1 }, /* SME_VL_13: VLx2 or VLx4, bit [13].  */
                {  0,  2 }, /* SME_ZAda_2b: tile ZA0-ZA3.  */
                {  0,  3 }, /* SME_ZAda_3b: tile ZA0-ZA7.  */
                {  1,  4 }, /* SME_Zdn2: Z0-Z31, multiple of 2, bits [4:1].  */
                {  2,  3 }, /* SME_Zdn4: Z0-Z31, multiple of 4, bits [4:2].  */
                { 16,  4 }, /* SME_Zm: Z0-Z15, bits [19:16].  */
                { 17,  4 }, /* SME_Zm2: Z0-Z31, multiple of 2, bits [20:17].  */
                { 18,  3 }, /* SME_Zm4: Z0-Z31, multiple of 4, bits [20:18].  */
                {  6,  4 }, /* SME_Zn2: Z0-Z31, multiple of 2, bits [9:6].  */
                {  7,  3 }, /* SME_Zn4: Z0-Z31, multiple of 4, bits [9:7].  */
                {  4,  1 }, /* SME_ZtT: upper bit of Zt, bit [4].  */
                {  0,  3 }, /* SME_Zt3: lower 3 bits of Zt, bits [2:0].  */
                {  0,  2 }, /* SME_Zt2: lower 2 bits of Zt, bits [1:0].  */
                { 23,  1 }, /* SME_i1: immediate field, bit 23.  */
                { 12,  2 }, /* SME_size_12: bits [13:12].  */
                { 22,  2 }, /* SME_size_22: size<1>, size<0> class field, [23:22].  */
                { 23,  1 }, /* SME_sz_23: bit [23].  */
                { 22,  1 }, /* SME_tszh: immediate and qualifier field, bit 22.  */
                { 18,  3 }, /* SME_tszl: immediate and qualifier field, bits [20:18].  */
                { 0,   8 }, /* SME_zero_mask: list of up to 8 tile names separated by commas [7:0].  */
                {  4,  1 }, /* SVE_M_4: Merge/zero select, bit 4.  */
                { 14,  1 }, /* SVE_M_14: Merge/zero select, bit 14.  */
                { 16,  1 }, /* SVE_M_16: Merge/zero select, bit 16.  */
                { 17,  1 }, /* SVE_N: SVE equivalent of N.  */
                {  0,  4 }, /* SVE_Pd: p0-p15, bits [3,0].  */
                { 10,  3 }, /* SVE_Pg3: p0-p7, bits [12,10].  */
                {  5,  4 }, /* SVE_Pg4_5: p0-p15, bits [8,5].  */
                { 10,  4 }, /* SVE_Pg4_10: p0-p15, bits [13,10].  */
                { 16,  4 }, /* SVE_Pg4_16: p0-p15, bits [19,16].  */
                { 16,  4 }, /* SVE_Pm: p0-p15, bits [19,16].  */
                {  5,  4 }, /* SVE_Pn: p0-p15, bits [8,5].  */
                {  0,  4 }, /* SVE_Pt: p0-p15, bits [3,0].  */
                {  5,  5 }, /* SVE_Rm: SVE alternative position for Rm.  */
                { 16,  5 }, /* SVE_Rn: SVE alternative position for Rn.  */
                {  0,  5 }, /* SVE_Vd: Scalar SIMD&FP register, bits [4,0].  */
                {  5,  5 }, /* SVE_Vm: Scalar SIMD&FP register, bits [9,5].  */
                {  5,  5 }, /* SVE_Vn: Scalar SIMD&FP register, bits [9,5].  */
                {  5,  5 }, /* SVE_Za_5: SVE vector register, bits [9,5].  */
                { 16,  5 }, /* SVE_Za_16: SVE vector register, bits [20,16].  */
                {  0,  5 }, /* SVE_Zd: SVE vector register. bits [4,0].  */
                {  5,  5 }, /* SVE_Zm_5: SVE vector register, bits [9,5].  */
                { 16,  5 }, /* SVE_Zm_16: SVE vector register, bits [20,16]. */
                {  5,  5 }, /* SVE_Zn: SVE vector register, bits [9,5].  */
                {  0,  5 }, /* SVE_Zt: SVE vector register, bits [4,0].  */
                {  5,  1 }, /* SVE_i1: single-bit immediate.  */
                { 20,  1 }, /* SVE_i2h: high bit of 2bit immediate, bits.  */
                { 22,  1 }, /* SVE_i3h: high bit of 3-bit immediate.  */
                { 19,  2 }, /* SVE_i3h2: two high bits of 3bit immediate, bits [20,19].  */
                { 11,  1 }, /* SVE_i3l: low bit of 3-bit immediate.  */
                { 16,  3 }, /* SVE_imm3: 3-bit immediate field.  */
                { 16,  4 }, /* SVE_imm4: 4-bit immediate field.  */
                {  5,  5 }, /* SVE_imm5: 5-bit immediate field.  */
                { 16,  5 }, /* SVE_imm5b: secondary 5-bit immediate field.  */
                { 16,  6 }, /* SVE_imm6: 6-bit immediate field.  */
                { 14,  7 }, /* SVE_imm7: 7-bit immediate field.  */
                {  5,  8 }, /* SVE_imm8: 8-bit immediate field.  */
                {  5,  9 }, /* SVE_imm9: 9-bit immediate field.  */
                { 11,  6 }, /* SVE_immr: SVE equivalent of immr.  */
                {  5,  6 }, /* SVE_imms: SVE equivalent of imms.  */
                { 10,  2 }, /* SVE_msz: 2-bit shift amount for ADR.  */
                {  5,  5 }, /* SVE_pattern: vector pattern enumeration.  */
                {  0,  4 }, /* SVE_prfop: prefetch operation for SVE PRF[BHWD].  */
                { 16,  1 }, /* SVE_rot1: 1-bit rotation amount.  */
                { 10,  2 }, /* SVE_rot2: 2-bit rotation amount.  */
                { 10,  1 }, /* SVE_rot3: 1-bit rotation amount at bit 10.  */
                { 17,  2 }, /* SVE_size: 2-bit element size, bits [18,17].  */
                { 22,  1 }, /* SVE_sz: 1-bit element size select.  */
                { 30,  1 }, /* SVE_sz2: 1-bit element size select.  */
                { 16,  4 }, /* SVE_tsz: triangular size select.  */
                { 22,  2 }, /* SVE_tszh: triangular size select high, bits [23,22].  */
                {  8,  2 }, /* SVE_tszl_8: triangular size select low, bits [9,8].  */
                { 19,  2 }, /* SVE_tszl_19: triangular size select low, bits [20,19].  */
                { 14,  1 }, /* SVE_xs_14: UXTW/SXTW select (bit 14).  */
                { 22,  1 }, /* SVE_xs_22: UXTW/SXTW select (bit 22).  */
                { 22,  1 },	/* S_imm10: in LDRAA and LDRAB instructions.  */
                { 16,  3 },	/* abc: a:b:c bits in AdvSIMD modified immediate.  */
                { 13,  3 },	/* asisdlso_opcode: opcode in advsimd ld/st single element.  */
                { 19,  5 },	/* b40: in the test bit and branch instructions.  */
                { 31,  1 },	/* b5: in the test bit and branch instructions.  */
                { 12,  4 },	/* cmode: in advsimd modified immediate instructions.  */
                { 12,  4 },	/* cond: condition flags as a source operand.  */
                {  0,  4 },	/* cond2: condition in truly conditional-executed inst.  */
                {  5,  5 },	/* defgh: d:e:f:g:h bits in AdvSIMD modified immediate.  */
                { 21,  2 },	/* hw: in move wide constant instructions.  */
                {  0,  1 },	/* imm1_0: general immediate in bits [0].  */
                {  2,  1 },	/* imm1_2: general immediate in bits [2].  */
                {  8,  1 },	/* imm1_8: general immediate in bits [8].  */
                { 10,  1 },	/* imm1_10: general immediate in bits [10].  */
                { 15,  1 },	/* imm1_15: general immediate in bits [15].  */
                { 16,  1 },	/* imm1_16: general immediate in bits [16].  */
                {  0,  2 },	/* imm2_0: general immediate in bits [1:0].  */
                {  1,  2 },	/* imm2_1: general immediate in bits [2:1].  */
                {  8,  2 },	/* imm2_8: general immediate in bits [9:8].  */
                { 10,  2 }, /* imm2_10: 2-bit immediate, bits [11:10] */
                { 12,  2 }, /* imm2_12: 2-bit immediate, bits [13:12] */
                { 15,  2 }, /* imm2_15: 2-bit immediate, bits [16:15] */
                { 16,  2 }, /* imm2_16: 2-bit immediate, bits [17:16] */
                { 19,  2 }, /* imm2_19: 2-bit immediate, bits [20:19] */
                {  0,  3 },	/* imm3_0: general immediate in bits [2:0].  */
                {  5,  3 },	/* imm3_5: general immediate in bits [7:5].  */
                { 10,  3 },	/* imm3_10: in add/sub extended reg instructions.  */
                { 12,  3 },	/* imm3_12: general immediate in bits [14:12].  */
                { 14,  3 },	/* imm3_14: general immediate in bits [16:14].  */
                { 15,  3 },	/* imm3_15: general immediate in bits [17:15].  */
                {  0,  4 },	/* imm4_0: in rmif instructions.  */
                {  5,  4 }, /* imm4_5: in SME instructions.  */
                { 10,  4 },	/* imm4_10: in adddg/subg instructions.  */
                { 11,  4 },	/* imm4_11: in advsimd ext and advsimd ins instructions.  */
                { 14,  4 },	/* imm4_14: general immediate in bits [17:14].  */
                { 16,  5 },	/* imm5: in conditional compare (immediate) instructions.  */
                { 10,  6 },	/* imm6_10: in add/sub reg shifted instructions.  */
                { 15,  6 },	/* imm6_15: in rmif instructions.  */
                { 15,  7 },	/* imm7: in load/store pair pre/post index instructions.  */
                { 13,  8 },	/* imm8: in floating-point scalar move immediate inst.  */
                { 12,  9 },	/* imm9: in load/store pre/post index instructions.  */
                { 10, 12 },	/* imm12: in ld/st unsigned imm or add/sub shifted inst.  */
                {  5, 14 },	/* imm14: in test bit and branch instructions.  */
                {  0, 16 },	/* imm16_0: in udf instruction. */
                {  5, 16 },	/* imm16_5: in exception instructions.  */
                {  5, 19 },	/* imm19: e.g. in CBZ.  */
                {  0, 26 },	/* imm26: in unconditional branch instructions.  */
                { 16,  3 },	/* immb: in advsimd shift by immediate instructions.  */
                { 19,  4 },	/* immh: in advsimd shift by immediate instructions.  */
                {  5, 19 },	/* immhi: e.g. in ADRP.  */
                { 29,  2 },	/* immlo: e.g. in ADRP.  */
                { 16,  6 },	/* immr: in bitfield and logical immediate instructions.  */
                { 10,  6 },	/* imms: in bitfield and logical immediate instructions.  */
                { 11,  1 },	/* index: in ld/st inst deciding the pre/post-index.  */
                { 24,  1 },	/* index2: in ld/st pair inst deciding the pre/post-index.  */
                { 30,  2 },	/* ldst_size: size field in ld/st reg offset inst.  */
                { 13,  2 },	/* len: in advsimd tbl/tbx instructions.  */
                { 30,  1 },	/* lse_sz: in LSE extension atomic instructions.  */
                {  0,  4 },	/* nzcv: flag bit specifier, encoded in the "nzcv" field.  */
                { 29,  1 },	/* op: in AdvSIMD modified immediate instructions.  */
                { 19,  2 },	/* op0: in the system instructions.  */
                { 16,  3 },	/* op1: in the system instructions.  */
                {  5,  3 },	/* op2: in the system instructions.  */
                { 22,  2 },	/* opc: in load/store reg offset instructions.  */
                { 23,  1 },	/* opc1: in load/store reg offset instructions.  */
                { 12,  4 },	/* opcode: in advsimd load/store instructions.  */
                { 13,  3 },	/* option: in ld/st reg offset + add/sub extended reg inst.  */
                { 11,  2 }, /* rotate1: FCMLA immediate rotate.  */
                { 13,  2 }, /* rotate2: Indexed element FCMLA immediate rotate.  */
                { 12,  1 }, /* rotate3: FCADD immediate rotate.  */
                { 10,  6 },	/* scale: in the fixed-point scalar to fp converting inst.  */
                { 31,  1 },	/* sf: in integer data processing instructions.  */
                { 22,  2 },	/* shift: in add/sub reg/imm shifted instructions.  */
                { 22,  2 },	/* size: in most AdvSIMD and floating-point instructions.  */
                { 22,  1 }, /* sz: 1-bit element size select.  */
                { 22,  2 },	/* type: floating point type field in fp data inst.  */
                { 10,  2 },	/* vldst_size: size field in the AdvSIMD load/store inst.  */
        };


#endif //OPCODES_AARCH64_INSN_BITS_H
