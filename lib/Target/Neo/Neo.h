//===-- Sparc.h - Top-level interface for Sparc representation --*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file contains the entry points for global functions defined in the LLVM
// Sparc back-end.
//
//===----------------------------------------------------------------------===//

#ifndef LLVM_LIB_TARGET_NEO_NEO_H
#define LLVM_LIB_TARGET_NEO_NEO_H

#include "llvm/Support/ErrorHandling.h"
#include "llvm/Target/TargetMachine.h"

namespace llvm {
  class FunctionPass;
  class SparcTargetMachine;
  class formatted_raw_ostream;
  class AsmPrinter;
  class MCInst;
  class MachineInstr;

  //FunctionPass *createNeoISelDag(SparcTargetMachine &TM);
  //FunctionPass *createNeoDelaySlotFillerPass(TargetMachine &TM);

  //void LowerNeoMachineInstrToMCInst(const MachineInstr *MI,
  //                                    MCInst &OutMI,
  //                                    AsmPrinter &AP);
} // end namespace llvm;

namespace llvm {
  // Enums corresponding to Neo condition codes, both icc's and fcc's.  These
  // values must be kept in sync with the ones in the .td file.
  namespace NEOCC {
    enum CondCodes {
      ALWAYS =  64   ,  // Always

      NEVER = 127

    };
  }

  inline static const char *NEOCondCodeToString(NEOCC::CondCodes CC) {
    switch (CC) {
    case NEOCC::ALWAYS:   return "always";
    case NEOCC::NEVER: return "never";
    }
    llvm_unreachable("Invalid cond code");
  }

  inline static unsigned HI22(int64_t imm) {
    return (unsigned)((imm >> 10) & ((1 << 22)-1));
  }

  inline static unsigned LO10(int64_t imm) {
    return (unsigned)(imm & 0x3FF);
  }

  inline static unsigned HIX22(int64_t imm) {
    return HI22(~imm);
  }

  inline static unsigned LOX10(int64_t imm) {
    return ~LO10(~imm);
  }

}  // end namespace llvm
#endif
