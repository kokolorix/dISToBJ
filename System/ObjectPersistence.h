	//---------------------------------------------------------------------------
#ifndef ObjectPersistenceH
#define ObjectPersistenceH
//---------------------------------------------------------------------------

#include "Object.h"
#include "Condition.h"

namespace srdev
{
	class ObjectPersistence;
	using ObjectPersistencePtr = shared_ptr<ObjectPersistence>;

	class ObjectPersistence : public Base
	{
	public:
		ObjectPersistence(const String& connectionString);
		virtual ~ObjectPersistence();
		static ObjectPersistencePtr make(const String& connectionString);

		ObjectPtr readObject(ConditionPtr condition);
		ObjectPtrVector readObjects(ConditionPtr condition);

	
	protected:
		ObjectPersistence(const ObjectPersistence& other);
		ObjectPersistence& operator=(const ObjectPersistence& other);

	private:
		struct Impl;
		struct ImplDeleter { void operator()(Impl* impl); };
		std::unique_ptr<Impl, ImplDeleter> impl_;
	};

}
#endif // ObjectPersistence_H
