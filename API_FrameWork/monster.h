#pragma once
#include "gameNode.h"

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
	//int def; Ȯ���� ����
	
	bool canBreakWall = false;
	bool isDetecting = false;
	bool isHit = false;
	bool isDead = false;
	bool isCurrentRight;
	bool isMove = false;
	bool isOnceMove = false;
	bool AniLeft = false;
	MONSTERSTATE monsterState;
	MONSTERMOVESTATE monsterMoveState;
};

class monster : public gameNode
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
	void update(Player* cp);//�÷��̾� ��ġ �����ϱ����� 
	void render();
	
	virtual void addMonster(float x, float y);
	virtual void move();
	virtual void stateCheck();
	virtual void moveMonster();


	vector<tagMonster>& getVMonster() { return _vMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

};

