#include "stdafx.h"
#include "mapTool.h"


mapTool::mapTool()
{
}


mapTool::~mapTool()
{

}


HRESULT mapTool::init()
{
	IMAGEMANAGER->addImage("selectBox", ".\\images\\selectBox.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectBoxSmall", ".\\images\\objectBoxSmall.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("objectBoxLarge", ".\\images\\objectBoxLarge.bmp", 32, 32, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("selectButton", ".\\images\\selectButton.bmp", 100, 20, true, RGB(255, 0, 255));
	for (int i = 0; i < MAXTILENUM; ++i)
	{
		_vTileImage.push_back(addImageInfo(i));
		IMAGEMANAGER->addFrameImage(_vTileImage[i].keyName, _vTileImage[i].directory, _vTileImage[i].imageWidth, _vTileImage[i].imageHeight, _vTileImage[i].imageFrameX, _vTileImage[i].imageFrameY, true, RGB(255, 0, 255));
	}
	_cameraX = 0; 
	_cameraY = 0;
	_pageX = 0;
	_pageY = 0;
	_selectTileNumX = 0;
	_selectTileNumY = 0;
	_frameCounter = 0;
	_currentFrameX = 0;
	_currentTileMapNum = 0;
	_isFrameTile = false;
	_isBlocked = false;
	_isObjectTile = false;
	_isDeleteTile = false;

	return S_OK;
}

HRESULT mapTool::initWorldMap()
{
	load(".\\mapFiles\\worldMap.map");
	IMAGEMANAGER->addFrameImage(_vTileImage[0].keyName, _vTileImage[0].directory, _vTileImage[0].imageWidth, _vTileImage[0].imageHeight, _vTileImage[0].imageFrameX, _vTileImage[0].imageFrameY, true, RGB(255, 0, 255));
	_frameCounter = 0;
	_currentFrameX = 0;
	return S_OK;
}

HRESULT mapTool::initS1()
{
	load(".\\mapFiles\\stage1test.map");
	IMAGEMANAGER->addFrameImage(_vTileImage[1].keyName, _vTileImage[1].directory, _vTileImage[1].imageWidth, _vTileImage[1].imageHeight, _vTileImage[1].imageFrameX, _vTileImage[1].imageFrameY, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("Tile1p", ".\\images\\Tile1P3.bmp", 1536, 2816, 12, 22, true, RGB(255, 0, 255));
	_frameCounter = 0;
	_currentFrameX = 0;
	return S_OK;
}

void mapTool::release()
{

}

void mapTool::update() 
{
	keyControl();
	frameUpdate();
}

void mapTool::render() 
{
	drawTile();
	drawMenu();
}

void mapTool::drawTile()
{
	int tileWidth = _vTileImage[_currentTileMapNum].tileWidth;
	int mapTileWidth = 32;
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 16; ++j)
		{
			_miMapTile = _mMapTile.find((1000 + i + _cameraX) * 1000 + j + _cameraY);
			if (_miMapTile == _mMapTile.end())
			{
				Rectangle(getMemDC(), i * mapTileWidth, j * mapTileWidth, i * mapTileWidth + mapTileWidth, j * mapTileWidth + mapTileWidth);
			}
			else if (i >= 0 && i < 16 && j >= 0 && j < 16)
			{
				if (_miMapTile->second.first > 0)
				{
					if ((_miMapTile->second.first / 100000) % 10 == true) //isFrameTile == true
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].keyName, getMemDC(),
							i * mapTileWidth, j * mapTileWidth,
							(_miMapTile->second.first / 100) % 100 + _currentFrameX,
							_miMapTile->second.first % 100,
							_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
							mapTileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth);
					}
					else
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].keyName, getMemDC(),
							i * mapTileWidth, j * mapTileWidth,
							(_miMapTile->second.first / 100) % 100,
							_miMapTile->second.first % 100,
							_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
							mapTileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth);
					}
				}
				if (_miMapTile->second.second > 0)
				{
					if ((_miMapTile->second.second / 100000) % 10 == true) //isFrameTile == true
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].keyName, getMemDC(),
							i * mapTileWidth, j * mapTileWidth,
							(_miMapTile->second.second / 100) % 100 + _currentFrameX,
							_miMapTile->second.second % 100,
							_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].imageFrameSpace,
							mapTileWidth, _vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].tileWidth);
					}
					else
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].keyName, getMemDC(),
							i * mapTileWidth, j * mapTileWidth,
							(_miMapTile->second.second / 100) % 100,
							_miMapTile->second.second % 100,
							_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].imageFrameSpace,
							mapTileWidth, _vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].tileWidth);
					}
				}
				if (_miMapTile->second.first / 10000 % 10 == true || _miMapTile->second.second / 10000 % 10 == true) // _isBlocked == true
				{
					if (_isBlocked == true) IMAGEMANAGER->findImage("objectBoxLarge")->render(getMemDC(), i * mapTileWidth, j * mapTileWidth);
					else IMAGEMANAGER->findImage("objectBoxSmall")->render(getMemDC(), i * mapTileWidth, j * mapTileWidth);
				}
			}
		}
	}
	for (int i = 0; i < 16; ++i)
	{
		for (int j = 0; j < 20; ++j)
		{
			if (i + _pageX * 16 >= _vTileImage[_currentTileMapNum].imageFrameX || j + _pageY * 20 >= _vTileImage[_currentTileMapNum].imageFrameY)
			{
				continue;
			}
			IMAGEMANAGER->renderTile(_vTileImage[_currentTileMapNum].keyName, getMemDC(), 512 + i * mapTileWidth, j * mapTileWidth, i + _pageX * 16, j + _pageY * 20, _vTileImage[_currentTileMapNum].imageFrameSpace, mapTileWidth, tileWidth);
		}
	}
	IMAGEMANAGER->findImage("selectBox")->enlargeRender(getMemDC(), 512 + _selectTileNumX * mapTileWidth, _selectTileNumY * mapTileWidth, mapTileWidth, mapTileWidth);
	
	char pageNum[128];
	char cameraNum[128];
	char mouseTileNum[128];
	char mouseMapNum[128];
	wsprintf(pageNum, "PageX : %d, PageY : %d", _pageX, _pageY);
	wsprintf(cameraNum, "MapX : %d, MapY : %d", _cameraX, _cameraY);
	wsprintf(mouseTileNum, "MouseX : %d, MouseY : %d", (_ptMouse.x - 512) / tileWidth + _pageX * (512 / tileWidth), _ptMouse.y / tileWidth + _pageY * (640 / tileWidth));
	wsprintf(mouseMapNum, "MouseX : %d, MouseY : %d", _ptMouse.x / tileWidth + _cameraX, _ptMouse.y / tileWidth + _cameraY);
	TextOut(getMemDC(), 640, 640, "(Num4)pageX--", strlen("(Num4)pageX--"));
	TextOut(getMemDC(), 640, 660, "(Num6)pageX++", strlen("(Num6)pageX++"));
	TextOut(getMemDC(), 640, 680, "(Num8)pageY--", strlen("(Num8)pageY--"));
	TextOut(getMemDC(), 640, 700, "(Num5)pageY++", strlen("(Num5)pageY++"));
	TextOut(getMemDC(), 800, 640, pageNum, strlen(pageNum));
	TextOut(getMemDC(), 800, 660, mouseTileNum, strlen(mouseTileNum));
	TextOut(getMemDC(), 800, 680, "(Num7)Next Tile", strlen("(Num7)Next Tile"));
	TextOut(getMemDC(), 800, 700, "(Num9)Prev Tile", strlen("(Num9)Prev Tile"));
	TextOut(getMemDC(), 5, 528, "Control : ← → ↑ ↓", strlen("Control : ← → ↑ ↓"));
	TextOut(getMemDC(), 200, 528, cameraNum, strlen(cameraNum));
	TextOut(getMemDC(), 200, 553, mouseMapNum, strlen(mouseMapNum));
}

