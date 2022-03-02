#pragma once
class breed
{
private:
	breed* _parent;
	int _health;

	int _atk;
	int _gold;
	image _image;
	animation _ani;
	bool _islight;

public:
	breed(breed* parent, int health,int atk,int gold, image image, animation ani, bool islight)
		:_parent(parent),
		_health(health),
		_atk(atk),
		_gold(gold),
		_image(image),
		_ani(ani),
		_islight(islight)
	{
		if (parent != NULL) {
			if (health == 0)
				_health = parent->getHealth();
			if (atk == 0)
				_atk = parent->getAtk();
			if (gold == 0)
				_gold = parent->getGold();
			if (_islight == 0)
				_islight = parent->getIslight();
		}
	};


	HRESULT init();
	void release();
	void update();
	void render(/*HDC hdc*/);
	void gameinit();
	void setIsDebug(bool isDebug) {}


	int getHealth() { return _health; }
	int getAtk() { return _atk; }
	int getGold() { return _gold; }
	image getImage() { return _image; }
	animation getAni() { return _ani; }
	bool getIslight() { return _islight; }
};

