#pragma once

#include <glm/vec2.hpp>
#include <glm/vec4.hpp>

namespace ViperGL
{
	namespace UI
	{
		using Color = glm::vec4;

		void InitUIRenderer(float aspectRatio);

		void PreDraw();
		void DrawLine(glm::vec2 from, glm::vec2 to, Color color);
	}
}