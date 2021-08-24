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

	_green_slime->addMonster(WINSIZEX / 2, WINSIZEY/2);
	return S_OK;
}

void monsterManager::release()
{
	_green_slime->release();
	SAFE_DELETE(_green_slime);
}

void monsterManager::update()
{
	_green_slime->update(_py);
}

void monsterManager::render()
{
	_green_slime->render();
}
