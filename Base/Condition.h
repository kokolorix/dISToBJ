//---------------------------------------------------------------------------
#ifndef ConditionH
#define ConditionH
//---------------------------------------------------------------------------

#include "Object.h"

namespace srdev
{
	class Condition;
	using ConditionPtr = shared_ptr<Condition>;
	using ConditionPtrVector = std::vector<ConditionPtr>;

	class Condition : public Base
	{
	public:
		Condition();
		virtual ~Condition();
		Condition(const String& expression);
		Condition(const Condition& other);

		static ConditionPtr make(ConditionPtr p) { return p; }

		bool checkCondition(ObjectPtr object);
		void parseExpression();

		String getSqlWhereStatement();
		String getXPathStatement();



		virtual String toString() const override;

	protected:

	private:
		String expression_;
	};
}
#endif // Condition_H