void mapTool::drawTile(int playerX, int playerY, int tileWidth, bool pixelCollision)
{
	int screenLeft = playerX - WINSIZEX / 2;
	int screenTop = playerY - WINSIZEY / 2;
	int cameraX = screenLeft / tileWidth;
	int cameraY = screenTop / tileWidth;
	int xLeft = screenLeft % tileWidth;
	int yLeft = screenTop % tileWidth;
	for (int i = 0; i < WINSIZEX / tileWidth + 1; ++i)
	{
		for (int j = 0; j < WINSIZEY / tileWidth + 1; ++j)
		{
			_miMapTile = _mMapTile.find((1000 + i + cameraX) * 1000 + j + cameraY);
			if (_miMapTile != _mMapTile.end() && i + cameraX >= 0 && j + cameraY >= 0)
			{
				if (_miMapTile->second.first > 0)
				{
					if ((_miMapTile->second.first / 100000) % 10 == true) //isFrameTile == true
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].keyName, getMemDC(),
							i * tileWidth - xLeft, j * tileWidth - yLeft,
							(_miMapTile->second.first / 100) % 100 + _currentFrameX,
							_miMapTile->second.first % 100,
							_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
							tileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth);
						if (pixelCollision == true)
						{
							IMAGEMANAGER->renderPixelTile("Tile1p", getPixelDC(),
								i * tileWidth - xLeft, j * tileWidth - yLeft,
								(_miMapTile->second.first / 100) % 100,
								_miMapTile->second.first % 100,
								_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
								tileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth, RGB(0, 0, 0));
						}
					}
					else
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].keyName, getMemDC(),
							i * tileWidth - xLeft, j * tileWidth - yLeft,
							(_miMapTile->second.first / 100) % 100,
							_miMapTile->second.first % 100,
							_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
							tileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth);
						if (pixelCollision == true)
						{
							IMAGEMANAGER->renderPixelTile("Tile1p", getPixelDC(),
								i * tileWidth - xLeft, j * tileWidth - yLeft,
								(_miMapTile->second.first / 100) % 100,
								_miMapTile->second.first % 100,
								_vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].imageFrameSpace,
								tileWidth, _vTileImage[(_miMapTile->second.first / 1000000) % 10 - 1].tileWidth, RGB(0, 0, 0));
						}
					}
				}
				if (_miMapTile->second.second > 0)
				{
					if ((_miMapTile->second.second / 100000) % 10 == true) //isFrameTile == true
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].keyName, getMemDC(),
							i * tileWidth - xLeft, j * tileWidth - yLeft,
							(_miMapTile->second.second / 100) % 100 + _currentFrameX,
							_miMapTile->second.second % 100,
							_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].imageFrameSpace,
							tileWidth, _vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].tileWidth);
					}
					else
					{
						IMAGEMANAGER->renderTile(_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].keyName, getMemDC(),
							i * tileWidth - xLeft, j * tileWidth - yLeft,
							(_miMapTile->second.second / 100) % 100,
							_miMapTile->second.second % 100,
							_vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].imageFrameSpace,
							tileWidth, _vTileImage[(_miMapTile->second.second / 1000000) % 10 - 1].tileWidth);
					}
				}
			}
		}
	}
	if (pixelCollision == true)
	{
		for (int i = playerX / tileWidth - 1; i < playerX / tileWidth + 1; ++i)
		{
			for (int j = playerY / tileWidth - 1; j < playerY / tileWidth + 1; ++j)
			{
				_miMapTile = _mMapTile.find((1000 + i + cameraX) * 1000 + j + cameraY);
				
			}
		}
	}
	//char test1[128];
	//char test2[128];
	//char test3[128];
	//char test4[128];
	//char test5[128];
	//char test6[128];
	//wsprintf(test1, "screenLeft : %d", screenLeft);
	//wsprintf(test2, "screenTop : %d", screenTop);
	//wsprintf(test3, "xLeft : %d", xLeft);
	//wsprintf(test4, "yLeft : %d", yLeft);
	//wsprintf(test5, "cameraX : %d", cameraX);
	//wsprintf(test6, "cameraY : %d", cameraY);
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2, test1, strlen(test1));
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2 + 20, test2, strlen(test2));
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2 + 40, test3, strlen(test3));
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2 + 60, test4, strlen(test4));
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2 + 80, test5, strlen(test3));
	//TextOut(getMemDC(), WINSIZEX / 2 + 32, WINSIZEY / 2 + 100, test6, strlen(test4));
}

