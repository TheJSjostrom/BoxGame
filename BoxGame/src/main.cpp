#include "src/Application.h"

static void CreateAndRunApp()
{
	BoxGame::Application app;
	app.Run();
}

int main()
{
	CreateAndRunApp();
}