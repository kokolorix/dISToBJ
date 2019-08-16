#ifndef BaseTypesH
#define BaseTypesH

#include "Object.h"
#include "Traits.h"

namespace srdev
{
	namespace System
	{
		namespace ObjectTypeT
		{
			using BaseTraits = System::ObjectBase;
			namespace Name
			{
				struct PropertyT
				{
					static String getName() { return "Name"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1>;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1>;
			}
			namespace PropertyTypes
			{
				struct PropertyT
				{
					static String getName() { return "PropertyTypes"; }
					static ValuePtr getDefaultValue() { return VectorValue::make(Vector()); }
				};
				using Traits = PropertyTraits<PropertyT,Vector, BaseTraits::Properties::LastId + 1>;
			}
			struct ObjectT
			{
				static String getCategory() { return "System"; }
				static String getName() { return "ObjectType"; }
				static UuId getTypeId() { static const UuId id = generateIdFromString("{C53E3E49-39B1-452E-9DEE-B20709A06F49}"); return id; }
			};
			struct PropertiesT
			{
				using Name = Name::Traits;
				using DisplayName = DisplayName::Traits;
				using PropertyTypes = PropertyTypes::Traits;
				using List = std::tuple<Name,DisplayName,PropertyTypes>;
				enum { LastId = std::tuple_size<List>::value };
			};
			using Traits = ObjectTraits<ObjectT, BaseTraits, PropertiesT>;
		}
		using ObjectType = ObjectTypeT::Traits;
	}
	template<>
	struct ObjectAccess<System::ObjectType> : public ObjectImpl<System::ObjectType::BaseTraits>
	{
		ValuePtr getNameValue() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::Name::Id)->getValue()); }
		void setNameValue(ValuePtr value) { getProperty(System::ObjectType::Properties::Name::Id)->setValue(value ); }
		String getName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::Name::Id)->getValue())->getValue(); }
		void setName(const String& value) { getProperty(System::ObjectType::Properties::Name::Id)->setValue(StringValue::make(value)); }

		ValuePtr getDisplayNameValue() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::DisplayName::Id)->getValue()); }
		void setDisplayNameValue(ValuePtr value) { getProperty(System::ObjectType::Properties::DisplayName::Id)->setValue(value ); }
		String getDisplayName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::ObjectType::Properties::DisplayName::Id)->getValue())->getValue(); }
		void setDisplayName(const String& value) { getProperty(System::ObjectType::Properties::DisplayName::Id)->setValue(StringValue::make(value)); }

		ValuePtr getPropertyTypesValue() const { return dynamic_pointer_cast<const VectorValue>(getProperty(System::ObjectType::Properties::PropertyTypes::Id)->getValue()); }
		void setPropertyTypesValue(ValuePtr value) { getProperty(System::ObjectType::Properties::PropertyTypes::Id)->setValue(value ); }
		Vector getPropertyTypes() const { return dynamic_pointer_cast<const VectorValue>(getProperty(System::ObjectType::Properties::PropertyTypes::Id)->getValue())->getValue(); }
		void setPropertyTypes(const Vector& value) { getProperty(System::ObjectType::Properties::PropertyTypes::Id)->setValue(VectorValue::make(value)); }
	};
	namespace System
	{
		namespace PropertyTypeT
		{
			using BaseTraits = System::ObjectBase;
			namespace Name
			{
				struct PropertyT
				{
					static String getName() { return "Name"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1>;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1>;
			}
			namespace Type
			{
				struct PropertyT
				{
					static String getName() { return "Type"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1>;
			}
			struct ObjectT
			{
				static String getCategory() { return "System"; }
				static String getName() { return "PropertyType"; }
				static UuId getTypeId() { static const UuId id = generateIdFromString("{5BD0E6BB-B3A8-4CD5-A764-F5B0826ED79A}"); return id; }
			};
			struct PropertiesT
			{
				using Name = Name::Traits;
				using DisplayName = DisplayName::Traits;
				using Type = Type::Traits;
				using List = std::tuple<Name,DisplayName,Type>;
				enum { LastId = std::tuple_size<List>::value };
			};
			using Traits = ObjectTraits<ObjectT, BaseTraits, PropertiesT>;
		}
		using PropertyType = PropertyTypeT::Traits;
	}
	template<>
	struct ObjectAccess<System::PropertyType> : public ObjectImpl<System::PropertyType::BaseTraits>
	{
		ValuePtr getNameValue() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::Name::Id)->getValue()); }
		void setNameValue(ValuePtr value) { getProperty(System::PropertyType::Properties::Name::Id)->setValue(value ); }
		String getName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::Name::Id)->getValue())->getValue(); }
		void setName(const String& value) { getProperty(System::PropertyType::Properties::Name::Id)->setValue(StringValue::make(value)); }

		ValuePtr getDisplayNameValue() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::DisplayName::Id)->getValue()); }
		void setDisplayNameValue(ValuePtr value) { getProperty(System::PropertyType::Properties::DisplayName::Id)->setValue(value ); }
		String getDisplayName() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::DisplayName::Id)->getValue())->getValue(); }
		void setDisplayName(const String& value) { getProperty(System::PropertyType::Properties::DisplayName::Id)->setValue(StringValue::make(value)); }

		ValuePtr getTypeValue() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::Type::Id)->getValue()); }
		void setTypeValue(ValuePtr value) { getProperty(System::PropertyType::Properties::Type::Id)->setValue(value ); }
		String getType() const { return dynamic_pointer_cast<const StringValue>(getProperty(System::PropertyType::Properties::Type::Id)->getValue())->getValue(); }
		void setType(const String& value) { getProperty(System::PropertyType::Properties::Type::Id)->setValue(StringValue::make(value)); }
	};
}

#endif
