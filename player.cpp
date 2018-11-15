#include "stdafx.h"
#include "player.h"


player::player()
{
}


player::~player()
{

}

HRESULT player::init(PLAYERIMAGE num, float playerSizeRate)
{
	_playerSizeRate = playerSizeRate;
	_frameCounter = 0;
	IMAGEMANAGER->deleteImage("Peach");
	switch (num)
	{
	case(PEACH_BABY_CRAWL):
		IMAGEMANAGER->addFrameImage("Peach", ".\\images\\babyPeachCrawl(192,112,8,4).bmp", 192, 112, 8, 4, true, RGB(255, 0, 255));
		_playerImg = IMAGEMANAGER->findImage("Peach");
		_playerDirection = DOWN;
		break;
	case(PEACH_BABY_STROLLER):
		IMAGEMANAGER->addFrameImage("Peach", ".\\images\\babyPeachStroller(144,288,4,8).bmp", 144, 288, 4, 8, true, RGB(255, 0, 255));
		_playerImg = IMAGEMANAGER->findImage("Peach");
		_playerDirection = RIGHT;
		break;
	case(MARIO):
		IMAGEMANAGER->addFrameImage("mario", ".\\images\\marioLarge.bmp", 210, 264, 5, 4, true, RGB(255, 0, 255));
		_playerImg = IMAGEMANAGER->findImage("mario");
		_playerDirection = RB;
	}

	return S_OK;
}

void player::release()
{

}

void player::updateWorldMap()
{
	switch (_playerState)
	{
	case(IDLE):
		_playerImg->setFrameX(0);
		break;
	case(WALKING):
		frameUpdate(20, 0, _playerImg->getMaxFrameX());
		break;
	}
}

void player::updateS1()
{
	frameUpdate(10, 0, _playerImg->getMaxFrameX());
}

void player::updateS2()
{
	switch (_playerState)
	{
	case(IDLE):
		_playerImg->setFrameX(0);
		break;
	case(WALKING):
		frameUpdate(10, 1, 2);
		break;
	case(JUMPING):
		break;
	}
}

void player::render(int fixY)
{
	_playerImg->enlargeFrameRender(getMemDC(), WINSIZEX / 2 - _playerImg->getFrameWidth() / 2 * _playerSizeRate, WINSIZEY / 2 - (_playerImg->getFrameHeight() / 2 + fixY) * _playerSizeRate, _playerImg->getFrameX(), _playerDirection, _playerSizeRate);	
}

void player::frameUpdate(int maxCounter, int beginFrame, int endFrame)
{
	_frameCounter++;
	if (_frameCounter > maxCounter)
	{
		_playerImg->setFrameX(_playerImg->getFrameX() + 1);
		if (_playerImg->getFrameX() > endFrame)
		{
			_playerImg->setFrameX(beginFrame);
		}
		_frameCounter = 0;
	}
}