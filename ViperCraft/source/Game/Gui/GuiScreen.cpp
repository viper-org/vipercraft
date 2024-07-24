#include <Game/Gui/GuiScreen.h>

#include <ViperCraft/ViperCraft.h>

namespace ViperCraft 
{
	void GuiScreen::init() 
	{
	}

	void GuiScreen::drawScreen(int mouseX, int mouseY) 
	{	
	}

	void GuiScreen::updateScreen() 
	{
		std::ignore = Input::GetInputAxis(Input::InputAxis::AxisX);
		std::ignore = Input::GetInputAxis(Input::InputAxis::AxisY);
	}

	void GuiScreen::onGuiClosed() 
	{
	}

	bool GuiScreen::doesGuiPauseGame() 
	{
		return true;
	}

	int GuiScreen::getWidth() const {
		return mWidth;
	}

	int GuiScreen::getHeight() const {
		return mHeight;
	}

	void GuiScreen::setResolution(int width, int height) {
		mWidth = width;
		mHeight = height;

		init();
	}

	void GuiScreen::handleKeyboardInput(Input::Key keycode) 
	{
		keyTyped('a', keycode);
	}

	void GuiScreen::handleMouseInput(int mouseX, int mouseY, Input::MouseButton button, bool state)
	{
		if (state)
		{
			mouseClicked(mouseX, mouseY, button);
		}
		else //TODO: STUFF FOR MOUSEMOVE 
		{
			mouseReleased(mouseX, mouseY, button);
		}
	}

	void GuiScreen::keyTyped(char typedChar, Input::Key keycode) 
	{
		if (keycode == Input::Key::Escape)
		{
			// exit the screen
			ViperCraft::GetInstance()->getUIManager()->displayScreen(nullptr);
		}
	}

	void GuiScreen::mouseClicked(int mouseX, int mouseY, Input::MouseButton button) 
	{

	}

	void GuiScreen::mouseReleased(int mouseX, int mouseY, Input::MouseButton button)
	{
	
	}

	void GuiScreen::mouseClickMove(int mouseX, int mouseY, Input::MouseButton button)
	{
	
	}
}