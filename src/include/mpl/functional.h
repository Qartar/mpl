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

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * map
 *
 * Metafunction for applying a metafunction to each type element in a `list` metatype.
 */
template<template<typename> class _Tfunc, typename _Tlist> using map = typename detail::fn_map<_Tfunc, _Tlist>::type;

} // namespace mpl

#endif _mpl_functional_h_
