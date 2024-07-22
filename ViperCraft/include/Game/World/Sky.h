#pragma once

#include <glm/vec2.hpp>

namespace ViperCraft
{
	class Sky
	{
	public:
		Sky();

		void addClouds(unsigned long long seed, glm::vec2 worldSize);

		void draw();

	private:
		int mRenderBuffer;
	};
}