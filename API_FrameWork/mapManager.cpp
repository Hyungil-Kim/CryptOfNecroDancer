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
	_wm = dynamic_cast<wallManager*>(SCENE->addScene("1Ãþ", new wallManager));
	_wm->setMonsterManagerMemoryLink(_mm);
	_wm->setrealWallManagerMemoryLink(_rwm);
	_wm->setrtmMemoryLink(_rtm);
	_bossmap = dynamic_cast<bossMap*>(SCENE->addScene("º¸½º¹æ", new bossMap));
	_bossmap->setMonsterManagerMemoryLink(_mm);
	_bossmap->setrealWallManagerMemoryLink(_rwm);
	_bossmap->setrtmMemoryLink(_rtm);
	

	return S_OK;
}

void mapManager::release()
{
}

void mapManager::update()
{
}

void mapManager::render()
{
}
