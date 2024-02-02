#ifndef LUA_EX_H
#define LUA_EX_H

#include "lua/include.h"

lua_Number lua_popnumber(lua_State *L);

const char *lua_popstring(lua_State *L);

int lua_popboolean(lua_State *L);


#endif
