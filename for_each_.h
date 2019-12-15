
#pragma once

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>
    
BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(for_each_)
  , (meta_grammar) // Con
    (meta_grammar) // Iter
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct for_each_eval
    {
        typedef void result_type;

        template <
				class Con
			  , class Iter
			  , class Do
			  , class Context
			>
        result_type operator()(
				const Con& con
			  , const Iter& iter
			  , const Do& do_it
			  , const Context & ctx
			) const
        {
            for(const auto& val : boost::phoenix::eval(con, ctx))
			{
				boost::phoenix::eval(iter, ctx) = val;
                boost::phoenix::eval(do_it, ctx);
			}
        }
    };
    
    template <class Dummy>
    struct default_actions::when<rule::for_each_, Dummy>
        : call<for_each_eval, Dummy>
    {};
    
    template <class Con, class Iter>
    struct for_each_gen
    {
        for_each_gen(const Con& con_, const Iter& iter_)
            : con(con_)
			, iter(iter_)
		{}

        template <class Do>
        const typename expression::for_each_<Con, Iter, Do>::type operator[](const Do& do_it) const
        {
            return expression::for_each_<Con, Iter, Do>::make(con, iter, do_it);
        }

        Con con;
		Iter iter;
    };

    template <class Con, class Iter>
    inline const for_each_gen<Con, Iter> for_each_(const Con& con, const Iter& iter)
    {
        return for_each_gen<Con, Iter>(con, iter);
    }

}}

