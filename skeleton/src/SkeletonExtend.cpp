#include "SkeletonExtend.h"
#include <iostream>
#include "utils/LuaEx.h"
#include "utils/SkeletonObjectCreator.h"
#include <float.h>

using namespace std;
using namespace skel;

SkeletonExtend::SkeletonExtend(SkeletonData *skeletonData, SkeletonObjectCreator &creator) : Skeleton(skeletonData, creator) {
	_clipper = new SkeletonClipping;
}

skel::SkeletonExtend::~SkeletonExtend()
{
	delete _clipper;
}

void compute_color(Color &skeletonColor, Color &slotColor, Color &attachmentColor, Color &color) {
	float alpha = skeletonColor.a * slotColor.a * attachmentColor.a;
	float multiplier = alpha;
	color.set(skeletonColor.r * slotColor.r * attachmentColor.r * multiplier,
		skeletonColor.g * slotColor.g * attachmentColor.g * multiplier,
		skeletonColor.b * slotColor.b * attachmentColor.b * multiplier,
		alpha);
}

int SkeletonExtend::getMatricesInfo(lua_State *L, bool refresh) {
	auto &matrices = getMatrices(refresh);
	lua_newtable(L);
	lua_pushlightuserdata(L, matrices.data());
	lua_setfield(L, -2, "data");
	lua_pushnumber(L, matrices.size());
	lua_setfield(L, -2, "size");
	return 1;
}

int SkeletonExtend::computeDrawData(lua_State *L, bool get_bounds) {
	if (gpuInstance) {
		return computeRenderDataWithGpu(L, get_bounds);
	}
	else {
		return computeRenderData(L, get_bounds);
	}
}

void SkeletonExtend::checkBlendMode(BlendMode &lastBlendMode, BlendMode currentBlendMode, int &breakStartIndex, int &breakStartVertexCount, int &breakStartVertexOffset) {
	
}

// if (i != 1 && currentBlendMode != lastBlendMode)
// {
// 	BlendInfo blendInfo;
// 	blendInfo.indexStart = index;
// 	blendInfo.indexFinish = index + 6;
// 	blendInfo.vertexStart = offset;
// 	blendInfo.vertexFinish = offset + 8;
// 	blendInfo.vertexOffset = vertexCount;
// 	blendInfo.blendMode = lastBlendMode;
// }

// index min = index
// index max = index + size
// index value = indexValue - vertexCount 

// vertex min = offset
// vertex max = offset + length

//blendInfo = {}
//blendInfo.index.start = index
//blendInfo.index.finish = index + size
//blendInfo.vertex.start = offset
//blendInfo.vertex.finish = offset + length
//blendInfo.vertex.offset = vertexCount
//blendInfo.blendFunc = blendFunc

//BlendInfo blendInfo;
//blendInfo.indexStart = breakStartIndex; //上一次记录的break掉的索引数组起始位置   0
//blendInfo.indexFinish = index - 1;//当前需要break到上一个mesh的索引数组结束位置   5
//blendInfo.vertexStart = breakStartVertexOffset; //上一次记录的break掉的顶点数据数组起始位置 0
//blendInfo.vertexFinish = offset - 1;//当前需要break到上一个mesh的顶点数据数组结束位置  4 * vertexFormatLength - 1 
//blendInfo.vertexOffset = vertexCount;
//blendInfo.blendMode = lastBlendMode;
//_blendInfoList.push_back(blendInfo);

//
//BlendInfo blendInfo;
//blendInfo.indexStart = breakStartIndex; //上一次记录的break掉的索引数组起始位置   0
//blendInfo.indexFinish = index - 1;//当前需要break到上一个mesh的索引数组结束位置   5
//blendInfo.vertexStart = breakStartVertexOffset; //上一次记录的break掉的顶点数据数组起始位置 0
//blendInfo.vertexFinish = vertexCount * vertexFormatLength - 1;//当前需要break到上一个mesh的顶点数据数组结束位置  4 * vertexFormatLength - 1 
//blendInfo.vertexOffset = vertexCount;
//blendInfo.blendMode = lastBlendMode;

