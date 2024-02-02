#include "SDFLoader.h"
#include <iostream>

std::mutex SDFLoader::_sdfDataMutex;
std::map<std::string, SDFData> SDFLoader::m_sdfDataMap;

SDFLoader::SDFLoader()
{
}

SDFLoader::~SDFLoader()
{
}

void SDFLoader::loadSDFData(lua_State* L, std::string id, LuaIntf::LuaRef sdfDataRef)
{
	std::lock_guard<std::mutex> guard(_sdfDataMutex);

	//std::cout << "loadSDFData" << std::endl;

	auto sdfData = SDFData();
	//std::cout << "kerning" << std::endl;
	auto kerningRef = sdfDataRef.get("kerning");

	for (int i = 1; i <= kerningRef.len(); i++)
	{
		auto kerningData = kerning();
		auto kerningDataRef = kerningRef.get(i);
		//std::cout << "advance" << std::endl;
		kerningData.advance = Get_Float(kerningDataRef, "advance");
		//std::cout << "unicode1" << std::endl;
		kerningData.unicode1 = Get_Int(kerningDataRef, "unicode1");
		//std::cout << "unicode2" << std::endl;
		kerningData.unicode2 = Get_Int(kerningDataRef, "unicode2");

		sdfData.kerning.push_back(kerningData);
	}

	//std::cout << "glyphs" << std::endl;
	auto glyphsRef = sdfDataRef.get("glyphs");

	for (int i = 1; i <= glyphsRef.len(); i++)
	{
		auto glyphsData = glyphs();
		auto glyphsDataRef = glyphsRef.get(i);

		//std::cout << "planeBounds" << std::endl;
		if (glyphsDataRef.has("planeBounds"))
		{
			auto planeBondsDataRef = glyphsDataRef.get("planeBounds");
			glyphsData.planeBounds = planeBounds();
			glyphsData.planeBounds.left = Get_Float(planeBondsDataRef, "left");
			glyphsData.planeBounds.top = Get_Float(planeBondsDataRef, "top");
			glyphsData.planeBounds.bottom = Get_Float(planeBondsDataRef, "bottom");
			glyphsData.planeBounds.right = Get_Float(planeBondsDataRef, "right");
		}
		

		//std::cout << "atlasBounds" << std::endl;
		if (glyphsDataRef.has("atlasBounds"))
		{
			auto atlasBondsDataRef = glyphsDataRef.get("atlasBounds");
			glyphsData.atlasBounds = atlasBounds();
			glyphsData.atlasBounds.left = Get_Float(atlasBondsDataRef, "left");
			glyphsData.atlasBounds.top = Get_Float(atlasBondsDataRef, "top");
			glyphsData.atlasBounds.bottom = Get_Float(atlasBondsDataRef, "bottom");
			glyphsData.atlasBounds.right = Get_Float(atlasBondsDataRef, "right");
		}

		//std::cout << "advance" << std::endl;
		glyphsData.advance = Get_Float(glyphsDataRef, "advance");
		//std::cout << "unicode" << std::endl;
		glyphsData.unicode = Get_Int(glyphsDataRef, "unicode");

		sdfData.glyphs.push_back(glyphsData);
	}

	//std::cout << "atlas" << std::endl;
	auto atlasDataRef = sdfDataRef.get("atlas");
	sdfData.atlas = atlas();
	sdfData.atlas.distanceRange = Get_Float(atlasDataRef, "distanceRange");
	sdfData.atlas.type = Get_String(atlasDataRef, "type");
	sdfData.atlas.width = Get_Float(atlasDataRef, "width");
	sdfData.atlas.height = Get_Float(atlasDataRef, "height");
	sdfData.atlas.size = Get_Float(atlasDataRef, "size");
	sdfData.atlas.yOrigin = Get_String(atlasDataRef, "yOrigin");

	//std::cout << "metrics" << std::endl;
	auto metricsDataRef = sdfDataRef.get("metrics");
	sdfData.metrics = metrics();
	sdfData.metrics.ascender = Get_Float(metricsDataRef, "ascender");
	sdfData.metrics.descender = Get_Float(metricsDataRef, "descender");
	sdfData.metrics.emSize = Get_Float(metricsDataRef, "emSize");
	sdfData.metrics.lineHeight = Get_Float(metricsDataRef, "lineHeight");
	sdfData.metrics.underlineThickness = Get_Float(metricsDataRef, "underlineThickness");
	sdfData.metrics.underlineY = Get_Float(metricsDataRef, "underlineY");

	for (int i = 0; i < sdfData.glyphs.size(); i++)
	{
		auto glyphsData = sdfData.glyphs[i];

		auto charInfoData = charInfo();
		//加载时计算纹理数据
		charInfoData.uvLeft = glyphsData.atlasBounds.left / sdfData.atlas.width;
		charInfoData.uvTop = 1.0 - glyphsData.atlasBounds.top / sdfData.atlas.height;
		charInfoData.uvBottom = 1.0 - glyphsData.atlasBounds.bottom / sdfData.atlas.height;
		charInfoData.uvRight = glyphsData.atlasBounds.right / sdfData.atlas.width;
		
		charInfoData.vertexleft = glyphsData.planeBounds.left;
		charInfoData.vertexTop = glyphsData.planeBounds.top;
		charInfoData.vertexBottom = glyphsData.planeBounds.bottom;
		charInfoData.vertexRight = glyphsData.planeBounds.right;
		charInfoData.advance = glyphsData.advance;

		sdfData.charInfos[glyphsData.unicode] = charInfoData;
	}


	m_sdfDataMap[id] = sdfData;
}

