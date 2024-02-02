#include "LuaEx.h"

// 将栈顶元素转换成number并弹出
lua_Number lua_popnumber(lua_State *L) {
	luaL_checktype(L, -1, LUA_TNUMBER);
	lua_Number n = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return n;
}

const char *lua_popstring(lua_State *L) {
	luaL_checktype(L, -1, LUA_TSTRING);
	const char *s = lua_tostring(L, -1);
	lua_pop(L, 1);
	return s;
}

int lua_popboolean(lua_State *L) {
	luaL_checktype(L, -1, LUA_TBOOLEAN);
	int b = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return b;
}

