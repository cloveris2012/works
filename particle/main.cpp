#define GLM_ENABLE_EXPERIMENTAL
#include "capi/capi.h"
#include "lua/include.h"
#include <iostream>
//#include <fstream>
#include "LuaIntf/LuaIntf.h"
#include "particle/Particle.h"
#include "particle/Particle.cpp"	
#include "rapidjson/document.h"
#include "particle/Emitter.h"
#include "defineEmitter.h"
#include "emitterFormat3.h"
#include "emitterFormat4.h"
#include "emitterFormat5.h"
#include "emitterFormat6.h"
#include "emitterFormat7.h"
#include "emitterFormat8.h"
#include "emitterFormat9.h"
#include "ParticleLoader.h"

//#include <android/log.h>
//#include "rapidjson"

//namespace LuaIntf
//{
//	LUA_USING_SHARED_PTR_TYPE(std::shared_ptr)
//}

//lua_State* global_lua_state = nullptr;

//static std::ofstream outFile("/storage/emulated/0/qqwwee.txt");

static int create_emitter(lua_State* L) {
	// std::cout << "create_emitter" << luaL_checkint(L, 1) << std::endl;

	if (luaL_checkint(L, 1) == 3) {
		LuaIntf::Lua::push(L, new Emittter<format3>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 4) {
		LuaIntf::Lua::push(L, new Emittter<format4>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 5) {
		LuaIntf::Lua::push(L, new Emittter<format5>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 6) {
		LuaIntf::Lua::push(L, new Emittter<format6>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 7) {
		LuaIntf::Lua::push(L, new Emittter<format7>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 8) {
		LuaIntf::Lua::push(L, new Emittter<format8>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 9) {
		LuaIntf::Lua::push(L, new Emittter<format9>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 10) {
		LuaIntf::Lua::push(L, new Emittter<format10>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 11) {
		LuaIntf::Lua::push(L, new Emittter<format11>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 12) {
		LuaIntf::Lua::push(L, new Emittter<format12>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 13) {
		LuaIntf::Lua::push(L, new Emittter<format13>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 14) {
		LuaIntf::Lua::push(L, new Emittter<format14>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 15) {
		LuaIntf::Lua::push(L, new Emittter<format15>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 16) {
		LuaIntf::Lua::push(L, new Emittter<format16>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 17) {
		LuaIntf::Lua::push(L, new Emittter<format17>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 18) {
		LuaIntf::Lua::push(L, new Emittter<format18>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 19) {
		LuaIntf::Lua::push(L, new Emittter<format19>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 20) {
		LuaIntf::Lua::push(L, new Emittter<format20>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 21) {
		LuaIntf::Lua::push(L, new Emittter<format21>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 22) {
		LuaIntf::Lua::push(L, new Emittter<format22>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 23) {
		LuaIntf::Lua::push(L, new Emittter<format23>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 24) {
		LuaIntf::Lua::push(L, new Emittter<format24>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 25) {
		LuaIntf::Lua::push(L, new Emittter<format25>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 26) {
		LuaIntf::Lua::push(L, new Emittter<format26>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 27) {
		LuaIntf::Lua::push(L, new Emittter<format27>);
		return 1;
	}
	else if (luaL_checkint(L, 1) == 28) {
		LuaIntf::Lua::push(L, new Emittter<format28>);
		return 1;
		}
	else if (luaL_checkint(L, 1) == 29) {
		LuaIntf::Lua::push(L, new Emittter<format29>);
		return 1;
	}
}

static void register_create_emitter_fun(lua_State* L) {
	//std::cout << "initEmitter" << std::endl;
	//outFile << "init_emitter" << std::endl;

	//LuaIntf::LuaBinding(L).addFunction("create_emitter", create_emitter);

	LuaIntf::LuaRef mod = LuaIntf::LuaRef::createTable(L);
    initEmitterFormat3(mod);
    initEmitterFormat4(mod);
    initEmitterFormat5(mod);
    initEmitterFormat6(mod);
    initEmitterFormat7(mod);
    initEmitterFormat8(mod);
	initEmitterFormat9(mod);
//	LuaIntf::LuaBinding(mod)
//		ExportEmitter(format3, "Emittter3")
//		ExportEmitter(format4, "Emittter4")
//		ExportEmitter(format5, "Emittter5")
//		ExportEmitter(format6, "Emittter6")
//		ExportEmitter(format7, "Emittter7")
//		ExportEmitter(format8, "Emittter8")
//		ExportEmitter(format9, "Emittter9")
//		ExportEmitter(format10, "Emittter10")
//		ExportEmitter(format11, "Emittter11")
//		ExportEmitter(format12, "Emittter12")
//		ExportEmitter(format13, "Emittter13")
//		ExportEmitter(format14, "Emittter14")
//		ExportEmitter(format15, "Emittter15")
//		ExportEmitter(format16, "Emittter16")
//		ExportEmitter(format17, "Emittter17")
//		ExportEmitter(format18, "Emittter18")
//		ExportEmitter(format19, "Emittter19")
//		ExportEmitter(format20, "Emittter20")
//		ExportEmitter(format21, "Emittter21")
//		ExportEmitter(format22, "Emittter22")
//		ExportEmitter(format23, "Emittter23")
//		ExportEmitter(format24, "Emittter24");

	/*LuaIntf::LuaBinding(L).addFunction("register_emitter", [mod](lua_State* L) {
		mod.pushToStack(L);
		return 1;
	});*/

	LuaIntf::LuaBinding(mod).addFunction("create_emitter", &create_emitter);

	auto particleLoader = LuaIntf::LuaBinding(mod).beginClass<ParticleLoader>("ParticleLoader");
	particleLoader.addStaticFunction("loadEmitterData", &ParticleLoader::loadEmitterData);
	auto emitterData = LuaIntf::LuaBinding(mod).beginClass<EmitterData>("EmitterData");
	emitterData.addConstructor(LUA_ARGS());

	mod.pushToStack();
}	

//static int test_json(lua_State* L) {
//	std::cout << "test_json" << std::endl;
//
//	const char* a = luaL_checkstring(L, 1);
//
//
//
//	std::cout << "passed from lua" << std::endl << a << std::endl;
//
//	rapidjson::Document d;
//
//	d.Parse(a);
//
//	std::cout << "get texturePaht" << d["texturePath"].GetString() << std::endl;
//
//	std::cout << "get emitterList" << d["emitterList"][0]["m_emitterName"].GetString() << std::endl;
//
//
//	return 0;
//}

//static void register_create_emitter_fun(lua_State* L) {
//	//std::cout << "register_create_emitter_fun" << std::endl;
//	//outFile << "register_create_emitter_fun" << std::endl;
//	//__android_log_print(1, "mmm", "register_create_emitter_fun");
//	//if (!global_lua_state) {
//	//	global_lua_state = L;
//	//}
//	//LuaIntf::LuaRef ref = LuaIntf::LuaRef::createFunction(L, create_emitter,);
//    lua_register(L, "create_emitter", create_emitter);    // 注册这个函数和函数名给LUA用
//}

//static void test_json_functions(lua_State* L) {
//	lua_register(L, "test_json", test_json);
//}



// 插件的主要入口从这里开始(主线程)
static int particle(EPluginMsgType eMsgType, void* param1) {
	//std::ofstream outFile("qqwwee.txt");
	//outFile.clear();
	//outFile << "test_plugin_proc" << std::endl;
	//std::cout << "test_plugin_proc" << std::endl;
	//__android_log_print(1, "mmm", "asdasdasdasd");
    switch (eMsgType) {
        case ELuaOnReady:
            // 主线程LUA初始化完毕
			//std::cout << "主线程LUA初始化完毕" << std::endl;
			//__android_log_print(1, "mmm", "主线程LUA初始化完毕");
			//outFile << "主线程LUA初始化完毕" << std::endl;
			register_create_emitter_fun((lua_State*)param1);
			//init_emitter((lua_State*)param1);
			//test_json_functions((lua_State*)engine->GetLuaState());
            break;
        case EThreadLuaOnReady:
			//std::cout << "线程池LUA初始化完毕，在线程池线程中调用" << std::endl;
			//__android_log_print(1, "mmm", "线程池LUA初始化完毕，在线程池线程中调用");
			//outFile << "线程池LUA初始化完毕，在线程池线程中调用" << std::endl;
            // 线程池LUA初始化完毕，在线程池线程中调用。
			register_create_emitter_fun((lua_State*)param1);
			//init_emitter((lua_State*)param1);
			//test_json_functions((lua_State*) param2);
            break;
        case EFrameUpdate:
            // 每帧回调
            break;
        case EOnPause:
            // 暂停
            break;
        case EOnResume:
            // 继续
            break;
        case EOnExit:
			//global_lua_state = nullptr;
            // 退出的时候, 基本上没什么用
            break;
        default:
            break;
    }

    return 0;
}

// example 既是插件名字也是入口函数名字。
//extern "C" __declspec(dllexport)
//int plugin_proc(ghost::EPluginMsgType eMsgType, void* param1, void* param2) {
//
//	return particle(eMsgType, param1, param2);
//}
BABE_PLUGIN_ENTRY(particle) //so


//const char* a = luaL_checkstring(L, 1);

//   lua_pushstring(L, a);

//std::cout << "passed from lua" << std::endl << a << std::endl;

//auto j = json::parse(a);

//std::cout << "get texturePaht" << j["texturePath"] << std::endl;

//std::cout << "get emitterList" << j["emitterList"][0]["m_emitterName"] << std::endl;

//std::cout << "parsed json" << std::endl << j.dump(4) << std::endl;

//glm::vec4 testVec = glm::vec4(1.0f);

//std::cout << "glm vector4" << std::endl << glm::to_string(testVec) << std::endl;

//Emittter* asd = new Emittter();

/*std::cout << "dddddd" << std::to_string(asd->myValue);
std::cout << "ffffff" << std::to_string(asd->getValue());*/

//void register_class_test(lua_State* L)
//{
//	//lua_register(L, "hello_plugin", hello_plugin)
//	
//
//	//LuaIntf::LuaBinding(L)
//	//	.beginClass<Emittter>("Emittter")
//	//	//.addConstructor(LUA_ARGS())
//	//	.addFactory("Emittter", [](Emittter<T>* emitter, lua_State* L) {
//	//		lua_pushlightuserdata(L, (void*)));
//	//		return 1;
//	//    })
//	//	.addFunction("loadEmitterData", &Emittter<T>::loadEmitterData, LUA_ARGS(std::string))
//	//	.addFunction("getIsVisible", &Emittter<T>::getIsVisible)
//	//	.addFunction("getAttributeFormat", &Emittter<T>::getAttributeFormat)
//	//	.addFunction("getParticleNum", &Emittter<T>::getParticleNum)
//	//	.addFunction("getAttriStripeSize", &Emittter<T>::getAttriStripeSize)
//	//	.addFunction("getParticleCount", &Emittter<T>::getParticleCount)
//	//	.addFunction("getMaxParticleCount", &Emittter:<T> :getMaxParticleCount)
//	//	.addFunction("update", &Emittter<T>::update, LUA_ARGS(int64_t))
//	//	/*.addFunction("test", [](Emittter* emitter, lua_State* L) {
//	//		lua_pushlightuserdata(L, (void*)(emitter->getShaderAttribute()));
//	//		return 1;
//	//	})*/
//	//	.endClass();
//}
