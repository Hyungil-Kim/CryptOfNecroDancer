#pragma once
#include"CObstacle.h"

class Player;
class wallManager;
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
	RECT rc;
	float x, y;
	float posx, posy;

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
	bool AttackOn = false;

	MONSTERSTATE monsterState;
	MONSTERMOVESTATE monsterMoveState;
};

class monster : public CObstacle
{
protected:
	vector<tagMonster> _vMonster;
	vector<tagMonster>::iterator _viMonster;
	bool _isDebug;
	wallManager* _wm;
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
	virtual void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	virtual void isCanMove();
	
	vector<tagMonster>& getVMonster() { return _vMonster; }
	vector<tagMonster>::iterator& getVIMonster() { return _viMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

};

