#pragma once

#include <Render/Renderable.h>

namespace ViperGL
{
	class RenderableRect : public Renderable
	{
	public:
		RenderableRect(ShaderProgram* shader);
		virtual void init(int id) override;
	};
}