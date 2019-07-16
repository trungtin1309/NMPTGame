#pragma once
#include <fstream>
#include <sstream>
#include <d3dx9.h>
#include <string.h>
#include "Sprites.h"
#include "ViewPort.h"

#define TILE_WIDTH 16
#define TILE_HEIGHT 16

class TileMap
{
private:
	int ** matrix; // map data
	int cols, rows; // cols and rows of our map
	int tileWidth, tileHeight;
	int mapWidth, mapHeight;

	Sprite * tileSet;

public:
	TileMap();
	TileMap(int _cols, int _rows, int _tileWidth, int _tileHeight);
	~TileMap();
	void InitTileSet(Sprite * _tileSet);
	void LoadMatrixMap(LPCSTR fileSource);
	void Draw(ViewPort *viewPort);
};

