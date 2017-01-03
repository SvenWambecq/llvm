
def s16imm : Operand<i32> {

}

class NeoInstruction<dag outs, dag ins, string asmstr, list<dag> pattern>
    : Instruction {

  let Namespace = "Neo";
  /// outs and ins are inherited from the instruction class.
  dag OutOperandList = outs;
  dag InOperandList  = ins;
  let AsmString   = asmstr;
  let Pattern = pattern;
}



class LRL<dag outs, dag ins, string asmstr, list<dag> pattern>:
    NeoInstruction<outs, ins, asmstr, pattern>
{
    field bits<29> Inst;
    bits<22> data;
    bits<7> reg;

    let Inst{28-7} = data;
    let Inst{6-0} = reg;

}

class SRL<dag outs, dag ins, string asmstr, list<dag> pattern>:
    NeoInstruction<outs, ins, asmstr, pattern>
{
    field bits<19> Inst;
    bits<12> data;
    bits<7> reg;

    let Inst{18-7} = data;
    let Inst{6-0} = reg;

}
