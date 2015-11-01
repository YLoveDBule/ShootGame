#pragma once

class PlayerMrg
{
public:
	PlayerMrg();
	virtual ~PlayerMrg();
	static PlayerMrg *getInstance();
public:
	void Init();
private:
	int _grade;
	int _nowHp;
};