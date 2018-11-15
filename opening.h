#pragma once
#include "gameNode.h"

class opening : public gameNode
{
private:

public:
	opening();
	~opening();

	HRESULT init();
	void release();
	void update();
	void render();
};

