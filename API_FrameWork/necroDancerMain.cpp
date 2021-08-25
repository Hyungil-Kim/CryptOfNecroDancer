#include "framework.h"
#include "necroDancerMain.h"

necroDancerMain::necroDancerMain()
	:map(new CMap({ 35, 35 }, { TILE_SIZE_X, TILE_SIZE_Y }))
{
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
	
	PLAYER->release();

	SAFE_DELETE(_mm);

}

void necroDancerMain::update()
{
	_mm->update();
	map->update();
	PLAYER->update();
}

void necroDancerMain::render()
{
	_mm->render();
	map->render();
	this->getMapBuffer()->render(getMemDC(), 0, 0);
	PLAYER->render(getDolDC());
	ZORDER->ZorderTotalRender(getMemDC());
}

void necroDancerMain::gameinit()
{
	_mm = new monsterManager;

	
	
	
	PLAYER->init();
	_mm->init();




}
