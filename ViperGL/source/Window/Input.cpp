#include <ViperGL/Window/Input.h>
#include <ViperGL/Window/Window.h>

#include <GLFW/glfw3.h>

namespace ViperGL
{
	namespace Input
	{
		static inline int GLFWKey(Key key)
		{
			using enum Key;
			switch (key)
			{
				case Escape:
					return GLFW_KEY_ESCAPE;
				case F1:
					return GLFW_KEY_F1;
				case F2:
					return GLFW_KEY_F2;
				case F3:
					return GLFW_KEY_F3;
				case F4:
					return GLFW_KEY_F4;
				case F5:
					return GLFW_KEY_F5;
				case F6:
					return GLFW_KEY_F6;
				case F7:
					return GLFW_KEY_F7;
				case F8:
					return GLFW_KEY_F8;
				case F9:
					return GLFW_KEY_F9;
				case F10:
					return GLFW_KEY_F10;
				case F11:
					return GLFW_KEY_F11;
				case F12:
					return GLFW_KEY_F12;
				case Grave:
					return GLFW_KEY_GRAVE_ACCENT;
				case One:
					return GLFW_KEY_1;
				case Two:
					return GLFW_KEY_2;
				case Three:
					return GLFW_KEY_3;
				case Four:
					return GLFW_KEY_4;
				case Five:
					return GLFW_KEY_5;
				case Six:
					return GLFW_KEY_6;
				case Seven:
					return GLFW_KEY_7;
				case Eight:
					return GLFW_KEY_8;
				case Nine:
					return GLFW_KEY_9;
				case Zero:
					return GLFW_KEY_0;
				case Minus:
					return GLFW_KEY_MINUS;
				case Equals:
					return GLFW_KEY_EQUAL;
				case Backspace:
					return GLFW_KEY_BACKSPACE;
				case Tab:
					return GLFW_KEY_TAB;
				case Q:
					return GLFW_KEY_Q;
				case W:
					return GLFW_KEY_W;
				case E:
					return GLFW_KEY_E;
				case R:
					return GLFW_KEY_R;
				case T:
					return GLFW_KEY_T;
				case Y:
					return GLFW_KEY_Y;
				case U:
					return GLFW_KEY_U;
				case I:
					return GLFW_KEY_I;
				case O:
					return GLFW_KEY_O;
				case P:
					return GLFW_KEY_P;
				case LBracket:
					return GLFW_KEY_LEFT_BRACKET;
				case RBracket:
					return GLFW_KEY_RIGHT_BRACKET;
				case Enter:
					return GLFW_KEY_ENTER;
				case CapsLock:
					return GLFW_KEY_CAPS_LOCK;
				case A:
					return GLFW_KEY_A;
				case S:
					return GLFW_KEY_S;
				case D:
					return GLFW_KEY_D;
				case F:
					return GLFW_KEY_F;
				case G:
					return GLFW_KEY_G;
				case H:
					return GLFW_KEY_H;
				case J:
					return GLFW_KEY_J;
				case K:
					return GLFW_KEY_K;
				case L:
					return GLFW_KEY_L;
				case Semicolon:
					return GLFW_KEY_SEMICOLON;
				case Apostrophe:
					return GLFW_KEY_APOSTROPHE;
				case Hash:
					return -1; // TODO: find this
				case LShift:
					return GLFW_KEY_LEFT_SHIFT;
				case Backslash:
					return GLFW_KEY_BACKSLASH;
				case Z:
					return GLFW_KEY_Z;
				case X:
					return GLFW_KEY_X;
				case C:
					return GLFW_KEY_C;
				case V:
					return GLFW_KEY_V;
				case B:
					return GLFW_KEY_B;
				case N:
					return GLFW_KEY_N;
				case M:
					return GLFW_KEY_M;
				case Comma:
					return GLFW_KEY_COMMA;
				case Dot:
					return GLFW_KEY_PERIOD;
				case Slash:
					return GLFW_KEY_SLASH;
				case RShift:
					return GLFW_KEY_RIGHT_SHIFT;
				case LCtrl:
					return GLFW_KEY_LEFT_CONTROL;
				case Win:
					return -1; // TODO: find this
				case LAlt:
					return GLFW_KEY_LEFT_ALT;
				case Space:
					return GLFW_KEY_SPACE;
				case RAlt:
					return GLFW_KEY_RIGHT_ALT;
				case Menu:
					return GLFW_KEY_MENU;
				case RCtrl:
					return GLFW_KEY_RIGHT_CONTROL;
				case ArrowLeft:
					return GLFW_KEY_LEFT;
				case ArrowUp:
					return GLFW_KEY_UP;
				case ArrowRight:
					return GLFW_KEY_RIGHT;
				case ArrowDown:
					return GLFW_KEY_DOWN;
			}
		}

		static inline int GLFWMouseButton(MouseButton button)
		{
			switch (button)
			{
				case MouseButton::Left:
					return GLFW_MOUSE_BUTTON_LEFT;
				case MouseButton::Right:
					return GLFW_MOUSE_BUTTON_RIGHT;
			}
		}

		static inline KeyState FromGLFWState(int state)
		{
			switch (state)
			{
				case GLFW_RELEASE:
					return KeyState::Released;
				case GLFW_PRESS:
					return KeyState::Pressed;
				case GLFW_REPEAT:
					return KeyState::Repeated;
				default:
					return KeyState::None;
			}
		}

		KeyState GetKeyState(Window& window, Key key)
		{
			GLFWwindow* windowCtx = window.getWindowCtx();
			int state = glfwGetKey(windowCtx, GLFWKey(key));
			return FromGLFWState(state);
		}

		void OnMouseButtonDown(Window& window, MouseButton button, std::function<void()> func)
		{
			window.onMouseButtonDown(GLFWMouseButton(button), func);
		}

		float GetMouseAxis(Window& window, MouseAxis axis)
		{
			constexpr float SENSITIVITY = 20.f;

			static double lastX = 0, lastY = 0;

			double currX, currY;
			GLFWwindow* windowCtx = window.getWindowCtx();
			glfwGetCursorPos(windowCtx, &currX, &currY);
			if (axis == MouseAxis::AxisY)
			{
				float ret = (lastY - currY) / SENSITIVITY;
				lastY = currY;
				return ret;
			}
			else if (axis == MouseAxis::AxisX)
			{
				float ret = (currX - lastX) / SENSITIVITY;
				lastX = currX;
				return ret;
			}
			return 0.f;
		}

		void SetCursorLocked(Window& window, bool locked)
		{
			GLFWwindow* windowCtx = window.getWindowCtx();
			glfwSetInputMode(windowCtx, GLFW_CURSOR, locked ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
		}
	}
}