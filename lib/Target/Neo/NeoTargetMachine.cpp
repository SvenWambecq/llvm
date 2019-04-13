//===-- NeoTargetMachine.cpp - Define TargetMachine for Neo -----------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
//
//===----------------------------------------------------------------------===//

#include "NeoTargetMachine.h"
//#include "NeoTargetObjectFile.h"
#include "Neo.h"
#include "llvm/CodeGen/Passes.h"
#include "llvm/CodeGen/TargetPassConfig.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

extern "C" void LLVMInitializeNeoTarget() {
  // Register the target.
  RegisterTargetMachine<NeoTargetMachine> X(getTheNeoTarget());
}


static Reloc::Model getEffectiveRelocModel(Optional<Reloc::Model> RM) {
  if (!RM.hasValue())
    return Reloc::Static;
  return *RM;
}

static std::string computeDataLayout(const Triple &T) {
  // Sparc is typically big endian, but some are little.
  std::string Ret = "e";
  Ret += "-m:e";
  Ret += "-p:32:32";
  return Ret;
}

/// Create an ILP32 architecture model
NeoTargetMachine::NeoTargetMachine(const Target &T, const Triple &TT,
                                       StringRef CPU, StringRef FS,
                                       const TargetOptions &Options,
                                       Optional<Reloc::Model> RM,
                                       CodeModel::Model CM,
                                       CodeGenOpt::Level OL)
    : LLVMTargetMachine(T, computeDataLayout(TT), TT, CPU, FS, Options,
                        getEffectiveRelocModel(RM), CM, OL),
      Subtarget(TT, CPU, FS, *this) {
  initAsmInfo();
}

NeoTargetMachine::~NeoTargetMachine() {}

const NeoSubtarget *
NeoTargetMachine::getSubtargetImpl(const Function &F) const {
  Attribute CPUAttr = F.getFnAttribute("target-cpu");
  Attribute FSAttr = F.getFnAttribute("target-features");

  std::string CPU = !CPUAttr.hasAttribute(Attribute::None)
                        ? CPUAttr.getValueAsString().str()
                        : TargetCPU;
  std::string FS = !FSAttr.hasAttribute(Attribute::None)
                       ? FSAttr.getValueAsString().str()
                       : TargetFS;

  // FIXME: This is related to the code below to reset the target options,
  // we need to know whether or not the soft float flag is set on the
  // function, so we can enable it as a subtarget feature.
  bool softFloat =
      F.hasFnAttribute("use-soft-float") &&
      F.getFnAttribute("use-soft-float").getValueAsString() == "true";

  if (softFloat)
    FS += FS.empty() ? "+soft-float" : ",+soft-float";

  auto &I = SubtargetMap[CPU + FS];
  if (!I) {
    // This needs to be done before we create a new subtarget since any
    // creation will depend on the TM and the code generation flags on the
    // function that reside in TargetOptions.
    resetTargetOptions(F);
    I = llvm::make_unique<NeoSubtarget>(TargetTriple, CPU, FS, *this);
  }
  return I.get();
}

namespace {
/// neo Code Generator Pass Configuration Options.
class NeoPassConfig : public TargetPassConfig {
public:
  NeoPassConfig(NeoTargetMachine *TM, PassManagerBase &PM)
    : TargetPassConfig(TM, PM) {}

  NeoTargetMachine &getNeoTargetMachine() const {
    return getTM<NeoTargetMachine>();
  }

  void addIRPasses() override;
  bool addInstSelector() override;
  void addPreEmitPass() override;
};
} // namespace

TargetPassConfig *NeoTargetMachine::createPassConfig(PassManagerBase &PM) {
  return new NeoPassConfig(this, PM);
}

void NeoPassConfig::addIRPasses() {
  addPass(createAtomicExpandPass(&getNeoTargetMachine()));

  TargetPassConfig::addIRPasses();
}

bool NeoPassConfig::addInstSelector()
{
  addPass(createNeoISelDag(getNeoTargetMachine()));
  return false;
}

void NeoPassConfig::addPreEmitPass(){


}
