#pragma once

#include <Game/Player/PlayerController.h>

#include <glm/vec3.hpp>

namespace ViperCraft
{
	class Player
	{
	friend class PlayerController;
	public:
		Player();

		void init();
		
		const glm::vec3& getPosition() const;
		PlayerController& getPlayerController();

	private:
		glm::vec3 mPosition;

		PlayerController mController;
	};
}