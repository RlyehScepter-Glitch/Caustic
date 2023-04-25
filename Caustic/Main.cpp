#include "Core/Ray.h"
#include "Core/Triangle.h"
#include "Core/Camera.h"
#include "glm/glm.hpp"

#include <fstream>
#include <math.h>

static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;

int main() 
{
	// Camera settings
	glm::vec3 cameraOrigin(0.0f, 0.0f, 0.0f);
	glm::vec3 cameraDirection(0.0f, 0.0f, -1.0f);
	glm::vec3 cameraUp(0.0f, 1.0f, 0.0f);
	float aspectRatio = 1920 / 1080;

	// Camera
	Caustic::Camera(cameraOrigin, cameraDirection, cameraUp, 80, aspectRatio);
	
	// Vertices
	glm::vec3 vertices[]
	{
		{ -1.0f, 0.0f, -2.0f },
		{  0.0f, 0.0f, -1.0f },
		{  1.0f, 0.0f, -2.0f },
		{  0.0f, 0.0f, -3.0f },
		{  0.0f, 1.0f, -2.0f }
	};

	// Triangles
	Caustic::Triangle triangles[]
	{
		{ vertices[1], vertices[2], vertices[5] },
		{ vertices[2], vertices[3], vertices[5] },
		{ vertices[3], vertices[4], vertices[5] },
		{ vertices[4], vertices[1], vertices[5] }
	};

	// Open Filestream
	std::ofstream ppmFileStream("HomeworkNo5.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	// Render image
	for (int y = 0; y < imageHeight; y++)
	{
		for (int x = 0; x < imageWidth; x++)
		{
			float tempX = x;
			float tempY = y;
			
			//Find center based on raster coordinates
			tempX += 0.5f;
			tempY += 0.5f;
			
			//Convert raster coordinates to NDC space [0.0, 1.0]
			tempX /= imageWidth;
			tempY /= imageHeight;
			
			//Convert NDC coordinates to Screen space [-1.0, 1.0]
			tempX = (2.0f * tempX) - 1.0f;
			tempY = 1.0f - (2.0f * tempY);
			
			//Aspect ratio
			tempX *= imageWidth / imageHeight;
			
			glm::vec3 rayDir(tempX, tempY, -1);
			rayDir = glm::normalize(rayDir);

			Caustic::Ray R(origin, rayDir);
			float t = 0.0f;

			if(T1.Intersect(R, t))
			{
				ppmFileStream << abs((int)t % 255) << " " << 0 << " " << 0 << "\t";
			}
			else if(T2.Intersect(R, t))
			{
				ppmFileStream << 0 << " " << abs((int)t % 255) << " " << 0 << "\t";
			}
			else if(T3.Intersect(R, t))
			{
				ppmFileStream << 0 << " " << 0 << " " << abs((int)t % 255) << "\t";
			}
			else if(T4.Intersect(R, t))
			{
				ppmFileStream << abs((int)t % 255) << " " << 0 << " " << abs((int)t % 255) << "\t";
			}
			else
			{
				ppmFileStream << abs(rayDir.x * 255) << " " << abs(rayDir.y * 255) << " " << abs(rayDir.z * 255) << "\t";
			}
		}

		ppmFileStream << "\n";
	}

	// Close Filestream
	ppmFileStream.close();

	// End program
	return 0;
}
