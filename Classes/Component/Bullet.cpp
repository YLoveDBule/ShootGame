#include "Bullet.h"
#include "cocos2d.h"
#include "math.h"

USING_NS_CC;

Bullet* Bullet::createBullet()
{
	Bullet *pBullet = new Bullet();
	if (pBullet && pBullet->initBullet())
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

bool Bullet::initBullet()
{
	this->initWithFile("common/actor_bullet.png");
	this->setAnchorPoint(ccp(0.5, 0));
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
	if (fBulletRotation < toScreenLeftRotation) {
		//屏幕左边
		CCLog("Screen left :%f", fBulletRotation);
		float fVerticalSideLength = this->getPositionX();	//垂直边的长度
		float fObliqueSideLength = fVerticalSideLength / cos(90 - fBulletRotation);	//斜边长
		float bottomSideLength = tan((90-fabs(fBulletRotation))*M_PI/180)*fVerticalSideLength;
		CCLog("tan(90+fBulletRotation):%f,fVerticalSideLength:%f,bottomSideLength:%f", tan(90 + fBulletRotation),fVerticalSideLength, bottomSideLength);
		this->runAction(CCMoveTo::actionWithDuration(3.0f, CCPointMake(0, bottomSideLength)));
	}
	else if (fBulletRotation >= toScreenLeftRotation && fBulletRotation <= toScreenRightRotation)
	{
		//屏幕顶部
		CCLog("Screen top");
	}
	else if (fBulletRotation > toScreenRightRotation)
	{
		//屏幕右边
		CCLog("Screen right");
	}


	//float fVerticalSideLength = this->getPositionX();	//垂直边的长度
	//float fObliqueSide = fVerticalSideLength / cos(90 - fBulletRotation);	//斜边长
	////初始Bullet位置
	//CCPoint startBullet = this->getPosition();
	////结束位置
	//CCPoint endBullet = ccpNormalize(startBullet) * fObliqueSide;
	//
	//this->runAction(CCMoveBy::actionWithDuration(3.0f, CCPointMake(0, fObliqueSide)));
}