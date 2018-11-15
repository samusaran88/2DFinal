#pragma once
#include "gameNode.h"

enum PLAYERIMAGE
{
	PEACH_BABY_CRAWL,
	PEACH_BABY_STROLLER,
	MARIO
};

enum PLAYERDIRECTION
{
	LEFT, RIGHT, DOWN, UP, 
	LEFT90 = 2, RIGHT90, LEFT180, RIGHT180, LEFT270, RIGHT270,
	LB = 0, LT, RB, RT
};

enum PLAYERSTATE
{
	IDLE, WALKING,
	RUNNING, JUMPING, FALLING
};

class player : public gameNode
{
private:
	int _playerDirection;
	int _playerState;
	int _frameCounter;
	float _playerSizeRate;
	image* _playerImg;

public:
	player();
	~player();

	HRESULT init(PLAYERIMAGE num, float playerSizeRate);
	void release();
	void updateWorldMap();
	void updateS1();
	void updateS2();
	void render(int fixY);

	void frameUpdate(int maxCounter, int beginFrame, int endFrame);

	inline void setPlayerDirection(int direction) { _playerDirection = direction; }
	inline int getPlayerDirection() { return _playerDirection; }
	inline void setPlayerState(int state) { _playerState = state; }
	inline void setPlayerFrame(int frameNum) { _playerImg->setFrameX(frameNum); }
};

