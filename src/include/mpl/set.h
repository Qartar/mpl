#ifndef _mpl_set_h_
#define _mpl_set_h_

#include "mpl/cons.h"
#include "mpl/list.h"
#include "mpl/logical.h"

namespace mpl {

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `is_same` metafunction
template<typename _Tx, typename _Ty> struct fn_is_same {
    using type = false_type;
};

template<typename _Tx> struct fn_is_same<_Tx, _Tx> {
    using type = true_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `contains` metafunction
template<typename _Tx, typename _Ty, template<typename, typename> class _Tcmp, typename = void>
struct fn_contains;

template<typename _Tx, typename _Ty, typename _Tz, template<typename, typename> class _Tcmp>
struct fn_contains<cons<_Tx, _Ty>, _Tz, _Tcmp, enable_if<!_Tcmp<_Tx, _Tz>::value>> {
    using type = typename fn_contains<_Ty, _Tz, _Tcmp>::type;
};

template<typename _Tx, typename _Ty, typename _Tz, template<typename, typename> class _Tcmp>
struct fn_contains<cons<_Tx, _Ty>, _Tz, _Tcmp, enable_if<_Tcmp<_Tx, _Tz>::value>> {
    using type = true_type;
};

template<typename _Tx, template<typename, typename> class _Tcmp>
struct fn_contains<nil, _Tx, _Tcmp, void> {
    using type = false_type;
};

template<typename _Tx, typename _Ty, template<typename, typename> class _Tcmp = is_same>
using fn_contains_t = typename fn_contains<_Tx, _Ty, _Tcmp>::type;

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `set` metafunction
template<template<typename, typename> class _Tcmp, typename _Tx, typename _Ty = nil, typename = void> struct fn_set_iter;

template<template<typename, typename> class _Tcmp, typename _Tx, typename _Ty>
struct fn_set_iter<_Tcmp, _Tx, _Ty, enable_if<fn_contains_t<_Ty, car<_Tx>, _Tcmp>::value>> {
    using type = typename fn_set_iter<_Tcmp, cdr<_Tx>, _Ty>::type; 
};

template<template<typename, typename> class _Tcmp, typename _Tx, typename _Ty>
struct fn_set_iter<_Tcmp, _Tx, _Ty, enable_if<!fn_contains_t<_Ty, car<_Tx>, _Tcmp>::value>> {
    using type = typename fn_set_iter<_Tcmp, cdr<_Tx>, append<_Ty, car<_Tx>>>::type;
};

template<template<typename, typename> class _Tcmp, typename _Tx>
struct fn_set_iter<_Tcmp, nil, _Tx, void> {
    using type = _Tx;
};

template<template<typename, typename> class _Tcmp, typename... _Targs> struct fn_set {
    using type = typename fn_set_iter<_Tcmp, list<_Targs...>>::type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `join` metafunction
template<template<typename, typename> class _Tcmp, typename... _Targs> struct fn_join {
    using type = typename fn_set_iter<_Tcmp, extend<_Targs...>>::type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * is_same
 */
template<typename _Tx, typename _Ty> using is_same = typename detail::fn_is_same<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * contains
 */
template<typename _Tx, typename _Ty, template<typename, typename> class _Tcmp = is_same>
using contains = typename detail::fn_contains<_Tx, _Ty, _Tcmp>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * set
 */
template<typename... _Targs> using set = typename detail::fn_set<is_same, _Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * join
 */
template<typename... _Targs> using join = typename detail::fn_join<is_same, _Targs...>::type;

} // namespace mpl

#endif _mpl_set_h_
