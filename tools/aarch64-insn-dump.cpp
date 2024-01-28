#define VERIFIER(x) NULL

#include "bfd.h"
#include "dis-asm.h"
#include "aarch64-tbl.h"

#include <cstdio>
#include <stdexcept>
#include <vector>
#include <string>

const char* iclass_name(enum aarch64_insn_class c) {
    switch (c)
    {
        case aarch64_misc: return "AARCH64_MISC";
        case addsub_carry: return "ADDSUB_CARRY";
        case addsub_ext: return "ADDSUB_EXT";
        case addsub_imm: return "ADDSUB_IMM";
        case addsub_shift: return "ADDSUB_SHIFT";
        case asimdall: return "ASIMDALL";
        case asimddiff: return "ASIMDDIFF";
        case asimdelem: return "ASIMDELEM";
        case asimdext: return "ASIMDEXT";
        case asimdimm: return "ASIMDIMM";
        case asimdins: return "ASIMDINS";
        case asimdmisc: return "ASIMDMISC";
        case asimdperm: return "ASIMDPERM";
        case asimdsame: return "ASIMDSAME";
        case asimdshf: return "ASIMDSHF";
        case asimdtbl: return "ASIMDTBL";
        case asisddiff: return "ASISDDIFF";
        case asisdelem: return "ASISDELEM";
        case asisdlse: return "ASISDLSE";
        case asisdlsep: return "ASISDLSEP";
        case asisdlso: return "ASISDLSO";
        case asisdlsop: return "ASISDLSOP";
        case asisdmisc: return "ASISDMISC";
        case asisdone: return "ASISDONE";
        case asisdpair: return "ASISDPAIR";
        case asisdsame: return "ASISDSAME";
        case asisdshf: return "ASISDSHF";
        case bitfield: return "BITFIELD";
        case branch_imm: return "BRANCH_IMM";
        case branch_reg: return "BRANCH_REG";
        case compbranch: return "COMPBRANCH";
        case condbranch: return "CONDBRANCH";
        case condcmp_imm: return "CONDCMP_IMM";
        case condcmp_reg: return "CONDCMP_REG";
        case condsel: return "CONDSEL";
        case cryptoaes: return "CRYPTOAES";
        case cryptosha2: return "CRYPTOSHA2";
        case cryptosha3: return "CRYPTOSHA3";
        case dp_1src: return "DP_1SRC";
        case dp_2src: return "DP_2SRC";
        case dp_3src: return "DP_3SRC";
        case exception: return "EXCEPTION";
        case extract: return "EXTRACT";
        case float2fix: return "FLOAT2FIX";
        case float2int: return "FLOAT2INT";
        case floatccmp: return "FLOATCCMP";
        case floatcmp: return "FLOATCMP";
        case floatdp1: return "FLOATDP1";
        case floatdp2: return "FLOATDP2";
        case floatdp3: return "FLOATDP3";
        case floatimm: return "FLOATIMM";
        case floatsel: return "FLOATSEL";
        case ldst_immpost: return "LDST_IMMPOST";
        case ldst_immpre: return "LDST_IMMPRE";
        case ldst_imm9: return "LDST_IMM9";
        case ldst_imm10: return "LDST_IMM10";
        case ldst_pos: return "LDST_POS";
        case ldst_regoff: return "LDST_REGOFF";
        case ldst_unpriv: return "LDST_UNPRIV";
        case ldst_unscaled: return "LDST_UNSCALED";
        case ldstexcl: return "LDSTEXCL";
        case ldstnapair_offs: return "LDSTNAPAIR_OFFS";
        case ldstpair_off: return "LDSTPAIR_OFF";
        case ldstpair_indexed: return "LDSTPAIR_INDEXED";
        case loadlit: return "LOADLIT";
        case log_imm: return "LOG_IMM";
        case log_shift: return "LOG_SHIFT";
        case lse_atomic: return "LSE_ATOMIC";
        case movewide: return "MOVEWIDE";
        case pcreladdr: return "PCRELADDR";
        case ic_system: return "IC_SYSTEM";
        case sme_fp_sd: return "SME_FP_SD";
        case sme_int_sd: return "SME_INT_SD";
        case sme_misc: return "SME_MISC";
        case sme_mov: return "SME_MOV";
        case sme_ldr: return "SME_LDR";
        case sme_psel: return "SME_PSEL";
        case sme_shift: return "SME_SHIFT";
        case sme_size_12_bhs: return "SME_SIZE_12_BHS";
        case sme_size_12_hs: return "SME_SIZE_12_HS";
        case sme_size_22: return "SME_SIZE_22";
        case sme_size_22_hsd: return "SME_SIZE_22_HSD";
        case sme_sz_23: return "SME_SZ_23";
        case sme_str: return "SME_STR";
        case sme_start: return "SME_START";
        case sme_stop: return "SME_STOP";
        case sme2_mov: return "SME2_MOV";
        case sve_cpy: return "SVE_CPY";
        case sve_index: return "SVE_INDEX";
        case sve_limm: return "SVE_LIMM";
        case sve_misc: return "SVE_MISC";
        case sve_movprfx: return "SVE_MOVPRFX";
        case sve_pred_zm: return "SVE_PRED_ZM";
        case sve_shift_pred: return "SVE_SHIFT_PRED";
        case sve_shift_unpred: return "SVE_SHIFT_UNPRED";
        case sve_size_bhs: return "SVE_SIZE_BHS";
        case sve_size_bhsd: return "SVE_SIZE_BHSD";
        case sve_size_hsd: return "SVE_SIZE_HSD";
        case sve_size_hsd2: return "SVE_SIZE_HSD2";
        case sve_size_sd: return "SVE_SIZE_SD";
        case sve_size_bh: return "SVE_SIZE_BH";
        case sve_size_sd2: return "SVE_SIZE_SD2";
        case sve_size_13: return "SVE_SIZE_13";
        case sve_shift_tsz_hsd: return "SVE_SHIFT_TSZ_HSD";
        case sve_shift_tsz_bhsd: return "SVE_SHIFT_TSZ_BHSD";
        case sve_size_tsz_bhs: return "SVE_SIZE_TSZ_BHS";
        case testbranch: return "TESTBRANCH";
        case cryptosm3: return "CRYPTOSM3";
        case cryptosm4: return "CRYPTOSM4";
        case dotproduct: return "DOTPRODUCT";
        case bfloat16: return "BFLOAT16";
        case cssc: return "CSSC";

        default: throw std::runtime_error("unknown error class");
      }
}

