#pragma once
#include "Utils.h"
#include "cocos2d.h"

USING_NS_CC;

bool Utils::IsRectCollision(CCNode *obj1, CCNode *obj2)
{
	return (CCRect::CCRectIntersectsRect(obj1->boundingBox(), obj2->boundingBox()));
}

bool Utils::IsRectContianPointCollision(CCNode *obj1, CCNode *obj2)
{
	CCPoint point = obj2->getPosition();
	return (CCRect::CCRectContainsPoint(obj1->boundingBox(), point));
}

void Utils::InitLoadPlist(const char *fileName)
{
	CCSpriteFrameCache *cache = CCSpriteFrameCache::sharedSpriteFrameCache();
	string ss = fileName;
	string sss = fileName;
	cache->addSpriteFramesWithFile(ss.append(".plist").c_str(), sss.append(".png").c_str());
}


void Utils::InitLoadAoeEffect()
{
	char str[20] = {};
	for (size_t i = 0; i < 24; ++i)
	{
		sprintf(str, "aoe/aoe_%d.png", i);
		CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(str);
	}
}

float Utils::getPointToPointDisatance(CCPoint point1, CCPoint point2)
{
	return sqrt(powf(point1.x - point2.x, 2) + powf(point1.y - point2.y, 2));
}

