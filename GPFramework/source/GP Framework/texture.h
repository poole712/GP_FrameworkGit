#ifndef _TEXTURE_H_
#define _TEXTURE_H_

class Texture
{
	//Member methods:
public:
	Texture();
	~Texture();

	bool Initialise(const char* pcFileName);

	void SetActive();

	int GetWidth() const;
	int GetHeight() const;

protected:

private:
	Texture(const Texture& texture);
	Texture& operator=(const Texture& texture);

	//Member data:
public:

protected:
	unsigned int m_uiTextureId;
	int m_iWidth;
	int m_iHeight;

private:

};
 
#endif // !_TEXTURE_H_
