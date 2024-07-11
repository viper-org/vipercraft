#pragma once

#include <Render/Renderable.h>

namespace ViperGL
{
	class RenderableVoxel : public Renderable
	{
	public:
		RenderableVoxel(float x, float y, float z, ShaderProgram* shader, Texture texture);
		virtual void init() override;

	private:
		float x;
		float y;
		float z;

		Texture mTex;
	};
}