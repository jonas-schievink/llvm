//===-- Mos6502ELFObjectWriter.cpp - Mos6502 ELF Writer ---------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "MCTargetDesc/Mos6502MCTargetDesc.h"
#include "llvm/MC/MCELFObjectWriter.h"
#include "llvm/MC/MCFixup.h"
#include "llvm/Support/ErrorHandling.h"

using namespace llvm;

namespace {
class Mos6502ELFObjectWriter : public MCELFObjectTargetWriter {
public:
  Mos6502ELFObjectWriter(uint8_t OSABI);

  ~Mos6502ELFObjectWriter() override;

protected:
  unsigned GetRelocType(const MCValue &Target, const MCFixup &Fixup,
                        bool IsPCRel) const override;
};
}

Mos6502ELFObjectWriter::Mos6502ELFObjectWriter(uint8_t OSABI)
    : MCELFObjectTargetWriter(/*Is64Bit*/ true, OSABI, ELF::EM_NONE,
                              /*HasRelocationAddend*/ false) {}

Mos6502ELFObjectWriter::~Mos6502ELFObjectWriter() {}

unsigned Mos6502ELFObjectWriter::GetRelocType(const MCValue &Target,
                                          const MCFixup &Fixup,
                                          bool IsPCRel) const {
  // determine the type of the relocation
  switch ((unsigned)Fixup.getKind()) {
  default:
    llvm_unreachable("invalid fixup kind!");
  case FK_SecRel_8:
    return ELF::R_X86_64_64;
  case FK_SecRel_4:
    return ELF::R_X86_64_PC32;
  case FK_Data_8:
    return IsPCRel ? ELF::R_X86_64_PC64 : ELF::R_X86_64_64;
  case FK_Data_4:
    return IsPCRel ? ELF::R_X86_64_PC32 : ELF::R_X86_64_32;
  }
}

MCObjectWriter *llvm::createMos6502ELFObjectWriter(raw_pwrite_stream &OS,
                                                   uint8_t OSABI) {
  MCELFObjectTargetWriter *MOTW = new Mos6502ELFObjectWriter(OSABI);
  return createELFObjectWriter(MOTW, OS, /*little endian*/true);
}
