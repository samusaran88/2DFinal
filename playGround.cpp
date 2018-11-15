#include "stdafx.h"
#include "playGround.h"


playGround::playGround()
{
}


playGround::~playGround()
{

}

HRESULT playGround::init()
{
	gameNode::init(true);

	_opening = new opening;
	_mapTool = new mapTool;
	_isoMapTool = new isoMapTool;
	_worldMap = new worldMap;
	_player = new player;
	_stage1 = new stage1;
	_taiko = new taiko;

	_worldMap->setMapToolMemoryAddressLink(_mapTool);
	_worldMap->setPlayerMemoryAddressLink(_player);
	_stage1->setMapToolMemoryAddressLink(_mapTool);
	_stage1->setPlayerMemoryAddressLink(_player);
	_isoMapTool->setPlayerMemoryAddressLink(_player);

	SCENEMANAGER->addScene("MapTool", _mapTool);
	SCENEMANAGER->addScene("isoMapTool", _isoMapTool);
	SCENEMANAGER->addScene("WorldMap", _worldMap);
	SCENEMANAGER->addScene("Stage1", _stage1);
	SCENEMANAGER->addScene("Taiko", _taiko);
	SCENEMANAGER->addScene("Opening", _opening);
	SCENEMANAGER->changeScene("Opening");



	return S_OK;
}

//메모리 관련 삭제
void playGround::release(void)
{
	gameNode::release();

}

//연산
void playGround::update(void)
{
	gameNode::update();

	//if (KEYMANAGER->isOnceKeyDown('M'))
	//{
	//	SCENEMANAGER->changeScene("MapTool");
	//}

	SCENEMANAGER->update();
}

//그리는거.......
void playGround::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, WHITENESS);
	//================== 이 위는 손대지 마시오 =========================

	SCENEMANAGER->render();
	//TIMEMANAGER->render(getMemDC());

	//================== 이 아래는 손대지 마시오 ========================
	this->getBackBuffer()->render(getHDC(), 0, 0);//hdc영역에 그려준다 
}
