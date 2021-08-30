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
	
}

void necroDancerMain::render()
{
	_mm->render();
	_wm->render();
	map->render();
	PLAYER->render(getMapDC());

	_mon->render();
	ZORDER->ZorderTotalRender(getMapDC());
	this->getMapBuffer()->render(getMemDC(), 0, 0,CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));

	//_mapBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
	//	RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
	//IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);
}

void necroDancerMain::gameinit()
{
	_mm = new monsterManager;
	_wm = new wallManager;
	_mon = new monster;
	PLAYER->init();
	CAMERA->init(PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y,MAP_SIZE_X, MAP_SIZE_Y,0,0,WINSIZEX/2,WINSIZEY/2,CAMERASIZEX,CAMERASIZEY);
	_wm->init();
	_mon->init();
	PLAYER->setWallmanagerMemoryLink(_wm);
	PLAYER->setmonsterMemoryLink(_mon);
	_mm->setWallMemoryLink(_wm);
	_mm->init();
	_wm->setMonsterManagerMemoryLink(_mm);
	
}
