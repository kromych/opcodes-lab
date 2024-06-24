set(TARGET
        aarch64-dis
)

add_definitions(-DBUILDING_DIS_TOOL)

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
        ../../opcodes/aarch64-dis.c
        ../../opcodes/aarch64-dis-2.c
        ../../opcodes/aarch64-opc.c
        ../../opcodes/aarch64-opc-2.c
        ../../include/obstack.h
        ../../opcodes/obstack.c
)

add_executable(${TARGET}
        ${SRC} ${INC}
)

target_include_directories(${TARGET} PRIVATE
        ../../include
        ../../opcodes
)
