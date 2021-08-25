#pragma once
#include"singleton.h"

//struct tagstatus {
//
//	image* player_headL;
//	image* player_bodyL;
//	animation* Aplayer_headL;
//	animation* Aplayer_bodyL;
//
//	image* player_headR;
//	image* player_bodyR;
//	animation* Aplayer_headR;
//	animation* Aplayer_bodyR;
//
//	RECT player_head_rc;
//	RECT player_body_rc;
//	RECT player_rc;
//	int hp;
//	int atk;
//	int def;
//	int sight;
//	int sholve;
//	bool hitFireTile;
//	bool hitIceTile;
//};

enum class STATE {
	MOVE,
	STOP,
	ATTACK,
	DIGGING,
	HIT
};

enum class WEAPONTYPE{
	EMPTY,
	DAGGER,
	BSWORD,
	LSWORD,
	WIPE

};

enum MOVESTATE {
	LEFT,
	UP,
	RIGHT,
	DOWN
};

struct InputDirection {
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
};

struct tagPlayer
{
	RECT player_rc;
	WEAPONTYPE weapon;
	float x, y;
	bool hitFireTile = false;
	bool hitIceTile =false ;
	bool isCurrentRight;
	bool ishit = false;
	int hp;
	int atk;
	int def;
	int sight;
	int sholve;
	float _speed;
	float jumpPower = 500.f;
	float moveTime = 0.1f;
};
class dummyMap;
class Player :public Singleton<Player>
{
private:
	STATE _state;
	MOVESTATE _movestate;
	InputDirection _inputdirection;
	tagPlayer _player;
	dummyMap* _dummyMap;
private:
	image* player_headL;
	image* player_bodyL;
	animation* Aplayer_headL;
	animation* Aplayer_bodyL;

	image* player_headR;
	image* player_bodyR;
	animation* Aplayer_headR;
	animation* Aplayer_bodyR;

	RECT player_head_rc;
	RECT player_body_rc;
private:
	image* daggerEffect;
	animation* AdaggerEffect;
	RECT attackrange;
	int tileX, tileY;
	int curTileX, curTileY;
private:
	bool _isDebug;
public:
	 HRESULT init();
	 void release();
	 void update(); //계산하는곳
	 void render(HDC hdc);
	 void inputCheck();
	 void moveCharater();
	 void inputDirectionCheck();
	 void stateCheck();
	 void changeAttackRange();
	 void playMove();

	 void setdummyMapMemoryLink(dummyMap* dummyMap) { _dummyMap = dummyMap; }
	 void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};