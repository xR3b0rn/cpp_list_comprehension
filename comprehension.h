
#pragma once

#include <type_traits>
#include <boost/phoenix.hpp>

#include "do__.h"
#include "for_each_.h"

namespace comprehension
{
	namespace detail
	{
		struct Insert
		{
			using result_type = void;
			template <class T, class V, class... Args>
			void operator()(T& comp_vec, const V& v, const Args&... args) const
			{
				comp_vec.ins(boost::phoenix::ref(v), args...);
			}
		};
	}
	template <class Con>
	class CompVec
		: public Con
	{
	public:
		using this_t = CompVec<Con>;
		using base1_t = Con;
		using base1_t::base1_t;
		template <class F1, class... Args, std::enable_if_t<std::is_invocable_v<F1>, void*> = nullptr>
		CompVec(const F1& fu, const Args&... args)
			: base1_t{}
		{
			ins(fu, args...);
		}

	private:
		template <class V, class F1>
		void ins(const V& v, const F1& f1)
		{
			f1
			[
				boost::phoenix::push_back(boost::phoenix::ref(*this), v)
			]();
		}
		template <class V, class F1, class F2, class... Args>
		void ins(const V& v, const F1& f1, const F2& f2, const Args&... args)
		{
			boost::phoenix::function<detail::Insert> ph_ins;
			f1
			[
				ph_ins(boost::phoenix::ref(*this), v, f2, args...)
			]();
		}
		friend detail::Insert;
	};
}
