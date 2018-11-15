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
	int _cameraX, _cameraY;											//�� ī�޶� ��ǥ
	int _pageX, _pageY;												//Ÿ�� ������ �ѹ�
	int _currentTileMapNum;											//���� Ÿ�ϸ� �ѹ�
	int _selectTileNumX, _selectTileNumY;							//������ Ÿ�� �ѹ�
	int _currentFrameX;												//���� ������ ���� ��ȣ
	unsigned int _frameCounter;										//������ ���� ī����
	bool _isObjectTile;												//���� Ÿ���� ������Ʈ Ÿ������									
	bool _isFrameTile;												//���� Ÿ���� ������ Ÿ������
	bool _isBlocked;												//���� Ÿ���� ���� Ÿ������
	bool _isDeleteTile;												//���� Ÿ���� ���� ������
	vector<unsigned int> _vUsedTile;								//���� Ÿ�ϵ��� ����
	vector<tagIMAGEINFO> _vTileImage;								//Ÿ�ϼ� ��� �� �� ���� ���� ����
	vector<unsigned int> _vTileInfo;								//�� Ÿ�� ���� ���� ����
	//map<pair<int, int>, vector<unsigned int>> _mMapTile;			//�� ��ǥ�� �� Ÿ�� ��ȣ ���� ��
	//map<pair<int, int>, vector<unsigned int>>::iterator _miMapTile;	//���ͷ�����

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

