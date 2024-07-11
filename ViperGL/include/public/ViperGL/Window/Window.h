#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <string>

namespace ViperGL
{
	enum WindowErrorCode
	{
		Success=0,
		GlfwCreateWindowFailed
	};

	class Window
	{
	public:
		Window();
		Window(unsigned int width, unsigned int height, std::string title, WindowErrorCode& errorCode);

		void postInit();

		bool shouldClose() const;
		void mainLoop();

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		std::string_view getTitle() const;
		GLFWwindow* getWindowCtx() const;

	private:
		unsigned int mWidth;
		unsigned int mHeight;

		std::string mTitle;

		GLFWwindow* mWindowCtx;
	};
}