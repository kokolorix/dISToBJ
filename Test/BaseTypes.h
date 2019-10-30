<?xml version="1.0" encoding="UTF-8"?>#ifndef BaseTypesH
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
				using Traits = PropertyTraits&lt;PropertyT,String, BaseTraits::Properties::LastId + 0 &gt;;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits&lt;PropertyT,String, BaseTraits::Properties::LastId + 1 &gt;;
			}
			namespace PropertyTypes
			{
				struct PropertyT
				{
					static String getName() { return "PropertyTypes"; }
					static ValuePtr getDefaultValue() { return VectorValue::make(Vector()); }
				};
				using Traits = PropertyTraits&lt;PropertyT,Vector, BaseTraits::Properties::LastId + 2 &gt;;
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
				using List = std::tuple&lt;Name,DisplayName,PropertyTypes&gt;;
				enum { LastId = std::tuple_size&lt;List&gt;::value };
			};
			using Traits = ObjectTraits&lt;ObjectT, BaseTraits, PropertiesT&gt;;
		}
		/*!
		\include ObjectType.xml
		\include ObjectType.cpp
		*/
		using ObjectType = ObjectTypeT::Traits;
	}
	/// \copydoc System::ObjectType
	template&lt;&gt;
	struct ObjectAccess&lt;System::ObjectType&gt; : public ObjectImpl&lt;System::ObjectType::BaseTraits&gt;
	{
		StringValuePtr getName() const
		{
			auto property = getProperty(System::ObjectType::Properties::Name::Id);
			return property-&gt;getValue();
		}
		void setName(StringValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::Name::Id);
			property-&gt;setValue(value);
		}

		StringValuePtr getDisplayName() const
		{
			auto property = getProperty(System::ObjectType::Properties::DisplayName::Id);
			return property-&gt;getValue();
		}
		void setDisplayName(StringValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::DisplayName::Id);
			property-&gt;setValue(value);
		}

		VectorValuePtr getPropertyTypes() const
		{
			auto property = getProperty(System::ObjectType::Properties::PropertyTypes::Id);
			return property-&gt;getValue();
		}
		void setPropertyTypes(VectorValuePtr value)
		{
			auto property = getProperty(System::ObjectType::Properties::PropertyTypes::Id);
			property-&gt;setValue(value);
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
				using Traits = PropertyTraits&lt;PropertyT,String, BaseTraits::Properties::LastId + 0 &gt;;
			}
			namespace DisplayName
			{
				struct PropertyT
				{
					static String getName() { return "DisplayName"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits&lt;PropertyT,String, BaseTraits::Properties::LastId + 1 &gt;;
			}
			namespace Type
			{
				struct PropertyT
				{
					static String getName() { return "Type"; }
					static ValuePtr getDefaultValue() { return StringValue::make(String()); }
				};
				using Traits = PropertyTraits&lt;PropertyT,String, BaseTraits::Properties::LastId + 2 &gt;;
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
				using List = std::tuple&lt;Name,DisplayName,Type&gt;;
				enum { LastId = std::tuple_size&lt;List&gt;::value };
			};
			using Traits = ObjectTraits&lt;ObjectT, BaseTraits, PropertiesT&gt;;
		}
		/*!
		\include PropertyType.xml
		\include PropertyType.cpp
		*/
		using PropertyType = PropertyTypeT::Traits;
	}
	/// \copydoc System::PropertyType
	template&lt;&gt;
	struct ObjectAccess&lt;System::PropertyType&gt; : public ObjectImpl&lt;System::PropertyType::BaseTraits&gt;
	{
		StringValuePtr getName() const
		{
			auto property = getProperty(System::PropertyType::Properties::Name::Id);
			return property-&gt;getValue();
		}
		void setName(StringValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::Name::Id);
			property-&gt;setValue(value);
		}

		StringValuePtr getDisplayName() const
		{
			auto property = getProperty(System::PropertyType::Properties::DisplayName::Id);
			return property-&gt;getValue();
		}
		void setDisplayName(StringValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::DisplayName::Id);
			property-&gt;setValue(value);
		}

		StringValuePtr getType() const
		{
			auto property = getProperty(System::PropertyType::Properties::Type::Id);
			return property-&gt;getValue();
		}
		void setType(StringValuePtr value)
		{
			auto property = getProperty(System::PropertyType::Properties::Type::Id);
			property-&gt;setValue(value);
		}
	};
}

#endif