LuaIntf::LuaRef SDFLoader::getCharInfoFromId(lua_State* L, std::string id, LuaIntf::LuaRef unicodes, int fontSize)
{
	std::lock_guard<std::mutex> guard(_sdfDataMutex);

	//std::cout << "getCharInfoFromId" << std::endl;
	//auto dddd = m_sdfDataMap.find(id);
	//std::cout << id << std::endl;
	//if (m_sdfDataMap.find(id) != m_sdfDataMap.end())
	//{
		//std::cout << "00000000000" << std::endl;

		LuaIntf::LuaState LS(L);
		LS.newTable();
		LuaIntf::LuaRef ref(L, -1);
		LS.pop();

		//std::cout << "1111111111" << std::endl;

		SDFData sdfData = m_sdfDataMap[id];

		LS.newTable();
		LuaIntf::LuaRef charInfoRef(L, -1);
		LS.pop();

		//std::cout << "charInfos" << std::endl;
		ref.set<std::string, LuaIntf::LuaRef>("charInfos", charInfoRef);

		LS.newTable();
		LuaIntf::LuaRef kerningRef(L, -1);
		LS.pop();

		//std::cout << "kerning" << std::endl;
		ref.set<std::string, LuaIntf::LuaRef>("kerning", kerningRef);

		for (int i = 1; i <= unicodes.len(); i++)
		{
			LS.newTable();
			LuaIntf::LuaRef charInfoDataRef(L, -1);
			LS.pop();

			//std::cout << "unicodes" << std::endl;
			int unicodeIndex = Get_Int(unicodes, i);
			charInfoRef.set<int, LuaIntf::LuaRef>(unicodeIndex, charInfoDataRef);
			charInfo charInfo = sdfData.charInfos[unicodeIndex];
			
			//std::cout << "uvInfo" << std::endl;
			charInfoDataRef.set<int, float>(1, charInfo.uvLeft);
			charInfoDataRef.set<int, float>(2, charInfo.uvTop);
			charInfoDataRef.set<int, float>(3, charInfo.uvBottom);
			charInfoDataRef.set<int, float>(4, charInfo.uvRight);

			//std::cout << "meshInfo" << std::endl;
			//获取数据的时候再根据尺寸计算文字布局
			charInfoDataRef.set<int, float>(5, charInfo.vertexleft * fontSize);
			charInfoDataRef.set<int, float>(6, fontSize - charInfo.vertexTop * fontSize + sdfData.metrics.underlineY);
			charInfoDataRef.set<int, float>(7, fontSize - charInfo.vertexBottom * fontSize + sdfData.metrics.underlineY);
			charInfoDataRef.set<int, float>(8, charInfo.vertexRight * fontSize);

			//std::cout << "advance" << std::endl;
			charInfoDataRef.set<int, float>(9, charInfo.advance * fontSize);

			////std::cout << "uvInfo" << std::endl;
			//charInfoDataRef.set<std::string, LuaIntf::LuaRef>("uvInfo", uvInfoRef);

			//uvInfoRef.set<std::string, float>("left", charInfo.uvLeft);
			//uvInfoRef.set<std::string, float>("top", charInfo.uvTop);
			//uvInfoRef.set<std::string, float>("bottom", charInfo.uvBottom);
			//uvInfoRef.set<std::string, float>("right", charInfo.uvRight);

			//LS.newTable();
			//LuaIntf::LuaRef meshInfoRef(L, -1);
			//LS.pop();

			////std::cout << "meshInfo" << std::endl;
			//charInfoDataRef.set<std::string, LuaIntf::LuaRef>("meshInfo", meshInfoRef);

			////获取数据的时候再根据尺寸计算文字布局
			//meshInfoRef.set<std::string, float>("left", charInfo.vertexleft * fontSize);
			//meshInfoRef.set<std::string, float>("top", fontSize - charInfo.vertexTop * fontSize + sdfData.metrics.underlineY);
			//meshInfoRef.set<std::string, float>("bottom", fontSize - charInfo.vertexBottom * fontSize + sdfData.metrics.underlineY);
			//meshInfoRef.set<std::string, float>("right", charInfo.vertexRight * fontSize);
		 //   
			////std::cout << "advance" << std::endl;
			//charInfoDataRef.set<std::string, float>("advance", charInfo.advance * fontSize);

			if (i < unicodes.len())
			{
				int unicode1 = Get_Int(unicodes, i);
				int unicode2 = Get_Int(unicodes, i + 1);

				for (int j = 1; j <= sdfData.kerning.size(); j++)
				{
					kerning kerningData = sdfData.kerning[i];
					if (unicode1 == kerningData.unicode1 && unicode2 == kerningData.unicode2)
					{
						LS.newTable();
						LuaIntf::LuaRef kerningDataRef(L, -1);
						LS.pop();

						kerningDataRef.set<int, int>(1, unicode1);
						kerningDataRef.set<int, int>(2, unicode2);
						kerningDataRef.set<int, float>(3, kerningData.advance);

						kerningRef.set<int, LuaIntf::LuaRef>(j, kerningDataRef);
					}
				}
			}
		}

		return ref;
	//}

}

