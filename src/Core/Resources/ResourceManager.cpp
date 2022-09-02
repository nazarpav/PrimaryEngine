#include "ResourceManager.h"
#include<sstream>
#include<fstream>
#include<iostream>

#define STB_IMAGE_IMPLEMENTATION
#define STBI_ONLY_PNG
#include "stb_image.h"
ResourceManager::ResourceManager(const std::string& executablePath) {
	size_t found = executablePath.find_last_of("/\\");
	_basePath = executablePath.substr(0, found);
}

std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> ResourceManager::LoadShader(const std::string& shaderName, const std::string& vshPath, const std::string& fshPath) {
	std::string vshData = GetStringFromFile(vshPath);
	if (vshData.empty()) {
		std::cerr << "No vertex shader!" << std::endl;
		return nullptr;
	}
	std::string fshData = GetStringFromFile(fshPath);
	if (vshData.empty()) {
		std::cerr << "No fragment shader!" << std::endl;
		return nullptr;
	}
	std::shared_ptr<Core::Renderer::Shaders::ShaderProgram>& newShader = _shaderPrograms.emplace(shaderName, std::make_shared<Core::Renderer::Shaders::ShaderProgram>(vshData, fshData)).first->second;
	if (newShader->IsCompiled()) {
		return newShader;
	}
	return nullptr;
}

std::shared_ptr<Core::Renderer::Shaders::ShaderProgram> ResourceManager::GetShader(const std::string& shaderName) {
	ShaderProgramMap::const_iterator it = _shaderPrograms.find(shaderName);
	if (it != _shaderPrograms.end()) {
		return it->second;
	}
	std::cerr << "Can`t find the shader program: " << shaderName << std::endl;
	return nullptr;
}

std::shared_ptr<Core::Renderer::Drawable::Texture2D> ResourceManager::LoadTexture(const std::string& textureName, const std::string& texturePath) {
	int channel = 0;
	int width = 0;
	int height = 0;

	stbi_set_flip_vertically_on_load(true);
	unsigned char* pixels = stbi_load(std::string(_basePath + "/" + texturePath).c_str(), &width, &height, &channel, 0);
	if (pixels == false) {
		std::cerr << "Can`t load image: " << texturePath << std::endl;
		return nullptr;
	}
	std::shared_ptr<Core::Renderer::Drawable::Texture2D> newTexture = _textures.emplace(textureName, std::make_shared<Core::Renderer::Drawable::Texture2D>(width, height, pixels, channel, GL_NEAREST, GL_CLAMP_TO_EDGE)).first->second;


	stbi_image_free(pixels);
	return newTexture;
}

std::shared_ptr<Core::Renderer::Drawable::Texture2D> ResourceManager::GetTexture(const std::string& textureName) {
	Texture2DMap::const_iterator it = _textures.find(textureName);
	if (it != _textures.end()) {
		return it->second;
	}
	std::cerr << "Can`t find the texture: " << textureName << std::endl;
	return nullptr;
}

std::string ResourceManager::GetStringFromFile(const std::string& relFilePath) {
	std::ifstream f;
	f.open(_basePath + "/" + relFilePath.c_str(), std::ios::in | std::ios::binary);
	if (f.is_open() == false) {
		std::cerr << "Failed to open file: " << relFilePath << std::endl;
		return std::string{};
	}
	std::stringstream buffer;
	buffer << f.rdbuf();
	return buffer.str();
}
