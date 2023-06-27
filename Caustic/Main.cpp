#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

#include <chrono>

int main() 
{
	// Create Scene
	Caustic::Scene scene("resources/scene1.crtscene");

	std::chrono::high_resolution_clock::time_point start = std::chrono::high_resolution_clock::now();

	// Render Image
	Caustic::Renderer::GenerateImage(scene, "Homework.ppm");
	
	std::chrono::high_resolution_clock::time_point stop = std::chrono::high_resolution_clock::now();

	std::chrono::microseconds duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
	const double seconds = duration.count() / 1000000.0;
	
	std::cout << "Scene done in " << seconds << " seconds.\n";
		
	// End program
	return 0;
}
