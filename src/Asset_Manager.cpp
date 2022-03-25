#include "Asset_Manager.h"

Asset_Manager::Asset_Manager()
{
}

Asset_Manager::~Asset_Manager()
{
}

void Asset_Manager::LoadTexture(const int name, const std::string FileName) 
{
	sf::Texture tex;

	if (tex.loadFromFile(FileName))
	{
		this->m_textures[name] = tex;
	}
}

sf::Texture& Asset_Manager::GetTexture(const int name) 
{
	return this->m_textures.at(name);
}

