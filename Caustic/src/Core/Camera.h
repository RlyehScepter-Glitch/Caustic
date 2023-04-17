#pragma once

#include "Vec3.h"
#include "Mat4.h"
#include "Ray.h"

namespace Caustic
{

	class Camera
	{
	public:
		Camera(const Vec3& position, const Vec3& direction);
		Camera(const Vec3& position, const Vec3& direction, const Vec3& up);
	private:
	};

}