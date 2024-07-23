#include <Game/Gui/Gui.h>

namespace ViperCraft 
{
	void Gui::drawHorizontalLine(int startX, int endX, int y, ViperGL::Color color) 
	{
		if (endX < startX) 
		{
			int i = startX;
			startX = endX;
			endX = i;
		}

		mUIRenderQueue.line(glm::vec2(startX, y), glm::vec2(endX, y), color);
	}

	void Gui::drawVerticalLine(int startY, int endY, int x, ViperGL::Color color) 
	{
		if (endY < startY) 
		{
			int i = startY;
			startY = endY;
			endY = i;
		}

		mUIRenderQueue.line(glm::vec2(x, startY), glm::vec2(x, endY), color);
	}

	void Gui::drawRect(int left, int top, int right, int bottom, ViperGL::Color color) 
	{
		
	}
}