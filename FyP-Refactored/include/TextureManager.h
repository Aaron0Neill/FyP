#pragma once

#include <SFML/Graphics.hpp>

#include <unordered_map>

using Texture = std::shared_ptr<sf::Texture>;

class TextureManager
{
public:
	static TextureManager* getInstance()
	{
		static TextureManager instance;
		return &instance;
	}

	TextureManager(const TextureManager&) = delete;
	void operator=(const TextureManager&) = delete;

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_safeName"></param>
	/// <param name="t_filePath"></param>
	/// <returns></returns>
	bool loadTexture(std::string t_safeName, std::string t_filePath)
	{
		Texture tex = std::make_shared<sf::Texture>();
		if (m_textureMapping.count(t_safeName)) return true;
		if (tex->loadFromFile(t_filePath))
		{
			m_textureMapping[t_safeName] = tex;
			std::cout << "Successfully loaded: " << t_safeName << "\n";
		}

		return m_textureMapping.count(t_safeName);
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_safeName"></param>
	/// <returns></returns>
	Texture getTexture(std::string t_safeName)
	{
		return m_textureMapping[t_safeName];
	};

	/// <summary>
	/// 
	/// </summary>
	/// <param name="t_texture"></param>
	/// <returns></returns>
	std::string findName(const sf::Texture* t_texture)
	{
		for (const auto&[name, texture] : m_textureMapping)
			if (texture.get() == t_texture)
				return name;
	}


private:
	TextureManager() = default;

	std::unordered_map<std::string, Texture> m_textureMapping;
};