set(TARGET
        aarch64-insn-dump
)

set(INC
        ../include/opcode/aarch64.h
        ../opcodes/aarch64-tbl.h
        ../include/bfd.h
        ../include/dis-asm.h
        ../include/config.h
        ../include/ansidecl.h
        ../include/aarch64-insn-bits.h
)

set(SRC
        aarch64-insn-dump.cpp
        ../opcodes/aarch64-opc-2.c
)

add_executable(${TARGET}
        ${SRC} ${INC}
)

target_include_directories(${TARGET} PRIVATE
        ../include
        ../opcodes
)
