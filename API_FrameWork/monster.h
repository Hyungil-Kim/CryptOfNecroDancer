#pragma once
#include"CObstacle.h"
#define INVINTIME 40

class Player;
class wallManager;
class rhythmUI;
class realwallManager;
class bossMap;
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
	image* img2;
	image* img3;
	animation* ani;
	animation* leftani;
	animation* rightani;
	animation* shadowani;
	animation* leftshadowani;

	image* _atkup;
	image* _atkleft;

	animation* A_atkup;
	animation* A_atkleft;
	animation* A_atkright;
	animation* A_atkdown;

	image* m_heart;
	image* m_halfheart;
	image* m_emptyheart;

	RECT rc;
	int x, y;
	int posx, posy;

	int maxhp;
	int hp;
	int atk;
	int speed;
	int limit;
	//int def; Ȯ���� ����
	
	bool canleft = false;
	bool canright = false;
	bool canup = false;
	bool candown = false;
	
	bool digleft = false;
	bool digright = false;
	bool digup = false;
	bool digdown = false;

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
	bool rtmcount = false;
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
	realwallManager* _rwm;
	monsterManager* _mm;
	rhythmUI* _rtm;
	bossMap* _boss;

	int monstermaxhp;
	int monsterhp;
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
	virtual void isCanMove();

	virtual bool findPlayer(tagPlayer& player);
	virtual bool findMonster(monster* monster);
	virtual bool monTomon(tagMonster& monster);
	virtual bool findPlayer(int x , int y);
	virtual bool findMonster(monster* monster, int x, int y);
	virtual bool monTomon(int x, int y);
	virtual void attack();
	virtual void getDamage();
	virtual void setdirection();
	virtual void setbrokerdirection();
	virtual void checkInvincibility();
	virtual void deathcheck();
	virtual void checkstate();
	virtual void checkstatebroker();

	virtual void setmonsterManagerMemoryLink(monsterManager* monsterManager) { _mm = monsterManager; }
	virtual void setwallManagerMemoryLink(wallManager* wallManager) { _wm = wallManager; }
	virtual void setbossMapMemoryLink(bossMap* bossMap) { _boss = bossMap; }
	virtual void setrtmMemoryLink(rhythmUI* rhythmUI) { _rtm = rhythmUI; }
	virtual void setrealwallManagerMemoryLink(realwallManager* realwallManager) { _rwm = realwallManager; }
	virtual void showhp();
	virtual void hpinit();
	
	vector<tagMonster>& getVMonster() { return _vMonster; }
	vector<tagMonster>::iterator& getVIMonster() { return _viMonster; }
	void setIsDebug(bool isDebug) { _isDebug = isDebug; }

};

