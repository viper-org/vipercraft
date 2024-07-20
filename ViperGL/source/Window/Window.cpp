#include <ViperGL/Window/Window.h>

#include <glad/glad.h>

#include <stb_image.h>

#include <unordered_map>

namespace ViperGL
{
	Window::Window()
		: mWidth(0)
		, mHeight(0)
		, mTitle()
		, mWindowCtx(nullptr)
	{
	}

	Window::Window(unsigned int width, unsigned int height, std::string title, WindowErrorCode& errorCode)
		: mWidth(width)
		, mHeight(height)
		, mTitle(std::move(title))
		, mWindowCtx(nullptr)
	{
		mWindowCtx = glfwCreateWindow(mWidth, mHeight, mTitle.c_str(), nullptr, nullptr);
		if (!mWindowCtx)
		{
			glfwTerminate();
			errorCode = WindowErrorCode::GlfwCreateWindowFailed;
			return;
		}

		glfwMakeContextCurrent(mWindowCtx);
		mLastTime = glfwGetTime();

		stbi_set_flip_vertically_on_load(true);

		errorCode = WindowErrorCode::Success;
	}

	void Window::postInit()
	{
		int fWidth, fHeight;
		glfwGetFramebufferSize(mWindowCtx, &fWidth, &fHeight);
		glViewport(0, 0, fWidth, fHeight);
		glEnable(GL_DEPTH_TEST);
		glEnable(GL_CULL_FACE);
		glClearColor(1.f, 0.f, 1.f, 1.f);

		glfwSetMouseButtonCallback(mWindowCtx, mouseButtonCallback);
	}


	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(mWindowCtx);
	}

	void Window::clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::mainLoop()
	{
		glfwSwapBuffers(mWindowCtx);
		glfwPollEvents();
		glFlush();
	}

	std::unordered_map<int, std::vector<std::function<void()> > > mouseHandlers;
	void Window::onMouseButtonDown(int button, std::function<void()> func)
	{
		mouseHandlers[button].push_back(func);
	}

	double Window::getDeltaTime()
	{
		double currentTime = glfwGetTime();
		double lastTime = mLastTime;
		mLastTime = currentTime;
		return currentTime - lastTime;
	}


	unsigned int Window::getWidth() const
	{
		return mWidth;
	}

	unsigned int Window::getHeight() const
	{
		return mHeight;
	}

	std::string_view Window::getTitle() const
	{
		return mTitle;
	}

	GLFWwindow* Window::getWindowCtx() const
	{
		return mWindowCtx;
	}

	void Window::mouseButtonCallback(GLFWwindow*, int button, int action, int)
	{
		if (action == GLFW_PRESS)
		{
			for (auto& func : mouseHandlers[button])
			{
				func();
			}
		}
	}
}