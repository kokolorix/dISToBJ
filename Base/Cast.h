//---------------------------------------------------------------------------

#ifndef CastH
#define CastH
#include <sstream>
//---------------------------------------------------------------------------

namespace srdev
{
	namespace impl
	{
		// template <typename R, class In, template <class In> class P>
		// struct cast_helper
		// {
		//     inline R operator()(P<In> p) { return *p; }
		// };
		template <typename R, typename In>
		struct cast_helper
		{
			inline R operator()(In in) { return static_cast<R>(in); }
		};
		template <typename In>
		struct cast_helper<String,In>
		{
			inline String operator()(In in) 
			{
				std::ostringstream os;
				os << in;
				return String(os.str());
			}
		};
	} // namespace impl
	template <typename R, typename In>
	R cast(In in)
	{
		impl::cast_helper<R, In> helper;
		return helper(in);
	}
} // namespace srdev
#endif
