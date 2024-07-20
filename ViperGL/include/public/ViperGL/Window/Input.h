#pragma once

#include <functional>

namespace ViperGL
{
	class Window;

	namespace Input
	{
		enum class KeyState
		{
			None,
			Pressed,
			Released,
			Repeated,
		};

		enum class Key
		{
			Escape, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
			Grave, One, Two, Three, Four, Five, Six, Seven, Eight, Nine, Zero, Minus, Equals, Backspace,
			Tab, Q, W, E, R, T, Y, U, I, O, P, LBracket, RBracket, Enter,
			CapsLock, A, S, D, F, G, H, J, K, L, Semicolon, Apostrophe, Hash,
			LShift, Backslash, Z, X, C, V, B, N, M, Comma, Dot, Slash, RShift,
			LCtrl, Win, LAlt, Space, RAlt, Menu, RCtrl,
			ArrowLeft, ArrowUp, ArrowRight, ArrowDown
		};

		enum class MouseAxis
		{
			AxisY,
			AxisX
		};

		enum class MouseButton
		{
			Left,
			Right,
		};

		KeyState GetKeyState(Window& window, Key key);

		void OnMouseButtonDown(Window& window, MouseButton button, std::function<void()> func);

		float GetMouseAxis(Window& window, MouseAxis axis);
		void SetCursorLocked(Window& window, bool locked);
	}
}