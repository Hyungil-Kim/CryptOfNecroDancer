#pragma once
#include"CObstacle.h"
#define INVINTIME 40

class Player;
class wallManager;
class rhythmUI;
enum class MONSTERSTATE {
	MOVE,
	STOP,
	ATTACK,
	DIGGING,
	HIT,
	DEAD
};

enum class MONSTERMOVESTATE {
	NONE,
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct tagMonster
{
	image* img;
	animation* ani;
	animation* leftani;
	animation* shadowani;
	animation* leftshadowani;

	image* _atkup;
	image* _atkleft;

	animation* A_atkup;
	animation* A_atkleft;
	animation* A_atkright;
	animation* A_atkdown;

	RECT rc;
	int x, y;
	int posx, posy;

	int hp;
	int atk;
	int speed;
	int limit;
	//int def; 확인후 삭제
	
	bool canleft = false;
	bool canright = false;
	bool canup = false;
	bool candown = false;
	
	bool canBreakWall = false;
	bool isDetecting = false;
	bool isHit = false;
	bool isDead = false;
	bool isCurrentRight;
	bool isMove = false;
	bool isOnceMove = false;
	bool AniLeft = false;
	
	bool atkup = false;
	bool atkdown = false;
	bool atkleft = false;
	bool atkright = false;
	bool isGraceperiod = false;			
	int gracePeriodCount = 0;
	int movecount = 0;
	MONSTERSTATE monsterState;
	MONSTERMOVESTATE monsterMoveState;
};
class monsterManager;
class monster : public CObstacle
{
protected:
	vector<tagMonster> _vMonster;
	vector<tagMonster>::iterator _viMonster;
	bool _isDebug;
	wallManager* _wm;
	monsterManager* _mm;
	rhythmUI* _rtm;
	
public:
	monster();
	~monster();

	HRESULT init();
	void release();
	void update(Player* cp);//플레이어 위치 참고하기위해 
	void render();
	
	virtual void addMonster(float x, float y);
	virtual void move();
	virtual void stateCheck();
	virtual void moveMonster();
	virtual void isCanMove();
	virtual void isCanMove2();
	
	virtual bool findPlayer(int x , int y);
	virtual bool findMonster(monster* monster, int x, int y);
	virtual bool monTomon(int x, int y);
	virtual void attack();
	virtual void getDamage();
	virtual void setdirection();
	virtual void checkInvincibility();
	virtual void deathcheck();
	virtual void setmonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	virtual void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	virtual void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	vector<tagMonster>& getVMonster() { return _vMonster; }
	vector<tagMonster>::iterator& getVIMonster() { return _viMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

};

