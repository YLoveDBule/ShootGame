#include "MonsterMrg.h"
#include <sstream>
#include "Config\NotificationNameConfig.h"
#include "MonsterData.h"

MonsterMrg::MonsterMrg()
{
	
}

MonsterMrg::~MonsterMrg()
{
	
}

MonsterMrg * MonsterMrg::Create(const int monsterId)
{
	MonsterMrg * monster = new MonsterMrg();
	if (monster && monster->MonsterInit(monsterId)) {
		monster->autorelease();
		return monster;
	}
	else
	{
		delete monster;
		monster = NULL;
		return NULL;
	}
}

void MonsterMrg::DestroyMonster()
{
	this->unschedule(schedule_selector(MonsterMrg::freshPos));
	//֪ͨ
	stringstream stream;
	stream >> _SkillGrade;
	CCString str = CCString(stream.str().c_str());
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);
	stream.str("");
	stream.clear();
	if (_SkillReward != 0)
	{
		stream >> _SkillReward;
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATENOWHP, &str);
	}
	stream.str("");
	stream.clear();

	removeFromParentAndCleanup(true);	
}

bool MonsterMrg::MonsterInit(const int monsterId)
{
	if (!CCSprite::init())
	{
		return false;
	}
	this->initWithFile("guai1.png");
	InitMonsterData(monsterId);
	this->schedule(schedule_selector(MonsterMrg::freshPos));
	return true;
}

void MonsterMrg::InitMonsterData(const int monsterId)
{
	_FreshSpeed = MonsterData::getInstance()->getFreshSpeed(monsterId);
	_Hurt = MonsterData::getInstance()->getHurt(monsterId);
	_Hp = MonsterData::getInstance()->getHp(monsterId);
	_resfile = MonsterData::getInstance()->getRes(monsterId);
	_showGrade = MonsterData::getInstance()->getShowGrade(monsterId);
	_SkillGrade = MonsterData::getInstance()->getSkillGrade(monsterId);
	_SkillReward = MonsterData::getInstance()->getSkillReward(monsterId);
	_MoveSpeed = MonsterData::getInstance()->getMoveSpeed(monsterId);

	// beigin pos
	_NowPos = MonsterPosCreate::getInstance()->getRandomPoint();
	setAnchorPoint(ccp(0.5, 0));
	setPosition(_NowPos);
}

void MonsterMrg::freshPos(float dt)
{
	_NowPos = ccpAdd(_NowPos, ccp(0, -_MoveSpeed));
	setPosition(_NowPos);
	if (_NowPos.y < 0)
	{
		DestroyMonster();
	}
	CCLog("posx == %f, posy ==== %f", _NowPos.x, _NowPos.y);
}


//////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////        MonsterPosCreate      //////////////////////////////

static MonsterPosCreate* s_monsterPosCreate = nullptr;
MonsterPosCreate::MonsterPosCreate()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCPoint beginPos = ccp(size.width / 2, size.height);
	for (size_t i = 0; i < 6; ++i)
	{
		if (i < 3)
		{
			_point[i] = ccp(beginPos.x - i * 100,beginPos.y);
		}
		else
		{
			_point[i] = ccp(beginPos.x + (i - 3) * 100, beginPos.y);
		}
	}
	_beforeIndex = 0;
}

MonsterPosCreate* MonsterPosCreate::getInstance()
{
	if (!s_monsterPosCreate)
	{
		s_monsterPosCreate = new MonsterPosCreate();
	}
	return s_monsterPosCreate;
}

cocos2d::CCPoint MonsterPosCreate::getRandomPoint()
{
	srand((unsigned)time(NULL));
	size_t index = rand() % 6;
	while (index == _beforeIndex)
	{
		index = rand() % 6;
	}
	_beforeIndex = index;
	return _point[index];
}
