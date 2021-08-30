#include "framework.h"
#include "necroDancerMain.h"

necroDancerMain::necroDancerMain()
 	:map(new CMap({25,25 }, { TILE_SIZE_X, TILE_SIZE_Y }))
{
	//IMAGE->addImage("SCORPDC", WINSIZEX * 3, WINSIZEY * 3);
}

necroDancerMain::~necroDancerMain()
{
}

HRESULT necroDancerMain::init()
{
	gameinit();

	return S_OK;
}

void necroDancerMain::release()
{
	_mm->release();
	_wm->release();
	PLAYER->release();
	RHYTHMUI->release();
	_mon->release();
	SAFE_DELETE(_mm);
	SAFE_DELETE(_mon);

}

void necroDancerMain::update()
{
	_mm->update();
	_wm->update();
	map->update();

	CAMERA->movePivot(PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y);
	CAMERA->update();
	PLAYER->update();
	_mon->update(PLAYER);
	RHYTHMUI->update();
	
}

void necroDancerMain::render()
{
	_mm->render();
	_wm->render();
	map->render();
	PLAYER->render(getMapDC());
	_mon->render();
	RHYTHMUI->render(getMemDC());
	ZORDER->ZorderTotalRender(getMapDC());
	this->getMapBuffer()->render(getMemDC(), 0, 0,CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));

	//_mapBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
	//	RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
	//IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);
	ZORDER->ZorderUITotalRender(getMemDC());
}

void necroDancerMain::gameinit()
{
	_mm = new monsterManager;
	_wm = new wallManager;
	_mon = new monster;
	RHYTHMUI->init();
	PLAYER->init();
	CAMERA->init(PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y,MAP_SIZE_X, MAP_SIZE_Y,0,0,WINSIZEX/2,WINSIZEY/2,CAMERASIZEX,CAMERASIZEY);
	_wm->init();
	PLAYER->setmonsterMemoryLink(_mon);
	_mon->init();
	_mm->setWallMemoryLink(_wm);
	PLAYER->setWallmanagerMemoryLink(_wm);
	_mm->init();
	_wm->setMonsterManagerMemoryLink(_mm);
	RHYTHMUI->setwallManagerMemoryLink(_wm);
}
