#include "SceneManager.h"

SceneManager * SceneManager::instance = NULL;

SceneManager::SceneManager()
{

}

SceneManager::~SceneManager()
{
}

Scene * SceneManager::GetCurrentScene()
{
	return currentScene;
}

SceneManager * SceneManager::GetInstance()
{
	if (!instance)
	{
		instance = new SceneManager();
	}
	return instance;
}

bool SceneManager::Initialze(HWND hWnd)
{
	return true;
}



void SceneManager::Update(DWORD dt)
{
	currentScene->Update(dt);

	if (currentScene->GetChangingState())
	{
		this->MoveToNextScene();
		this->LoadScene(sceneID);
	}
}


void SceneManager::LoadScene(int sceneID)
{
	

}

void SceneManager::MoveToNextScene()
{
	sceneID++;
}