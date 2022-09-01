#pragma once
#include<string>
#include<memory>
#include<map>
#include "../../Renderer/Shaders/ShaderProgram.h"

//namespace Core::Renderer::Shaders {
//	class  ShaderProgram;
//}
class ResourceManager {
public:
	ResourceManager(const std::string& executablePath);
	~ResourceManager() = default;
	ResourceManager(const ResourceManager&) = delete;
	ResourceManager(ResourceManager&&) = delete;
	ResourceManager& operator=(ResourceManager&) = delete;
	ResourceManager& operator=(ResourceManager&&) = delete;

	std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> LoadShader(const std::string& shaderName, const std::string& vshPath, const std::string& fshPath);
	std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> GetShader(const std::string& shaderName);

private:
	std::string GetStringFromFile(const std::string& relFilePath);
	typedef std::map<const std::string, std::shared_ptr<Core::Renderer::Shaders::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap _shaderPrograms;
	std::string _basePath;
};