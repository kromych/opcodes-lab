#define VERIFIER(x) NULL

extern "C" {

#include "bfd.h"
#include "dis-asm.h"
}

extern "C" {

#include "aarch64-dis.h"
#include "aarch64-insn-bits.h"
#include "aarch64-tbl.h"
}

#include <cstdio>
#include <stdexcept>
#include <string>
#include <vector>

const char *iclass_name(enum aarch64_insn_class c) {
    switch (c) {
    case aarch64_misc:
        return "AARCH64_MISC";
    case addsub_carry:
        return "ADDSUB_CARRY";
    case addsub_ext:
        return "ADDSUB_EXT";
    case addsub_imm:
        return "ADDSUB_IMM";
    case addsub_shift:
        return "ADDSUB_SHIFT";
    case asimdall:
        return "ASIMDALL";
    case asimddiff:
        return "ASIMDDIFF";
    case asimdelem:
        return "ASIMDELEM";
    case asimdext:
        return "ASIMDEXT";
    case asimdimm:
        return "ASIMDIMM";
    case asimdins:
        return "ASIMDINS";
    case asimdmisc:
        return "ASIMDMISC";
    case asimdperm:
        return "ASIMDPERM";
    case asimdsame:
        return "ASIMDSAME";
    case asimdshf:
        return "ASIMDSHF";
    case asimdtbl:
        return "ASIMDTBL";
    case asisddiff:
        return "ASISDDIFF";
    case asisdelem:
        return "ASISDELEM";
    case asisdlse:
        return "ASISDLSE";
    case asisdlsep:
        return "ASISDLSEP";
    case asisdlso:
        return "ASISDLSO";
    case asisdlsop:
        return "ASISDLSOP";
    case asisdmisc:
        return "ASISDMISC";
    case asisdone:
        return "ASISDONE";
    case asisdpair:
        return "ASISDPAIR";
    case asisdsame:
        return "ASISDSAME";
    case asisdshf:
        return "ASISDSHF";
    case bitfield:
        return "BITFIELD";
    case branch_imm:
        return "BRANCH_IMM";
    case branch_reg:
        return "BRANCH_REG";
    case compbranch:
        return "COMPBRANCH";
    case condbranch:
        return "CONDBRANCH";
    case condcmp_imm:
        return "CONDCMP_IMM";
    case condcmp_reg:
        return "CONDCMP_REG";
    case condsel:
        return "CONDSEL";
    case cryptoaes:
        return "CRYPTOAES";
    case cryptosha2:
        return "CRYPTOSHA2";
    case cryptosha3:
        return "CRYPTOSHA3";
    case dp_1src:
        return "DP_1SRC";
    case dp_2src:
        return "DP_2SRC";
    case dp_3src:
        return "DP_3SRC";
    case exception:
        return "EXCEPTION";
    case extract:
        return "EXTRACT";
    case float2fix:
        return "FLOAT2FIX";
    case float2int:
        return "FLOAT2INT";
    case floatccmp:
        return "FLOATCCMP";
    case floatcmp:
        return "FLOATCMP";
    case floatdp1:
        return "FLOATDP1";
    case floatdp2:
        return "FLOATDP2";
    case floatdp3:
        return "FLOATDP3";
    case floatimm:
        return "FLOATIMM";
    case floatsel:
        return "FLOATSEL";
    case fprcvtfloat2int:
        return "FPRCVTFLOAT2INT";
    case fprcvtint2float:
        return "FPRCVTINT2FLOAT";
    case ldst_immpost:
        return "LDST_IMMPOST";
    case ldst_immpre:
        return "LDST_IMMPRE";
    case ldst_imm9:
        return "LDST_IMM9";
    case ldst_imm10:
        return "LDST_IMM10";
    case ldst_pos:
        return "LDST_POS";
    case ldst_regoff:
        return "LDST_REGOFF";
    case ldst_unpriv:
        return "LDST_UNPRIV";
    case ldst_unscaled:
        return "LDST_UNSCALED";
    case ldstexcl:
        return "LDSTEXCL";
    case ldstnapair_offs:
        return "LDSTNAPAIR_OFFS";
    case ldstpair_off:
        return "LDSTPAIR_OFF";
    case ldstpair_indexed:
        return "LDSTPAIR_INDEXED";
    case loadlit:
        return "LOADLIT";
    case log_imm:
        return "LOG_IMM";
    case log_shift:
        return "LOG_SHIFT";
    case lse_atomic:
        return "LSE_ATOMIC";
    case lse128_atomic:
        return "LSE128_ATOMIC";
    case movewide:
        return "MOVEWIDE";
    case pcreladdr:
        return "PCRELADDR";
    case ic_system:
        return "IC_SYSTEM";
    case sme_fp_sd:
        return "SME_FP_SD";
    case sme_int_sd:
        return "SME_INT_SD";
    case sme_misc:
        return "SME_MISC";
    case sme_mov:
        return "SME_MOV";
    case sme_ldr:
        return "SME_LDR";
    case sme_psel:
        return "SME_PSEL";
    case sme_shift:
        return "SME_SHIFT";
    case sme_size_12_bh:
        return "SME_SIZE_12_BH";
    case sme_size_12_bhs:
        return "SME_SIZE_12_BHS";
    case sme_size_12_hs:
        return "SME_SIZE_12_HS";
    case sme_size_12_b:
        return "SME_SIZE_12_B";
    case sme_size_22:
        return "SME_SIZE_22";
    case sme_size_22_hsd:
        return "SME_SIZE_22_HSD";
    case sme_sz_23:
        return "SME_SZ_23";
    case sme_str:
        return "SME_STR";
    case sme_start:
        return "SME_START";
    case sme_stop:
        return "SME_STOP";
    case sme2_mov:
        return "SME2_MOV";
    case sve_cpy:
        return "SVE_CPY";
    case sve_index:
        return "SVE_INDEX";
    case sve_limm:
        return "SVE_LIMM";
    case sve_misc:
        return "SVE_MISC";
    case sve_movprfx:
        return "SVE_MOVPRFX";
    case sve_pred_zm:
        return "SVE_PRED_ZM";
    case sve_shift_pred:
        return "SVE_SHIFT_PRED";
    case sve_shift_unpred:
        return "SVE_SHIFT_UNPRED";
    case sve_size_bh:
        return "SVE_SIZE_BH";
    case sve_size_bhs:
        return "SVE_SIZE_BHS";
    case sve_size_bhsd:
        return "SVE_SIZE_BHSD";
    case sve_size_hsd:
        return "SVE_SIZE_HSD";
    case sve_size_hsd2:
        return "SVE_SIZE_HSD2";
    case sve_size_hsd3:
        return "SVE_SIZE_HSD3";
    case sve_size_sd:
        return "SVE_SIZE_SD";
    case sve_size_sd2:
        return "SVE_SIZE_SD2";
    case sve_size_sd3:
        return "SVE_SIZE_SD3";
    case sve_size_sd4:
        return "SVE_SIZE_SD4";
    case sve_size_13:
        return "SVE_SIZE_13";
    case sve_shift_tsz_hsd:
        return "SVE_SHIFT_TSZ_HSD";
    case sve_shift_tsz_bhsd:
        return "SVE_SHIFT_TSZ_BHSD";
    case sve_size_tsz_bhs:
        return "SVE_SIZE_TSZ_BHS";
    case testbranch:
        return "TESTBRANCH";
    case cryptosm3:
        return "CRYPTOSM3";
    case cryptosm4:
        return "CRYPTOSM4";
    case dotproduct:
        return "DOTPRODUCT";
    case bfloat16:
        return "BFLOAT16";
    case cssc:
        return "CSSC";
    case gcs:
        return "GCS";
    case the:
        return "THE";
    case sve2_urqvs:
        return "SVE2_URQVS";
    case sve_index1:
        return "SVE_INDEX1";
    case rcpc3:
        return "RCPC3";
    case lut:
        return "LUT";

    default:
        throw std::runtime_error("unknown instruction class");
    }
}

