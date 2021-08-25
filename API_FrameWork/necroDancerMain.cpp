#include "framework.h"
#include "necroDancerMain.h"

necroDancerMain::necroDancerMain()
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

	_dmap->release();
	PLAYER->release();

	
	SAFE_DELETE(_dmap);
}

void necroDancerMain::update()
{
	
	_dmap->update();
	PLAYER->update();
}

void necroDancerMain::render()
{

	_dmap->render();
	PLAYER->render(getMemDC());
	ZORDER->ZorderTotalRender(getMemDC());
}

void necroDancerMain::gameinit()
{
	
	_dmap = new dummyMap;
	
	
	
	PLAYER->init();

	_dmap->init();

	PLAYER->setdummyMapMemoryLink(_dmap);

}
