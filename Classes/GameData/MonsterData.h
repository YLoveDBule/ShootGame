#pragma once
#include "../CsvReader/CsvReader.h"

enum MonsterDataSate
{
	Monster_ShowTerm= 0, //出现条件 和 人物当前的分数有关系
	Monster_Res = 1,
	Monster_Hp,
	Monster_MoveSpeed,
	Monster_SkillGrade,
	Monster_SkillReward,
	Monster_Hurt,
	Monster_FreshSpeed,
};

class MonsterData
{
public:
	MonsterData();
	~MonsterData();
public:
	static MonsterData *getInstance();
	void init();
	const char* getRes(const int playerGrade);
	int getHp(const int playerGrade);
	int getMoveSpeed(const int playerGrade);
	int getSkillGrade(const int playerGrade);
	int getSkillReward(const int playerGrade);
	int getHurt(const int playerGrade);
	int FreshSpeed(const int playerGrade);
protected:
	int getRow(const int playerGrade);
private:
	CCSVParse *_csvParse;
};

