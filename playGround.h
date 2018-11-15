#pragma once
#include "gameNode.h"
#include "mapTool.h"
#include "isoMapTool.h"
#include "worldMap.h"
#include "player.h"
#include "stage1.h"
#include "taiko.h"
#include "opening.h"

class playGround : public gameNode
{
private:
	mapTool* _mapTool;
	isoMapTool* _isoMapTool;
	worldMap* _worldMap;
	player* _player;
	stage1* _stage1;
	taiko* _taiko;
	opening* _opening;

public:
	virtual HRESULT init(void);		//초기화 함수
	virtual void release(void);		//메모리 관련 해제
	virtual void update(void);		//업데이트(연산)
	virtual void render(void);		//그려주는 함수


	playGround();
	~playGround();
};

