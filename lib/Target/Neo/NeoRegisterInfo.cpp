//===-- SparcRegisterInfo.cpp - SPARC Register Information ----------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the SPARC implementation of the TargetRegisterInfo class.
//
//===----------------------------------------------------------------------===//

#include "NeoRegisterInfo.h"
#include "Neo.h"
#include "NeoSubtarget.h"
#include "llvm/ADT/BitVector.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/CodeGen/MachineFrameInfo.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/CodeGen/MachineInstrBuilder.h"
#include "llvm/IR/Type.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetInstrInfo.h"

using namespace llvm;

#define GET_REGINFO_ENUM
#include "NeoGenRegisterInfo.inc"

#define GET_REGINFO_TARGET_DESC
#include "NeoGenRegisterInfo.inc"

NeoRegisterInfo::NeoRegisterInfo() : NeoGenRegisterInfo(NeoArch::R15) {}

const MCPhysReg*
NeoRegisterInfo::getCalleeSavedRegs(const MachineFunction *MF) const {
  return nullptr;
}

const uint32_t *
NeoRegisterInfo::getCallPreservedMask(const MachineFunction &MF,
                                        CallingConv::ID CC) const {
  return nullptr;
}

const uint32_t*
NeoRegisterInfo::getRTCallPreservedMask(CallingConv::ID CC) const {
  return nullptr;
}

BitVector NeoRegisterInfo::getReservedRegs(const MachineFunction &MF) const {
  BitVector Reserved(getNumRegs());
  return Reserved;
}

const TargetRegisterClass*
NeoRegisterInfo::getPointerRegClass(const MachineFunction &MF,
                                      unsigned Kind) const {
  return nullptr;
}

unsigned NeoRegisterInfo::getFrameRegister(const MachineFunction &MF)
{
  return 0;
}

bool NeoRegisterInfo::canRealignStack(const MachineFunction &MF) const
{
  return false;
}