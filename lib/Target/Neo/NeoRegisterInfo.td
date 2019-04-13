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
  let Namespace = "NeoArch";
}

class MPi<bits<16> Enc, string n> : Register<n> {
  let HWEncoding = Enc;
  let Namespace = "NeoArch";
}

class NeoStatusReg<bits<16> Enc, string n>: Register<n> {
  let HWEncoding = Enc;
  let Namespace = "NeoArch";
}

foreach I = 0-15 in
  def R#I : Ri<I, "r"#I>;

foreach I = 0-5 in
  def MP#I : MPi<I, "mp"#I>;

def DataRegs : RegisterClass<"NeoArch", [i32], 32, (sequence "R%u", 0, 15)>;
def PtrRegs: RegisterClass<"NeoArch", [i32], 32, (sequence "MP%u", 0, 5)>;
