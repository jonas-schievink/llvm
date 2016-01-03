//===-- Mos6502FrameLowering.cpp - Mos6502 Frame Information --------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Mos6502 implementation of TargetFrameLowering class.
//
//===----------------------------------------------------------------------===//

#include "Mos6502FrameLowering.h"
#include "Mos6502InstrInfo.h"
#include "Mos6502Subtarget.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/CodeGen/MachineRegisterInfo.h"

using namespace llvm;

// TODO: Do we need anything in here? If not, remove.
