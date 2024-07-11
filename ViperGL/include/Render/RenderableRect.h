#pragma once

#include <Render/Renderable.h>

namespace ViperGL
{
	class RenderableRect : public Renderable
	{
	public:
		RenderableRect(float x1, float y1, float x2, float y2, ShaderProgram* shader);
		virtual void init() override;

	private:
		float x1, y1;
		float x2, y2;
	};
}