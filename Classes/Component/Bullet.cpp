#include "Bullet.h"
#include "cocos2d.h"
#include "math.h"
#include "Config/BaseConfig.h"
#include "Config/NotificationNameConfig.h"
#include "GamingLayer.h"
#include <iostream>

using namespace std;
USING_NS_CC;

Bullet* Bullet::createBullet(GamingLayer* gamingLayer)
{
	Bullet *pBullet = new Bullet();
	if (pBullet && pBullet->initBullet(gamingLayer))
	{
		pBullet->autorelease();
		return pBullet;
	}
	else
	{
		CC_SAFE_DELETE(pBullet);
		return NULL;
	}
}

Bullet::Bullet(){}
Bullet::~Bullet(){}

bool Bullet::initBullet(GamingLayer* gamingLayer)
{
	this->m_bHit = false;
	this->initWithFile("common/actor_bullet.png");
	this->setAnchorPoint(ccp(0.5, 0));
	this->m_pGamingLayer = gamingLayer;
	return true;
}

void Bullet::shootBullet()
{
	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	//子弹位置到屏幕左对角线角度
	float lAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX());
	float toScreenLeftRotation =  lAngle / M_PI * 180.0f;
	//子弹位置到屏幕右对角线的角度
	float rAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX()-winSize.width);
	float toScreenRightRotation = fabs(rAngle / M_PI * 180.0f)-90;



	CCLog("toScreenLeftRotation:%f,toScreenRightRotation:%f", toScreenLeftRotation, toScreenRightRotation);

	float fBulletRotation = this->getRotation();						//角度
	CCPoint endPoint = ccp(0,0);
	if (fBulletRotation < toScreenLeftRotation) {
		//屏幕左边
		CCLog("Screen left :%f", fBulletRotation);
		float fVerticalSideLength = this->getPositionX();	//垂直边的长度
		float fObliqueSideLength = fVerticalSideLength / cos(90 - fBulletRotation);	//斜边长
		float fBottomSideLength = tan((90-fabs(fBulletRotation))*M_PI/180)*fVerticalSideLength;
		endPoint = ccp(0, fBottomSideLength);
	}
	else if (fBulletRotation >= toScreenLeftRotation && fBulletRotation <= toScreenRightRotation)
	{
		//屏幕顶部
		CCLog("Screen top");
		float fVerticalSideLength = winSize.height - this->getPositionY();//垂直边的长度
		float fBottomSideLength = tan(fabs(fBulletRotation)*M_PI / 180)*fVerticalSideLength;
		endPoint = ccp(winSize.width / 2 - fBottomSideLength, winSize.height);
		if (fBulletRotation > 0)
		{
			endPoint = ccp(winSize.width / 2 + fBottomSideLength, winSize.height);
			
		}
	}
	else if (fBulletRotation > toScreenRightRotation)
	{
		//屏幕右边
		CCLog("Screen right");
		float fVerticalSideLength = winSize.width - this->getPositionX();//垂直边的长度
		float fBottomSideLength = tan((90-fabs(fBulletRotation))*M_PI / 180)*fVerticalSideLength;
		endPoint = ccp(winSize.width, fBottomSideLength);		
	}
	//移动的距离
	float fDistance = sqrt(powf(endPoint.x - this->getPositionX(),2) + powf(endPoint.y - this->getPositionY(),2));
	float duration = fDistance / BULLET_SPEED;
	CCCallFunc *pCallfunc = CCCallFunc::actionWithTarget(this, callfunc_selector(Bullet::destroyBullet));
	this->runAction(CCSequence::actions(CCMoveTo::actionWithDuration(duration, endPoint), pCallfunc, NULL));
}

void Bullet::collision()
{
	this->m_bHit = true;
	CCCallFunc *pCallfunc = CCCallFunc::actionWithTarget(this, callfunc_selector(Bullet::destroyBullet));
	this->runAction(CCSequence::actions(CCFadeOut::actionWithDuration(0.2), pCallfunc, NULL));
}

void Bullet::destroyBullet()
{
	this->m_bHit = true;
	this->stopAllActions();
	
	//移除子弹，并从子弹容器里删除
	/*for (vector<Bullet*>::iterator it = m_pGamingLayer->m_pBulletVector.begin(); it != m_pGamingLayer->m_pBulletVector.end(); it++)
	{
		if (*it == this)
		{
			it = m_pGamingLayer->m_pBulletVector.erase(it);
			break;
		}
	}*/
	m_pGamingLayer->m_pBullets->removeObject(this);
	this->removeFromParentAndCleanup(true);
	
}
