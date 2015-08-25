#ifndef _mpl_logical_h_
#define _mpl_logical_h_

namespace mpl {

///////////////////////////////////////////////////////////////////////////////
/**
 * true_type
 */
struct true_type {
    static const bool value = true;
};

///////////////////////////////////////////////////////////////////////////////
/**
 * false_type
 */
struct false_type {
    static const bool value = false;
};

namespace detail {

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `enable_if` metafunction
template<bool _Tbool, typename _Ty = void> struct fn_enable_if;

template<typename _Ty>
struct fn_enable_if<true, _Ty> {
    using type = _Ty;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `and` metafunction
template<typename _Tx, typename _Ty, typename = void> struct op_and;

template<typename _Tx, typename _Ty>
struct op_and < _Tx, _Ty, typename fn_enable_if < !(_Tx::value&& _Ty::value) >::type > {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct op_and < _Tx, _Ty, typename fn_enable_if < _Tx::value&& _Ty::value >::type > {
    using type = true_type;
};

template<typename _Tx, typename... _Targs> struct fn_and;

template<typename _Tx, typename... _Targs>
struct fn_and<_Tx, _Targs...> {
    using type = typename op_and<_Tx, typename fn_and<_Targs...>::type>::type;
};

template<typename _Tx, typename _Ty>
struct fn_and<_Tx, _Ty> {
    using type = typename op_and<_Tx, _Ty>::type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `or` metafunction
template<typename _Tx, typename _Ty, typename = void> struct op_or;

template<typename _Tx, typename _Ty>
struct op_or < _Tx, _Ty, typename fn_enable_if < !(_Tx::value || _Ty::value) >::type > {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct op_or < _Tx, _Ty, typename fn_enable_if < _Tx::value || _Ty::value >::type > {
    using type = true_type;
};

template<typename _Tx, typename... _Targs> struct fn_or;

template<typename _Tx, typename... _Targs>
struct fn_or<_Tx, _Targs...> {
    using type = typename op_or<_Tx, typename fn_or<_Targs...>::type>::type;
};

template<typename _Tx, typename _Ty>
struct fn_or<_Tx, _Ty> {
    using type = typename op_or<_Tx, _Ty>::type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * enable_if
 */
template<bool _Tbool, typename _Ty = void> using enable_if = typename detail::fn_enable_if<_Tbool, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * and
 */
template<typename _Tx, typename _Ty, typename... _Targs> using and = typename detail::fn_and<_Tx, _Ty, _Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * or
 */
template<typename _Tx, typename _Ty, typename... _Targs> using or = typename detail::fn_or<_Tx, _Ty, _Targs...>::type;

} // namespace mpl

#endif _mpl_logical_h_
