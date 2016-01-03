//===-- Mos6502MCCodeEmitter.cpp - Convert Mos6502 code to machine code -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the Mos6502MCCodeEmitter class.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/Mos6502MCTargetDesc.h"
#include "llvm/MC/MCCodeEmitter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/MC/MCInst.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/MC/MCSymbol.h"
#include "llvm/ADT/Statistic.h"
#include "llvm/Support/raw_ostream.h"
using namespace llvm;

#define DEBUG_TYPE "mccodeemitter"

namespace {
class Mos6502MCCodeEmitter : public MCCodeEmitter {
  Mos6502MCCodeEmitter(const Mos6502MCCodeEmitter &) = delete;
  void operator=(const Mos6502MCCodeEmitter &) = delete;
  const MCRegisterInfo &MRI;

public:
  Mos6502MCCodeEmitter(const MCRegisterInfo &mri)
    : MRI(mri) {}

  ~Mos6502MCCodeEmitter() {}

  // getBinaryCodeForInstr - TableGen'erated function for getting the
  // binary encoding for an instruction.
  uint64_t getBinaryCodeForInstr(const MCInst &MI,
                                 SmallVectorImpl<MCFixup> &Fixups,
                                 const MCSubtargetInfo &STI) const;

  // getMachineOpValue - Return binary encoding of operand. If the machin
  // operand requires relocation, record the relocation and return zero.
  unsigned getMachineOpValue(const MCInst &MI, const MCOperand &MO,
                             SmallVectorImpl<MCFixup> &Fixups,
                             const MCSubtargetInfo &STI) const;

  uint64_t getMemoryOpValue(const MCInst &MI, unsigned Op,
                            SmallVectorImpl<MCFixup> &Fixups,
                            const MCSubtargetInfo &STI) const;

  void encodeInstruction(const MCInst &MI, raw_ostream &OS,
                         SmallVectorImpl<MCFixup> &Fixups,
                         const MCSubtargetInfo &STI) const override;
};
}

MCCodeEmitter *llvm::createMos6502MCCodeEmitter(const MCInstrInfo &MCII,
                                            const MCRegisterInfo &MRI,
                                            MCContext &Ctx) {
  return new Mos6502MCCodeEmitter(MRI);
}

unsigned Mos6502MCCodeEmitter::getMachineOpValue(const MCInst &MI,
                                             const MCOperand &MO,
                                             SmallVectorImpl<MCFixup> &Fixups,
                                             const MCSubtargetInfo &STI) const {
  if (MO.isReg())
    return MRI.getEncodingValue(MO.getReg());
  if (MO.isImm())
    return static_cast<unsigned>(MO.getImm());

  assert(MO.isExpr());

  const MCExpr *Expr = MO.getExpr();

  assert(Expr->getKind() == MCExpr::SymbolRef);

  // bb label
  Fixups.push_back(MCFixup::create(0, Expr, FK_PCRel_2));

  return 0;
}

static uint8_t SwapBits(uint8_t Val)
{
  return (Val & 0x0F) << 4 | (Val & 0xF0) >> 4;
}

void Mos6502MCCodeEmitter::encodeInstruction(const MCInst &MI, raw_ostream &OS,
                                         SmallVectorImpl<MCFixup> &Fixups,
                                         const MCSubtargetInfo &STI) const {
  unsigned Opcode = MI.getOpcode();
  support::endian::Writer<support::little> LE(OS);
  support::endian::Writer<support::big> BE(OS);

  // Get instruction encoding and emit it
  uint64_t Value = getBinaryCodeForInstr(MI, Fixups, STI);
  LE.write<uint8_t>(Value >> 56);
  LE.write<uint8_t>((Value >> 48) & 0xff);
  LE.write<uint16_t>((Value >> 32) & 0xffff);
  LE.write<uint32_t>(Value & 0xffffFFFF);

  // FIXME I think this method can be deleted
}

// Encode Mos6502 Memory Operand
uint64_t Mos6502MCCodeEmitter::getMemoryOpValue(const MCInst &MI, unsigned Op,
                                            SmallVectorImpl<MCFixup> &Fixups,
                                            const MCSubtargetInfo &STI) const {
  uint64_t Encoding;
  const MCOperand Op1 = MI.getOperand(1);
  assert(Op1.isReg() && "First operand is not register.");
  Encoding = MRI.getEncodingValue(Op1.getReg());
  Encoding <<= 16;
  MCOperand Op2 = MI.getOperand(2);
  assert(Op2.isImm() && "Second operand is not immediate.");
  Encoding |= Op2.getImm() & 0xffff;
  return Encoding;
}

#include "Mos6502GenMCCodeEmitter.inc"
