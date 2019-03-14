//---------------------------------------------------------------------------
#include "pch.h"
#include <rapidxml/rapidxml_print.hpp>
#include <fstream>
#pragma hdrstop

#include "Json.h"
#include "Xml.h"

using namespace srdev;
using namespace rapidxml;

String srdev::xml::ELEMENT_NAME = "#element_name#";
String srdev::xml::ROOT_NAME = "root";
String srdev::xml::TEXT_NODE = "#text_node#";
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace srdev
{
bool isDataNode(XmlNode* node)
{
	XmlAttribute *fa = node->first_attribute();//, *la = node->last_attribute();
	if (fa)
		return false;
	XmlNode* fn = node->first_node(), *ln = node->last_node();
	if (fn && fn == ln && fn->type() == node_data)
		return true;
	return false;
}
String toString(XmlNode* node)
{
	String x;
	print(std::back_inserter(x), *node, 0);
	return x;
}
ObjectPtr objectFromXml(XmlNode* node);
ValuePtr valueFromXml(XmlNode* node)
{
	if (isDataNode(node))
	{
		String::value_type* val = node->value();
		String::size_type sze = node->value_size();
		//node->value(val, sze);
		return Value::parse(String(val, val + sze));
	}
	ObjectPtr o = objectFromXml(node);
	if (o->empty())
		return Value::make();
	if (o.size() == 1)
		if (auto v = dynamic_pointer_cast<const VectorValue>(o.front()->getValue()))
			return v;
	return Value::make(o);
}
ValuePtr valueFromXml(XmlAttribute* attribute)
{
	return Value::parse(attribute->value());
}
PropertyPtr propertyFromXml(XmlNode* node)
{
	return PropertyPtr();
}
PropertyPtr propertyFromXml(XmlAttribute* attribute)
{
	return Property::make(attribute->name(), valueFromXml(attribute));
}
ObjectPtr objectFromXml(XmlNode* node)
{
	String x = toString(node);
	ObjectPtr obj = Object::make();

	for (XmlAttribute*a = node->first_attribute(); a; a = a->next_attribute())
	{
		static const String n("null"), t("true");
		if (a->name() == n && a->value() == t)
			return Object::make();

		PropertyPtr p = propertyFromXml(a);
		obj.push_back(p);
	}
	for (XmlNode* n = node->first_node(); n; n = n->next_sibling())
	{
		String x = toString(n);
		PropertyPtr p = obj->findProperty(n->name());
		if (auto v = dynamic_pointer_cast<const VectorValue>(p ? p->getValue() : ValuePtr()))
		{
			ValuePtr value = valueFromXml(n);
			const_cast<ValuePtrVector&>(v->getValue()).push_back(value);
		}
		else if (n->next_sibling(n->name(), n->name_size()))
		{
			ValuePtr value = valueFromXml(n);
			ValuePtrVector v = {value};
			PropertyPtr p = Property::make(n->name(), v);
			obj.push_back(p);
		}
		else
		{
			ObjectPtr o = objectFromXml(n);
			if (o.empty())
				obj.push_back(Property::make(n->name(), Value::make()));
			else
				obj.push_back(Property::make(n->name(), o));
		}
	}
	auto& p = obj;
	std::sort(p.begin(), p.end(), [](PropertyPtr x, PropertyPtr y) {return x->getName() < y->getName(); });
	return obj;
}
XmlNode* toXml(XmlNode* parent, ObjectPtr object);
XmlNode* toXml(XmlNode* parent, ValuePtr value, const String& name = "")
{
	XmlDocument* doc = parent->document();
	if (auto v = std::dynamic_pointer_cast<const ObjectValue>(value))
	{
		if (name.empty())
		{
			return toXml(parent, v->getValue());
		}
		else
		{
			XmlNode* objectNode = doc->allocate_node(node_element, doc->allocate_string(name.c_str()));
			parent->append_node(objectNode);
			return toXml(objectNode, v->getValue());
		}
	}
	else if (auto v = std::dynamic_pointer_cast<const VectorValue>(value))
	{
		for (ValuePtr element : v->getValue())
		{
			String::value_type* str = name.empty() ? parent->name() : doc->allocate_string(name.c_str());
			XmlNode* elementNode = doc->allocate_node(node_element, str);
			parent->append_node(elementNode);
			/*XmlNode* valueNode = */toXml(elementNode, element);
		}
		return parent;
	}
	else
	{
		String strValue = value;
		if (name.empty())
		{
			parent->value(parent->document()->allocate_string(strValue.c_str()));
			return parent;
		}
		else
		{
			if (dynamic_pointer_cast<const VoidValue>(value))
			{
				XmlNode* objectNode = doc->allocate_node(node_element, doc->allocate_string(name.c_str()));
				parent->append_node(objectNode);
				XmlAttribute* attribute = doc->allocate_attribute("null", "true");
				objectNode->append_attribute(attribute);
				return objectNode;
			}
			XmlAttribute* attribute = doc->allocate_attribute(
				doc->allocate_string(name.c_str()),
				doc->allocate_string(strValue.c_str()));
			parent->append_attribute(attribute);
			return parent;
		}
	}
}
XmlNode* toXml(XmlNode* parent, PropertyPtr property)
{
	if (property->getName() == xml::TEXT_NODE)
	{
		/*XmlNode* valueNode =*/ toXml(parent, property->getValue());
		return parent;
	}
	else
	{
		/*XmlNode* valueNode =*/ toXml(parent, property->getValue(), property->getName());
		return parent;
	}
}
XmlNode* toXml(XmlNode* parent, ObjectPtr object)
{
	if (object.empty())
	{
		XmlDocument* doc = parent->document();
		XmlAttribute* attribute = doc->allocate_attribute("null", "true");
		parent->append_attribute(attribute);
		return parent;
	}

	for (PropertyPtr p : object)
	{
		if (p->getName() == xml::ELEMENT_NAME)
			continue;
		XmlNode* propertyNode = toXml(parent, p);
		if (propertyNode != parent)
			parent->append_node(propertyNode);
	}
	return parent;
}


}//srdev

