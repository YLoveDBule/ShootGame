#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Player;
class MonsterKindVector;
class PlayerMrg
{
public:
	PlayerMrg();
	virtual ~PlayerMrg();
	static PlayerMrg *getInstance();
	MonsterKindVector * _monsterkindVec;
public:
	void Init();
	void Delete();
	Player *getPlayer()
	{
		return _player;
	}
private:
	Player *_player;
	
};


class Player : public CCNode
{
public:
	Player();
	~Player();
	void UpdatePlayerGrade(CCObject *pSender);
	void UpdatePlayerNowHp(CCObject *pSender);
	void PostFreshMonsterVec();
protected:
	void initData();
	void UpdateData();
private:
	CC_SYNTHESIZE(int, _grade,PlayerGrade);
	CC_SYNTHESIZE(int, _nowHp, PlayerNowHp);
	CC_SYNTHESIZE(int, _nowAtt, PlayerNowAtt);
	CC_SYNTHESIZE(int, _skillCd, PlayerSkillCd);
	CC_SYNTHESIZE(int, _HpLimit, PlayerHpLimit);
	CC_SYNTHESIZE(int, _aoeAtt, PlayerAoeAtt);
};

#define Monster_KindNumber  6
class MonsterKindVector : public CCNode
{
public:
	MonsterKindVector();
	~MonsterKindVector();
	void UpdateMonsterKind(CCObject *pSender);
	std::vector<int > getMonsterKindId();
private:
	std::vector<int > _monsterKindId;
	int _monsterId[Monster_KindNumber];
};