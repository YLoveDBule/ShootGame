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
	void collision();
	CC_SYNTHESIZE(bool, m_bHit, Hit);
private:
	Bullet();
	bool initBullet(GamingLayer* gamingLayer);
	GamingLayer* m_pGamingLayer;
};