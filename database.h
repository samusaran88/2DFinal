#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//elements == �Ӽ��� 
class elements
{
public:


	elements() {};
	~elements() {};
};

//���� �̱��� DB �����д�
class database : public singletonBase <database>
{
private:
	typedef vector<string> arrElements;
	typedef vector<string>::iterator iterElements;

	typedef map<string, elements*> arrElement;
	typedef map<string, elements*>::iterator iterElement;

private:
	arrElement _mTotalElement;


public:
	HRESULT init();
	void release();

	database();
	~database();
};

