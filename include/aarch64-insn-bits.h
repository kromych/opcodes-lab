//
// Created by krom on 1/28/24.
//

#ifndef OPCODES_AARCH64_INSN_BITS_H
#define OPCODES_AARCH64_INSN_BITS_H

#include "bfd.h"
#include "dis-asm.h"
#include "aarch64-opc.h"

/* copied from aarch64-opc.c */

/* Instruction bit-fields.
   Keep synced with 'enum aarch64_field_kind'.  */
const aarch64_field aarch64_fields[] =
{
    AARCH64_FIELD_NIL,	/* NIL.  */
    AARCH64_FIELD_CONST (0, 1),	/* CONST_0.  */
    AARCH64_FIELD_CONST (0, 2),	/* CONST_00.  */
    AARCH64_FIELD_CONST (1, 2),	/* CONST_01.  */
    AARCH64_FIELD_CONST (1, 1),	/* CONST_1.  */
    AARCH64_FIELD ( 8, 4), /* CRm: in the system instructions.  */
    AARCH64_FIELD (10, 2), /* CRm_dsb_nxs: 2-bit imm. encoded in CRm<3:2>.  */
    AARCH64_FIELD (12, 4), /* CRn: in the system instructions.  */
    AARCH64_FIELD (10, 8), /* CSSC_imm8.  */
    AARCH64_FIELD (11, 1), /* H: in advsimd scalar x indexed element instructions.  */
    AARCH64_FIELD (21, 1), /* L: in advsimd scalar x indexed element instructions.  */
    AARCH64_FIELD ( 0, 5), /* LSE128_Rt: Shared input+output operand register.  */
    AARCH64_FIELD (16, 5), /* LSE128_Rt2: Shared input+output operand register 2.  */
    AARCH64_FIELD (20, 1), /* M: in advsimd scalar x indexed element instructions.  */
    AARCH64_FIELD (22, 1), /* N: in logical (immediate) instructions.  */
    AARCH64_FIELD (30, 1), /* Q: in most AdvSIMD instructions.  */
    AARCH64_FIELD (10, 5), /* Ra: in fp instructions.  */
    AARCH64_FIELD ( 0, 5), /* Rd: in many integer instructions.  */
    AARCH64_FIELD (16, 5), /* Rm: in ld/st reg offset and some integer inst.  */
    AARCH64_FIELD ( 5, 5), /* Rn: in many integer instructions.  */
    AARCH64_FIELD (16, 5), /* Rs: in load/store exclusive instructions.  */
    AARCH64_FIELD ( 0, 5), /* Rt: in load/store instructions.  */
    AARCH64_FIELD (10, 5), /* Rt2: in load/store pair instructions.  */
    AARCH64_FIELD (12, 1), /* S: in load/store reg offset instructions.  */
    AARCH64_FIELD (12, 2), /* SM3_imm2: Indexed element SM3 2 bits index immediate.  */
    AARCH64_FIELD ( 1, 3), /* SME_Pdx2: predicate register, multiple of 2, [3:1].  */
    AARCH64_FIELD (13, 3), /* SME_Pm: second source scalable predicate register P0-P7.  */
    AARCH64_FIELD ( 0, 3), /* SME_PNd3: PN0-PN7, bits [2:0].  */
    AARCH64_FIELD ( 5, 3), /* SME_PNn3: PN0-PN7, bits [7:5].  */
    AARCH64_FIELD (16, 1), /* SME_Q: Q class bit, bit 16.  */
    AARCH64_FIELD (16, 2), /* SME_Rm: index base register W12-W15 [17:16].  */
    AARCH64_FIELD (13, 2), /* SME_Rv: vector select register W12-W15, bits [14:13].  */
    AARCH64_FIELD (15, 1), /* SME_V: (horizontal / vertical tiles), bit 15.  */
    AARCH64_FIELD (10, 1), /* SME_VL_10: VLx2 or VLx4, bit [10].  */
    AARCH64_FIELD (13, 1), /* SME_VL_13: VLx2 or VLx4, bit [13].  */
    AARCH64_FIELD ( 0, 1), /* SME_ZAda_1b: tile ZA0-ZA1.  */
    AARCH64_FIELD ( 0, 2), /* SME_ZAda_2b: tile ZA0-ZA3.  */
    AARCH64_FIELD ( 0, 3), /* SME_ZAda_3b: tile ZA0-ZA7.  */
    AARCH64_FIELD ( 1, 4), /* SME_Zdn2: Z0-Z31, multiple of 2, bits [4:1].  */
    AARCH64_FIELD ( 2, 3), /* SME_Zdn4: Z0-Z31, multiple of 4, bits [4:2].  */
    AARCH64_FIELD (16, 4), /* SME_Zm: Z0-Z15, bits [19:16].  */
    AARCH64_FIELD (17, 3), /* SME_Zm17_3: Z0-Z15/Z16-Z31, multiple of 2, bits [19:17].  */
    AARCH64_FIELD (17, 4), /* SME_Zm2: Z0-Z31, multiple of 2, bits [20:17].  */
    AARCH64_FIELD (18, 3), /* SME_Zm4: Z0-Z31, multiple of 4, bits [20:18].  */
    AARCH64_FIELD ( 6, 4), /* SME_Zn2: Z0-Z31, multiple of 2, bits [9:6].  */
    AARCH64_FIELD ( 7, 3), /* SME_Zn4: Z0-Z31, multiple of 4, bits [9:7].  */
    AARCH64_FIELD ( 6, 3), /* SME_Zn6_3: Z0-Z15/Z16-Z31, multiple of 2, bits [8:6].  */
    AARCH64_FIELD ( 4, 1), /* SME_ZtT: upper bit of Zt, bit [4].  */
    AARCH64_FIELD ( 0, 3), /* SME_Zt3: lower 3 bits of Zt, bits [2:0].  */
    AARCH64_FIELD ( 0, 2), /* SME_Zt2: lower 2 bits of Zt, bits [1:0].  */
    AARCH64_FIELD (23, 1), /* SME_i1: immediate field, bit 23.  */
    AARCH64_FIELD (12, 2), /* SME_size_12: bits [13:12].  */
    AARCH64_FIELD (22, 2), /* SME_size_22: size<1>, size<0> class field, [23:22].  */
    AARCH64_FIELD (23, 1), /* SME_sz_23: bit [23].  */
    AARCH64_FIELD (22, 1), /* SME_tszh: immediate and qualifier field, bit 22.  */
    AARCH64_FIELD (18, 3), /* SME_tszl: immediate and qualifier field, bits [20:18].  */
    AARCH64_FIELD (0,  8), /* SME_zero_mask: list of up to 8 tile names separated by commas [7:0].  */
    AARCH64_FIELD ( 4, 1), /* SVE_M_4: Merge/zero select, bit 4.  */
    AARCH64_FIELD (14, 1), /* SVE_M_14: Merge/zero select, bit 14.  */
    AARCH64_FIELD (16, 1), /* SVE_M_16: Merge/zero select, bit 16.  */
    AARCH64_FIELD (17, 1), /* SVE_N: SVE equivalent of N.  */
    AARCH64_FIELD ( 0, 4), /* SVE_Pd: p0-p15, bits [3,0].  */
    AARCH64_FIELD (10, 3), /* SVE_Pg3: p0-p7, bits [12,10].  */
    AARCH64_FIELD ( 5, 4), /* SVE_Pg4_5: p0-p15, bits [8,5].  */
    AARCH64_FIELD (10, 4), /* SVE_Pg4_10: p0-p15, bits [13,10].  */
    AARCH64_FIELD (16, 4), /* SVE_Pg4_16: p0-p15, bits [19,16].  */
    AARCH64_FIELD (16, 4), /* SVE_Pm: p0-p15, bits [19,16].  */
    AARCH64_FIELD ( 5, 4), /* SVE_Pn: p0-p15, bits [8,5].  */
    AARCH64_FIELD ( 0, 4), /* SVE_Pt: p0-p15, bits [3,0].  */
    AARCH64_FIELD ( 5, 5), /* SVE_Rm: SVE alternative position for Rm.  */
    AARCH64_FIELD (16, 5), /* SVE_Rn: SVE alternative position for Rn.  */
    AARCH64_FIELD ( 0, 5), /* SVE_Vd: Scalar SIMD&FP register, bits [4,0].  */
    AARCH64_FIELD ( 5, 5), /* SVE_Vm: Scalar SIMD&FP register, bits [9,5].  */
    AARCH64_FIELD ( 5, 5), /* SVE_Vn: Scalar SIMD&FP register, bits [9,5].  */
    AARCH64_FIELD ( 5, 5), /* SVE_Za_5: SVE vector register, bits [9,5].  */
    AARCH64_FIELD (16, 5), /* SVE_Za_16: SVE vector register, bits [20,16].  */
    AARCH64_FIELD ( 0, 5), /* SVE_Zd: SVE vector register. bits [4,0].  */
    AARCH64_FIELD ( 5, 5), /* SVE_Zm_5: SVE vector register, bits [9,5].  */
    AARCH64_FIELD (16, 5), /* SVE_Zm_16: SVE vector register, bits [20,16]. */
    AARCH64_FIELD ( 5, 5), /* SVE_Zn: SVE vector register, bits [9,5].  */
    AARCH64_FIELD ( 0, 5), /* SVE_Zt: SVE vector register, bits [4,0].  */
    AARCH64_FIELD ( 5, 1), /* SVE_i1: single-bit immediate.  */
    AARCH64_FIELD (23, 1), /* SVE_i1_23: single-bit immediate.  */
    AARCH64_FIELD (22, 2), /* SVE_i2: 2-bit index, bits [23,22].  */
    AARCH64_FIELD (20, 1), /* SVE_i2h: high bit of 2bit immediate, bits.  */
    AARCH64_FIELD (22, 1), /* SVE_i3h: high bit of 3-bit immediate.  */
    AARCH64_FIELD (19, 2), /* SVE_i3h2: two high bits of 3bit immediate, bits [20,19].  */
    AARCH64_FIELD (22, 2), /* SVE_i3h3: two high bits of 3bit immediate, bits [22,23].  */
    AARCH64_FIELD (11, 1), /* SVE_i3l: low bit of 3-bit immediate.  */
    AARCH64_FIELD (12, 1), /* SVE_i3l2: low bit of 3-bit immediate, bit 12.  */
    AARCH64_FIELD (10, 2), /* SVE_i4l2: two low bits of 4bit immediate, bits [11,10].  */
    AARCH64_FIELD (16, 3), /* SVE_imm3: 3-bit immediate field.  */
    AARCH64_FIELD (16, 4), /* SVE_imm4: 4-bit immediate field.  */
    AARCH64_FIELD ( 5, 5), /* SVE_imm5: 5-bit immediate field.  */
    AARCH64_FIELD (16, 5), /* SVE_imm5b: secondary 5-bit immediate field.  */
    AARCH64_FIELD (16, 6), /* SVE_imm6: 6-bit immediate field.  */
    AARCH64_FIELD (14, 7), /* SVE_imm7: 7-bit immediate field.  */
    AARCH64_FIELD ( 5, 8), /* SVE_imm8: 8-bit immediate field.  */
    AARCH64_FIELD ( 5, 9), /* SVE_imm9: 9-bit immediate field.  */
    AARCH64_FIELD (11, 6), /* SVE_immr: SVE equivalent of immr.  */
    AARCH64_FIELD ( 5, 6), /* SVE_imms: SVE equivalent of imms.  */
    AARCH64_FIELD (10, 2), /* SVE_msz: 2-bit shift amount for ADR.  */
    AARCH64_FIELD ( 5, 5), /* SVE_pattern: vector pattern enumeration.  */
    AARCH64_FIELD ( 0, 4), /* SVE_prfop: prefetch operation for SVE PRF[BHWD].  */
    AARCH64_FIELD (16, 1), /* SVE_rot1: 1-bit rotation amount.  */
    AARCH64_FIELD (10, 2), /* SVE_rot2: 2-bit rotation amount.  */
    AARCH64_FIELD (10, 1), /* SVE_rot3: 1-bit rotation amount at bit 10.  */
    AARCH64_FIELD (17, 2), /* SVE_size: 2-bit element size, bits [18,17].  */
    AARCH64_FIELD (22, 1), /* SVE_sz: 1-bit element size select.  */
    AARCH64_FIELD (30, 1), /* SVE_sz2: 1-bit element size select.  */
    AARCH64_FIELD (17, 1), /* SVE_sz3: 1-bit element size select.  */
    AARCH64_FIELD (14, 1), /* SVE_sz4: 1-bit element size select.  */
    AARCH64_FIELD (16, 4), /* SVE_tsz: triangular size select.  */
    AARCH64_FIELD (22, 2), /* SVE_tszh: triangular size select high, bits [23,22].  */
    AARCH64_FIELD ( 8, 2), /* SVE_tszl_8: triangular size select low, bits [9,8].  */
    AARCH64_FIELD (19, 2), /* SVE_tszl_19: triangular size select low, bits [20,19].  */
    AARCH64_FIELD (14, 1), /* SVE_xs_14: UXTW/SXTW select (bit 14).  */
    AARCH64_FIELD (22, 1), /* SVE_xs_22: UXTW/SXTW select (bit 22).  */
    AARCH64_FIELD (22, 1), /* S_imm10: in LDRAA and LDRAB instructions.  */
    AARCH64_FIELD (16, 3), /* abc: a:b:c bits in AdvSIMD modified immediate.  */
    AARCH64_FIELD (13, 3), /* asisdlso_opcode: opcode in advsimd ld/st single element.  */
    AARCH64_FIELD (19, 5), /* b40: in the test bit and branch instructions.  */
    AARCH64_FIELD (31, 1), /* b5: in the test bit and branch instructions.  */
    AARCH64_FIELD (12, 4), /* cmode: in advsimd modified immediate instructions.  */
    AARCH64_FIELD (12, 4), /* cond: condition flags as a source operand.  */
    AARCH64_FIELD ( 0, 4), /* cond2: condition in truly conditional-executed inst.  */
    AARCH64_FIELD ( 5, 5), /* defgh: d:e:f:g:h bits in AdvSIMD modified immediate.  */
    AARCH64_FIELD (21, 2), /* hw: in move wide constant instructions.  */
    AARCH64_FIELD ( 0, 1), /* imm1_0: general immediate in bits [0].  */
    AARCH64_FIELD ( 2, 1), /* imm1_2: general immediate in bits [2].  */
    AARCH64_FIELD ( 3, 1), /* imm1_3: general immediate in bits [3].  */
    AARCH64_FIELD ( 8, 1), /* imm1_8: general immediate in bits [8].  */
    AARCH64_FIELD (10, 1), /* imm1_10: general immediate in bits [10].  */
    AARCH64_FIELD (14, 1), /* imm1_14: general immediate in bits [14].  */
    AARCH64_FIELD (15, 1), /* imm1_15: general immediate in bits [15].  */
    AARCH64_FIELD (16, 1), /* imm1_16: general immediate in bits [16].  */
    AARCH64_FIELD (22, 1), /* imm1_22: general immediate in bits [22].  */
    AARCH64_FIELD ( 0, 2), /* imm2_0: general immediate in bits [1:0].  */
    AARCH64_FIELD ( 1, 2), /* imm2_1: general immediate in bits [2:1].  */
    AARCH64_FIELD ( 2, 2), /* imm2_2: general immediate in bits [3:2].  */
    AARCH64_FIELD ( 4, 2), /* imm2_4: general immediate in bits [5:4].  */
    AARCH64_FIELD ( 8, 2), /* imm2_8: general immediate in bits [9:8].  */
    AARCH64_FIELD (10, 2), /* imm2_10: 2-bit immediate, bits [11:10] */
    AARCH64_FIELD (12, 2), /* imm2_12: 2-bit immediate, bits [13:12] */
    AARCH64_FIELD (13, 2), /* imm2_13: 2-bit immediate, bits [14:13] */
    AARCH64_FIELD (15, 2), /* imm2_15: 2-bit immediate, bits [16:15] */
    AARCH64_FIELD (16, 2), /* imm2_16: 2-bit immediate, bits [17:16] */
    AARCH64_FIELD (19, 2), /* imm2_19: 2-bit immediate, bits [20:19] */
    AARCH64_FIELD ( 0, 3), /* imm3_0: general immediate in bits [2:0].  */
    AARCH64_FIELD ( 5, 3), /* imm3_5: general immediate in bits [7:5].  */
    AARCH64_FIELD (10, 3), /* imm3_10: in add/sub extended reg instructions.  */
    AARCH64_FIELD (12, 3), /* imm3_12: general immediate in bits [14:12].  */
    AARCH64_FIELD (14, 3), /* imm3_14: general immediate in bits [16:14].  */
    AARCH64_FIELD (15, 3), /* imm3_15: general immediate in bits [17:15].  */
    AARCH64_FIELD (19, 3), /* imm3_19: general immediate in bits [21:19].  */
    AARCH64_FIELD ( 0, 4), /* imm4_0: in rmif instructions.  */
    AARCH64_FIELD ( 5, 4), /* imm4_5: in SME instructions.  */
    AARCH64_FIELD (10, 4), /* imm4_10: in adddg/subg instructions.  */
    AARCH64_FIELD (11, 4), /* imm4_11: in advsimd ext and advsimd ins instructions.  */
    AARCH64_FIELD (14, 4), /* imm4_14: general immediate in bits [17:14].  */
    AARCH64_FIELD (16, 5), /* imm5: in conditional compare (immediate) instructions.  */
    AARCH64_FIELD (10, 6), /* imm6_10: in add/sub reg shifted instructions.  */
    AARCH64_FIELD (15, 6), /* imm6_15: in rmif instructions.  */
    AARCH64_FIELD (15, 7), /* imm7: in load/store pair pre/post index instructions.  */
    AARCH64_FIELD (13, 8), /* imm8: in floating-point scalar move immediate inst.  */
    AARCH64_FIELD (12, 9), /* imm9: in load/store pre/post index instructions.  */
    AARCH64_FIELD ( 5, 9), /* imm9_5: in CB<cc> (immediate).  */
    AARCH64_FIELD (10,12), /* imm12: in ld/st unsigned imm or add/sub shifted inst.  */
    AARCH64_FIELD ( 5,14), /* imm14: in test bit and branch instructions.  */
    AARCH64_FIELD ( 0,16), /* imm16_0: in udf instruction. */
    AARCH64_FIELD ( 5,16), /* imm16_5: in exception instructions.  */
    AARCH64_FIELD (17, 1), /* imm17_1: in 1 bit element index.  */
    AARCH64_FIELD (17, 2), /* imm17_2: in 2 bits element index.  */
    AARCH64_FIELD ( 5,19), /* imm19: e.g. in CBZ.  */
    AARCH64_FIELD ( 0,26), /* imm26: in unconditional branch instructions.  */
    AARCH64_FIELD (16, 3), /* immb: in advsimd shift by immediate instructions.  */
    AARCH64_FIELD (19, 4), /* immh: in advsimd shift by immediate instructions.  */
    AARCH64_FIELD ( 5,19), /* immhi: e.g. in ADRP.  */
    AARCH64_FIELD (29, 2), /* immlo: e.g. in ADRP.  */
    AARCH64_FIELD (16, 6), /* immr: in bitfield and logical immediate instructions.  */
    AARCH64_FIELD (10, 6), /* imms: in bitfield and logical immediate instructions.  */
    AARCH64_FIELD (11, 1), /* index: in ld/st inst deciding the pre/post-index.  */
    AARCH64_FIELD (24, 1), /* index2: in ld/st pair inst deciding the pre/post-index.  */
    AARCH64_FIELD (30, 2), /* ldst_size: size field in ld/st reg offset inst.  */
    AARCH64_FIELD (13, 2), /* len: in advsimd tbl/tbx instructions.  */
    AARCH64_FIELD (30, 1), /* lse_sz: in LSE extension atomic instructions.  */
    AARCH64_FIELD ( 0, 4), /* nzcv: flag bit specifier, encoded in the "nzcv" field.  */
    AARCH64_FIELD (29, 1), /* op: in AdvSIMD modified immediate instructions.  */
    AARCH64_FIELD (19, 2), /* op0: in the system instructions.  */
    AARCH64_FIELD (16, 3), /* op1: in the system instructions.  */
    AARCH64_FIELD ( 5, 3), /* op2: in the system instructions.  */
    AARCH64_FIELD (22, 2), /* opc: in load/store reg offset instructions.  */
    AARCH64_FIELD (23, 1), /* opc1: in load/store reg offset instructions.  */
    AARCH64_FIELD (12, 4), /* opcode: in advsimd load/store instructions.  */
    AARCH64_FIELD (13, 3), /* option: in ld/st reg offset + add/sub extended reg inst.  */
    AARCH64_FIELD (11, 2), /* rotate1: FCMLA immediate rotate.  */
    AARCH64_FIELD (13, 2), /* rotate2: Indexed element FCMLA immediate rotate.  */
    AARCH64_FIELD (12, 1), /* rotate3: FCADD immediate rotate.  */
    AARCH64_FIELD (10, 6), /* scale: in the fixed-point scalar to fp converting inst.  */
    AARCH64_FIELD (31, 1), /* sf: in integer data processing instructions.  */
    AARCH64_FIELD (22, 2), /* shift: in add/sub reg/imm shifted instructions.  */
    AARCH64_FIELD (22, 2), /* size: in most AdvSIMD and floating-point instructions.  */
    AARCH64_FIELD (22, 1), /* sz: 1-bit element size select.  */
    AARCH64_FIELD (22, 2), /* type: floating point type field in fp data inst.  */
    AARCH64_FIELD (10, 2), /* vldst_size: size field in the AdvSIMD load/store inst.  */
    AARCH64_FIELD ( 5, 3), /* off3: immediate offset used to calculate slice number in a ZA tile.  */
    AARCH64_FIELD ( 5, 2), /* off2: immediate offset used to calculate slice number in a ZA tile.  */
    AARCH64_FIELD ( 7, 1), /* ZAn_1: name of the 1bit encoded ZA tile.  */
    AARCH64_FIELD ( 5, 1), /* ol: immediate offset used to calculate slice number in a ZA tile. */
    AARCH64_FIELD ( 6, 2), /* ZAn_2: name of the 2bit encoded ZA tile.  */
    AARCH64_FIELD ( 5, 3), /* ZAn_3: name of the 3bit encoded ZA tile.  */
    AARCH64_FIELD ( 6, 1), /* ZAn: name of the bit encoded ZA tile.  */
    AARCH64_FIELD (12, 4), /* opc2: in rcpc3 ld/st inst deciding the pre/post-index.  */
    AARCH64_FIELD (30, 2), /* rcpc3_size: in rcpc3 ld/st, field controls Rt/Rt2 width.  */
    AARCH64_FIELD ( 5, 1), /* FLD_brbop: used in BRB to mean IALL or INJ.  */
    AARCH64_FIELD ( 8, 1), /* ZA8_1: name of the 1 bit encoded ZA tile ZA0-ZA1.  */
    AARCH64_FIELD ( 7, 2), /* ZA7_2: name of the 2 bits encoded ZA tile ZA0-ZA3.  */
    AARCH64_FIELD ( 6, 3), /* ZA6_3: name of the 3 bits encoded ZA tile ZA0-ZA7.  */
    AARCH64_FIELD ( 5, 4), /* ZA5_4: name of the 4 bits encoded ZA tile ZA0-ZA15.  */
};

#endif //OPCODES_AARCH64_INSN_BITS_H
