#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

int main() 
{
	// Create Scene
	Caustic::Scene scene("resources/scene5.crtscene");

	// Render Image
	Caustic::Renderer::GenerateImage(scene, "HomeworkDragon.ppm");

	// End program
	return 0;
}
