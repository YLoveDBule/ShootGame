#include "MonsterData.h"

static MonsterData *s_monsterData = nullptr;
MonsterData::MonsterData()
{
	_csvParse = new CCSVParse();
}


MonsterData::~MonsterData()
{
	delete _csvParse;
}

MonsterData * MonsterData::getInstance()
{
	if (!s_monsterData)
	{
		s_monsterData = new MonsterData();
	}
	return s_monsterData;
}

void MonsterData::init()
{
	_csvParse->openFile("MonsterData.csv");
}

const char* MonsterData::getRes(const int id)
{
	size_t row = getRow(id);
	return _csvParse->getData(row, Monster_Res);
}

int MonsterData::getHp(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_Hp));
}

int MonsterData::getMoveSpeed(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_MoveSpeed));
}

int MonsterData::getSkillGrade(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_SkillGrade));
}

int MonsterData::getSkillReward(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_SkillReward));
}

int MonsterData::getHurt(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_Hurt));
}

int MonsterData::getFreshSpeed(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_FreshSpeed));
}

int MonsterData::getShowGrade(const int id)
{
	size_t row = getRow(id);
	return atoi(_csvParse->getData(row, Monster_ShowTerm));
}

int MonsterData::getRow(const int id)
{
	size_t dataSize = _csvParse->getRows();
	size_t index = 0;
	for (; index < dataSize; ++index)
	{
		const char * data = _csvParse->getData(index, Monster_Id);
		size_t temp = atoi(data);
		if (id == temp)
		{
			return index;
		}
		continue;
	}
	return -1;
}