//_blendInfoList.push_back(blendInfo);

//引擎中纹理的RGB为预乘alpha的情况下对应混合模式为
//spine       IDE
//NORMAL      PREMUL_ALPHA 5         //{GL_ONE, GL_ONE_MINUS_SRC_ALPHA, GL_ONE, GL_ONE_MINUS_SRC_ALPHA}
//ADDTIVE     ADDTIVE 7              //{GL_ONE, GL_ONE, GL_SRC_ALPHA, GL_ONE}
//MULTIPLE    ADD_ALPHA 4            //{GL_SRC_ALPHA, GL_ONE, GL_SRC_ALPHA, GL_ONE}
//SCREEN      SCREEN  8              //{GL_ONE, GL_ONE_MINUS_SRC_COLOR,GL_ONE, GL_ONE_MINUS_SRC_COLOR}
int convertBlendModeToIDE(int spineBlendMode)
{
	BlendMode mode = (BlendMode)spineBlendMode;
	switch (spineBlendMode){
	case BlendMode::BlendMode_Normal:
		return 5;
	case BlendMode::BlendMode_Additive: 
		return 7;
	case BlendMode::BlendMode_Multiply:
		return 4;
	case BlendMode::BlendMode_Screen:
		return 8;
	default:
		return mode;
	}
}


