#ifndef  _MATRIX4_H
#define _MATRIX_H

struct Matrix4
{
	float m[4][4];
};

void SetZero(Matrix4& mat);
void SetIdentity(Matrix4& mat);
void CreateOrthoProjection(Matrix4& mat, float width, float height);

#endif // ! _MATRIX4_H
