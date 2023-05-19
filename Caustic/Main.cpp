#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

int main() 
{
	// Create Scene
	Caustic::Scene scene("resources/scene0.crtscene");

	// Render Image
	Caustic::Renderer::GenerateImage(scene, "Homework.ppm");

	// End program
	return 0;
}
