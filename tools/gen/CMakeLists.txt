set(TARGET
        aarch64-gen
)

set(INC
        ../../include/opcode/aarch64.h
        ../../opcodes/aarch64-tbl.h
        ../../opcodes/aarch64-opc.h
        ../../opcodes/aarch64-dis.h
        ../../include/bfd.h
        ../../include/dis-asm.h
        ../../include/config.h
        ../../include/ansidecl.h
        ../../include/aarch64-insn-bits.h
)

set(SRC
        ../../opcodes/aarch64-gen.c
)

add_executable(${TARGET}
        ${SRC} ${INC}
)

target_include_directories(${TARGET} PRIVATE
        ../../include
        ../../opcodes
)
