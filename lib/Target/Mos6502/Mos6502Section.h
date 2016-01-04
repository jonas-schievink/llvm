//===- Mos6502Section.h - Mos6502-specific section --------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Mos6502Section class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502SECTION_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502SECTION_H

#include "llvm/IR/GlobalVariable.h"
#include "llvm/MC/MCSectionELF.h"
#include <vector>

namespace llvm {

/// Mos6502 assembly uses the ".segment" directive as an equivalent of
/// ".section", which has different syntax. It would be nice if LLVM allowed us
/// to tune this without making our own class (along the lines of MCAsmInfo).
class Mos6502Section final : public MCSection {
  // FIXME step 1: understand how anchors work. step 2: do this right
  virtual void anchor() {}
public:
  Mos6502Section(SectionVariant V, SectionKind K) : MCSection(V, K, nullptr) {}
  ~Mos6502Section() {}

  const char* getSectionName() const {
    if (Kind.isText())
      return "CODE";
    if (Kind.isReadOnly())
      return "RODATA";
    if (Kind.isData())
      return "DATA";
    if (Kind.isBSS())
      return "BSS";
    llvm_unreachable("unhandled section kind");
    return 0;
  }

  void PrintSwitchToSection(const MCAsmInfo &MAI,
                            raw_ostream &OS,
                            const MCExpr *Subsection) const override {
    OS << "\t.segment\t\"" << getSectionName() << "\"\n";
    // FIXME: Append segment type?

    // No subsection support
  }

  bool UseCodeAlign() const override { return false; }
  bool isVirtualSection() const override { return false; }
};

} // end namespace llvm

#endif
