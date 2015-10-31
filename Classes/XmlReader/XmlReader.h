#ifndef __XMLREADER_H__
#define __XMLREADER_H__
#include "cocos2d.h"
USING_NS_CC;
class XmlReader
{
public:
	XmlReader();
	virtual ~XmlReader();
public:
	static XmlReader *getInstance();
	void ReadXml(const char* xmlFile);
};


#endif