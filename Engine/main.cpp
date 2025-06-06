////////////////////////////////////////////////////////////////////////////////
// Filename: main.cpp
////////////////////////////////////////////////////////////////////////////////
#include "System.h"


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pScmdline, int iCmdshow)
{
	CSystem* system;
	bool result;


	// Create the system object.
	system = new CSystem;

	// Initialize and run the system object.
	result = system->Initialize();
	if (result)
	{
		system->Run();
	}

	// Shutdown and release the system object.
	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}