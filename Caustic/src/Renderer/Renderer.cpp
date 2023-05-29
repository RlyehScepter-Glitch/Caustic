#include "Renderer.h"

#include <fstream>
#include <iostream>
#include <algorithm>
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>

static const uint32_t maxColorComponent = 255;
static const float shadowBias = 0.1f;
static const uint32_t maxRayDepth = 5;

namespace Caustic
{
	void Renderer::GenerateImage(const Scene& scene, const std::string& fileName)
	{
		// Scene Settings
		Caustic::Settings sceneSettings = scene.GetSettings();
		uint32_t sceneWidth = sceneSettings.GetWidth();
		uint32_t sceneHeight = sceneSettings.GetHeight();
		glm::mat3 viewMatrix = (glm::mat3)scene.GetCamera().GetViewMatrix();

		// Open Filestream
		std::ofstream ppmFileStream(fileName, std::ios::out | std::ios::binary);
		ppmFileStream << "P3\n";
		ppmFileStream << sceneWidth << " " << sceneHeight << "\n";
		ppmFileStream << maxColorComponent << "\n";

		// Create a two-dimensional array to represent the image
		std::vector<std::vector<glm::vec3>> image(sceneHeight, std::vector<glm::vec3>(sceneWidth));

		// Fill in image data
		for (uint32_t y = 0; y < sceneHeight; y++)
		{
			for (uint32_t x = 0; x < sceneWidth; x++)
			{
				// Ray Generation
				Ray R = Renderer::GenerateCameraRay(x, y, scene);

				// Trace Ray
				IntersectionData data = scene.TraceRay(R);

				// Shade Pixel
				image[y][x] = Renderer::Shade(R, data, scene);
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
	}
	
	Ray Renderer::GenerateCameraRay(const uint32_t& x, const uint32_t& y, const Scene& scene)
	{
		//-----Ray Generation----//
		float tempX = x;
		float tempY = y;

		//Find center based on raster coordinates
		tempX += 0.5f;
		tempY += 0.5f;

		//Convert raster coordinates to NDC space [0.0, 1.0]
		tempX /= scene.GetSettings().GetWidth();
		tempY /= scene.GetSettings().GetHeight();

		//Convert NDC coordinates to Screen space [-1.0, 1.0]
		tempX = (2.0f * tempX) - 1.0f;
		tempY = 1.0f - (2.0f * tempY);

		//Aspect ratio
		tempX *= scene.GetSettings().GetAspectRatio();

		glm::vec3 rayDir(tempX, tempY, -1);
		rayDir = (glm::mat3)scene.GetCamera().GetViewMatrix() * glm::normalize(rayDir);

		Caustic::Ray ray(scene.GetCamera().GetPosition(), rayDir, RayType::camera);

		return ray;
	}
	
	glm::vec3 Renderer::Shade(const Ray& ray, const IntersectionData& data, const Scene& scene)
	{
		glm::vec3 finalColor(0.0f, 0.0f, 0.0f);
		if (ray.GetDepth() >= maxRayDepth || data.triangleIdx == -1)
		{
			float depthMulti = 1.0f - 0.2f * ray.GetDepth();
			finalColor = scene.GetSettings().GetBackgroundColor() * depthMulti;
			return finalColor;
		}

		Material mat = scene.GetMaterials()[data.materialIdx];

		if(mat.GetMaterialType() == MaterialType::diffuse)
		{
			finalColor = ShadeDiffuse(ray, data, scene);
		}
		else if (mat.GetMaterialType() == MaterialType::reflective)
		{
			finalColor = ShadeReflective(ray, data, scene);
		}
		else if (mat.GetMaterialType() == MaterialType::refractive)
		{
			//TBI
			finalColor = ShadeRefractive(ray, data, scene);
		}
		else if (mat.GetMaterialType() == MaterialType::constant)
		{
			//TBI
			finalColor = ShadeConstant(ray, data, scene);
		}
		else
		{
			assert(false);
		}

		return finalColor;
	}
	
	glm::vec3 Renderer::ShadeDiffuse(const Ray& ray, const IntersectionData& data, const Scene& scene)
	{
		float u = data.UV.x;
		float v = data.UV.y;
		float w = 1 - data.UV.x - data.UV.y;

		// Color Based on UV
		//glm::vec3 triangleColor(u, v, w);
		// Flat Color
		//glm::vec3 triangleColor(0.8f, 0.0f, 0.3f);
		// Internal Triangle Color
		glm::vec3 triangleColor = scene.GetObjects()[data.objectIdx].GetTriangles()[data.triangleIdx].GetColor();

		glm::vec3 diffuseColor(0.0f, 0.0f, 0.0f);

		for (const Caustic::Light& light : scene.GetLights())
		{
			glm::vec3 lightDir;
			glm::vec3 originOffset;
			float cosLaw;
			float sphereRad;

			if (scene.GetMaterials()[data.materialIdx].SmoothShading())
			{
				lightDir = light.GetPosition() - data.hitPoint;
				sphereRad = glm::length(lightDir);
				lightDir = glm::normalize(lightDir);
				cosLaw = glm::max(0.0f, glm::dot(lightDir, data.interpolatedVertexNormal));
				originOffset = data.hitPoint + data.interpolatedVertexNormal * shadowBias;
			}
			else
			{
				lightDir = light.GetPosition() - data.hitPoint;
				sphereRad = glm::length(lightDir);
				lightDir = glm::normalize(lightDir);
				cosLaw = glm::max(0.0f, glm::dot(lightDir, data.hitPointNormal));
				originOffset = data.hitPoint + data.hitPointNormal * shadowBias;
			}
			
			float lightIntensity = light.GetIntensity();

			Caustic::Ray shadowRay(originOffset, lightDir, RayType::shadow);

			float sphereArea = 4.0f * glm::pi<float>() * sphereRad * sphereRad;

			glm::vec3 lightContribution(0.0f, 0.0f, 0.0f);

			// Check if Shadow ray intersects anything
			IntersectionData shadowData = scene.TraceRay(shadowRay);
			
			if(shadowData.triangleIdx == -1)
			{
				lightContribution = lightIntensity / sphereArea * triangleColor * cosLaw;
			}

			diffuseColor += lightContribution;
		}

		return diffuseColor;
	}

	glm::vec3 Renderer::ShadeReflective(const Ray& ray, const IntersectionData& data, const Scene& scene)
	{
		bool smoothShading = scene.GetMaterials()[data.materialIdx].SmoothShading();

		glm::vec3 originOffset;
		glm::vec3 N;
		glm::vec3 A = ray.GetDirection();

		if(smoothShading)
		{
			originOffset = data.interpolatedVertexNormal * shadowBias;
			N = data.interpolatedVertexNormal;
		}
		else
		{
			originOffset = data.hitPointNormal * shadowBias;
			N = data.hitPointNormal;
		}
		
		glm::vec3 reflOrigin = data.hitPoint + originOffset;
		glm::vec3 reflDir = A - 2 * glm::dot(A, N) * N;
		
		Ray reflRay(reflOrigin, reflDir, RayType::reflection, ray.GetDepth() + 1);
		IntersectionData reflData = scene.TraceRay(reflRay);
		glm::vec3 reflectColor = Shade(reflRay, reflData, scene);

		return reflectColor;
	}
	
	glm::vec3 Renderer::ShadeRefractive(const Ray& ray, const IntersectionData& data, const Scene& scene)
	{
		return glm::vec3();
	}
	
	glm::vec3 Renderer::ShadeConstant(const Ray& ray, const IntersectionData& data, const Scene& scene)
	{
		return glm::vec3();
	}
}