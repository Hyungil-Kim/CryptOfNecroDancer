#pragma once
#include"CObstacle.h"

class Player;
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

	int hp;
	int atk;
	int speed;
	int limit;
	//int def; 확인후 삭제
	
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


	vector<tagMonster>& getVMonster() { return _vMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

};

