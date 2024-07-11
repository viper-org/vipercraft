#pragma once

#include <ViperGL/Window/Window.h>

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

		void processInput();
		void render();
		void postEvents();
	};
}