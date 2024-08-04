#ifndef  _VERTEXARRAY_H
#define _VERTEXARRAY_H

class VertexArray
{
	//Memebr methods:
public:
	VertexArray(const float* pVertices, unsigned int numVertices, const unsigned int* pIndicies, unsigned int numIndicies);
	~VertexArray();

	void SetActive();

	unsigned int GetNumVertices() const;
	unsigned int GetNumIndicies() const;

protected:

private:
	VertexArray(const VertexArray& vertexArray);
	VertexArray& operator=(const VertexArray& vertexArray);

	//Member data
public:

protected:
	unsigned int m_numVertices;
	unsigned int m_numIndicies;

	unsigned int m_glVertexBuffer;
	unsigned int m_glIndexBuffer;
	unsigned int m_glVertexArray;

private:

};

#endif // ! _VERTEXARRAY_H
