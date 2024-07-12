#pragma once

#include <Game/Block/Chunk.h>

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

	private:
		ViperGL::Window mWindow;
		ViperGL::RenderQueue mRenderQueue;
		ViperGL::Camera mCamera;

		std::unique_ptr<Chunk[]> mChunks; // TODO: Move this into a world class

		void processInput(double deltaTime);
		void render();
		void postEvents(double deltaTime);
	};
}