int SkeletonExtend::computeRenderData(lua_State *L, bool get_bounds) {
	float minX = FLT_MAX;
	float minY = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;

	int absVertexCount = 0;
	int absIndex = 0;
	size_t vertexFormatLength = 14;// xyz uv rgba r_g_b_a_ blend

	int lastBlendMode = (int)BlendMode::BlendMode_Normal;
	std::string lastTexture = "";
    int breakStartIndex = 0;

	_vertices.clear();
	_indices.clear();
	_blendInfos.clear();
	_materialInfos.clear();

	int verticesCount;
	int indicesCount;

	auto drawOrder = getDrawOrder();

	/*printf("slots size:%d \n", getSlots().size());
	printf("draworder size:%d \n", getDrawOrder().size());*/

	/*for (size_t i = 0; i < getSlots().size(); ++i) {
		Slot *slot = drawOrder[i];*/

	for (size_t i = 0; i < drawOrder.size(); ++i) {
		Slot *slot = drawOrder[i];

		//toClipVertices.clear();
		//toClipUvs.clear();
		//toClipIndices.clear();
		/*std::string slotName = slot != NULL ? slot->getData().getName().buffer() : "NULL";
		std::string boneActive = slot->getBone().isActive() == true ? "true": "false";
		std::string attachementName = slot->getAttachment() != NULL ? slot->getAttachment()->getName().buffer() : "NULL";
		std::string clipping = _clipper->isClipping() == true ? "true" : "false";
		printf("slot name:%s   boneActive:%s   attachement name:%s   clipping:%s \n", slotName.c_str(), boneActive.c_str(), attachementName.c_str(), clipping.c_str());*/

		//以下的情况下不需要绘制, 但是要判断是否结束裁剪
		if (!slot->getBone().isActive() || !slot->getAttachment() || slot->getColor().a == 0)
		{
			_clipper->clipEnd(*slot);
			continue;
		}

		if (slot->getAttachment()->getRTTI().instanceOf(RegionAttachment::rtti))
		{
			if (static_cast<RegionAttachment *>(slot->getAttachment())->getColor().a == 0)
			{
				_clipper->clipEnd(*slot);
				continue;
			}
		}

		if (slot->getAttachment()->getRTTI().instanceOf(MeshAttachment::rtti))
		{
			if (static_cast<MeshAttachment *>(slot->getAttachment())->getColor().a == 0)
			{
				_clipper->clipEnd(*slot);
				continue;
			}
		}

		size_t offset = absVertexCount * vertexFormatLength;
		size_t verticesLength = 0;

		//========================材质处理========================================================
		BlendMode currentBlendMode = slot->getData().getBlendMode();
		std::string currentTexture = "";
		if (slot->getAttachment()->getRTTI().instanceOf(RegionAttachment::rtti))
		{
			RegionAttachment *regionAttachment = static_cast<RegionAttachment *>(slot->getAttachment());
			currentTexture = regionAttachment->getTexName();
		}
		else if (slot->getAttachment()->getRTTI().instanceOf(MeshAttachment::rtti))
		{
			MeshAttachment *meshAttachment = static_cast<MeshAttachment *>(slot->getAttachment());
			currentTexture = meshAttachment->getTexName();
		}

		// 如果是addtive则转成normal一样处理blendinfos逻辑
		int dealAddtiveInShader = currentBlendMode == BlendMode_Additive ? 1 : 0;
		currentBlendMode = currentBlendMode == BlendMode_Additive ? BlendMode_Normal : currentBlendMode;
				
		if (i == 0)
		{
			lastBlendMode = currentBlendMode;
			lastTexture = currentTexture;
		}
		else
		{
			if (currentBlendMode != lastBlendMode || currentTexture != lastTexture)
			{
				MaterialInfo materialInfo;
				materialInfo.startPos = breakStartIndex;
				materialInfo.endPos = absIndex;
				materialInfo.blend = convertBlendModeToIDE(lastBlendMode);
				materialInfo.texInfo = lastTexture;
				_materialInfos.push_back(materialInfo);

				breakStartIndex = absIndex;
				lastBlendMode = currentBlendMode;
				lastTexture = currentTexture;
			}
		}

		//========================顶点数据和索引=====================================================
		if (slot->getAttachment()->getRTTI().instanceOf(RegionAttachment::rtti)) {
			//printf("RegionAttachment \n");

			RegionAttachment *regionAttachment = static_cast<RegionAttachment *>(slot->getAttachment());

			//std::string clipping = _clipper->isClipping() == true ? "true" : "false";
			//printf("RegionAttachment : %s %s \n", slot->getAttachment()->getName().buffer(), clipping.c_str());

			if (!_clipper->isClipping())
			{
				//设置索引数据和更新索引, 这里是绝对索引
				_indices.resize(absIndex + 6);
				_indices[absIndex] = (0 + absVertexCount);
				_indices[absIndex + 1] = (1 + absVertexCount);
				_indices[absIndex + 2] = (2 + absVertexCount);
				_indices[absIndex + 3] = (0 + absVertexCount);
				_indices[absIndex + 4] = (2 + absVertexCount);
				_indices[absIndex + 5] = (3 + absVertexCount);
				absIndex += regionIndexSize;

				//更新顶点坐标数据,转化成世界坐标
				absVertexCount += regionVertexSize;
				_vertices.resize(absVertexCount * vertexFormatLength);
				regionAttachment->computeWorldVertices(slot->getBone(), &_vertices[offset], 0, vertexFormatLength);
					
				auto uvs = regionAttachment->getUVs();
				for (int i = 0; i < regionVertexSize; i++)
				{
					_vertices[offset + i * vertexFormatLength + 3] = uvs[i * 2];
					_vertices[offset + i * vertexFormatLength + 4] = uvs[i * 2 + 1];
				}
			}
			else
			{
				//更新顶点坐标数据,转化成世界坐标
				Vector<float> toClipVertices;
				toClipVertices.setSize(8, 0);
				regionAttachment->computeWorldVertices(slot->getBone(), toClipVertices, 0, 2);
					
				//获取当前的uv数据
				Vector<float>& toClipUvs = regionAttachment->getUVs();
					
				//构建当前的索引数据
				Vector<unsigned short> toClipIndices;
				toClipIndices.setSize(6, 0);
				toClipIndices[0] = 0;
				toClipIndices[1] = 1;
				toClipIndices[2] = 2;
				toClipIndices[3] = 0;
				toClipIndices[4] = 2;
				toClipIndices[5] = 3;
					
				//获取当前的数据裁剪后顶点,索引,uv
				_clipper->clipTriangles(toClipVertices, toClipIndices, toClipUvs, 2);
				auto vertices = _clipper->getClippedVertices();
				auto verticesCount = _clipper->getClippedVertices().size() >> 1;
				auto uvs = _clipper->getClippedUVs();
				auto indices = _clipper->getClippedTriangles();
				auto indicesCount = _clipper->getClippedTriangles().size();

				//写入裁剪后的索引数据, 这里是绝对索引
				_indices.resize(absIndex + indicesCount);
				for (int i = 0; i < indicesCount; i++)
				{
					_indices[absIndex + i] = indices[i] + absVertexCount;
				}
				absIndex += indicesCount;

				//写入裁剪后的顶点和uv数据
				absVertexCount += verticesCount;
				_vertices.resize(absVertexCount * vertexFormatLength);
				for (int i = 0; i < verticesCount; i++)
				{
					_vertices[offset + i * vertexFormatLength] = vertices[i * 2];
					_vertices[offset + i * vertexFormatLength + 1] = vertices[i * 2 + 1];
					_vertices[offset + i * vertexFormatLength + 3] = uvs[i * 2];
					_vertices[offset + i * vertexFormatLength + 4] = uvs[i * 2 + 1];
				}
			}
					
			compute_color(getColor(), slot->getColor(), regionAttachment->getColor(), color);
		}
		else if (slot->getAttachment()->getRTTI().instanceOf(MeshAttachment::rtti)) {
			//printf("MeshAttachment \n");
			MeshAttachment *mesh = static_cast<MeshAttachment *>(slot->getAttachment());

			//std::string clipping = _clipper->isClipping() == true ? "true" : "false";
			//printf("MeshAttachment : %s %s \n", slot->getAttachment()->getName().buffer(), clipping.c_str());

			if (!_clipper->isClipping())
			{
				auto &meshTriangles = mesh->getTriangles();
				size_t size = meshTriangles.size();
				_indices.resize(absIndex + size);
				for (size_t i = 0; i < size; ++i) {
					_indices[absIndex + i] = meshTriangles[i] + absVertexCount;
				}
				absIndex += size;

				size_t length = mesh->getWorldVerticesLength(); // 顶点坐标数据数量(x,y)
				absVertexCount += length / 2; //顶点数量
				_vertices.resize(absVertexCount * vertexFormatLength); //顶点数据数量(x,y,z,u,v,r,g,b,a,r1,g1,b1,a1,blend)
				mesh->computeWorldVertices(*slot, 0, length, &_vertices[offset], 0, vertexFormatLength);
				auto uvs = mesh->getUVs();
				for (int i = 0; i < length / 2; i++)
				{
					_vertices[offset + i * vertexFormatLength + 3] = uvs[i * 2];
					_vertices[offset + i * vertexFormatLength + 4] = uvs[i * 2 + 1];
				}
			}
			else
			{
				//更新顶点坐标数据,转化成世界坐标
				Vector<float> toClipVertices;
				toClipVertices.setSize(mesh->getWorldVerticesLength(), 0);
				mesh->computeWorldVertices(*slot, 0, mesh->getWorldVerticesLength(), toClipVertices, 0, 2);

				//获取当前的uv数据
				Vector<float>& toClipUvs = mesh->getUVs();

				//构建当前的索引数据
				Vector<unsigned short>& toClipIndices = mesh->getTriangles();

				//获取当前的数据裁剪后顶点,索引,uv
				_clipper->clipTriangles(toClipVertices, toClipIndices, toClipUvs, 2);
				auto vertices = _clipper->getClippedVertices();
				auto verticesCount = _clipper->getClippedVertices().size() >> 1;
				auto uvs = _clipper->getClippedUVs();
				auto indices = _clipper->getClippedTriangles();
				auto indicesCount = _clipper->getClippedTriangles().size();

				//写入裁剪后的索引数据, 这里是绝对索引
				_indices.resize(absIndex + indicesCount);
				for (int i = 0; i < indicesCount; i++)
				{
					_indices[absIndex + i] = indices[i] + absVertexCount;
				}
				absIndex += indicesCount;

				//写入裁剪后的顶点和uv数据
				absVertexCount += verticesCount;
				_vertices.resize(absVertexCount * vertexFormatLength);
				int vCount = 0;
				for (int i = 0; i < verticesCount; i++)
				{
					_vertices[offset + vCount * vertexFormatLength] = vertices[i * 2];
					_vertices[offset + vCount * vertexFormatLength + 1] = vertices[i * 2 + 1];
					_vertices[offset + vCount * vertexFormatLength + 3] = uvs[i * 2];
					_vertices[offset + vCount * vertexFormatLength + 4] = uvs[i * 2 + 1];
					vCount++;
				}
			}
					
			compute_color(getColor(), slot->getColor(), mesh->getColor(), color);
		}
		else if (slot->getAttachment()->getRTTI().instanceOf(ClippingAttachment::rtti))
		{
			//printf("Clip start ************************\n");
			ClippingAttachment *clip = static_cast<ClippingAttachment *>(slot->getAttachment());
			_clipper->clipStart(*slot, clip);
			continue;
		}
		else
			continue;

		for (size_t j = offset; j < absVertexCount * vertexFormatLength; j += vertexFormatLength) {
			//x
			//y
			_vertices[j + 2] = 0;//z
			//u
			//v
			_vertices[j + 5] = color.r;
			_vertices[j + 6] = color.g;
			_vertices[j + 7] = color.b;
			_vertices[j + 8] = color.a;
			_vertices[j + 9] = 0;
			_vertices[j + 10] = 0;
			_vertices[j + 11] = 0;
			_vertices[j + 12] = 0;
			_vertices[j + 13] = dealAddtiveInShader;

			if (get_bounds) {
				float vx = _vertices[j];
				float vy = _vertices[j + 1];
				minX = MathUtil::min(minX, vx);
				minY = MathUtil::min(minY, vy);
				maxX = MathUtil::max(maxX, vx);
				maxY = MathUtil::max(maxY, vy);
			}
		}
		_clipper->clipEnd(*slot);
	}

	//printf("**************************** vertices and index end \n");
	
	MaterialInfo materialInfo;
	materialInfo.startPos = breakStartIndex;
	materialInfo.endPos = absIndex;
	materialInfo.blend = convertBlendModeToIDE(lastBlendMode);
	materialInfo.texInfo = lastTexture;
	_materialInfos.push_back(materialInfo);

	//printf("**************************** last material \n");
	
	constructRenderData(L, absVertexCount, get_bounds, minX, minY, maxX, maxY);

	_clipper->clipEnd();

	return 1;
}