const char *iclass_description(const aarch64_insn_class c) {
    switch (c) {
    case aarch64_misc:
        return "Misc. instructions";
    case addsub_carry:
        return "Add/subtract (with carry)";
    case addsub_ext:
        return "Add/subtract (extended register)";
    case addsub_imm:
        return "Add/subtract (immediate)";
    case addsub_shift:
        return "Add/subtract (shifted register)";
    case asimdall:
        return "AdvSIMD across lanes";
    case asimddiff:
        return "AdvSIMD three different";
    case asimdelem:
        return "AdvSIMD vector x indexed element";
    case asimdext:
        return "AdvSIMD EXT";
    case asimdimm:
        return "AdvSIMD modified immediate";
    case asimdins:
        return "AdvSIMD copy";
    case asimdmisc:
        return "AdvSIMD two-reg misc";
    case asimdperm:
        return "AdvSIMD ZIP/UZP/TRN";
    case asimdsame:
        return "AdvSIMD three same";
    case asimdshf:
        return "AdvSIMD shift by immediate";
    case asimdtbl:
        return "AdvSIMD TBL/TBX";
    case asisddiff:
        return "AdvSIMD scalar three different";
    case asisdelem:
        return "AdvSIMD scalar x indexed element";
    case asisdlse:
        return "AdvSIMD load/store multiple structures";
    case asisdlsep:
        return "AdvSIMD load/store multiple structures (post-indexed)";
    case asisdlso:
        return "AdvSIMD load/store single structure";
    case asisdlsop:
        return "AdvSIMD load/store single structure (post-indexed)";
    case asisdmisc:
        return "AdvSIMD scalar two-reg misc";
    case asisdone:
        return "AdvSIMD scalar copy";
    case asisdpair:
        return "AdvSIMD scalar pairwise";
    case asisdsame:
        return "AdvSIMD scalar three same";
    case asisdshf:
        return "AdvSIMD scalar shift by immediate";
    case bfloat16:
        return "BFloat Advanced SIMD instructions";
    case bitfield:
        return "Bitfield";
    case branch_imm:
        return "Unconditional branch (immediate)";
    case branch_reg:
        return "Unconditional branch (register)";
    case compbranch:
        return "Compare & branch (immediate)";
    case condbranch:
        return "Conditional branch (immediate)";
    case condcmp_imm:
        return "Conditional compare (immediate)";
    case condcmp_reg:
        return "Conditional compare (register)";
    case condsel:
        return "Conditional select";
    case cryptoaes:
        return "Crypto AES";
    case cryptosha2:
        return "Crypto two-reg SHA";
    case cryptosha3:
        return "Crypto three-reg SHA";
    case cryptosm3:
        return "Crypto SM3 (optional in ARMv8.2-a)";
    case cryptosm4:
        return "Crypto SM4 (optional in ARMv8.2-a)";
    case cssc:
        return "Common Short Sequence Compression";
    case dotproduct:
        return "SIMD Dot Product (optional in v8.2-A)";
    case dp_1src:
        return "Data-processing (1 source)";
    case dp_2src:
        return "Data-processing (2 source)";
    case dp_3src:
        return "Data-processing (3 source)";
    case exception:
        return "Exception generation";
    case extract:
        return "Extract";
    case float2fix:
        return "Floating-point<->fixed-point conversions";
    case float2int:
        return "Floating-point<->integer conversions";
    case floatccmp:
        return "Floating-point conditional compare";
    case floatcmp:
        return "Floating-point compare";
    case floatdp1:
        return "Floating-point data-processing (1 source)";
    case floatdp2:
        return "Floating-point data-processing (2 source)";
    case floatdp3:
        return "Floating-point data-processing (3 source)";
    case floatimm:
        return "Floating-point immediate";
    case floatsel:
        return "Floating-point conditional select";
    case fprcvtfloat2int:
        return "Floating-point<->integer conversions (FPRCVT)";
    case fprcvtint2float:
        return "Integer<->floating-point conversions (FPRCVT)";
    case ic_system:
        return "System instructions";
    case ldst_imm10:
        return "Load/store register (scaled signed immediate)";
    case ldst_imm9:
        return "Load/store register (immediate indexed)";
    case ldst_pos:
        return "Load/store register (unsigned immediate)";
    case ldst_regoff:
        return "Load/store register (register offset)";
    case ldst_unpriv:
        return "Load/store register (unprivileged)";
    case ldst_unscaled:
        return "Load/store register (unscaled immediate)";
    case ldstexcl:
        return "Load/store exclusive";
    case ldstnapair_offs:
        return "Load/store no-allocate pair (offset)";
    case ldstpair_indexed:
        return "Load/store register pair (indexed)";
    case ldstpair_off:
        return "Load/store register pair (offset)";
    case loadlit:
        return "Load register (literal)";
    case log_imm:
        return "Logical (immediate)";
    case log_shift:
        return "Logical (shifted register)";
    case lse_atomic:
        return "LSE extension (atomic)";
    case lse128_atomic:
        return "LSE extension (atomic) 128-bit";
    case movewide:
        return "Move wide (immediate)";
    case pcreladdr:
        return "PC-rel. addressing";
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
    case sme_size_12_bh:
    case sme_size_12_b:
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
    case sve2_urqvs:
    case sve_index1:
    case sve_size_hsd3:
    case sve_size_sd3:
    case sve_size_sd4:
        return "SVE instructions";
    case rcpc3:
        return "RCPC3 instructions";
    case gcs:
        return "GCS instructions";
    case the:
        return "THE instructions";
    case lut:
        return "LUT instructions";
    case testbranch:
        return "Test & branch (immediate)";

    default:
        throw std::runtime_error("no known description");
    }
}

