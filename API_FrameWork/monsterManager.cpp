#include "framework.h"
#include "monsterManager.h"
#include "wallManager.h"
#include "monster.h"
#include "rhythmUI.h"
#include "bossMap.h"
#include "realwallManager.h"
monsterManager::monsterManager()
{

}

monsterManager::~monsterManager()
{
}

HRESULT monsterManager::init()
{
	_green_slime = new green_slime;
	_blue_slime = new blue_slime;
	_orange_slime = new orange_slime;
	_white_skeleton = new white_skeleton;
	_green_dragon = new green_dragon;
	_king_konga = new king_konga;


	_green_slime->setwallManagerMemoryLink(_wm);
	_blue_slime->setwallManagerMemoryLink(_wm);
	_orange_slime->setwallManagerMemoryLink(_wm);
	_white_skeleton->setwallManagerMemoryLink(_wm);
	_green_dragon->setwallManagerMemoryLink(_wm);
	_king_konga->setwallManagerMemoryLink(_wm);
	_green_slime->setbossMapMemoryLink(_boss);
	_blue_slime->setbossMapMemoryLink(_boss);
	_orange_slime->setbossMapMemoryLink(_boss);
	_white_skeleton->setbossMapMemoryLink(_boss);
	_green_dragon->setbossMapMemoryLink(_boss);
	_king_konga->setbossMapMemoryLink(_boss);
	_green_slime->setmonsterManagerMemoryLink(this);
	_blue_slime->setmonsterManagerMemoryLink(this);
	_orange_slime->setmonsterManagerMemoryLink(this);
	_white_skeleton->setmonsterManagerMemoryLink(this);
	_green_dragon->setmonsterManagerMemoryLink(this);
	_king_konga->setmonsterManagerMemoryLink(this);
	_white_skeleton->setrtmMemoryLink(_rtm);
	_green_dragon->setrtmMemoryLink(_rtm);
	_king_konga->setrtmMemoryLink(_rtm);
	_green_dragon->setrealwallManagerMemoryLink(_rwm);
	_king_konga->setrealwallManagerMemoryLink(_rwm);
	return S_OK;
}

void monsterManager::release()
{
	_green_slime->release();
	_blue_slime->release();
	_orange_slime->release();
	_white_skeleton->release();
	_green_dragon->release();
	_king_konga->release();
	SAFE_DELETE(_green_slime);
	SAFE_DELETE(_blue_slime);
	SAFE_DELETE(_orange_slime);
	SAFE_DELETE(_white_skeleton);
	SAFE_DELETE(_green_dragon);
	SAFE_DELETE(_king_konga);
}

void monsterManager::update()
{
	_green_slime->update(_py);
	_blue_slime->update(_py);
	_orange_slime->update(_py);
	_white_skeleton->update(_rtm);
	_green_dragon->update(_rtm);
	_king_konga->update(_rtm);
}

void monsterManager::render()
{
	_green_slime->render();
	_blue_slime->render();
	_orange_slime->render();
	_white_skeleton->render();
	_green_dragon->render();
	_king_konga->render();
}
