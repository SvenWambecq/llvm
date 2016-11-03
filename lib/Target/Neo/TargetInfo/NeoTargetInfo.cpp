//===-- SparcTargetInfo.cpp - Sparc Target Implementation -----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "Neo.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/TargetRegistry.h"
using namespace llvm;

Target &llvm::getTheNeoTarget() {
  static Target TheNeoTarget;
  return TheNeoTarget;
}
Target &llvm::getTheNeoXSTarget() {
  static Target TheNeoXSTarget;
  return TheNeoXSTarget;
}


extern "C" void LLVMInitializeNeoTargetInfo() {
  RegisterTarget<Triple::neo, /*HasJIT=*/false> X(getTheNeoTarget(), "neo",
                                                   "Neo");
  RegisterTarget<Triple::neoxs, /*HasJIT=*/false> Y(getTheNeoXSTarget(),
                                                     "neoxs", "NEO XS");
}
