#include "Core/Ray.h"
#include "Core/Triangle.h"
#include "Core/Camera.h"
#include "Scene/Scene.h"

#include <fstream>
#include <iostream>
#include <rapidjson/rapidjson.h>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <algorithm>

static const int maxColorComponent = 255;
static const float shadowBias = 0.001f;

int main() 
{
	// Scene
	Caustic::Scene scene("resources/scene3.crtscene");
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
			tempX *= aspectRatio;

			glm::vec3 rayDir(tempX, tempY, -1);
			rayDir = (glm::mat3)scene.GetCamera().GetViewMatrix() * glm::normalize(rayDir);

			Caustic::Ray R(scene.GetCamera().GetPosition(), rayDir);
			float t = 0.0f;

			float tNear = FLT_MAX;
			uint32_t triangleIndex;
			glm::vec2 uv(0, 0);

			glm::vec3 backgroundColor(bgR, bgG, bgB);

			//-----Ray Triangle Intersection-----//
			// Check every Mesh for intersection with Camera Ray
			for (const Caustic::Mesh& mesh : scene.GetObjects())
			{
				if (mesh.Intersect(R, scene.GetCamera().GetNearClip(), tNear, triangleIndex, uv))
				{
					Caustic::Triangle triangle = mesh.GetTriangles()[triangleIndex];
					glm::vec3 hitPoint = R.GetOrigin() + R.GetDirection() * tNear;

					glm::vec3 finalColor(0.0f, 0.0f, 0.0f);

					// Check every light
					for (const Caustic::Light& light : scene.GetLights())
					{
						glm::vec3 lightDir = light.GetPosition() - hitPoint;
						float sphereRad = glm::length(lightDir);
						lightDir = glm::normalize(lightDir);
						float cosLaw = glm::max(0.0f, glm::dot(lightDir, triangle.GetNormal()));
						float sphereArea = 4.0f * glm::pi<float>() * sphereRad * sphereRad;

						float lightIntensity = light.GetIntensity();
						glm::vec3 triangleColor = triangle.GetColor();

						Caustic::Ray shadowRay(hitPoint + triangle.GetNormal() * shadowBias, lightDir);

						glm::vec3 lightContribution(0.0f);
						
						bool shadowRayIntersect = false;

						// Check if Shadow ray intersects anything
						for (const Caustic::Mesh& meshAgain : scene.GetObjects())
						{
							if (meshAgain.ShadowIntersect(shadowRay))
							{
								shadowRayIntersect = true;
								break;
							}							
						}

						if (shadowRayIntersect == false)
						{
							lightContribution = lightIntensity / sphereArea * triangleColor * cosLaw;
						}

						finalColor += lightContribution;
					}

					backgroundColor = finalColor;
				}
			}

			image[y][x] = backgroundColor;
		}

		
	}

	// Write the image to file
	for (uint32_t y = 0; y < sceneHeight; y++)
	{
		for (uint32_t x = 0; x < sceneWidth; x++)
		{
			glm::vec3 color = image[y][x];
			ppmFileStream << std::clamp(color.r * 255.0f, 0.0f, 255.0f) << " " << std::clamp(color.g * 255.0f, 0.0f, 255.0f) << " " << std::clamp(color.b * 255.0f, 0.0f, 255.0f) << " \t";
		}
		ppmFileStream << "\n";
	}

	// Close Filestream
	ppmFileStream.close();

	// End program
	return 0;
}
