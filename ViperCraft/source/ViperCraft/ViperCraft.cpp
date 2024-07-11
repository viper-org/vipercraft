#include <ViperCraft/ViperCraft.h>

#include <glad/glad.h>

namespace ViperCraft
{
	ViperCraft::ViperCraft(ViperCraftErrorCode& errorCode)
		: mRenderQueue(mCamera)
	{
		if (!glfwInit()) // maybe move this to something like ViperGL::StaticInit
		{
			errorCode = ViperCraftErrorCode::GlfwInitFailed;
			return;
		}

		ViperGL::WindowErrorCode windowErrorCode;
		mWindow = ViperGL::Window(1920, 1080, "Viper Craft 0.0.1", windowErrorCode);
		if (windowErrorCode != ViperGL::WindowErrorCode::Success)
		{
			errorCode = ViperCraftErrorCode::WindowFailed;
			return;
		}

		if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) // this should probably be moved as well
		{
			errorCode = ViperCraftErrorCode::GladInitFailed;
			return;
		}
		mWindow.postInit(); // stuff that requires glad to be loaded
		mRenderQueue.init();

		mRenderQueue.push(ViperGL::Rect(0.f, 0.f, 0.25f, 0.25f));
		mRenderQueue.push(ViperGL::Rect(-0.25f, -0.25f, 0.f, 0.f));

		errorCode = ViperCraftErrorCode::Success;
	}

	ViperCraft::~ViperCraft()
	{
		glfwTerminate();
	}

	void ViperCraft::run()
	{
		while (!mWindow.shouldClose())
		{
			double deltaTime = mWindow.getDeltaTime();
			mCamera.yaw += 5 * deltaTime;
			mCamera.pitch += 5 * deltaTime;

			processInput();

			mWindow.clear();
			render();

			postEvents();

			mWindow.mainLoop();
		}
	}


	void ViperCraft::processInput()
	{
	}

	void ViperCraft::render()
	{
		mRenderQueue.draw();
	}

	void ViperCraft::postEvents()
	{
	}
}