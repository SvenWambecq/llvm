set(LLVM_TARGET_DEFINITIONS Neo.td)

tablegen(LLVM NeoGenRegisterInfo.inc -gen-register-info)
#tablegen(LLVM NeoGenInstrInfo.inc -gen-instr-info)
#tablegen(LLVM NeoGenDisassemblerTables.inc -gen-disassembler)
#tablegen(LLVM NeoGenMCCodeEmitter.inc -gen-emitter)
#tablegen(LLVM NeoGenAsmWriter.inc -gen-asm-writer)
#tablegen(LLVM NeoGenAsmMatcher.inc -gen-asm-matcher)
#tablegen(LLVM NeoGenDAGISel.inc -gen-dag-isel)
#tablegen(LLVM NeoGenSubtargetInfo.inc -gen-subtarget)
#tablegen(LLVM NeoGenCallingConv.inc -gen-callingconv)
add_public_tablegen_target(NeoCommonTableGen)

add_llvm_target(NeoCodeGen
  NeoRegisterInfo.cpp
  )

add_subdirectory(TargetInfo)
#add_subdirectory(MCTargetDesc)
#add_subdirectory(InstPrinter)
#add_subdirectory(AsmParser)
#add_subdirectory(Disassembler)
