#ifndef _mpl_functional_h_
#define _mpl_functional_h_

#include "mpl/cons.h"
#include "mpl/list.h"

namespace mpl {

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `map` metafunction
template<template<typename> class _Tfunc, typename _Tlist> struct fn_map;

template<template<typename> class _Tfunc, typename _Tx, typename _Ty>
struct fn_map<_Tfunc, cons<_Tx, _Ty>> {
    using type = cons<_Tfunc<_Tx>, typename fn_map<_Tfunc, _Ty>::type>;
};

template<template<typename> class _Tfunc>
struct fn_map<_Tfunc, nil> {
    using type = nil;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `filter` metafunction
template<template<typename> class _Tpred, typename _Tlist, typename = void> struct fn_filter;

template<template<typename> class _Tpred, typename _Tx, typename _Ty>
struct fn_filter < _Tpred, cons<_Tx, _Ty>, std::enable_if_t < !_Tpred<_Tx>::value >> {
    using type = typename fn_filter<_Tpred, _Ty>::type;
};

template<template<typename> class _Tpred, typename _Tx, typename _Ty>
struct fn_filter<_Tpred, cons<_Tx, _Ty>, std::enable_if_t<_Tpred<_Tx>::value>> {
    using type = cons<_Tx, typename fn_filter<_Tpred, _Ty>::type>;
};

template<template<typename> class _Tpred>
struct fn_filter<_Tpred, nil> {
    using type = nil;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `reduce` metafunction
template<template<typename, typename> class _Top, typename _Tlist> struct fn_reduce;

template<template<typename, typename> class _Top, typename _Tx, typename _Ty>
struct fn_reduce<_Top, cons<_Tx, _Ty>> {
    using type = _Top<_Tx, typename fn_reduce<_Top, _Ty>::type>;
};

template<template<typename, typename> class _Top, typename _Tx, typename _Ty>
struct fn_reduce<_Top, cons<_Tx, cons<_Ty, nil>>> {
    using type = _Top<_Tx, _Ty>;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * map
 *
 * Metafunction for applying a metafunction to each type element in a `list` metatype.
 */
template<template<typename> class _Tfunc, typename _Tlist> using map = typename detail::fn_map<_Tfunc, _Tlist>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * filter
 *
 * Metafunction for filtering out type elements in a `list` metatype which do
 * not satisfy a given predicate metafunction.
 */
template<template<typename> class _Tpred, typename _Tlist> using filter = typename detail::fn_filter<_Tpred, _Tlist>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * reduce
 *
 * Metafunction for combining all type elements in a `list` metatype by
 * repeatedly applying an operator metafunction to adjacent type elements.
 */
template<template<typename, typename> class _Top, typename _Tlist> using reduce = typename detail::fn_reduce<_Top, _Tlist>::type;

} // namespace mpl

#endif _mpl_functional_h_
