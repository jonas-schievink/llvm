//===-- Mos6502MCTargetDesc.cpp - Mos6502 Target Descriptions ---------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file provides Mos6502 specific target descriptions.
//
//===----------------------------------------------------------------------===//

#include "Mos6502.h"
#include "Mos6502MCTargetDesc.h"
#include "Mos6502MCAsmInfo.h"
#include "InstPrinter/Mos6502InstPrinter.h"
#include "llvm/MC/MCCodeGenInfo.h"
#include "llvm/MC/MCInstrInfo.h"
#include "llvm/MC/MCRegisterInfo.h"
#include "llvm/MC/MCStreamer.h"
#include "llvm/MC/MCSubtargetInfo.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Support/TargetRegistry.h"

#define GET_INSTRINFO_MC_DESC
#include "Mos6502GenInstrInfo.inc"

#define GET_SUBTARGETINFO_MC_DESC
#include "Mos6502GenSubtargetInfo.inc"

#define GET_REGINFO_MC_DESC
#include "Mos6502GenRegisterInfo.inc"

using namespace llvm;

static MCInstrInfo *createMos6502MCInstrInfo() {
  MCInstrInfo *X = new MCInstrInfo();
  InitMos6502MCInstrInfo(X);
  return X;
}

static MCRegisterInfo *createMos6502MCRegisterInfo(const Triple &TT) {
  MCRegisterInfo *X = new MCRegisterInfo();

  // 2nd parameter is the register storing the "return address".
  // FIXME A is obviously wrong, but what the hell should I put there???
  InitMos6502MCRegisterInfo(X, Mos6502::A);
  return X;
}

static MCSubtargetInfo *createMos6502MCSubtargetInfo(const Triple &TT,
                                                     StringRef CPU,
                                                     StringRef FS) {
  return createMos6502MCSubtargetInfoImpl(TT, CPU, FS);
}

static MCCodeGenInfo *createMos6502MCCodeGenInfo(const Triple &TT,
                                                 Reloc::Model RM,
                                                 CodeModel::Model CM,
                                                 CodeGenOpt::Level OL) {
  MCCodeGenInfo *X = new MCCodeGenInfo();
  X->initMCCodeGenInfo(RM, CM, OL);
  return X;
}

static MCStreamer *createMos6502MCStreamer(const Triple &T,
                                           MCContext &Ctx, MCAsmBackend &MAB,
                                           raw_pwrite_stream &OS,
                                           MCCodeEmitter *Emitter,
                                           bool RelaxAll) {
  return createELFStreamer(Ctx, MAB, OS, Emitter, RelaxAll);
}

static MCInstPrinter *createMos6502MCInstPrinter(const Triple &T,
                                                 unsigned SyntaxVariant,
                                                 const MCAsmInfo &MAI,
                                                 const MCInstrInfo &MII,
                                                 const MCRegisterInfo &MRI) {
  if (SyntaxVariant == 0)
    return new Mos6502InstPrinter(MAI, MII, MRI);
  return 0;
}

extern "C" void LLVMInitializeMos6502TargetMC() {
  // Register the MC asm info.
  RegisterMCAsmInfo<Mos6502MCAsmInfo> X(TheMos6502Target);

  // Register the MC codegen info.
  TargetRegistry::RegisterMCCodeGenInfo(TheMos6502Target,
                                        createMos6502MCCodeGenInfo);

  // Register the MC instruction info.
  TargetRegistry::RegisterMCInstrInfo(TheMos6502Target,
                                      createMos6502MCInstrInfo);

  // Register the MC register info.
  TargetRegistry::RegisterMCRegInfo(TheMos6502Target,
                                    createMos6502MCRegisterInfo);

  // Register the MC subtarget info.
  TargetRegistry::RegisterMCSubtargetInfo(TheMos6502Target,
                                          createMos6502MCSubtargetInfo);

  // Register the object streamer
  TargetRegistry::RegisterELFStreamer(TheMos6502Target,
                                      createMos6502MCStreamer);

  // Register the MCInstPrinter.
  TargetRegistry::RegisterMCInstPrinter(TheMos6502Target,
                                        createMos6502MCInstPrinter);

  TargetRegistry::RegisterMCCodeEmitter(TheMos6502Target,
                                        createMos6502MCCodeEmitter);
  TargetRegistry::RegisterMCAsmBackend(TheMos6502Target,
                                       createMos6502AsmBackend);
}
