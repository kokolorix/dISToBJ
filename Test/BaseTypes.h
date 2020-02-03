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
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 0 >;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1 >;
			}
			namespace PropertyTypes
			{
				struct PropertyT
				{
					static String getName() { return "PropertyTypes"; }
					static ValuePtr getDefaultValue() { return VectorValue::make(Vector()); }
				};
				using Traits = PropertyTraits<PropertyT,Vector, BaseTraits::Properties::LastId + 2 >;
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
		/*!
		\include ObjectType.xml
		\include ObjectType.cpp
		*/
		using ObjectType = ObjectTypeT::Traits;
	}
	/// \copydoc System::ObjectType
	template<>
	struct ObjectAccess<System::ObjectType> : public ObjectImpl<System::ObjectType::BaseTraits>
	{
		ValuePtr getName() const
		{
			auto property = getProperty(System::ObjectType::Properties::Name::Id);
			return property->getValue();
		}
		void setName(ValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::Name::Id);
			property->setValue(value);
		}

		ValuePtr getDisplayName() const
		{
			auto property = getProperty(System::ObjectType::Properties::DisplayName::Id);
			return property->getValue();
		}
		void setDisplayName(ValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::DisplayName::Id);
			property->setValue(value);
		}

		ValuePtr getPropertyTypes() const
		{
			auto property = getProperty(System::ObjectType::Properties::PropertyTypes::Id);
			return property->getValue();
		}
		void setPropertyTypes(ValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::PropertyTypes::Id);
			property->setValue(value);
		}
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
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 0 >;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 1 >;
			}
			namespace Type
			{
				struct PropertyT
				{
					static String getName() { return "Type"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits<PropertyT,String, BaseTraits::Properties::LastId + 2 >;
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
		/*!
		\include PropertyType.xml
		\include PropertyType.cpp
		*/
		using PropertyType = PropertyTypeT::Traits;
	}
	/// \copydoc System::PropertyType
	template<>
	struct ObjectAccess<System::PropertyType> : public ObjectImpl<System::PropertyType::BaseTraits>
	{
		ValuePtr getName() const
		{
			auto property = getProperty(System::PropertyType::Properties::Name::Id);
			return property->getValue();
		}
		void setName(ValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::Name::Id);
			property->setValue(value);
		}

		ValuePtr getDisplayName() const
		{
			auto property = getProperty(System::PropertyType::Properties::DisplayName::Id);
			return property->getValue();
		}
		void setDisplayName(ValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::DisplayName::Id);
			property->setValue(value);
		}

		ValuePtr getType() const
		{
			auto property = getProperty(System::PropertyType::Properties::Type::Id);
			return property->getValue();
		}
		void setType(ValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::Type::Id);
			property->setValue(value);
		}
	};
}

#endif
