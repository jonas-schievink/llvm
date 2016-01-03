//===-- Mos6502.h - Top-level interface for Mos6502 representation ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502_H

#include "MCTargetDesc/Mos6502MCTargetDesc.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
class Mos6502TargetMachine;

FunctionPass *createMos6502ISelDag(Mos6502TargetMachine &TM);
} // end namespace llvm

#endif
