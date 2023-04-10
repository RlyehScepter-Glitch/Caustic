#pragma once

namespace Caustic
{
	
	class Vec3 
	{
	public:
		//Constructors
		Vec3() : x(0), y(0), z(0) {}
		Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

		//Getters
		float getX() const { return x; }
		float getY() const { return y; }
		float getZ() const { return z; }

		//Setters
		void setX(float x) { this->x = x; }
		void setY(float y) { this->y = y; }
		void setZ(float z) { this->z = z; }

		//Static vector operations
		static float Dot(const Vec3& v1, const Vec3& v2);
		static Vec3 Cross(const Vec3& v1, const Vec3& v2);

		//Vector operations
		float Length() const;
		void Normalize();
		float Dot(const Vec3& other) const;
		Vec3 Cross(const Vec3& other) const;

		Vec3 operator+(const Vec3& other) const;
		Vec3 operator-(const Vec3& other) const;
		Vec3 operator*(float scalar) const;
		Vec3 operator/(float scalar) const;

		Vec3& operator+=(const Vec3& other);
		Vec3& operator-=(const Vec3& other);
		Vec3& operator*=(float scalar);
		Vec3& operator/=(float scalar);

	private:
		float x, y, z;
	};

}