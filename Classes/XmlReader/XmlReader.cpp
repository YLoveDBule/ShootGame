#include "XmlReader.h"
#include "rapidxml_iterators.hpp"
#include "rapidxml.hpp"
#include "rapidxml_print.hpp"
#include "rapidxml_utils.hpp"

static XmlReader *s_xmlReader = nullptr;
XmlReader::XmlReader()
{

}

XmlReader::~XmlReader()
{

}

XmlReader * XmlReader::getInstance()
{
	if (!s_xmlReader)
	{
		s_xmlReader = new XmlReader();
	}
	return s_xmlReader;
}

void XmlReader::ReadXml(const char* xmlFile)
{
	rapidxml::file<> xmldoc(CCFileUtils::fullPathFromRelativePath(xmlFile));
    rapidxml::xml_document<> myRapaidXmlDoc;
	myRapaidXmlDoc.parse<0>(xmldoc.data());
	//root
	rapidxml::xml_node<> *root = myRapaidXmlDoc.first_node();
	CCLog(root->name());
	rapidxml::xml_node<> *info = root->first_node();
	int size = root->name_size();
	int aaa = 0;
	for (rapidxml::xml_node<char> * node = root->first_node();
		node != NULL;
		node = node->next_sibling())
	{
		CCLog(node->first_attribute()->value());
		CCLog(node->last_attribute()->value());
	}
}
