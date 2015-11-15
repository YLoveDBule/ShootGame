#include "LoginScene.h"
#include "GameData/PlayerMrg.h"
#include "Component/GamingLayer.h"
#include "Config/NotificationNameConfig.h"
#include "GameData/MonsterMrg.h"
#include "Config/BaseConfig.h"
#include "Utils/AudioManager.h"
bool LoginScene::init()
{
	//play background music
	AudioManager::getInstance()->playMusic("audio/background.mp3", true);
	_nowSate = MenuState_Star;
	if (!CCLayer::init())
	{
		return false;
	}
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCSprite *bg = CCSprite::spriteWithFile("common/actor_gamingbg.png");
	bg->setPosition(ccp(size.width / 2, size.height / 2));
	addChild(bg);
	//logo
#if defined LANG_CH 
	CCSprite *logo = CCSprite::spriteWithFile("logo.png");
#else 
	CCSprite *logo = CCSprite::spriteWithFile("En/logo.png");
#endif 
	logo->setPosition(ccp(size.width / 2, size.height / 2 + size.height / 4));
	addChild(logo);

	//chenbao
	CCSprite *chenbao = CCSprite::spriteWithFile("common/actor_controllBg.png");
	chenbao->setAnchorPoint(ccp(0, 0));
	addChild(chenbao);
	//menu
	std::string nemuOneName = "";
	std::string nemuTwoName = "";
#if defined LANG_CH 
	nemuOneName = "kaishi.png";
	nemuTwoName = "tuichu.png";
#else
	nemuOneName = "En/kaishi.png";
	nemuTwoName = "En/tuichu.png";
#endif
	_pStarMenu = CCMenuItemImage::itemFromNormalImage(
		nemuOneName.c_str(),
		NULL,
		this,
		menu_selector(LoginScene::clickStar));
	_pStarMenu->setPosition(ccp(size.width / 2, size.height / 2 - 15));
	_pExitMenu = CCMenuItemImage::itemFromNormalImage(
		nemuTwoName.c_str(),
		NULL,
		this,
		menu_selector(LoginScene::clickExit));
	_pExitMenu->setPosition(ccp(size.width / 2, size.height / 2  - 20 - _pStarMenu->getContentSize().height));
	CCMenu *pMenu = CCMenu::menuWithItems(_pStarMenu, _pExitMenu, NULL);
	pMenu->setPosition(CCPointZero);
	addChild(pMenu);
	CCLayer::setIsKeypadEnabled(true); 


	//row
	_rowSp = CCSprite::spriteWithFile("shouzi.png");
	_rowSp->setAnchorPoint(ccp(1, 0.5));
	ChangeRowPosition();
	addChild(_rowSp);

	//init data 
	//PlayerMrg::getInstance()->Init();
	return true;
}

CCScene* LoginScene::scene()
{
	// 'scene' is an autorelease object
	CCScene *scene = CCScene::node();

	// 'layer' is an autorelease object
	LoginScene *layer = LoginScene::node();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

bool LoginScene::keyAllClicked(int iKeyID, cocos2d::CCKeypadStatus iKeyState)
{


	if (iKeyID == 'w' || iKeyID == 'W' || iKeyID == HANDSET_UP || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_UP)
	{
		onClickW(iKeyState);
	}
	else if (iKeyID == 's' || iKeyID == 'S' || iKeyID == HANDSET_DOWN || iKeyID == HANDSET_DOWN_ || iKeyID == KEY_DOWN)
	{
		onClickS(iKeyState);
	}
	else if (iKeyID == 'a' || iKeyID == 'A' || iKeyID == HANDSET_LEFT || iKeyID == HANDSET_LEFT_ || iKeyID == KEY_LEFT)
	{
		onClickA(iKeyState);
	}
	else if (iKeyID == 'd' || iKeyID == 'D' || iKeyID == HANDSET_RIGHT || iKeyID == HANDSET_RIGHT_ || iKeyID == KEY_RIGHT)
	{
		onClickD(iKeyState);
	}
	else if (iKeyID == 'j' || iKeyID == 'J' || iKeyID == HANDSET_Y || iKeyID == HANDSET_Y_ || iKeyID == KEY_Y)
	{
		onClickJ(iKeyState);
	}
	else if (iKeyID == 'i' || iKeyID == 'I' || iKeyID == HANDSET_A || iKeyID == HANDSET_A_ || iKeyID == KEY_A)
	{
		onClickI(iKeyState);
	}
	else if (iKeyID == 'k' || iKeyID == 'K' || iKeyID == HANDSET_B || iKeyID == HANDSET_B_ || iKeyID == KEY_B)
	{
		onClickK(iKeyState);
	}
	else if (iKeyID == 'l' || iKeyID == 'L' || iKeyID == HANDSET_X || iKeyID == HANDSET_X_ || iKeyID == KEY_X)
	{
		onClickL(iKeyState);
	}
	else 
	{
		CCLog("-------KeyNotFind----KeyID = %d -------KeyState = %d-----\n", iKeyID, iKeyState);
		return false;
	}
	return true;
}

void LoginScene::onClickA(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate + 1);
		if (_nowSate == MenuState_End)
		{
			_nowSate = MenuState_Star;
		}
		ChangeRowPosition();
	}
}

void LoginScene::onClickS(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate + 1);
		if (_nowSate == MenuState_End)
		{
			_nowSate = MenuState_Star;
		}
		ChangeRowPosition();
	}
	
}

void LoginScene::onClickD(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
	}
}

void LoginScene::onClickW(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		_nowSate = MenuState(_nowSate - 1);
		if (_nowSate == MenuState_Begin)
		{
			_nowSate = MenuState_Exit;
		}
		ChangeRowPosition();
	}
	
}

void LoginScene::onClickI(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
	}
}

void LoginScene::onClickL(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
	}
}

void LoginScene::onClickJ(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{
		switch (_nowSate)
		{
		case MenuState_Star:
			clickStar(NULL);
			break;
		case MenuState_Exit:
		{
			CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
			exit(0);
#endif
		}
		break;
		default:
			break;
	}
	}
	
}

void LoginScene::onClickK(cocos2d::CCKeypadStatus key_status)
{
	if (key_status == EVENT_KEY_DOWN)
	{

	}
}

void LoginScene::clickStar(CCObject* pSender)
{

	PlayerMrg::getInstance()->Init();
	CCScene *scene = CCScene::node();
	GamingLayer*layer = GamingLayer::createGamingLayer();
	scene->addChild(layer);
	CCDirector::sharedDirector()->replaceScene(scene);
	//PlayerMrg::getInstance()->Init();
	/*CCString str = CCString("100");
	CCNotificationCenter::sharedNotifCenter()->postNotification(NOTIFY_PLAYER_UPDATEGRADE, &str);*/
	/*MonsterMrg *monster = MonsterMrg::Create(1001);
	addChild(monster);*/
}

void LoginScene::clickExit(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
	exit(0);
#endif
}

void LoginScene::ChangeRowPosition()
{
	switch (_nowSate)
	{
	case MenuState_Star:
	    {
			_rowSp->setPosition(ccp(_pStarMenu->getPosition().x - _pStarMenu->getContentSize().width / 2 - 20, _pStarMenu->getPosition().y));
	    }
		break;
	case MenuState_Exit:
	   {
		   _rowSp->setPosition(ccp(_pExitMenu->getPosition().x - _pExitMenu->getContentSize().width / 2 - 20, _pExitMenu->getPosition().y));
	   }
		break;
	default:
		break;
	}
}
