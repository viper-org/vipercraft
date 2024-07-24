﻿#include <ViperCraft/ViperCraft.h>

#include <Game/Block/Tile.h>

#include <Game/Gui/GuiPause.h>

#include <Input/Input.h>

#include <ViperGL/Render/UI.h>

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
		mWindow = ViperGL::Window(1920, 1080, "Viper Craft 0.0.2", windowErrorCode);
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
		ViperGL::UI::InitUIRenderer(mWindow.getAspectRatio());

		Input::InitInputManager(&mWindow);

		mUIManager.init();

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

			mUIManager.update();

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

	UIManager* ViperCraft::getUIManager()
	{
		return &mUIManager;
	}

	ViperGL::RenderQueue* ViperCraft::getRenderQueue()
	{
		return &mRenderQueue;
	}

	bool ViperCraft::isGameInFocus() const
	{
		return mUIManager.isGameInFocus();
	}

	void ViperCraft::render()
	{
		mWorld.render();

		mUIManager.draw();
	}

	void ViperCraft::postEvents(double deltaTime)
	{
		// in case of very long frames, limit the deltatime
		if (deltaTime >= 0.04) deltaTime = 0.04;
		for (auto& handler : mOnTickHandlers)
		{
			handler(deltaTime);
		}
	}


	void ViperCraft::initGame()
	{
		srand(time(NULL)); // randomly generate a seed for now
		World::Generate(mWorld, (unsigned long long)rand() * rand());
		mPlayer.init();
	}
}