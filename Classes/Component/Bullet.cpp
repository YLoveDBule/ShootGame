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
	//�ӵ�λ�õ���Ļ��Խ��߽Ƕ�
	float lAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX());
	float toScreenLeftRotation =  lAngle / M_PI * 180.0f;
	//�ӵ�λ�õ���Ļ�ҶԽ��ߵĽǶ�
	float rAngle = atan2f(this->getPositionY() - winSize.height, this->getPositionX()-winSize.width);
	float toScreenRightRotation = fabs(rAngle / M_PI * 180.0f)-90;



	CCLog("toScreenLeftRotation:%f,toScreenRightRotation:%f", toScreenLeftRotation, toScreenRightRotation);

	float fBulletRotation = this->getRotation();						//�Ƕ�
	if (fBulletRotation < toScreenLeftRotation) {
		//��Ļ���
		CCLog("Screen left :%f", fBulletRotation);
		float fVerticalSideLength = this->getPositionX();	//��ֱ�ߵĳ���
		float fObliqueSideLength = fVerticalSideLength / cos(90 - fBulletRotation);	//б�߳�
		float bottomSideLength = tan((90-fabs(fBulletRotation))*M_PI/180)*fVerticalSideLength;
		CCLog("tan(90+fBulletRotation):%f,fVerticalSideLength:%f,bottomSideLength:%f", tan(90 + fBulletRotation),fVerticalSideLength, bottomSideLength);
		this->runAction(CCMoveTo::actionWithDuration(3.0f, CCPointMake(0, bottomSideLength)));
	}
	else if (fBulletRotation >= toScreenLeftRotation && fBulletRotation <= toScreenRightRotation)
	{
		//��Ļ����
		CCLog("Screen top");
	}
	else if (fBulletRotation > toScreenRightRotation)
	{
		//��Ļ�ұ�
		CCLog("Screen right");
	}


	//float fVerticalSideLength = this->getPositionX();	//��ֱ�ߵĳ���
	//float fObliqueSide = fVerticalSideLength / cos(90 - fBulletRotation);	//б�߳�
	////��ʼBulletλ��
	//CCPoint startBullet = this->getPosition();
	////����λ��
	//CCPoint endBullet = ccpNormalize(startBullet) * fObliqueSide;
	//
	//this->runAction(CCMoveBy::actionWithDuration(3.0f, CCPointMake(0, fObliqueSide)));
}