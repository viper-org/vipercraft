#include <Game/Gui/UIManager.h>

#include <Game/Gui/GuiScreen.h>
#include <Game/Gui/GuiPause.h>

namespace ViperCraft
{
	UIManager::UIManager()
		: mGameInFocus(true)
	{
	}

	void UIManager::init()
	{
		setGameInFocus(true);
		Input::OnKeyDown(std::bind(&UIManager::keyDownHandler, this, std::placeholders::_1));
		Input::OnMouseButton(std::bind(&UIManager::mouseButtonHandler, this, std::placeholders::_1, std::placeholders::_2));
	}

	void UIManager::draw()
	{
		ViperGL::UI::PreDraw();
		if (mActiveScreen != nullptr)
		{
			mActiveScreen->drawScreen(1337, 42069); //TODO: GET MOUSE X AND MOUSE Y VERY IMPORTANT
		}
		else
		{
			ViperGL::UI::DrawLine(glm::vec2(-0.03f, 0.f), glm::vec2(0.03f, 0.f), ViperGL::Colors::White);
			ViperGL::UI::DrawLine(glm::vec2(0.f, -0.03f), glm::vec2(0.f, 0.03f), ViperGL::Colors::White);
		}
	}

	void UIManager::update()
	{
		if (mActiveScreen)
			mActiveScreen->updateScreen();
	}

	void UIManager::displayScreen(std::unique_ptr<GuiScreen> newScreen)
	{
		if (mActiveScreen)
		{
			mActiveScreen->onGuiClosed();
		}

		mActiveScreen = std::move(newScreen);

		if (mActiveScreen)
		{
			setGameInFocus(false);
			mActiveScreen->setResolution(1920, 1080); // TODO: Get this properly
		}
		else
		{
			setGameInFocus(true);
		}
	}

	bool UIManager::isGameInFocus() const
	{
		return mGameInFocus;
	}

	void UIManager::setGameInFocus(bool focus)
	{
		mGameInFocus = focus;
		Input::SetCursorLocked(focus);
	}


	void UIManager::keyDownHandler(Input::Key key)
	{
		if (!mActiveScreen)
		{
			if (key == Input::Key::Escape) displayScreen(std::make_unique<GuiPause>());
			return;
		}

		mActiveScreen->handleKeyboardInput(key);
	}

	void UIManager::mouseButtonHandler(Input::MouseButton btn, bool state)
	{
		if (mActiveScreen)
			mActiveScreen->handleMouseInput(1337, 69420, btn, state); //TODO: GET MOUSE X AND MOUSE Y VERY IMPORTANT
	}
}