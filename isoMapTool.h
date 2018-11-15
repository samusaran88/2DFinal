#pragma once
#include "gameNode.h"

#define TOTALa 30								//a축의 타일 총 갯수
#define TOTALb 30								//b축의 타일 총 갯수
#define TOTALh 30								//z축의 타일 총 갯수
#define DIAMONDWIDTH 16							//마름모 가로 길이 절반
#define DIAMONDHEIGHT 8							//마름모 세로 길이 절반
#define ISOTILEWIDTH 128						//맵에 깔릴 타일 가로 크기
#define ISOTILEHEIGHT 64						//맵에 깔릴 타일 세로 크기
#define EXTRA_Y_AXIS (DIAMONDHEIGHT * TOTALh)	//y축 여분

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

	//			깔릴 타일 정보, 깔릴 오브젝트 정보
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

