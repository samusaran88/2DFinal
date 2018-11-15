#include "stdafx.h"
#include "stage1.h"
#include "worldMap.h"
#include "mapTool.h"
#include "player.h"


stage1::stage1()
{
}


stage1::~stage1()
{

}

HRESULT stage1::init()
{
	SOUNDMANAGER->addSound("kirbyFirstCourse", ".\\sounds\\kirbyFirstCourse.mp3", true, true);
	SOUNDMANAGER->play("kirbyFirstCourse", CH_BGM, 1.0f);
	IMAGEMANAGER->addImage("background", ".\\images\\backgroundSky.bmp", 1024, 768, true, RGB(255, 0, 255));
	_player->init(PEACH_BABY_STROLLER, 2.0f);
	_loopX = 0;
	_vXp = _vYp = 0;
	_spinCenterX = _spinCenterY = 0;
	_playerSpeed = 0; 
	_playerAngleF = 0;
	_playerAngleB = 0;
	_jumpPower = 0;
	_jumpCount = 0;
	_gravity = 0.4f;
	_hillAngle = 0;
	_playerState = FALLING;
	_spin = false;
	_mapTool->initS1();
	_playerX = 5 * S1TILESIZE - S1TILESIZE / 2;
	_playerY = 6 * S1TILESIZE - S1TILESIZE / 2;

	return S_OK;
}

void stage1::release()
{

}

void stage1::update() 
{
	_loopX += 0.1f;
	if (_loopX >= WINSIZEX) _loopX = 0;
	_player->updateS1();
	playerControl();
	collision();
	playerPhysics();
}

void stage1::render() 
{
	IMAGEMANAGER->findImage("background")->loopRender(getMemDC(), &RectMake(0, 0, WINSIZEX, WINSIZEY), _loopX, 0);
	_mapTool->drawTile(_playerX, _playerY, S1TILESIZE, true);
	_player->render(0);
}

