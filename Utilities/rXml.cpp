#include "stdafx.h"
#include "restore_new.h"
#include "Utilities/rXml.h"
#include "define_new_memleakdetect.h"

rXmlNode::rXmlNode() : handle()
{
}

rXmlNode::rXmlNode(const pugi::xml_node &node)
{
	handle = node;
}

std::shared_ptr<rXmlNode> rXmlNode::GetChildren()
{
	// it.begin() returns node_iterator*, *it.begin() return node*.
	pugi::xml_object_range<pugi::xml_node_iterator> it = handle.children();
	pugi::xml_node begin = *it.begin();

	if (begin)
	{
		return std::make_shared<rXmlNode>(begin);
	}
	else
	{
		return nullptr;
	}
}

std::shared_ptr<rXmlNode> rXmlNode::GetNext()
{
	pugi::xml_node result = handle.next_sibling();
	if (result)
	{
		return std::make_shared<rXmlNode>(result);
	}
	else
	{
		return nullptr;
	}
}

std::string rXmlNode::GetName()
{
	return handle.name();
}

std::string rXmlNode::GetAttribute(const std::string &name)
{
	auto pred = [&name](pugi::xml_attribute attr) { return (name == attr.name()); };
	return handle.find_attribute(pred).value();
}

std::string rXmlNode::GetNodeContent()
{
	return handle.text().get(); 
}

rXmlDocument::rXmlDocument() : handle()
{
}

void rXmlDocument::Load(const std::string & path)
{
	// TODO: Unsure of use of c_str.
	handle.load_file(path.c_str());
}

std::shared_ptr<rXmlNode> rXmlDocument::GetRoot()
{
	return std::make_shared<rXmlNode>(handle.root());
}

