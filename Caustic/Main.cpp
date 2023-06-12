#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

int main() 
{
	// Create Scene
	Caustic::Scene scene("resources/scene1.crtscene");

	// Render Image
	Caustic::Renderer::GenerateImage(scene, "Homework.ppm");
	std::cout << "Scene done \n";

	// End program
	return 0;
}
