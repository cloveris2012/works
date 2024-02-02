#include "common/Atlas.h"
#include "utils/ContainerUtil.h"
using namespace std;
using namespace skel;

lua_Number loadNumber(lua_State* L, const char *k) {
	lua_getfield(L, -1, k);
	lua_Number num = lua_tonumber(L, -1);
	lua_pop(L, 1);
	return num;
}

int loadBoolean(lua_State* L, const char *k) {
	lua_getfield(L, -1, k);
	int value = lua_toboolean(L, -1);
	lua_pop(L, 1);
	return value;
}

bool checkIsPartName(const String &name, std::vector<String> &textureSizeNameList)
{
	for (auto i : textureSizeNameList)
	{
		if (name == i) 
			return false;
	}
	return true;
}

Atlas::Atlas(LuaIntf::LuaRef &unitData) {
	_regions.clear();

	std::string textureSizeName = "__texture_info__";
	unsigned int textureCount = 1;
	std::vector<String> textureSizeNameList;
	std::string name = textureSizeName;
	textureSizeName = name + std::to_string(textureCount);
	while (unitData.get(textureSizeName))
	{
		textureSizeNameList.push_back(String(textureSizeName.c_str()));
		TextureInfo textureInfo;
		auto textureInfoRef = unitData.get(textureSizeName);
		textureInfo.x = textureInfoRef.get(1).toValue<int>();
		textureInfo.y = textureInfoRef.get(2).toValue<int>();
		textureInfo.name = String(textureInfoRef.get(3).toValue<std::string>().c_str());
		_textureInfos.push_back(textureInfo);
		textureCount++;
		textureSizeName = name + std::to_string(textureCount);
	}

	auto beg = unitData.begin();
	auto end = unitData.end();
	//int count = 0;
	while (beg != end) {

		

		const String &name = String(beg.key().toValue<std::string>().c_str());

		//count++;
		//std::cout << name.buffer() << std::endl;
		//std::cout << count << std::endl;

		if (checkIsPartName(name, textureSizeNameList)) {
			_regions.add(loadRegion(beg, name));
		}

		

		++beg;
	}
}

AtlasRegion *Atlas::findRegion(const String &name) {
	for (size_t i = 0, n = _regions.size(); i < n; ++i)
		if (_regions[i]->name == name) return _regions[i];
	return NULL;
}

AtlasRegion *Atlas::loadRegion(LuaIntf::LuaTableIterator &iter, const String &name) {
	AtlasRegion *region = new(__FILE__, __LINE__) AtlasRegion();

	region->name = name.buffer();

	region->texName = iter.value().get("texName").toValue<std::string>();

	region->x = iter.value().get("x").toValue<int>();
	region->y = iter.value().get("y").toValue<int>();

	region->rotate = iter.value().get("rotated").toValue<bool>();

	region->width = iter.value().get("width").toValue<int>();
	region->height = iter.value().get("height").toValue<int>();

	if (iter.value().has("originalWidth"))
		region->originalWidth = iter.value().get("originalWidth").toValue<int>();
	else
		region->originalWidth = region->width;
	
	if (iter.value().has("originalHeight"))
		region->originalHeight = iter.value().get("originalHeight").toValue<int>();
	else
		region->originalHeight = region->height;

	int textureWidth, textureHeight;
	for (auto i : _textureInfos)
	{
		std::string strName = i.name.buffer();
		if (strName == region->texName)
		{
			textureWidth = i.x;
			textureHeight = i.y;
		}
	}

	if (region->rotate)
	{
		region->degrees = 90;
		region->u2 = (region->x + region->height) / (float)textureWidth;
		region->v2 = (region->y + region->width) / (float)textureHeight;
	}
	else
	{
		region->degrees = 0;
		region->u2 = (region->x + region->width) / (float)textureWidth;
		region->v2 = (region->y + region->height) / (float)textureHeight;
	}

	region->u = region->x / (float)textureWidth;
	region->v = region->y / (float)textureHeight;

	region->textureWidth = textureWidth;
	region->textureHeight = textureHeight;

	if (iter.value().has("offsetX"))
		region->offsetX = iter.value().get("offsetX").toValue<int>();
	else
		region->offsetX = 0;

	if (iter.value().has("offsetY"))
		region->offsetY = iter.value().get("offsetY").toValue<int>();
	else
		region->offsetY = 0;

	return region;
}

Atlas::~Atlas() {
	ContainerUtil::cleanUpVectorOfPointers(_regions);
}



