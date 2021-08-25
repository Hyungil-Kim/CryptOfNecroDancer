#pragma once
#include "image.h"

static image* _backBuffer = IMAGE->addImage("backBuffer", WINSIZEX, WINSIZEY);
static image* _mapBuffer = IMAGE->addImage("mapBuffer", WINSIZEX, WINSIZEY);
static image* _tileBuffer = IMAGE->addImage("tileBuffer", MAP_SIZE_X, MAP_SIZE_Y);
static image* _DOLBuffer = IMAGE->addImage("DOLBuffer", MAP_SIZE_X, MAP_SIZE_Y);	//������ DC
class gameNode
{
private:
	HDC _hdc;
	bool _managerInit;
	RECT _rt;
public:
	gameNode();
	virtual ~gameNode();

	virtual HRESULT init();
	virtual HRESULT init(bool managerInit);
	virtual void release();
	virtual void update(); //����ϴ°�
	virtual void render(/*HDC hdc*/);


	image* getBackBuffer()const { return _backBuffer; }
	image* getMapBuffer()const { return _mapBuffer; }
	image* getTileBuffer()const { return _tileBuffer; }
	image* getDolBUffer()const { return _DOLBuffer; }
	HDC getHDC()const { return _hdc; }
	HDC getMemDC()const { return _backBuffer->getMemDC(); }
	HDC getMapDC()const { return _mapBuffer->getMemDC(); }
	HDC getTileDC()const { return _tileBuffer->getMemDC(); }
	HDC getDolDC()const { return _DOLBuffer->getMemDC(); }		//������ DC

	LRESULT MainProc(HWND hWnd, UINT imessage, WPARAM wParam, LPARAM lParam);
	RECT getClRect() { return _rt; }	//����â�� �簢�� ��������(0, 0, ����, ����)
};

