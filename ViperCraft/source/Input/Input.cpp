#include <Input/Input.h>

namespace ViperCraft
{
	namespace Input
	{
		static ViperGL::Window* gameWindow = nullptr;

		static void MouseButtonCallback()
		{

		}

		void InitInputManager(ViperGL::Window* window)
		{ // maybe assert that gameWindow is nullptr here
			gameWindow = window;
		}

		bool GetButtonDown(Key key)
		{ // assert that gameWindow is initialized here
			return ViperGL::Input::GetKeyState(*gameWindow, key) == ViperGL::Input::KeyState::Pressed;
		}

		void OnKeyDown(std::function<void(Key)> func)
		{
			ViperGL::Input::OnKeyDown(*gameWindow, func);
		}

		void OnMouseButton(std::function<void(MouseButton, bool)> func) 
		{
			ViperGL::Input::OnMouseButton(*gameWindow, func);
		}
		
		void OnMouseButtonDown(MouseButton button, std::function<void()> func)
		{
			ViperGL::Input::OnMouseButtonDown(*gameWindow, button, func);
		}

		void OnMouseButtonUp(MouseButton button, std::function<void()> func)
		{
			ViperGL::Input::OnMouseButtonUp(*gameWindow, button, func);
		}

		void GetMousePosition(float* x, float* y)
		{ // assert that gameWindow is initialized here
			ViperGL::Input::GetMousePosition(*gameWindow, x, y);
		}

		float GetInputAxis(InputAxis axis)
		{ // assert that gameWindow is initialized here
			return ViperGL::Input::GetMouseAxis(*gameWindow, axis);
		}

		void SetCursorLocked(bool locked)
		{ // assert that gameWindow is initialized here
			ViperGL::Input::SetCursorLocked(*gameWindow, locked);
		}
	}
}