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
	int limit;
	int speed;
	int posx, posy;
	bool goleft = true;
	bool goright = true;
	bool gotop = true;
	bool gobottom = true;
	bool isSpawn;
	float _speed;
	float jumpPower = 500.f;
	float moveTime = 0.1f;
};
class wallManager;
class monster;
class Player :public Singleton<Player>
{
private:
	STATE _state;
	MOVESTATE _movestate;
	InputDirection _inputdirection;
	tagPlayer _player;
	int tileX;
	int tileY;

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
	int checkwall[30][30];
	int curTile;
private:
	bool _isDebug;
	wallManager* _wm;
	monster* _mon;
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
	 void playerMove();
	 void spawn();
	 void setWallmanagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	 void setmonsterMemoryLink(monster* monster) { _mon = monster; }
	tagPlayer& getPlayerAddress() { return _player; }
	
	 void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};