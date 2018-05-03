// main.cpp : Defines the entry point for the console application.
#include "GameManager.h"

using namespace std;

int main(int argc, char *argv[])
{
	GameManager* gameManager = GameManager::getInstance();

	gameManager->Initialize();
	gameManager->Update();
	gameManager->Release();

	return EXIT_SUCCESS;
}