//===-- Mos6502TargetInfo.cpp - Mos6502 Target Implementation ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Mos6502.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

namespace llvm {
Target TheMos6502Target;
}

extern "C" void LLVMInitializeMos6502TargetInfo() {
  RegisterTarget<llvm::Triple::mos6502> X(
      TheMos6502Target, "mos6502", "MOS Technology 6502");
}
