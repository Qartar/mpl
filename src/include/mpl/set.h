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

} // namespace mpl

#endif _mpl_set_h_
