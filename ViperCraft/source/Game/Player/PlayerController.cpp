#include <Game/Player/PlayerController.h>
#include <Game/Player/Player.h>

#include <ViperCraft/ViperCraft.h>

#include <Input/Input.h>

namespace ViperCraft
{
	PlayerController::PlayerController(Player& parent)
		: mParent(parent)
	{
	}
	
	void PlayerController::init()
	{
		auto handler = std::bind(&PlayerController::onTick, this, std::placeholders::_1);
		ViperCraft::GetInstance()->onTick(handler);
	}

	ViperGL::Camera& PlayerController::getCamera()
	{
		return mCamera;
	}


	void PlayerController::onTick(double deltaTime)
	{
		glm::vec3 move = glm::vec3(0.f);
		constexpr float MOVE_SPEED = 5.f;
		if (Input::GetButtonDown(Input::Key::A))
		{
			move -= mCamera.right * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::D))
		{
			move += mCamera.right * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::W))
		{
			move += mCamera.forward * (float)(MOVE_SPEED * deltaTime);
		}
		if (Input::GetButtonDown(Input::Key::S))
		{
			move -= mCamera.forward * (float)(MOVE_SPEED * deltaTime);
		}
		mCamera.position += move;

		mCamera.yaw += Input::GetInputAxis(Input::InputAxis::AxisX);
		mCamera.pitch += Input::GetInputAxis(Input::InputAxis::AxisY);

		mCamera.pitch = glm::clamp(mCamera.pitch, -89.9f, 89.9f);
	}
}