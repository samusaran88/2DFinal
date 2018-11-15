#pragma once
#include "gameNode.h"

#define TOTALa 30								//a���� Ÿ�� �� ����
#define TOTALb 30								//b���� Ÿ�� �� ����
#define TOTALh 30								//z���� Ÿ�� �� ����
#define DIAMONDWIDTH 16							//������ ���� ���� ����
#define DIAMONDHEIGHT 8							//������ ���� ���� ����
#define ISOTILEWIDTH 128						//�ʿ� �� Ÿ�� ���� ũ��
#define ISOTILEHEIGHT 64						//�ʿ� �� Ÿ�� ���� ũ��
#define EXTRA_Y_AXIS (DIAMONDHEIGHT * TOTALh)	//y�� ����

class player;

class isoMapTool : public gameNode
{
private:
	float _playerX;
	float _playerY;
	float _jumpPower;
	float _playerHeight;
	float _shadowHeight;

	int _playerFloor;
	int _playerDirection;

	int _playerTileNumA;
	int _playerTileNumB;
	int _minA, _maxA, _minB, _maxB;
	int _mouseNumA, _mouseNumB;
	int _tileNum;
	int _screenLeft;
	int _screenTop;
	int _screenRight;
	int _screenBottom;
	int _tileFrame;
	int _counter;
	int _wheelCounter;

	int _test;

	bool _runThread[3];
	bool _isDrawBackLayer;
	bool _isDrawBottomLayer;
	bool _isDrawFrontLayer;
	bool _isReadyBackLayer;
	bool _isReadyBottomLayer;
	bool _isReadyFrontLayer;
	bool _playerBlock[4];
	bool _isPointingUp;
	bool _isPointingDown;
	bool _isJump;
	bool _isFalling;

	//			�� Ÿ�� ����, �� ������Ʈ ����
	typedef map<unsigned int, unsigned int> TileInfo;
	typedef map<unsigned int, unsigned int>::iterator arrTileInfo;
	map<unsigned int, map<unsigned int, unsigned int>> _mMapTile;
	map<unsigned int, map<unsigned int, unsigned int>>::iterator _miMapTile;

	player* _player;
	image* _backLayer;
	image* _bottomLayer;
	image* _frontLayer; 
	image* _bufferBack;
	image* _bufferBottom;
	image* _bufferFront;
	image* _bufferBack2;
	image* _bufferBottom2;
	image* _bufferFront2;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	void playerControl();
	void drawBackLayer();
	void drawBottomLayer();
	void drawFrontLayer();
	void copyLayer();
	void minMaxCalculation();
	void activateThreadFunction();
	void frameCounter();
	void detectTile();
	void createTile();
	void drawMouseTile();
	void jumpPhysics();

	inline void setPlayerMemoryAddressLink(player* player) { _player = player; }
	inline bool getRunThread(int num) { return _runThread[num]; }
	inline void setRunThread(int num, bool trueOrFalse) { _runThread[num] = trueOrFalse; }


	static DWORD WINAPI threadFunc1(LPVOID lpParam);
	static DWORD WINAPI threadFunc2(LPVOID lpParam);
	static DWORD WINAPI threadFunc3(LPVOID lpParam);

	isoMapTool();
	~isoMapTool();
};

