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

		virtual void updateScreen();

		virtual void onGuiClosed();

		virtual bool doesGuiPauseGame();

		int getWidth() const;
		int getHeight() const;

		void setResolution(int width, int height);

		void handleKeyboardInput(Input::Key keycode);
		void handleMouseInput(int mouseX, int mouseY, Input::MouseButton button, bool state);

	protected:
		int mWidth;
		int mHeight;

		virtual void keyTyped(char typedChar, Input::Key keycode);

		virtual void mouseClicked(int mouseX, int mouseY, Input::MouseButton button);

		virtual void mouseReleased(int mouseX, int mouseY, Input::MouseButton button);

		virtual void mouseClickMove(int mouseX, int mouseY, Input::MouseButton button);
	};
}