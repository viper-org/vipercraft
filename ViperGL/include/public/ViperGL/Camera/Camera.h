#pragma once

namespace ViperGL
{
	struct Camera
	{
		float pitch{ 0.f };
		float yaw{ 270.f };

		struct
		{
			float x{ 0.f };
			float y{ 0.f };
			float z{ 3.f };
		} position;
	};
}