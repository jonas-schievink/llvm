//===-- Mos6502Subtarget.h - Define Subtarget for the Mos6502 ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Mos6502 specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502SUBTARGET_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502SUBTARGET_H

#include "Mos6502FrameLowering.h"
#include "Mos6502ISelLowering.h"
#include "Mos6502InstrInfo.h"
#include "llvm/Target/TargetSelectionDAGInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetMachine.h"
#include "llvm/Target/TargetSubtargetInfo.h"

#define GET_SUBTARGETINFO_HEADER
#include "Mos6502GenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class Mos6502Subtarget : public Mos6502GenSubtargetInfo {
  virtual void anchor();
  Mos6502InstrInfo InstrInfo;
  Mos6502FrameLowering FrameLowering;
  Mos6502TargetLowering TLInfo;
  TargetSelectionDAGInfo TSInfo;

public:
  // This constructor initializes the data members to match that
  // of the specified triple.
  Mos6502Subtarget(const Triple &TT, const std::string &CPU, const std::string &FS,
               const TargetMachine &TM);

  // ParseSubtargetFeatures - Parses features string setting specified
  // subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);

  const Mos6502InstrInfo *getInstrInfo() const override { return &InstrInfo; }
  const Mos6502FrameLowering *getFrameLowering() const override {
    return &FrameLowering;
  }
  const Mos6502TargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const TargetSelectionDAGInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  }
  const TargetRegisterInfo *getRegisterInfo() const override {
    return &InstrInfo.getRegisterInfo();
  }
};
} // end namespace llvm

#endif
