#ifndef _mpl_units_h_
#define _mpl_units_h_

namespace mpl {
namespace units {

namespace detail {

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `product` metafunction
template<typename _Tx, typename _Ty> struct fn_product {
    using type = void;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation of `quotient` metafunction
template<typename _Tx, typename _Ty> struct fn_quotient {
    using type = void;
};

} // namespace detail

////////////////////////////////////////////////////////////////////////////////
/**
 * product
 *
 * Metafunction which takes two unit metatypes and evaluates to their product.
 */
template<typename _Tx, typename _Ty> using product = typename detail::fn_product<_Tx, _Ty>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * quotient
 *
 * Metafunction which takes two unit metatypes and evaluates to their quotient.
 */
template<typename _Tx, typename _Ty> using quotient = typename detail::fn_quotient<_Tx, _Ty>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * value
 *
 * Strongly-typed container for a value with units.
 */
template<typename _Tx, typename _Ty>
class value {

    _Tx     _value;

  public:

    value() {}

    //! Explicit construction from type
    explicit value(_Tx const& v)
        : _value(v) {}

    //! Addition
    value<_Tx, _Ty> operator+(value<_Tx, _Ty> const& a) const {
        return value<_Tx, _Ty>(_value + a._value);
    }

    //! Subtraction
    value<_Tx, _Ty> operator-(value<_Tx, _Ty> const& a) const {
        return value<_Tx, _Ty>(_value - a._value);
    }

    //! Scalar multiplication
    value<_Tx, _Ty> operator*(_Tx const& s) const {
        return value<_Tx, _Ty>(_value * s);
    }

    //! Scalar division
    value<_Tx, _Ty> operator/(_Tx const& s) const {
        return value<_Tx, _Ty>(_value / s);
    }

    //! Addition
    value<_Tx, _Ty>& operator+=(value<_Tx, _Ty> const& a) {
        _value += a._value;
        return *this;
    }

    //! Subtraction
    value<_Tx, _Ty>& operator-=(value<_Tx, _Ty> const& a) {
        _value -= a._value;
        return *this;
    }

    //! Scalar multiplication
    value<_Tx, _Ty> operator*=(_Tx const& s) {
        _value *= s;
        return *this;
    }

    //! Scalar division
    value<_Tx, _Ty> operator/=(_Tx const& s) {
        _value /= s;
        return *this;
    }

    //! Negation
    value<_Tx, _Ty> operator-() const {
        return value<_Tx, _Ty>(-_value);
    }

    //! Multiplication
    template<typename _Tz>
    value<_Tx, product<_Ty, _Tz>> operator*(value<_Tx, _Tz> const& a) const {
        return value<_Tx, product<_Ty, _Tz>>(_value * a._value);
    }

    //! Division
    template<typename _Tz>
    value<_Tx, quotient<_Ty, _Tz>> operator/(value<_Tx, _Tz> const& a) const {
        return value<_Tx, quotient<_Ty, _Tz>>(_value * a._value);
    }

    //! Division to scalar
    _Tx operator/(value<_Tx, _Ty> const& a) const {
        return _value / a._value;
    }
};

} // namespace units
} // namespace mpl

#endif _mpl_units_h_
