//
//  emitterFormat9.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat9_h
#define emitterFormat9_h

void initEmitterFormat9(LuaIntf::LuaRef mod)
{ 
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format27, "Emittter27")
    ExportEmitter(format28, "Emittter28")
    ExportEmitter(format29, "Emittter29");
}

#endif /* emitterFormat9_h */