// gpu instance
int SkeletonExtend::computeRenderDataWithGpu(lua_State *L, bool get_bounds) {
	/*float minX = FLT_MAX;
	float minY = FLT_MAX;
	float maxX = FLT_MIN;
	float maxY = FLT_MIN;

	int vertexCount = 0;
	int index = 0;

	int vertexFormatLength = 22;
	Color skeletonColor = getColor();
	auto drawOrder = getDrawOrder();
	for (size_t i = 0; i < drawOrder.size(); ++i) {
		Slot *slot = drawOrder[i];
		if (slot->getBone().isActive()) {
			auto attachment = slot->getAttachment();
			Color slotColor = slot->getColor();
			Vector<float> *uvs;
			if (attachment != NULL) {
				Color color;
				size_t offset = vertexCount * vertexFormatLength;
				if (attachment->getRTTI().instanceOf(RegionAttachment::rtti)) {
					RegionAttachment *regionAttachment = static_cast<RegionAttachment *>(attachment);

					_indices.resize(index + 6);
					_indices[index] = (0 + vertexCount);
					_indices[index + 1] = (1 + vertexCount);
					_indices[index + 2] = (2 + vertexCount);
					_indices[index + 3] = (0 + vertexCount);
					_indices[index + 4] = (2 + vertexCount);
					_indices[index + 5] = (3 + vertexCount);
					index += 6;

					vertexCount += 4;
					_vertices.resize(vertexCount * vertexFormatLength);

					regionAttachment->computeVertices(slot->getBone(), &_vertices[offset], 0, vertexFormatLength);
					uvs = &regionAttachment->getUVs();
					compute_color(skeletonColor, slotColor, regionAttachment->getColor(), color);
				}
				else if (attachment->getRTTI().instanceOf(MeshAttachment::rtti)) {
					MeshAttachment *mesh = static_cast<MeshAttachment *>(attachment);

					auto &meshTriangles = mesh->getTriangles();
					size_t size = meshTriangles.size();
					_indices.resize(index + size);
					for (size_t i = 0; i < size; ++i) {
						_indices[index + i] = (meshTriangles[i] + vertexCount);
					}
					index += size;

					size_t count = mesh->getWorldVerticesLength() / 2;
					vertexCount += count;
					_vertices.resize(vertexCount * vertexFormatLength);

					mesh->computeVertices(*slot, 0, count * vertexFormatLength, &_vertices[offset], 0, vertexFormatLength);
					uvs = &mesh->getUVs();
					compute_color(skeletonColor, slotColor, mesh->getColor(), color);
				}

				int start = 12;
				for (size_t i = 0, j = offset; i < uvs->size(); i += 2, j += vertexFormatLength) {
					_vertices[j + start] = (*uvs)[i];
					_vertices[j + start + 1] = (*uvs)[i + 1];
					_vertices[j + start + 2] = color.r;
					_vertices[j + start + 3] = color.g;
					_vertices[j + start + 4] = color.b;
					_vertices[j + start + 5] = color.a;
					_vertices[j + start + 6] = 0;
					_vertices[j + start + 7] = 0;
					_vertices[j + start + 8] = 0;
					_vertices[j + start + 9] = 0;

					if (get_bounds) {
						float wx = 0, wy = 0;
						for (int k = 0; k < 4 && _vertices[j + k + 8] != -1; k++) {
							float vx = _vertices[j + k], vy = _vertices[j + k + 4];
							float weight = _vertices[j + k + 8];
							weight = (weight - (int)weight) * 10.0f;
							auto &bone = slot->getBone();
							wx += (vx * bone.getA() + vy * bone.getB() + bone.getWorldX()) * weight;
							wy += (vx * bone.getC() + vy * bone.getD() + bone.getWorldY()) * weight;
						}
						minX = MathUtil::min(minX, wx);
						minY = MathUtil::min(minY, wy);
						maxX = MathUtil::max(maxX, wx);
						maxY = MathUtil::max(maxY, wy);
					}
				}
			}
		}
	}

	constructRenderData(L, vertexCount, get_bounds, minX, minY, maxX, maxY);
	*/
	return 1;
}