const char *operand_name(const aarch64_opnd o) {
    const char *name = aarch64_operands[o].name;
    if (!name || !name[0])
        return "NONE";
    return name;
}

const char *qual_name(const aarch64_opnd_qualifier q) {
    switch (q) {
    case AARCH64_OPND_QLF_NIL:
        return "NONE";
    case AARCH64_OPND_QLF_W:
        return "W";
    case AARCH64_OPND_QLF_X:
        return "X";
    case AARCH64_OPND_QLF_WSP:
        return "WSP";
    case AARCH64_OPND_QLF_SP:
        return "SP";
    case AARCH64_OPND_QLF_S_B:
        return "S_B";
    case AARCH64_OPND_QLF_S_H:
        return "S_H";
    case AARCH64_OPND_QLF_S_S:
        return "S_S";
    case AARCH64_OPND_QLF_S_D:
        return "S_D";
    case AARCH64_OPND_QLF_S_Q:
        return "S_Q";
    case AARCH64_OPND_QLF_S_2B:
        return "S_2B";
    case AARCH64_OPND_QLF_S_4B:
        return "S_4B";
    case AARCH64_OPND_QLF_S_2H:
        return "S_2H";
    case AARCH64_OPND_QLF_V_4B:
        return "V_4B";
    case AARCH64_OPND_QLF_V_8B:
        return "V_8B";
    case AARCH64_OPND_QLF_V_16B:
        return "V_16B";
    case AARCH64_OPND_QLF_V_2H:
        return "V_2H";
    case AARCH64_OPND_QLF_V_4H:
        return "V_4H";
    case AARCH64_OPND_QLF_V_8H:
        return "V_8H";
    case AARCH64_OPND_QLF_V_2S:
        return "V_2S";
    case AARCH64_OPND_QLF_V_4S:
        return "V_4S";
    case AARCH64_OPND_QLF_V_1D:
        return "V_1D";
    case AARCH64_OPND_QLF_V_2D:
        return "V_2D";
    case AARCH64_OPND_QLF_V_1Q:
        return "V_1Q";
    case AARCH64_OPND_QLF_P_Z:
        return "P_Z";
    case AARCH64_OPND_QLF_P_M:
        return "P_M";
    case AARCH64_OPND_QLF_imm_tag:
        return "imm_tag";
    case AARCH64_OPND_QLF_CR:
        return "CR";
    case AARCH64_OPND_QLF_imm_0_7:
        return "imm_0_7";
    case AARCH64_OPND_QLF_imm_0_15:
        return "imm_0_15";
    case AARCH64_OPND_QLF_imm_0_31:
        return "imm_0_31";
    case AARCH64_OPND_QLF_imm_0_63:
        return "imm_0_63";
    case AARCH64_OPND_QLF_imm_1_32:
        return "imm_1_32";
    case AARCH64_OPND_QLF_imm_1_64:
        return "imm_1_64";
    case AARCH64_OPND_QLF_LSL:
        return "LSL";
    case AARCH64_OPND_QLF_MSL:
        return "MSL";
    case AARCH64_OPND_QLF_RETRIEVE:
        return "RETRIEVE";
    case AARCH64_OPND_QLF_ERR:
        return "ERR";

    default:
        throw std::runtime_error("unknown qualifier");
    }
}

std::string to_str_array(const std::vector<std::string> &list,
                         bool quote = true) {
    std::string joined;
    joined += "[";
    for (auto i = 0; i < list.size(); ++i) {
        if (quote)
            joined += "\"";
        joined += list[i];
        if (quote)
            joined += "\"";

        if (list.size() - i != 1) {
            joined += ',';
        }
    }
    joined += "]";
    return joined;
}

std::string flags_str(uint64_t flags) {
    std::vector<std::string> sflags;

    if (flags & F_ALIAS)
        sflags.emplace_back("IS_ALIAS");
    if (flags & F_HAS_ALIAS)
        sflags.emplace_back("HAS_ALIAS");
    if (flags & F_COND)
        sflags.emplace_back("IS_COND");
    if (flags & F_SF)
        sflags.emplace_back("HAS_SF_FIELD");
    if (flags & F_SIZEQ)
        sflags.emplace_back("HAS_SIZEQ_FIELD");
    if (flags & F_FPTYPE)
        sflags.emplace_back("HAS_FPTYPE_FIELD");
    if (flags & F_SSIZE)
        sflags.emplace_back("HAS_ADVSIMD_SCALAR_SIZE");
    if (flags & F_T)
        sflags.emplace_back("HAS_ADVSIMV_VEC_IN_Q");
    if (flags & F_GPRSIZE_IN_Q)
        sflags.emplace_back("HAS_ADVSIMV_GPRSIZE_IN_Q");
    if (flags & F_LDS_SIZE)
        sflags.emplace_back("HAS_LDS_SIZE_IN_BIT_22");
    if (flags & F_MISC)
        sflags.emplace_back("HAS_SPEC_DECODE_RULES");
    if (flags & F_N)
        sflags.emplace_back("HAS_N_FIELD");

    if (flags & F_OD(0))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_0");
    if (flags & F_OD(1))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_1");
    if (flags & F_OD(2))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_2");
    if (flags & F_OD(3))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_3");
    if (flags & F_OD(4))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_4");
    if (flags & F_OD(5))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_5");
    if (flags & F_OD(6))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_6");
    if (flags & F_OD(7))
        sflags.emplace_back("HAS_OPCODE_DEPENDENT_FIELD_7");

    if (flags & F_LSE_SZ)
        sflags.emplace_back("HAS_LSE_SZ_FIELD");
    if (flags & F_SYS_READ)
        sflags.emplace_back("IS_SYS_READ");
    if (flags & F_SYS_WRITE)
        sflags.emplace_back("IS_SYS_WRITE");
    if (flags & F_SCAN)
        sflags.emplace_back("RESTRICTED_NEXT_INSN_SET");

    if (flags & F_OPD_NARROW)
        sflags.emplace_back("HAS_NARROW");
    if (flags & F_OPD_SIZE)
        sflags.emplace_back("HAS_SIZE");
    if (flags & F_RCPC3_SIZE)
        sflags.emplace_back("HAS_RCPC3_SIZE");
    if (flags & F_LSFE_SZ)
        sflags.emplace_back("HAS_LSFE_SZ_FIELD");

    std::string joined;
    for (auto i = 0; i < sflags.size(); ++i) {
        joined += sflags[i];
        if (sflags.size() - i != 1) {
            joined += '|';
        }
    }

    return joined;
}