const char* iclass_description(const aarch64_insn_class c) {
    switch (c) {
        case aarch64_misc: return "Misc. instructions";
        case addsub_carry: return "Add/subtract (with carry)";
        case addsub_ext: return "Add/subtract (extended register)";
        case addsub_imm: return "Add/subtract (immediate)";
        case addsub_shift: return "Add/subtract (shifted register)";
        case asimdall: return "AdvSIMD across lanes";
        case asimddiff: return "AdvSIMD three different";
        case asimdelem: return "AdvSIMD vector x indexed element";
        case asimdext: return "AdvSIMD EXT";
        case asimdimm: return "AdvSIMD modified immediate";
        case asimdins: return "AdvSIMD copy";
        case asimdmisc: return "AdvSIMD two-reg misc";
        case asimdperm: return "AdvSIMD ZIP/UZP/TRN";
        case asimdsame: return "AdvSIMD three same";
        case asimdshf: return "AdvSIMD shift by immediate";
        case asimdtbl: return "AdvSIMD TBL/TBX";
        case asisddiff: return "AdvSIMD scalar three different";
        case asisdelem: return "AdvSIMD scalar x indexed element";
        case asisdlse: return "AdvSIMD load/store multiple structures";
        case asisdlsep: return "AdvSIMD load/store multiple structures (post-indexed)";
        case asisdlso: return "AdvSIMD load/store single structure";
        case asisdlsop: return "AdvSIMD load/store single structure (post-indexed)";
        case asisdmisc: return "AdvSIMD scalar two-reg misc";
        case asisdone: return "AdvSIMD scalar copy";
        case asisdpair: return "AdvSIMD scalar pairwise";
        case asisdsame: return "AdvSIMD scalar three same";
        case asisdshf: return "AdvSIMD scalar shift by immediate";
        case bfloat16: return "BFloat Advanced SIMD instructions";
        case bitfield: return "Bitfield";
        case branch_imm: return "Unconditional branch (immediate)";
        case branch_reg: return "Unconditional branch (register)";
        case compbranch: return "Compare & branch (immediate)";
        case condbranch: return "Conditional branch (immediate)";
        case condcmp_imm: return "Conditional compare (immediate)";
        case condcmp_reg: return "Conditional compare (register)";
        case condsel: return "Conditional select";
        case cryptoaes: return "Crypto AES";
        case cryptosha2: return "Crypto two-reg SHA";
        case cryptosha3: return "Crypto three-reg SHA";
        case cryptosm3: return "Crypto SM3 (optional in ARMv8.2-a)";
        case cryptosm4: return "Crypto SM4 (optional in ARMv8.2-a)";
        case cssc: return "Common Short Sequence Compression";
        case dotproduct: return "SIMD Dot Product (optional in v8.2-A)";
        case dp_1src: return "Data-processing (1 source)";
        case dp_2src: return "Data-processing (2 source)";
        case dp_3src: return "Data-processing (3 source)";
        case exception: return "Exception generation";
        case extract: return "Extract";
        case float2fix: return "Floating-point<->fixed-point conversions";
        case float2int: return "Floating-point<->integer conversions";
        case floatccmp: return "Floating-point conditional compare";
        case floatcmp: return "Floating-point compare";
        case floatdp1: return "Floating-point data-processing (1 source)";
        case floatdp2: return "Floating-point data-processing (2 source)";
        case floatdp3: return "Floating-point data-processing (3 source)";
        case floatimm: return "Floating-point immediate";
        case floatsel: return "Floating-point conditional select";
        case ic_system: return "System instructions";
        case ldst_imm10: return "Load/store register (scaled signed immediate)";
        case ldst_imm9: return "Load/store register (immediate indexed)";
        case ldst_pos: return "Load/store register (unsigned immediate)";
        case ldst_regoff: return "Load/store register (register offset)";
        case ldst_unpriv: return "Load/store register (unprivileged)";
        case ldst_unscaled: return "Load/store register (unscaled immediate)";
        case ldstexcl: return "Load/store exclusive";
        case ldstnapair_offs: return "Load/store no-allocate pair (offset)";
        case ldstpair_indexed: return "Load/store register pair (indexed)";
        case ldstpair_off: return "Load/store register pair (offset)";
        case loadlit: return "Load register (literal)";
        case log_imm: return "Logical (immediate)";
        case log_shift: return "Logical (shifted register)";
        case lse_atomic: return "LSE extension (atomic)";
        case movewide: return "Move wide (immediate)";
        case pcreladdr: return "PC-rel. addressing";
        case sme_fp_sd:
        case sme_int_sd:
        case sme_misc:
        case sme_mov:
        case sme_ldr:
        case sme_psel:
        case sme_shift:
        case sme_size_12_bhs:
        case sme_size_12_hs:
        case sme_size_22:
        case sme_size_22_hsd:
        case sme_sz_23:
        case sme_str:
        case sme_start:
        case sme_stop:
        case sme2_mov:
            return "SME instructions";
        case sve_cpy:
        case sve_index:
        case sve_limm:
        case sve_misc:
        case sve_movprfx:
        case sve_pred_zm:
        case sve_shift_pred:
        case sve_shift_unpred:
        case sve_size_bhs:
        case sve_size_bhsd:
        case sve_size_hsd:
        case sve_size_hsd2:
        case sve_size_sd:
        case sve_size_bh:
        case sve_size_sd2:
        case sve_size_13:
        case sve_shift_tsz_hsd:
        case sve_shift_tsz_bhsd:
        case sve_size_tsz_bhs:
            return "SVE instructions";
        case testbranch: return "Test & branch (immediate)";

        default: throw std::runtime_error("no description");
    }
}

