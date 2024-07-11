#include <Shader/Shader.h>

#include <glad/glad.h>

#include <filesystem>
#include <fstream>

#ifndef SHADER_SOURCE_DIR
#error Shader Source Directory Not Specified
#endif

namespace ViperGL
{
	Shader::Shader(std::string code, ShaderType type, ShaderErrorCode& errorCode)
		: mId(0)
		, mType(type)
	{
		const char* shaderCode = code.c_str();
		int success;

		mId = glCreateShader(mType == ShaderType::Vertex ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);
		glShaderSource(mId, 1, &shaderCode, nullptr);
		glCompileShader(mId);

		glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			errorCode = ShaderErrorCode::CompileFailed;
			// TODO: debug print
			return;
		}
		errorCode = ShaderErrorCode::Success;
	}

	Shader::~Shader()
	{
		glDeleteShader(mId);
	}

	unsigned int Shader::getId() const
	{
		return mId;
	}


	ShaderProgram::ShaderProgram(std::string name, ShaderErrorCode& errorCode)
		: mName(name)
		, mId(0)
	{
		std::filesystem::path vertPath = std::filesystem::path(SHADER_SOURCE_DIR) / "shader" / ("vert-" + name);
		std::filesystem::path fragPath = std::filesystem::path(SHADER_SOURCE_DIR) / "shader" / ("frag-" + name);

		std::ifstream vertFile(vertPath);
		std::ifstream fragFile(fragPath);

		std::stringstream vertSS, fragSS;
		vertSS << vertFile.rdbuf();
		fragSS << fragFile.rdbuf();

		std::string vertCode = vertSS.str();
		std::string fragCode = fragSS.str();

		Shader vertex = Shader(vertCode, ShaderType::Vertex, errorCode);
		if (errorCode != ShaderErrorCode::Success)
			return;

		Shader fragment = Shader(fragCode, ShaderType::Fragment, errorCode);
		if (errorCode != ShaderErrorCode::Success)
			return;

		int success;

		mId = glCreateProgram();
		glAttachShader(mId, vertex.getId());
		glAttachShader(mId, fragment.getId());
		glLinkProgram(mId);

		glGetProgramiv(mId, GL_LINK_STATUS, &success);
		if (!success)
		{
			errorCode = ShaderErrorCode::LinkFailed;
			// TODO: debug print
			return;
		}
		errorCode = ShaderErrorCode::Success;
	}

	void ShaderProgram::use()
	{
		glUseProgram(mId);
	}
}