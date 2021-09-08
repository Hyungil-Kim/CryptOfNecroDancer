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
	_title = dynamic_cast<Title*>(SCENE->addScene("Ÿ��Ʋ", new Title, false));
	
	_sceneState = SCENESTATE::START;
	SCENE->changeScene("Ÿ��Ʋ");
	_rwm->setcurScene("Ÿ��Ʋ");
	if (_rwm->getcurScene() == "Ÿ��Ʋ");
		SOUND->play("������", 0.5);

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
	_rUI->release();
	_mon->release();
	_rwm->release();
	_boss->release();
	SAFE_DELETE(_mm);
	SAFE_DELETE(_mon);
	SAFE_DELETE(_rwm);
	SAFE_DELETE(_wm);
	SAFE_DELETE(_rUI);
	SAFE_DELETE(_boss);
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
	SCENE->update();
	map->update();
	POINT lerp;
	lerp.x = CAMERA->getPivotX() * (1 - 0.08) + PLAYER->getPlayerAddress().x *0.08;
	lerp.y = CAMERA->getPivotY() * (1 - 0.08) + PLAYER->getPlayerAddress().y * 0.08;
	CAMERA->movePivot(lerp.x, lerp.y);
	CAMERA->update();
	//CAMERA->movePivot(PLAYER->getPlayerAddress().x,PLAYER->getPlayerAddress().y);
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
	SCENE->render();
	PLAYERUI->render(getMemDC());
	PLAYER->render(getMapDC());
	ZORDER->ZorderTotalRender(getMapDC());
	this->getMapBuffer()->render(getMemDC(), 0, 0, CAMERA->getRect().left, CAMERA->getRect().top,
		RecWidth(CAMERA->getRect()), RecHeight(CAMERA->getRect())); _mon->render();

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
	_wm = dynamic_cast<wallManager*>(SCENE->addScene("1��", new wallManager));
	_boss = dynamic_cast<bossMap*>(SCENE->addScene("������", new bossMap));
	//map = new CMap;
	initForSound();
	
	PLAYER->init();
	_rUI->init();
	CAMERA->init(PLAYER->getPlayerAddress().x, PLAYER->getPlayerAddress().y, MAP_SIZE_X, MAP_SIZE_Y, 0, 0, WINSIZEX / 2, WINSIZEY / 2, CAMERASIZEX, CAMERASIZEY);
	_rwm->init();
	_wm->setrealWallManagerMemoryLink(_rwm);
	_boss->setrealWallManagerMemoryLink(_rwm);
	PLAYER->setmonsterManagerMemoryLink(_mm);
	_mon->init();
	_mm->setWallMemoryLink(_wm);
	_mm->setbossMapMemoryLink(_boss);
	//_wm->init();
	_rwm->setWallManagerMemoryLink(_wm);
	_rwm->setbossMapMemoryLink(_boss);
	PLAYER->setWallmanagerMemoryLink(_wm);
	PLAYER->setbossMapMemoryLink(_boss);
	PLAYER->setRealWallManagerMemoryLink(_rwm);
	_mm->setrealwallManagerMemoryLink(_rwm);
	_mm->init();
	_wm->setMonsterManagerMemoryLink(_mm);
	_boss->setMonsterManagerMemoryLink(_mm);
	_wm->setrtmMemoryLink(_rUI);
	_boss->setrtmMemoryLink(_rUI);
	PLAYER->setrtmMemoryLink(_rUI);
	_rUI->setwallManagerMemoryLink(_wm);
	PLAYER->setmonsterMemoryLink(_mon);
	_rUI->setMonsterManagerMemoryLink(_mm);
	_rUI->setbossMapMemoryLink(_boss);
	_mm->setrtmMemoryLink(_rUI);
	PLAYERUI->init();


}

void necroDancerMain::initForSound()
{
	SOUND->addSound("1��������","sound/zone1_1.ogg", true, true);
	SOUND->addSound("������", "sound/lobby.ogg", true, true);
	SOUND->addSound("������", "sound/boss_1.ogg", true, true);
	SOUND->addSound("����", "sound/ending.ogg", true, false);

}
