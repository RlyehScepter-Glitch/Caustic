#include "Core/Vec3.h"
#include "Core/Ray.h"
#include "Core/Triangle.h"

#include <fstream>
#include <math.h>

static const int imageWidth = 1920;
static const int imageHeight = 1080;

static const int maxColorComponent = 255;

int main() 
{
	std::ofstream ppmFileStream("HomeworkNo5.ppm", std::ios::out | std::ios::binary);
	ppmFileStream << "P3\n";
	ppmFileStream << imageWidth << " " << imageHeight << "\n";
	ppmFileStream << maxColorComponent << "\n";

	Caustic::Vec3 origin(0.0f, 0.5f, 0.0f);
	Caustic::Vec3 P1(-1.0f, 0.0f, -2.0f);
	Caustic::Vec3 P2(0.0f, 0.0f, -1.0f);
	Caustic::Vec3 P3(1.0f, 0.0f, -2.0f);
	Caustic::Vec3 P4(0.0f, 0.0f, -3.0f);
	Caustic::Vec3 P5(0.0f, 1.0f, -2.0f);

	Caustic::Triangle T1(P1, P2, P5);
	Caustic::Triangle T2(P2, P3, P5);
	Caustic::Triangle T3(P3, P4, P5);
	Caustic::Triangle T4(P4, P1, P5);

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
				ppmFileStream << abs(rayDir.GetX() * 255) << " " << abs(rayDir.GetY() * 255) << " " << abs(rayDir.GetZ() * 255) << "\t";
			}
		}

		ppmFileStream << "\n";
	}

	ppmFileStream.close();

	return 0;
}
