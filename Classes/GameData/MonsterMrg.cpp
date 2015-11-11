#include "MonsterMrg.h"
#include <sstream>
#include "Config\NotificationNameConfig.h"
#include "MonsterData.h"
#include "Component\GamingLayer.h"
#include "Utils\AudioManager.h"

MonsterMrg::MonsterMrg()
{
	
}

MonsterMrg::~MonsterMrg()
{
	
}

MonsterMrg * MonsterMrg::Create(const int monsterId, GamingLayer* gamingLayer)
{
	MonsterMrg * monster = new MonsterMrg();
	if (monster && monster->MonsterInit(monsterId, gamingLayer)) {
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

	if(rand() / double(RAND_MAX) >= 0.5)
		AudioManager::getInstance()->playEffect("audio/dead1.mp3");
	else
		AudioManager::getInstance()->playEffect("audio/dead2.mp3");

	stopAllActions();
	this->unschedule(schedule_selector(MonsterMrg::freshPos));
	stringstream stream;
	stream << _SkillGrade;
	CCString str = CCString(stream.str().c_str());
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);
	stream.str("");
	stream.clear();
	if (_SkillReward != 0)
	{
		stream << _SkillReward;
		CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATENOWHP, &str);
	}
	stream.str("");
	stream.clear();

	/*removeFromParentAndCleanup(true);
	_gamingLayer->m_pMonsters->removeObject(this);*/
	DestoryMonsterEffect();
}

void MonsterMrg::DestoryMonsterEffect()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(7);
	char str[20] = {};
	for (size_t i = 0; i < 7; ++i)
	{
		sprintf(str, "%s_%d.png", "siwang", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.1);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	CCSprite * zibao = CCSprite::spriteWithSpriteFrameName("siwang_0.png");
	zibao->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
	addChild(zibao);
	CCCallFuncN *callback = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MonsterMrg::ReMoveMonsterDieEffect));
	CCFiniteTimeAction *seq = CCSequence::actions(animate, callback, NULL);
	zibao->runAction(seq);
}

void MonsterMrg::ReMoveMonsterDieEffect(CCNode *pSender)
{
	((CCSprite *)pSender)->removeFromParentAndCleanup(true);
	removeFromParentAndCleanup(true);
	_gamingLayer->m_pMonsters->removeObject(this);
}
bool MonsterMrg::MonsterInit(const int monsterId, GamingLayer* gamingLayer)
{
	if (!CCSprite::init())
	{
		return false;
	}
	InitMonsterData(monsterId);
	this->schedule(schedule_selector(MonsterMrg::freshPos));
	_gamingLayer = gamingLayer;
	return true;
}

void MonsterMrg::InitMonsterData(const int monsterId)
{
	_FreshSpeed = MonsterData::getInstance()->getFreshSpeed(monsterId);
	_Hurt = MonsterData::getInstance()->getHurt(monsterId);
	_Hp = _NowHp = MonsterData::getInstance()->getHp(monsterId);
	_resfile = MonsterData::getInstance()->getRes(monsterId);
	_showGrade = MonsterData::getInstance()->getShowGrade(monsterId);
	_SkillGrade = MonsterData::getInstance()->getSkillGrade(monsterId);
	_SkillReward = MonsterData::getInstance()->getSkillReward(monsterId);
	_MoveSpeed = float(MonsterData::getInstance()->getMoveSpeed(monsterId)) / 10.0f;

	// beigin pos
	_NowPos = MonsterPosCreate::getInstance()->getRandomPoint();
	setAnchorPoint(ccp(0.5, 0));
	setPosition(_NowPos);
    runAction(CCRepeatForever::actionWithAction(getMonsterAction(_resfile)));
	addHpProgress();

	//是否已经死亡
	m_bIsDead = false;
}

void MonsterMrg::freshPos(float dt)
{
	_NowPos = ccpAdd(_NowPos, ccp(0, -_MoveSpeed));
	setPosition(_NowPos);
	if (_NowPos.y < 100)
	{
		MonsterHurtPlayerHp();
	}
	//CCLog("posx == %f, posy ==== %f", _NowPos.x, _NowPos.y);
}


CCAnimate * MonsterMrg::getMonsterAction(const char *filename)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//string ss = filename;
	//string sss = filename;
	//cache->addSpriteFramesWithFile(ss.append(".plist").c_str(), sss.append(".png").c_str());
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(2);
	char str[20] = {};
	for (size_t i = 0; i < 2; ++i)
	{
		sprintf(str, "%s_%d.png",filename,i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.2);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	char fileStr[20] = {};
	sprintf(fileStr, "%s_0.png",filename);
	CCSprite::initWithSpriteFrameName(fileStr);
	return animate;
}