const char *field_name(aarch64_field_kind f) {
    switch (f) {
    case FLD_NIL:
        return "NONE";
    case FLD_CONST_0:
        return "CONST_0";
    case FLD_CONST_00:
        return "CONST_00";
    case FLD_CONST_01:
        return "CONST_01";
    case FLD_CONST_1:
        return "CONST_1";
    case FLD_CRm:
        return "CRm";
    case FLD_CRm_dsb_nxs:
        return "CRm_dsb_nxs";
    case FLD_CRn:
        return "CRn";
    case FLD_CSSC_imm8:
        return "CSSC_imm8";
    case FLD_H:
        return "H";
    case FLD_L:
        return "L";
    case FLD_LSE128_Rt:
        return "LSE128_Rt";
    case FLD_LSE128_Rt2:
        return "LSE128_Rt2";
    case FLD_M:
        return "M";
    case FLD_N:
        return "N";
    case FLD_Q:
        return "Q";
    case FLD_Ra:
        return "Ra";
    case FLD_Rd:
        return "Rd";
    case FLD_Rm:
        return "Rm";
    case FLD_Rn:
        return "Rn";
    case FLD_Rs:
        return "Rs";
    case FLD_Rt:
        return "Rt";
    case FLD_Rt2:
        return "Rt2";
    case FLD_S:
        return "S";
    case FLD_SM3_imm2:
        return "SM3_imm2";
    case FLD_SME_Pdx2:
        return "SME_Pdx2";
    case FLD_SME_Pm:
        return "SME_Pm";
    case FLD_SME_PNd3:
        return "SME_PNd3";
    case FLD_SME_PNn3:
        return "SME_PNn3";
    case FLD_SME_Q:
        return "SME_Q";
    case FLD_SME_Rm:
        return "SME_Rm";
    case FLD_SME_Rv:
        return "SME_Rv";
    case FLD_SME_V:
        return "SME_V";
    case FLD_SME_VL_10:
        return "SME_VL_10";
    case FLD_SME_VL_13:
        return "SME_VL_13";
    case FLD_SME_ZAda_1b:
        return "SME_ZAda_1b";
    case FLD_SME_ZAda_2b:
        return "SME_ZAda_2b";
    case FLD_SME_ZAda_3b:
        return "SME_ZAda_3b";
    case FLD_SME_Zdn2:
        return "SME_Zdn2";
    case FLD_SME_Zdn4:
        return "SME_Zdn4";
    case FLD_SME_Zm:
        return "SME_Zm";
    case FLD_SME_Zm17_3:
        return "SME_Zm17_3";
    case FLD_SME_Zm2:
        return "SME_Zm2";
    case FLD_SME_Zm4:
        return "SME_Zm4";
    case FLD_SME_Zn2:
        return "SME_Zn2";
    case FLD_SME_Zn4:
        return "SME_Zn4";
    case FLD_SME_Zn6_3:
        return "SME_Zn6_3";
    case FLD_SME_ZtT:
        return "SME_ZtT";
    case FLD_SME_Zt3:
        return "SME_Zt3";
    case FLD_SME_Zt2:
        return "SME_Zt2";
    case FLD_SME_i1:
        return "SME_i1";
    case FLD_SME_size_12:
        return "SME_size_12";
    case FLD_SME_size_22:
        return "SME_size_22";
    case FLD_SME_sz_23:
        return "SME_sz_23";
    case FLD_SME_tszh:
        return "SME_tszh";
    case FLD_SME_tszl:
        return "SME_tszl";
    case FLD_SME_zero_mask:
        return "SME_zero_mask";
    case FLD_SVE_M_4:
        return "SVE_M_4";
    case FLD_SVE_M_14:
        return "SVE_M_14";
    case FLD_SVE_M_16:
        return "SVE_M_16";
    case FLD_SVE_N:
        return "SVE_N";
    case FLD_SVE_Pd:
        return "SVE_Pd";
    case FLD_SVE_Pg3:
        return "SVE_Pg3";
    case FLD_SVE_Pg4_5:
        return "SVE_Pg4_5";
    case FLD_SVE_Pg4_10:
        return "SVE_Pg4_10";
    case FLD_SVE_Pg4_16:
        return "SVE_Pg4_16";
    case FLD_SVE_Pm:
        return "SVE_Pm";
    case FLD_SVE_Pn:
        return "SVE_Pn";
    case FLD_SVE_Pt:
        return "SVE_Pt";
    case FLD_SVE_Rm:
        return "SVE_Rm";
    case FLD_SVE_Rn:
        return "SVE_Rn";
    case FLD_SVE_Vd:
        return "SVE_Vd";
    case FLD_SVE_Vm:
        return "SVE_Vm";
    case FLD_SVE_Vn:
        return "SVE_Vn";
    case FLD_SVE_Za_5:
        return "SVE_Za_5";
    case FLD_SVE_Za_16:
        return "SVE_Za_16";
    case FLD_SVE_Zd:
        return "SVE_Zd";
    case FLD_SVE_Zm_5:
        return "SVE_Zm_5";
    case FLD_SVE_Zm_16:
        return "SVE_Zm_16";
    case FLD_SVE_Zn:
        return "SVE_Zn";
    case FLD_SVE_Zt:
        return "SVE_Zt";
    case FLD_SVE_i1:
        return "SVE_i1";
    case FLD_SVE_i1_23:
        return "SVE_i1_23";
    case FLD_SVE_i2:
        return "SVE_i2";
    case FLD_SVE_i2h:
        return "SVE_i2h";
    case FLD_SVE_i3h:
        return "SVE_i3h";
    case FLD_SVE_i3h2:
        return "SVE_i3h2";
    case FLD_SVE_i3h3:
        return "SVE_i3h3";
    case FLD_SVE_i3l:
        return "SVE_i3l";
    case FLD_SVE_i3l2:
        return "SVE_i3l2";
    case FLD_SVE_i4l2:
        return "SVE_i4l2";
    case FLD_SVE_imm3:
        return "SVE_imm3";
    case FLD_SVE_imm4:
        return "SVE_imm4";
    case FLD_SVE_imm5:
        return "SVE_imm5";
    case FLD_SVE_imm5b:
        return "SVE_imm5b";
    case FLD_SVE_imm6:
        return "SVE_imm6";
    case FLD_SVE_imm7:
        return "SVE_imm7";
    case FLD_SVE_imm8:
        return "SVE_imm8";
    case FLD_SVE_imm9:
        return "SVE_imm9";
    case FLD_SVE_immr:
        return "SVE_immr";
    case FLD_SVE_imms:
        return "SVE_imms";
    case FLD_SVE_msz:
        return "SVE_msz";
    case FLD_SVE_pattern:
        return "SVE_pattern";
    case FLD_SVE_prfop:
        return "SVE_prfop";
    case FLD_SVE_rot1:
        return "SVE_rot1";
    case FLD_SVE_rot2:
        return "SVE_rot2";
    case FLD_SVE_rot3:
        return "SVE_rot3";
    case FLD_SVE_size:
        return "SVE_size";
    case FLD_SVE_sz:
        return "SVE_sz";
    case FLD_SVE_sz2:
        return "SVE_sz2";
    case FLD_SVE_sz3:
        return "SVE_sz3";
    case FLD_SVE_sz4:
        return "SVE_sz4";
    case FLD_SVE_tsz:
        return "SVE_tsz";
    case FLD_SVE_tszh:
        return "SVE_tszh";
    case FLD_SVE_tszl_8:
        return "SVE_tszl_8";
    case FLD_SVE_tszl_19:
        return "SVE_tszl_19";
    case FLD_SVE_xs_14:
        return "SVE_xs_14";
    case FLD_SVE_xs_22:
        return "SVE_xs_22";
    case FLD_S_imm10:
        return "S_imm10";
    case FLD_abc:
        return "abc";
    case FLD_asisdlso_opcode:
        return "asisdlso_opcode";
    case FLD_b40:
        return "b40";
    case FLD_b5:
        return "b5";
    case FLD_cmode:
        return "cmode";
    case FLD_cond:
        return "cond";
    case FLD_cond2:
        return "cond2";
    case FLD_defgh:
        return "defgh";
    case FLD_hw:
        return "hw";
    case FLD_imm1_0:
        return "imm1_0";
    case FLD_imm1_2:
        return "imm1_2";
    case FLD_imm1_3:
        return "imm1_3";
    case FLD_imm1_8:
        return "imm1_8";
    case FLD_imm1_10:
        return "imm1_10";
    case FLD_imm1_14:
        return "imm1_14";
    case FLD_imm1_15:
        return "imm1_15";
    case FLD_imm1_16:
        return "imm1_16";
    case FLD_imm1_22:
        return "imm1_22";
    case FLD_imm2_0:
        return "imm2_0";
    case FLD_imm2_1:
        return "imm2_1";
    case FLD_imm2_2:
        return "imm2_2";
    case FLD_imm2_4:
        return "imm2_4";
    case FLD_imm2_8:
        return "imm2_8";
    case FLD_imm2_10:
        return "imm2_10";
    case FLD_imm2_12:
        return "imm2_12";
    case FLD_imm2_13:
        return "imm2_13";
    case FLD_imm2_15:
        return "imm2_15";
    case FLD_imm2_16:
        return "imm2_16";
    case FLD_imm2_19:
        return "imm2_19";
    case FLD_imm3_0:
        return "imm3_0";
    case FLD_imm3_5:
        return "imm3_5";
    case FLD_imm3_10:
        return "imm3_10";
    case FLD_imm3_12:
        return "imm3_12";
    case FLD_imm3_14:
        return "imm3_14";
    case FLD_imm3_15:
        return "imm3_15";
    case FLD_imm3_19:
        return "imm3_19";
    case FLD_imm4_0:
        return "imm4_0";
    case FLD_imm4_5:
        return "imm4_5";
    case FLD_imm4_10:
        return "imm4_10";
    case FLD_imm4_11:
        return "imm4_11";
    case FLD_imm4_14:
        return "imm4_14";
    case FLD_imm5:
        return "imm5";
    case FLD_imm6_10:
        return "imm6_10";
    case FLD_imm6_15:
        return "imm6_15";
    case FLD_imm7:
        return "imm7";
    case FLD_imm8:
        return "imm8";
    case FLD_imm9:
        return "imm9";
    case FLD_imm9_5:
        return "imm9_5";
    case FLD_imm12:
        return "imm12";
    case FLD_imm14:
        return "imm14";
    case FLD_imm16_0:
        return "imm16_0";
    case FLD_imm16_5:
        return "imm16_5";
    case FLD_imm17_1:
        return "imm17_1";
    case FLD_imm17_2:
        return "imm17_2";
    case FLD_imm19:
        return "imm19";
    case FLD_imm26:
        return "imm26";
    case FLD_immb:
        return "immb";
    case FLD_immh:
        return "immh";
    case FLD_immhi:
        return "immhi";
    case FLD_immlo:
        return "immlo";
    case FLD_immr:
        return "immr";
    case FLD_imms:
        return "imms";
    case FLD_index:
        return "index";
    case FLD_index2:
        return "index2";
    case FLD_ldst_size:
        return "ldst_size";
    case FLD_len:
        return "len";
    case FLD_lse_sz:
        return "lse_sz";
    case FLD_nzcv:
        return "nzcv";
    case FLD_op:
        return "op";
    case FLD_op0:
        return "op0";
    case FLD_op1:
        return "op1";
    case FLD_op2:
        return "op2";
    case FLD_opc:
        return "opc";
    case FLD_opc1:
        return "opc1";
    case FLD_opcode:
        return "opcode";
    case FLD_option:
        return "option";
    case FLD_rotate1:
        return "rotate1";
    case FLD_rotate2:
        return "rotate2";
    case FLD_rotate3:
        return "rotate3";
    case FLD_scale:
        return "scale";
    case FLD_sf:
        return "sf";
    case FLD_shift:
        return "shift";
    case FLD_size:
        return "size";
    case FLD_sz:
        return "sz";
    case FLD_type:
        return "type";
    case FLD_vldst_size:
        return "vldst_size";
    case FLD_off3:
        return "off3";
    case FLD_off2:
        return "off2";
    case FLD_ZAn_1:
        return "ZAn_1";
    case FLD_ol:
        return "ol";
    case FLD_ZAn_2:
        return "ZAn_2";
    case FLD_ZAn_3:
        return "ZAn_3";
    case FLD_ZAn:
        return "ZAn";
    case FLD_opc2:
        return "opc2";
    case FLD_rcpc3_size:
        return "rcpc3_size";
    case FLD_brbop:
        return "brbop";
    case FLD_ZA8_1:
        return "ZA8_1";
    case FLD_ZA7_2:
        return "ZA7_2";
    case FLD_ZA6_3:
        return "ZA6_3";
    case FLD_ZA5_4:
        return "ZA5_4";

    default:
        throw std::runtime_error("unknown field kind");
    }
}

