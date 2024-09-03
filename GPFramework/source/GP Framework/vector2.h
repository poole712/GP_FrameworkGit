#ifndef  _VECTOR2_H
#define _VECTOR2_H

class Vector2
{
public:
	Vector2();
	Vector2(float max, float iny);
	~Vector2();

	void Set(float inx, float iny);

	float LengthSquared() const;
	float Length() const;

	void Normalise();

	friend Vector2 operator+(const Vector2& veca, const Vector2& vecb)
	{
		return (Vector2(veca.x + vecb.x, veca.y + vecb.y));
	}

	friend Vector2 operator-(const Vector2& veca, const Vector2& vecb)
	{
		return (Vector2(veca.x - vecb.x, veca.y - vecb.y));
	}

	friend Vector2 operator*(float scalar, const Vector2& vec)
	{
		return (Vector2(vec.x * scalar, vec.y * scalar));
	}

	friend Vector2 operator*(const Vector2& vec, float scalar)
	{
		return (Vector2(vec.x * scalar, vec.y * scalar));
	}

	Vector2& operator*=(float scalar)
	{
		x = x * scalar;
		y = y * scalar;
		return(*this);
	}

	Vector2& operator+=(const Vector2& vecRight)
	{
		x = x + vecRight.x;
		y = y + vecRight.y;
		return (*this);
	}

	Vector2& operator-=(const Vector2& vecRight)
	{
		x = x - vecRight.x;
		y = y - vecRight.y;
		return (*this);
	}

	static float DotProduct(const Vector2& veca, const Vector2& vecb);
	static Vector2 Lerp(const Vector2& veca, const Vector2& vecb, float time);
	static Vector2 Reflect(const Vector2& veca, const Vector2& vecb);

public:
	float x;
	float y;

protected:

private:
	//Vector2(const Vector2& vector2);
	//Vector2& operator=(const Vector2& vector2);

};

#endif // ! _VECTOR2_H
