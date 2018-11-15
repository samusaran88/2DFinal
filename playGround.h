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
	virtual HRESULT init(void);		//�ʱ�ȭ �Լ�
	virtual void release(void);		//�޸� ���� ����
	virtual void update(void);		//������Ʈ(����)
	virtual void render(void);		//�׷��ִ� �Լ�


	playGround();
	~playGround();
};

