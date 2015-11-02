#include "PlayerMrg.h"
#include "PlayerData.h"
static PlayerMrg* s_playerMrg = nullptr;
PlayerMrg::PlayerMrg()
{

}

PlayerMrg::~PlayerMrg()
{

}

PlayerMrg * PlayerMrg::getInstance()
{
	if (!s_playerMrg)
	{
		s_playerMrg = new PlayerMrg;
	}
	return s_playerMrg;
}

void PlayerMrg::Init()
{
	_grade = 0;
	_nowHp = PlayerData::getInstance()->getHpLimit(_grade);
}
