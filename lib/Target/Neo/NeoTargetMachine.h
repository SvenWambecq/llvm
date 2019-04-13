//===-- NeoTargetMachine.h - Define TargetMachine for Neo ---*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file declares the Neo specific subclass of TargetMachine.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_NEO_NEOTARGETMACHINE_H
#define LLVM_LIB_TARGET_NEO_NEOTARGETMACHINE_H

#include "NeoInstrInfo.h"
#include "NeoSubtarget.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {

class NeoTargetMachine : public LLVMTargetMachine {
  //std::unique_ptr<TargetLoweringObjectFile> TLOF;
  NeoSubtarget Subtarget;
  mutable StringMap<std::unique_ptr<NeoSubtarget>> SubtargetMap;
public:
  NeoTargetMachine(const Target &T, const Triple &TT, StringRef CPU,
                     StringRef FS, const TargetOptions &Options,
                     Optional<Reloc::Model> RM, CodeModel::Model CM,
                     CodeGenOpt::Level OL);
  ~NeoTargetMachine() override;

  const NeoSubtarget *getSubtargetImpl() const { return &Subtarget; }
  const NeoSubtarget *getSubtargetImpl(const Function &) const override;

  // Pass Pipeline Configuration
  TargetPassConfig *createPassConfig(PassManagerBase &PM) override;
  // TargetLoweringObjectFile *getObjFileLowering() const override {
  //   return TLOF.get();
  // }
};

} // end namespace llvm

#endif