LuaIntf::LuaRef SDFLoader::getUniformDataFromId(lua_State* L, std::string id)
{
	std::lock_guard<std::mutex> guard(_sdfDataMutex);

	//if (m_sdfDataMap.find(id) != m_sdfDataMap.end())
	//{
		SDFData sdfData = m_sdfDataMap[id];

		LuaIntf::LuaState LS(L);
		LS.newTable();
		LuaIntf::LuaRef ref(L, -1);
		LS.pop();

		ref.set<int, float>(1, sdfData.atlas.distanceRange);
		ref.set<int, std::string>(2, sdfData.atlas.type);
		ref.set<int, float>(3, sdfData.atlas.width);
		ref.set<int, float>(4, sdfData.atlas.height);
		ref.set<int, float>(5, sdfData.atlas.size);
		ref.set<int, std::string>(6, sdfData.atlas.yOrigin);

		ref.set<int, float>(7, sdfData.metrics.ascender);
		ref.set<int, float>(8, sdfData.metrics.descender);
		ref.set<int, float>(9, sdfData.metrics.emSize);
		ref.set<int, float>(10, sdfData.metrics.lineHeight);
		ref.set<int, float>(11, sdfData.metrics.underlineThickness);
		ref.set<int, float>(12, sdfData.metrics.underlineY);

		/*LS.newTable();
		LuaIntf::LuaRef atlasRef(L, -1);
		LS.pop();

		ref.set<std::string, LuaIntf::LuaRef>("atlas", atlasRef);

		atlasRef.set<std::string, float>("distanceRange", sdfData.atlas.distanceRange);
		atlasRef.set<std::string, std::string>("type", sdfData.atlas.type);
		atlasRef.set<std::string, float>("width", sdfData.atlas.width);
		atlasRef.set<std::string, float>("height", sdfData.atlas.height);
		atlasRef.set<std::string, float>("size", sdfData.atlas.size);
		atlasRef.set<std::string, std::string>("yOrigin", sdfData.atlas.yOrigin);

		LS.newTable();
		LuaIntf::LuaRef metricsRef(L, -1);
		LS.pop();

		ref.set<std::string, LuaIntf::LuaRef>("metrics", metricsRef);

		metricsRef.set<std::string, float>("ascender", sdfData.metrics.ascender);
		metricsRef.set<std::string, float>("descender", sdfData.metrics.descender);
		metricsRef.set<std::string, float>("emSize", sdfData.metrics.emSize);
		metricsRef.set<std::string, float>("lineHeight", sdfData.metrics.lineHeight);
		metricsRef.set<std::string, float>("underlineThickness", sdfData.metrics.underlineThickness);
		metricsRef.set<std::string, float>("underlineY", sdfData.metrics.underlineY);*/

		return ref;
	//}
}

float SDFLoader::getStringWidthFromId(lua_State* L, std::string id, LuaIntf::LuaRef unicodes, int fontSize, LuaIntf::LuaRef charAdjustment, float advanceOffset)
{
	std::lock_guard<std::mutex> guard(_sdfDataMutex);

	SDFData sdfData = m_sdfDataMap[id];
	
	float originX = 0.0;

	for (int i = 1; i <= unicodes.len(); i++)
	{
		//std::cout << "unicodes" << std::endl;
		int unicodeIndex = Get_Int(unicodes, i);
		std::string unicodeIndexStr = std::to_string(unicodeIndex);
		charInfo charInfo = sdfData.charInfos[unicodeIndex];

		originX += charInfo.advance * fontSize + advanceOffset;

		if (charAdjustment.has(unicodeIndexStr))
		{
			auto charAdjustmentInfo = charAdjustment.get(unicodeIndexStr);
			auto offsetRef = charAdjustmentInfo.get("offset");
			auto sizeRef = charAdjustmentInfo.get("size");
			originX += Get_Float(offsetRef, 1) + Get_Float(offsetRef, 1);
		}

		float kerningAdvance = 0.0;

		if (i < unicodes.len())
		{
			int currentUnicode = Get_Int(unicodes, i);
			int nextUnicode = Get_Int(unicodes, i + 1);

			for (int j = 0; j < sdfData.kerning.size(); j++)
			{
				auto kerningInfo = sdfData.kerning[j];
				if (currentUnicode == kerningInfo.unicode1 && nextUnicode == kerningInfo.unicode2)
				{
					kerningAdvance = kerningInfo.advance;
				}
			}
		}

		originX -= kerningAdvance;
	}

	return originX;
}






