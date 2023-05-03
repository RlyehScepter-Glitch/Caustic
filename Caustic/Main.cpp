#include "src/Core/Ray.h"
#include "src/Core/Triangle.h"
#include "src/Core/Camera.h"
#include "src/Core/Renderer.h"
#include "src/Scene/Scene.h"

#include <fstream>
#include <rapidjson/rapidjson.h>
#include <glm/glm.hpp>
#include <math.h>

static const int maxColorComponent = 255;

int main() 
{
	// Scene
	Caustic::Scene scene("resources/scene0.crtscene");
	Caustic::Settings sceneSettings = scene.GetSettings();
	uint32_t sceneWidth = sceneSettings.GetWidth();
	uint32_t sceneHeight = sceneSettings.GetHeight();
	float aspectRatio = sceneWidth / sceneHeight;
	glm::vec3 background = scene.GetSettings().GetBackgroundColor();

	// Open Filestream
	std::ofstream ppmFileStream("Homework.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << sceneWidth << " " << sceneHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	// Render image
	for (int y = 0; y < sceneHeight; y++)
	{
		for (int x = 0; x < sceneWidth; x++)
		{
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
			rayDir = glm::normalize(rayDir);

			Caustic::Ray R(scene.GetCamera().GetPosition(), rayDir);
			float t = 0.0f;
			
			for (auto mesh : scene.GetObjects())
			{
				for (auto triangle : mesh.GetTriangles())
				{
					if(triangle.Intersect(R, t))
					{
						ppmFileStream << 200 << " " << 200 << " " << 0 << "\t";
					}
					else
					{
						ppmFileStream << background.r << " " << background.g << " " << background.b << "\t";
					}
				}
			}

			//ppmFileStream << R << " " << G << " " << B << "\t";
		}

		ppmFileStream << "\n";
	}

	// Close Filestream
	ppmFileStream.close();

	// End program
	return 0;
}
