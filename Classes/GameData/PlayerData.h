#ifndef __PLAYER_DATA_H__
#define __PLAYER_DATA_H__
#include <map>
#include "../CsvReader/CsvReader.h"
enum PlayerDataState
{
	Player_ScoreLimit = 0,
	Player_Att = 1,
	Player_Aoe = 2,
	Player_AoeCd,
	Player_HpLimit,
};

class PlayerData
{
public:
	PlayerData();
	~PlayerData();
public:
	static PlayerData* getInstance();
	void Init();
	int getAtt(const int score);
	int getAoe(const int score);
	int getAoeCd(const int score);
	int getHpLimit(const int score);
protected:
	int getRow(const int score);
private:
	CCSVParse * _csvParse;
};

#endif