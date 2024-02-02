//
//  emitterFormat7.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat7_h
#define emitterFormat7_h

void initEmitterFormat7(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format19, "Emittter19")
    ExportEmitter(format20, "Emittter20")
    ExportEmitter(format21, "Emittter21")
    ExportEmitter(format22, "Emittter22");
}
#endif /* emitterFormat7_h */
