#include "Scene/Scene.h"
#include "Renderer/Renderer.h"

int main() 
{
	// Scene
	Caustic::Scene scene("resources/scene3.crtscene");
	Caustic::Renderer::GenerateImage(scene);

	// End program
	return 0;
}
