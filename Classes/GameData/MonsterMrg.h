#pragma once
#include "cocos2d.h"

USING_NS_CC;
class MonsterMrg : public CCNode
{
public:
	MonsterMrg();
	virtual ~MonsterMrg();
public:
	virtual void DestroyMonster();
	virtual void InitMonsterData();
protected:
	int _Hp;
	int _MoveSpeed;
	int _SkillGrade;
	int _SkillReward;
	int _Hurt;
	int _FreshSpeed;
	int _showGrade;
	char * _resfile;
};

class MonsterA : public MonsterMrg
{
public:
	MonsterA(){};
	virtual ~MonsterA(){};
public:
	
};

class MonsterInitData
{
public:
	MonsterInitData();
	virtual ~MonsterInitData();

};