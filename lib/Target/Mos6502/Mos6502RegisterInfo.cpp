//===-- Mos6502RegisterInfo.cpp - Mos6502 Register Information ------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Mos6502 implementation of the TargetRegisterInfo
// class.
//
//===----------------------------------------------------------------------===//

#include "Mos6502.h"
#include "Mos6502RegisterInfo.h"
#include "Mos6502Subtarget.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/RegisterScavenging.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetInstrInfo.h"

#define GET_REGINFO_TARGET_DESC
#include "Mos6502GenRegisterInfo.inc"
using namespace llvm;

// FIXME: Accumulator is probably not right
Mos6502RegisterInfo::Mos6502RegisterInfo()
    : Mos6502GenRegisterInfo(Mos6502::A) {}

const MCPhysReg *
Mos6502RegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return CSR_SaveList;
}

BitVector Mos6502RegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}

void Mos6502RegisterInfo::eliminateFrameIndex(MachineBasicBlock::iterator II,
                                              int SPAdj, unsigned FIOperandNum,
                                              RegScavenger *RS) const {
  assert(SPAdj == 0 && "Unexpected");

  unsigned i = 0;
  MachineInstr &MI = *II;
  MachineFunction &MF = *MI.getParent()->getParent();
  DebugLoc DL = MI.getDebugLoc();

  while (!MI.getOperand(i).isFI()) {
    ++i;
    assert(i < MI.getNumOperands() && "Instr doesn't have FrameIndex operand!");
  }

  unsigned FrameReg = getFrameRegister(MF);
  int FrameIndex = MI.getOperand(i).getIndex();
  const TargetInstrInfo &TII = *MF.getSubtarget().getInstrInfo();
  MachineBasicBlock &MBB = *MI.getParent();

  int Offset = MF.getFrameInfo()->getObjectOffset(FrameIndex) +
               MI.getOperand(i + 1).getImm();

  if (!isInt<32>(Offset))
    llvm_unreachable("bug in frame offset");

  MI.getOperand(i).ChangeToRegister(FrameReg, false);
  MI.getOperand(i + 1).ChangeToImmediate(Offset);
}

unsigned Mos6502RegisterInfo::getFrameRegister(const MachineFunction &MF) const {
  // FIXME Is this okay?
  //llvm_unreachable("getFrameRegister - there is no frame register");
  return Mos6502::A;
}
