
include "NeoInstrFormats.td"

def immS16 : PatLeaf<(i32 imm), [{ return true; }]>;



def LoadReg : LRL<(outs DataRegs:$reg),
                   (ins s16imm:$data),
                   "LRL0: $reg = $data",
                   [(set DataRegs:$reg, (immS16:$data))]>;
