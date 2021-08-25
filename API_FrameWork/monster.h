#pragma once
#include "breed.h"
class monster
{
	friend class breed;
private:
	monster(breed& breed)
		:_health(breed.getHealth()),
		_atk(breed.getAtk()),
		_gold(breed.getGold()),
		_image(breed.getImage()),
		_ani(breed.getAni()),
		_islight(breed.getIslight()),
		_breed(breed) {}

	int _health;
	int _atk;
	int _gold;
	image _image;
	animation _ani;
	bool _islight;

	breed& _breed;
public:

	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);
	void gameinit();
	void setIsDebug(bool isDebug) {}
};

