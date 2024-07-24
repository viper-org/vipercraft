#include <Game/World/Sky.h>

#include <ViperCraft/ViperCraft.h>

#include <stb_perlin/stb_perlin.h>

#include <iostream>

namespace ViperCraft
{
	Sky::Sky()
		: mRenderBuffer(0)
	{
	}

	void Sky::addClouds(unsigned long long seed, glm::vec2 worldSize)
	{
		auto renderQueue = ViperCraft::GetInstance()->getRenderQueue();
		mRenderBuffer = renderQueue->newBuffer();
		renderQueue->resetModels(mRenderBuffer);

		for (float x = 0; x < worldSize.x; ++x)
		{
			for (float z = 0; z < worldSize.y; ++z)
			{
				auto noise = (
					stb_perlin_noise3_seed(x / 16, z / 16, .2f, 0, 0, 0, seed)
					);
				if (noise > .3f)
				{
					std::array<glm::vec3, 4> corners = {
						glm::vec3(x, 100, z),
						glm::vec3(x+1, 100, z),
						glm::vec3(x+1, 100, z+1),
						glm::vec3(x, 100, z+1),
					};
					renderQueue->quad(mRenderBuffer, corners, glm::vec2(3, 2), 0.9f, 0.8f);
				}
			}
		}
		renderQueue->bindModels(mRenderBuffer);
	}

	void Sky::draw()
	{
		ViperCraft::GetInstance()->getRenderQueue()->draw(mRenderBuffer);
	}
}