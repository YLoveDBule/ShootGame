#include "PlayerMrg.h"
#include "PlayerData.h"
#include "Config/NotificationNameConfig.h"
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
	_player = new Player();
}

void PlayerMrg::Delete()
{
	CC_SAFE_DELETE(_player);
}



//////////////////////////////////////////////////////////////////////////
/*       player                 */

Player::Player()
{
	initData();
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(Player::UpdatePlayerGrade), NOTIFY_PLAYER_UPDATEGRADE, NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(Player::UpdatePlayerNowHp), NOTIFY_PLAYER_UPDATENOWHP, NULL);
}

Player::~Player()
{
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATEGRADE);
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_PLAYER_UPDATENOWHP);
}

void Player::UpdatePlayerGrade(CCObject *pSender)
{
	CCString* str = static_cast<CCString*>(pSender);
	_grade += str->toInt();
	UpdateData();
}

void Player::UpdatePlayerNowHp(CCObject *pSender)
{
	CCString* str = static_cast<CCString*>(pSender);
	_nowHp += str->toInt();
}

void Player::initData()
{
	_grade = 0;
	_nowHp = PlayerData::getInstance()->getHpLimit(_grade);
	UpdateData();
}

void Player::UpdateData()
{
	_HpLimit = PlayerData::getInstance()->getHpLimit(_grade);
	_nowAtt = PlayerData::getInstance()->getAtt(_grade);
	_skillCd = PlayerData::getInstance()->getAoeCd(_grade);
	_aoeAtt = PlayerData::getInstance()->getAoe(_grade);
}
