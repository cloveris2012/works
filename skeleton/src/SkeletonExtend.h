/*
* Skeleton对象通用扩展
*/
#ifndef SKELETON_EXTEND_H
#define SKELETON_EXTEND_H

#define regionIndexSize 6
#define regionVertexSize 4

#include <map>
#include <vector>
#include "common/skel.h"
#include "entities/SkeletonClipping.h"

struct MaterialInfo {
	int startPos;
	int endPos;
	int blend;
	std::string texInfo;
};

namespace skel {
	class SkeletonObjectCreator;
	class SkeletonExtend : public Skeleton {
	private:
		std::vector<uint16_t> _indices;
		std::vector<float> _vertices;
		//std::vector<BlendInfo> _blendInfoList;
		std::vector<int> _blendInfos;
		std::vector<MaterialInfo> _materialInfos;
		SkeletonClipping* _clipper;
		
	public:
		SkeletonExtend(SkeletonData *skeletonData, SkeletonObjectCreator &creator);
		~SkeletonExtend();

		int computeDrawData(lua_State *L, bool get_bounds = false);
		void checkBlendMode(BlendMode &lastBlendMode, BlendMode currentBlendMode, int &breakStartIndex, int &breakStartVertexCount, int &breakStartVertexOffset);
		int computeRenderData(lua_State *L, bool get_bounds = false);
		int computeRenderDataWithGpu(lua_State *L, bool get_bounds = false);
		void constructRenderData(lua_State *L, int vertexCount, bool get_bounds, float minX = 0, float minY = 0, float maxX = 0, float maxY = 0);
		int getMatricesInfo(lua_State *L, bool refresh = false);
		int getAnimationsInfo(lua_State *L);
		void setAttachmentLua(const char *slotName, const char *attachementName);
		Bone *findBoneLua(const char *boneName);
		Attachment *getAttachmentLua(const char* slotName, const char *attachmentName);
		int testCustomData(lua_State *L);
		void setSkinByName(const char *skinName);
		void setSkinBySkin(Skin *newSkin);
		int getSkeletonId();
		LuaIntf::LuaRef getBoneInfo(lua_State *L);
		LuaIntf::LuaRef getAttachmentAndSlotInfo(lua_State *L);
		
		float width = 0;
		float height = 0;
		float x = 0;
		float y = 0;
		bool gpuInstance = true;
		std::size_t id = 0;
		LuaIntf::LuaRef unitdata;
		Color color;
	};
}
#endif