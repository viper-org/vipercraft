#pragma once

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

		void processInput();
		void render();
		void postEvents();
	};
}