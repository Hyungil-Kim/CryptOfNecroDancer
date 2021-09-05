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
	_sceneState = SCENESTATE::START;
	SCENE->changeScene("타이틀");
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
	_wm->release();
	_mapm->release();
	_rUI->release();
	_mon->release();

	SAFE_DELETE(_mm);
	SAFE_DELETE(_mon);
	SAFE_DELETE(_wm);
	SAFE_DELETE(_rUI);
	SAFE_DELETE(_mapm);
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
	_wm->update();
	map->update();
	_mapm->update();
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
	_wm->render();
	_rUI->render();
	PLAYERUI->render(getMemDC());
	PLAYER->render(getMapDC());
	_mon->render();
	_mapm->render();
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
	_wm = new wallManager;
	_mon = new monster;
	_rUI = new rhythmUI;
	_mapm = new mapManager;
	initForSound();

	PLAYER->init();
	_rUI->init();
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, MAP_SIZE_X, MAP_SIZE_Y, 0, 0, WINSIZEX / 2, WINSIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	_wm->init();
	PLAYER->setmonsterManagerMemoryLink(_mm);
	_mon->init();
	_mm->setWallMemoryLink(_wm);
	PLAYER->setWallmanagerMemoryLink(_wm);
	_mm->init();
	_mapm->init();
	_wm->setMonsterManagerMemoryLink(_mm);
	_wm->setrtmMemoryLink(_rUI);
	PLAYER->setrtmMemoryLink(_rUI);
	_rUI->setwallManagerMemoryLink(_wm);
	PLAYER->setmonsterMemoryLink(_mon);
	_rUI->setMonsterManagerMemoryLink(_mm);
	_mm->setrtmMemoryLink(_rUI);
	PLAYERUI->init();
	_mapm->setWallManagerMemoryLink(_wm);
}

void necroDancerMain::initForSound()
{
	SOUND->addSound("1스테이지","sound/zone1_1.ogg", true, true);
	SOUND->addSound("오프닝", "sound/lobby.ogg", true, true);
	SOUND->addSound("보스전", "sound/boss_1.ogg", true, true);
	SOUND->addSound("엔딩", "sound/ending.ogg", true, false);
	SOUND->play("1스테이지", 0.5);
}
