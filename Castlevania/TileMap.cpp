#include "TileMap.h"
#include "Textures.h"

TileMap::TileMap()
{
	tileWidth = TILE_WIDTH;
	tileHeight = TILE_HEIGHT;
}

TileMap::TileMap(int _cols, int _rows, int _tileWidth, int _tileHeight)
{
	cols = _cols;
	rows = _rows;
	tileWidth = _tileWidth;
	tileHeight = _tileHeight;
	mapWidth = cols * tileWidth;
	mapHeight = rows * tileHeight;

	matrix = new int *[rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols];
	}
}

TileMap::~TileMap()
{
	if (matrix)
	{
		for (int i = 0; i < rows; i++)
		{
			delete matrix[i];
		}
		delete matrix;
		matrix = nullptr;
	}
}  

void TileMap::InitTileSet(Sprite * _tileSet)
{
	tileSet = _tileSet;
}

void TileMap::LoadMatrixMap(LPCSTR fileSource)
{
	fstream pFile;
	pFile.open(fileSource, fstream::in);

	string lineString;
	int * posSpace = NULL;
	string subString;
	int countLine = 0;
	int i = 0;

	while (pFile.good())
	{
		getline(pFile, lineString);
		if (countLine == 0)
		{
			cols = atoi(lineString.c_str());
		}
		else if (countLine == 1)
		{
			rows = atoi(lineString.c_str());

			matrix = new int *[rows];
			for (int row = 0; row < rows; row++)
			{
				matrix[row] = new int[cols];
			}
		}
		else
		{
			posSpace = new int[cols];
			for (int j = 0; j < cols; j++)
			{
				if (j == 0)
				{
					posSpace[0] = lineString.find(" ", 0);
					subString = lineString.substr(0, posSpace[0]);
					int id = atoi(subString.c_str());
					matrix[i][j] = id;
				}
				else
				{
					posSpace[j] = lineString.find(" ", posSpace[j - 1] + 1);
					subString = lineString.substr(posSpace[j - 1] + 1, posSpace[j] - (posSpace[j - 1] + 1));
					int id = atoi(subString.c_str());
					matrix[i][j] = id;
				}
			}
			i++;
		}
		countLine++;
	}

	mapWidth = cols * tileWidth;
	mapHeight = rows * tileHeight;
}

void TileMap::Draw(ViewPort *viewPort)
{
	RECT tileRect;
	D3DXVECTOR3 tilePos;
	D3DXVECTOR3 camPos = viewPort->GetCameraPos();

	D3DXVECTOR3 test = viewPort->ConvertPosInViewPort(D3DXVECTOR3(0, 0, 0));

	int cameraWidth = viewPort->GetCameraWidth();
	int cameraHeight = viewPort->GetCameraHeight();

	int colStart = (int)camPos.x / tileWidth;
	int colEnd = colStart + 16 < cols - 1 ? colStart + 16 : cols - 1;
	int rowStart = (int)(camPos.y) / tileHeight;
	int rowEnd = rowStart + 15 < rows - 1 ? rowStart + 15 : rows - 1;

	if (colStart >= 0 && rowStart > 0) 
	{
		for (int i = rowStart; i <= rowEnd; i++)
		{
			for (int j = colStart; j <= colEnd; j++)
			{
				//tileRect dung de lay ra RECT trong tile set de ve
				tileRect.left = (matrix[i][j] % 16) * tileWidth;
				tileRect.top = (matrix[i][j] / 16) * tileHeight;
				tileRect.right = tileRect.left + tileWidth;
				tileRect.bottom = tileRect.top + tileHeight;

				//tilePos la vi tri de ve tile len camera
				tilePos = viewPort->ConvertPosInViewPort(D3DXVECTOR3(j * tileWidth, i * tileHeight, 0));
				//cast pos to int-type to avoid tearing tilemap
				tileSet->Draw((short int)tilePos.x, (short int)tilePos.y, tileRect);
			}
		}
	}
}

