//===-- Mos6502MCAsmInfo.h - Mos6502 asm properties -------------------*- C++ -*--====//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the declaration of the Mos6502MCAsmInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MCTARGETDESC_MOS6502MCASMINFO_H
#define LLVM_LIB_TARGET_MOS6502_MCTARGETDESC_MOS6502MCASMINFO_H

#include "llvm/ADT/StringRef.h"
#include "llvm/MC/MCAsmInfo.h"
#include "llvm/ADT/Triple.h"

namespace llvm {
class Target;
class Triple;

class Mos6502MCAsmInfo : public MCAsmInfo {
public:
  explicit Mos6502MCAsmInfo(const Triple &TT) {
    SupportsDebugInformation = false;
    ExceptionsType = ExceptionHandling::None;
    CommentString = ";";
    HasDotTypeDotSizeDirective = false;
    GlobalDirective = ".global ";
    HasSingleParameterDotFile = false;
    PointerSize = 2;

    // FIXME: ca65 uses ".segment" while LLVM wants to use ".section"
    // (it also uses ".code" while LLVM uses ".text")
  }

  bool shouldOmitSectionDirective(StringRef SectionName) const override {
    return false;
  }
};
} // end namespace llvm

#endif
