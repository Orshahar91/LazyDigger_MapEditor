#pragma once

#include <string>
#include <map>
#include <SFML/Graphics.hpp>
#include "Consts.h"

class Asset_Manager
{
public:
	Asset_Manager();
	~Asset_Manager();

	void LoadTexture(const int name, const std::string FileName);
	sf::Texture& GetTexture(const int name);


private:
	std::map<int, sf::Texture> m_textures; // map to texture load and extraction
	sf::Context context; // to use openGL functions without an active window
};
