#include <Render/RenderableRect.h>

namespace ViperGL
{
	RenderableRect::RenderableRect(float x, float y, ShaderProgram* shader)
		: x(x)
		, y(y)
	{
		mShaderProgram = shader;
		mPosition = glm::vec3(x, y, 0.f);
	}

	void RenderableRect::init()
	{
		mVO.~VertexObject();
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