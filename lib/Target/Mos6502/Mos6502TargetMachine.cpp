//===-- Mos6502TargetMachine.cpp - Define TargetMachine for Mos6502 -------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// Implements the info about Mos6502 target spec.
//
//===----------------------------------------------------------------------===//

#include "Mos6502.h"
#include "Mos6502TargetMachine.h"
#include "llvm/CodeGen/TargetLoweringObjectFileImpl.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/Support/FormattedStream.h"
#include "llvm/Support/TargetRegistry.h"
#include "llvm/Target/TargetOptions.h"
using namespace llvm;

extern "C" void LLVMInitializeMos6502Target() {
  RegisterTargetMachine<Mos6502TargetMachine> Z(TheMos6502Target);
}

Mos6502TargetMachine::Mos6502TargetMachine(const Target &T, const Triple &TT,
                                   StringRef CPU, StringRef FS,
                                   const TargetOptions &Options,
                                   Reloc::Model RM, CodeModel::Model CM,
                                   CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, "e-p:16:8", TT, CPU, FS, Options, RM, CM, OL),
      TLOF(make_unique<TargetLoweringObjectFileELF>()),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

namespace {
// Mos6502 Code Generator Pass Configuration Options.
class Mos6502PassConfig : public TargetPassConfig {
public:
  Mos6502PassConfig(Mos6502TargetMachine *TM, PassManagerBase &PM)
      : TargetPassConfig(TM, PM) {}

  Mos6502TargetMachine &getMos6502TargetMachine() const {
    return getTM<Mos6502TargetMachine>();
  }

  bool addInstSelector() override;
};
}

TargetPassConfig *Mos6502TargetMachine::createPassConfig(PassManagerBase &PM) {
  return new Mos6502PassConfig(this, PM);
}

// Install an instruction selector pass using
// the ISelDag to gen Mos6502 code.
bool Mos6502PassConfig::addInstSelector() {
  addPass(createMos6502ISelDag(getMos6502TargetMachine()));

  return false;
}
