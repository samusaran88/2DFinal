#include "stdafx.h"
#include "worldMap.h"
#include "mapTool.h"
#include "player.h"

worldMap::worldMap()
{
}


worldMap::~worldMap()
{

}

HRESULT worldMap::init()
{
	SOUNDMANAGER->addSound("mario3GrassLand", ".\\sounds\\mario3GrassLand.mp3", true, true);
	SOUNDMANAGER->play("mario3GrassLand", CH_BGM, 1.0f);
	_player->init(PEACH_BABY_CRAWL, 2.0f);
	_mapTool->initWorldMap();
	_playerX = 17 * WMTILESIZE - WMTILESIZE / 2;
	_playerY = 14 * WMTILESIZE - WMTILESIZE / 2;

	return S_OK;
}

void worldMap::release()
{

}

void worldMap::update()	
{
	_mapTool->frameUpdate();
	_player->updateWorldMap();
	playerControl();
}

void worldMap::render()	
{
	_mapTool->drawTile(_playerX, _playerY, WMTILESIZE);
	_player->render(0);
}

void worldMap::playerControl()
{
	int detectXNum;
	int detectYNum;

	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		detectXNum = (_playerX - WMTILESIZE / 2) / WMTILESIZE;
		detectYNum = _playerY / WMTILESIZE;
		if (_mapTool->getMapTile()[(1000 + detectXNum) * 1000 + detectYNum].first / 10000 % 10 == false)
		{
			_player->setPlayerState(WALKING);
			_player->setPlayerDirection(LEFT);
			_playerX -= 2;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{
		_player->setPlayerState(IDLE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		detectXNum = (_playerX + WMTILESIZE / 2) / WMTILESIZE;
		detectYNum = _playerY / WMTILESIZE;
		if (_mapTool->getMapTile()[(1000 + detectXNum) * 1000 + detectYNum].first / 10000 % 10 == false)
		{
			_player->setPlayerState(WALKING);
			_player->setPlayerDirection(RIGHT);
			_playerX += 2;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{
		_player->setPlayerState(IDLE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		detectXNum = _playerX / WMTILESIZE;
		detectYNum = (_playerY + WMTILESIZE / 2) / WMTILESIZE;
		if (_mapTool->getMapTile()[(1000 + detectXNum) * 1000 + detectYNum].first / 10000 % 10 == false)
		{
			_player->setPlayerState(WALKING);
			_player->setPlayerDirection(DOWN);
			_playerY += 2;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{
		_player->setPlayerState(IDLE);
	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		detectXNum = _playerX / WMTILESIZE;
		detectYNum = (_playerY - WMTILESIZE / 2) / WMTILESIZE;
		if (_mapTool->getMapTile()[(1000 + detectXNum) * 1000 + detectYNum].first / 10000 % 10 == false)
		{
			_player->setPlayerState(WALKING);
			_player->setPlayerDirection(UP);
			_playerY -= 2;
		}
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{
		_player->setPlayerState(IDLE);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		detectXNum = _playerX / WMTILESIZE;
		detectYNum = _playerY / WMTILESIZE;
		if (detectXNum == 11 && detectYNum == 9)
		{
			SOUNDMANAGER->stop(CH_BGM);
			SCENEMANAGER->changeScene("Stage1");
		}
		if (detectXNum == 22 && detectYNum == 16)
		{
			SOUNDMANAGER->stop(CH_BGM);
			SCENEMANAGER->changeScene("isoMapTool");
		}
		if (detectXNum == 22 && detectYNum == 9)
		{
			SOUNDMANAGER->stop(CH_BGM);
			SCENEMANAGER->changeScene("Taiko");
		}


		
	}
}
