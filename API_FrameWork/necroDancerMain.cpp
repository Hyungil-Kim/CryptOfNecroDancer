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
	_mm->release();
	
	PLAYER->release();

	SAFE_DELETE(_mm);

}

void necroDancerMain::update()
{
	_mm->update();
	
	PLAYER->update();
}

void necroDancerMain::render()
{
	_mm->render();
	
	PLAYER->render(getMemDC());
	ZORDER->ZorderTotalRender(getMemDC());
}

void necroDancerMain::gameinit()
{
	_mm = new monsterManager;

	
	
	
	PLAYER->init();
	_mm->init();




}
