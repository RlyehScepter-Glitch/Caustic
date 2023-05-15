#include "Core/Ray.h"
#include "Core/Triangle.h"
#include "Core/Camera.h"
#include "Scene/Scene.h"

#include <fstream>
#include <iostream>
#include <rapidjson/rapidjson.h>
#include <glm/glm.hpp>
#include <math.h>

static const int maxColorComponent = 255;

int main() 
{
	// Scene
	Caustic::Scene scene("resources/scene4.crtscene");
	Caustic::Settings sceneSettings = scene.GetSettings();
	uint32_t sceneWidth = sceneSettings.GetWidth();
	uint32_t sceneHeight = sceneSettings.GetHeight();
	float aspectRatio = (float)sceneWidth / (float)sceneHeight;
	glm::vec3 background = scene.GetSettings().GetBackgroundColor();
	float bgR = background.r;
	float bgG = background.g;
	float bgB = background.b;

	// Open Filestream
	std::ofstream ppmFileStream("HomeworkDragon.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << sceneWidth << " " << sceneHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	// Create a two-dimensional array to represent the image
	std::vector<std::vector<glm::vec3>> image(sceneHeight, std::vector<glm::vec3>(sceneWidth));

	// Render image
	for (uint32_t y = 0; y < sceneHeight; y++)
	{
		for (uint32_t x = 0; x < sceneWidth; x++)
		{
			//-----Ray Generation----//
			float tempX = x;
			float tempY = y;

			//Find center based on raster coordinates
			tempX += 0.5f;
			tempY += 0.5f;

			//Convert raster coordinates to NDC space [0.0, 1.0]
			tempX /= sceneWidth;
			tempY /= sceneHeight;

			//Convert NDC coordinates to Screen space [-1.0, 1.0]
			tempX = (2.0f * tempX) - 1.0f;
			tempY = 1.0f - (2.0f * tempY);

			//Aspect ratio
			tempX *= sceneWidth / sceneHeight;

			glm::vec3 rayDir(tempX, tempY, -1);
			rayDir = (glm::mat3)scene.GetCamera().GetViewMatrix() * glm::normalize(rayDir);

			Caustic::Ray R(scene.GetCamera().GetPosition(), rayDir);
			float t = 0.0f;

			float tNear = FLT_MAX;
			uint32_t triangleIndex;
			glm::vec2 uv(0, 0);

			glm::vec3 color(bgR, bgG, bgB);

			//-----Ray Triangle Intersection-----//
			for (const Caustic::Mesh& mesh : scene.GetObjects())
			{
				if (mesh.Intersect(R, scene.GetCamera().GetNearClip(), tNear, triangleIndex, uv))
				{
					Caustic::Triangle triangle = mesh.GetTriangles()[triangleIndex];
					color = triangle.GetColor();
				}
			}

			image[y][x] = color;
		}

		
	}

	// Write the image to file
	for (uint32_t y = 0; y < sceneHeight; y++)
	{
		for (uint32_t x = 0; x < sceneWidth; x++)
		{
			glm::vec3 color = image[y][x];
			ppmFileStream << color.r * 255 << " " << color.g * 255 << " " << color.b * 255 << " \t";
		}
		ppmFileStream << "\n";
	}

	// Close Filestream
	ppmFileStream.close();

	// End program
	return 0;
}
