#include <Render/RenderableRect.h>

namespace ViperGL
{
	RenderableRect::RenderableRect(ShaderProgram* shader)
	{
		mShaderProgram = shader;
	}

	void RenderableRect::init(int id)
	{
		mId = id;

		mVO.~VertexObject(); // TODO: add texture coordinates
		new (&mVO) VertexObject({
			 0.5f,  0.5f, 0.f,
			 0.5f, -0.5f, 0.f,
			-0.5f,  0.5f, 0.f,
			-0.5f, -0.5f, 0.f
		});

		mEB.~ElementBuffer();
		new (&mEB) ElementBuffer({
			0, 1, 2,
			1, 2, 3
		});
	}
}