void SkeletonExtend::constructRenderData(lua_State *L, int vertexCount, bool get_bounds, float minX, float minY, float maxX, float maxY) {
	lua_newtable(L);

	// vbo data
	lua_newtable(L);
	lua_pushlightuserdata(L, _vertices.data());
	lua_setfield(L, -2, "data");
	lua_pushnumber(L, vertexCount);
	lua_setfield(L, -2, "count");
	lua_setfield(L, -2, "vertices");

	// ibo data
	lua_newtable(L);
	lua_pushlightuserdata(L, _indices.data());
	lua_setfield(L, -2, "data");
	lua_pushnumber(L, _indices.size());
	lua_setfield(L, -2, "size");
	lua_setfield(L, -2, "indices");

	//// blend data
	//lua_newtable(L);
	//lua_pushlightuserdata(L, _blendInfos.data());
	//lua_setfield(L, -2, "data");
	//lua_pushnumber(L, _blendInfos.size());
	//lua_setfield(L, -2, "size");
	//lua_setfield(L, -2, "blends");

	//material data
	lua_newtable(L);
	int count = 1;
	for (auto i : _materialInfos)
	{
		lua_newtable(L);
		lua_pushnumber(L, i.startPos);
		lua_setfield(L, -2, "start_index");
		lua_pushnumber(L, i.endPos);
		lua_setfield(L, -2, "end_index");
		lua_newtable(L);
		lua_pushnumber(L, i.blend);
		lua_setfield(L, -2, "blend");
		lua_pushstring(L, i.texInfo.c_str());
		lua_setfield(L, -2, "texture0");
		lua_setfield(L, -2, "uniforms");
		lua_rawseti(L, -2, count++);
	}
	lua_setfield(L, -2, "material");

	// bound
	if (get_bounds) {
		x = minX;
		y = minY;
		width = maxX - minX;
		height = maxY - minY;

		lua_newtable(L);
		lua_pushnumber(L, width);
		lua_setfield(L, -2, "width");
		lua_pushnumber(L, height);
		lua_setfield(L, -2, "height");
		lua_pushnumber(L, x);
		lua_setfield(L, -2, "x");
		lua_pushnumber(L, y);
		lua_setfield(L, -2, "y");
		lua_setfield(L, -2, "bounds");
	}
}

