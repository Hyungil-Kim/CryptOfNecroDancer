#include "framework.h"
#include "Player.h"
#include "wallManager.h"
#include "monster.h"
#include "monsterManager.h"
#include "rhythmUI.h"
HRESULT Player::init()
{
	_player.hp = 12;
	_player.atk = 0;
	_player.def = 0;
	_player.sight = 2;
	_player.sholve = 0;
	_player.ishit = false;
	_player.x = 0;
	_player.y = 0;
	_player.isInput = false;
	_player.posx = _player.x / 48;
	_player.posy = _player.y / 48;
	_player.speed = 4;
	_player.limit = TILE_SIZE_X;
	_player.hitFireTile = false;
	_player.hitIceTile = false;
	_player.goleft = true;
	_player.goright = true;
	_player.gotop = true;
	_player.gobottom = true;
	_player.atkleft = false;
	_player.atkright = false;
	_player.atktop = false;
	_player.atkbottom = false;
	_player.isatk = false;
	_movestate = MOVESTATE::RIGHT;
	_player.isCurrentRight = true;
	player_headL = IMAGE->addFrameImage("플레이어왼쪽머리", "images/player/player_headL.bmp", 48 * 16, 48 * 2, 16, 2, true, RGB(255, 0, 255));
	player_bodyL = IMAGE->addFrameImage("플레이어왼쪽몸", "images/player/player_bodyL.bmp", 48 * 16, 48 * 14, 16, 14, true, RGB(255, 0, 255));
	player_headR = IMAGE->addFrameImage("플레이어오른쪽머리", "images/player/player_headR.bmp", 48 * 16, 48 * 2, 16, 2, true, RGB(255, 0, 255));
	player_bodyR = IMAGE->addFrameImage("플레이어오른쪽몸", "images/player/player_bodyR.bmp", 48 * 16, 48 * 14, 16, 14, true, RGB(255, 0, 255));
	_player.isSpawn = true;
	Aplayer_headL = ANIMATION->addNoneKeyAnimation("플레이어왼쪽머리", 15, 13, 10, false, true);
	Aplayer_bodyL = ANIMATION->addNoneKeyAnimation("플레이어왼쪽몸", 15, 13, 10, false, true);
	Aplayer_headR = ANIMATION->addNoneKeyAnimation("플레이어오른쪽머리", 0, 3, 10, false, true);
	Aplayer_bodyR = ANIMATION->addNoneKeyAnimation("플레이어오른쪽몸", 0, 3, 10, false, true);

	player_dagAtk = IMAGE->addFrameImage("플레이어단검공격", "images/player/attack/swipe_dagger.bmp", 48 * 3, 48 * 4, 3, 4, true, RGB(255, 0, 255));
	Aplayer_dagAtkR = ANIMATION->addNoneKeyAnimation("플레이어단검공격", 0, 2, 10, false, true);
	Aplayer_dagAtkL = ANIMATION->addNoneKeyAnimation("플레이어단검공격", 3, 5, 10, false, true);
	Aplayer_dagAtkU = ANIMATION->addNoneKeyAnimation("플레이어단검공격", 6, 8, 10, false, true);
	Aplayer_dagAtkD = ANIMATION->addNoneKeyAnimation("플레이어단검공격", 9, 11, 10, false, true);

	_player.player_rc = RectMake(_player.x, _player.y, player_bodyL->getFrameWidth(), player_bodyL->getFrameHeight());

	return S_OK;
}

void Player::release()
{
}

void Player::update()
{
	if (_player.isSpawn == true) {
		this->spawn();

	}
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
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate == MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL, 5, 3000, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR, 5, 3000, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	if (_state == STATE::MOVE)
	{
		if ((_player.isCurrentRight == false && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == false && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == false && _movestate == MOVESTATE::LEFT))
		{
			ZORDER->ZorderAniRender(player_headL, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_headL);
			ZORDER->ZorderAniRender(player_bodyL, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyL);
		}
		else if ((_player.isCurrentRight == true && _movestate == MOVESTATE::UP) || (_player.isCurrentRight == true && _movestate == MOVESTATE::DOWN) || (_player.isCurrentRight == true && _movestate == MOVESTATE::RIGHT))
		{
			ZORDER->ZorderAniRender(player_headR, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_headR);
			ZORDER->ZorderAniRender(player_bodyR, 5, player_body_rc.bottom, _player.x, _player.y, Aplayer_bodyR);
		}
	}
	if (_player.atkright == true)
	{
		ZORDER->ZorderAniRender(player_dagAtk, 5, player_body_rc.bottom + 1, _player.x + 36, _player.y, Aplayer_dagAtkR);

	}
	else if (_player.atktop == true)
	{
		ZORDER->ZorderAniRender(player_dagAtk, 5, player_body_rc.bottom + 1, _player.x, _player.y - 36, Aplayer_dagAtkU);
	}
	else if (_player.atkleft == true)
	{
		ZORDER->ZorderAniRender(player_dagAtk, 5, player_body_rc.bottom + 1, _player.x - 36, _player.y, Aplayer_dagAtkL);

	}
	else if (_player.atkbottom == true)
	{
		ZORDER->ZorderAniRender(player_dagAtk, 5, player_body_rc.bottom + 1, _player.x, _player.y + 36, Aplayer_dagAtkD);

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
		playerMove();
	case STATE::HIT:
		break;
	default:
		break;
	}
}

