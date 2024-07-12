#pragma once

#include <ViperGL/Window/Window.h>

#include <ViperGL/Window/Input.h>

namespace ViperCraft
{
	namespace Input
	{
		using Key = ViperGL::Input::Key;
		using InputAxis = ViperGL::Input::MouseAxis;

		void InitInputManager(ViperGL::Window* window);

		bool GetButtonDown(Key key);

		float GetInputAxis(InputAxis axis);
		void SetCursorLocked(bool locked);
	}
}