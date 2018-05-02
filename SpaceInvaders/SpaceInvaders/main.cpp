// main.cpp : Defines the entry point for the console application.
#include "WindowManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	WindowManager* winManager = WindowManager::getInstance();

	winManager->SetupWindow();

	system("PAUSE");

	winManager->DeleteWindow();
	winManager->Release();

	return EXIT_SUCCESS;
}