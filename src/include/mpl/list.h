#ifndef _mpl_list_h_
#define _mpl_list_h_

#include "mpl/cons.h"

namespace mpl {

///////////////////////////////////////////////////////////////////////////////
/**
 * nil
 *
 * Fundamental metatype which marks the end of a list.
 */
class nil;

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `list` metafunction
template<typename... _Targs> struct fn_list;

template<typename _Tx, typename... _Targs>
struct fn_list<_Tx, _Targs...> {
    using type = cons<_Tx, typename fn_list<_Targs...>::type>;
};

template<typename _Tx>
struct fn_list<_Tx> {
    using type = cons<_Tx, nil>;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * list
 *
 * Fundamental metafunction for constructing an s-expression list from a
 * variadic list of type arguments.
 */
template<typename... _Targs> using list = typename detail::fn_list<_Targs...>::type;

} // namespace mpl

#endif _mpl_list_h
