#pragma once

#include <Input/Input.h>

#include <memory>

namespace ViperCraft
{
	class GuiScreen;

	class UIManager
	{
	public:
		UIManager();

		void init();
		void draw();
		void update();

		void displayScreen(std::unique_ptr<GuiScreen> newScreen);

		bool isGameInFocus() const;
		void setGameInFocus(bool focus);

	private:
		std::unique_ptr<GuiScreen> mActiveScreen;

		bool mGameInFocus;

		void keyDownHandler(Input::Key key);
		void mouseButtonHandler(Input::MouseButton btn, bool state);
	};
}