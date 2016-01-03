//===-- Mos6502FrameLowering.h - Define Mos6502 frame lowering --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This class implements Mos6502-specific bits of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502FRAMELOWERING_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502FRAMELOWERING_H

#include "llvm/Target/TargetFrameLowering.h"

namespace llvm {
class Mos6502Subtarget;

class Mos6502FrameLowering : public TargetFrameLowering {
public:
  explicit Mos6502FrameLowering(const Mos6502Subtarget &sti)
      : TargetFrameLowering(TargetFrameLowering::StackGrowsDown, 1, 0) {}
  // The "1" is the stack alignment (there never is any alignment restriction or
  // guarantee on the Mos6502). The "0" defines the "Local area offset".

  // No prologue/epilogue stuff going on (gotta save the cycles)
  void emitPrologue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}
  void emitEpilogue(MachineFunction &MF,
                    MachineBasicBlock &MBB) const override {}

  bool hasFP(const MachineFunction &MF) const override {
    // We can't spare a frame pointer
    return false;
  }
  //void determineCalleeSaves(MachineFunction &MF, BitVector &SavedRegs,
  //                          RegScavenger *RS) const override;

  void eliminateCallFramePseudoInstr(MachineFunction &MF,
                                     MachineBasicBlock &MBB,
                                     MachineBasicBlock::iterator MI)
                                     const override {
    MBB.erase(MI);
  }
};
} // end namespace llvm

#endif
