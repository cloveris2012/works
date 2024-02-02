#ifndef SKELETON_ATLAS_h
#define SKELETON_ATLAS_h
#include "lua/include.h"
#include "common/Vector.h"
#include "../Extension.h"
#include "common/SkelObject.h"
#include "common/SkelString.h"
#include "LuaIntf/LuaIntf.h"
#include <vector>
#include <iostream>

namespace skel {
	struct TextureInfo {
		int x;
		int y;
		String name;
	};

	class SK_API AtlasRegion : public SkelObject {
	public:
		bool rotate = 0;
		int degrees = 0;
		int x, y, width, height;
		int originalWidth, originalHeight;
		float u, v, u2, v2;
		float offsetX, offsetY;
		size_t textureWidth;
		size_t textureHeight;
		String name;
		std::string texName;
	};

	class SK_API Atlas : public SkelObject {
	public:
		Atlas(LuaIntf::LuaRef &unitData);
		~Atlas();
		AtlasRegion *findRegion(const String &name);

	private:
		Vector<AtlasRegion *> _regions;
		std::vector<TextureInfo> _textureInfos;
		void load(lua_State* L);
		AtlasRegion *loadRegion(LuaIntf::LuaTableIterator &iter, const String &name);
	};
}
#endif /* SKELETON_ATLAS_h */