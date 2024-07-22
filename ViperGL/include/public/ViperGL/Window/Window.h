#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <functional>
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
		void clear();
		void mainLoop();

		void onMouseButtonDown(int button, std::function<void()> func);

		double getDeltaTime();

		unsigned int getWidth() const;
		unsigned int getHeight() const;
		float getAspectRatio() const;
		std::string_view getTitle() const;
		GLFWwindow* getWindowCtx() const;

	private:
		unsigned int mWidth;
		unsigned int mHeight;

		std::string mTitle;

		GLFWwindow* mWindowCtx;

		double mLastTime; // for deltatime calculation

		static void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
		static void framebufferSizeCallback(GLFWwindow* window, int width, int height);
	};
}