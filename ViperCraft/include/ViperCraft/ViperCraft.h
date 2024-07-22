#pragma once

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

		World* getWorld();
		Player* getPlayer();
		ViperGL::RenderQueue* getRenderQueue();

	private:
		ViperGL::Window mWindow;
		ViperGL::RenderQueue mRenderQueue;
		ViperGL::UIRenderQueue mUIRenderQueue;

		std::vector<std::function<void(double)> > mOnTickHandlers;

		World mWorld;
		Player mPlayer;

		void initGame();

		void render();
		void postEvents(double deltaTime);
	};
}