#pragma once

#include <Render/Renderable.h>

namespace ViperGL
{
	class RenderableRect : public Renderable
	{
	public:
		RenderableRect(float x, float y, ShaderProgram* shader);
		virtual void init() override;

	private:
		float x;
		float y;
	};
}