int SkeletonExtend::getAnimationsInfo(lua_State *L) {
	lua_newtable(L);
	auto &animations = getData()->getAnimations();
	for (size_t i = 0; i < animations.size(); ++i) {
		lua_pushstring(L, animations[i]->getName().buffer());
		lua_newtable(L);

		//lua_pushstring(L, "duration");
		lua_pushnumber(L, animations[i]->getDuration());
		lua_setfield(L, -2, "duration");

		lua_settable(L, -3);
	}
	return 1;
}

void SkeletonExtend::setAttachmentLua(const char *slotName, const char *attachementName)
{
	setAttachment(slotName, attachementName);
}

Bone *SkeletonExtend::findBoneLua(const char *boneName)
{
	Bone *bone = findBone(boneName);
	return bone;
}

Attachment *SkeletonExtend::getAttachmentLua(const char *slotName, const char *attachmentName)
{
	Attachment *attachment = getAttachment(slotName, attachmentName);
	return attachment;
}

int SkeletonExtend::testCustomData(lua_State *L){
	_vertices = {-100,-100,0,0,0,1,1,1,1,0,0,0,0,
		         -100, 100,0,0,1,1,1,1,1,0,0,0,0,
		          100, 100,0,1,1,1,1,1,1,0,0,0,0,
		          100,-100,0,1,0,1,1,1,1,0,0,0,0};
	/*,
		-50, -50, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0,
		-50, 50, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		50, 50, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0,
		50, -50, 0, 1, 0, 1, 1, 1, 1, 0, 0, 0, 0*/
	//,4,5,6,4,6,7 
	_indices = {0,1,2,0,2,3};
	_blendInfos = {1,6,5};

	constructRenderData(L, _vertices.size() / 13 , false);

	return 1;
}

