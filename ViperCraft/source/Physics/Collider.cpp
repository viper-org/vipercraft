#include <Physics/Collider.h>

#include <array>

namespace ViperCraft
{
	namespace Physics
	{
		BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
			: mMin(min)
			, mMax(max)
		{
		}

		bool BoundingBox::collide(const BoundingBox& other, Collision& collision) const
		{
			constexpr std::array<glm::vec3, 6> faces = {
				glm::vec3(-1,  0,  0),
				glm::vec3(1,  0,  0),
				glm::vec3(0, -1,  0),
				glm::vec3(0,  1,  0),
				glm::vec3(0,  0, -1),
				glm::vec3(0,  0,  1)
			};
			std::array<float, 6> distances = {
				(other.mMax.x - mMin.x),
				(mMax.x - other.mMin.x),
				(other.mMax.y - mMin.y),
				(mMax.y - other.mMin.y),
				(other.mMax.z - mMin.z),
				(mMax.z - other.mMin.z)
			};
			for (int i = 0; i < 6; i++)
			{
				if (distances[i] < 0.0f) return false;

				if ((i == 0) || (distances[i] < collision.depth))
				{
					collision.normal = faces[i];
					collision.depth = distances[i];
				}
			}
			return true;
		}
	}
}