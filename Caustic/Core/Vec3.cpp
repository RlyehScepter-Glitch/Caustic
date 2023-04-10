#include "Vec3.h"

#include <math.h>

namespace Caustic
{
	float Vec3::Dot(const Vec3& v1, const Vec3& v2)
	{
		return (v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z);
	}

	Vec3 Vec3::Cross(const Vec3& v1, const Vec3& v2)
	{
		float cx = v1.y * v2.z - v1.z * v2.y;
		float cy = v1.z * v2.x - v1.x * v2.z;
		float cz = v1.x * v2.y - v1.y * v2.x;
		return Vec3(cx, cy, cz);
	}

	float Vec3::Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

	void Vec3::Normalize()
	{
		float len = Length();

		if(len != 0)
		{
			x /= len;
			y /= len;
			z /= len;
		}
	}

	float Vec3::Dot(const Vec3& other) const
	{
		return (x * other.x) + (y * other.y) + (z * other.z);
	}

	Vec3 Vec3::Cross(const Vec3& other) const
	{
		float cx = y * other.z - z * other.y;
		float cy = z * other.x - x * other.z;
		float cz = x * other.y - y * other.x;
		return Vec3(cx, cy, cz);
	}

	Vec3 Vec3::operator+(const Vec3& other) const
	{
		return Vec3(x + other.x, y + other.y, z + other.z);
	}

	Vec3 Vec3::operator-(const Vec3& other) const
	{
		return Vec3(x - other.x, y - other.y, z - other.z);
	}

	Vec3 Vec3::operator*(float scalar) const
	{
		return Vec3(x * scalar, y + scalar, z * scalar);
	}

	Vec3 Vec3::operator/(float scalar) const
	{
		return Vec3(x / scalar, y / scalar, z / scalar);
	}

	Vec3& Vec3::operator+=(const Vec3& other)
	{
		x += other.x;
		y += other.y;
		z += other.z;

		return *this;
	}

	Vec3& Vec3::operator-=(const Vec3& other)
	{
		x -= other.x;
		y -= other.y;
		z -= other.z;

		return *this;
	}

	Vec3& Vec3::operator*=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vec3& Vec3::operator/=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}
}