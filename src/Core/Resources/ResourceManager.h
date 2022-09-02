#pragma once
#include<string>
#include<memory>
#include<map>
#include "../../Renderer/Shaders/ShaderProgram.h"
#include "../../Renderer/Drawable/Texture2D.h"

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
		
	std::shared_ptr<Core::Renderer::Drawable::Texture2D> LoadTexture(const std::string& textureName, const std::string& texturePath);
	std::shared_ptr<Core::Renderer::Drawable::Texture2D> GetTexture(const std::string& textureName);
private:
	std::string GetStringFromFile(const std::string& relFilePath);
	typedef std::map<const std::string, std::shared_ptr<Core::Renderer::Shaders::ShaderProgram>> ShaderProgramMap;
	ShaderProgramMap _shaderPrograms;

	typedef std::map<const std::string, std::shared_ptr<Core::Renderer::Drawable::Texture2D>> Texture2DMap;
	Texture2DMap _textures;
	
	std::string _basePath;
};