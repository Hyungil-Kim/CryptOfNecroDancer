#include "framework.h"
#include "mapManager.h"
#include "monsterManager.h"
#include "wallManager.h"
#include "rhythmUI.h"
mapManager::mapManager()
{
}

mapManager::~mapManager()
{
}

HRESULT mapManager::init()
{


	_wm = dynamic_cast<wallManager*>(SCENE->addScene("1Ãþ", new wallManager,false));
	_wm->setMonsterManagerMemoryLink(_mm);
	_wm->setrealWallManagerMemoryLink(_rwm);
	_wm->setrtmMemoryLink(_rtm);

	

	return S_OK;
}

void mapManager::release()
{
	SCENE->release();
}

void mapManager::update()
{
	SCENE->update();
}

void mapManager::render()
{
	SCENE->render();
}
