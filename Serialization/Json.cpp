//---------------------------------------------------------------------------
#include "pch.h"
#include <fstream>
#pragma hdrstop

#include "Json.h"
#include "Value.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
namespace srdev
{
using namespace nlohmann;

void from_json(const Json &j, ValuePtr &v)
{
	if (j.is_boolean())
		v = BooleanValue::make(j.get<bool>());
	else if (j.is_number_integer())
		v = Int32Value::make(j.get<int32_t>());
	else if (j.is_string())
		v = StringValue::make(j.get<String>());
	else if (j.is_number_float())
		v = DoubleValue::make(j.get<double>());
	else if (j.is_object())
	{
		ObjectPtr o = j;
		v = ObjectValue::make(o);
	}
	else if (j.is_array())
	{
		std::vector<ValuePtr> valueVector;
		for (Json::const_iterator i = j.begin(); i != j.end(); ++i)
		{
		    ValuePtr v;
		    from_json(*i, v);
		    valueVector.push_back(v);
		}

		v = VectorValue::make(valueVector);
	}
	else
	{
		v = Value::make();
	}
}

void from_json(const Json &j, ObjectPtr &o)
{
	o = Object::make();
	for (auto i = j.begin(); i != j.end(); ++i)
	{
		ValuePtr v;
		from_json(i.value(), v);
		o->insert(o->end(), Property::make(i.key(), v));
	}
}

void to_json(Json &j, const ValuePtr &p)
{
	//using boost::uuids::to_string;
	if (auto v = std::dynamic_pointer_cast<const VoidValue>(p))
		j = Json();
	else if (auto v = std::dynamic_pointer_cast<const StringValue>(p))
		j = v->getValue();
	else if (auto v = std::dynamic_pointer_cast<const BooleanValue>(p))
		j = v->getValue();
	else if (auto v = std::dynamic_pointer_cast<const Int32Value>(p))
		j = v->getValue();
	else if (auto v = std::dynamic_pointer_cast<const DoubleValue>(p))
		j = v->getValue();
	//else if (auto v = std::dynamic_pointer_cast<const UuIdValue>(p))
	//	j = to_string(v->getValue());
	else if (auto v = std::dynamic_pointer_cast<const ObjectValue>(p))
		j = v->getValue();
	else if (auto v = std::dynamic_pointer_cast<const VectorValue>(p))
		std::copy(v->getValue().begin(), v->getValue().end(), std::back_inserter(j));
}

void to_json(Json &j, const PropertyPtr &p)
{
	Json jv = p->getValue();
	j[p->getName()] = jv;
}

void to_json(Json &j, const ObjectPtr &o)
{
	j = json::object();
	for (PropertyPtr p : o)
	{
		Json val = p->getValue();
		String key = p->getName();
		//j.insert(j.end(), std::make_pair(key, val));
		j[key] = val;
	}
	//std::transform(o->begin(), o->end(), std::inserter(j, j.end()), [](PropertyPtr p)
	//{
	//	return std::make_pair(p->getName(), Json(p->getValue()));
	//});
}

}//srdev

srdev::ObjectPtr srdev::js::readJson(const Json& j)
{
	 ObjectPtr object = j;
	 return object;
}

srdev::ObjectPtr srdev::js::readFile(const Path &filePath)
{
	 std::ifstream is(filePath);
	 Json j;
	 is >> j;
	 return readJson(j);
}

srdev::ObjectPtr srdev::js::readString(const String &jsonString)
{
	 istringstream is(jsonString);
	 Json j;
	 is >> j;
	 return readJson(j);
}

srdev::Json srdev::js::writeJson(ObjectPtr object)
{
	Json j = object;
	return j;
}

void srdev::js::writeFile(const Path &filePath, ObjectPtr object)
{
	 std::ofstream os(filePath);
	 Json j = object;
	 os << j;
}

srdev::String srdev::js::writeString(ObjectPtr object)
{
	 ostringstream os;
	 Json j = object;
	 os << j;
	 return os.str();
}
