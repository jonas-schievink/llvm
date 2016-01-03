//===-- Mos6502Subtarget.cpp - Mos6502 Subtarget Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Mos6502 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "Mos6502Subtarget.h"
#include "Mos6502.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "Mos6502-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "Mos6502GenSubtargetInfo.inc"

void Mos6502Subtarget::anchor() {}

Mos6502Subtarget::Mos6502Subtarget(const Triple &TT, const std::string &CPU,
                           const std::string &FS, const TargetMachine &TM)
    : Mos6502GenSubtargetInfo(TT, CPU, FS), InstrInfo(), FrameLowering(*this),
      TLInfo(TM, *this) {}
