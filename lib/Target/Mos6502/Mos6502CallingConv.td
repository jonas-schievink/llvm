//===-- Mos6502CallingConv.td - Calling Conventions --------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This describes the calling conventions for the Mos6502 architecture.
//
//===----------------------------------------------------------------------===//

// Return 8-bit values in the accumulator
def RetCC_Mos6502 : CallingConv<[CCIfType<[i8], CCAssignToReg<[ A ]>>]>;

// Mos6502 Default Calling convention.
def CC_Mos6502 : CallingConv<[
  // Pass 8-bit arguments in our 3 registers
  CCIfType<[ i8 ], CCAssignToReg<[ A, X, Y ]>>,

  // Assign everything else to the stack
  // FIXME: Is the size/alignment okay?
  // FIXME: This can overflow the stack really quickly!
  CCAssignToStack<0, 0>
]>;

// Just let the callee save all regs. There aren't that many, after all...
def CSR : CalleeSavedRegs<(add A, X, Y)>;
