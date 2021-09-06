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
	_title = dynamic_cast<Title*>(SCENE->addScene("타이틀", new Title, false));
	_boss  =  dynamic_cast<bossMap*>(SCENE->addScene("보스방", new bossMap, false));
	_boss->setMonsterManagerMemoryLink(_mm);
	_boss->setrealWallManagerMemoryLink(_rwm);
	_boss->setrtmMemoryLink(_rUI);

	_sceneState = SCENESTATE::START;
	SCENE->changeScene("타이틀");
		SOUND->play("오프닝", 0.5);

	return S_OK;
}

void necroDancerMain::release()
{
	switch (_sceneState)
	{
	case necroDancerMain::SCENESTATE::START:
		break;
	case necroDancerMain::SCENESTATE::GAME:
	_mm->release();

	_rUI->release();
	_mon->release();
	_rwm->release();
	_map->release();
	SAFE_DELETE(_mm);
	SAFE_DELETE(_mon);
	SAFE_DELETE(_rwm);
	SAFE_DELETE(_wm);
	SAFE_DELETE(_rUI);
		break;
	case necroDancerMain::SCENESTATE::ENDING:
		break;
	default:
		break;
	}

}

void necroDancerMain::update()
{
	if (_sceneState == SCENESTATE::START && _title->getIsDone()) {
		_sceneState = SCENESTATE::GAME;
	}
	switch (_sceneState)
	{
	case necroDancerMain::SCENESTATE::START:
	SCENE->update();
	
		break;
	case necroDancerMain::SCENESTATE::GAME:
	_mm->update();
	_rUI->update();
	_rwm->update();

	map->update();
	_map->update();
	CAMERA->movePivot(PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y);
	CAMERA->update();
	PLAYER->update();
	PLAYERUI->update();
	_mon->update(PLAYER);
		break;
	case necroDancerMain::SCENESTATE::ENDING:
		break;
	default:
		break;
	}
}

void necroDancerMain::render()
{
	switch (_sceneState)
	{
	case necroDancerMain::SCENESTATE::START:
	SCENE->render();
		break;
	case necroDancerMain::SCENESTATE::GAME:
	_mm->render();
	map->render();
	_rwm->render();
	_rUI->render();
	_map->render();
	PLAYERUI->render(getMemDC());
	PLAYER->render(getMapDC());
	_mon->render();
	ZORDER->ZorderTotalRender(getMapDC());
	this->getMapBuffer()->render(getMemDC(), 0, 0,CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
		break;
	case necroDancerMain::SCENESTATE::ENDING:
		break;
	default:
		break;
	}

	//_mapBuffer->render(IMAGE->findImage("SCORPDC")->getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
	//	RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect()));
	//IMAGE->findImage("SCORPDC")->stretchRenderXY(getMemDC(), 0, 0, GAMEDCRATIO);

	ZORDER->ZorderUITotalRender(getMemDC());
}

void necroDancerMain::gameinit()
{
	_mm = new monsterManager;
	_rwm = new realwallManager;
	_mon = new monster;
	_rUI = new rhythmUI;
	_map = new mapManager;
	initForSound();

	PLAYER->init();
	_rUI->init();
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, MAP_SIZE_X, MAP_SIZE_Y, 0, 0, WINSIZEX / 2, WINSIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	_rwm->init();
	_mon->init();
	_mm->init();
	PLAYERUI->init();
	_map->init();
	_map->setMonsterManagerMemoryLink(_mm);
	_map->setrealWallManagerMemoryLink(_rwm);
	_map->setrhythmMemoryLink(_rUI);
	PLAYER->setmonsterManagerMemoryLink(_mm);
	PLAYER->setRealWallManagerMemoryLink(_rwm);
	PLAYER->setrtmMemoryLink(_rUI);
	PLAYER->setmonsterMemoryLink(_mon);
	_rUI->setMonsterManagerMemoryLink(_mm);
	_mm->setrtmMemoryLink(_rUI);

}

void necroDancerMain::initForSound()
{
	SOUND->addSound("1스테이지","sound/zone1_1.ogg", true, true);
	SOUND->addSound("오프닝", "sound/lobby.ogg", true, true);
	SOUND->addSound("보스전", "sound/boss_1.ogg", true, true);
	SOUND->addSound("엔딩", "sound/ending.ogg", true, false);

}
