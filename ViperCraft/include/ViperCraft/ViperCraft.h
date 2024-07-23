#pragma once

#include <Game/Gui/GuiScreen.h>

#include <Game/Player/Player.h>

#include <Game/World/World.h>

#include <ViperGL/Window/Window.h>
#include <ViperGL/Render/RenderQueue.h>
#include <ViperGL/Camera/Camera.h>

namespace ViperCraft
{
	enum class ViperCraftErrorCode
	{
		Success=0,
		GlfwInitFailed,
		GladInitFailed,
		WindowFailed,
	};

	class ViperCraft
	{
	public:
		ViperCraft(ViperCraftErrorCode& errorCode);
		~ViperCraft();

		void setPlayerSpawn(glm::vec3 position);
		void run();

		static void CreateGame(ViperCraftErrorCode& errorCode);
		static ViperCraft* GetInstance();

		void onTick(std::function<void(double)> handler);

		void displayGuiScreen(std::unique_ptr<GuiScreen> newGuiScreen);

		World* getWorld();
		Player* getPlayer();
		ViperGL::RenderQueue* getRenderQueue();
		
		bool isGameInFocus();

		void setGameInFocus();
		void setGameNotInFocus();

	private:
		ViperGL::Window mWindow;
		ViperGL::RenderQueue mRenderQueue;

		std::vector<std::function<void(double)> > mOnTickHandlers;

		std::unique_ptr<GuiScreen> mCurrentScreen;

		World mWorld;
		Player mPlayer;

		bool mGameHasFocus;

		void initGame();

		void render();
		void postEvents(double deltaTime);

		void processKeyDownForGui(Input::Key key);
		void processMouseButtonForGui(Input::MouseButton button, bool state);
	};
}