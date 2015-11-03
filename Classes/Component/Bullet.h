#pragma once
#include "cocos2d.h"
USING_NS_CC;
class GamingLayer;
class Bullet : public CCSprite
{
public:
	static Bullet* createBullet(GamingLayer* gamingLayer);
	virtual ~Bullet();
	//void setBulletDirection(float rotation);
	void shootBullet();
	void destroyBullet();
private:
	Bullet();
	bool initBullet(GamingLayer* gamingLayer);
	GamingLayer* m_pGamingLayer;
};