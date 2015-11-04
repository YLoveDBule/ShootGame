#include "PlayerData.h"

static PlayerData* s_playerData;
PlayerData::PlayerData()
{
	_csvParse = new CCSVParse();
}

PlayerData::~PlayerData()
{
	delete _csvParse; 
}

PlayerData* PlayerData::getInstance()
{
	if (!s_playerData)
	{
		s_playerData = new PlayerData();
	}
	return s_playerData;
}

void PlayerData::Init()
{
	_csvParse->openFile("playerData.csv");
}

int PlayerData::getAtt(const int score)
{
	size_t row = getRow(score);
	return atoi(_csvParse->getData(row,Player_Att));
}

int PlayerData::getAoe(const int score)
{
	size_t row = getRow(score);
	return atoi(_csvParse->getData(row, Player_Aoe));
}

int PlayerData::getAoeCd(const int score)
{
	size_t row = getRow(score);
	return atoi(_csvParse->getData(row, Player_AoeCd));
}

int PlayerData::getHpLimit(const int score)
{
	size_t row = getRow(score);
	return atoi(_csvParse->getData(row, Player_HpLimit));
}

int PlayerData::getRow(const int score)
{
	size_t dataSize = _csvParse->getRows();
	size_t index = 0;
	for (; index < dataSize; ++index)
	{
		const char * data = _csvParse->getData(index, Player_ScoreLimit);
		size_t temp = atoi(data);
		if (score <= temp)
		{
			return index;
		}
		continue;
	}
	return -1;
}
