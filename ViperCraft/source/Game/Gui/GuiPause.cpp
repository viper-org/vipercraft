#include <Game/Gui/GuiPause.h>

#include <iostream>

namespace ViperCraft
{
	void GuiPause::init()
	{
		std::cout << "Pause GUI initialized\n";
	}

	void GuiPause::drawScreen(int mouseX, int mouseY)
	{
		drawRect(-0.05f, 0.05f, 0.05f, -0.05f, ViperGL::Colors::Black);
	}
}