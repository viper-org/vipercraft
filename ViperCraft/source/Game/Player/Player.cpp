#include <Game/Player/Player.h>

namespace ViperCraft
{
	Player::Player()
		: mPosition(0, 1, 0)
		, mController(*this)
	{
	}

	void Player::init()
	{
		mController.init();
	}

	const glm::vec3& Player::getPosition() const
	{
		return mPosition;
	}

	PlayerController& Player::getPlayerController()
	{
		return mController;
	}
}