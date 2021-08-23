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
	PLAYER->init();
	return S_OK;
}

void necroDancerMain::release()
{
	PLAYER->release();
}

void necroDancerMain::update()
{
	PLAYER->update();
}

void necroDancerMain::render()
{
	PLAYER->render();
	ZORDER->ZorderTotalRender(getMemDC());
}
