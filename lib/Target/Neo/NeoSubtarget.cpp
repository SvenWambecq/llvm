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
                               const std::string &FS, const TargetMachine &TM,
                               bool is64Bit)
    : NeoGenSubtargetInfo(TT, CPU, FS), TargetTriple(TT), Is64Bit(is64Bit),
      InstrInfo(initializeSubtargetDependencies(CPU, FS)), TLInfo(TM, *this),
      FrameLowering(*this) {}

int NeoSubtarget::getAdjustedFrameSize(int frameSize) const {

    // Emit the correct save instruction based on the number of bytes in
    // the frame. Minimum stack frame size according to V8 ABI is:
    //   16 words for register window spill
    //    1 word for address of returned aggregate-value
    // +  6 words for passing parameters on the stack
    // ----------
    //   23 words * 4 bytes per word = 92 bytes
    frameSize += 92;

    // Round up to next doubleword boundary -- a double-word boundary
    // is required by the ABI.
    frameSize = alignTo(frameSize, 8);
  }
  return frameSize;
}

bool NeoSubtarget::enableMachineScheduler() const {
  return true;
}
