//===-- NeoISelLowering.h - Sparc DAG Lowering Interface ------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file defines the interfaces that Sparc uses to lower LLVM code into a
// selection DAG.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_NEO_NEOISELLOWERING_H
#define LLVM_LIB_TARGET_NEO_NEOISELLOWERING_H

#include "Neo.h"
#include "llvm/Target/TargetLowering.h"

namespace llvm {
    class NeoSubtarget; 

    class NeoTargetLowering : public TargetLowering {
      const NeoSubtarget *Subtarget;
    public:
      NeoTargetLowering(const TargetMachine &TM, const NeoSubtarget &STI);
  };
}

#endif    // NEO_ISELLOWERING_H
