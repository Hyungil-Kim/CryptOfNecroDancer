#include "framework.h"
#include "Player.h"

HRESULT Player::init()
{
	hp = 12;
	atk = 0;
	def = 0;
	sight = 2;
	sholve = 0;
	x = WINSIZEX/2;
	y = WINSIZEY/2;
	hitFireTile = false;
	hitIceTile = false;
	_direction = DIRECTION::RIGHT;
	isCurrentRight = true;
	player_headL=IMAGE->addFrameImage("플레이어왼쪽머리", "images/player/player_headL.bmp", 384*3, 48 * 3, 16, 2, true, RGB(255, 0, 255));
	player_bodyL=IMAGE->addFrameImage("플레이어왼쪽몸", "images/player/player_bodyL.bmp", 384 * 3, 336 * 3, 16, 14, true, RGB(255, 0, 255));
	player_headR=IMAGE->addFrameImage("플레이어오른쪽머리", "images/player/player_headR.bmp", 384 * 3, 48 * 3, 16, 2, true, RGB(255, 0, 255));
	player_bodyR=IMAGE->addFrameImage("플레이어오른쪽몸", "images/player/player_bodyR.bmp", 384 * 3, 336 * 3, 16, 14, true, RGB(255, 0, 255));
	
	Aplayer_headL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽머리", 15, 13, 10, false, true);
	Aplayer_bodyL=ANIMATION->addNoneKeyAnimation("플레이어왼쪽몸", 15,13,10, false, true);
	Aplayer_headR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽머리", 0,3, 10, false, true);
	Aplayer_bodyR=ANIMATION->addNoneKeyAnimation("플레이어오른쪽몸", 0,3, 10, false, true);

	player_rc = RectMake(x,y, player_headL->getFrameWidth(), player_headL->getFrameHeight() + player_bodyL->getFrameHeight());
	player_head_rc = RectMake(x,y, player_headL->getFrameWidth(), -player_headL->getFrameHeight());
	player_body_rc = RectMake(x,y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());
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
}

void Player::render()
{
	if (_state == STATE::STOP)
	{
		if ((_direction == DIRECTION::LEFT && isCurrentRight == false || _direction == DIRECTION::UP) || (_direction == DIRECTION::LEFT && isCurrentRight == false || _direction == DIRECTION::DOWN))
		{
			ZORDER->ZorderAniRender(player_headL, 3, player_body_rc.bottom, x, y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 3, player_body_rc.bottom, x, y, Aplayer_bodyL);
		}
		else if ((_direction == DIRECTION::RIGHT && isCurrentRight == true || _direction == DIRECTION::UP) || (_direction == DIRECTION::RIGHT && isCurrentRight == true || _direction == DIRECTION::DOWN))
		{
			ZORDER->ZorderAniRender(player_headR, 3, player_body_rc.bottom, x, y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR, 3, player_body_rc.bottom, x, y, Aplayer_bodyR);
		}
	}
	if (_state == STATE::MOVE)
	{
		if ((_direction == DIRECTION::LEFT && isCurrentRight == false || _direction == DIRECTION::UP)|| (_direction == DIRECTION::LEFT && isCurrentRight == false || _direction == DIRECTION::DOWN))
		{
			ZORDER->ZorderAniRender(player_headL, 3, player_body_rc.bottom, x, y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 3, player_body_rc.bottom, x, y, Aplayer_bodyL);
		}
		else if ((_direction == DIRECTION::RIGHT && isCurrentRight == true || _direction == DIRECTION::UP) ||
			(_direction == DIRECTION::RIGHT && isCurrentRight == true || _direction == DIRECTION::DOWN))
		{
			ZORDER->ZorderAniRender(player_headR, 3, player_body_rc.bottom, x, y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR, 3, player_body_rc.bottom, x, y, Aplayer_bodyR);
		}
	}
	

	//ZORDER->ZorderAniRender(player_headR, 3, player_body_rc.bottom,x,y, Aplayer_headR);
	//ZORDER->ZorderAniRender(player_bodyR, 3, player_body_rc.bottom,x,y, Aplayer_bodyR);
	if (_isDebug)
	{
		ZORDER->ZorderRectangle(player_rc, 3);
		ZORDER->ZorderRectangle(player_head_rc, 4);
		ZORDER->ZorderRectangle(player_body_rc, 4);
	}
}



void Player::moveCharater()
{
	switch (_state)
	{
	case STATE::MOVE:
		switch (_direction)
		{
		case LEFT:
			x -= 30;
			break;
		case RIGHT:
			x += 30;
			break;
		case UP:
			y -= 30;
			break;
		case DOWN:
			y += 30;
			break;
		default:
			break;
		}
		break;
	case STATE::STOP:    
		break;
	case STATE::ATTACK:
		break;
	case STATE::DIGGING:
		break;
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
		isCurrentRight = true;
	}
	else _inputdirection.isRight = false;

	if (INPUT->isOnceKeyDown(VK_LEFT))
	{
		_inputdirection.isLeft = true;
		isCurrentRight = false;
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
	if (_inputdirection.isLeft == true && !_inputdirection.isRight) _direction = LEFT;
	
	if (_inputdirection.isRight == true && !_inputdirection.isLeft) _direction = RIGHT;
	
	if (_inputdirection.isDown == true)_direction = DOWN;
	if (_inputdirection.isUp == true) _direction = UP;


}


