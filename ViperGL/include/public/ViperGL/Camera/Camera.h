#pragma once

#include <glm/glm.hpp>

namespace ViperGL
{
	struct Camera
	{
	friend class RenderQueue;
		float pitch{ 0.f };
		float yaw{ 270.f };

		glm::vec3 position{ 0.f, 2.f, 0.f };
		glm::vec3 target;

		glm::vec3 front{ 0.f, 0.f, -1.f };
		glm::vec3 forward{ 0.f, 0.f, -1.f };
		glm::vec3 right;
		glm::vec3 up;

		glm::vec3 worldUp{ 0.f, 1.f, 0.f };

	private:
		void updateVectors()
		{
			front.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
			front.y = sin(glm::radians(pitch));
			front.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));

			forward.x = cos(glm::radians(yaw));
			forward.z = sin(glm::radians(yaw));

			right = glm::normalize(glm::cross(front, worldUp));
			up = glm::normalize(glm::cross(right, front));
		}
	};
}