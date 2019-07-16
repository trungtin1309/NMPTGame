#pragma once
#include "Scene.h"

class SceneManager
{
private:
	static SceneManager * instance;
	Scene * currentScene;
	int sceneID;

public:
	static SceneManager * GetInstance();
	SceneManager();
	~SceneManager();

	bool Initialze(HWND hWnd);

	void LoadScene(int sceneID);

	void MoveToNextScene();

	void Update(DWORD dt);

	Scene * GetCurrentScene();
};

