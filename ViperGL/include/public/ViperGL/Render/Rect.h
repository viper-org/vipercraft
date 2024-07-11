#pragma once

namespace ViperGL
{
	// exposed so it can be pushed onto the RenderQueue which creates the RenderableRect
	class Rect
	{
	friend class RenderQueue;
	public:
		Rect(float x, float y);

	private:
		float x;
		float y;
	};
}