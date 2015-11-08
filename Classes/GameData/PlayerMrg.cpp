#include "PlayerMrg.h"
#include "PlayerData.h"
#include "Config/NotificationNameConfig.h"
#include <sstream>
#include "MonsterData.h"
static PlayerMrg* s_playerMrg = nullptr;
PlayerMrg::PlayerMrg()
{
	lastHightGrade = 0;
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
	_monsterkindVec = new MonsterKindVector();
}

void PlayerMrg::Delete()
{
	CC_SAFE_DELETE(_player);
	CC_SAFE_DELETE(_monsterkindVec);
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
	CCLog("playerGrade ===== %d", _grade);
	PostFreshMonsterVec();
}

void Player::UpdatePlayerNowHp(CCObject *pSender)
{
	CCString* str = static_cast<CCString*>(pSender);
	int tempHp = _nowHp;
	tempHp += str->toInt();
	if (tempHp >= _HpLimit)
	{
		_nowHp = _HpLimit;
	}
	else if (tempHp < _HpLimit && tempHp > 0)
	{
		_nowHp = tempHp;
	}
	else
	{
		//½áËã½çÃæ
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_GETRESLUT);
	}
	_nowHp += str->toInt();
}

void Player::PostFreshMonsterVec()
{
	stringstream ss;
	ss << _grade;
	CCString str = CCString(ss.str().c_str());
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_MONSTER_UPDATEKIND,&str);
	ss.str("");
	ss.clear();
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



////////////////////////////////
MonsterKindVector::MonsterKindVector()
{
	for (size_t i = 0; i < Monster_KindNumber; ++i)
	{
		_monsterId[i] = 1000 + i + 1;
	}
	_monsterKindId.clear();
	UpdateMonsterKind(NULL);
	CCNotificationCenter::sharedNotifCenter()->addObserver(this, callfuncO_selector(MonsterKindVector::UpdateMonsterKind), NOTIFY_MONSTER_UPDATEKIND, NULL);
}

MonsterKindVector::~MonsterKindVector()
{
	CCNotificationCenter::sharedNotifCenter()->removeObserver(this, NOTIFY_MONSTER_UPDATEKIND);
}

void MonsterKindVector::UpdateMonsterKind(CCObject *pSender)
{
	int nowGrade = PlayerMrg::getInstance()->getPlayer()->getPlayerGrade();
	if (pSender)
	{
		CCString* str = static_cast<CCString*>(pSender);
		nowGrade = str->toInt();
	}

	bool bIsAdded = false;
	for (size_t i = 0; i < Monster_KindNumber; ++i)
	{
		if (std::find(_monsterKindId.begin(),_monsterKindId.end(), _monsterId[i]) == _monsterKindId.end())
		{
			int showGrade = MonsterData::getInstance()->getShowGrade(_monsterId[i]);
			if (nowGrade < showGrade)
			{
				break;
			}
			else
			{
				_monsterKindId.push_back(_monsterId[i]);
				bIsAdded = true;
			}
		}
		continue;
	}
	if(bIsAdded)
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_MONSTER_UPDATEFRESHPOOL);
}

std::vector<int > MonsterKindVector::getMonsterKindId()
{
	return _monsterKindId;
}
