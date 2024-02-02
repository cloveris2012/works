//
//  emitterFormat3.h
//  particle
//
//  Created by 衡黎 on 2021/4/29.
//

#ifndef emitterFormat3_h
#define emitterFormat3_h

#include "defineEmitter.h"

void initEmitterFormat3(LuaIntf::LuaRef mod)
{
    LuaIntf::LuaBinding(mod)
    ExportEmitter(format3, "Emittter3")
    ExportEmitter(format4, "Emittter4")
    ExportEmitter(format5, "Emittter5")
    ExportEmitter(format6, "Emittter6");
}

#endif /* emitterFormat3_h */
