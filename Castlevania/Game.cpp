#include "Game.h"


Game * Game::__instance = NULL;

Game::Game()
{
}

Game::~Game()
{

}

Game *Game::GetInstance()
{
	if (__instance == NULL) __instance = new Game();
	return __instance;
}


bool Game::Initialize(HWND hWnd)
{
	this->hWnd = hWnd;

	if (!Graphics::GetInstance()->Initialize(this->hWnd, GAME_WINDOWED) || !InputDevice::GetInstance()->Initialize(this->hWnd))
	{
		return false;
	}

	//Database::GetInstance()->LoadTexture();
	//Database::GetInstance()->CreateSprite();
	//Database::GetInstance()->CreateAnimation();

	ViewPort::GetInstance()->SetCameraSize(256, 240);
	ViewPort::GetInstance()->SetCameraPos(D3DXVECTOR3(0, ViewPort::GetInstance()->GetCameraHeight(), 0));

	Textures::GetInstance()->Add(0, "Resource\\Map\\Charleston_2_tileset.png", D3DCOLOR_XRGB(0, 0, 0));

	map = new TileMap();
	map->LoadMatrixMap("Resource\\Map\\Charleston_2_tileset_bg.txt");
	map->InitTileSet(new Sprite(0, 0, 0, 256, 80, Textures::GetInstance()->GetTexture(0)));
	return true;
}

void Game::Update(DWORD gameTime)
{
	//SceneManager::GetInstance()->Update(gameTime);
	InputDevice::GetInstance()->ProcessKeyBoard();
}

void Game::Render(DWORD gameTime)
{
	Graphics::GetInstance()->Clear(D3DCOLOR_XRGB(0, 0, 0));

	if (Graphics::GetInstance()->Begin())
	{
		Graphics::GetInstance()->device->ColorFill(Graphics::GetInstance()->GetBackBuffer(), NULL, D3DCOLOR_XRGB(0, 0, 0));

		//SceneManager::GetInstance()->GetCurrentScene()->Draw();
		map->Draw(ViewPort::GetInstance());

		Graphics::GetInstance()->End();
	}

	Graphics::GetInstance()->Present(); // !!!
	
}

void Game::Run()
{
	MSG msg;
	int done = 0;
	DWORD frameStart = GetTickCount();
	DWORD tickPerFrame = 1000 / FRAMERATE;

	while (!done)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			if (msg.message == WM_QUIT) done = 1;

			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		DWORD now = GetTickCount();

		// dt: the time between (beginning of last frame) and now
		// this frame: the frame we are about to render
		DWORD dt = now - frameStart;

		if (dt >= tickPerFrame)
		{
			frameStart = now;

			Update(dt);

			Render(dt);
		}
		else
			Sleep(tickPerFrame - dt);
	}
}
