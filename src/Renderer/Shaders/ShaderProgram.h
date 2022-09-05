#pragma once
#include "glad/glad.h"
#include "glm/mat4x4.hpp"
#include <string>

namespace Core::Renderer::Shaders {
	class ShaderProgram {
	public:
		ShaderProgram(const std::string& vertexShader, const std::string& fragmentShader);
		~ShaderProgram();
		inline bool IsCompiled()const {
			return _isCompiled;
		}
		void Use();
		ShaderProgram() = delete;
		ShaderProgram(ShaderProgram&) = delete;
		ShaderProgram& operator=(const ShaderProgram&) = delete;
		ShaderProgram& operator=(ShaderProgram&& shaderProgram) noexcept;
		ShaderProgram(ShaderProgram&& shaderProgram)noexcept;
		void SetSampler(const std::string& name, const GLint val);
		void SetMatrix4(const std::string& name, const glm::mat4 mtrx);

	private:
		bool CreateShader(const std::string& source, const GLenum shaderType, GLuint& shaderID);

	private:
		bool _isCompiled = false;
		GLuint _ID = 0;
	};
}