#pragma once

#include <Render/Renderable.h>

namespace ViperGL
{
	class RenderableVoxel : public Renderable
	{
	public:
		RenderableVoxel(ShaderProgram* shader, Texture texture);
		virtual void init(int id) override;

	private:
		Texture mTex;
	};
}