#include "framework.h"
#include "monsterManager.h"

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

	_green_slime->addMonster(49*10+1, 49*10+1);
	_blue_slime->addMonster(49*11,49*10+1);
	_orange_slime->addMonster(49*13-2,49*10+1);
	return S_OK;
}

void monsterManager::release()
{
	_green_slime->release();
	_blue_slime->release();
	_orange_slime->release();
	SAFE_DELETE(_green_slime);
	SAFE_DELETE(_blue_slime);
	SAFE_DELETE(_orange_slime);
}

void monsterManager::update()
{
	_green_slime->update(_py);
	_blue_slime->update(_py);
	_orange_slime->update(_py);
}

void monsterManager::render()
{
	_green_slime->render();
	_blue_slime->render();
	_orange_slime->render();
}
