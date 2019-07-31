	//---------------------------------------------------------------------------
#ifndef ObjectRepositoryH
#define ObjectRepositoryH
//---------------------------------------------------------------------------

#include "Object.h"

namespace srdev
{
	class ObjectRepository;
	using ObjectRepositoryPtr = shared_ptr<ObjectRepository>;

	class ObjectRepository : public Base
	{
	public:
		ObjectRepository();
		virtual ~ObjectRepository();
		ObjectRepository(const ObjectRepository& other);
		ObjectRepository& operator=(const ObjectRepository& other);

		static ObjectRepositoryPtr make();

		ObjectPtr getObject();
		ObjectPtrVector getObjects();

	
	protected:

	private:
		struct Impl;
		struct ImplDeleter { void operator()(Impl* impl); };
		std::unique_ptr<Impl, ImplDeleter> impl_;
	};

}
#endif // ObjectRepository_H
