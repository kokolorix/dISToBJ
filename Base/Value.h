//---------------------------------------------------------------------------
#ifndef ValueH
#define ValueH
//---------------------------------------------------------------------------
#include "Base.h"
#include "Cast.h"
namespace srdev
{
	class Value;
	struct ValuePtr : public shared_ptr<const Value>
	{
		using Base = shared_ptr<const Value>;
		using Base::Base;
		ValuePtr() : Base() {}
		ValuePtr(Base ptr) : Base(ptr) {}
		template<typename T>
		ValuePtr(T v);
		operator int32_t() const;
		operator uint32_t() const;
		operator double() const;
		operator String() const;
		//operator UuId() const;
	};
	using ValuePtrVector = std::vector<ValuePtr>;
	class Value : public Base
	{
	public:
		Value();
		virtual ~Value();
		Value(const Value& other);
		Value& operator=(const Value& other);

		operator String () const { return toString(); }
		static ValuePtr parse(const String& s);

		static ValuePtr make();
		static ValuePtr make(std::initializer_list<ValuePtr> v);

		template<typename T>
		static ValuePtr make(T v);

	protected:

	private:
	};
}

namespace srdev
{
	template <typename T>
	class ValueImpl : public Value
	{
	public:
		ValueImpl() : value_() {}
		ValueImpl(T v) : value_(v) {}
		virtual ~ValueImpl() {}
		template<typename U>
		operator U () const { return cast<U>(value_); }

	public:
		const T& getValue() const { return value_; }
		T& getValue() { return value_; }

		static std::shared_ptr<const ValueImpl<T>> make(T v)
		{
			return make_shared<const ValueImpl<T>>(v);
		}

		virtual String toString() const
		{
			return cast<String>(value_);
		}

	private:
		T value_;
	};
	template <>
	class ValueImpl<void> : public Value
	{
	public:
		ValueImpl() {}
		//ValueImpl(IdType id) : Value(id) {}
		virtual ~ValueImpl() {}
		virtual bool operator<(const Base & other) const override
		{
			if (auto o = dynamic_cast<decltype(this)>(&other))
				return *this < *o;
			else
				return Base::operator<(other);
		}
		bool operator < (const ValueImpl& other) const
		{
			return this < &other;
		}

	public:
		struct voidT {};
		voidT getValue() const { return voidT(); }

		static std::shared_ptr<ValueImpl<void>> make()
		{
			return make_shared<ValueImpl<void>>();
		}

		virtual String toString() const override
		{
			return String();
		}
	};

	using VoidValue = ValueImpl<void>;
	using BooleanValue = ValueImpl<bool>;
	using Int32Value = ValueImpl<int32_t>;
	using UInt32Value = ValueImpl<uint32_t>;
	using Int64Value = ValueImpl<int64_t>;
	using UInt64Value = ValueImpl<uint64_t>;
	using DoubleValue = ValueImpl<double>;
	using StringValue = ValueImpl<String>;
	//using UuIdValue = ValueImpl<UuId>;
	using VectorValue = ValueImpl<ValuePtrVector>;
	template<typename T>
	inline ValuePtr Value::make(T v)
	{
		return ValueImpl<T>::make(v);
	}
	template<>
	inline ValuePtr Value::make(const String::value_type* v)
	{
		return ValueImpl<String>::make(String(v));
	}
	template<>
	inline ValuePtr Value::make(ValuePtr v)
	{
		return v;
	}

	template< typename T >
	inline ValuePtr::ValuePtr(T v) : Base(Value::make(v))
	{
	}
	template<>
	inline ValuePtr::ValuePtr(const String::value_type* v) : Base(Value::make(v))
	{
	}

	inline bool operator < (ValuePtr x, ValuePtr y)
	{
		bool result = (x.get() && y.get()) ? (*x < *y) : x.get() < y.get();
		return result;
	}
	inline bool operator == (ValuePtr x, ValuePtr y)
	{
		bool result = x.get() == y.get() || (x.get() && y.get() && !(*x < *y) && !(*y < *x));
		return result;
	}

	template<typename T>
	inline bool operator < (T x, const Value& y)
	{
		if (auto yv = dynamic_cast<const ValueImpl<T>*>(&y))
			return x < yv->getValue();
		else
			throw srdev::ImpossibleCompareException(__func__);
	}

	template<typename T>
	inline bool operator > (T x, const Value& y)
	{
		if (auto yv = dynamic_cast<const ValueImpl<T>*>(&y))
			return x > yv->getValue();
		else
			throw srdev::ImpossibleCompareException(__func__);
	}

	template<typename T>
	inline bool operator == (T x, const Value& y)
	{
		if (auto yv = dynamic_cast<const ValueImpl<T>*>(&y))
			return x == yv->getValue();
		else
			throw srdev::ImpossibleCompareException(__func__);
	}
	template<>
	inline bool operator == (const String& x, const Value& y)
	{
		return  x == y.toString();
	}
	template<>
	inline bool operator == (const char* x, const Value& y)
	{
		return  String(x) == y.toString();
	}

	template<typename T>
	inline bool operator == (const Value& x, T y)
	{
		if (auto xv = dynamic_cast<const ValueImpl<T>*>(&x))
			return xv->getValue() == y;
		else
			throw srdev::ImpossibleCompareException(__func__);
	}
	template<>
	inline bool operator == (const Value& x, const String::value_type* y)
	{
		if (auto xv = dynamic_cast<const ValueImpl<String>*>(&x))
			return xv->getValue() == y;
		else
			throw srdev::ImpossibleCompareException(__func__);
	}
	template<typename T>
	inline bool operator < (const Value& x, T y)
	{
		if (auto xv = dynamic_cast<const ValueImpl<T>*>(&x))
			return xv->getValue() < y;
		else
			throw srdev::ImpossibleCompareException(__func__);
	}
	template<typename T>
	inline bool operator > (const Value& x, T y)
	{
		if (auto xv = dynamic_cast<const ValueImpl<T>*>(&x))
			return xv->getValue() > y;
		else
			throw srdev::ImpossibleCompareException(__func__);
	}
}

namespace srdev
{
	namespace impl
	{
		template<>
		struct cast_helper<String, ValuePtrVector>
		{
			inline String operator()(ValuePtrVector in)
			{
				std::ostringstream os;
				for(auto it = in.begin(); it != in.end(); ++it)
					os << (it == in.begin() ? cast<String>(*it) : String(" ,") + cast<String>(*it));
				return String(os.str());
			}
		};
	}
}

#endif