const char* specifics_name(const aarch64_op op) {
    switch (op) {
        case OP_NIL: return "NONE";
        case OP_STRB_POS: return "STRB_POS";
        case OP_LDRB_POS: return "LDRB_POS";
        case OP_LDRSB_POS: return "LDRSB_POS";
        case OP_STRH_POS: return "STRH_POS";
        case OP_LDRH_POS: return "LDRH_POS";
        case OP_LDRSH_POS: return "LDRSH_POS";
        case OP_STR_POS: return "STR_POS";
        case OP_LDR_POS: return "LDR_POS";
        case OP_STRF_POS: return "STRF_POS";
        case OP_LDRF_POS: return "LDRF_POS";
        case OP_LDRSW_POS: return "LDRSW_POS";
        case OP_PRFM_POS: return "PRFM_POS";
        case OP_STURB: return "STURB";
        case OP_LDURB: return "LDURB";
        case OP_LDURSB: return "LDURSB";
        case OP_STURH: return "STURH";
        case OP_LDURH: return "LDURH";
        case OP_LDURSH: return "LDURSH";
        case OP_STUR: return "STUR";
        case OP_LDUR: return "LDUR";
        case OP_STURV: return "STURV";
        case OP_LDURV: return "LDURV";
        case OP_LDURSW: return "LDURSW";
        case OP_PRFUM: return "PRFUM";
        case OP_LDR_LIT: return "LDR_LIT";
        case OP_LDRV_LIT: return "LDRV_LIT";
        case OP_LDRSW_LIT: return "LDRSW_LIT";
        case OP_PRFM_LIT: return "PRFM_LIT";
        case OP_ADD: return "ADD";
        case OP_B: return "B";
        case OP_BL: return "BL";
        case OP_MOVN: return "MOVN";
        case OP_MOVZ: return "MOVZ";
        case OP_MOVK: return "MOVK";
        case OP_MOV_IMM_LOG: return "MOV_IMM_LOG";
        case OP_MOV_IMM_WIDE: return "MOV_IMM_WIDE";
        case OP_MOV_IMM_WIDEN: return "MOV_IMM_WIDEN";
        case OP_MOV_V: return "MOV_V";
        case OP_ASR_IMM: return "ASR_IMM";
        case OP_LSR_IMM: return "LSR_IMM";
        case OP_LSL_IMM: return "LSL_IMM";
        case OP_BIC: return "BIC";
        case OP_UBFX: return "UBFX";
        case OP_BFXIL: return "BFXIL";
        case OP_SBFX: return "SBFX";
        case OP_SBFIZ: return "SBFIZ";
        case OP_BFI: return "BFI";
        case OP_BFC: return "BFC";
        case OP_UBFIZ: return "UBFIZ";
        case OP_UXTB: return "UXTB";
        case OP_UXTH: return "UXTH";
        case OP_UXTW: return "UXTW";
        case OP_CINC: return "CINC";
        case OP_CINV: return "CINV";
        case OP_CNEG: return "CNEG";
        case OP_CSET: return "CSET";
        case OP_CSETM: return "CSETM";
        case OP_FCVT: return "FCVT";
        case OP_FCVTN: return "FCVTN";
        case OP_FCVTN2: return "FCVTN2";
        case OP_FCVTL: return "FCVTL";
        case OP_FCVTL2: return "FCVTL2";
        case OP_FCVTXN_S: return "FCVTXN_S";
        case OP_ROR_IMM: return "ROR_IMM";
        case OP_SXTL: return "SXTL";
        case OP_SXTL2: return "SXTL2";
        case OP_UXTL: return "UXTL";
        case OP_UXTL2: return "UXTL2";
        case OP_MOV_P_P: return "MOV_P_P";
        case OP_MOV_PN_PN: return "MOV_PN_PN";
        case OP_MOV_Z_P_Z: return "MOV_Z_P_Z";
        case OP_MOV_Z_V: return "MOV_Z_V";
        case OP_MOV_Z_Z: return "MOV_Z_Z";
        case OP_MOV_Z_Zi: return "MOV_Z_Zi";
        case OP_MOVM_P_P_P: return "MOVM_P_P_P";
        case OP_MOVS_P_P: return "MOVS_P_P";
        case OP_MOVZS_P_P_P: return "MOVZS_P_P_P";
        case OP_MOVZ_P_P_P: return "MOVZ_P_P_P";
        case OP_NOTS_P_P_P_Z: return "NOTS_P_P_P_Z";
        case OP_NOT_P_P_P_Z: return "NOT_P_P_P_Z";
        case OP_FCMLA_ELEM: return "FCMLA_ELEM";

        default: throw std::runtime_error("unknown enumerator");
    }
}