const char *operand_class_name(aarch64_operand_class c) {
    switch (c) {
    case AARCH64_OPND_CLASS_NIL:
        return "NONE";
    case AARCH64_OPND_CLASS_INT_REG:
        return "INT_REG";
    case AARCH64_OPND_CLASS_MODIFIED_REG:
        return "MODIFIED_REG";
    case AARCH64_OPND_CLASS_FP_REG:
        return "FP_REG";
    case AARCH64_OPND_CLASS_SIMD_REG:
        return "SIMD_REG";
    case AARCH64_OPND_CLASS_SIMD_ELEMENT:
        return "SIMD_ELEMENT";
    case AARCH64_OPND_CLASS_SISD_REG:
        return "SISD_REG";
    case AARCH64_OPND_CLASS_SIMD_REGLIST:
        return "SIMD_REGLIST";
    case AARCH64_OPND_CLASS_SVE_REG:
        return "SVE_REG";
    case AARCH64_OPND_CLASS_SVE_REGLIST:
        return "SVE_REGLIST";
    case AARCH64_OPND_CLASS_PRED_REG:
        return "PRED_REG";
    case AARCH64_OPND_CLASS_ZA_ACCESS:
        return "ZA_ACCESS";
    case AARCH64_OPND_CLASS_ADDRESS:
        return "ADDRESS";
    case AARCH64_OPND_CLASS_IMMEDIATE:
        return "IMMEDIATE";
    case AARCH64_OPND_CLASS_SYSTEM:
        return "SYSTEM";
    case AARCH64_OPND_CLASS_COND:
        return "COND";

    default:
        throw std::runtime_error("unknown operand class");
    }
}

