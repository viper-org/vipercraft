#include <ViperCraft/ViperCraft.h>

#include <Game/Block/Tile.h>

#include <Input/Input.h>

#include <glad/glad.h>

namespace ViperCraft
{
	constexpr int CHUNK_COUNT = 4;

	ViperCraft::ViperCraft(ViperCraftErrorCode& errorCode)
		: mRenderQueue(mCamera)
		, mChunks(std::make_unique<Chunk[]>(CHUNK_COUNT))
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

		Input::InitInputManager(&mWindow);
		Input::SetCursorLocked(true);

		Tile::BuildRenderables(mRenderQueue);
		glm::vec3 chunkPos = glm::vec3(0.f);
		for (int i = 0; i < CHUNK_COUNT; ++i)
		{
			mChunks[i].mPosition = chunkPos;
			chunkPos.x += 16;
		}
		for (int i = 0; i < 16; ++i)
		{
			for (int j = 0; j < 16; ++j)
			{
				mChunks[0].getTile(glm::vec3(i, 0, j)) = Tile::GetTile("cobblestone");
			}
		}

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


	void ViperCraft::processInput(double deltaTime)
	{
		glm::vec3 move = glm::vec3(0.f);
		constexpr float MOVE_SPEED = 2.5f;
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
		mRenderQueue.prepareDraw();
		for (int i = 0; i < CHUNK_COUNT; ++i)
		{
			mChunks[i].drawAll(mRenderQueue);
		}
	}

	void ViperCraft::postEvents(double deltaTime)
	{
	}
}