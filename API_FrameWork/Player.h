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

enum DIRECTION {
	LEFT,
	RIGHT,
	UP,
	DOWN
};

struct InputDirection {
	bool isLeft;
	bool isRight;
	bool isUp;
	bool isDown;
};

class Player :public Singleton<Player>
{
private:
	STATE _state;
	DIRECTION _direction;
	InputDirection _inputdirection;

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
	RECT player_rc;



private:
	int x, y;
	int hp;
	int atk;
	int def;
	int sight;
	int sholve;
	bool hitFireTile;
	bool hitIceTile;
	bool _isDebug;
	bool isCurrentRight;
public:
	 HRESULT init();
	 void release();
	 void update(); //계산하는곳
	 void render(/*HDC hdc*/);
	 void inputCheck();
	 void moveCharater();
	 void inputDirectionCheck();
	 void stateCheck();
	 void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};