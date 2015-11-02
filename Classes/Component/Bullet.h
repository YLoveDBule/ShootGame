#pragma once
#include "cocos2d.h"
USING_NS_CC;
class Bullet : public CCSprite
{
public:
	static Bullet* createBullet();
	virtual ~Bullet();
	void setBulletDirection(float rotation);
	void shootBullet();
private:
	Bullet();
	bool initBullet();

};