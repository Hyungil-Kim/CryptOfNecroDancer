#include "framework.h"
#include "monsterManager.h"
#include "wallManager.h"
#include "monster.h"
#include "rhythmUI.h"
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

	_green_slime->setwallManagerMemoryLink(_wm);
	_blue_slime->setwallManagerMemoryLink(_wm);
	_orange_slime->setwallManagerMemoryLink(_wm);
	_white_skeleton->setwallManagerMemoryLink(_wm);
	_green_slime->setmonsterManagerMemoryLink(this);
	_blue_slime->setmonsterManagerMemoryLink(this);
	_orange_slime->setmonsterManagerMemoryLink(this);
	_white_skeleton->setmonsterManagerMemoryLink(this);
	_white_skeleton->setrtmMemoryLink(_rtm);
	return S_OK;
}

void monsterManager::release()
{
	_green_slime->release();
	_blue_slime->release();
	_orange_slime->release();
	_white_skeleton->release();
	SAFE_DELETE(_green_slime);
	SAFE_DELETE(_blue_slime);
	SAFE_DELETE(_orange_slime);
	SAFE_DELETE(_white_skeleton);
}

void monsterManager::update()
{
	_green_slime->update(_py);
	_blue_slime->update(_py);
	_orange_slime->update(_py);
	_white_skeleton->update(_py,_rtm);
}

void monsterManager::render()
{
	_green_slime->render();
	_blue_slime->render();
	_orange_slime->render();
	_white_skeleton->render();
}

void monsterManager::spawn()
{
}
