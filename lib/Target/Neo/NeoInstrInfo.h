//===-- SparcInstrInfo.h - Sparc Instruction Information --------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the Sparc implementation of the TargetInstrInfo class.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_NEO_NEOINSTRINFO_H
#define LLVM_LIB_TARGET_NEO_NEOINSTRINFO_H

#include "NeoRegisterInfo.h"
#include "llvm/Target/TargetInstrInfo.h"

#define GET_INSTRINFO_HEADER
#include "NeoGenInstrInfo.inc"

namespace llvm {

class NeoSubtarget;

/// SPII - This namespace holds all of the target specific flags that
/// instruction info tracks.
///

class NeoInstrInfo : public NeoGenInstrInfo {
  const NeoRegisterInfo RI;
  const NeoSubtarget& Subtarget;
  virtual void anchor();
public:
  explicit NeoInstrInfo(NeoSubtarget &ST);

  /// getRegisterInfo - TargetInstrInfo is a superset of MRegister info.  As
  /// such, whenever a client has an instance of instruction info, it should
  /// always be able to get register info as well (through this method).
  ///
  const NeoRegisterInfo &getRegisterInfo() const { return RI; }


};

}

#endif
