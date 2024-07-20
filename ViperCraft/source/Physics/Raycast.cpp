#include <Physics/Raycast.h>

#include <ViperCraft/ViperCraft.h>

#include <glm/geometric.hpp>

namespace ViperCraft
{
	namespace Physics
	{

		static inline glm::vec3 GetNormal(glm::vec3 center, glm::vec3 point)
		{
			glm::vec3 normal = glm::vec3(0.f);
			float min = INFINITY;
			float distance;
			point -= center;

			distance = abs(1 - abs(point.x));
			if (distance < min)
			{
				min = distance;
				normal = glm::sign(point.x) * glm::vec3(1.f, 0.f, 0.f);
			}

			distance = abs(1 - abs(point.y));
			if (distance < min)
			{
				min = distance;
				normal = glm::sign(point.y) * glm::vec3(0.f, 1.f, 0.f);
			}

			distance = abs(1 - abs(point.z));
			if (distance < min)
			{
				min = distance;
				normal = glm::sign(point.z) * glm::vec3(0.f, 0.f, 1.f);
			}

			return normal;
		}
		bool RaycastSolid(glm::vec3 origin, glm::vec3 direction, float maxDist, RaycastHit& hit)
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
					hit.point = position;
					auto blockCenter = floor(position) + 0.5f;
					hit.normal = GetNormal(blockCenter, position);
					return true;
				}

				position += direction * RAY_STEP;
			}

			return false;
		}
	}
}
