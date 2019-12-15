
#pragma once

#include <vector>
#include <iostream>
#include <type_traits>
#include <boost/phoenix.hpp>

#include "do__.h"

namespace comprehension
{
	namespace detail
	{
		struct Insert
		{
			using result_type = void;
			template <class T, class F1, class... Args>
			void operator()(T& comp_vec, const F1& fu, const Args&... args) const
			{
				comp_vec.ins(boost::phoenix::ref(fu), args...);
			}
		};
	}
	template <class Con>
	class CompVec
		: public Con
	{
	public:
		using base1_t = Con;
		using base1_t::base1_t;
		template <class F1, class... Args, std::enable_if_t<std::is_invocable_v<F1>, void*> = nullptr>
		CompVec(const F1& fu, const Args&... args)
			: base1_t{}
		{
			ins(fu, args...);
		}

	private:
		template <class F1, class F2>
		auto ins(const F1& fu, const F2& fo)
		{
			fo
			[
				boost::phoenix::push_back(boost::phoenix::ref(*this), fu)
			]();
		}
		template <class F1, class F2, class... Args>
		void ins(const F1& fu, const F2& fo, const Args&... args)
		{
			boost::phoenix::function<detail::Insert> ph_ins;
			fo
			[
				ph_ins(boost::phoenix::ref(*this), fu, args...)
			]();
		}
		friend detail::Insert;
	};
}
