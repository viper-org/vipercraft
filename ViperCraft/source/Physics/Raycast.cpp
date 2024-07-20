#include <Physics/Raycast.h>

#include <ViperCraft/ViperCraft.h>

#include <glm/geometric.hpp>

namespace ViperCraft
{
	namespace Physics
	{
		bool RaycastSolid(glm::vec3 origin, glm::vec3 direction, float maxDist, glm::vec3& hit)
		{
			constexpr float RAY_STEP = 0.1f;

			direction = glm::normalize(direction); // in case direction has a huge magnitude

			glm::vec3 position = origin;

			while (glm::distance(position, origin) <= maxDist)
			{
				auto chunk = ViperCraft::GetInstance()->getWorld()->getPositionChunk(position);
				auto tile = chunk->getTile(position);
				if (tile && tile->isSolidTile())
				{
					hit = position;
					return true;
				}

				position += direction * RAY_STEP;
			}

			return false;
		}
	}
}