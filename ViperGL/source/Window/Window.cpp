#include <ViperGL/Window/Window.h>

#include <ViperGL/Window/Input.h>

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
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glClearColor(0.53f, 0.81f, 0.92f, 1.f);

		glfwSetKeyCallback(mWindowCtx, keyCallback);
		glfwSetMouseButtonCallback(mWindowCtx, mouseButtonCallback);
		glfwSetFramebufferSizeCallback(mWindowCtx, framebufferSizeCallback);
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

	std::vector<std::function<void(Input::Key)> > keyHandlers;
	void Window::onKeyDown(std::function<void(Input::Key)> func)
	{
		keyHandlers.push_back(func);
	}

	std::vector<std::function<void(Input::MouseButton, bool)> > mouseButtonHandlers;
	void Window::onMouseButton(std::function<void(Input::MouseButton, bool)> func) 
	{
		mouseButtonHandlers.push_back(func);
	}

	std::unordered_map<int, std::vector<std::function<void()> > > mouseDownHandlers;
	void Window::onMouseButtonDown(int button, std::function<void()> func)
	{
		mouseDownHandlers[button].push_back(func);
	}

	std::unordered_map<int, std::vector<std::function<void()> > > mouseUpHandlers;
	void Window::onMouseButtonUp(int button, std::function<void()> func)
	{
		mouseUpHandlers[button].push_back(func);
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

	float Window::getAspectRatio() const
	{
		return (float)mWidth / (float)mHeight;
	}

	std::string_view Window::getTitle() const
	{
		return mTitle;
	}

	GLFWwindow* Window::getWindowCtx() const
	{
		return mWindowCtx;
	}

	void Window::keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		if (action == GLFW_PRESS)
		{
			for (auto& func : keyHandlers)
			{
				func(Input::KeyFromGLFW(key));
			}
		}
	}

	void Window::mouseButtonCallback(GLFWwindow*, int button, int action, int)
	{
		if (action == GLFW_PRESS)
		{
			for (auto& func : mouseDownHandlers[button])
			{
				func();
			}
		}
		else if (action == GLFW_RELEASE)
		{
			for (auto& func : mouseUpHandlers[button])
			{
				func();
			}
		}

		for (auto& func : mouseButtonHandlers)
		{
			func(Input::MouseButtonFromGLFW(button), action == GLFW_PRESS);
		}
	}

	void Window::framebufferSizeCallback(GLFWwindow*, int width, int height)
	{
		glViewport(0, 0, width, height);
	}
}