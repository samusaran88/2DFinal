#include "stdafx.h"
#include "opening.h"


opening::opening()
{
}


opening::~opening()
{

}

HRESULT opening::init()
{
	IMAGEMANAGER->addImage("opening", ".\\images\\opening.bmp", 1024, 768, true, RGB(255, 0, 255));
	SOUNDMANAGER->addSound("simCityTitleTheme", ".\\sounds\\simCityTitleTheme.mp3", true, true);
	SOUNDMANAGER->play("simCityTitleTheme", CH_BGM, 1.0f);
	return S_OK;
}

void opening::release()
{

}

void opening::update() 
{
	if (KEYMANAGER->isOnceKeyDown(VK_RETURN))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("WorldMap");
	}
}

void opening::render() 
{
	IMAGEMANAGER->render("opening", getMemDC());
}