const char* operand_name(const aarch64_opnd o) {
    switch (o) {
          case AARCH64_OPND_NIL: return "NONE";
          case AARCH64_OPND_Rd: return "Rd";
          case AARCH64_OPND_Rn: return "Rn";
          case AARCH64_OPND_Rm: return "Rm";
          case AARCH64_OPND_Rt: return "Rt";
          case AARCH64_OPND_Rt2: return "Rt2";
          case AARCH64_OPND_Rt_LS64: return "Rt_LS64";
          case AARCH64_OPND_Rt_SP: return "Rt_SP";
          case AARCH64_OPND_Rs: return "Rs";
          case AARCH64_OPND_Ra: return "Ra";
          case AARCH64_OPND_Rt_SYS: return "Rt_SYS";
          case AARCH64_OPND_Rd_SP: return "Rd_SP";
          case AARCH64_OPND_Rn_SP: return "Rn_SP";
          case AARCH64_OPND_Rm_SP: return "Rm_SP";
          case AARCH64_OPND_PAIRREG: return "PAIRREG";
          case AARCH64_OPND_Rm_EXT: return "Rm_EXT";
          case AARCH64_OPND_Rm_SFT: return "Rm_SFT";
          case AARCH64_OPND_Fd: return "Fd";
          case AARCH64_OPND_Fn: return "Fn";
          case AARCH64_OPND_Fm: return "Fm";
          case AARCH64_OPND_Fa: return "Fa";
          case AARCH64_OPND_Ft: return "Ft";
          case AARCH64_OPND_Ft2: return "Ft2";
          case AARCH64_OPND_Sd: return "Sd";
          case AARCH64_OPND_Sn: return "Sn";
          case AARCH64_OPND_Sm: return "Sm";
          case AARCH64_OPND_Va: return "Va";
          case AARCH64_OPND_Vd: return "Vd";
          case AARCH64_OPND_Vn: return "Vn";
          case AARCH64_OPND_Vm: return "Vm";
          case AARCH64_OPND_VdD1: return "VdD1";
          case AARCH64_OPND_VnD1: return "VnD1";
          case AARCH64_OPND_Ed: return "Ed";
          case AARCH64_OPND_En: return "En";
          case AARCH64_OPND_Em: return "Em";
          case AARCH64_OPND_Em16: return "Em16";
          case AARCH64_OPND_LVn: return "LVn";
          case AARCH64_OPND_LVt: return "LVt";
          case AARCH64_OPND_LVt_AL: return "LVt_AL";
          case AARCH64_OPND_LEt: return "LEt";
          case AARCH64_OPND_CRn: return "CRn";
          case AARCH64_OPND_CRm: return "CRm";
          case AARCH64_OPND_IDX: return "IDX";
          case AARCH64_OPND_MASK: return "MASK";
          case AARCH64_OPND_IMM_VLSL: return "IMM_VLSL";
          case AARCH64_OPND_IMM_VLSR: return "IMM_VLSR";
          case AARCH64_OPND_SIMD_IMM: return "SIMD_IMM";
          case AARCH64_OPND_SIMD_IMM_SFT: return "SIMD_IMM_SFT";
          case AARCH64_OPND_SIMD_FPIMM: return "SIMD_FPIMM";
          case AARCH64_OPND_SHLL_IMM: return "SHLL_IMM";
          case AARCH64_OPND_IMM0: return "IMM0";
          case AARCH64_OPND_FPIMM0: return "FPIMM0";
          case AARCH64_OPND_FPIMM: return "FPIMM";
          case AARCH64_OPND_IMMR: return "IMMR";
          case AARCH64_OPND_IMMS: return "IMMS";
          case AARCH64_OPND_WIDTH: return "WIDTH";
          case AARCH64_OPND_IMM: return "IMM";
          case AARCH64_OPND_IMM_2: return "IMM_2";
          case AARCH64_OPND_UIMM3_OP1: return "UIMM3_OP1";
          case AARCH64_OPND_UIMM3_OP2: return "UIMM3_OP2";
          case AARCH64_OPND_UIMM4: return "UIMM4";
          case AARCH64_OPND_UIMM4_ADDG: return "UIMM4_ADDG";
          case AARCH64_OPND_UIMM7: return "UIMM7";
          case AARCH64_OPND_UIMM10: return "UIMM10";
          case AARCH64_OPND_BIT_NUM: return "BIT_NUM";
          case AARCH64_OPND_EXCEPTION: return "EXCEPTION";
          case AARCH64_OPND_UNDEFINED: return "UNDEFINED";
          case AARCH64_OPND_CCMP_IMM: return "CCMP_IMM";
          case AARCH64_OPND_SIMM5: return "SIMM5";
          case AARCH64_OPND_NZCV: return "NZCV";
          case AARCH64_OPND_LIMM: return "LIMM";
          case AARCH64_OPND_AIMM: return "AIMM";
          case AARCH64_OPND_HALF: return "HALF";
          case AARCH64_OPND_FBITS: return "FBITS";
          case AARCH64_OPND_IMM_MOV: return "IMM_MOV";
          case AARCH64_OPND_IMM_ROT1: return "IMM_ROT1";
          case AARCH64_OPND_IMM_ROT2: return "IMM_ROT2";
          case AARCH64_OPND_IMM_ROT3: return "IMM_ROT3";
          case AARCH64_OPND_COND: return "COND";
          case AARCH64_OPND_COND1: return "COND1";
          case AARCH64_OPND_ADDR_ADRP: return "ADDR_ADRP";
          case AARCH64_OPND_ADDR_PCREL14: return "ADDR_PCREL14";
          case AARCH64_OPND_ADDR_PCREL19: return "ADDR_PCREL19";
          case AARCH64_OPND_ADDR_PCREL21: return "ADDR_PCREL21";
          case AARCH64_OPND_ADDR_PCREL26: return "ADDR_PCREL26";
          case AARCH64_OPND_ADDR_SIMPLE: return "ADDR_SIMPLE";
          case AARCH64_OPND_ADDR_REGOFF: return "ADDR_REGOFF";
          case AARCH64_OPND_ADDR_SIMM7: return "ADDR_SIMM7";
          case AARCH64_OPND_ADDR_SIMM9: return "ADDR_SIMM9";
          case AARCH64_OPND_ADDR_SIMM10: return "ADDR_SIMM10";
          case AARCH64_OPND_ADDR_SIMM11: return "ADDR_SIMM11";
          case AARCH64_OPND_ADDR_UIMM12: return "ADDR_UIMM12";
          case AARCH64_OPND_ADDR_SIMM13: return "ADDR_SIMM13";
          case AARCH64_OPND_SIMD_ADDR_SIMPLE: return "SIMD_ADDR_SIMPLE";
          case AARCH64_OPND_ADDR_OFFSET: return "ADDR_OFFSET";
          case AARCH64_OPND_SIMD_ADDR_POST: return "SIMD_ADDR_POST";
          case AARCH64_OPND_SYSREG: return "SYSREG";
          case AARCH64_OPND_PSTATEFIELD: return "PSTATEFIELD";
          case AARCH64_OPND_SYSREG_AT: return "SYSREG_AT";
          case AARCH64_OPND_SYSREG_DC: return "SYSREG_DC";
          case AARCH64_OPND_SYSREG_IC: return "SYSREG_IC";
          case AARCH64_OPND_SYSREG_TLBI: return "SYSREG_TLBI";
          case AARCH64_OPND_SYSREG_SR: return "SYSREG_SR";
          case AARCH64_OPND_BARRIER: return "BARRIER";
          case AARCH64_OPND_BARRIER_DSB_NXS: return "BARRIER_DSB_NXS";
          case AARCH64_OPND_BARRIER_ISB: return "BARRIER_ISB";
          case AARCH64_OPND_PRFOP: return "PRFOP";
          case AARCH64_OPND_RPRFMOP: return "RPRFMOP";
          case AARCH64_OPND_BARRIER_PSB: return "BARRIER_PSB";
          case AARCH64_OPND_BTI_TARGET: return "BTI_TARGET";
          case AARCH64_OPND_SVE_ADDR_RI_S4x16: return "SVE_ADDR_RI_S4x16";
          case AARCH64_OPND_SVE_ADDR_RI_S4x32: return "SVE_ADDR_RI_S4x32";
          case AARCH64_OPND_SVE_ADDR_RI_S4xVL: return "SVE_ADDR_RI_S4xVL";
          case AARCH64_OPND_SVE_ADDR_RI_S4x2xVL: return "SVE_ADDR_RI_S4x2xVL";
          case AARCH64_OPND_SVE_ADDR_RI_S4x3xVL: return "SVE_ADDR_RI_S4x3xVL";
          case AARCH64_OPND_SVE_ADDR_RI_S4x4xVL: return "SVE_ADDR_RI_S4x4xVL";
          case AARCH64_OPND_SVE_ADDR_RI_S6xVL: return "SVE_ADDR_RI_S6xVL";
          case AARCH64_OPND_SVE_ADDR_RI_S9xVL: return "SVE_ADDR_RI_S9xVL";
          case AARCH64_OPND_SVE_ADDR_RI_U6: return "SVE_ADDR_RI_U6";
          case AARCH64_OPND_SVE_ADDR_RI_U6x2: return "SVE_ADDR_RI_U6x2";
          case AARCH64_OPND_SVE_ADDR_RI_U6x4: return "SVE_ADDR_RI_U6x4";
          case AARCH64_OPND_SVE_ADDR_RI_U6x8: return "SVE_ADDR_RI_U6x8";
          case AARCH64_OPND_SVE_ADDR_R: return "SVE_ADDR_R";
          case AARCH64_OPND_SVE_ADDR_RR: return "SVE_ADDR_RR";
          case AARCH64_OPND_SVE_ADDR_RR_LSL1: return "SVE_ADDR_RR_LSL1";
          case AARCH64_OPND_SVE_ADDR_RR_LSL2: return "SVE_ADDR_RR_LSL2";
          case AARCH64_OPND_SVE_ADDR_RR_LSL3: return "SVE_ADDR_RR_LSL3";
          case AARCH64_OPND_SVE_ADDR_RR_LSL4: return "SVE_ADDR_RR_LSL4";
          case AARCH64_OPND_SVE_ADDR_RX: return "SVE_ADDR_RX";
          case AARCH64_OPND_SVE_ADDR_RX_LSL1: return "SVE_ADDR_RX_LSL1";
          case AARCH64_OPND_SVE_ADDR_RX_LSL2: return "SVE_ADDR_RX_LSL2";
          case AARCH64_OPND_SVE_ADDR_RX_LSL3: return "SVE_ADDR_RX_LSL3";
          case AARCH64_OPND_SVE_ADDR_ZX: return "SVE_ADDR_ZX";
          case AARCH64_OPND_SVE_ADDR_RZ: return "SVE_ADDR_RZ";
          case AARCH64_OPND_SVE_ADDR_RZ_LSL1: return "SVE_ADDR_RZ_LSL1";
          case AARCH64_OPND_SVE_ADDR_RZ_LSL2: return "SVE_ADDR_RZ_LSL2";
          case AARCH64_OPND_SVE_ADDR_RZ_LSL3: return "SVE_ADDR_RZ_LSL3";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW_14: return "SVE_ADDR_RZ_XTW_14";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW_22: return "SVE_ADDR_RZ_XTW_22";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW1_14: return "SVE_ADDR_RZ_XTW1_14";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW1_22: return "SVE_ADDR_RZ_XTW1_22";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW2_14: return "SVE_ADDR_RZ_XTW2_14";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW2_22: return "SVE_ADDR_RZ_XTW2_22";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW3_14: return "SVE_ADDR_RZ_XTW3_14";
          case AARCH64_OPND_SVE_ADDR_RZ_XTW3_22: return "SVE_ADDR_RZ_XTW3_22";
          case AARCH64_OPND_SVE_ADDR_ZI_U5: return "SVE_ADDR_ZI_U5";
          case AARCH64_OPND_SVE_ADDR_ZI_U5x2: return "SVE_ADDR_ZI_U5x2";
          case AARCH64_OPND_SVE_ADDR_ZI_U5x4: return "SVE_ADDR_ZI_U5x4";
          case AARCH64_OPND_SVE_ADDR_ZI_U5x8: return "SVE_ADDR_ZI_U5x8";
          case AARCH64_OPND_SVE_ADDR_ZZ_LSL: return "SVE_ADDR_ZZ_LSL";
          case AARCH64_OPND_SVE_ADDR_ZZ_SXTW: return "SVE_ADDR_ZZ_SXTW";
          case AARCH64_OPND_SVE_ADDR_ZZ_UXTW: return "SVE_ADDR_ZZ_UXTW";
          case AARCH64_OPND_SVE_AIMM: return "SVE_AIMM";
          case AARCH64_OPND_SVE_ASIMM: return "SVE_ASIMM";
          case AARCH64_OPND_SVE_FPIMM8: return "SVE_FPIMM8";
          case AARCH64_OPND_SVE_I1_HALF_ONE: return "SVE_I1_HALF_ONE";
          case AARCH64_OPND_SVE_I1_HALF_TWO: return "SVE_I1_HALF_TWO";
          case AARCH64_OPND_SVE_I1_ZERO_ONE: return "SVE_I1_ZERO_ONE";
          case AARCH64_OPND_SVE_IMM_ROT1: return "SVE_IMM_ROT1";
          case AARCH64_OPND_SVE_IMM_ROT2: return "SVE_IMM_ROT2";
          case AARCH64_OPND_SVE_IMM_ROT3: return "SVE_IMM_ROT3";
          case AARCH64_OPND_SVE_INV_LIMM: return "SVE_INV_LIMM";
          case AARCH64_OPND_SVE_LIMM: return "SVE_LIMM";
          case AARCH64_OPND_SVE_LIMM_MOV: return "SVE_LIMM_MOV";
          case AARCH64_OPND_SVE_PATTERN: return "SVE_PATTERN";
          case AARCH64_OPND_SVE_PATTERN_SCALED: return "SVE_PATTERN_SCALED";
          case AARCH64_OPND_SVE_PRFOP: return "SVE_PRFOP";
          case AARCH64_OPND_SVE_Pd: return "SVE_Pd";
          case AARCH64_OPND_SVE_PNd: return "SVE_PNd";
          case AARCH64_OPND_SVE_Pg3: return "SVE_Pg3";
          case AARCH64_OPND_SVE_Pg4_5: return "SVE_Pg4_5";
          case AARCH64_OPND_SVE_Pg4_10: return "SVE_Pg4_10";
          case AARCH64_OPND_SVE_PNg4_10: return "SVE_PNg4_10";
          case AARCH64_OPND_SVE_Pg4_16: return "SVE_Pg4_16";
          case AARCH64_OPND_SVE_Pm: return "SVE_Pm";
          case AARCH64_OPND_SVE_Pn: return "SVE_Pn";
          case AARCH64_OPND_SVE_PNn: return "SVE_PNn";
          case AARCH64_OPND_SVE_Pt: return "SVE_Pt";
          case AARCH64_OPND_SVE_PNt: return "SVE_PNt";
          case AARCH64_OPND_SVE_Rm: return "SVE_Rm";
          case AARCH64_OPND_SVE_Rn_SP: return "SVE_Rn_SP";
          case AARCH64_OPND_SVE_SHLIMM_PRED: return "SVE_SHLIMM_PRED";
          case AARCH64_OPND_SVE_SHLIMM_UNPRED: return "SVE_SHLIMM_UNPRED";
          case AARCH64_OPND_SVE_SHLIMM_UNPRED_22: return "SVE_SHLIMM_UNPRED_22";
          case AARCH64_OPND_SVE_SHRIMM_PRED: return "SVE_SHRIMM_PRED";
          case AARCH64_OPND_SVE_SHRIMM_UNPRED: return "SVE_SHRIMM_UNPRED";
          case AARCH64_OPND_SVE_SHRIMM_UNPRED_22: return "SVE_SHRIMM_UNPRED_22";
          case AARCH64_OPND_SVE_SIMM5: return "SVE_SIMM5";
          case AARCH64_OPND_SVE_SIMM5B: return "SVE_SIMM5B";
          case AARCH64_OPND_SVE_SIMM6: return "SVE_SIMM6";
          case AARCH64_OPND_SVE_SIMM8: return "SVE_SIMM8";
          case AARCH64_OPND_SVE_UIMM3: return "SVE_UIMM3";
          case AARCH64_OPND_SVE_UIMM7: return "SVE_UIMM7";
          case AARCH64_OPND_SVE_UIMM8: return "SVE_UIMM8";
          case AARCH64_OPND_SVE_UIMM8_53: return "SVE_UIMM8_53";
          case AARCH64_OPND_SVE_VZn: return "SVE_VZn";
          case AARCH64_OPND_SVE_Vd: return "SVE_Vd";
          case AARCH64_OPND_SVE_Vm: return "SVE_Vm";
          case AARCH64_OPND_SVE_Vn: return "SVE_Vn";
          case AARCH64_OPND_SVE_Za_5: return "SVE_Za_5";
          case AARCH64_OPND_SVE_Za_16: return "SVE_Za_16";
          case AARCH64_OPND_SVE_Zd: return "SVE_Zd";
          case AARCH64_OPND_SVE_Zm_5: return "SVE_Zm_5";
          case AARCH64_OPND_SVE_Zm_16: return "SVE_Zm_16";
          case AARCH64_OPND_SVE_Zm3_INDEX: return "SVE_Zm3_INDEX";
          case AARCH64_OPND_SVE_Zm3_11_INDEX: return "SVE_Zm3_11_INDEX";
          case AARCH64_OPND_SVE_Zm3_19_INDEX: return "SVE_Zm3_19_INDEX";
          case AARCH64_OPND_SVE_Zm3_22_INDEX: return "SVE_Zm3_22_INDEX";
          case AARCH64_OPND_SVE_Zm4_11_INDEX: return "SVE_Zm4_11_INDEX";
          case AARCH64_OPND_SVE_Zm4_INDEX: return "SVE_Zm4_INDEX";
          case AARCH64_OPND_SVE_Zn: return "SVE_Zn";
          case AARCH64_OPND_SVE_Zn_INDEX: return "SVE_Zn_INDEX";
          case AARCH64_OPND_SVE_ZnxN: return "SVE_ZnxN";
          case AARCH64_OPND_SVE_Zt: return "SVE_Zt";
          case AARCH64_OPND_SVE_ZtxN: return "SVE_ZtxN";
          case AARCH64_OPND_SME_Zdnx2: return "SME_Zdnx2";
          case AARCH64_OPND_SME_Zdnx4: return "SME_Zdnx4";
          case AARCH64_OPND_SME_Zm: return "SME_Zm";
          case AARCH64_OPND_SME_Zmx2: return "SME_Zmx2";
          case AARCH64_OPND_SME_Zmx4: return "SME_Zmx4";
          case AARCH64_OPND_SME_Znx2: return "SME_Znx2";
          case AARCH64_OPND_SME_Znx4: return "SME_Znx4";
          case AARCH64_OPND_SME_Ztx2_STRIDED: return "SME_Ztx2_STRIDED";
          case AARCH64_OPND_SME_Ztx4_STRIDED: return "SME_Ztx4_STRIDED";
          case AARCH64_OPND_SME_ZAda_2b: return "SME_ZAda_2b";
          case AARCH64_OPND_SME_ZAda_3b: return "SME_ZAda_3b";
          case AARCH64_OPND_SME_ZA_HV_idx_src: return "SME_ZA_HV_idx_src";
          case AARCH64_OPND_SME_ZA_HV_idx_srcxN: return "SME_ZA_HV_idx_srcxN";
          case AARCH64_OPND_SME_ZA_HV_idx_dest: return "SME_ZA_HV_idx_dest";
          case AARCH64_OPND_SME_ZA_HV_idx_destxN: return "SME_ZA_HV_idx_destxN";
          case AARCH64_OPND_SME_Pdx2: return "SME_Pdx2";
          case AARCH64_OPND_SME_PdxN: return "SME_PdxN";
          case AARCH64_OPND_SME_Pm: return "SME_Pm";
          case AARCH64_OPND_SME_PNd3: return "SME_PNd3";
          case AARCH64_OPND_SME_PNg3: return "SME_PNg3";
          case AARCH64_OPND_SME_PNn: return "SME_PNn";
          case AARCH64_OPND_SME_PNn3_INDEX1: return "SME_PNn3_INDEX1";
          case AARCH64_OPND_SME_PNn3_INDEX2: return "SME_PNn3_INDEX2";
          case AARCH64_OPND_SME_list_of_64bit_tiles: return "SME_list_of_64bit_tiles";
          case AARCH64_OPND_SME_ZA_HV_idx_ldstr: return "SME_ZA_HV_idx_ldstr";
          case AARCH64_OPND_SME_ZA_array_off1x4: return "SME_ZA_array_off1x4";
          case AARCH64_OPND_SME_ZA_array_off2x2: return "SME_ZA_array_off2x2";
          case AARCH64_OPND_SME_ZA_array_off2x4: return "SME_ZA_array_off2x4";
          case AARCH64_OPND_SME_ZA_array_off3_0: return "SME_ZA_array_off3_0";
          case AARCH64_OPND_SME_ZA_array_off3_5: return "SME_ZA_array_off3_5";
          case AARCH64_OPND_SME_ZA_array_off3x2: return "SME_ZA_array_off3x2";
          case AARCH64_OPND_SME_ZA_array_off4: return "SME_ZA_array_off4";
          case AARCH64_OPND_SME_ADDR_RI_U4xVL: return "SME_ADDR_RI_U4xVL";
          case AARCH64_OPND_SME_SM_ZA: return "SME_SM_ZA";
          case AARCH64_OPND_SME_PnT_Wm_imm: return "SME_PnT_Wm_imm";
          case AARCH64_OPND_SME_SHRIMM4: return "SME_SHRIMM4";
          case AARCH64_OPND_SME_SHRIMM5: return "SME_SHRIMM5";
          case AARCH64_OPND_SME_Zm_INDEX1: return "SME_Zm_INDEX1";
          case AARCH64_OPND_SME_Zm_INDEX2: return "SME_Zm_INDEX2";
          case AARCH64_OPND_SME_Zm_INDEX3_1: return "SME_Zm_INDEX3_1";
          case AARCH64_OPND_SME_Zm_INDEX3_2: return "SME_Zm_INDEX3_2";
          case AARCH64_OPND_SME_Zm_INDEX3_10: return "SME_Zm_INDEX3_10";
          case AARCH64_OPND_SME_Zm_INDEX4_1: return "SME_Zm_INDEX4_1";
          case AARCH64_OPND_SME_Zm_INDEX4_10: return "SME_Zm_INDEX4_10";
          case AARCH64_OPND_SME_Zn_INDEX1_16: return "SME_Zn_INDEX1_16";
          case AARCH64_OPND_SME_Zn_INDEX2_15: return "SME_Zn_INDEX2_15";
          case AARCH64_OPND_SME_Zn_INDEX2_16: return "SME_Zn_INDEX2_16";
          case AARCH64_OPND_SME_Zn_INDEX3_14: return "SME_Zn_INDEX3_14";
          case AARCH64_OPND_SME_Zn_INDEX3_15: return "SME_Zn_INDEX3_15";
          case AARCH64_OPND_SME_Zn_INDEX4_14: return "SME_Zn_INDEX4_14";
          case AARCH64_OPND_SME_VLxN_10: return "SME_VLxN_10";
          case AARCH64_OPND_SME_VLxN_13: return "SME_VLxN_13";
          case AARCH64_OPND_SME_ZT0: return "SME_ZT0";
          case AARCH64_OPND_SME_ZT0_INDEX: return "SME_ZT0_INDEX";
          case AARCH64_OPND_SME_ZT0_LIST: return "SME_ZT0_LIST";
          case AARCH64_OPND_TME_UIMM16: return "TME_UIMM16";
          case AARCH64_OPND_SM3_IMM2: return "SM3_IMM2";
          case AARCH64_OPND_MOPS_ADDR_Rd: return "MOPS_ADDR_Rd";
          case AARCH64_OPND_MOPS_ADDR_Rs: return "MOPS_ADDR_Rs";
          case AARCH64_OPND_MOPS_WB_Rn: return "MOPS_WB_Rn";
          case AARCH64_OPND_CSSC_SIMM8: return "CSSC_SIMM8";
          case AARCH64_OPND_CSSC_UIMM8: return "CSSC_UIMM8";
        default: throw std::runtime_error("unknown operand");
    }
}

