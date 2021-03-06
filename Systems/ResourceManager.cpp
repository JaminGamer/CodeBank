#include "stdafx.h"

ResourceManager::ResourceManager()
{
}

ResourceManager::~ResourceManager()
{
	DeleteAllResources();
}
std::basic_string<TCHAR> toTCHAR(const std::string &s)
{
#ifdef UNICODE
	std::basic_string<TCHAR> result;
	int len = MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.length(), NULL, 0);
	if (len > 0)
	{
		result.resize(len);
		MultiByteToWideChar(CP_ACP, 0, s.c_str(), s.length(), &result[0], len);
	}
	return result;
#else
	return s;
#endif
}
void ResourceManager::LoadDirectory(const char* folder)
{
    // TODO: Find a good way of getting the names of files in a folder/directory

	tinydir_dir dir;
	int i;
	// tinydir_open_sorted(&dir, folder);
	std::basic_string<TCHAR> result = toTCHAR(std::string(folder));
	tinydir_open(&dir, result.data());
	for (i = 0; i < dir.n_files; i++)
	{
		tinydir_file file;
		tinydir_readfile_n(&dir, &file, i);

		printf("%s", file.name);
		if (file.is_dir)
		{
			printf("/");
		}
		printf("\n");
	}

	tinydir_close(&dir);
}

void ResourceManager::DeleteAllResources()
{
	for (auto object : m_HotMeshes)
		delete object.second;

	for (auto object : m_HotShaders)
		delete object.second;

	for (auto object : m_HotTextures)
		glDeleteTextures(1, &object.second);

	for (auto object : m_HotMaterials)
		delete object.second;

    for (auto object : m_HotModels)
        delete object.second;

	m_HotMeshes.clear(); // Empty std::maps
	m_HotShaders.clear();
	m_HotTextures.clear();
	m_HotMaterials.clear();
	m_HotModels.clear();
}
// getters
// TODO: Return nullptr values
Mesh* ResourceManager::GetMesh(const char* name)
{
	if (m_HotMeshes.find(name) != m_HotMeshes.end())
	{
		return m_HotMeshes[name];
	}
	return InstantiateMesh(name);
}

ShaderProgram* ResourceManager::GetShader(const char* name)
{
	if (m_HotShaders.find(name) != m_HotShaders.end()) // unique name
	{
		return m_HotShaders[name];
	}
	return InstantiateShader(name);
}

GLuint ResourceManager::GetTexture(const char* name)
{
	if (m_HotTextures.find(name) != m_HotTextures.end())
	{
		return m_HotTextures[name];
	}
	return InstantiateTexture(name);
}

MaterialData* ResourceManager::GetMaterial(const char* name)
{
	if (m_HotMaterials.find(name) != m_HotMaterials.end())
	{
		return m_HotMaterials[name];
	}
	return InstantiateMaterial(name);
}

Model* ResourceManager::GetModel(const char* name)
{
	if (m_HotModels.find(name) != m_HotModels.end())
	{
		return m_HotModels[name];
	}
	return InstantiateModel(name);
}
// Utilities
bool ResourceManager::isUnique(Mesh* mesh)
{
	std::map<std::string, Mesh*>::iterator it;
	for (it = m_HotMeshes.begin(); it != m_HotMeshes.end(); it++)
	{
		if (it->second == mesh) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(ShaderProgram* shader)
{
	std::map<std::string, ShaderProgram*>::iterator it;
	for (it = m_HotShaders.begin(); it != m_HotShaders.end(); it++)
	{
		if (it->second == shader) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(GLuint texturehandle)
{
	std::map<std::string, GLuint>::iterator it;
	for (it = m_HotTextures.begin(); it != m_HotTextures.end(); it++)
	{
		if (it->second == texturehandle) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(MaterialData* material)
{
	std::map<std::string, MaterialData*>::iterator it;
	for (it = m_HotMaterials.begin(); it != m_HotMaterials.end(); it++)
	{
		if (it->second == material) // pointer comparison
			return false;
	}
	return true;
}

bool ResourceManager::isUnique(Model* model)
{
	std::map<std::string, Model*>::iterator it;
	for (it = m_HotModels.begin(); it != m_HotModels.end(); it++)
	{
		if (it->second == model) // pointer comparison
			return false;
	}
	return true;
}