void mapTool::drawMenu()
{
	RECT textRC[10];
	for (int i = 0; i < 10; ++i)
	{
		textRC[i] = { 5, 550 + 25 * i, 125, 575 + 25 * i };
	}
	drawText(20, "(N)ew", textRC[0], DT_LEFT);
	drawText(20, "(S)ave", textRC[1], DT_LEFT);
	drawText(20, "(L)oad", textRC[2], DT_LEFT);
	drawText(20, "(T)errain", textRC[3], DT_LEFT);
	if (_isObjectTile == true)
	{
		Rectangle(getMemDC(), textRC[4].left - 1, textRC[4].top - 1, textRC[4].right, textRC[4].bottom);
	}
	drawText(20, "(O)bject", textRC[4], DT_LEFT);
	if (_isBlocked == true)
	{
		Rectangle(getMemDC(), textRC[5].left - 1, textRC[5].top - 1, textRC[5].right, textRC[5].bottom);
	}
	drawText(20, "(B)locked", textRC[5], DT_LEFT);
	if (_isFrameTile == true)
	{
		Rectangle(getMemDC(), textRC[6].left - 1, textRC[6].top - 1, textRC[6].right, textRC[6].bottom);
	}
	drawText(20, "(F)rame", textRC[6], DT_LEFT);
	if (_isDeleteTile == true)
	{
		Rectangle(getMemDC(), textRC[7].left - 1, textRC[7].top - 1, textRC[7].right, textRC[7].bottom);
	}
	drawText(20, "(D)elete", textRC[7], DT_LEFT);
}

