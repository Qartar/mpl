#ifndef _mpl_cons_h_
#define _mpl_cons_h_

namespace mpl {

///////////////////////////////////////////////////////////////////////////////
/**
 * cons
 *
 * Fundamental metatype for constructing s-expressions. Binds two types into a
 * pair which can be retrieved with the `car` and `cdr` metafunctions.
 */
template<typename _Tx, typename _Ty> class cons;

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `car` metafunction
template<typename _Tx> struct fn_car;

template<typename _Tx, typename _Ty>
struct fn_car<cons<_Tx, _Ty>> {
    using type = _Tx;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `cdr` metafunction
template<typename _Tx> struct fn_cdr;

template <typename _Tx, typename _Ty>
struct fn_cdr<cons<_Tx, _Ty>> {
    using type = _Ty;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * car
 *
 * Fundamental metafunction for retreiving the first type bound to a `cons`
 * metatype.
 */
template<typename _Tx> using car = typename detail::fn_car<_Tx>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * cdr
 *
 * Fundamental metafunction for retreiving the second type bound to a `cons`
 * metatype.
 */
template<typename _Tx> using cdr = typename detail::fn_cdr<_Tx>::type;

} // namespace mpl

#endif _mpl_cons_h_
