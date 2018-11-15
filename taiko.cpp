#include "stdafx.h"
#include "taiko.h"


taiko::taiko()
{
}


taiko::~taiko()
{

}

HRESULT taiko::init()
{
	IMAGEMANAGER->addImage("taikoBackground", ".\\images\\taikoBackground.bmp", 1024, 768, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("hitPoint", ".\\images\\hitPoint.bmp", 132, 132, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("taikoNote", ".\\images\\taikoNote.bmp", 528, 132, 4, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taikoExplodeLarge", ".\\images\\taikoExplodeLarge.bmp", 272, 272, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taikoExpodeSmall", ".\\images\\taikoExpodeSmall.bmp", 212, 212, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taikoGaugeBack", ".\\images\\taikoGaugeBack.bmp", 540, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("taikoOni", ".\\images\\taikoOni.bmp", 520, 100, 5, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("taikoGaugeRed", ".\\images\\taikoGaugeRed.bmp", 8, 24, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("taikoGaugeYellow", ".\\images\\taikoGaugeYellow.bmp", 156, 40, 13, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("mikuDancing", ".\\images\\mikuDancing.bmp", 2720, 283, 8, 1, true, RGB(255, 0, 255));

	SOUNDMANAGER->addSound("don", ".\\sounds\\don.wav", false, false);
	SOUNDMANAGER->addSound("tak", ".\\sounds\\tak.wav", false, false);
	SOUNDMANAGER->addSound("ghostRule", ".\\sounds\\ghostRule.mp3", true, false);
	SOUNDMANAGER->addSound("deadEnd", ".\\sounds\\deadEnd.mp3", true, false);

	_maxNote = 151;//INIDATA->loadDataInterger("note", "deadEnd", "maxNote");
	char noteNum[128];
	for (int i = 0; i < _maxNote; ++i)
	{
		wsprintf(noteNum, "note%d", i);
		tagTAIKO temp;
		temp.x = WINSIZEX;
		temp.y = 272;
		temp.noteType = INIDATA->loadDataInterger("note", noteNum, "Notetype");
		temp.timing = INIDATA->loadDataInterger("note", noteNum, "timer");
		temp.isHit = false;
		temp.miss = false;
		_note.push_back(temp);
	}

	_count = 0;
	_noteNumber = 0;
	_position = 0;
	_noteSpeed = 8;
	_hitPoint = 50;
	_currentNote = 0;
	_explodeCount = 10;
	_frameCount = 0;
	_frameX = 0;
	_score = 0;
	_isPlaying = false;
	_explode = false;

	return S_OK;
}

void taiko::release()
{

}

void taiko::update() 
{
	SOUNDMANAGER->getChannel(CH_BGM)->getPosition(&_position, FMOD_TIMEUNIT_MS);
	SOUNDMANAGER->getChannel(CH_BGM)->isPlaying(&_isPlaying);
	keyControl();
	noteControl();
	counter();
}

void taiko::render() 
{
	IMAGEMANAGER->render("taikoBackground", getMemDC());
	IMAGEMANAGER->frameRender("mikuDancing", getMemDC(), -23, 0, _frameX % 8, 0);
	IMAGEMANAGER->render("taikoGaugeBack", getMemDC(), 470, 200);
	drawScore();
	IMAGEMANAGER->render("hitPoint", getMemDC(), _hitPoint, 272);
	for (int i = 0; i < 20; ++i)
	{
		if (_currentNote + i >= _maxNote) continue;
		IMAGEMANAGER->frameRender("taikoNote", getMemDC(), _note[_currentNote + i].x, _note[_currentNote + i].y, _note[_currentNote + i].noteType, 0);
	}
	if (_explode == false && _explodeCount > 4 && _explodeCount < 10)
	{
		IMAGEMANAGER->render("taikoExpodeSmall", getMemDC(), _hitPoint - 40, 232);
	}
	if (_explode == true)
	{
		IMAGEMANAGER->render("taikoExplodeLarge", getMemDC(), _hitPoint - 70, 202);
	}


	/*
	char pos[128];
	wsprintf(pos, "%d", _position);
	TextOut(getMemDC(), WINSIZEX / 2, 0, pos, strlen(pos));
	*/
}

void taiko::keyControl()
{
	//autoNote
	//if (_isPlaying == true && _currentNote < _maxNote)
	//{
	//	if (_note[_currentNote].timing == _count)
	//	{
	//		if (_note[_currentNote].noteType == RED_LARGE || _note[_currentNote].noteType == RED_SMALL) SOUNDMANAGER->play("don", CH_DON1, 1.0f);
	//		if (_note[_currentNote].noteType == BLUE_LARGE || _note[_currentNote].noteType == BLUE_SMALL) SOUNDMANAGER->play("tak", CH_TAK1, 1.0f);
	//		_note[_currentNote].isHit = true;
	//		_score++;
	//		_currentNote++;
	//		_explodeCount = 0;
	//		_explode = true;
	//	}
	//}
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		SOUNDMANAGER->play("deadEnd", CH_BGM, 0.5f);
	}

	if (KEYMANAGER->isOnceKeyDown('Z') || KEYMANAGER->isOnceKeyDown('N'))
	{
		SOUNDMANAGER->play("don", CH_DON1, 1.0f);
		hitTaiko(RED_SMALL);
		//noteSave(1);
	}
	if (KEYMANAGER->isOnceKeyDown('M') || KEYMANAGER->isOnceKeyDown('X'))
	{
		SOUNDMANAGER->play("don", CH_DON2, 1.0f);
		hitTaiko(RED_SMALL);
		//noteSave(1);
	}
	if (KEYMANAGER->isOnceKeyDown('A') || KEYMANAGER->isOnceKeyDown('J'))
	{
		SOUNDMANAGER->play("tak", CH_TAK1, 1.0f);
		hitTaiko(BLUE_SMALL);
	}
	if (KEYMANAGER->isOnceKeyDown('K') || KEYMANAGER->isOnceKeyDown('S'))
	{
		SOUNDMANAGER->play("tak", CH_TAK2, 1.0f);
		hitTaiko(BLUE_SMALL);
	}

	if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
	{
		if (_noteSpeed > 2) _noteSpeed -= 2;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_RIGHT))
	{
		_noteSpeed += 2;
	}
	if (KEYMANAGER->isOnceKeyDown(VK_UP))
	{

	}
	if (KEYMANAGER->isOnceKeyDown(VK_DOWN))
	{

	}

	if (KEYMANAGER->isOnceKeyDown(VK_BACK))
	{
		SOUNDMANAGER->stop(CH_BGM);
		SCENEMANAGER->changeScene("WorldMap");
	}
}

void taiko::noteControl()
{
	if (_currentNote < _maxNote)
	{
		for (int i = 0; i < 20; ++i)
		{
			if (_currentNote + i >= _maxNote) continue;
			_note[_currentNote + i].x = _hitPoint + (_note[_currentNote + i].timing - _count) * _noteSpeed;
		}
		if (_note[_currentNote].x <= _hitPoint - (_noteSpeed * 4) && _note[_currentNote].isHit == false && _note[_currentNote].miss == false)
		{
			_note[_currentNote].miss = true;
		}
		if (_note[_currentNote].x < -132)
		{
			_currentNote++;
		}
	}
}

void taiko::counter()
{
	if (_isPlaying == true)
	{
		_count++;
	}
	if (_explodeCount < 10)
	{
		_explodeCount++;
		if (_explodeCount > 4) _explode = false;
	}
	_frameCount++;
	if (_frameCount % 6 == 0)
	{
		_frameX++;
		if (_frameX > 103) _frameX = 0;
		_frameCount = 0;
	}
}

void taiko::noteSave(int type)
{
	char timer[128];
	char noteNum[128];
	char noteType[128];
	char maxNote[128];
	wsprintf(timer, "%d", _count);
	wsprintf(noteNum, "note%d", _noteNumber);
	wsprintf(maxNote, "%d", _noteNumber);
	wsprintf(noteType, "%d", type);
	INIDATA->addData("deadEnd", "maxNote", maxNote);
	INIDATA->addData(noteNum, "timer", timer);
	INIDATA->addData(noteNum, "Notetype", noteType);
	INIDATA->iniSave("note");
	_noteNumber++;
}

void taiko::hitTaiko(int type)
{
	if (_note[_currentNote].noteType == type)
	{
		if (_note[_currentNote].x <= _hitPoint + (_noteSpeed * 4) && _note[_currentNote].x >= _hitPoint - (_noteSpeed * 4) && _note[_currentNote].miss == false && _note[_currentNote].isHit == false)
		{
			_note[_currentNote].isHit = true;
			_score++;
			_currentNote++;
			_explodeCount = 0;
			_explode = true;
		}
	}
}

void taiko::drawScore()
{
	float tempScore = (float)_score / (float)_maxNote * 50;
	if (tempScore > 40) tempScore = 40;
	for (int i = 0; i < (int)tempScore; ++i)
	{
		if (i < 31)
		{
			IMAGEMANAGER->render("taikoGaugeRed", getMemDC(), 474 + 12 * i, 232);
		}
		else
		{
			IMAGEMANAGER->frameRender("taikoGaugeYellow", getMemDC(), 474 + 12 * i, 216, _frameX % 13, 0);
		}
	}
	if (tempScore == 40) IMAGEMANAGER->frameRender("taikoOni", getMemDC(), 938, 180, _frameX % 4, 0);
}