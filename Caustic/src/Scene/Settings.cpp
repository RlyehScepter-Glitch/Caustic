#include "Settings.h"

namespace Caustic
{
	Settings::Settings(const glm::vec3& backgroundColor, uint32_t width, uint32_t height)
		:m_BackgroundColor(backgroundColor), m_Width(width), m_Height(height)
	{}
}