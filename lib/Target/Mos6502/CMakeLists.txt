set(LLVM_TARGET_DEFINITIONS Mos6502.td)

tablegen(LLVM Mos6502GenRegisterInfo.inc -gen-register-info)
tablegen(LLVM Mos6502GenInstrInfo.inc -gen-instr-info)
tablegen(LLVM Mos6502GenAsmWriter.inc -gen-asm-writer)
tablegen(LLVM X86GenAsmMatcher.inc -gen-asm-matcher)
tablegen(LLVM Mos6502GenDAGISel.inc -gen-dag-isel)
tablegen(LLVM Mos6502GenMCCodeEmitter.inc -gen-emitter)
tablegen(LLVM Mos6502GenCallingConv.inc -gen-callingconv)
tablegen(LLVM Mos6502GenSubtargetInfo.inc -gen-subtarget)
add_public_tablegen_target(Mos6502CommonTableGen)

add_llvm_target(Mos6502CodeGen
  Mos6502AsmPrinter.cpp
  Mos6502FrameLowering.cpp
  Mos6502InstrInfo.cpp
  Mos6502ISelDAGToDAG.cpp
  Mos6502ISelLowering.cpp
  Mos6502MCInstLower.cpp
  Mos6502RegisterInfo.cpp
  Mos6502Subtarget.cpp
  Mos6502TargetMachine.cpp
  )

add_subdirectory(InstPrinter)
add_subdirectory(TargetInfo)
add_subdirectory(MCTargetDesc)
