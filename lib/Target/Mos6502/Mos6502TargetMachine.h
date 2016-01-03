//===-- Mos6502TargetMachine.h - The Mos6502 TargetMachine ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Mos6502 specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502TARGETMACHINE_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502TARGETMACHINE_H

#include "Mos6502Subtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class Mos6502TargetMachine : public LLVMTargetMachine {
  std::unique_ptr<TargetLoweringObjectFile> TLOF;
  Mos6502Subtarget Subtarget;

public:
  Mos6502TargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                   StringRef FS, const TargetOptions &Options, Reloc::Model RM,
                   CodeModel::Model CM, CodeGenOpt::Level OL);

  const Mos6502Subtarget *getSubtargetImpl() const { return &Subtarget; }
  const Mos6502Subtarget *getSubtargetImpl(const Function &) const override {
    return &Subtarget;
  }

  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;

  TargetLoweringObjectFile *getObjFileLowering() const override {
    return TLOF.get();
  }
};
} // end namespace llvm

#endif
