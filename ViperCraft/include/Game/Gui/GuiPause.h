#pragma once

#include <Game/Gui/GuiScreen.h>

namespace ViperCraft 
{
	class GuiPause : public GuiScreen
	{
	public:
		virtual void init() override;

		virtual void drawScreen(int mouseX, int mouseY) override;
	};
}