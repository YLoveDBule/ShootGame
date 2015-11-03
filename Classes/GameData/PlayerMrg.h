#pragma once
#include "cocos2d.h"
USING_NS_CC;

class Player;
class PlayerMrg
{
public:
	PlayerMrg();
	virtual ~PlayerMrg();
	static PlayerMrg *getInstance();
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