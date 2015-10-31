#pragma once
#include "../CsvReader/CsvReader.h"

enum MonsterDataSate
{
	Monster_ShowTerm= 0, //�������� �� ���ﵱǰ�ķ����й�ϵ
	Monster_Res = 1, //��Դ·��
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

