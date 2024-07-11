#pragma once

#include <string>

namespace ViperGL
{
	enum class ShaderType
	{
		Vertex,
		Fragment,
	};

	enum class ShaderErrorCode
	{
		Success=0,
		CompileFailed,
		LinkFailed
	};

	class Shader
	{
	public:
		Shader(std::string code, ShaderType type, ShaderErrorCode& errorCode);
		~Shader();

		unsigned int getId() const;

	private:
		unsigned int mId;
		ShaderType mType;
	};

	class ShaderProgram
	{
	public:
		ShaderProgram(std::string name, ShaderErrorCode& errorCode); // vertex and fragment shaders are at location ./shader/vert-{name} and ./shader/frag-{name} respectively

		void use();

	private:
		std::string mName;

		unsigned int mId;
		unsigned int compileShader(std::string code, ShaderType type);
	};
}