void mapTool::drawText(int fontSize, char* str, RECT rc, int position)
{
	HFONT newFont = CreateFont(fontSize, 0, 0, 0, 1000, 0, 0, 0, HANGUL_CHARSET, 0, 0, 0, 0, TEXT("Consolas"));
	HFONT oldFont = (HFONT)SelectObject(getMemDC(), newFont);
	DrawText(getMemDC(), str, -1, &rc, position | DT_WORDBREAK);
	SelectObject(getMemDC(), oldFont);
	DeleteObject(oldFont);
	DeleteObject(newFont);
}

void mapTool::keyControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		if (_ptMouse.x >= 512)
		{
			_selectTileNumX = (_ptMouse.x - 512) / 32;
			_selectTileNumY = _ptMouse.y / 32;
		}
		if (_ptMouse.x <= 512 && _ptMouse.y <= 512)
		{
			_miMapTile = _mMapTile.find((1000 + _ptMouse.x / 32 + _cameraX) * 1000 + (_ptMouse.y / 32 + _cameraY));
			if (_isDeleteTile == true)
			{
				if (_miMapTile != _mMapTile.end())
				{
					_mMapTile.erase(_miMapTile);
				}
			}
			else if (_isObjectTile == true)
			{
				unsigned int tempTileInfoFirst;
				unsigned int tempTileInfoSecond;
				tempTileInfoFirst = 0;									//타일 정보 저장 변수 초기화
				tempTileInfoSecond = 0;
				tempTileInfoSecond += _currentTileMapNum + 1;			//뿌릴 타일맵 번호 저장
				tempTileInfoSecond = tempTileInfoSecond * 10;
				tempTileInfoSecond += _isFrameTile;						//뿌릴 타일이 프레임 타일인지 저장
				tempTileInfoSecond = tempTileInfoSecond * 10;
				tempTileInfoSecond += _isBlocked;						//뿌릴 타일이 막힌 타일인지 저장
				tempTileInfoSecond = 100 * tempTileInfoSecond;
				tempTileInfoSecond += _selectTileNumX + _pageX * 16;	//뿌릴 타일 X축 번호 저장	
				tempTileInfoSecond = tempTileInfoSecond * 100;
				tempTileInfoSecond += _selectTileNumY + _pageY * 20;	//뿌릴 타일 Y축 번호 저장
				if (_miMapTile == _mMapTile.end())
				{
					_mMapTile.insert(make_pair((1000 + _ptMouse.x / 32 + _cameraX) * 1000 + (_ptMouse.y / 32 + _cameraY), make_pair(tempTileInfoFirst, tempTileInfoSecond)));	//타일 정보를 맵에 저장
				}
				else
				{
					_miMapTile->second.second = tempTileInfoSecond;
				}
			}
			else
			{
				unsigned int tempTileInfoFirst;
				unsigned int tempTileInfoSecond;
				tempTileInfoFirst = 0;									//타일 정보 저장 변수 초기화
				tempTileInfoSecond = 0;
				tempTileInfoFirst += _currentTileMapNum + 1;			//뿌릴 타일맵 번호 저장
				tempTileInfoFirst = tempTileInfoFirst * 10;
				tempTileInfoFirst += _isFrameTile;						//뿌릴 타일이 프레임 타일인지 저장
				tempTileInfoFirst = tempTileInfoFirst * 10;
				tempTileInfoFirst += _isBlocked;						//뿌릴 타일이 막힌 타일인지 저장
				tempTileInfoFirst = 100 * tempTileInfoFirst;
				tempTileInfoFirst += _selectTileNumX + _pageX * 16;		//뿌릴 타일 X축 번호 저장	
				tempTileInfoFirst = tempTileInfoFirst * 100;
				tempTileInfoFirst += _selectTileNumY + _pageY * 20;		//뿌릴 타일 Y축 번호 저장
				if (_miMapTile == _mMapTile.end())
				{
					_mMapTile.insert(make_pair((1000 + _ptMouse.x / 32 + _cameraX) * 1000 + (_ptMouse.y / 32 + _cameraY), make_pair(tempTileInfoFirst, tempTileInfoSecond)));	//타일 정보를 맵에 저장
				}
				else
				{
					_miMapTile->second.first = tempTileInfoFirst;
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('N'))
	{
		newMap();
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		save();
	}
	if (KEYMANAGER->isOnceKeyDown('L'))
	{
		load();
	}
	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		if (_isObjectTile == true) _isObjectTile = false;
		else if (_isObjectTile == false) _isObjectTile = true;
	}
	if (KEYMANAGER->isOnceKeyDown('B'))
	{
		if (_isBlocked == true) _isBlocked = false;
		else if (_isBlocked == false) _isBlocked = true;
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		if (_isFrameTile == true) _isFrameTile = false;
		else if (_isFrameTile == false) _isFrameTile = true;
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		if (_isDeleteTile == true) _isDeleteTile = false;
		else if (_isDeleteTile == false) _isDeleteTile = true;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD7))
	{
		if (_currentTileMapNum > 0)
		{
			_currentTileMapNum--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD9))
	{
		if (_currentTileMapNum < MAXTILENUM - 1)
		{
			_currentTileMapNum++;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD4))
	{
		if (_pageX > 0)
		{
			_pageX--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD6))
	{
		_pageX++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD8))
	{
		if (_pageY)
		{
			_pageY--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_NUMPAD5))
	{
		_pageY++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_cameraX > 0)
		{
			_cameraX--;
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_cameraX++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{
		_cameraY++;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{
		if (_cameraY > 0)
		{
			_cameraY--;
		}
	}
}

void mapTool::newMap()
{
	_mMapTile.clear();
}

void mapTool::save()
{
	HANDLE file;
	DWORD write;

	OPENFILENAME ofn;
	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";			// 오픈파일네임에서 읽을수 있는 파일을 제한하는 필터 설정
	ofn.Flags = OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == false) return;

	string curMapFileName = ofn.lpstrFile;
	file = CreateFile(curMapFileName.c_str(), GENERIC_WRITE, NULL, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	tagIMAGEINFO temp;
	int maxTile = _vTileImage.size();
	int maxMap = _mMapTile.size();
	WriteFile(file, &maxTile, sizeof(int), &write, NULL);
	WriteFile(file, &maxMap, sizeof(int), &write, NULL);
	for (int i = 0; i < maxTile; ++i)
	{
		temp = _vTileImage[i];
		WriteFile(file, &temp, sizeof(tagIMAGEINFO), &write, NULL);
	}
	_miMapTile = _mMapTile.begin();
	unsigned int key;
	unsigned int pairFirst;
	unsigned int pairSecond;
	for (; _miMapTile != _mMapTile.end(); ++_miMapTile)
	{
		key = _miMapTile->first;
		pairFirst = _miMapTile->second.first;
		pairSecond = _miMapTile->second.second;
		WriteFile(file, &key, sizeof(unsigned int), &write, NULL);
		WriteFile(file, &pairFirst, sizeof(unsigned int), &write, NULL);
		WriteFile(file, &pairSecond, sizeof(unsigned int), &write, NULL);
	}

	CloseHandle(file);
}

void mapTool::load()
{
	HANDLE file;
	DWORD read;

	OPENFILENAME ofn;

	char filePath[1024] = "";
	ZeroMemory(&ofn, sizeof(OPENFILENAME));

	ofn.lStructSize = sizeof(OPENFILENAME);
	ofn.hwndOwner = NULL;
	ofn.lpstrFile = filePath;
	ofn.nMaxFile = sizeof(filePath);
	ofn.nFilterIndex = true;
	ofn.nMaxFileTitle = NULL;
	ofn.lpstrFileTitle = NULL;
	ofn.lpstrInitialDir = NULL;
	ofn.lpstrFilter = "Map File(*.map)\0*.map\0";
	ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == FALSE) return;

	string curMapFileName = ofn.lpstrFile;
	file = CreateFile(curMapFileName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	tagIMAGEINFO temp;
	int maxTile;
	int maxMap;
	ReadFile(file, &maxTile, sizeof(int), &read, NULL);
	ReadFile(file, &maxMap, sizeof(int), &read, NULL);

	_vTileImage.clear();
	for (int i = 0; i < maxTile; ++i)
	{
		ReadFile(file, &temp, sizeof(tagIMAGEINFO), &read, NULL);
		_vTileImage.push_back(temp);
	}

	_mMapTile.clear();
	unsigned int key;
	unsigned int pairFirst;
	unsigned int pairSecond;
	for (int i = 0; i < maxMap; ++i)
	{
		ReadFile(file, &key, sizeof(unsigned int), &read, NULL);
		ReadFile(file, &pairFirst, sizeof(unsigned int), &read, NULL);
		ReadFile(file, &pairSecond, sizeof(unsigned int), &read, NULL);
		_mMapTile.insert(make_pair(key, make_pair(pairFirst, pairSecond)));
	}

	CloseHandle(file);
}

void mapTool::load(string fileName)
{
	HANDLE file;
	DWORD read;

	string curMapFileName = fileName;
	file = CreateFile(curMapFileName.c_str(), GENERIC_READ, NULL, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);

	tagIMAGEINFO temp;
	int maxTile;
	int maxMap;
	ReadFile(file, &maxTile, sizeof(int), &read, NULL);
	ReadFile(file, &maxMap, sizeof(int), &read, NULL);

	_vTileImage.clear();
	for (int i = 0; i < maxTile; ++i)
	{
		ReadFile(file, &temp, sizeof(tagIMAGEINFO), &read, NULL);
		_vTileImage.push_back(temp);
	}

	_mMapTile.clear();
	unsigned int key;
	unsigned int pairFirst;
	unsigned int pairSecond;
	for (int i = 0; i < maxMap; ++i)
	{
		ReadFile(file, &key, sizeof(unsigned int), &read, NULL);
		ReadFile(file, &pairFirst, sizeof(unsigned int), &read, NULL);
		ReadFile(file, &pairSecond, sizeof(unsigned int), &read, NULL);
		_mMapTile.insert(make_pair(key, make_pair(pairFirst, pairSecond)));
	}

	CloseHandle(file);
}

tagIMAGEINFO mapTool::addImageInfo(int imageNum)
{
	tagIMAGEINFO tempImageInfo;
	switch (imageNum)
	{
	case(0):
		wsprintf(tempImageInfo.directory, ".\\images\\Tile0.bmp");
		wsprintf(tempImageInfo.keyName, "Tile0");
		tempImageInfo.tileWidth = 32;
		tempImageInfo.imageWidth = 1400;
		tempImageInfo.imageHeight = 1400;
		tempImageInfo.imageFrameX = 41;
		tempImageInfo.imageFrameY = 41;
		tempImageInfo.imageFrameSpace = 2;
		return tempImageInfo;
		break;
	case(1):
		wsprintf(tempImageInfo.directory, ".\\images\\Tile1.bmp");
		wsprintf(tempImageInfo.keyName, "Tile1");
		tempImageInfo.tileWidth = 128;
		tempImageInfo.imageWidth = 1536;
		tempImageInfo.imageHeight = 2816;
		tempImageInfo.imageFrameX = 12;
		tempImageInfo.imageFrameY = 22;
		tempImageInfo.imageFrameSpace = 0;
		return tempImageInfo;
		break;
	}
}

void mapTool::frameUpdate()
{
	_frameCounter++;
	if (_frameCounter > 29)
	{
		_currentFrameX++;
		if (_currentFrameX > 3) _currentFrameX = 0;
		_frameCounter = 0;
	}
}