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
template<bool _Bx, typename _Ty = void> struct fn_enable_if;

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

template<typename... _Targs>
struct fn_all<false_type, _Targs...> {
    using type = false_type;
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

template<typename... _Targs>
struct fn_any<true_type, _Targs...> {
    using type = true_type;
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
 *
 * Helper function for SFINAE resolution. Evaluates to _Ty (default: void) if
 * the boolean expression is true, otherwise does not evaluate, causing a
 * substitution failure which prevents use of the template specialization.
 */
template<bool _Bx, typename _Ty = void> using enable_if = typename detail::fn_enable_if<_Bx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * truth_type
 *
 * Helper function for evaluating the truth type of a metatype. Evaluates to
 * true_type if _Tx::value is true, evaluates to false_type if _Tx::value is
 * false.
 */
template<typename _Tx> using truth_type = typename detail::fn_truth_type<_Tx>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * not
 *
 * Evaluates to the opposite truth type of _Tx.
 */
template<typename _Tx> using not = typename detail::fn_not<_Tx>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * and
 *
 *  * | 0 1  Evaluates to true_type if both _Tx and _Ty evaluate to true_type.
 *  --+----
 *  0 | 0 0  Both arguments must evaluate to either true_type or false_type.
 *  1 | 0 1
 */
template<typename _Tx, typename _Ty> using and = typename detail::fn_and<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * or
 *
 *  * | 0 1  Evaluates to true_type if either _Tx or _Ty evaluate to true_type.
 *  --+----
 *  0 | 0 1  Both arguments must evaluate to either true_type or false_type.
 *  1 | 1 1
 */
template<typename _Tx, typename _Ty> using or = typename detail::fn_or<_Tx, _Ty>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * nand
 *
 *  * | 0 1  Evaluates to true_type if either _Tx or _Ty evaluate to false_type.
 *  --+----
 *  0 | 1 1  Both arguments must evaluate to either true_type or false_type.
 *  1 | 1 0
 */
template<typename _Tx, typename _Ty> using nand = not<and<_Tx, _Ty>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * nor
 *
 *  * | 0 1  Evaluates to false_type if both _Tx or _Ty evaluate to false_type.
 *  --+----
 *  0 | 1 0  Both arguments must evaluate to either true_type or false_type.
 *  1 | 0 0
 */
template<typename _Tx, typename _Ty> using nor = not<or<_Tx, _Ty>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * xor
 *
 *  * | 0 1  Evaluates to true_type if either but not both _Tx or _Ty evaluate
 *  --+----  to true_type.
 *  0 | 0 1
 *  1 | 1 0  Both arguments must evaluate to either true_type or false_type.
 */
template<typename _Tx, typename _Ty> using xor = and <or<_Tx, _Ty>, nand<_Tx, _Ty>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * xnor
 *
 *  * | 0 1  Evaluates to true_type if _Tx and _Ty both evaluate to either
 *  --+----  true_type or false_type.
 *  0 | 1 0
 *  1 | 0 1  Both arguments must evaluate to either true_type or false_type.
 */
template<typename _Tx, typename _Ty> using xnor = or <nor<_Tx, _Ty>, and<_Tx, _Ty>>;

///////////////////////////////////////////////////////////////////////////////
/**
 * all
 *
 * Evaluates to true_type if all type arguments evaluate to true_type. An empty
 * argument list evaluates to false_type.
 *
 * All arguments must evaluate to either true_type or false_type.
 */
template<typename... _Targs> using all = typename detail::fn_all<_Targs...>::type;

///////////////////////////////////////////////////////////////////////////////
/**
 * any
 *
 * Evaluates to true_type if any type arguments evaluate to true_type. An empty
 * argument list evaluates to false_type.
 *
 * All arguments must evaluate to either true_type or false_type.
 */
template<typename... _Targs> using any = typename detail::fn_any<_Targs...>::type;

} // namespace mpl

#endif _mpl_logical_h_
