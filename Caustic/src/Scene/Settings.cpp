#include "Settings.h"

namespace Caustic
{
	Settings::Settings(const glm::vec3& backgroundColor, uint32_t width, uint32_t height, uint32_t bucketSize)
		:m_BackgroundColor(backgroundColor), m_Width(width), m_Height(height), m_BucketSize(bucketSize)
	{
		m_AspectRatio = (float)width / (float)height;
	}

	void Settings::SetBackgroundColor(const glm::vec3& bgColor)
	{
		m_BackgroundColor = bgColor;
	}

	void Settings::SetWidth(uint32_t width)
	{
		m_Width = width;
	}

	void Settings::SetHeight(uint32_t height)
	{
		m_Height = height;
	}

	void Settings::BucketSize(uint32_t size)
	{
		m_BucketSize = size;
	}

	void Settings::SetGI(bool gi)
	{
		m_GlobalIllumination = gi;
	}

	void Settings::SetReflections(bool refl)
	{
		m_Reflections = refl;
	}

	void Settings::SetRefractions(bool refract)
	{
		m_Refractions = refract;
	}

	void Settings::UpdateAspectRatio()
	{
		m_AspectRatio = (float)m_Width / (float)m_Height;
	}

}