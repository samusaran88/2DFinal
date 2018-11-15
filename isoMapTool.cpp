#include "stdafx.h"
#include "isoMapTool.h"
#include "player.h"


isoMapTool::isoMapTool()
{
}


isoMapTool::~isoMapTool()
{

}

HRESULT isoMapTool::init()
{
	SOUNDMANAGER->addSound("MineCraftSubwooferLullaby", ".\\sounds\\MineCraftSubwooferLullaby.mp3", true, true);
	SOUNDMANAGER->play("MineCraftSubwooferLullaby", CH_BGM, 1.0f);
	IMAGEMANAGER->addFrameImage("isoMapTile", ".\\images\\isoTile.bmp", 256, 512, 8, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("isoMapTileBack", ".\\images\\isoTile.bmp", 256, 512, 8, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("isoMapTileBottom", ".\\images\\isoTile.bmp", 256, 512, 8, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("isoMapTileFront", ".\\images\\isoTile.bmp", 256, 512, 8, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("emptyDiamond", ".\\images\\emptyDiamond.bmp", 32, 16, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("background", ".\\images\\backgroundSky.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("shade", ".\\images\\shade.bmp", 63, 99, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magentaBack", ".\\images\\magenta.bmp", 1024, 768, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magentaBottom", ".\\images\\magenta.bmp", 1024, 768, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("magentaFront", ".\\images\\magenta.bmp", 1024, 768, false, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("skeletonTile", ".\\images\\skeletonTile.bmp", 32, 32, true, RGB(255, 0, 255));
	_backLayer = IMAGEMANAGER->addTransImage("backLayer", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_bottomLayer = IMAGEMANAGER->addTransImage("bottomLayer", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_frontLayer = IMAGEMANAGER->addTransImage("frontLayer", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	_bufferBack = IMAGEMANAGER->addImage("bufferBack", WINSIZEX, WINSIZEY);
	_bufferBottom = IMAGEMANAGER->addImage("bufferBottom", WINSIZEX, WINSIZEY);
	_bufferFront = IMAGEMANAGER->addImage("bufferFront", WINSIZEX, WINSIZEY);
	_bufferBack2 = IMAGEMANAGER->addImage("bufferBack2", WINSIZEX, WINSIZEY);
	_bufferBottom2 = IMAGEMANAGER->addImage("bufferBottom2", WINSIZEX, WINSIZEY);
	_bufferFront2 = IMAGEMANAGER->addImage("bufferFront2", WINSIZEX, WINSIZEY);
	IMAGEMANAGER->render("magentaBack", _bufferBack2->getMemDC());
	IMAGEMANAGER->render("magentaBottom", _bufferBottom2->getMemDC());
	IMAGEMANAGER->render("magentaFront", _bufferFront2->getMemDC());

	_wheel_delta = 0;

	_playerX = ISOTILEWIDTH / 2 * TOTALb;
	_playerY = ISOTILEHEIGHT / 2 * TOTALa;
	_playerHeight = 0;
	_shadowHeight = 0;
	_playerFloor = 0;
	_minA = _maxA = _minB = _maxB = 0;
	_mouseNumA = _mouseNumB = 0;
	_screenLeft = 0;
	_screenTop = 0;
	_screenRight = 0;
	_screenBottom = 0;
	_playerDirection = RB;
	_isDrawBackLayer = false;
	_isDrawBottomLayer = false;
	_isDrawFrontLayer = false;
	_isReadyBackLayer = true;
	_isReadyBottomLayer = true;
	_isReadyFrontLayer = true;
	_isPointingUp = false;
	_isPointingDown = false;
	_tileFrame = 0;
	_tileNum = 0;
	_counter = 0;
	_wheelCounter = 0;
	_jumpPower = 0;
	_isJump = false;
	_isFalling = false;
	float tempTileNum;
	tempTileNum = ((float)_playerY / (ISOTILEHEIGHT / 2) + (float)_playerX / (ISOTILEWIDTH / 2) - TOTALb) / 2;
	_playerTileNumA = tempTileNum;
	tempTileNum = ((float)_playerY / (ISOTILEHEIGHT / 2) - (float)_playerX / (ISOTILEWIDTH / 2) + TOTALb) / 2;
	_playerTileNumB = tempTileNum;

	for (int i = 0; i < 4; ++i)
	{
		_playerBlock[i] = false;
	}
	for (int i = 0; i < TOTALa; ++i)
	{
		for (int j = 0; j < TOTALb; ++j)
		{
			for (int k = 0; k < TOTALh; ++k)
			{
				if (i == 0 || j == 0 || k == 0)
				{
					TileInfo tempTileInfo;
					tempTileInfo.insert(make_pair(k, 1));
					_miMapTile = _mMapTile.find(1000000 + i * 1000 + j);
					if (_miMapTile != _mMapTile.end())
					{
						_miMapTile->second.insert(make_pair(k, 1));
					}
					else
					{
						_mMapTile.insert(make_pair(1000000 + i * 1000 + j, tempTileInfo));
					}
				}
			}
		}
	}

	_player->init(MARIO, 1.5f);

	//for (int i = 0; i < 3; ++i)
	//{
	//	_runThread[i] = true;
	//}

	return S_OK;
}

void isoMapTool::release()
{

}

void isoMapTool::update() 
{
	minMaxCalculation();
	activateThreadFunction();
	playerControl();
	jumpPhysics();
	_player->updateS2();
	detectTile();
	createTile();
	frameCounter();
}

void isoMapTool::render() 
{
	IMAGEMANAGER->findImage("background")->render(getMemDC());
	copyLayer();
	IMAGEMANAGER->findImage("bottomLayer")->render(getMemDC());
	IMAGEMANAGER->findImage("backLayer")->render(getMemDC());
	_player->render(24);
	drawMouseTile();
	IMAGEMANAGER->findImage("frontLayer")->render(getMemDC());

	//char test[128];
	//wsprintf(test, "%d", _playerFloor);
	//TextOut(getMemDC(), WINSIZEX / 2 + 50, WINSIZEY / 2 + 50, test, strlen(test));
}

void isoMapTool::playerControl()
{
	if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown('A'))
	{
		_player->setPlayerDirection(LB);
		if (_isJump == false) _player->setPlayerState(WALKING);
		if (_playerBlock[LB] == false)
		{
			_playerX -= 4;
			_playerY += 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_RIGHT) || KEYMANAGER->isStayKeyDown('D'))
	{
		_player->setPlayerDirection(RT);
		if (_isJump == false) _player->setPlayerState(WALKING);
		if (_playerBlock[RT] == false)
		{
			_playerX += 4;
			_playerY -= 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN) || KEYMANAGER->isStayKeyDown('S'))
	{
		_player->setPlayerDirection(RB);
		if (_isJump == false) _player->setPlayerState(WALKING);
		if (_playerBlock[RB] == false)
		{
			_playerX += 4;
			_playerY += 2;
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_UP) || KEYMANAGER->isStayKeyDown('W'))
	{
		_player->setPlayerDirection(LT);
		if (_isJump == false) _player->setPlayerState(WALKING);
		if (_playerBlock[LT] == false)
		{
			_playerX -= 4;
			_playerY -= 2;
		}
	}

	if (KEYMANAGER->isOnceKeyUp(VK_LEFT) || KEYMANAGER->isOnceKeyUp('A'))
	{
		if (_isJump == false) _player->setPlayerState(IDLE);
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT) || KEYMANAGER->isOnceKeyUp('D'))
	{
		if (_isJump == false) _player->setPlayerState(IDLE);
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN) || KEYMANAGER->isOnceKeyUp('S'))
	{
		if (_isJump == false) _player->setPlayerState(IDLE);
	}
	
	if (KEYMANAGER->isOnceKeyUp(VK_UP) || KEYMANAGER->isOnceKeyUp('W'))
	{
		if (_isJump == false) _player->setPlayerState(IDLE);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_isJump == false)
		{
			_player->setPlayerState(JUMPING);
			_jumpPower = 6;
			_isJump = true;
		}
	}

	if (KEYMANAGER->isStayKeyDown('E'))
	{
		_isPointingUp = true;
	}
	if (KEYMANAGER->isOnceKeyUp('E'))
	{
		_isPointingUp = false;
	}

	if (KEYMANAGER->isStayKeyDown('Q'))
	{
		_isPointingDown = true;
	}
	if (KEYMANAGER->isOnceKeyUp('Q'))
	{
		_isPointingDown = false;
	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("WorldMap");
	}
}

void isoMapTool::createTile()
{
	float tempTileNumA, tempTileNumB;
	if (_isPointingUp == true)
	{
		tempTileNumA = ((float)(_screenTop + _ptMouse.y + ISOTILEHEIGHT * 2) / (ISOTILEHEIGHT / 2) + (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_screenTop + _ptMouse.y + ISOTILEHEIGHT * 2) / (ISOTILEHEIGHT / 2) - (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		_mouseNumA = tempTileNumA;
		_mouseNumB = tempTileNumB;
	}
	else if (_isPointingDown == true)
	{
		tempTileNumA = ((float)(_screenTop + _ptMouse.y) / (ISOTILEHEIGHT / 2) + (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_screenTop + _ptMouse.y) / (ISOTILEHEIGHT / 2) - (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		_mouseNumA = tempTileNumA;
		_mouseNumB = tempTileNumB;
	}
	else
	{
		tempTileNumA = ((float)(_screenTop + _ptMouse.y + ISOTILEHEIGHT) / (ISOTILEHEIGHT / 2) + (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_screenTop + _ptMouse.y + ISOTILEHEIGHT) / (ISOTILEHEIGHT / 2) - (float)(_screenLeft + _ptMouse.x) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		_mouseNumA = tempTileNumA;
		_mouseNumB = tempTileNumB;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		if (_isPointingUp == true)
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				tempTileInfo = _miMapTile->second.find(_playerFloor + 2);
				if (tempTileInfo != _miMapTile->second.end())
				{
					_miMapTile->second.erase(_playerFloor);
					_miMapTile->second.insert(make_pair(_playerFloor + 2, _wheel_delta));
				}
				else
				{
					_miMapTile->second.insert(make_pair(_playerFloor + 2, _wheel_delta));
				}
			}
		}
		else if (_isPointingDown == true)
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				if (_playerFloor != 0)
				{
					tempTileInfo = _miMapTile->second.find(_playerFloor);
					if (tempTileInfo != _miMapTile->second.end())
					{
						_miMapTile->second.erase(_playerFloor);
						_miMapTile->second.insert(make_pair(_playerFloor, _wheel_delta));
					}
					else
					{
						_miMapTile->second.insert(make_pair(_playerFloor, _wheel_delta));
					}
				}
			}
		}
		else
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				tempTileInfo = _miMapTile->second.find(_playerFloor + 1);
				if (tempTileInfo != _miMapTile->second.end())
				{
					_miMapTile->second.erase(_playerFloor + 1);
					_miMapTile->second.insert(make_pair(_playerFloor + 1, _wheel_delta));
				}
				else
				{
					_miMapTile->second.insert(make_pair(_playerFloor + 1, _wheel_delta));
				}
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
	{
		if (_isPointingUp == true)
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				tempTileInfo = _miMapTile->second.find(_playerFloor + 2);
				if (tempTileInfo != _miMapTile->second.end())
				{
					_miMapTile->second.erase(_playerFloor + 2);
				}
			}
		}
		else if (_isPointingDown == true)
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				if (_playerFloor != 0)
				{
					tempTileInfo = _miMapTile->second.find(_playerFloor);
					if (tempTileInfo != _miMapTile->second.end())
					{
						_miMapTile->second.erase(_playerFloor);
					}
				}
			}
		}
		else
		{
			arrTileInfo tempTileInfo;
			_miMapTile = _mMapTile.find(1000000 + _mouseNumA * 1000 + _mouseNumB);
			if (_miMapTile != _mMapTile.end())
			{
				tempTileInfo = _miMapTile->second.find(_playerFloor + 1);
				if (tempTileInfo != _miMapTile->second.end())
				{
					_miMapTile->second.erase(_playerFloor + 1);
				}
			}
		}
	}
}

void isoMapTool::drawMouseTile()
{
	if (_isPointingUp == true)
	{
		IMAGEMANAGER->renderTile("isoMapTile", getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (_mouseNumA - _mouseNumB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (_mouseNumA + _mouseNumB - 4) * ISOTILEHEIGHT / 2 - _screenTop, 0, _wheel_delta, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
	}
	else if (_isPointingDown == true)
	{
		IMAGEMANAGER->renderTile("isoMapTile", getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (_mouseNumA - _mouseNumB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (_mouseNumA + _mouseNumB) * ISOTILEHEIGHT / 2 - _screenTop, 0, _wheel_delta, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
	}
	else
	{
		IMAGEMANAGER->renderTile("isoMapTile", getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (_mouseNumA - _mouseNumB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (_mouseNumA + _mouseNumB - 2) * ISOTILEHEIGHT / 2 - _screenTop, 0, _wheel_delta, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
	}
}

void isoMapTool::frameCounter()
{
	_counter++;
	if (_counter > 10)
	{
		_tileFrame++;
		if (_tileFrame > 7) _tileFrame = 0;
		_counter = 0;
	}
	if (_wheel_delta > 15) _wheel_delta = 0;
	else if (_wheel_delta < 0) _wheel_delta = 15;
}

void isoMapTool::drawBackLayer()
{
	IMAGEMANAGER->render("magentaBack", _bufferBack2->getMemDC());
	for (int i = 0; i < TOTALa; ++i)
	{
		for (int j = 0; j < TOTALb; ++j)
		{
			if (i >= _playerTileNumA && j >= _playerTileNumB) continue;
			map<unsigned int, map<unsigned int, unsigned int>>::iterator iter1;
			arrTileInfo element1;
			iter1 = _mMapTile.find(1000000 + i * 1000 + j);
			if (iter1 != _mMapTile.end())
			{
				for (element1 = iter1->second.begin(); element1 != iter1->second.end(); ++element1)
				{
					if (element1->first <= _playerFloor) continue;
					int tileHeight;
					int corrA, corrB;
					tileHeight = _playerFloor - element1->first;
					corrA = i + tileHeight;
					corrB = j + tileHeight;
					IMAGEMANAGER->renderTile("isoMapTileBack", _bufferBack2->getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (corrA - corrB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (corrA + corrB) * ISOTILEHEIGHT / 2 - _screenTop + _playerHeight, _tileFrame, element1->second, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
				}
			}
			//if (iter1 != _mMapTile.end())
			//{
			//	IMAGEMANAGER->renderTile("isoMapTileBack", _bufferBack2->getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (i - j - 1) * ISOTILEWIDTH / 2 - _screenLeft, (i + j) * ISOTILEHEIGHT / 2 - _screenTop, _tileFrame, 1, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
			//}
		}
	}
	BitBlt
	(_bufferBack->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferBack2->getMemDC(), 0, 0, SRCCOPY);
	_isReadyBackLayer = true;
}

void isoMapTool::drawBottomLayer()
{
	IMAGEMANAGER->render("magentaBottom", _bufferBottom2->getMemDC());
	for (int i = 0; i < TOTALa; ++i)
	{
		for (int j = 0; j < TOTALb; ++j)
		{
			map<unsigned int, map<unsigned int, unsigned int>>::iterator iter2;
			arrTileInfo element2;
			iter2 = _mMapTile.find(1000000 + i * 1000 + j);
			if (iter2 != _mMapTile.end())
			{
				for (element2 = iter2->second.begin(); element2 != iter2->second.end(); ++element2)
				{
					if (element2->first > _playerFloor) break;
					int tileHeight;
					int corrA, corrB;
					tileHeight = _playerFloor - element2->first;
					corrA = i + tileHeight;
					corrB = j + tileHeight;
					IMAGEMANAGER->renderTile("isoMapTileBottom", _bufferBottom2->getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (corrA - corrB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (corrA + corrB) * ISOTILEHEIGHT / 2 - _screenTop + _playerHeight, _tileFrame, element2->second, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
				}
			}
		}
	}
	IMAGEMANAGER->findImage("shade")->render(_bufferBottom2->getMemDC(), WINSIZEX / 2 - 31, WINSIZEY / 2 - 86 + _shadowHeight);
	BitBlt
	(_bufferBottom->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferBottom2->getMemDC(), 0, 0, SRCCOPY);
	_isReadyBottomLayer = true;
}

void isoMapTool::drawFrontLayer() 
{
	IMAGEMANAGER->render("magentaFront", _bufferFront2->getMemDC());
	for (int i = _playerTileNumA; i < TOTALa; ++i)
	{
		for (int j = _playerTileNumB; j < TOTALb; ++j)
		{
			map<unsigned int, map<unsigned int, unsigned int>>::iterator iter3;
			arrTileInfo element3;
			iter3 = _mMapTile.find(1000000 + i * 1000 + j);
			if (iter3 != _mMapTile.end())
			{
				for (element3 = iter3->second.begin(); element3 != iter3->second.end(); ++element3)
				{
					if (element3->first <= _playerFloor) continue;
					int tileHeight;
					int corrA, corrB;
					tileHeight = _playerFloor - element3->first;
					corrA = i + tileHeight;
					corrB = j + tileHeight;
					IMAGEMANAGER->renderTile("skeletonTile", _bufferFront2->getMemDC(), TOTALb * ISOTILEWIDTH / 2 + (corrA - corrB - 1) * ISOTILEWIDTH / 2 - _screenLeft, (corrA + corrB) * ISOTILEHEIGHT / 2 - _screenTop + _playerHeight, 0, 0, 0, ISOTILEWIDTH, ISOTILEHEIGHT * 2, 32, 32);
				}
			}
		}
	}
	BitBlt
	(_bufferFront->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferFront2->getMemDC(), 0, 0, SRCCOPY);
	_isReadyFrontLayer = true;
}

void isoMapTool::copyLayer()
{
	if (_isReadyBackLayer == true && _isReadyBottomLayer == true)
	{
		BitBlt
		(_backLayer->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferBack->getMemDC(), 0, 0, SRCCOPY);
		_isReadyBackLayer = false;
		_runThread[0] = true;
		BitBlt
		(_bottomLayer->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferBottom->getMemDC(), 0, 0, SRCCOPY);
		_isReadyBottomLayer = false;
		_runThread[1] = true;
		BitBlt
		(_frontLayer->getMemDC(), 0, 0, WINSIZEX, WINSIZEY, _bufferFront->getMemDC(), 0, 0, SRCCOPY);
		_isReadyFrontLayer = false;
		_runThread[2] = true;
	}
}

void isoMapTool::minMaxCalculation()
{
	_screenLeft = _playerX - WINSIZEX / 2;
	_screenTop = _playerY - WINSIZEY / 2;
	_screenRight = _playerX + WINSIZEX / 2;
	_screenBottom = _playerY + WINSIZEY / 2;

	float tempTileNum;

	tempTileNum = ((float)_playerY / (ISOTILEHEIGHT / 2) + (float)_playerX / (ISOTILEWIDTH / 2) - TOTALb) / 2;
	_playerTileNumA = tempTileNum;
	tempTileNum = ((float)_playerY / (ISOTILEHEIGHT / 2) - (float)_playerX / (ISOTILEWIDTH / 2) + TOTALb) / 2;
	_playerTileNumB = tempTileNum;
}

void isoMapTool::detectTile()
{
	float tempTileNumA, tempTileNumB;
	tempTileNumA = tempTileNumB = 0;
	int tileNumA, tileNumB;
	tileNumA = tileNumB = 0;
	arrTileInfo element;
	switch (_player->getPlayerDirection())
	{
	case(LB):
		tempTileNumA = ((float)(_playerY + 17) / (ISOTILEHEIGHT / 2) + (float)(_playerX - 33) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_playerY + 17) / (ISOTILEHEIGHT / 2) - (float)(_playerX - 33) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		tileNumA = tempTileNumA;
		tileNumB = tempTileNumB;
		_miMapTile = _mMapTile.find(1000000 + tileNumA * 1000 + tileNumB);
		if (_miMapTile != _mMapTile.end())
		{
			element = _miMapTile->second.find(_playerFloor + 1);
			if (element != _miMapTile->second.end())
			{
				_playerBlock[LB] = true;
			}
			else
			{
				_playerBlock[LB] = false;
			}
		}
		else
		{
			_playerBlock[LB] = true;
		}
		break;
	case(LT):
		tempTileNumA = ((float)(_playerY - 17) / (ISOTILEHEIGHT / 2) + (float)(_playerX - 33) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_playerY - 17) / (ISOTILEHEIGHT / 2) - (float)(_playerX - 33) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		tileNumA = tempTileNumA;
		tileNumB = tempTileNumB;
		_miMapTile = _mMapTile.find(1000000 + tileNumA * 1000 + tileNumB);
		if (_miMapTile != _mMapTile.end())
		{
			element = _miMapTile->second.find(_playerFloor + 1);
			if (element != _miMapTile->second.end())
			{
				_playerBlock[LT] = true;
			}
			else
			{
				_playerBlock[LT] = false;
			}
		}
		else
		{
			_playerBlock[LT] = true;
		}
		break;
	case(RB):
		tempTileNumA = ((float)(_playerY + 17) / (ISOTILEHEIGHT / 2) + (float)(_playerX + 33) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_playerY + 17) / (ISOTILEHEIGHT / 2) - (float)(_playerX + 33) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		tileNumA = tempTileNumA;
		tileNumB = tempTileNumB;
		_miMapTile = _mMapTile.find(1000000 + tileNumA * 1000 + tileNumB);
		if (_miMapTile != _mMapTile.end())
		{
			element = _miMapTile->second.find(_playerFloor + 1);
			if (element != _miMapTile->second.end())
			{
				_playerBlock[RB] = true;
			}
			else
			{
				_playerBlock[RB] = false;
			}
		}
		else
		{
			_playerBlock[RB] = true;
		}
		break;
	case(RT):
		tempTileNumA = ((float)(_playerY - 17) / (ISOTILEHEIGHT / 2) + (float)(_playerX + 33) / (ISOTILEWIDTH / 2) - TOTALb) / 2;
		tempTileNumB = ((float)(_playerY - 17) / (ISOTILEHEIGHT / 2) - (float)(_playerX + 33) / (ISOTILEWIDTH / 2) + TOTALb) / 2;
		tileNumA = tempTileNumA;
		tileNumB = tempTileNumB;
		_miMapTile = _mMapTile.find(1000000 + tileNumA * 1000 + tileNumB);
		if (_miMapTile != _mMapTile.end())
		{
			element = _miMapTile->second.find(_playerFloor + 1);
			if (element != _miMapTile->second.end())
			{
				_playerBlock[RT] = true;
			}
			else
			{
				_playerBlock[RT] = false;
			}
		}
		else
		{
			_playerBlock[RT] = true;
		}
		break;
	}

	if (_playerHeight > 64)
	{
		_playerHeight -= 64;
		_playerFloor += 1;
	}
	_miMapTile = _mMapTile.find(1000000 + _playerTileNumA * 1000 + _playerTileNumB);
	if (_playerHeight <= 0)
	{
		element = _miMapTile->second.find(_playerFloor);
		if (element != _miMapTile->second.end())
		{
			_player->setPlayerState(IDLE);
			_playerHeight = 0;
			_shadowHeight = 0;
			_jumpPower = 0;
			_isJump = false;
			_isFalling = false;
		}
		else
		{
			_playerHeight += 64;
			_playerFloor -= 1;
			_isJump = true;
			if (_isJump == false) _isFalling = true;
		}
	}
	if (_isJump == true && _jumpPower > 0)
	{
		element = _miMapTile->second.find(_playerFloor + 2);
		if (element != _miMapTile->second.end())
		{
			_jumpPower = -0.1;
		}
	}

}

void isoMapTool::jumpPhysics()
{
	if (_isJump == true || _isFalling == true)
	{
		if (_jumpPower > 0) _player->setPlayerFrame(3);
		else if (_jumpPower <= 0) _player->setPlayerFrame(4);
		_playerHeight += _jumpPower;
		_shadowHeight += _jumpPower;
		_jumpPower -= 0.2;
		if (_jumpPower < -4) _jumpPower = -4;
	}
}

void isoMapTool::activateThreadFunction()
{
	HANDLE hThread[3];
	DWORD dwThreadID[3];

	for (int i = 0; i < 3; ++i)
	{
		hThread[i] = NULL;
		dwThreadID[i] = NULL;
		if (_runThread[i] == true)
		{
			_runThread[i] = false;
			dwThreadID[i] = 0;
			switch (i)
			{
			case(0):
				hThread[i] = CreateThread(NULL, 0, threadFunc1, (void*)this, NULL, &dwThreadID[i]);
				break;
			case(1):
				hThread[i] = CreateThread(NULL, 0, threadFunc2, (void*)this, NULL, &dwThreadID[i]);
				break;
			case(2):
				hThread[i] = CreateThread(NULL, 0, threadFunc3, (void*)this, NULL, &dwThreadID[i]);
				break;
			}
			GetExitCodeThread(hThread[i], &dwThreadID[i]);
			CloseHandle(hThread[i]);
		}
	}
}

DWORD WINAPI isoMapTool::threadFunc1(LPVOID lpParam)
{
	isoMapTool* threadF = (isoMapTool*)lpParam;

	threadF->drawBackLayer();

	return 0;
}

DWORD WINAPI isoMapTool::threadFunc2(LPVOID lpParam)
{
	isoMapTool* threadF = (isoMapTool*)lpParam;

	threadF->drawBottomLayer();

	return 0;
}

DWORD WINAPI isoMapTool::threadFunc3(LPVOID lpParam)
{
	isoMapTool* threadF = (isoMapTool*)lpParam;

	threadF->drawFrontLayer();

	return 0;
}
