#include <ViperCraft/ViperCraft.h>

#include <Game/Block/Tile.h>

#include <Game/Gui/GuiPause.h>

#include <Input/Input.h>

#include <ViperGL/Render/UI.h>

#include <glad/glad.h>

namespace ViperCraft
{
	ViperCraft::ViperCraft(ViperCraftErrorCode& errorCode)
		: mRenderQueue(mPlayer.getPlayerController().getCamera())
		, mGameHasFocus(false)
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

		Input::OnKeyDown(std::bind(&ViperCraft::processKeyDownForGui, this, std::placeholders::_1));
		Input::OnMouseButton(std::bind(&ViperCraft::processMouseButtonForGui, this, std::placeholders::_1, std::placeholders::_2));

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

			if (mCurrentScreen != nullptr)
			{
				mCurrentScreen->updateScreen();
			}
			else
			{
				setGameInFocus();
			}

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

	void ViperCraft::displayGuiScreen(std::unique_ptr<GuiScreen> newGuiScreen) 
	{
		if (mCurrentScreen != nullptr) 
		{
			mCurrentScreen->onGuiClosed();
		}

		mCurrentScreen = std::move(newGuiScreen);

		if (mCurrentScreen != nullptr) 
		{
			setGameNotInFocus();
			mCurrentScreen->setResolution(1920, 1080); //TODO: some other display size stuff
		}
		else 			
		{
			setGameInFocus();
		}
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

	bool ViperCraft::isGameInFocus() 
	{
		return mGameHasFocus;
	}

	void ViperCraft::setGameInFocus() 
	{
		if (!mGameHasFocus) 
		{
			mGameHasFocus = true;
			Input::SetCursorLocked(true);
			displayGuiScreen(nullptr);
		}
	}

	void ViperCraft::setGameNotInFocus() 
	{
		if (mGameHasFocus)
		{
			mGameHasFocus = false;
			Input::SetCursorLocked(false);
		}
	}

	void ViperCraft::render()
	{
		mWorld.render();

		// TODO: Move this
		ViperGL::UI::PreDraw();

		if (mCurrentScreen != nullptr)
		{
			mCurrentScreen->drawScreen(1337, 42069); //TODO: GET MOUSE X AND MOUSE Y VERY IMPORTANT
		}
		else
		{
			ViperGL::UI::DrawLine(glm::vec2(-0.03f, 0.f), glm::vec2(0.03f, 0.f), ViperGL::Colors::White);
			ViperGL::UI::DrawLine(glm::vec2(0.f, -0.03f), glm::vec2(0.f, 0.03f), ViperGL::Colors::White);
			//ViperGL::UI::DrawQuad({ -0.5f, -.5f }, { -.5f, -.4f }, { -.4f, -.5f }, { -.4f, -.4f }, ViperGL::Colors::Black);
		}
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

	void ViperCraft::processKeyDownForGui(Input::Key key)
	{
		if (mCurrentScreen == nullptr) 
		{
			if (key == Input::Key::Escape) displayGuiScreen(std::make_unique<GuiPause>());
			return;
		}

		mCurrentScreen->handleKeyboardInput(key);
	}

	void ViperCraft::processMouseButtonForGui(Input::MouseButton button, bool state)
	{
		if (mCurrentScreen == nullptr) return;

		mCurrentScreen->handleMouseInput(1337, 69420, button, state); //TODO: GET MOUSE X AND MOUSE Y VERY IMPORTANT
	}
}