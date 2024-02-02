//
//  emitterFormat6.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat6_h
#define emitterFormat6_h

void initEmitterFormat6(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format15, "Emittter15")
    ExportEmitter(format16, "Emittter16")
    ExportEmitter(format17, "Emittter17")
    ExportEmitter(format18, "Emittter18");
}

#endif /* emitterFormat6_h */
