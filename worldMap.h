#pragma once
#include "gameNode.h"

#define WMTILESIZE 64

class mapTool;
class player;

class worldMap : public gameNode
{
private:
	mapTool* _mapTool;
	player* _player;
	float _playerX, _playerY;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerControl();

	inline void setMapToolMemoryAddressLink(mapTool* mt) { _mapTool = mt; }
	inline void setPlayerMemoryAddressLink(player* player) { _player = player; }


	worldMap();
	~worldMap();
};

