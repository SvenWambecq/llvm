//===-- SparcSubtarget.h - Define Subtarget for the SPARC -------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the SPARC specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_NEO_NEOSUBTARGET_H
#define LLVM_LIB_TARGET_NEO_NEOSUBTARGET_H

#include "NeoFrameLowering.h"
#include "NeoISelLowering.h"
#include "NeoInstrInfo.h"
#include "llvm/CodeGen/SelectionDAGTargetInfo.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Target/TargetFrameLowering.h"
#include "llvm/Target/TargetSubtargetInfo.h"
#include <string>

#define GET_SUBTARGETINFO_HEADER
#include "NeoGenSubtargetInfo.inc"

namespace llvm {
class StringRef;

class NeoSubtarget : public NeoGenSubtargetInfo {
  Triple TargetTriple;
  virtual void anchor();

  NeoInstrInfo InstrInfo;
  NeoTargetLowering TLInfo;
  SelectionDAGTargetInfo TSInfo;
  NeoFrameLowering FrameLowering;

public:
  NeoSubtarget(const Triple &TT, const std::string &CPU,
                 const std::string &FS, const TargetMachine &TM);

  //const NeoInstrInfo *getInstrInfo() const override { return &InstrInfo; }
  //const TargetFrameLowering *getFrameLowering() const override {
  //  return &FrameLowering;
  //}
  //const NeoRegisterInfo *getRegisterInfo() const override {
  //  return &InstrInfo.getRegisterInfo();
 // }
  /*const NeoTargetLowering *getTargetLowering() const override {
    return &TLInfo;
  }
  const SelectionDAGTargetInfo *getSelectionDAGInfo() const override {
    return &TSInfo;
  } */

  bool enableMachineScheduler() const override;


  /// ParseSubtargetFeatures - Parses features string setting specified
  /// subtarget options.  Definition of function is auto generated by tblgen.
  void ParseSubtargetFeatures(StringRef CPU, StringRef FS);
  NeoSubtarget &initializeSubtargetDependencies(StringRef CPU, StringRef FS);

  /// The 64-bit ABI uses biased stack and frame pointers, so the stack frame
  /// of the current function is the area from [%sp+BIAS] to [%fp+BIAS].
  int64_t getStackPointerBias() const {
    return 0;
  }

  /// Given a actual stack size as determined by FrameInfo, this function
  /// returns adjusted framesize which includes space for register window
  /// spills and arguments.
  int getAdjustedFrameSize(int stackSize) const;

};

} // end namespace llvm

#endif
