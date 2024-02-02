//
//  emitterFormat5.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat5_h
#define emitterFormat5_h

void initEmitterFormat5(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format11, "Emittter11")
    ExportEmitter(format12, "Emittter12")
    ExportEmitter(format13, "Emittter13")
    ExportEmitter(format14, "Emittter14");
}

#endif /* emitterFormat5_h */
