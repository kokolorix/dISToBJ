//---------------------------------------------------------------------------
#ifndef XmlH
#define XmlH
//---------------------------------------------------------------------------

#include "Object.h"
#pragma warning(push)
#pragma warning(disable:4003)
#pragma warning(disable:26451) // Arithmetic overflow : Using operator '-' on a 4 byte value and then casting the result to a 8 byte value.Cast the value to the wider type before calling operator '-' to avoid overflow(io.2).
#include <rapidxml\rapidxml.hpp>
#pragma warning(pop)

namespace srdev
{
	using XmlDocument = rapidxml::xml_document<String::value_type>;
	using XmlDocumentPtr = shared_ptr<XmlDocument>;
	using XmlBase = rapidxml::xml_base<String::value_type>;
	using XmlNode = rapidxml::xml_node<String::value_type>;
	using XmlAttribute = rapidxml::xml_attribute<String::value_type>;

	namespace xml
	{
		extern String ELEMENT_NAME;
		extern String ROOT_NAME;
		extern String TEXT_NODE;
		ObjectPtr readXml(const XmlDocumentPtr doc);
		ObjectPtr readXml(const XmlDocument& doc);
		ObjectPtr readFile(const Path& filePath);
		ObjectPtr readString(String xmlString);
		XmlDocumentPtr writeXml(ObjectPtr object, const String& rootName = "");
		void writeFile(const Path& filePath, ObjectPtr object);
		String writeString(ObjectPtr object);
	}//xml
}//srdev
#endif