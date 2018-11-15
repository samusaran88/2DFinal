#pragma once
#include "gameNode.h"
#include <commdlg.h>
#include <vector>
#include <map>

#define MAXTILENUM 2

struct tagIMAGEINFO
{
	TCHAR keyName[255];
	TCHAR directory[255];
	int tileWidth;													
	int imageWidth;
	int imageHeight;
	int imageFrameX;
	int imageFrameY;
	int imageFrameSpace;
};

class mapTool : public gameNode
{
private:
	int _cameraX, _cameraY;											//맵 카메라 좌표
	int _pageX, _pageY;												//타일 페이지 넘버
	int _currentTileMapNum;											//현재 타일맵 넘버
	int _selectTileNumX, _selectTileNumY;							//선택한 타일 넘버
	int _currentFrameX;												//현재 프레임 순서 번호
	unsigned int _frameCounter;										//프레임 돌릴 카운터
	bool _isObjectTile;												//현재 타일이 오브젝트 타일인지									
	bool _isFrameTile;												//현재 타일이 프레임 타일인지
	bool _isBlocked;												//현재 타일이 막힌 타일인지
	bool _isDeleteTile;												//현재 타일을 지울 것인지
	vector<unsigned int> _vUsedTile;								//사용된 타일들을 저장
	vector<tagIMAGEINFO> _vTileImage;								//타일셋 경로 및 맵 정보 저장 벡터
	vector<unsigned int> _vTileInfo;								//깔릴 타일 정보 저장 벡터
	//map<pair<int, int>, vector<unsigned int>> _mMapTile;			//맵 좌표에 깔릴 타일 번호 저장 맵
	//map<pair<int, int>, vector<unsigned int>>::iterator _miMapTile;	//이터레이터

	map<unsigned int, pair<unsigned int, unsigned int>> _mMapTile;
	map<unsigned int, pair<unsigned int, unsigned int>>::iterator _miMapTile;

public:
	HRESULT init();
	HRESULT initWorldMap();
	HRESULT initS1();
	void release();
	void update();
	void render();

	void drawTile();
	void drawTile(int playerX, int playerY, int tileWidth, bool pixelCollision = FALSE);
	void drawMenu();
	void drawText(int fontSize, char* str, RECT rc, int position);
	void keyControl();
	void newMap();
	void save();
	void load();
	void load(string fileName);
	void frameUpdate();
	tagIMAGEINFO addImageInfo(int imageNum);

	inline map<unsigned int, pair<unsigned int, unsigned int>> getMapTile() { return _mMapTile; }

	mapTool();
	~mapTool();
};

