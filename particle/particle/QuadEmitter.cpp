#include "QuadEmitter.h"


template<class T>
void QuadEmitter<T>::setAttributeFormat()
{
	//std::cout << "8888888888" << std::endl;
	if ((m_texturePath.IsObject() || m_texturePathInfo.isPinMap == true) && m_subUVMode == 0)
	{
		m_attributeFormat["pinAttribute"] = true;

		m_stripeSize += 5;

		m_attributeFormat["subUVAttribute"] = false;
	}
	else
	{
		m_attributeFormat["pinAttribute"] = false;

		if (m_subUVMode == 1 || m_subUVMode == 3)
		{
			m_attributeFormat["subUVAttribute"] = true;
			m_stripeSize += 4;
		}
		else if (m_subUVMode == 2 || m_subUVMode == 4)
		{
			m_attributeFormat["subUVAttribute"] = true;
			m_attributeFormat["subUVBlendAttribute"] = true;
			m_stripeSize += 9;
		}
	}

	if (m_subUVMode == 0)
	{
		m_attributeFormat["subUVAttribute"] = false;
	}
	else 

	//std::cout << "8888888888" << std::endl;
	/*if (m_moduleMap[InitialSize] == true || m_moduleMap[SizeByScale] == true || m_moduleMap[SizeByLife] == true || m_moduleMap[SizeBySpeed] == true)
	{
		m_attributeFormat["sizeAttribute"] = true;
		m_stripeSize += 1;
	}
	else
		m_attributeFormat["sizeAttribute"] = false;*/

	//std::cout << "8888888888" << std::endl;
	if (m_moduleMap[InitialColor] == true || m_moduleMap[ColorOverLife] == true || m_moduleMap[ColorScaleLife] == true)
	{
		m_attributeFormat["colorAttribute"] = true;
		m_stripeSize += 4;
	}
	else
		m_attributeFormat["colorAttribute"] = false;

	//std::cout << "8888888888" << std::endl;
	/*if (m_flipUV != 0)
	{
		m_attributeFormat["flipAttribute"] = true;
		m_stripeSize += 2;
	}
	else
		m_attributeFormat["flipAttribute"] = false;*/


	if (m_moduleMap[InitRotate] == true ||
		m_moduleMap[RotateOverLife] == true ||
		m_moduleMap[InitRotRate] == true ||
		m_moduleMap[RotRateLife] == true ||
		m_inheritSourceRotation == true)
	{
		m_attributeFormat["rotationAttribute"] = true;
		m_stripeSize += 1;
	}
	else
		m_attributeFormat["rotationAttribute"] = false;


	//std::cout << "init vector length" << m_shaderAttribute.size() << m_shaderAttribute.capacity() << std::endl;

	m_particleList.clear();
	m_particleList.reserve(m_particleNum);

	m_shaderAttribute.clear();
	m_shaderAttribute.reserve(m_particleNum);

	int index = 0;

	for (int i = 0; i < m_particleNum; i++)
	{
		Particle<T>* par = new Particle<T>(this);
		m_particleList.push_back(par);
		T attri;

		m_shaderAttribute.push_back(attri);
		vec3 pos = par->getShaderAttriPos();
		m_shaderAttribute[i].data[index] = pos.x;
		m_shaderAttribute[i].data[index + 1] = pos.y;
		m_shaderAttribute[i].data[index + 2] = pos.z;
	}

	index += 3;

	if (m_attributeFormat["pinAttribute"] == true)
	{
		vec2 oriSize = m_textureSize;
		vec2 pos = vec2();
		vec2 size = vec2();
		bool rotated = false;
		if (m_texturePath != "" && m_texturePathInfo.isPinMap == false)
		{
			jsonVal& texData = m_texturePath;
			vec2 realPos = vec2(texData["x"].GetFloat(), texData["y"].GetFloat());
			vec2 realSize = vec2(texData["width"].GetFloat(), texData["height"].GetFloat());
			pos = realPos / oriSize;
			size = realSize / oriSize;
			if (texData.HasMember("rotated") && texData["rotated"].IsBool())
				rotated = texData["rotated"].GetBool();
		}
		else if (m_texturePath == "" && m_texturePathInfo.isPinMap == true)
		{
			vec2 realPos = vec2(m_texturePathInfo.x, m_texturePathInfo.y);
			vec2 realSize = vec2(m_texturePathInfo.width, m_texturePathInfo.height);
			pos = realPos / oriSize;
			size = realSize / oriSize;
			rotated = m_texturePathInfo.rotated;
		}

		//std::cout << "textureSize" << oriSize.x << "  " << oriSize.y << std::endl;

		//maybe could make it uniform;

		if (rotated == true)
			m_pinAngle = 3.1415926 / 2.0f;
		else
			m_pinAngle = 0.0f;

		m_pinCoord = vec4(pos.x, pos.y, size.x, size.y);

		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_pinCoord.x;
			m_shaderAttribute[i].data[index + 1] = m_pinCoord.y;
			m_shaderAttribute[i].data[index + 2] = m_pinCoord.z;
			m_shaderAttribute[i].data[index + 3] = m_pinCoord.w;
			m_shaderAttribute[i].data[index + 4] = m_pinAngle;
		}

		index += 5;//8
	}

	/*if (m_attributeFormat["sizeAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriSize();
		}

		index++;
	}*/

	if (m_attributeFormat["colorAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			vec3 color = m_particleList[i]->getShaderAttriColor();
			m_shaderAttribute[i].data[index] = color.x;
			m_shaderAttribute[i].data[index + 1] = color.y;
			m_shaderAttribute[i].data[index + 2] = color.z;
			m_shaderAttribute[i].data[index + 3] = m_particleList[i]->getShaderAttriAlpha();
		}
		index += 4;
	}

	/*if (m_attributeFormat["flipAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriFlipU();
			m_shaderAttribute[i].data[index + 1] = m_particleList[i]->getShaderAttriFlipV();
		}

		index += 2;
	}*/

	if (m_attributeFormat["rotationAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriRot();
		}

		index++;
	}

	if (m_attributeFormat["subUVAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			vec4 coord = m_particleList[i]->getShaderAttriSubCoord();
			m_shaderAttribute[i].data[index] = coord.x;
			m_shaderAttribute[i].data[index + 1] = coord.y;
			m_shaderAttribute[i].data[index + 2] = coord.z;
			m_shaderAttribute[i].data[index + 3] = coord.w;
		}

		index += 4;
	}

	if (m_attributeFormat["subUVBlendAttribute"] == true)
	{
		for (int i = 0; i < m_particleNum; i++)
		{
			vec4 coordNext = m_particleList[i]->getShaderAttriSubCoordNext();
			m_shaderAttribute[i].data[index] = coordNext.x;
			m_shaderAttribute[i].data[index + 1] = coordNext.y;
			m_shaderAttribute[i].data[index + 2] = coordNext.z;
			m_shaderAttribute[i].data[index + 3] = coordNext.w;
			m_shaderAttribute[i].data[index + 4] = m_particleList[i]->getShaderAttriSubRatio();
		}
	}

	setSubCoordList();
}

