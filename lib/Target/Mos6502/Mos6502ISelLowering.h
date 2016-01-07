//===-- Mos6502ISelLowering.h - Mos6502 DAG Lowering Interface --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Mos6502 uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_MOS6502_MOS6502ISELLOWERING_H
#define LLVM_LIB_TARGET_MOS6502_MOS6502ISELLOWERING_H

#include "Mos6502.h"
#include "llvm/CodeGen/SelectionDAG.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {
class Mos6502Subtarget;
namespace Mos6502ISD {
enum NodeType : unsigned {
  FIRST_NUMBER = ISD::BUILTIN_OP_END,
  RET_FLAG,
  CALL,
  SELECT_CC,
  BR_CC,
  // TODO: Understand exactly what this does. It seems to be emitted whenever
  // we're loading from a globaladdr.
  Wrapper
};
}

class Mos6502TargetLowering : public TargetLowering {
public:
  explicit Mos6502TargetLowering(const TargetMachine &TM, const Mos6502Subtarget &STI);

  // Provide custom lowering hooks for some operations.
  SDValue LowerOperation(SDValue Op, SelectionDAG &DAG) const override;

  // This method returns the name of a target specific DAG node.
  const char *getTargetNodeName(unsigned Opcode) const override;

  void ReplaceNodeResults(SDNode *N,
                          SmallVectorImpl<SDValue> &Results,
                          SelectionDAG &DAG) const override;

/*
  MachineBasicBlock *
  EmitInstrWithCustomInserter(MachineInstr *MI,
                              MachineBasicBlock *BB) const override;
*/

private:
  SDValue LowerBR_CC(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerSELECT_CC(SDValue Op, SelectionDAG &DAG) const;
  SDValue LowerGlobalAddress(SDValue Op, SelectionDAG &DAG) const;

  // Lower the result values of a call, copying them out of physregs into vregs
  SDValue LowerCallResult(SDValue Chain, SDValue InFlag,
                          CallingConv::ID CallConv, bool IsVarArg,
                          const SmallVectorImpl<ISD::InputArg> &Ins, SDLoc DL,
                          SelectionDAG &DAG,
                          SmallVectorImpl<SDValue> &InVals) const;

  // Lower a call into CALLSEQ_START - Mos6502ISD:CALL - CALLSEQ_END chain
  SDValue LowerCall(TargetLowering::CallLoweringInfo &CLI,
                    SmallVectorImpl<SDValue> &InVals) const override;

  // Lower incoming arguments, copy physregs into vregs
  SDValue LowerFormalArguments(SDValue Chain, CallingConv::ID CallConv,
                               bool IsVarArg,
                               const SmallVectorImpl<ISD::InputArg> &Ins,
                               SDLoc DL, SelectionDAG &DAG,
                               SmallVectorImpl<SDValue> &InVals) const override;

  SDValue LowerReturn(SDValue Chain, CallingConv::ID CallConv, bool IsVarArg,
                      const SmallVectorImpl<ISD::OutputArg> &Outs,
                      const SmallVectorImpl<SDValue> &OutVals, SDLoc DL,
                      SelectionDAG &DAG) const override;

  EVT getOptimalMemOpType(uint64_t Size, unsigned DstAlign, unsigned SrcAlign,
                          bool IsMemset, bool ZeroMemset, bool MemcpyStrSrc,
                          MachineFunction &MF) const override {
    return MVT::i8;
  }

  bool shouldConvertConstantLoadToIntImm(const APInt &Imm,
                                         Type *Ty) const override {
    return true;
  }
};
} // end namespace llvm

#endif
