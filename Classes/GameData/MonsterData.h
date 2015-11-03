#pragma once
#include "../CsvReader/CsvReader.h"

enum MonsterDataSate
{
	Monster_Id = 0,       //ID
	Monster_ShowTerm = 1, //出现条件 和 人物当前的分数有关系
	Monster_Res = 2, //资源路径
	Monster_Hp, //怪物血量
	Monster_MoveSpeed, //怪物从上到下移动的速度
	Monster_SkillGrade, //杀死怪物获得的分数
	Monster_SkillReward, //杀死怪物获得的血量
	Monster_Hurt, //怪物走到下方没被杀死对玩家造成的伤害
	Monster_FreshSpeed, //刷新频率  
};

class MonsterData
{
public:
	MonsterData();
	~MonsterData();
public:
	static MonsterData *getInstance();
	void init();
	const char* getRes(const int id);
	int getHp(const int id);
	int getMoveSpeed(const int id);
	int getSkillGrade(const int id);
	int getSkillReward(const int id);
	int getHurt(const int id);
	int FreshSpeed(const int id);
	int getShowGrade(const int id);
protected:
	int getRow(const int id);
private:
	CCSVParse *_csvParse;
};

