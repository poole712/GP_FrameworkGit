#include "texturemanager.h"

#include "texture.h"
#include "logmanager.h"

#include <cassert>
#include <SDL.h>

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	std::map<std::string, Texture*>::iterator iter = m_pLoadedTextures.begin();

	while (iter != m_pLoadedTextures.end())
	{
		Texture* pTexture = iter->second;
		delete pTexture;

		++iter;
	}

	m_pLoadedTextures.clear();
}

bool 
TextureManager::Initialise()
{
	LogManager::GetInstance().Log("TextureManager starting...");

	return true;
}

Texture*
TextureManager::GetTexture(const char* pcFilename)
{
	Texture* pTexture = 0;

	if (m_pLoadedTextures.find(pcFilename) == m_pLoadedTextures.end())
	{
		pTexture = new Texture();
		if (!pTexture->Initialise(pcFilename))
		{
			LogManager::GetInstance().Log("Texture failed to initialise!");
			assert(0);
		}

		m_pLoadedTextures[pcFilename] = pTexture;
	}
	else
	{
		pTexture = m_pLoadedTextures[pcFilename];
	}

	return pTexture;
}

void 
TextureManager::AddTexture(const char* key, Texture* pTexture)
{
	m_pLoadedTextures[key] = pTexture;
}