#include <Physics/Collider.h>

namespace ViperCraft
{
	namespace Physics
	{
		BoundingBox::BoundingBox(glm::vec3 min, glm::vec3 max)
			: mMin(min)
			, mMax(max)
		{
		}

		bool BoundingBox::intersects(const BoundingBox& other) const
		{
			return (
				mMin.x <= other.mMax.x &&
				mMax.x >= other.mMin.x &&
				mMin.y <= other.mMax.y &&
				mMax.y >= other.mMin.y &&
				mMin.z <= other.mMax.z &&
				mMax.z >= other.mMin.z
			);
		}
	}
}