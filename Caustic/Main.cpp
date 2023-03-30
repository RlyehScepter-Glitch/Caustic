#include "Vec3.h"
#include "Ray.h"

#include <fstream>
#include <math.h>

static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;

int main() 
{
	std::ofstream ppmFileStream("CRT_Homework_3.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	Caustic::Vec3 origin(0, 0, 0);

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

			Caustic::Vec3 rayDir(tempX, tempY, -1);
			rayDir.Normalize();

			ppmFileStream << abs(rayDir.getX() * 255) << " " << abs(rayDir.getY() * 255) << " " << abs(rayDir.getZ() * 255) << "\t";
		}

		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}