const char *feature_set_name(const aarch64_feature_set *f) {
    if (f == &aarch64_feature_v8)
        return "V8";
    else if (f == &aarch64_feature_fp)
        return "FP";
    else if (f == &aarch64_feature_simd)
        return "SIMD";
    else if (f == &aarch64_feature_crc)
        return "CRC";
    else if (f == &aarch64_feature_lse)
        return "LSE";
    else if (f == &aarch64_feature_lsfe)
        return "LSFE";
    else if (f == &aarch64_feature_lse128)
        return "LSE128";
    else if (f == &aarch64_feature_lsui)
        return "LSUI";
    else if (f == &aarch64_feature_lsui_fp)
        return "LSUI_FP";
    else if (f == &aarch64_feature_lor)
        return "LOR";
    else if (f == &aarch64_feature_rdma)
        return "RDMA";
    else if (f == &aarch64_feature_fp_f16)
        return "FP_F16";
    else if (f == &aarch64_feature_simd_f16)
        return "SIMD_F16";
    else if (f == &aarch64_feature_fprcvt)
        return "FPRCVT";
    else if (f == &aarch64_feature_sve)
        return "SVE";
    else if (f == &aarch64_feature_pauth)
        return "PAUTH";
    else if (f == &aarch64_feature_compnum)
        return "COMPNUM";
    else if (f == &aarch64_feature_jscvt)
        return "JSCVT";
    else if (f == &aarch64_feature_rcpc)
        return "RCPC";
    else if (f == &aarch64_feature_rcpc2)
        return "RCPC2";
    else if (f == &aarch64_feature_dotprod)
        return "DOTPROD";
    else if (f == &aarch64_feature_sha2)
        return "SHA2";
    else if (f == &aarch64_feature_aes)
        return "AES";
    else if (f == &aarch64_feature_sm4)
        return "SM4";
    else if (f == &aarch64_feature_sha3)
        return "SHA3";
    else if (f == &aarch64_feature_fp_16_v8_2a)
        return "FP_16_V8_2A";
    else if (f == &aarch64_feature_flagmanip)
        return "FLAGMANIP";
    else if (f == &aarch64_feature_frintts)
        return "FRINTTS";
    else if (f == &aarch64_feature_sb)
        return "SB";
    else if (f == &aarch64_feature_predres)
        return "PREDRES";
    else if (f == &aarch64_feature_predres2)
        return "PREDRES2";
    else if (f == &aarch64_feature_cmpbr)
        return "CMPBR";
    else if (f == &aarch64_feature_memtag)
        return "MEMTAG";
    else if (f == &aarch64_feature_bfloat16)
        return "BFLOAT16";
    else if (f == &aarch64_feature_bfloat16_sve)
        return "BFLOAT16_SVE";
    else if (f == &aarch64_feature_tme)
        return "TME";
    else if (f == &aarch64_feature_sve2)
        return "SVE2";
    else if (f == &aarch64_feature_sve2aes)
        return "SVE2AES";
    else if (f == &aarch64_feature_sve2sha3)
        return "SVE2SHA3";
    else if (f == &aarch64_feature_sve2sm4)
        return "SVE2SM4";
    else if (f == &aarch64_feature_sve2bitperm)
        return "SVE2BITPERM";
    else if (f == &aarch64_feature_sme)
        return "SME";
    else if (f == &aarch64_feature_sme_f64f64)
        return "SME_F64F64";
    else if (f == &aarch64_feature_sme_i16i64)
        return "SME_I16I64";
    else if (f == &aarch64_feature_sme2)
        return "SME2";
    else if (f == &aarch64_feature_sme2_i16i64)
        return "SME2_I16I64";
    else if (f == &aarch64_feature_sme2_f64f64)
        return "SME2_F64F64";
    else if (f == &aarch64_feature_i8mm)
        return "I8MM";
    else if (f == &aarch64_feature_i8mm_sve)
        return "I8MM_SVE";
    else if (f == &aarch64_feature_f32mm_sve)
        return "F32MM_SVE";
    else if (f == &aarch64_feature_f64mm_sve)
        return "F64MM_SVE";
    else if (f == &aarch64_feature_v8r)
        return "V8R";
    else if (f == &aarch64_feature_ls64)
        return "LS64";
    else if (f == &aarch64_feature_lscp)
        return "LSCP";
    else if (f == &aarch64_feature_flagm)
        return "FLAGM";
    else if (f == &aarch64_feature_xs)
        return "XS";
    else if (f == &aarch64_feature_wfxt)
        return "WFXT";
    else if (f == &aarch64_feature_mops)
        return "MOPS";
    else if (f == &aarch64_feature_mops_memtag)
        return "MOPS_MEMTAG";
    else if (f == &aarch64_feature_mops_go)
        return "MOPS_GO";
    else if (f == &aarch64_feature_hbc)
        return "HBC";
    else if (f == &aarch64_feature_cssc)
        return "CSSC";
    else if (f == &aarch64_feature_chk)
        return "CHK";
    else if (f == &aarch64_feature_gcs)
        return "GCS";
    else if (f == &aarch64_feature_ite)
        return "ITE";
    else if (f == &aarch64_feature_d128)
        return "D128";
    else if (f == &aarch64_feature_d128_tlbid)
        return "D128_TLBID";
    else if (f == &aarch64_feature_the)
        return "THE";
    else if (f == &aarch64_feature_d128_the)
        return "D128_THE";
    else if (f == &aarch64_feature_sve_b16b16_sve2)
        return "SVE_B16B16_SVE2";
    else if (f == &aarch64_feature_sve_b16b16_sme2)
        return "SVE_B16B16_SME2";
    else if (f == &aarch64_feature_sme_b16b16)
        return "SME_B16B16";
    else if (f == &aarch64_feature_sme2p1)
        return "SME2P1";
    else if (f == &aarch64_feature_sve2p1)
        return "SVE2P1";
    else if (f == &aarch64_feature_sve_f16f32mm)
        return "SVE_F16F32MM";
    else if (f == &aarch64_feature_f8f32mm)
        return "F8F32MM";
    else if (f == &aarch64_feature_f8f32mm_sve2)
        return "F8F32MM_SVE2";
    else if (f == &aarch64_feature_f8f16mm)
        return "F8F16MM";
    else if (f == &aarch64_feature_f8f16mm_sve2)
        return "F8F16MM_SVE2";
    else if (f == &aarch64_feature_sve_aes2)
        return "SVE_AES2";
    else if (f == &aarch64_feature_rcpc3)
        return "RCPC3";
    else if (f == &aarch64_feature_cpa)
        return "CPA";
    else if (f == &aarch64_feature_cpa_sve)
        return "CPA_SVE";
    else if (f == &aarch64_feature_faminmax)
        return "FAMINMAX";
    else if (f == &aarch64_feature_faminmax_sve2)
        return "FAMINMAX_SVE2";
    else if (f == &aarch64_feature_faminmax_sme2)
        return "FAMINMAX_SME2";
    else if (f == &aarch64_feature_fp8)
        return "FP8";
    else if (f == &aarch64_feature_fp8_sve2)
        return "FP8_SVE2";
    else if (f == &aarch64_feature_fp8_sme2)
        return "FP8_SME2";
    else if (f == &aarch64_feature_sve_bfscale)
        return "SVE_BFSCALE";
    else if (f == &aarch64_feature_sve_bfscale_sme2)
        return "SVE_BFSCALE_SME2";
    else if (f == &aarch64_feature_lut)
        return "LUT";
    else if (f == &aarch64_feature_lut_sve2)
        return "LUT_SVE2";
    else if (f == &aarch64_feature_brbe)
        return "BRBE";
    else if (f == &aarch64_feature_lutv2_sme2)
        return "LUTV2_SME2";
    else if (f == &aarch64_feature_lutv2_sme2p1)
        return "LUTV2_SME2P1";
    else if (f == &aarch64_feature_fp8fma)
        return "FP8FMA";
    else if (f == &aarch64_feature_fp8dot4)
        return "FP8DOT4";
    else if (f == &aarch64_feature_fp8dot2)
        return "FP8DOT2";
    else if (f == &aarch64_feature_fp8fma_sve)
        return "FP8FMA_SVE";
    else if (f == &aarch64_feature_fp8dot4_sve)
        return "FP8DOT4_SVE";
    else if (f == &aarch64_feature_fp8dot2_sve)
        return "FP8DOT2_SVE";
    else if (f == &aarch64_feature_sme_f8f32)
        return "SME_F8F32";
    else if (f == &aarch64_feature_sme_f8f16)
        return "SME_F8F16";
    else if (f == &aarch64_feature_sme_f16f16_f8f16)
        return "SME_F16F16_F8F16";
    else if (f == &aarch64_feature_sme_f16f16)
        return "SME_F16F16";
    else if (f == &aarch64_feature_sve2p1_sme)
        return "SVE2P1_SME";
    else if (f == &aarch64_feature_sve2p1_sme2)
        return "SVE2P1_SME2";
    else if (f == &aarch64_feature_sve2p1_sme2p1)
        return "SVE2P1_SME2P1";
    else if (f == &aarch64_feature_sme2p2)
        return "SME2P2";
    else if (f == &aarch64_feature_sve_sme2p2)
        return "SVE_SME2P2";
    else if (f == &aarch64_feature_sve2p2_sme2p2)
        return "SVE2P2_SME2P2";
    else if (f == &aarch64_feature_gcie)
        return "GCIE";
    else if (f == &aarch64_feature_sve_ssve_fexpa)
        return "SVE_SSVE_FEXPA";
    else if (f == &aarch64_feature_sme_tmop)
        return "SME_TMOP";
    else if (f == &aarch64_feature_sme_tmop_b16b16)
        return "SME_TMOP_B16B16";
    else if (f == &aarch64_feature_sme_tmop_f16f16)
        return "SME_TMOP_F16F16";
    else if (f == &aarch64_feature_sme_tmop_f8f16)
        return "SME_TMOP_F8F16";
    else if (f == &aarch64_feature_sme_tmop_f8f32)
        return "SME_TMOP_F8F32";
    else if (f == &aarch64_feature_sme_mop4)
        return "SME_MOP4";
    else if (f == &aarch64_feature_sme_mop4_b16b16)
        return "SME_MOP4_B16B16";
    else if (f == &aarch64_feature_sme_mop4_f16f16)
        return "SME_MOP4_F16F16";
    else if (f == &aarch64_feature_sme_mop4_f64f64)
        return "SME_MOP4_F64F64";
    else if (f == &aarch64_feature_sme_mop4_f8f16)
        return "SME_MOP4_F8F16";
    else if (f == &aarch64_feature_sme_mop4_f8f32)
        return "SME_MOP4_F8F32";
    else if (f == &aarch64_feature_sme_mop4_i16i64)
        return "SME_MOP4_I16I64";
    else if (f == &aarch64_feature_sve2p3)
        return "SVE2P3";
    else if (f == &aarch64_feature_sme2p3)
        return "SME2P3";
    else if (f == &aarch64_feature_sve2p3_sme2p3)
        return "SVE2P3_SME2P3";
    else if (f == &aarch64_feature_f16f32dot)
        return "F16F32DOT";
    else if (f == &aarch64_feature_f16f32mm)
        return "F16F32MM";
    else if (f == &aarch64_feature_f16mm)
        return "F16MM";
    else if (f == &aarch64_feature_f16mm_sve2p2)
        return "F16MM_SVE2P2";
    else if (f == &aarch64_feature_sve_b16mm)
        return "SVE_B16MM";
    else if (f == &aarch64_feature_POE2)
        return "POE2";
    else if (f == &aarch64_feature_tev)
        return "TEV";
    else if (f == &aarch64_feature_mpamv2)
        return "MPAMV2";
    else
        throw std::runtime_error("unknown features set");
}

