#include <Render/RenderableRect.h>

namespace ViperGL
{
	RenderableRect::RenderableRect(float x1, float y1, float x2, float y2, ShaderProgram* shader)
		: x1(x1)
		, y1(y1)
		, x2(x2)
		, y2(y2)
	{
		mShaderProgram = shader;
	}

	void RenderableRect::init()
	{
		mVO.~VertexObject();
		new (&mVO) VertexObject({
			x1, y1, 0.f,
			x1, y2, 0.f,
			x2, y1, 0.f,
			x2, y2, 0.f,
		});

		mEB.~ElementBuffer();
		new (&mEB) ElementBuffer({
			0, 1, 2,
			1, 2, 3
		});
	}
}