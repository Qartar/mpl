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

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `extend` metafunction
template<typename... _Targs> struct fn_extend;

template<typename _Tx, typename _Ty, typename... _Targs>
struct fn_extend<_Tx, _Ty, _Targs...> {
    using type = typename fn_extend<typename fn_extend<_Tx, _Ty>::type, _Targs...>::type;
};

template<typename _Tx, typename _Ty, typename _Tz>
struct fn_extend<cons<_Tx, _Ty>, _Tz> {
    using type = cons<_Tx, typename fn_extend<_Ty, _Tz>::type>;
};

template<typename _Tx, typename _Ty>
struct fn_extend<cons<_Tx, nil>, _Ty> {
    using type = cons<_Tx, _Ty>;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `index` metafunction
template<int _Tx, typename _Ty> struct fn_index;

template<int _Tx, typename _Ty, typename _Tz>
struct fn_index<_Tx, cons<_Ty, _Tz>> {
    using type = typename fn_index < _Tx - 1, _Tz >::type;
};

template<typename _Tx, typename _Ty>
struct fn_index<0, cons<_Tx, _Ty>> {
    using type = _Tx;
};

template<int _Tx>
struct fn_index<_Tx, nil> {
    static_assert(_Tx < 0, "Index out of bounds.");
    using type = nil;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * list
 *
 * Fundamental metafunction for constructing an s-expression list metatype from
 * a variadic list of type arguments.
 */
template<typename... _Targs> using list = typename detail::fn_list<_Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * extend
 *
 * Metafunction for concatenating two or more s-expression list metatypes into
 * a single s-expression list metatype.
 */
template<typename... _Targs> using extend = typename detail::fn_extend<_Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * append
 *
 * Metafunction for appending one or more types to an s-expression list metatype.
 */
template<typename _Tx, typename... _Targs> using append = extend<_Tx, list<_Targs...>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * index
 *
 * Metafunction for retrieving the n-th type from an s-expression list metatype.
 */
template<int _Tx, typename _Ty> using index = typename detail::fn_index<_Tx, _Ty>::type;

} // namespace mpl

#endif _mpl_list_h