const char* qual_name(const aarch64_opnd_qualifier q) {
    switch (q) {
        case AARCH64_OPND_QLF_NIL: return "NONE";
        case AARCH64_OPND_QLF_W: return "W";
        case AARCH64_OPND_QLF_X: return "X";
        case AARCH64_OPND_QLF_WSP: return "WSP";
        case AARCH64_OPND_QLF_SP: return "SP";
        case AARCH64_OPND_QLF_S_B: return "S_B";
        case AARCH64_OPND_QLF_S_H: return "S_H";
        case AARCH64_OPND_QLF_S_S: return "S_S";
        case AARCH64_OPND_QLF_S_D: return "S_D";
        case AARCH64_OPND_QLF_S_Q: return "S_Q";
        case AARCH64_OPND_QLF_S_4B: return "S_4B";
        case AARCH64_OPND_QLF_S_2H: return "S_2H";
        case AARCH64_OPND_QLF_V_4B: return "V_4B";
        case AARCH64_OPND_QLF_V_8B: return "V_8B";
        case AARCH64_OPND_QLF_V_16B: return "V_16B";
        case AARCH64_OPND_QLF_V_2H: return "V_2H";
        case AARCH64_OPND_QLF_V_4H: return "V_4H";
        case AARCH64_OPND_QLF_V_8H: return "V_8H";
        case AARCH64_OPND_QLF_V_2S: return "V_2S";
        case AARCH64_OPND_QLF_V_4S: return "V_4S";
        case AARCH64_OPND_QLF_V_1D: return "V_1D";
        case AARCH64_OPND_QLF_V_2D: return "V_2D";
        case AARCH64_OPND_QLF_V_1Q: return "V_1Q";
        case AARCH64_OPND_QLF_P_Z: return "P_Z";
        case AARCH64_OPND_QLF_P_M: return "P_M";
        case AARCH64_OPND_QLF_imm_tag: return "imm_tag";
        case AARCH64_OPND_QLF_CR: return "CR";
        case AARCH64_OPND_QLF_imm_0_7: return "imm_0_7";
        case AARCH64_OPND_QLF_imm_0_15: return "imm_0_15";
        case AARCH64_OPND_QLF_imm_0_31: return "imm_0_31";
        case AARCH64_OPND_QLF_imm_0_63: return "imm_0_63";
        case AARCH64_OPND_QLF_imm_1_32: return "imm_1_32";
        case AARCH64_OPND_QLF_imm_1_64: return "imm_1_64";
        case AARCH64_OPND_QLF_LSL: return "LSL";
        case AARCH64_OPND_QLF_MSL: return "MSL";

        default: throw std::runtime_error("unknown qualifier");
    }
}

