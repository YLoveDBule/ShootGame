#pragma once
#include "cocos2d.h"

USING_NS_CC;
class GamingLayer;
class MonsterMrg : public CCSprite
{
public:
	MonsterMrg();
	virtual ~MonsterMrg();
	static MonsterMrg *Create(const int monsterId, GamingLayer* gamingLayer);
	GamingLayer *_gamingLayer;
public:
	virtual void DestroyMonster();
	bool MonsterInit(const int monsterId, GamingLayer* gamingLayer);
	virtual void InitMonsterData(const int monsterId);
	void freshPos(float dt);
	void pause();
	void resume();
	CCAnimate * getMonsterAction(const char *filename);
	void addHpProgress();
	void freshMonsterHp(const int playerAtt);
	void shouJiEffect();
	void RemoveShoujiEffect(CCNode *pSender);
	void MonsterSuicideEffect();
	void MonsterHurtPlayerHp();
	void RemoveSuicideEffect(CCNode *pSender);
protected:
	CC_SYNTHESIZE(int, _Hp,monsterHp);
	CC_SYNTHESIZE(int, _SkillGrade, monsterSkillGrade);
	CC_SYNTHESIZE(int, _SkillReward, monsterSkillReward);
	CC_SYNTHESIZE(int, _Hurt, monsterHurt);
	CC_SYNTHESIZE(int, _FreshSpeed, monsterFreshSpeed); 
	CC_SYNTHESIZE(int, _showGrade, monsterShowGrade);
	CC_SYNTHESIZE(float, _MoveSpeed, monsterMoveSpeed);
	CC_SYNTHESIZE(const char *, _resfile, monsterResFile);
	CC_SYNTHESIZE(CCPoint, _NowPos, monsterNowPos);
	CC_SYNTHESIZE(int, _NowHp, monsterNowHp);
private:
	CCProgressTimer *_hpProgress;
};


//monster begin pos 
//保证上一个刷新的和下一个不一样 所以用了单例。。。这是策划需求的
class MonsterPosCreate
{ 
public:
	MonsterPosCreate();
	~MonsterPosCreate(){};
	static MonsterPosCreate* getInstance();
	CCPoint getRandomPoint();
private:
	CCPoint _point[6];
	size_t _beforeIndex;
};