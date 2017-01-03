//===-- SparcSubtarget.cpp - SPARC Subtarget Information ------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file implements the SPARC specific subclass of TargetSubtargetInfo.
//
//===----------------------------------------------------------------------===//

#include "NeoSubtarget.h"
#include "Neo.h"
#include "llvm/Support/MathExtras.h"
#include "llvm/Support/TargetRegistry.h"

using namespace llvm;

#define DEBUG_TYPE "neo-subtarget"

#define GET_SUBTARGETINFO_TARGET_DESC
#define GET_SUBTARGETINFO_CTOR
#include "NeoGenSubtargetInfo.inc"

void NeoSubtarget::anchor() { }

NeoSubtarget &NeoSubtarget::initializeSubtargetDependencies(StringRef CPU,
                                                                StringRef FS) {

  // Determine default and user specified characteristics
  std::string CPUName = CPU;

  // Parse features string.
  ParseSubtargetFeatures(CPUName, FS);

  return *this;
}

NeoSubtarget::NeoSubtarget(const Triple &TT, const std::string &CPU,
                               const std::string &FS, const TargetMachine &TM)
    : NeoGenSubtargetInfo(TT, CPU, FS), TargetTriple(TT),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this),
      FrameLowering(*this) {}

int NeoSubtarget::getAdjustedFrameSize(int frameSize) const {
  return frameSize;
}

bool NeoSubtarget::enableMachineScheduler() const {
  return true;
}
