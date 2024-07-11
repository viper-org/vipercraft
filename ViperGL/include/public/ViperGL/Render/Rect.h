#pragma once

namespace ViperGL
{
	// exposed so it can be pushed onto the RenderQueue which creates the RenderableRect
	class Rect
	{
	friend class RenderQueue;
	public:
		Rect(float x1, float y1, float x2, float y2);

	private:
		float x1, y1;
		float x2, y2;
	};
}