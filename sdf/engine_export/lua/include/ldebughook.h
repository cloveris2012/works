#ifndef ldebughook_h
#define ldebughook_h

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
	lua_State *(*get_debugging_lua_state)();
	int(*is_break_point_enable)();
	int(*is_single_step_enable)();
	int(*is_break_point_or_single_step_enable)();
	int(*fast_check_break_point_by_line_number)(int line_number);
	int(*fast_check_break_point_by_source_filename)(const char *source_filename);
	void(*source_string_to_source_filename)(char *source_filename, const char *source_string);
	int(*get_break_index_on_file)(const char *filename);
	int(*find_break_point)(const char *filename, int line);
	void(*set_break_point_hit)(int break_point_hit);
	int(*have_messages)();
	void(*dispatch_network_messages)();
	void(*debugger_lua_throw)(int error_code);
	int(*get_protected_call_mode)();
	void(*set_protected_call_mode)(int protected_call_mode);
} LuaDebugHook;

extern LuaDebugHook *g_lua_debug_hook;

extern LuaDebugHook *g_lua_debug_hook_editor;

LUA_API void setup_lua_debug_hook(LuaDebugHook *lua_debug_hook);

LUA_API void setup_lua_debug_hook_editor(LuaDebugHook *lua_debug_hook_editor);

#ifdef __cplusplus
}
#endif

#endif

