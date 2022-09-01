#include "ShaderProgram.h"
#include <iostream>
namespace Core::Renderer::Shaders {

	Core::Renderer::Shaders::ShaderProgram::ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader) {
		GLuint vsh;
		if (CreateShader(vertexShader, GL_VERTEX_SHADER, vsh) == false) {
			std::cerr << "VERTEX SHADER compile-time error" << std::endl;
			return;
		}
		GLuint fsh;
		if (CreateShader(fragmentShader, GL_FRAGMENT_SHADER, fsh) == false) {
			std::cerr << "FRAGMENT SHADER compile-time error" << std::endl;
			glDeleteShader(vsh);
			return;
		}
		_ID = glCreateProgram();
		glAttachShader(_ID, vsh);
		glAttachShader(_ID, fsh);
		glLinkProgram(_ID);
		GLint success;
		glGetProgramiv(_ID, GL_LINK_STATUS, &success);
		if (success == false) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(_ID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Link- time error: \n" << infoLog << std::endl;
		}
		else {
			_isCompiled = true;
		}
		glDeleteShader(vsh);
		glDeleteShader(fsh);
	}

	Core::Renderer::Shaders::ShaderProgram::~ShaderProgram() {
		glDeleteProgram(_ID);
	}

	void Core::Renderer::Shaders::ShaderProgram::use() {
		glUseProgram(_ID);
	}

	ShaderProgram& Core::Renderer::Shaders::ShaderProgram::operator=(ShaderProgram&& shaderProgram) noexcept {
		glDeleteProgram(_ID);
		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;
		return *this;
	}

	Core::Renderer::Shaders::ShaderProgram::ShaderProgram(ShaderProgram&& shaderProgram) noexcept {
		_ID = shaderProgram._ID;
		_isCompiled = shaderProgram._isCompiled;

		shaderProgram._ID = 0;
		shaderProgram._isCompiled = false;
	}

	bool Core::Renderer::Shaders::ShaderProgram::CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID) {
		shaderID = glCreateShader(shaderType);
		const char* code = source.c_str();
		glShaderSource(shaderID, 1, &code, nullptr);
		glCompileShader(shaderID);

		GLint success;
		glGetShaderiv(shaderID, GL_COMPILE_STATUS, &success);
		if (success == false) {
			GLchar infoLog[1024];
			glGetShaderInfoLog(shaderID, 1024, nullptr, infoLog);
			std::cerr << "ERROR::SHADER: Compile- time error: \n" << infoLog << std::endl;
			return false;
		}
		return true;
	}
}