template<class T>
void QuadEmitter<T>::update()
{
	float delay = m_currentDelay;
	// deal with delay, delay only first loop and loops
	if (m_currentDuration != 0)
	{
		m_elapsed = m_elapsed + dt;

		m_elapsedDraw = m_elapsedDraw + dt;

		// for clear logic
		// if delay every loop, then do nothing
		if (!m_delayFirstLoop)
		{
		}
		// if delay first loop and current loop is in the first loop, do nothing
		else if (m_delayFirstLoop && m_loopCount == 0)
		{
		}
		//if delay first loop and current loop is not first loop, make delay time 0
		else
			delay = 0.0f;
	}

	//during delay time
	if (m_elapsed < delay)
	{
		m_emitterRunningState = RUNNING_FRAME_STATE::IDEL;
		m_emitterLifeTime = 0.0f;
	}
	//end delay,doing loop update
	else if ((m_elapsed >= delay) && ((m_elapsed - delay) < m_currentDuration))
	{
		//return life rate or seconds
		//self.m_emitterLifeTime = (self.m_elapsed - self.delay) / self.m_currentDuration;

		m_emitterRunningState = RUNNING_FRAME_STATE::RUNNING;
		m_emitterLifeTime = ((float)m_elapsed - delay) / 1000.0f;


		if (getFloatDistriValue(m_emission) > 0.0f || m_useBrust)
		{
			// doing loops in loopCount
			if ((m_loop == 0) || (m_loopCount < m_loop))
			{
				if (m_emitCount == 0.0f && getFloatDistriValue(m_emission) > 0.0f)
					addParticle();

				float emission = getFloatDistriValue(m_emission) * getFloatDistriValue(m_emissionScale) / 1000.0f;

				//std::cout << "emission " << getFloatDistriValue(m_emission) << std::endl;

				if (emission != 0.0)
				{
					float perParticleTime = 1.0f / emission;
					m_emitCount = m_emitCount + (float)dt;

					//emit one frame particles
					while ((!isFull()) && m_emitCount > perParticleTime)
					{
						m_emitCount = m_emitCount - perParticleTime;

						addParticle();
					}
				}
				else
					m_emitCount = -0.000001;

			}
			else
				m_currentBrust = 0;
		}
	}
	// if end a loop 
	else if ((m_elapsed - delay) >= m_currentDuration)
	{
		m_emitterRunningState = RUNNING_FRAME_STATE::LOOP_END;
		//std::cout << "Emitter One Loop End" << std::endl;

		//emitter loop end state = true --> render thread put end state --> lua do callback



		//when emitter deactivated kill all particles
		if (m_killOnDeactivate == true)
		{
			/*for (int i = 0; i < m_particleCount; i++)
			{
				m_particleList[i]->reset();
			}*/

			m_particleCount = 0;//need reset attribute as well
		}

		m_emitterLifeTime = 0.0f;
		m_elapsed = 0;
		m_loopCount = m_loopCount + 1;
		setCurrentBrust();
		if (m_durationRecal == true)
		{
			setCurrentDuration();
			resetParticlePool();
			m_particleList.resize(m_particleNum);
			m_shaderAttribute.resize(m_particleNum);
			return;
		}
	}

	//brust..... needs redo: to do add mutiple support(loop through points)
	if (m_useBrust && (m_elapsed > m_currentDuration * m_brustTiming + delay))
	{
		if (m_currentBrust != 0)
		{
			for (int i = 0; i < m_currentBrust; i++)
			{
				if (!isFull())
				{
					addParticle();
				}
			}
			m_currentBrust = 0;
		}
	}

	//update particles
	m_currentIndex = 0;

	if (m_moduleMap[EventReceiver] == true)
	{
		addParticleByEvent();
	}

	while (m_currentIndex < m_particleCount)
	{
		this->updateParticle(dt, m_particleList[m_currentIndex], m_currentIndex);
	}

	int index = 0;

	for (int i = 0; i < m_particleCount; i++)
	{
		vec3 pos = m_particleList[i]->getShaderAttriPos();

		m_shaderAttribute[i].data[index] = pos.x;
		m_shaderAttribute[i].data[index + 1] = pos.y;
		m_shaderAttribute[i].data[index + 2] = pos.z;
	}

	index += 3;//3

	if (m_attributeFormat["pinAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_pinCoord.x;
			m_shaderAttribute[i].data[index + 1] = m_pinCoord.y;
			m_shaderAttribute[i].data[index + 2] = m_pinCoord.z;
			m_shaderAttribute[i].data[index + 3] = m_pinCoord.w;
			m_shaderAttribute[i].data[index + 4] = m_pinAngle;
		}

		index += 5;//8
	}

	if (m_attributeFormat["sizeAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriSize();
		}

		index++;//9
	}

	if (m_attributeFormat["colorAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			vec3 color = m_particleList[i]->getShaderAttriColor();
			m_shaderAttribute[i].data[index] = color.x;
			m_shaderAttribute[i].data[index + 1] = color.y;
			m_shaderAttribute[i].data[index + 2] = color.z;
			m_shaderAttribute[i].data[index + 3] = m_particleList[i]->getShaderAttriAlpha();
		}
		index += 4;
	}

	if (m_attributeFormat["flipAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriFlipU();
			m_shaderAttribute[i].data[index + 1] = m_particleList[i]->getShaderAttriFlipV();
		}

		index += 2;
	}

	if (m_attributeFormat["rotationAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			m_shaderAttribute[i].data[index] = m_particleList[i]->getShaderAttriRot();
		}

		index++;
	}

	if (m_attributeFormat["subUVAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			vec4 coord = m_particleList[i]->getShaderAttriSubCoord();
			m_shaderAttribute[i].data[index] = coord.x;
			m_shaderAttribute[i].data[index + 1] = coord.y;
			m_shaderAttribute[i].data[index + 2] = coord.z;
			m_shaderAttribute[i].data[index + 3] = coord.w;

			/*std::cout << "subUVAttribute"
				<< m_shaderAttribute[i].data[index] <<   "[" << index << "]" << ","
				<< m_shaderAttribute[i].data[index + 1] << "[" << index+1 << "]" << ","
				<< m_shaderAttribute[i].data[index + 2] << "[" << index+2 << "]" << ","
				<< m_shaderAttribute[i].data[index + 3] << "[" << index+3 << "]" << ","
				<< std::endl;*/
		}

		index += 4;
	}

	if (m_attributeFormat["subUVBlendAttribute"] == true)
	{
		for (int i = 0; i < m_particleCount; i++)
		{
			vec4 coordNext = m_particleList[i]->getShaderAttriSubCoordNext();
			m_shaderAttribute[i].data[index] = coordNext.x;
			m_shaderAttribute[i].data[index + 1] = coordNext.y;
			m_shaderAttribute[i].data[index + 2] = coordNext.z;
			m_shaderAttribute[i].data[index + 3] = coordNext.w;
			m_shaderAttribute[i].data[index + 4] = m_particleList[i]->getShaderAttriSubRatio();
			/*std::cout << "insert blend attribute :"
				<< m_shaderAttribute[i].data[index] << "[" << index << "]" << ","
				<< m_shaderAttribute[i].data[index + 1] << "[" << index+1 << "]" << ","
				<< m_shaderAttribute[i].data[index + 2] << "[" << index+2 << "]" << ","
				<< m_shaderAttribute[i].data[index + 3] << "[" << index+3 << "]" << ","
				<< m_shaderAttribute[i].data[index + 4] << "[" << index+4 << "]" << ","
				<< std::endl; */
		}

		// index += 4;
	}

	//decide action when emitter finished
	if ((m_loop != 0) && ((m_elapsedDraw - delay * m_loop) > (m_currentDuration * m_loop)))
	{
		m_emitterRunningState = RUNNING_FRAME_STATE::FINISHED;
		//std::cout << "Emitter finish" << std::endl;

		//emitter finish state = true --> render thread put finish state --> lua do callback

		// on finish remove self from parent  should do in lua thread
		//if (m_killOnComplete)
		//{
		//     // should remove self from parent 	
		//}
	}
}

