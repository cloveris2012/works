#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>
#include <vector>
#include "capi/capi.h"

#define Get_Float(ref, keyName)\
ref.has(keyName) && (ref.get(keyName).type() == LuaIntf::LuaTypeID::NUMBER) ? ref.get(keyName).toValue<float>() : 0;\

#define Get_Int(ref, keyName)\
ref.has(keyName) && (ref.get(keyName).type() == LuaIntf::LuaTypeID::NUMBER) ? ref.get(keyName).toValue<int>() : 0;\

#define Get_String(ref, keyName)\
ref.has(keyName) && ref.get(keyName).type() == LuaIntf::LuaTypeID::STRING ? ref.get(keyName).toValue<std::string>() : "";\

struct kerning
{
	int unicode1;
	int unicode2;
	float advance;
};

struct planeBounds 
{
	float top;
	float right;
	float left;
	float bottom;
};

struct atlasBounds
{
	float top;
	float right;
	float left;
	float bottom;
};

struct glyphs
{
	planeBounds planeBounds;
	atlasBounds atlasBounds;
	float advance;
	int unicode;
};

struct atlas
{
	float distanceRange;
	std::string type;
	float width;
	float height;
	float size;
	std::string yOrigin;
};

struct metrics
{
	float ascender;
	float descender;
	float lineHeight;
	float emSize;
	float underlineThickness;
	float underlineY;
};


struct charInfo
{
	float vertexleft;
	float vertexTop;
	float vertexBottom;
	float vertexRight;
	float uvLeft;
	float uvTop;
	float uvBottom;
	float uvRight;
	float advance;
};

struct SDFData 
{
	std::vector<kerning> kerning;
	std::vector<glyphs> glyphs;
	atlas atlas;
	metrics metrics;
	std::map<int, charInfo> charInfos;
};


class SDFLoader
{
public:
	SDFLoader();
	~SDFLoader();

	static std::mutex _sdfDataMutex;
	static std::map<std::string, SDFData> m_sdfDataMap;
	static void loadSDFData(lua_State* L, std::string id, LuaIntf::LuaRef sdfDataRef);
	static LuaIntf::LuaRef getCharInfoFromId(lua_State* L, std::string id, LuaIntf::LuaRef unicodes, int fontSize);
	static LuaIntf::LuaRef getUniformDataFromId(lua_State* L, std::string id);
	static float getStringWidthFromId(lua_State* L, std::string id, LuaIntf::LuaRef unicodes, int fontSize, LuaIntf::LuaRef charAdjustment, float advanceOffset);
	//static LuaIntf::LuaRef getCharInfoFromId(lua_State* L, const char* id, const char* chars, int fontSize);
};

