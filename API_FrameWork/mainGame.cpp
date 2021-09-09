#include "framework.h"
#include "mainGame.h"

mainGame::mainGame()
{
	_finalBuffer = IMAGE->addImage("final", WINSIZEX*2, WINSIZEY*2);
}

mainGame::~mainGame()
{
}

HRESULT mainGame::init()
{

	gameNode::init(true);	//필요한동적할당
	_necroMain = new necroDancerMain;
	_necroMain->init();
	return S_OK;
}

void mainGame::release()
{
	gameNode::release();	//해제
	SAFE_DELETE(_necroMain);
}

void mainGame::update()
{
	gameNode::update();


	_necroMain->update();
	ANIMATION->update();



	setIsDebug();
	setFPSprint();
	//======================================================================//
	INPUT->setAnyKeyDown(false);
	//======================================================================//
}

void mainGame::render(/*HDC hdc*/)	//그림그리는곳
{
	PatBlt(getMemDC(), 0, 0, WINSIZEX, WINSIZEY, BLACKNESS);
	PatBlt(_finalBuffer->getMemDC(), 0, 0, _finalBuffer->getWidth(), _finalBuffer->getHeight(), BLACKNESS);
	//========================================================
						/*렌더링 공간*/
	_necroMain->render();



	//RECT rc = checkGameSize();
	//RECT wrc = getClRect();
	//HBRUSH brush = CreateSolidBrush(MINT);
	//HBRUSH oldBrush = (HBRUSH)SelectObject(_finalBuffer->getMemDC(), brush);
	//RectangleMake(_finalBuffer->getMemDC(), rc);
	//SelectObject(_finalBuffer->getMemDC(), oldBrush);
	//DeleteObject(brush);
	//TCHAR str[128];
	//wsprintf(str, "%d, %d, %d, %d", rc.left, rc.top, rc.right, rc.bottom);
	//TextOut(getMemDC(), 0, 0, str, lstrlen(str));
	//wsprintf(str, "윈렉트 %d, %d, %d, %d", wrc.left, wrc.top, wrc.right, wrc.bottom);
	//TextOut(getMemDC(), 0, 20, str, lstrlen(str));
	//========================================================
	RECT rc = checkGameSize();
	this->getBackBuffer()->stretchRender(_finalBuffer->getMemDC(), RecCenX(rc), RecCenY(rc), RecWidth(rc), RecHeight(rc));
	if (_showFPS) TIME->render(_finalBuffer->getMemDC());
	//백퍼버의 내용을 HDC에 그린다. (건드리지 말것)
	_finalBuffer->render(getHDC());
}

RECT mainGame::checkGameSize()
{
	RECT rc = this->getClRect();
	float wid = rc.right;
	float hei = rc.bottom;
	float widOverHei = (float)GAMESIZEX / GAMESIZEY;
	float heiOverWid = (float)GAMESIZEY / GAMESIZEX;
	
	float w, h;
	//현재 가로에 맞춘 세로가 현재 창의 세로보다 크다면, 현재 세로에 맞춘다.
	(wid * heiOverWid > hei) ? w = hei * widOverHei, h = hei
		: w = wid, h = w * heiOverWid;

	int left, top, right, bottom;
	if (w < wid) {
		left = wid / 2 - w / 2;
		right = left + w;
		top = 0;
		bottom = h;
	}
	else {
		left = 0;
		right = w;
		top = hei / 2 - h / 2;
		bottom = top + h;
	}
	//MoveWindow(gethwnd(), left, top, right, bottom, TRUE);    // listbox의 size를 change
	return { left, top, right, bottom };


}