void Player::inputCheck()
{
	_rtm->step();
	if (INPUT->isOnceKeyDown(VK_RIGHT))
	{
		_player.isInput = true;
		if (_rtm->checkstep() == true)
		{
			_inputdirection.isRight = true;
			_inputdirection.isLeft = false;
			_player.isCurrentRight = true;
		}
	}
	else _inputdirection.isRight = false;

	if (INPUT->isOnceKeyDown(VK_LEFT))
	{
		_player.isInput = true;
		if (_rtm->checkstep() == true)
		{
			_inputdirection.isLeft = true;
			_inputdirection.isRight = false;
			_player.isCurrentRight = false;
		}

	}
	else _inputdirection.isLeft = false;

	if (INPUT->isOnceKeyDown(VK_UP))
	{
		_player.isInput = true;
		if (_rtm->checkstep() == true)
		{
			_inputdirection.isUp = true;
		}

	}
	else _inputdirection.isUp = false;

	if (INPUT->isOnceKeyDown(VK_DOWN))
	{
		_player.isInput = true;
		if (_rtm->checkstep() == true)
		{
			_inputdirection.isDown = true;
		}
	}
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

	if (_inputdirection.isRight == true) _movestate = RIGHT;

	if (_inputdirection.isDown == true)_movestate = DOWN;
	if (_inputdirection.isUp == true) _movestate = UP;


}

void Player::changeAttackRange()
{

}

void Player::spawn()
{

	for (int i = 0; i < _wm->getVSpawnPoint().size(); i++)
	{
		_player.x = _wm->getVSpawnPoint()[0].x;
		_player.y = _wm->getVSpawnPoint()[0].y;
		_player.posx = _player.x / 48;
		_player.posy = _player.y / 48;
		_wm->eraseSPoint(0);
		_player.isSpawn = false;
	}
}

void Player::Attack()
{
	switch (_movestate)
	{
	case LEFT:
		_player.atkleft = true;
		break;
	case UP:
		_player.atktop = true;
		break;
	case RIGHT:
		_player.atkright = true;
		break;
	case DOWN:
		_player.atkbottom = true;
		break;
	default:
		break;
	}
}

bool Player::playerToMon(int x, int y)
{
	if (findMonster(_mm->getGreenSlime(), x, y) ||
		findMonster(_mm->getBlueSlime(), x, y) ||
		findMonster(_mm->getOrangeSlime(), x, y)
		)
	{
		return true;
	}
	return false;
}

bool Player::findMonster(monster* monster,int x , int y)
{

	vector<tagMonster>& vMonster = monster->getVMonster();
	vector<tagMonster>::iterator iter = vMonster.begin();
	for (iter; iter != vMonster.end(); ++iter)
	{
		if (iter->posx == x && iter->posy == y)
		{
			return true;
		}
	}
	return false;
}




void Player::playerMove()
{
	int tempX = _player.posx;
	int tempY = _player.posy;
	switch (_movestate)
	{
	case LEFT:
		tempX -= 1;
		break;
	case UP:
		tempY -= 1;
		break;
	case RIGHT:
		tempX += 1;
		break;
	case DOWN:
		tempY += 1;
		break;
	default:
		break;
	}

	if (_wm->getDungeon(tempX, tempY) != 0)
	{
		
		if (playerToMon(tempX,tempY)==true)
		{
			Attack();
		}
		else
		{
			_player.atkbottom = false;
			_player.atktop = false;
			_player.atkleft = false;
			_player.atkright = false;
			_player.posx = tempX;
			_player.posy = tempY;
			switch (_movestate)
			{
			case LEFT:
				_player.x -= TILE_SIZE_X;
				break;
			case UP:
				_player.y -= TILE_SIZE_Y;
				break;
			case RIGHT:
				_player.x += TILE_SIZE_X;
				break;
			case DOWN:
				_player.y += TILE_SIZE_Y;
				break;
			default:
				break;
			}
		}
	}
	if (_wm->getDungeon(tempX, tempY) == 0)
	{

		switch (_movestate)
		{
		case LEFT:
			_wm->setDungeon(tempX, tempY, 1);
			_wm->getsoftWall()->eraseWall(tempX, tempY);
			break;
		case UP:
			_wm->setDungeon(tempX, tempY, 1);
			_wm->getsoftWall()->eraseWall(tempX, tempY);
			break;
		case RIGHT:
			_wm->setDungeon(tempX, tempY, 1);
			_wm->getsoftWall()->eraseWall(tempX, tempY);
			break;
		case DOWN:
			_wm->setDungeon(tempX, tempY, 1);
			_wm->getsoftWall()->eraseWall(tempX, tempY);
			break;
		default:
			break;
		}
	}
	/*if (_wm->getDungeon(tempX, tempY) != 0)
	{
		_player.posx = tempX;
		_player.posy = tempY;
		switch (_movestate)
		{
		case LEFT:
			_player.x -= TILE_SIZE_X;
			break;
		case UP:
			_player.y -= TILE_SIZE_Y;
			break;
		case RIGHT:
			_player.x += TILE_SIZE_X;
			break;
		case DOWN:
			_player.y += TILE_SIZE_Y;
			break;
		default:
			break;
		}
	}*/


}


