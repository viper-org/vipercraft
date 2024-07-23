#pragma once

#include <Game/Gui/Gui.h>

#include <Input/Input.h>

namespace ViperCraft 
{
	class GuiScreen : public Gui
	{
	public:
		virtual void init();

		virtual void drawScreen(int mouseX, int mouseY);

	protected:
		virtual void keyTyped(char typedChar, Input::Key keycode);

		virtual void mouseClicked(int mouseX, int mouseY, Input::MouseButton button);
	};
}