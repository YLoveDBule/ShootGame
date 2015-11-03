#pragma once
#include "../CsvReader/CsvReader.h"

enum MonsterDataSate
{
	Monster_Id = 0,       //ID
	Monster_ShowTerm = 1, //�������� �� ���ﵱǰ�ķ����й�ϵ
	Monster_Res = 2, //��Դ·��
	Monster_Hp, //����Ѫ��
	Monster_MoveSpeed, //������ϵ����ƶ����ٶ�
	Monster_SkillGrade, //ɱ�������õķ���
	Monster_SkillReward, //ɱ�������õ�Ѫ��
	Monster_Hurt, //�����ߵ��·�û��ɱ���������ɵ��˺�
	Monster_FreshSpeed, //ˢ��Ƶ��  
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

