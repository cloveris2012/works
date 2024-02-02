//
//  emitterFormat8.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat8_h
#define emitterFormat8_h

void initEmitterFormat8(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format23, "Emittter23")
    ExportEmitter(format24, "Emittter24")
    ExportEmitter(format25, "Emittter25")
    ExportEmitter(format26, "Emittter26");
}

#endif /* emitterFormat8_h */
