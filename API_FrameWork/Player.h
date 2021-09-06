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
	int maxhp;
	int hp;
	int atk;
	int def;
	int sight;
	int sholve;
	int limit;
	int speed;
	int posx, posy;
	bool goleft;
	bool goright;
	bool gotop;
	bool gobottom;
	bool atkleft;
	bool atkright;
	bool atktop;
	bool atkbottom;
	bool isInput;
	bool isSpawn;
	bool isatk;
	float _speed;
	float jumpPower = 500.f;
	float moveTime = 0.1f;
};
class rhythmUI;
class wallManager;
class monsterManager;
class monster;
class realwallManager;
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

	image* player_dagAtk;
	animation* Aplayer_dagAtkL;
	animation* Aplayer_dagAtkU;
	animation* Aplayer_dagAtkD;
	animation* Aplayer_dagAtkR;
	RECT player_head_rc;
	RECT player_body_rc;
private:

	RECT attackrange;
	int checkwall[30][30];
	int curTile;
private:
	bool _isDebug;
	wallManager* _wm;
	monster* _mon;
	rhythmUI* _rtm;
	monsterManager* _mm;
	realwallManager* _rwm;
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
	 void Attack();
	 void giveDamage(int x, int y);
	 bool findMonster(monster* monster,int x, int y);
	 bool playerToMon(int x, int y);
	 void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	 void setWallmanagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	 void setRealWallManagerMemoryLink(realwallManager* realwallManager) { _rwm = realwallManager; }
	 void setmonsterMemoryLink(monster* monster) { _mon = monster; }
	 void setmonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	tagPlayer& getPlayerAddress() { return _player; }
	
	 void setIsDebug(bool isDebug) { _isDebug = isDebug; }


};