#pragma once

#include <ViperGL/Render/RenderQueue.h>
#include <ViperGL/Render/UI.h>

namespace ViperCraft 
{
	class Gui 
	{
	public:
		void drawHorizontalLine(float startX, float endX, float y, ViperGL::Color color);

		void drawVerticalLine(float startY, float endY, float x, ViperGL::Color color);

		void drawRect(float left, float top, float right, float bottom, ViperGL::Color color);
	};
}