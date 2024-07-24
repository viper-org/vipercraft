#include <Game/Gui/Gui.h>

namespace ViperCraft 
{
	void Gui::drawHorizontalLine(float startX, float endX, float y, ViperGL::Color color) 
	{
		ViperGL::UI::DrawLine(glm::vec2(startX, y), glm::vec2(endX, y), color);
	}

	void Gui::drawVerticalLine(float startY, float endY, float x, ViperGL::Color color) 
	{
		ViperGL::UI::DrawLine(glm::vec2(x, startY), glm::vec2(x, endY), color);
	}

	void Gui::drawRect(float left, float top, float right, float bottom, ViperGL::Color color) 
	{
		ViperGL::UI::DrawQuad(glm::vec2(left, bottom), glm::vec2(left, top), glm::vec2(right, bottom), glm::vec2(right, top), color);
	}
}