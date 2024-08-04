#ifndef  _TEXTUREMANAGER_H
#define _TEXTUREMANAGER_H

#include <string>
#include <map>

class Texture;

class TextureManager
{
	//Member methods
public:
	TextureManager();
	~TextureManager();

	bool Initialise();

	Texture* GetTexture(const char* pcFilename);

protected:

private:
	TextureManager(const TextureManager& textureManager);
	TextureManager& operator=(const TextureManager& textureManager);

	//Member data:
public:

protected:
	std::map<std::string, Texture*> m_pLoadedTextures;

private:

};

#endif // ! _TEXTUREMANAGER_H
