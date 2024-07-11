#include <ViperGL/Window/Window.h>

#include <Shader/Shader.h>
#include <Vertex/VertexObject.h>
#include <Vertex/ElementBuffer.h>

#include <glad/glad.h>

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

		errorCode = WindowErrorCode::Success;
	}

	void Window::postInit()
	{
		int fWidth, fHeight;
		glfwGetFramebufferSize(mWindowCtx, &fWidth, &fHeight);
		glViewport(0, 0, fWidth, fHeight);
		glEnable(GL_DEPTH_TEST);
	}


	bool Window::shouldClose() const
	{
		return glfwWindowShouldClose(mWindowCtx);
	}

	void Window::clear()
	{
		glClearColor(1.f, 0.f, 1.f, 1.f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void Window::mainLoop()
	{
		// this is really bad but its temporary
		ShaderErrorCode ec;
		ShaderProgram shader("test", ec);
		shader.use();
		VertexObject v({
			 0.5f,  0.5f, 0.0f,  // top right
			 0.5f, -0.5f, 0.0f,  // bottom right
			-0.5f, -0.5f, 0.0f,  // bottom left
			-0.5f,  0.5f, 0.0f   // top left  
		});
		ElementBuffer e({
			0, 1, 3,
			1, 2, 3
			});
		v.bind();
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

		glfwSwapBuffers(mWindowCtx);
		glfwPollEvents();
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
}