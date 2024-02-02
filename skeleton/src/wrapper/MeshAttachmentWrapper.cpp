#include "MeshAttachmentWrapper.h"

using namespace skel;

MeshAttachmentWrapper::MeshAttachmentWrapper(const String &name) : MeshAttachment(name) {
	_tag = "mesh";
}

std::string MeshAttachmentWrapper::getTag()
{
	return _tag;
}

std::string MeshAttachmentWrapper::getName2() {
	std::string name = getName().buffer();
	return name;
}

LuaIntf::LuaRef MeshAttachmentWrapper::computeWorldVerticesWrapper(lua_State* L, SlotWrapper slot)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef vertices(L, -1);
	LS.pop();

	Vector<float> worldVertices;
	auto size = getWorldVerticesLength();
	worldVertices.setSize(size, size);
	computeWorldVertices(slot, worldVertices);

	size_t index = 0;
	while (index < worldVertices.size())
	{
		vertices.set<int, float>(index + 1, worldVertices[index]);
		index++;
	}

	return vertices;
}

LuaIntf::LuaRef MeshAttachmentWrapper::verticesGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef vertices(L, -1);
	LS.pop();

	size_t index = 0;
	auto versVec = getVertices();
	// normal vertices
	if (_bones.size() == 0) {
		while (index < versVec.size())
		{
			vertices.set<int, float>(index + 1, versVec[index]);
			index++;
		}
		return vertices;
	}
	// weighted vertices
	else {
		int index = 1;
		int i, n,total = 0;
		for (i = 0, n = _bones.size(); i < n;) {
			int bCount = _bones[i++];
			vertices.set<int, int>(index++, bCount);
			for (int j = 0; j < bCount; j++) {
				vertices.set<int, int>(index++, _bones[i++]);//bone index
				vertices.set<int, float>(index++, _vertices[total * 3]);//x
				vertices.set<int, float>(index++, _vertices[total * 3 + 1]);//y
				vertices.set<int, float>(index++, _vertices[total * 3 + 2]);//weight
				total++;
			}
		}
		if (vertices.len() != _vertices.size() + _bones.size()) {
			printf("verticesGetter    error!!!!!\n");
		}
		return vertices;
	}
}

void MeshAttachmentWrapper::verticesSetter(LuaIntf::LuaRef vertices) {

	int len = vertices.len();
	int realVerticesCount = _regionUVs.size();
	_bones.clear();
	_vertices.clear();
	// normal vertices
	if (realVerticesCount == len) {
		int index = 1;
		while (index <= len) {
			_vertices.add(vertices.get<float>(index));
			index++;
		}
		_worldVerticesLength = _vertices.size();
	}
	// weighted vertices 
	else {
		
		int vCount = 0;
		int i, n, nn;
		for (i = 1, n = len; i <= n;) {
			int boneCount = vertices.get<int>(i++);
			_bones.add(boneCount);
			for (nn = i + boneCount * 4; i < nn; i += 4) {
				_bones.add(vertices.get<int>(i));
				_vertices.add(vertices.get<float>(i+1) );
				_vertices.add(vertices.get<float>(i + 2) );
				_vertices.add(vertices.get<float>(i + 3));
			}
			vCount += 2;
		}
		_worldVerticesLength = vCount;
	}
}

LuaIntf::LuaRef MeshAttachmentWrapper::trianglesGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef triangles(L, -1);
	LS.pop();
	size_t index = 0;
	while (index < _triangles.size())
	{
		triangles.set<int, float>(index + 1, _triangles[index]);
		index++;
	}
	return triangles;
}

void MeshAttachmentWrapper::trianglesSetter(LuaIntf::LuaRef triangles) {
	_triangles.clear();

	int index = 1;
	int len = triangles.len();
	while (index <= len) {
		_triangles.add(triangles.get<int>(index));
		index++;
	}
}

LuaIntf::LuaRef MeshAttachmentWrapper::uvsGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef uvs(L, -1);
	LS.pop();
	size_t index = 0;
	while (index < _uvs.size())
	{
		uvs.set<int, float>(index + 1, _uvs[index]);
		index++;
	}
	return uvs;
}

void MeshAttachmentWrapper::uvsSetter(LuaIntf::LuaRef uvs) {
	_uvs.clear();

	int index = 1;
	int len = uvs.len();
	while (index <= len) {
		_uvs.add(uvs.get<float>(index));
		index++;
	}
}

LuaIntf::LuaRef MeshAttachmentWrapper::edgesGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef edges(L, -1);
	LS.pop();
	size_t index = 0;
	while (index < _edges.size())
	{
		edges.set<int, float>(index + 1, _edges[index]);
		index++;
	}
	return edges;
}

void MeshAttachmentWrapper::edgesSetter(LuaIntf::LuaRef edges) {
	_edges.clear();

	int index = 1;
	int len = edges.len();
	while (index <= len) {
		_edges.add(edges.get<int>(index));
		index++;
	}
}


LuaIntf::LuaRef MeshAttachmentWrapper::regionUVsGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef regionUVs(L, -1);
	LS.pop();
	size_t index = 0;
	while (index < _regionUVs.size())
	{
		regionUVs.set<int, float>(index + 1, _regionUVs[index]);
		index++;
	}
	return regionUVs;
}

void MeshAttachmentWrapper::regionUVsSetter(LuaIntf::LuaRef uvs) {
	_regionUVs.clear();

	int index = 1;
	int len = uvs.len();
	while (index <= len) {
		_regionUVs.add(uvs.get<float>(index));
		index++;
	}
}

LuaIntf::LuaRef MeshAttachmentWrapper::bonesGetter(lua_State* L)
{
	LuaIntf::LuaState LS(L);
	LS.newTable();
	LuaIntf::LuaRef bones(L, -1);
	LS.pop();
	size_t index = 0;
	while (index < _bones.size())
	{
		bones.set<int, int>(index + 1, _bones[index]);
		index++;
	}
	return bones;
}

void MeshAttachmentWrapper::bonesSetter(LuaIntf::LuaRef uvs) {
	
}

void MeshAttachmentWrapper::setPath(std::string path) {
	MeshAttachment::setPath(path.c_str());
}

std::string MeshAttachmentWrapper::getPath() {
	return MeshAttachment::getPath().buffer();
}