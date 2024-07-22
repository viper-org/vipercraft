#include <ViperCraft/ViperCraft.h>

#include <Game/Block/Tile.h>

#include <Input/Input.h>

#include <glad/glad.h>

namespace ViperCraft
{
	ViperCraft::ViperCraft(ViperCraftErrorCode& errorCode)
		: mRenderQueue(mPlayer.getPlayerController().getCamera())
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

	void ViperCraft::setPlayerSpawn(glm::vec3 position)
	{
		mPlayer.mPosition = position;
	}

	void ViperCraft::run()
	{
		while (!mWindow.shouldClose())
		{
			double deltaTime = mWindow.getDeltaTime();

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

	void ViperCraft::onTick(std::function<void(double)> handler)
	{
		mOnTickHandlers.push_back(std::move(handler));
	}

	World* ViperCraft::getWorld()
	{
		return &mWorld;
	}

	Player* ViperCraft::getPlayer()
	{
		return &mPlayer;
	}

	ViperGL::RenderQueue* ViperCraft::getRenderQueue()
	{
		return &mRenderQueue;
	}


	void ViperCraft::render()
	{
		mWorld.render();
	}

	void ViperCraft::postEvents(double deltaTime)
	{
		for (auto& handler : mOnTickHandlers)
		{
			handler(deltaTime);
		}
	}


	void ViperCraft::initGame()
	{
		World::Generate(mWorld, (unsigned long long)rand() * rand());
		mPlayer.init();
	}
}