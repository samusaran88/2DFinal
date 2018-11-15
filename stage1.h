#pragma once
#include "gameNode.h"

#define S1TILESIZE 256

class mapTool;
class player;

class stage1 : public gameNode
{
private:
	float _playerX, _playerY;
	float _spinCenterX, _spinCenterY;
	float _loopX;
	float _vXp, _vYp;
	float _playerSpeed;
	float _playerAngleF;
	float _playerAngleB;
	float _jumpPower;
	float _gravity;
	float _hillAngle;
	int _playerState;
	int _jumpCount;
	bool _spin;

	mapTool * _mapTool;
	player* _player;

public:
	stage1();
	~stage1();

	HRESULT init();
	void release();
	void update();
	void render();

	void collision();
	void playerControl();
	void playerPhysics();

	inline void setMapToolMemoryAddressLink(mapTool* mt) { _mapTool = mt; }
	inline void setPlayerMemoryAddressLink(player* player) { _player = player; }
};

