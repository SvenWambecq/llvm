//===-- Sparc.td - Describe the Sparc Target Machine -------*- tablegen -*-===//
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

//===----------------------------------------------------------------------===//
// Target-independent interfaces which we are implementing
//===----------------------------------------------------------------------===//

include "llvm/Target/Target.td"

//===----------------------------------------------------------------------===//
// NEO Subtarget features.
//

//def FeatureXS
//  : SubtargetFeature<"XS", "IsXS", "true",
//                     "Enable Neo XS instructions">;


//===----------------------------------------------------------------------===//
// Register File, Calling Conv, Instruction Descriptions
//===----------------------------------------------------------------------===//

include "NeoRegisterInfo.td"
//include "NeoCallingConv.td"
//include "NeoSchedule.td"
include "NeoInstrInfo.td"

def NeoInstrInfo : InstrInfo;

def NeoAsmParser : AsmParser {
  bit ShouldEmitMatchRegisterName = 0;
}

//===----------------------------------------------------------------------===//
// SPARC processors supported.
//===----------------------------------------------------------------------===//

class Proc<string Name, list<SubtargetFeature> Features>
 : Processor<Name, NoItineraries, Features>;

def : Proc<"generic",         []>;


//===----------------------------------------------------------------------===//
// Declare the target which we are implementing
//===----------------------------------------------------------------------===//

def NeoAsmWriter : AsmWriter {
  string AsmWriterClassName  = "InstPrinter";
  int PassSubtarget = 1;
  int Variant = 0;
}

def Neo : Target {
  // Pull in Instruction Info:
  let InstructionSet = NeoInstrInfo;
  let AssemblyParsers  = [NeoAsmParser];
  let AssemblyWriters = [NeoAsmWriter];
}
