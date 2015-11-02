#include "Bullet.h"
#include "cocos2d.h"
#include "math.h"
#include "Config/BaseConfig.h"

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
	//�ӵ�λ�õ���Ļ��Խ��߽Ƕ�
	float lAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX());
	float toScreenLeftRotation =  lAngle / M_PI * 180.0f;
	//�ӵ�λ�õ���Ļ�ҶԽ��ߵĽǶ�
	float rAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX()-winSize.width);
	float toScreenRightRotation = fabs(rAngle / M_PI * 180.0f)-90;



	CCLog("toScreenLeftRotation:%f,toScreenRightRotation:%f", toScreenLeftRotation, toScreenRightRotation);

	float fBulletRotation = this->getRotation();						//�Ƕ�
	CCPoint endPoint = ccp(0,0);
	if (fBulletRotation < toScreenLeftRotation) {
		//��Ļ���
		CCLog("Screen left :%f", fBulletRotation);
		float fVerticalSideLength = this->getPositionX();	//��ֱ�ߵĳ���
		float fObliqueSideLength = fVerticalSideLength / cos(90 - fBulletRotation);	//б�߳�
		float fBottomSideLength = tan((90-fabs(fBulletRotation))*M_PI/180)*fVerticalSideLength;
		endPoint = ccp(0, fBottomSideLength);
	}
	else if (fBulletRotation >= toScreenLeftRotation && fBulletRotation <= toScreenRightRotation)
	{
		//��Ļ����
		CCLog("Screen top");
		float fVerticalSideLength = winSize.height - this->getPositionY();//��ֱ�ߵĳ���
		float fBottomSideLength = tan(fabs(fBulletRotation)*M_PI / 180)*fVerticalSideLength;
		endPoint = ccp(winSize.width / 2 - fBottomSideLength, winSize.height);
		if (fBulletRotation > 0)
		{
			endPoint = ccp(winSize.width / 2 + fBottomSideLength, winSize.height);
			
		}
	}
	else if (fBulletRotation > toScreenRightRotation)
	{
		//��Ļ�ұ�
		CCLog("Screen right");
		float fVerticalSideLength = winSize.width - this->getPositionX();//��ֱ�ߵĳ���
		float fBottomSideLength = tan((90-fabs(fBulletRotation))*M_PI / 180)*fVerticalSideLength;
		endPoint = ccp(winSize.width, fBottomSideLength);		
	}
	//�ƶ��ľ���
	float fDistance = sqrt(powf(endPoint.x - this->getPositionX(),2) + powf(endPoint.y - this->getPositionY(),2));
	float duration = fDistance / BULLET_SPEED;
	this->runAction(CCMoveTo::actionWithDuration(duration, endPoint));

	//float fVerticalSideLength = this->getPositionX();	//��ֱ�ߵĳ���
	//float fObliqueSide = fVerticalSideLength / cos(90 - fBulletRotation);	//б�߳�
	////��ʼBulletλ��
	//CCPoint startBullet = this->getPosition();
	////����λ��
	//CCPoint endBullet = ccpNormalize(startBullet) * fObliqueSide;
	//
	//this->runAction(CCMoveBy::actionWithDuration(3.0f, CCPointMake(0, fObliqueSide)));
}