ObjectPtr srdev::xml::readXml(const XmlDocumentPtr doc)
{
	assert(doc);
	return readXml(*doc);
}

ObjectPtr srdev::xml::readXml(const XmlDocument & doc)
{
	ObjectPtr obj = objectFromXml(doc.first_node());
	return obj;
}

srdev::ObjectPtr srdev::xml::readString(String xmlString_)
{
	XmlDocumentPtr doc = make_shared<XmlDocument>();
	String xmlString = xmlString_ + " ";
	doc->parse<rapidxml::parse_default>(const_cast<String::value_type*>(xmlString.c_str()));
	ObjectPtr obj = readXml(doc);
	return obj;
}

ObjectPtr srdev::xml::readFile(const Path & filePath)
{
	std::ostringstream os;
	std::ifstream fs(filePath);
	String line;
	while (std::getline(fs, line))
		os << line << std::endl;
	String xmlString = os.str();
	return readString(xmlString);
}

XmlDocumentPtr srdev::xml::writeXml(ObjectPtr object, const String& rootName_ /*= ""*/)
{
	XmlDocumentPtr doc = make_shared<XmlDocument>();
	PropertyPtr rootProperty = object->findProperty(ELEMENT_NAME);
	String rootName = rootName_.empty() ? (rootProperty ? rootProperty->getValue()->toString() : ROOT_NAME) : rootName_;
	XmlNode* root = doc->allocate_node(node_element, doc->allocate_string(rootName.c_str()));
	doc->append_node(root);
	/*XmlNode* obj =*/ toXml(root, object);
	return doc;
}

void srdev::xml::writeFile(const Path & filePath, ObjectPtr object)
{
	XmlDocumentPtr doc = writeXml(object);
	std::ofstream os(filePath);
	os << "<?xml version=\"1.0\" encoding=\"UTF - 8\"?>" << std::endl;
	os << *doc;
}

String srdev::xml::writeString(ObjectPtr object)
{
	XmlDocumentPtr doc = writeXml(object);
	String str("<?xml version=\"1.0\" encoding=\"UTF - 8\"?>\r\n");
	print(std::back_inserter(str), *doc, 0);
	return str;
}