void MonsterMrg::addHpProgress()
{
	CCSprite *hpBack = CCSprite::spriteWithFile("hpBack.png");
	CCSprite *hp = CCSprite::spriteWithFile("hp.png");
	hp->setContentSize(hpBack->getContentSize());
	_hpProgress = CCProgressTimer::progressWithTexture(hp->getTexture());
	addChild(hpBack);
	hpBack->setAnchorPoint(ccp(0.5, 0));
	float posy = getContentSize().height - 10; 
	hpBack->setPosition(ccp(getContentSize().width / 2, posy));
	hpBack->addChild(_hpProgress);
	_hpProgress->setAnchorPoint(ccp(0, 0));
	_hpProgress->setPosition(ccp(4, 2));
	_hpProgress->setType(kCCProgressTimerTypeHorizontalBarLR);
	_hpProgress->setPercentage(100);
}

void MonsterMrg::freshMonsterHp(const int playerAtt)
{
	_NowHp -= playerAtt;
	if (_NowHp <= 0)
	{
		_hpProgress->setPercentage(0);
		m_bIsDead = true;
		DestroyMonster();
	}
	else
	{
		float percent = float(_NowHp) /float( _Hp) * 100;
		_hpProgress->setPercentage(percent);
		shouJiEffect();
	}
}

void MonsterMrg::shouJiEffect()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	//string ss = filename;
	//string sss = filename;
	//cache->addSpriteFramesWithFile(ss.append(".plist").c_str(), sss.append(".png").c_str());
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(5);
	char str[20] = {};
	for (size_t i = 0; i < 5; ++i)
	{
		sprintf(str, "%s_%d.png", "shouji", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames, 0.2);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	CCSprite * shouji = CCSprite::spriteWithSpriteFrameName("shouji_0.png");
	shouji->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
	addChild(shouji);
	CCCallFuncN *callback = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MonsterMrg::RemoveShoujiEffect));
	CCFiniteTimeAction *seq = CCSequence::actions(animate, callback , NULL);
	shouji->runAction(seq);
}

void MonsterMrg::RemoveShoujiEffect(CCNode *pSender)
{
	((CCSprite *)pSender)->removeFromParentAndCleanup(true);
}

void MonsterMrg::MonsterSuicideEffect()
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	CCMutableArray<CCSpriteFrame*>* animFrames = new CCMutableArray<CCSpriteFrame*>(12);
	char str[20] = {};
	for (size_t i = 0; i < 12; ++i)
	{
		sprintf(str, "%s_%d.png", "zibao", i);
		CCSpriteFrame *frame = cache->spriteFrameByName(str);
		animFrames->addObject(frame);
	}
	CCAnimation* animation = CCAnimation::animationWithFrames(animFrames,0.01);
	CCAnimate* animate = CCAnimate::actionWithAnimation(animation);
	CCSprite * zibao = CCSprite::spriteWithSpriteFrameName("zibao_0.png");
	zibao->setPosition(ccp(getContentSize().width / 2, getContentSize().height / 2));
	addChild(zibao);
	CCCallFuncN *callback = CCCallFuncN::actionWithTarget(this, callfuncN_selector(MonsterMrg::RemoveSuicideEffect));
	CCFiniteTimeAction *seq = CCSequence::actions(animate, callback, NULL);
	zibao->runAction(seq);
}

void MonsterMrg::MonsterHurtPlayerHp()
{
	AudioManager::getInstance()->playEffect("audio/escape.mp3");
	this->unschedule(schedule_selector(MonsterMrg::freshPos));
	stringstream stream;
	stream << (-1 *_Hurt);
	CCString str = CCString(stream.str().c_str());
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATENOWHP, &str);
	stream.str("");
	stream.clear();
	MonsterSuicideEffect();
}

void MonsterMrg::RemoveSuicideEffect(CCNode *pSender)
{
	((CCSprite *)pSender)->removeFromParentAndCleanup(true);
	removeFromParentAndCleanup(true);
	_gamingLayer->m_pMonsters->removeObject(this);
}

//////////////////////////
//////////////////////////////////////////////////////////////////////////
/////////////        MonsterPosCreate      //////////////////////////////

static MonsterPosCreate* s_monsterPosCreate = nullptr;
MonsterPosCreate::MonsterPosCreate()
{
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	float offsetX = size.width / 7;
	for (size_t i = 0; i < 6; ++i)
	{
		_point[i] = ccp(offsetX * (i + 1), size.height);
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
