#include"Engine.h"

using CHINSTANCE = const HINSTANCE__*;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, [[maybe_unused]] _In_opt_  HINSTANCE  hPrevInstance, [[maybe_unused]] _In_  LPWSTR lpCmdLine, [[maybe_unused]] _In_ int nCmdShow)
{
	HRESULT hr = CoInitialize(nullptr);   // needed for textures to work
	if (FAILED(hr))
	{
		ErrorLogger::errorLog(hr, "CoInitialize failed");
	}
	// start engine
	Engine engine;
	engine.Initialize(hInstance, "Title", "Class", 1080, 1080);	
	while (engine.ProcessMessages())	
	{
		engine.Update();			
		engine.RenderFrame();		
	}
	return 0;
}