void stage1::collision()
{
	//24, 36
	float y1, y2, yp, x1, x2, xp;
	bool detectHill;
	COLORREF color[3];
	int R[3], G[3], B[3];
	detectHill = true;
	x1 = x2 = y1 = y2 = xp = yp = 0;
	if (_spin == true)
	{
		float spinAngle;
		float spinDistance;
		float vXtemp1, vXtemp2, vYtemp1, vYtemp2;
		if (_spinCenterX == 0 && _spinCenterY == 0)
		{
			int xLeft, yLeft;
			xLeft = (int)_playerX % S1TILESIZE;
			yLeft = (int)_playerY % S1TILESIZE;
			_spinCenterX = _playerX - xLeft;
			_spinCenterY = _playerY - yLeft - 40;
		}
		spinDistance = getDistance(_spinCenterX, _spinCenterY, _playerX, _playerY);
		spinAngle = getAngleF(_spinCenterX, _spinCenterY, _playerX, _playerY);
		vXtemp1 = spinDistance * cosf(spinAngle);
		vYtemp1 = spinDistance * -sinf(spinAngle);
		spinAngle += 0.1f;
		vXtemp2 = spinDistance * cosf(spinAngle);
		vYtemp2 = spinDistance * -sinf(spinAngle);
		_vXp = vXtemp2 - vXtemp1;
		_vYp = vYtemp2 - vYtemp1;
	}
	else if (_spin == false)
	{
		color[0] = GetPixel(getPixelDC(), WINSIZEX / 2, WINSIZEY / 2 + 38);
		R[0] = GetRValue(color[0]);
		G[0] = GetGValue(color[0]);
		B[0] = GetBValue(color[0]);
		color[1] = GetPixel(getPixelDC(), WINSIZEX / 2 - 24, WINSIZEY / 2 + 38);
		R[1] = GetRValue(color[1]);
		G[1] = GetGValue(color[1]);
		B[1] = GetBValue(color[1]);
		color[2] = GetPixel(getPixelDC(), WINSIZEX / 2 + 24, WINSIZEY / 2 + 38);
		R[2] = GetRValue(color[2]);
		G[2] = GetGValue(color[2]);
		B[2] = GetBValue(color[2]);
		for (int i = 0; i < 3; ++i)
		{
			if (R[i] == 0 && G[i] == 255 && B[i] == 0)
			{
				break;
			}
			_playerState = FALLING;
		}
		if (_vYp >= 0)
		{
			for (int i = 0; i < 20; ++i)
			{
				color[0] = GetPixel(getPixelDC(), WINSIZEX / 2, WINSIZEY / 2 + 26 + i);
				R[0] = GetRValue(color[0]);
				G[0] = GetGValue(color[0]);
				B[0] = GetBValue(color[0]);
				if (R[0] == 0 && G[0] == 0 && B[0] == 255)
				{
					_playerY += i - 10;
					_jumpCount = 0;
					_spin = true;
					_playerState = RUNNING;
					break;
				}
				if (R[0] == 0 && G[0] == 255 && B[0] == 0)
				{
					_playerY += i - 10;
					_jumpCount = 1;
					_playerState = RUNNING;
					break;
				}
			}
		}
		for (int i = 0; i < 40; ++i)
		{
			color[0] = GetPixel(getPixelDC(), WINSIZEX / 2, WINSIZEY / 2 + 10 + i);
			R[0] = GetRValue(color[0]);
			G[0] = GetGValue(color[0]);
			B[0] = GetBValue(color[0]);
			if (R[0] == 0 && G[0] == 255 && B[0] == 0)
			{
				yp = i + 10;
				break;
			}
			if (i == 39)
			{
				detectHill = false;
			}
		}
		if (_vXp < 0)
		{
			for (int i = 0; i < 40; ++i)
			{
				color[1] = GetPixel(getPixelDC(), WINSIZEX / 2 - 16, WINSIZEY / 2 + 10 + i);
				R[1] = GetRValue(color[1]);
				G[1] = GetGValue(color[1]);
				B[1] = GetBValue(color[1]);
				if (R[1] == 0 && G[1] == 255 && B[1] == 0)
				{
					x1 = -16;
					y1 = i + 10;
					break;
				}
				if (i == 39)
				{
					detectHill = false;
				}
			}
			_hillAngle = getAngleF(0, yp, x1, y1);
		}
		if (_vXp >= 0)
		{
			for (int i = 0; i < 40; ++i)
			{
				color[2] = GetPixel(getPixelDC(), WINSIZEX / 2 + 16, WINSIZEY / 2 + 10 + i);
				R[2] = GetRValue(color[2]);
				G[2] = GetGValue(color[2]);
				B[2] = GetBValue(color[2]);
				if (R[2] == 0 && G[2] == 255 && B[2] == 0)
				{
					x2 = 16;
					y2 = i + 10;
					break;
				}
				if (i == 39)
				{
					detectHill = false;
				}
			}
			_hillAngle = getAngleF(0, yp, x2, y2);
		}
		if (detectHill == true && _playerState == RUNNING)
		{
			_vYp = _vXp * -tanf(_hillAngle);
			_playerSpeed = sqrtf(_vXp * _vXp + _vYp * _vYp);
			if (_hillAngle > 0)
			{
				_playerSpeed -= 0.05f;
				if (_playerSpeed < -15) _playerSpeed = -15;
			}
			else if (_hillAngle < 0)
			{
				_playerSpeed += 0.05f;
				if (_playerSpeed > 15) _playerSpeed = 15;
			}
			_vXp = _playerSpeed * cosf(_hillAngle);
			_vYp = _playerSpeed * (-sinf(_hillAngle));
		}
	}
}

void stage1::playerPhysics()
{
	if (_playerState == FALLING || _playerState == JUMPING)
	{
		_vYp += _gravity;
		if (_vYp > 10) _vYp = 10;
	}
	_playerSpeed = sqrtf(_vXp * _vXp + _vYp * _vYp);
	//if (_playerSpeed > 10) _playerSpeed = 10;
	_playerAngleF = getAngleF(0, 0, _vXp, _vYp);
	_playerX += _playerSpeed * cosf(_playerAngleF);
	_playerY -= _playerSpeed * sinf(_playerAngleF);
}

void stage1::playerControl()
{
	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		if (_jumpCount == 1)
		{
			_playerState = JUMPING;
			_vYp = -10;
			_jumpCount--;
		}
	}
	if (KEYMANAGER->isStayKeyDown(VK_LEFT))
	{
		_vXp -= 0.1;
		if (_vXp < -10) _vXp += 0.1;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_LEFT))
	{

	}
	if (KEYMANAGER->isStayKeyDown(VK_RIGHT))
	{
		_vXp += 0.1;
		if (_vXp > 10) _vXp -= 0.1;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_RIGHT))
	{

	}
	if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		_playerY += 5;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_DOWN))
	{

	}
	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		_playerY -= 5;
	}
	if (KEYMANAGER->isOnceKeyUp(VK_UP))
	{

	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("WorldMap");
	}
}