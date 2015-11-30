#ifndef _mpl_list_h_
#define _mpl_list_h_

#include "mpl/cons.h"
#include "mpl/logical.h"

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

template<>
struct fn_list<> {
    using type = nil;
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

template<typename _Tx>
struct fn_extend<nil, _Tx> {
    using type = _Tx;
};

template<typename _Tx>
struct fn_extend<_Tx> {
    using type = _Tx;
};

template<>
struct fn_extend<> {
    using type = nil;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `insert` metafunction
template<typename _Tx, int _Ny, typename... _Targs> struct fn_insert;

template<typename _Tx, typename _Ty, int _Nz, typename... _Targs>
struct fn_insert<cons<_Tx, _Ty>, _Nz, _Targs...> {
    using type = cons < _Tx, typename fn_insert < _Ty, _Nz - 1, _Targs... >::type >;
};

template<typename _Tx, typename _Ty, typename... _Targs>
struct fn_insert<cons<_Tx, _Ty>, 0, _Targs...> {
    using type = typename fn_extend<typename fn_list<_Targs..., _Tx>::type, _Ty>::type;
};

template<typename... _Targs>
struct fn_insert<nil, 0, _Targs...> {
    using type = typename fn_list<_Targs...>::type;
};

template<int _Nx, typename... _Targs>
struct fn_insert<nil, _Nx, _Targs...> {
    static_assert(_Nx < 0, "Index out of bounds.");
    using type = nil;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `remove` metafunction
template<typename _Tx, int _Ny> struct fn_remove;

template<typename _Tx, typename _Ty, int _Nz>
struct fn_remove<cons<_Tx, _Ty>, _Nz> {
    using type = cons < _Tx, typename fn_remove < _Ty, _Nz - 1 >::type >;
};

template<typename _Tx, typename _Ty>
struct fn_remove<cons<_Tx, _Ty>, 0> {
    using type = _Ty;
};

template<int _Nx>
struct fn_remove<nil, _Nx> {
    static_assert(_Nx < 0, "Index out of bounds.");
    using type = nil;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `index` metafunction
template<typename _Tx, int _Ny> struct fn_index;

template<typename _Tx, typename _Ty, int _Nz>
struct fn_index<cons<_Tx, _Ty>, _Nz> {
    using type = typename fn_index < _Ty, _Nz - 1 >::type;
};

template<typename _Tx, typename _Ty>
struct fn_index<cons<_Tx, _Ty>, 0> {
    using type = _Tx;
};

template<int _Nx>
struct fn_index<nil, _Nx> {
    static_assert(_Nx < 0, "Index out of bounds.");
    using type = nil;
};

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `find` metafunction
template<typename _Tx, template<typename> class _Tpred, typename = void>
struct fn_find;

template<typename _Tx, typename _Ty, template<typename> class _Tpred>
struct fn_find<cons<_Tx, _Ty>, _Tpred, enable_if<!_Tpred<_Tx>::value>> {
    using type = typename fn_find<_Ty, _Tpred>::type;
};

template<typename _Tx, typename _Ty, template<typename> class _Tpred>
struct fn_find<cons<_Tx, _Ty>, _Tpred, enable_if<_Tpred<_Tx>::value>> {
    using type = _Tx;
};

template<template<typename> class _Tpred>
struct fn_find<nil, _Tpred, void> {
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
 * Metafunction for concatenating a variadic list of `list` metatypes into a
 * single `list` metatype.
 */
template<typename... _Targs> using extend = typename detail::fn_extend<_Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * append
 *
 * Metafunction for appending one or more type elements onto a `list` metatype.
 */
template<typename _Tx, typename _Ty, typename... _Targs> using append = extend<_Tx, list<_Ty, _Targs...>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * insert
 *
 * Metafunction for inserting one or more type elements into a `list` metatype.
 */
template<typename _Tx, int _Ny, typename _Tz, typename... _Targs> using insert = typename detail::fn_insert<_Tx, _Ny, _Tz, _Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * remove
 *
 * Metafunction for removing a type element by index from a `list` metatype.
 */
template<typename _Tx, int _Ny> using remove = typename detail::fn_remove<_Tx, _Ny>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * index
 *
 * Metafunction for retrieving the n-th type element from a `list` metatype.
 */
template<typename _Tx, int _Ny> using index = typename detail::fn_index<_Tx, _Ny>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * find
 *
 * Metafunction for retrieving the first type element from a `list` metatype
 * which satisfies the given predicate metafunction. For retrieving all type
 * elements which satisfy a predicate use `filter`. (mpl/functional.h)
 */
template<typename _Tx, template<typename> class _Tpred>
using find = typename detail::fn_find<_Tx, _Tpred>::type;

} // namespace mpl

#endif _mpl_list_h