void skel::SkeletonExtend::setSkinByName(const char *skinName)
{
	setSkin(skinName);
}

void skel::SkeletonExtend::setSkinBySkin(Skin *newSkin)
{
	setSkin(newSkin);
}

int skel::SkeletonExtend::getSkeletonId()
{
	return (int)id;
}

LuaIntf::LuaRef skel::SkeletonExtend::getBoneInfo(lua_State *L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef info(L, -1);
	LS.pop();

	//当前激活的骨骼列表
	Vector<Updatable *> updataCacheList = getUpdateCacheList();

	int boneCount = 0;
	for (size_t i = 0; i < updataCacheList.size(); ++i)
	{
		Updatable *updatable = updataCacheList[i];
		if (updatable->getRTTI().isExactly(Bone::rtti))
		{
			Bone *b = ((Bone *)updatable);
			
			if (b->isActive())
			{
				boneCount++;

				LS.newTable();
				LuaIntf::LuaRef boneInfo(L, -1);
				LS.pop();
				
				boneInfo.set<std::string, std::string>("name", b->getData().getName().buffer());
				boneInfo.set<std::string, bool>("state", b->isActive());
				boneInfo.set<std::string, float>("worldX", b->getWorldX());
				boneInfo.set<std::string, float>("worldY", b->getWorldY());
				boneInfo.set<std::string, float>("rotation", b->localToWorldRotation(b->getRotation()));
				boneInfo.set<std::string, float>("worldScaleX", b->getWorldScaleX());
				boneInfo.set<std::string, float>("worldScaleY", b->getWorldScaleY());
				boneInfo.set<std::string, float>("shearX", b->getShearX());
				boneInfo.set<std::string, float>("shearY", b->getShearY());
				boneInfo.set<std::string, float>("length", b->getData().getLength());
				boneInfo.set<std::string, float>("localRotation", b->getRotation());

				info.set<int, LuaIntf::LuaRef>(boneCount, boneInfo);
			}
		}
	}
	
	return info;
}

