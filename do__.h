
#pragma once

#include <boost/phoenix/core/limits.hpp>
#include <boost/phoenix/core/call.hpp>
#include <boost/phoenix/core/expression.hpp>
#include <boost/phoenix/core/meta_grammar.hpp>

BOOST_PHOENIX_DEFINE_EXPRESSION(
    (boost)(phoenix)(do__)
  , (meta_grammar) // Cond
    (meta_grammar) // Do
)

namespace boost { namespace phoenix
{
    struct do__eval
    {
        typedef void result_type;
        template <typename Cond, typename Do, typename Context>
        result_type operator()(Cond const& cond, Do const& do_it, Context const & ctx) const
        {
            do
            {
                boost::phoenix::eval(do_it, ctx);
            } while (boost::phoenix::eval(cond, ctx));
        }
    };
    
    template <typename Dummy>
    struct default_actions::when<rule::do__, Dummy>
        : call<do__eval, Dummy>
    {};

    template <typename Cond>
    struct do__gen
    {
        do__gen(Cond const& cond_)
			: cond(cond_)
		{}

        template <typename Do>
        typename expression::do__<Cond, Do>::type const operator[](Do const& do_it) const
        {
            return expression::do__<Cond, Do>::make(cond, do_it);
        }

        const Cond& cond;
    };

    template <typename Cond>
    inline const do__gen<Cond> do__(Cond const& cond)
    {
        return do__gen<Cond>(cond);
    }


}}
