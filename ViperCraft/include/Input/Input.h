#pragma once

#include <ViperGL/Window/Window.h>
#include <ViperGL/Window/Input.h>

#include <functional>

namespace ViperCraft
{
	namespace Input
	{
		using Key = ViperGL::Input::Key;
		using InputAxis = ViperGL::Input::MouseAxis;
		using MouseButton = ViperGL::Input::MouseButton;

		void InitInputManager(ViperGL::Window* window);

		bool GetButtonDown(Key key);
		
		void OnKeyDown(std::function<void(Key)> func);
		void OnMouseButtonDown(MouseButton button, std::function<void()> func);
		void OnMouseButtonUp(MouseButton button, std::function<void()> func);

		float GetInputAxis(InputAxis axis);
		void SetCursorLocked(bool locked);
	}
}