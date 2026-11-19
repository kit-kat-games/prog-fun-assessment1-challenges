#pragma once

class Vector2
{
public:
	Vector2(float _x, float _y) {
		x = _x;
		y = _y;
	}
	// A suitable copy constructor for constructing a Vector2 instance from another.
	Vector2(const Vector2& v) {
		x = v.x;
		y = v.y;
	}
	float readx() { return x; }
	float ready() { return y; }

	// A suitable copy-assignment overload for assigning a Vector2 instance to another.í
	Vector2& operator = (Vector2& other) {
		std::swap(x, other.x);
		std::swap(y, other.y);
		return *this;
	}
	Vector2 operator = (Vector2 other) {
		std::swap(x, other.x);
		std::swap(y, other.y);
		return *this;
	}

	// An operator overload for adding a Vector2 instance to another Vector2 instance
	Vector2 operator + (const Vector2& v) {
		return Vector2(x + v.x, y + v.y);
	}
	// An operator overload for subtracting a Vector2 instance to another Vector2 instance
	Vector2 operator - (const Vector2& v) {
		return Vector2(x - v.x, y - v.y);
	}
	// An operator overload for multiplying a Vector2 instance by a scalar float value
	Vector2 operator * (const float& f) {
		return Vector2(x * f, y * f);
	}
	// An operator overload for unary negation of a Vector2 instance, e.g. -Vector2.
	Vector2 operator - () const
	{
		return Vector2(-x, -y);
	}
	// A static method Vector2::Dot which computes the dot product of two Vector2 instances.
	static float Dot(Vector2 v1, Vector2 v2) {
		return v1.x * v2.x + v1.y * v2.y;
	}
	// A method Vector2.Magnitude() to compute the magnitude of the Vector2 instance.
	float Magnitude() {
		return sqrtf(pow(x, 2) + pow(y, 2));
	}
	// A method Vector2.Normalize() to normalize the Vector2 instance.
	void Normalize() {
		if (x < 0) { x = -x; }
		if (y < 0) { y = -y; }
	}
	// A method Vector2.Normalized() to return a normalized copy of the Vector2 instance.
	Vector2 Normalized() {
		float nx;
		float ny;
		if (x < 0) { nx = -x; }
		if (y < 0) { ny = -y; }
		return Vector2(nx, ny);
	}
	static float Distance(Vector2 v1, Vector2 v2) {
		float xdist = v2.x - v1.x;
		float ydist = v2.y - v1.y;
		return sqrtf(pow(xdist, 2) + pow(ydist, 2));
	}
private:
	float x;
	float y;
};