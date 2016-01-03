//===-- Mos6502RegisterInfo.td - Mos6502 Register defs -----*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Mos6502 register file
//===----------------------------------------------------------------------===//

class Mos6502Reg<bits<16> num, string name> : Register<name>
{
  field bits<16> Num = num;
  // FIXME let HWEncoding = num; ?
  let Namespace = "Mos6502";
}

def A  : Mos6502Reg<0, "A">,  DwarfRegNum<[0]>;
def X  : Mos6502Reg<1, "X">,  DwarfRegNum<[1]>;
def Y  : Mos6502Reg<2, "Y">,  DwarfRegNum<[2]>;
def SP : Mos6502Reg<3, "SP">, DwarfRegNum<[3]>;
def P  : Mos6502Reg<4, "P">,  DwarfRegNum<[4]>;

//===----------------------------------------------------------------------===//
//  Register classes
//===----------------------------------------------------------------------===//

def Acc    : RegisterClass<"Mos6502", [i8], 0, (add A)>;
def Index  : RegisterClass<"Mos6502", [i8], 0, (add X, Y)>;
def Status : RegisterClass<"Mos6502", [i8], 0, (add P)>;
