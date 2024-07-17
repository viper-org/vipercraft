#include <Game/Player/PlayerController.h>
#include <Game/Player/Player.h>

#include <ViperCraft/ViperCraft.h>

#include <Physics/Collider.h>

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
		constexpr float MOVE_SPEED = 5.f;
		constexpr float CAMERA_HEIGHT = 1.62f;

		glm::vec3 move = glm::vec3(0.f);
		if (Input::GetButtonDown(Input::Key::A))
		{
			auto step = -mCamera.right * (float)(MOVE_SPEED * deltaTime);
			//if (canPlayerMoveInto(mParent.mPosition + step))
				move += step;
		}
		if (Input::GetButtonDown(Input::Key::D))
		{
			auto step = mCamera.right * (float)(MOVE_SPEED * deltaTime);
			//if (canPlayerMoveInto(mParent.mPosition + step))
				move += step;
		}
		if (Input::GetButtonDown(Input::Key::W))
		{
			auto step = mCamera.forward * (float)(MOVE_SPEED * deltaTime);
			//if (canPlayerMoveInto(mParent.mPosition + step))
				move += step;
		}
		if (Input::GetButtonDown(Input::Key::S))
		{
			auto step = -mCamera.forward * (float)(MOVE_SPEED * deltaTime);
			//if (canPlayerMoveInto(mParent.mPosition + step))
				move += step;
		}

		// TODO: Replace this with proper wall sliding
		if (!canPlayerMoveInto(mParent.mPosition + glm::vec3(move.x, 0, 0))) move.x = 0;
		if (!canPlayerMoveInto(mParent.mPosition + glm::vec3(0, 0, move.z))) move.z = 0;
		mParent.mPosition += move;

		mCamera.yaw += Input::GetInputAxis(Input::InputAxis::AxisX);
		mCamera.pitch += Input::GetInputAxis(Input::InputAxis::AxisY);

		mCamera.pitch = glm::clamp(mCamera.pitch, -89.9f, 89.9f);
		mCamera.position = mParent.mPosition + glm::vec3(0, CAMERA_HEIGHT, 0) - mCamera.forward * 0.1f;
	}

	bool PlayerController::canPlayerMoveInto(glm::vec3 position)
	{
		constexpr float PLAYER_SIZE = 0.6f;

		auto checkIndividualPos = [](Physics::BoundingBox& player, glm::vec3 block) {
			auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(block);

			auto tile = chunk->getTile(block);
			Physics::BoundingBox BB = Physics::BoundingBox(block, block + 1.f);

			if (tile)
				if (tile->isSolidTile() && BB.intersects(player)) return false;
			return true;
		};

		// create player bounding box
		std::array<glm::vec3, 4> playerCorners = {
			position + mCamera.forward * PLAYER_SIZE + mCamera.right * PLAYER_SIZE,
			position + mCamera.forward * PLAYER_SIZE - mCamera.right * PLAYER_SIZE,
			position - mCamera.forward * PLAYER_SIZE + mCamera.right * PLAYER_SIZE,
			position - mCamera.forward * PLAYER_SIZE - mCamera.right * PLAYER_SIZE,
		};
		auto minX = std::min_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
			return a.x < b.x;
		})->x;
		auto maxX = std::max_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
			return a.x < b.x;
		})->x;
		auto minZ = std::min_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
			return a.z < b.z;
		})->z;
		auto maxZ = std::max_element(playerCorners.begin(), playerCorners.end(), [](auto& a, auto& b) {
			return a.z < b.z;
		})->z;
		Physics::BoundingBox playerBB = Physics::BoundingBox(glm::vec3(minX, position.y, minZ), glm::vec3(maxX, position.y + 1.8f, maxZ));
		
		// check against top and bottom blocks of new position(maybe change this to a larger volume of blocks)
		if (!checkIndividualPos(playerBB, position)) return false;
		if (!checkIndividualPos(playerBB, position + glm::vec3(0, 1, 0))) return false;

		return true;
	}
}