#pragma once
#include "singletonBase.h"
#include <vector>
#include <map>

//elements == ¼Ó¼ºµé 
class elements
{
public:


	elements() {};
	~elements() {};
};

//³»ºÎ ½Ì±ÛÅæ DB ¸¸µé¾îµÐ´Ù
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

