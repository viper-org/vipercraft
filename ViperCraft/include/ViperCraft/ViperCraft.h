#pragma once

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

		void run();

		static void CreateGame(ViperCraftErrorCode& errorCode);
		static ViperCraft* GetInstance();

		ViperGL::RenderQueue* getRenderQueue();

	private:
		ViperGL::Window mWindow;
		ViperGL::RenderQueue mRenderQueue;
		ViperGL::Camera mCamera;

		World mWorld;

		void initGame();

		void processInput(double deltaTime);
		void render();
		void postEvents(double deltaTime);
	};
}