std::string to_str_array(const std::vector<std::string>& list, bool quote = true) {
    std::string joined;
    joined += "[";
    for (auto i = 0; i < list.size(); ++i) {
        if (quote) joined += "\"";
        joined += list[i];
        if (quote) joined += "\"";

        if (list.size() - i != 1) {
            joined += ",";
        }
    }
    joined += "]";
    return joined;
}

int main() {
    puts("[\n");

    constexpr auto len = sizeof(aarch64_opcode_table)/sizeof(aarch64_opcode_table[0]);
    for (auto i = 0; i < len; ++i) {
        const auto& x = aarch64_opcode_table[i];

        if (!x.name)
            break;

        const auto iclass = static_cast<aarch64_insn_class>(x.iclass);
        const auto specifics = static_cast<aarch64_op>(x.op);

        printf("{\n");

        printf("\t\"mnemonic\": \"%s\",\n", x.name);
        printf("\t\"opcode\": \"0x%08x\",\n", x.opcode);
        printf("\t\"mask\": \"0x%08x\",\n", x.mask);
        printf("\t\"class\": \"%s\",\n", iclass_name(iclass));
        printf("\t\"specifics\": \"%s\",\n", specifics_name(specifics));
        printf("\t\"description\": \"%s\",\n", iclass_description(iclass));

        auto operand_count = 0;
        {
            std::vector<std::string> operands;

            for (const auto o : x.operands) {
                if (!o)
                    break;

                const auto name = std::string(operand_name(o));
                operands.push_back(name);
                operand_count += 1;
            }

            printf("\t\"operands\": %s,\n", to_str_array(operands).c_str());
        }

        {
            std::vector<std::string> quals;

            for (const auto& ql : x.qualifiers_list) {
                if (quals.size() + 1 >= operand_count)
                    break;

                std::vector<std::string> qs;
                for (const auto& q : ql) {
                    if (!q)
                        break;
                    
                    qs.emplace_back(qual_name(static_cast<aarch64_opnd_qualifier>(q)));
                }
                quals.push_back(to_str_array(qs));
            }

            printf("\t\"operand_quals\": %s,\n", to_str_array(quals, false).c_str());
        }

        if (len - i != 2)
            printf("\t\"index\": %d },\n", i);
        else
            printf("\t\"index\": %d }\n", i);
    }

    puts("\n]");

    return 0;
}
