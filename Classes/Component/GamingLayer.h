#pragma once
#include "cocos2d.h"
#include "ControllPanel.h"
//#include <vector>
USING_NS_CC;
class Bullet;
class GamingLayer : public CCLayer, public CCKeypadDelegate{
public:
	static GamingLayer* createGamingLayer();
	virtual ~GamingLayer();
	virtual bool keyAllClicked(int iKeyID, CCKeypadStatus key_status);
	vector<Bullet*> m_pBulletVector;
protected:
	void onClickA(cocos2d::CCKeypadStatus key_status);
	void onClickS(cocos2d::CCKeypadStatus key_status);
	void onClickD(cocos2d::CCKeypadStatus key_status);
	void onClickW(cocos2d::CCKeypadStatus key_status);

	void onClickI(cocos2d::CCKeypadStatus key_status);
	void onClickL(cocos2d::CCKeypadStatus key_status);
	void onClickJ(cocos2d::CCKeypadStatus key_status);
	void onClickK(cocos2d::CCKeypadStatus key_status);
private:
	GamingLayer();

	CCSprite *m_pBg;		//����sprite
	CCNode *m_pHud;			//hud�ڵ�
	ControllPanel* m_pControllPanel; //controll Panel

	void initGameBg();		//��Ϸ����
	void initHudPanel();		//��Ϸhud Paenl
	void initControllPanel();	//��Ϸ����panel

	bool initGamingLayer();		//��ʼ��
};