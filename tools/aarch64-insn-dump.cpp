#define VERIFIER(x) NULL

#include "bfd.h"
#include "dis-asm.h"
#include "aarch64-tbl.h"

#include <cstdio>
#include <stdexcept>

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

const char* enumerator_name(const aarch64_op op) {
    switch (op) {
        case OP_NIL: return "NIL";
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

int main() {
    puts("[\n");

    constexpr auto len = sizeof(aarch64_opcode_table)/sizeof(aarch64_opcode_table[0]);
    for (auto i = 0; i < len; ++i) {
        const auto& x = aarch64_opcode_table[i];

        if (!x.name)
            break;

        const auto iclass = static_cast<aarch64_insn_class>(x.iclass);
        const auto subclass = static_cast<aarch64_op>(x.op);

        printf("{\n");

        printf("\t\"mnemonic\": \"%s\",\n", x.name);
        printf("\t\"opcode\": \"0x%08x\",\n", x.opcode);
        printf("\t\"mask\": \"0x%08x\",\n", x.mask);
        printf("\t\"class\": \"%s\",\n", iclass_name(iclass));
        printf("\t\"subclass\": \"%s\",\n", enumerator_name(subclass));
        printf("\t\"description\": \"%s\",\n", iclass_description(iclass));

        if (len - i != 2)
            printf("\t\"index\": %d },\n", i);
        else
            printf("\t\"index\": %d }\n", i);
    }

    puts("\n]");

    return 0;
}
