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
//! Implementation of `truth_type` metafunction
template<typename _Tx, typename = void> struct fn_truth_type;

template<typename _Tx>
struct fn_truth_type<_Tx, typename fn_enable_if<_Tx::value>::type> {
    using type = true_type;
};

template<typename _Tx>
struct fn_truth_type < _Tx, typename fn_enable_if < !_Tx::value >::type > {
    using type = false_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `and` metafunction
template<typename _Tx, typename _Ty, typename = void> struct fn_and;

template<typename _Tx, typename _Ty>
struct fn_and < _Tx, _Ty, typename fn_enable_if < !(_Tx::value&& _Ty::value) >::type > {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct fn_and < _Tx, _Ty, typename fn_enable_if < _Tx::value&& _Ty::value >::type > {
    using type = true_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `or` metafunction
template<typename _Tx, typename _Ty, typename = void> struct fn_or;

template<typename _Tx, typename _Ty>
struct fn_or < _Tx, _Ty, typename fn_enable_if < !(_Tx::value || _Ty::value) >::type > {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct fn_or < _Tx, _Ty, typename fn_enable_if < _Tx::value || _Ty::value >::type > {
    using type = true_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `not` metafunction
template<typename _Tx, typename = void> struct fn_not;

template<typename _Tx>
struct fn_not<_Tx, typename fn_enable_if<_Tx::value>::type> {
    using type = false_type;
};

template<typename _Tx>
struct fn_not < _Tx, typename fn_enable_if < !_Tx::value >::type > {
    using type = true_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `all` metafunction
template<typename... _Targs> struct fn_all;

template<typename _Tx, typename... _Targs>
struct fn_all<_Tx, _Targs...> {
    using type = typename fn_all<_Tx, typename fn_all<_Targs...>::type>::type;
};

template<typename _Tx, typename _Ty>
struct fn_all<_Tx, _Ty> {
    using type = typename fn_and<_Tx, _Ty>::type;
};

template<typename _Tx>
struct fn_all<_Tx> {
    using type = typename fn_truth_type<_Tx>::type;
};

template<>
struct fn_all<> {
    using type = false_type;
};

///////////////////////////////////////////////////////////////////////////////
//! Implementation of `any` metafunction
template<typename... _Targs> struct fn_any;

template<typename _Tx, typename... _Targs>
struct fn_any<_Tx, _Targs...> {
    using type = typename fn_any<_Tx, typename fn_any<_Targs...>::type>::type;
};

template<typename _Tx, typename _Ty>
struct fn_any<_Tx, _Ty> {
    using type = typename fn_or<_Tx, _Ty>::type;
};

template<typename _Tx>
struct fn_any<_Tx> {
    using type = typename fn_truth_type<_Tx>::type;
};

template<>
struct fn_any<> {
    using type = false_type;
};

} // namespace detail

///////////////////////////////////////////////////////////////////////////////
/**
 * enable_if
 */
template<bool _Tbool, typename _Ty = void> using enable_if = typename detail::fn_enable_if<_Tbool, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * truth_type
 */
template<typename _Tx> using truth_type = typename detail::fn_truth_type<_Tx>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * and
 */
template<typename _Tx, typename _Ty> using and = typename detail::fn_and<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * or
 */
template<typename _Tx, typename _Ty> using or = typename detail::fn_or<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * not
 */
template<typename _Tx> using not = typename detail::fn_not<_Tx>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * all
 */
template<typename... _Targs> using all = typename detail::fn_all<_Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * any
 */
template<typename... _Targs> using any = typename detail::fn_any<_Targs...>::type;

} // namespace mpl

#endif _mpl_logical_h_
