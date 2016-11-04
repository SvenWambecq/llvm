//===-- SparcRegisterInfo.td - Sparc Register defs ---------*- tablegen -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

//===----------------------------------------------------------------------===//
//  Declarations that describe the Neo register file
//===----------------------------------------------------------------------===//

class Ri<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "Neo";
}

class MPi<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "Neo";
}

class NeoStatusReg<bits<16> Enc, string n>: Register<n> {
  let HWEncoding = Enc;
  let Namespace = "Neo";
}

foreach I = 0-15 in
  def R#I : Ri<I, "r"#I>;

foreach I = 0-5 in
  def MP#I : MPi<I, "mp"#I>;

def DataRegs : RegisterClass<"Neo", [i16, i32], 32, (sequence "R%u", 0, 15)>;
def PtrRegs: RegisterClass<"Neo", [i16, i32], 32, (sequence "MP%u", 0, 5)>;

