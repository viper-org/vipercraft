#pragma once

#include <ViperGL/Render/RenderQueue.h>

namespace ViperCraft 
{
	class Gui 
	{
	public:
		void drawHorizontalLine(int startX, int endX, int y, ViperGL::Color color);

		void drawVerticalLine(int startY, int endY, int x, ViperGL::Color color);

		void drawRect(int left, int top, int right, int bottom, ViperGL::Color color);

	protected:
		ViperGL::UIRenderQueue mUIRenderQueue;
	};
}