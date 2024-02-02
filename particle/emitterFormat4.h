//
//  emitterFormat4.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat4_h
#define emitterFormat4_h

void initEmitterFormat4(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format7, "Emittter7")
    ExportEmitter(format8, "Emittter8")
    ExportEmitter(format9, "Emittter9")
    ExportEmitter(format10, "Emittter10");
}

#endif /* emitterFormat4_h */
