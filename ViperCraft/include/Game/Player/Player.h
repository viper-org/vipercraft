#pragma once

#include <Game/Player/PlayerController.h>

#include <glm/vec3.hpp>

namespace ViperCraft
{
	class Player
	{
	public:
		Player();

		void init();

		PlayerController& getPlayerController();

	private:
		glm::vec3* mPosition; // references the position inside PlayerController's camera

		PlayerController mController;
	};
}