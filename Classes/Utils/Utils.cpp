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