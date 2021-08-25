#include "framework.h"
#include "Player.h"

HRESULT Player::init()
{
	_player.hp = 12;
	_player.atk = 0;
	_player.def = 0;
	_player.sight = 2;
	_player.sholve = 0;
	_player.ishit = false;
	_player.x = 50;
	_player.y = 50;
	_player._speed = 1800;
	_player.hitFireTile = false;
	_player.hitIceTile = false;
	_movestate = MOVESTATE::RIGHT;
	_player.isCurrentRight = true;
	player_headL=IMAGE->addFrameImage("플레이어왼쪽머리", "images/player/player_headL.bmp", 384, 48 , 16, 2, true, RGB(255, 0, 255));
	player_bodyL=IMAGE->addFrameImage("플레이어왼쪽몸", "images/player/player_bodyL.bmp", 384 , 336 , 16, 14, true, RGB(255, 0, 255));
	player_headR=IMAGE->addFrameImage("플레이어오른쪽머리", "images/player/player_headR.bmp", 384 , 48 , 16, 2, true, RGB(255, 0, 255));
	player_bodyR=IMAGE->addFrameImage("플레이어오른쪽몸", "images/player/player_bodyR.bmp", 384 , 336 , 16, 14, true, RGB(255, 0, 255));
	
	Aplayer_headL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽머리", 15, 13, 10, false, true);
	Aplayer_bodyL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽몸", 15,13,10, false, true);
	Aplayer_headR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽머리", 0,3, 10, false, true);
	Aplayer_bodyR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽몸", 0,3, 10, false, true);

	_player.player_rc = RectMake(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
	
	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	this->inputCheck();
	this->inputDirectionCheck();
	this->stateCheck();
	this->moveCharater();
	_player.player_rc = RectMake(_player.x, _player.y, player_headL->getFrameWidth(), player_bodyL->getFrameHeight());
}

void Player::render(HDC hdc)
{

	if (_state == STATE::STOP)
	{
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate ==MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL, 4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	if (_state == STATE::MOVE)
	{
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate == MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR,4, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	

	//ZORDER->ZorderAniRender(player_headR, 3, player_body_rc.bottom,x,y, Aplayer_headR);
	//ZORDER->ZorderAniRender(player_bodyR, 3, player_body_rc.bottom,x,y, Aplayer_bodyR);
	if (_isDebug)
	{
		ZORDER->ZorderRectangle(_player.player_rc, 3);
		//ZORDER->ZorderRectangle(player_head_rc, 4);
		//ZORDER->ZorderRectangle(player_body_rc, 4);
	}
}



void Player::moveCharater()
{
	switch (_state)
	{
	case STATE::STOP:    
		break;
	case STATE::ATTACK:
		break;
	case STATE::DIGGING:
		break;
	case STATE::MOVE:
	
	case STATE::HIT:
		break;
	default:
		break;
	}
}

void Player::inputCheck()
{
	if (INPUT->isOnceKeyDown(VK_RIGHT))
	{
		_inputdirection.isRight = true;
		_inputdirection.isLeft = false;
		_player.isCurrentRight = true;
		
	}
	else _inputdirection.isRight = false;

	if (INPUT->isOnceKeyDown(VK_LEFT))
	{
		_inputdirection.isLeft = true;
		_inputdirection.isRight = false;
		_player.isCurrentRight = false;
	}
	else _inputdirection.isLeft = false;

	if (INPUT->isOnceKeyDown(VK_UP)) 
		_inputdirection.isUp = true;
	else _inputdirection.isUp = false;

	if (INPUT->isOnceKeyDown(VK_DOWN))
		_inputdirection.isDown = true;
	else _inputdirection.isDown = false;
	
}

void Player::stateCheck()
{
	if (_inputdirection.isRight || _inputdirection.isLeft || _inputdirection.isDown || _inputdirection.isUp)
	{
		_state = STATE::MOVE;
	}
	else
	{
		_state = STATE::STOP;
	}
}

void Player::inputDirectionCheck()
{
	if (_inputdirection.isLeft == true) _movestate = LEFT;
	
	if (_inputdirection.isRight == true ) _movestate = RIGHT;
	
	if (_inputdirection.isDown == true)_movestate = DOWN;
	if (_inputdirection.isUp == true) _movestate = UP;


}

void Player::changeAttackRange()
{
	
}



