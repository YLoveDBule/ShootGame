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
	int _grade;
	int _nowHp;
	int _nowAtt;
	int _skillCd;
	int _HpLimit;
	int _aoeAtt;
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