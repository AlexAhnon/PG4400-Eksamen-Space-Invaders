// main.cpp : Defines the entry point for the console application.
#include "GameManager.h"

int main(int argc, char *argv[])
{
	GameManager* gameManager = GameManager::getInstance();

	gameManager->Run();
	gameManager->Release();

	system("PAUSE");
	return EXIT_SUCCESS;
}