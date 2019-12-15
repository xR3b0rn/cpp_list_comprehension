
#pragma once

#include <type_traits>

namespace comprehension
{
	namespace detail
	{
		template <class Ret, auto F>
		struct s_lazy
		{
			using result_type = Ret;
			template <class... Args>
			result_type operator()(Args&&... args) const
			{
				return F(std::forward<Args>(args)...);
			}
		};
	}
	template <class Ret, auto F>
	constexpr auto make_lazy()
	{
		return boost::phoenix::function<detail::s_lazy<Ret, F>>();
	}
}
