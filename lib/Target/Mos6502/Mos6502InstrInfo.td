//===-- Mos6502InstrInfo.td - Instructions of the Mos6502 --*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file describes the Mos6502 instructions in TableGen format.
//
//===----------------------------------------------------------------------===//


//===----------------------------------------------------------------------===//
// Operands
//===----------------------------------------------------------------------===//

/// Immediate value
def MEMimm : Operand<i8> {
  let MIOperandInfo = (ops i8imm);
}

//===----------------------------------------------------------------------===//
// Abstract instruction classes and encoding
//===----------------------------------------------------------------------===//

class Mos6502Instr<dag outs,
                   dag ins,
                   string fmt,
                   list<dag> pattern>
                   : Instruction {
  field bits<8> Inst;
  let Namespace = "Mos6502";
  let OutOperandList = outs;
  let InOperandList = ins;
  let AsmString = fmt;
  let Pattern = pattern;
}

class GroupOneInstr<bits<3> op,
                    bits<3> mode,
                    dag outs,
                    dag ins,
                    string fmt,
                    list<dag> pattern>
                    : Mos6502Instr<outs, ins, fmt, pattern> {
  let Inst{7-5} = op;
  let Inst{4-2} = mode;
  let Inst{0-1} = 0b01;
}

/// Define a "Group One" opcode supporting the 8 addressing modes
/// Indexed Indirect (0b000), Zero Page (0b001), Immediate (0b010),
/// Absolute (0b011), Indirect Indexed (0b100), Zero Page Indexed by X (0b101),
/// Absolute Indexed by Y (0b110), Absolute Indexed by X (0b111).
///
/// Group One instructions are encoded as 0bIIIAAA01, where A selects one of the
/// 8 addressing modes (as shown above) and I selects the instruction. The 3 I
/// bits are passed as the `enc` parameter.
multiclass GroupOne<string opstrn, bits<3> enc, dag pat> {
  def imm : GroupOneInstr<enc, 0b010, (outs Acc:$acc),
                          (ins i8imm:$imm),
                          !strconcat(opstrn, " #$imm"),
                          [pat]>;
}

defm LDA : GroupOne<"lda", 0b000 /*FIXME*/, (set i8:$acc, (load i8:$imm))>;
