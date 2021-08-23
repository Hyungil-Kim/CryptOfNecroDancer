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

enum {
	GoLeft,
	GoRight,
	GoUp,
	GoDown,
	Stop,
	Attack,
	Digging,
	Hit
};

class Player :public Singleton<Player>
{
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
	int hp;
	int atk;
	int def;
	int sight;
	int sholve;
	bool hitFireTile;
	bool hitIceTile;
	bool _isDebug;

public:
	 HRESULT init();
	 void release();
	 void update(); //계산하는곳
	 void render(/*HDC hdc*/);
	 void setIsDebug(bool isDebug) { _isDebug = isDebug; }
};

