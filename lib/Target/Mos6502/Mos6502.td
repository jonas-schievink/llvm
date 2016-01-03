//===-- Mos6502.td - Describe the Mos6502 Target Machine ---*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

include "Mos6502RegisterInfo.td"
include "Mos6502CallingConv.td"
include "Mos6502InstrInfo.td"

//===----------------------------------------------------------------------===//
// Supported Processors
//===----------------------------------------------------------------------===//

// (this could be used to implement support for the 65816)

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic", []>;

//===----------------------------------------------------------------------===//
// AsmWriter definition
//===----------------------------------------------------------------------===//

def Mos6502InstPrinter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  bit isMCAsmWriter = 1;
}

/*
def Mos6502AsmParserVariant : AsmParserVariant {
  int Variant = 0;
  string Name = "Mos6502";
  string BreakCharacters = ".";
}
*/

//===----------------------------------------------------------------------===//
// Mos6502 Target Definition
//===----------------------------------------------------------------------===//

def Mos6502InstrInfo : InstrInfo;

def Mos6502 : Target {
  let InstructionSet = Mos6502InstrInfo;
  let AssemblyWriters = [Mos6502InstPrinter];
//  let AssemblyParserVariants = [Mos6502AsmParserVariant];
}
