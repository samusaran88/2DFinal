#pragma once
#include "gameNode.h"

enum TAIKO_NOTE_TYPE
{
	RED_LARGE, RED_SMALL, BLUE_LARGE, BLUE_SMALL
};

struct tagTAIKO
{
	int x;
	int y;
	int noteType;
	unsigned int timing;
	bool isHit;
	bool miss;
};

class taiko : public gameNode
{
private:
	unsigned int _count;
	unsigned int _position;
	unsigned int _noteNumber;
	unsigned int _currentNote;
	unsigned int _maxNote;
	
	int _hitPoint;
	int _noteSpeed;
	int _explodeCount;
	int _frameCount;
	int _frameX;
	int _score;

	bool _isPlaying;
	bool _explode;
	vector<tagTAIKO> _note;

public:
	taiko();
	~taiko();

	HRESULT init();
	void release();
	void update();
	void render();

	void keyControl();
	void noteControl();
	void counter();
	void noteSave(int type);
	void hitTaiko(int type);
	void drawScore();
};

