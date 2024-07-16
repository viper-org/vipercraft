#include <ViperCraft/ViperCraft.h>

#include <Game/Block/Tile.h>

#include <Input/Input.h>

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
		mRenderQueue.init("atlas");

		Input::InitInputManager(&mWindow);
		Input::SetCursorLocked(true);

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

			processInput(deltaTime);

			mWindow.clear();
			render();

			postEvents(deltaTime);

			mWindow.mainLoop();
		}
	}

	static std::unique_ptr<ViperCraft> instance;
	void ViperCraft::CreateGame(ViperCraftErrorCode& errorCode)
	{
		if (instance); // TODO: Error
		instance = std::make_unique<ViperCraft>(errorCode);
		instance->initGame();
	}

	ViperCraft* ViperCraft::GetInstance()
	{
		return instance.get();
	}

	ViperGL::RenderQueue* ViperCraft::getRenderQueue()
	{
		return &mRenderQueue;
	}


	void ViperCraft::processInput(double deltaTime)
	{
		glm::vec3 move = glm::vec3(0.f);
		constexpr float MOVE_SPEED = 5.f;
		if (Input::GetButtonDown(Input::Key::A))
		{
			move -= mCamera.right * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::D))
		{
			move += mCamera.right * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::W))
		{
			move += mCamera.forward * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::S))
		{
			move -= mCamera.forward * (float)(MOVE_SPEED * deltaTime);
		}
		mCamera.position += move;

		mCamera.yaw += Input::GetInputAxis(Input::InputAxis::AxisX);
		mCamera.pitch += Input::GetInputAxis(Input::InputAxis::AxisY);

		mCamera.pitch = glm::clamp(mCamera.pitch, -89.9f, 89.9f);
	}

	void ViperCraft::render()
	{
		mWorld.render();
	}

	void ViperCraft::postEvents(double deltaTime)
	{
	}


	void ViperCraft::initGame()
	{
		World::Generate(mWorld);
	}
}