LuaIntf::LuaRef skel::SkeletonExtend::getAttachmentAndSlotInfo(lua_State * L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef info(L, -1);
	LS.pop();

	Vector<Slot *> &slots = getSlots();

    Skin *defaultSkin = getData()->getDefaultSkin();

	if (defaultSkin == NULL) {
		return info;
	}

	Skin::AttachmentMap::Entries defaultAttachments = defaultSkin->getAttachments();

	int boneCount = 0;

	while (defaultAttachments.hasNext())
	{
		Skin::AttachmentMap::Entry &entry = defaultAttachments.next();
		int slotIndex = entry._slotIndex;
		Slot *slot = slots[slotIndex];
		Bone *b = &slot->getBone();

		if (b->isActive())
		{
			boneCount++;

			LS.newTable();
			LuaIntf::LuaRef boneInfo(L, -1);
			LS.pop();

			boneInfo.set<std::string, bool>("state", b->isActive());
			boneInfo.set<std::string, float>("worldX", b->getWorldX());
			boneInfo.set<std::string, float>("worldY", b->getWorldY());
			boneInfo.set<std::string, float>("rotation", b->localToWorldRotation(b->getRotation()));
			boneInfo.set<std::string, float>("worldScaleX", b->getWorldScaleX());
			boneInfo.set<std::string, float>("worldScaleY", b->getWorldScaleY());
			boneInfo.set<std::string, float>("shearX", b->getShearX());
			boneInfo.set<std::string, float>("shearY", b->getShearY());
			boneInfo.set<std::string, float>("length", b->getData().getLength());
			boneInfo.set<std::string, float>("localRotation", b->getRotation());
			boneInfo.set<std::string, std::string>("slotName", slot->getData().getName().buffer());
			boneInfo.set<std::string, std::string>("attachmentName", entry._name.buffer());

			info.set<int, LuaIntf::LuaRef>(boneCount, boneInfo);
		}
	}


	Skin *skin = getSkin();

	if (skin == NULL)
	{
		return info;
	}

	Skin::AttachmentMap::Entries attachments = skin->getAttachments();
	

	while (attachments.hasNext())
	{
		Skin::AttachmentMap::Entry &entry = attachments.next();
		int slotIndex = entry._slotIndex;
		Slot *slot = slots[slotIndex];
		Bone *b = &slot->getBone();

		if (b->isActive())
		{
			boneCount++;

			LS.newTable();
			LuaIntf::LuaRef boneInfo(L, -1);
			LS.pop();

			boneInfo.set<std::string, bool>("state", b->isActive());
			boneInfo.set<std::string, float>("worldX", b->getWorldX());
			boneInfo.set<std::string, float>("worldY", b->getWorldY());
			boneInfo.set<std::string, float>("rotation", b->localToWorldRotation(b->getRotation()));
			boneInfo.set<std::string, float>("worldScaleX", b->getWorldScaleX());
			boneInfo.set<std::string, float>("worldScaleY", b->getWorldScaleY());
			boneInfo.set<std::string, float>("shearX", b->getShearX());
			boneInfo.set<std::string, float>("shearY", b->getShearY());
			boneInfo.set<std::string, float>("length", b->getData().getLength());
			boneInfo.set<std::string, float>("localRotation", b->getRotation());
			boneInfo.set<std::string, std::string>("slotName", slot->getData().getName().buffer());
			boneInfo.set<std::string, std::string>("attachmentName", entry._name.buffer());

			info.set<int, LuaIntf::LuaRef>(boneCount, boneInfo);
		}
	}

	return info;
}

