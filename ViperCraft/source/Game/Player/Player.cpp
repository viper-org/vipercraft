#include <Game/Player/Player.h>

namespace ViperCraft
{
	Player::Player()
		: mPosition(3, 3.f, 3)
		, mMoveSpeed(4.317f)
		, mJumpHeight(1.25f)
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