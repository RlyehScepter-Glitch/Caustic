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

//TODO: REWRITE RAY-TRIANGLE INTERSECTION METHOD

int main() 
{
	// Scene
	Caustic::Scene scene("resources/scene2.crtscene");
	Caustic::Settings sceneSettings = scene.GetSettings();
	uint32_t sceneWidth = sceneSettings.GetWidth();
	uint32_t sceneHeight = sceneSettings.GetHeight();
	float aspectRatio = sceneWidth / sceneHeight;
	glm::vec3 background = scene.GetSettings().GetBackgroundColor();
	float bgR = background.r;
	float bgG = background.g;
	float bgB = background.b;

	// Open Filestream
	std::ofstream ppmFileStream("Homework.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << sceneWidth << " " << sceneHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	// Render image
	for (uint32_t y = 0; y < sceneHeight; y++)
	{
		for (uint32_t x = 0; x < sceneWidth; x++)
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
			
			bool hitTriangle = false;
			bool hitMesh = false;

			for (const Caustic::Mesh& mesh : scene.GetObjects())
			{
				if(hitMesh)
				{
					break;
				}

				for (const Caustic::Triangle& triangle : mesh.GetTriangles())
				{
					if(triangle.Intersect(R, t))
					{
						ppmFileStream << triangle.GetColor().r * 255 << " " << triangle.GetColor().g * 255 << " " << triangle.GetColor().b * 255 << " \t";
						hitTriangle = true;
						hitMesh = true;
						break;
					}
					
				}

				if(hitTriangle)
				{
					hitTriangle = false;
					break;
				}
				
			}
			
			if (!hitMesh)
			{
				ppmFileStream << bgR * 255 << " " << bgG * 255 << " " << bgB * 255 << " \t";
			}
			
		}

		ppmFileStream << "\n";
	}

	// Close Filestream
	ppmFileStream.close();

	// End program
	return 0;
}
