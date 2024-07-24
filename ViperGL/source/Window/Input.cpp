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

		Key KeyFromGLFW(int k)
		{
			using enum Key;
			switch (k)
			{
				case GLFW_KEY_ESCAPE:
					return Escape;
				case GLFW_KEY_F1:
					return F1;
				case GLFW_KEY_F2:
						return F2;
				case GLFW_KEY_F3:
					return F3;
				case GLFW_KEY_F4:
					return F4;
				case GLFW_KEY_F5:
					return F5;
				case GLFW_KEY_F6:
					return F6;
				case GLFW_KEY_F7:
					return F7;
				case GLFW_KEY_F8:
					return F8;
				case GLFW_KEY_F9:
					return F9;
				case GLFW_KEY_F10:
					return F10;
				case GLFW_KEY_F11:
					return F11;
				case GLFW_KEY_F12:
					return F12;
				case GLFW_KEY_GRAVE_ACCENT:
					return Grave;
				case GLFW_KEY_1:
					return One;
				case GLFW_KEY_2:
					return Two;
				case GLFW_KEY_3:
					return Three;
				case GLFW_KEY_4:
					return Four;
				case GLFW_KEY_5:
					return Five;
				case GLFW_KEY_6:
					return Six;
				case GLFW_KEY_7:
					return Seven;
				case GLFW_KEY_8:
					return Eight;
				case GLFW_KEY_9:
					return Nine;
				case GLFW_KEY_0:
					return Zero;
				case GLFW_KEY_MINUS:
					return Minus;
				case GLFW_KEY_EQUAL:
					return Equals;
				case GLFW_KEY_BACKSPACE:
					return Backspace;
				case GLFW_KEY_TAB:
					return Tab;
				case GLFW_KEY_Q:
					return Q;
				case GLFW_KEY_W:
					return W;
				case GLFW_KEY_E:
					return E;
				case GLFW_KEY_R:
					return R;
				case GLFW_KEY_T:
					return T;
				case GLFW_KEY_Y:
					return Y;
				case GLFW_KEY_U:
					return U;
				case GLFW_KEY_I:
					return I;
				case GLFW_KEY_O:
					return O;
				case GLFW_KEY_P:
					return P;
				case GLFW_KEY_LEFT_BRACKET:
					return LBracket;
				case GLFW_KEY_RIGHT_BRACKET:
					return RBracket;
				case GLFW_KEY_ENTER:
					return Enter;
				case GLFW_KEY_CAPS_LOCK:
					return CapsLock;
				case GLFW_KEY_A:
					return A;
				case GLFW_KEY_S:
					return S;
				case GLFW_KEY_D:
					return D;
				case GLFW_KEY_F:
					return F;
				case GLFW_KEY_G:
					return G;
				case GLFW_KEY_H:
					return H;
				case GLFW_KEY_J:
					return J;
				case GLFW_KEY_K:
					return K;
				case GLFW_KEY_L:
					return L;
				case GLFW_KEY_SEMICOLON:
					return Semicolon;
				case GLFW_KEY_APOSTROPHE:
					return Apostrophe;
				case GLFW_KEY_LEFT_SHIFT:
					return LShift;
				case GLFW_KEY_BACKSLASH:
					return Backslash;
				case GLFW_KEY_Z:
					return Z;
				case GLFW_KEY_X:
					return X;
				case GLFW_KEY_C:
					return C;
				case GLFW_KEY_V:
					return V;
				case GLFW_KEY_B:
					return B;
				case GLFW_KEY_N:
					return N;
				case GLFW_KEY_M:
					return M;
				case GLFW_KEY_COMMA:
					return Comma;
				case GLFW_KEY_PERIOD:
					return Dot;
				case GLFW_KEY_SLASH:
					return Slash;
				case GLFW_KEY_RIGHT_SHIFT:
					return RShift;
				case GLFW_KEY_LEFT_CONTROL:
					return LCtrl;
				case GLFW_KEY_LEFT_ALT:
					return LAlt;
				case GLFW_KEY_SPACE:
					return Space;
				case GLFW_KEY_RIGHT_ALT:
					return RAlt;
				case GLFW_KEY_MENU:
					return Menu;
				case GLFW_KEY_RIGHT_CONTROL:
					return RCtrl;
				case GLFW_KEY_LEFT:
					return ArrowLeft;
				case GLFW_KEY_UP:
					return ArrowUp;
				case GLFW_KEY_RIGHT:
					return ArrowRight;
				case GLFW_KEY_DOWN:
					return ArrowDown;
			}
		}

		MouseButton MouseButtonFromGLFW(int button) 
		{
			using enum MouseButton;

			switch (button)
			{
				case GLFW_MOUSE_BUTTON_LEFT:
					return Left;
				case GLFW_MOUSE_BUTTON_RIGHT:
					return Right;
			}
		}

		KeyState GetKeyState(Window& window, Key key)
		{
			GLFWwindow* windowCtx = window.getWindowCtx();
			int state = glfwGetKey(windowCtx, GLFWKey(key));
			return FromGLFWState(state);
		}

		void OnKeyDown(Window& window, std::function<void(Key)> func)
		{
			window.onKeyDown(func);
		}

		void OnMouseButton(Window& window, std::function<void(MouseButton, bool)> func) 
		{
			window.onMouseButton(func);
		}

		void OnMouseButtonDown(Window& window, MouseButton button, std::function<void()> func)
		{
			window.onMouseButtonDown(GLFWMouseButton(button), func);
		}

		void OnMouseButtonUp(Window& window, MouseButton button, std::function<void()> func)
		{
			window.onMouseButtonUp(GLFWMouseButton(button), func);
		}

		void GetMousePosition(Window& window, float* x, float* y)
		{
			double currX, currY;
			GLFWwindow* windowCtx = window.getWindowCtx();
			glfwGetCursorPos(windowCtx, &currX, &currY);

			*x = currX;
			*y = currY;
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