int main() {
    puts("[\n");

    constexpr auto bc_opcode = 0x54000000;
    auto bc_index = 0;
    constexpr auto len = std::size(aarch64_opcode_table);
    for (auto i = 0; i < len; ++i) {
        const auto &x = aarch64_opcode_table[i];

        if (!x.name)
            break;

        const auto iclass = static_cast<aarch64_insn_class>(x.iclass);

        printf("{\n");

        printf("\t\"mnemonic\": \"%s\",\n", x.name);

        {
            std::vector<std::string> aliases;
            for (auto a = aarch64_find_next_alias_opcode(&x); a;
                 a = aarch64_find_next_alias_opcode(a))
                aliases.emplace_back(std::to_string(a - aarch64_opcode_table));

            // Special handling for the branch pseudo-instructions
            if (x.opcode == bc_opcode && x.mask == 0xff000010)
                bc_index = i;
            else if ((x.opcode & 0xfffffff0) == bc_opcode)
                aliases.emplace_back(std::to_string(bc_index));

            printf("\t\"aliases\": %s,\n",
                   to_str_array(aliases, false).c_str());
        }

        uint32_t mask = x.mask;

        const uint32_t lost_dont_care = x.opcode ^ (x.mask & x.opcode); // == opcode & !mask
        if (lost_dont_care) {
            fprintf(stderr, "%s: lost_dont_care: %08x\n", x.name, lost_dont_care);
            mask |= lost_dont_care;
        }

        printf("\t\"opcode\": \"0x%08x\",\n", x.opcode);
        printf("\t\"mask\": \"0x%08x\",\n", mask);
        printf("\t\"class\": \"%s\",\n", iclass_name(iclass));
        printf("\t\"feature_set\": \"%s\",\n", feature_set_name(x.avariant));
        printf("\t\"description\": \"%s\",\n", iclass_description(iclass));

        std::vector<std::string> operands;
        std::vector<aarch64_operand> operand_info;
        {
            for (const auto o : x.operands) {
                if (!o)
                    break;

                const auto name = std::string(operand_name(o));
                operands.push_back(name);

                operand_info.push_back(aarch64_operands[o]);
            }
        }

        std::vector<std::vector<std::string>> quals;
        {
            for (const auto &ql : x.qualifiers_list) {
                std::vector<std::string> qs;
                for (const auto &q : ql) {
                    if (!q)
                        break;

                    qs.emplace_back(
                        qual_name(static_cast<aarch64_opnd_qualifier>(q)));
                }
                quals.push_back(qs);
            }
        }

        printf("\t\"operands\": [\n");

        for (auto oi = 0; oi < operands.size(); ++oi) {
            const auto &o = operands[oi];
            std::vector<std::string> oquals;

            for (const auto &q : quals) {
                if (oi >= q.size())
                    break;

                oquals.push_back(q[oi]);
            }

            printf("\t\t{\n");
            printf("\t\t\t\"kind\": \"%s\",\n", o.c_str());
            printf("\t\t\t\"class\": \"%s\",\n",
                   operand_class_name(operand_info[oi].op_class));
            printf("\t\t\t\"qualifiers\": %s,\n", to_str_array(oquals).c_str());

            const auto &op_info = operand_info[oi];
            std::vector<std::string> field_info;
            for (const auto &f : op_info.fields) {
                if (!f)
                    break;

                auto field_spec = std::string(field_name(f));
                field_spec += ":";
                field_spec += std::to_string(aarch64_fields[f].num);
                field_spec += ":";
                field_spec += std::to_string(aarch64_fields[f].width);

                field_info.emplace_back(field_spec);
            }
            if (x.flags & F_COND)
                field_info.emplace_back("cond:0:4");
            printf("\t\t\t\"bit_fields\": %s",
                   to_str_array(field_info).c_str());

            printf("\n\t\t}");
            if (oi + 1 < operands.size()) {
                printf(",");
            }
            printf("\n");
        }

        printf("\t],\n");

        printf("\t\"flags\": \"%s\",\n", flags_str(x.flags).c_str());

        if (len - i != 2)
            printf("\t\"index\": %d },\n", i);
        else
            printf("\t\"index\": %d }\n", i);
    }

    puts("\n]");

    return 0;
}
