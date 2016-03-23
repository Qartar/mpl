#ifndef _mpl_set_h_
#define _mpl_set_h_

#include "mpl/cons.h"
#include "mpl/list.h"
#include "mpl/logical.h"

namespace mpl {

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `is_same` metafunction
template<typename _Tx, typename _Ty> struct fn_is_same_impl {
    using type = false_type;
};

template<typename _Tx> struct fn_is_same_impl<_Tx, _Tx> {
    using type = true_type;
};

//! Use a layer of indirection to allow specialization.
template<typename _Tx, typename _Ty, typename = void> struct fn_is_same {
    using type = typename fn_is_same_impl<_Tx, _Ty>::type;
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

template<typename _Tx, typename _Ty, template<typename, typename> class _Tcmp>
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

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `meet` metafunction
template<template<typename, typename> class _Tcmp, typename _Tsets, typename _Ty, typename = void> struct fn_all_contains {
    using type = false_type;
};

template<template<typename, typename> class _Tcmp, typename _Tsets, typename _Ty>
struct fn_all_contains<_Tcmp, _Tsets, _Ty, enable_if<fn_contains_t<car<_Tsets>, _Ty, _Tcmp>::value>> {
    using type = typename fn_all_contains<_Tcmp, cdr<_Tsets>, _Ty>::type;
};

template<template<typename, typename> class _Tcmp, typename _Ty>
struct fn_all_contains<_Tcmp, nil, _Ty, void> {
    using type = true_type;
};

template<template<typename, typename> class _Tcmp, typename _Tsets, typename _Ty>
using fn_all_contains_t = typename fn_all_contains<_Tcmp, _Tsets, _Ty>::type;

template<template<typename, typename> class _Tcmp, typename _Telems, typename _Tsets, typename _Tout = nil, typename = void> struct fn_meet_iter {
    using type = typename fn_meet_iter<_Tcmp, cdr<_Telems>, _Tsets, _Tout>::type;
};

template<template<typename, typename> class _Tcmp, typename _Telems, typename _Tsets, typename _Tout>
struct fn_meet_iter<_Tcmp, _Telems, _Tsets, _Tout, enable_if<fn_all_contains_t<_Tcmp, _Tsets, car<_Telems>>::value>> {
    using type = typename fn_meet_iter<_Tcmp, cdr<_Telems>, _Tsets, append<_Tout, car<_Telems>>>::type;
};

template<template<typename, typename> class _Tcmp, typename _Tsets, typename _Tout>
struct fn_meet_iter<_Tcmp, nil, _Tsets, _Tout, void> {
    using type = _Tout;
};

template<template<typename, typename> class _Tcmp, typename... _Targs> struct fn_meet {
    using type = typename fn_meet_iter<_Tcmp,
                                       typename fn_join<_Tcmp, _Targs...>::type,
                                       typename fn_list<_Targs...>::type>::type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * is_same
 *
 * Metafunction for determining whether two types are the same. Evaluates to
 * `true_type` if _Tx and _Ty are the same type, otherwise evaluates to
 * `false_type`.
 */
template<typename _Tx, typename _Ty> using is_same = typename detail::fn_is_same<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * contains
 *
 * Metafunction for determining if an iterable container metatype contains
 * another type. Evaluates to `true_type` if container _Tx contains the type
 * _Ty as determined by the _Tcmp operator. (default: `is_same`)
 */
template<typename _Tx, typename _Ty, template<typename, typename> class _Tcmp = is_same>
using contains = typename detail::fn_contains<_Tx, _Ty, _Tcmp>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * set
 *
 * Metafunction for constructing an s-expression set metatype from a variadic
 * list of type arguments. The `is_same` metafunction is used to determine type
 * equivalence.
 */
template<typename... _Targs> using set = typename detail::fn_set<is_same, _Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * join
 *
 * Metafunction for determining the union of a variadic list of `set` metatypes.
 */
template<typename... _Targs> using join = typename detail::fn_join<is_same, _Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * meet
 *
 * Metafunction for determining the intersection of a variadic list of `set`
 * metatypes.
 */
template<typename... _Targs> using meet = typename detail::fn_meet<is_same, _Targs...>::type;

} // namespace mpl

#endif //_mpl_set_h_
