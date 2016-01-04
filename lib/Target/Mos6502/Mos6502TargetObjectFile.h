//===-- Mos6502TargetObjectFile.h - Mos6502 Object Info ---------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502TARGETOBJECTFILE_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502TARGETOBJECTFILE_H

#include "Mos6502Section.h"
#include "llvm/Target/TargetLoweringObjectFile.h"
#include <string>

namespace llvm {
class GlobalVariable;
class Module;

class Mos6502TargetObjectFile : public TargetLoweringObjectFile {

public:
  Mos6502TargetObjectFile() {
    TextSection = nullptr;
    DataSection = nullptr;
    BSSSection = nullptr;
    ReadOnlySection = nullptr;

    StaticCtorSection = nullptr;
    StaticDtorSection = nullptr;
    LSDASection = nullptr;
    EHFrameSection = nullptr;
    DwarfAbbrevSection = nullptr;
    DwarfInfoSection = nullptr;
    DwarfLineSection = nullptr;
    DwarfFrameSection = nullptr;
    DwarfPubTypesSection = nullptr;
    DwarfDebugInlineSection = nullptr;
    DwarfStrSection = nullptr;
    DwarfLocSection = nullptr;
    DwarfARangesSection = nullptr;
    DwarfRangesSection = nullptr;
  }

  virtual ~Mos6502TargetObjectFile() {}

  void Initialize(MCContext &ctx, const TargetMachine &TM) override {
    TargetLoweringObjectFile::Initialize(ctx, TM);
    TextSection = new Mos6502Section(MCSection::SV_ELF, SectionKind::getText());
    DataSection = new Mos6502Section(MCSection::SV_ELF, SectionKind::getData());
    BSSSection = new Mos6502Section(MCSection::SV_ELF, SectionKind::getBSS());
    ReadOnlySection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getReadOnly());

    StaticCtorSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    StaticDtorSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    LSDASection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    EHFrameSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfAbbrevSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfInfoSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfLineSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfFrameSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfPubTypesSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfDebugInlineSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfStrSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfLocSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfARangesSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
    DwarfRangesSection =
        new Mos6502Section(MCSection::SV_ELF, SectionKind::getMetadata());
  }

  MCSection *getSectionForConstant(const DataLayout &DL, SectionKind Kind,
                                   const Constant *C) const override {
    return ReadOnlySection;
  }

  MCSection *getExplicitSectionGlobal(const GlobalValue *GV, SectionKind Kind,
                                      Mangler &Mang,
                                      const TargetMachine &TM) const override {
    return DataSection;
  }

  MCSection *SelectSectionForGlobal(const GlobalValue *GV, SectionKind Kind,
                                    Mangler &Mang,
                                    const TargetMachine &TM) const override {
    if (Kind.isText())
      return TextSection;
    if (Kind.isData())
      return DataSection;

    // FIXME
    llvm_unreachable("couldn't SelectSectionForGlobal");
  }
};

} // end namespace llvm

#endif
