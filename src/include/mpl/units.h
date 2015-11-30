#ifndef _mpl_units_h_
#define _mpl_units_h_

#include "mpl/functional.h"
#include "mpl/logical.h"
#include "mpl/set.h"

namespace mpl {
namespace units {

////////////////////////////////////////////////////////////////////////////////
/**
 * dimension
 */
struct dimension {
    struct length;      //!< Length
    struct mass;        //!< Mass
    struct time;        //!< Time
    struct current;     //!< Electric current
    struct temperature; //!< Absolute temperature
    struct amount;      //!< Amount of substance
    struct intensity;   //!< Luminous intensity
};

namespace detail {

////////////////////////////////////////////////////////////////////////////////
//! The unit metatype is a list of unitbase metatypes.
template<typename _Tbase, int _Npower = 1> struct unitbase {
    using base = _Tbase;
    static const int power = _Npower;
};

template<int _Nx> struct fn_raise {
    template<typename _Ty> struct _func;

    template<typename _Tbase, int _Npower>
    struct _func<unitbase<_Tbase, _Npower>> {
        using type = unitbase<_Tbase, _Npower* _Nx>;
    };

    template<typename _Ty> using func = typename _func<_Ty>::type;
};

////////////////////////////////////////////////////////////////////////////////
//!
template<typename _Tx, typename _Ty> struct fn_is_same_base {
    using type = false_type;
};

template<typename _Tbase, int _Nx, int _Ny>
struct fn_is_same_base<unitbase<_Tbase, _Nx>, unitbase<_Tbase, _Ny>> {
    using type = true_type;
};

template<typename _Tx, typename _Ty> using is_same_base = typename fn_is_same_base<_Tx, _Ty>::type;

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `is_same` metafunction
template<typename _Tx, typename _Ty, typename = void> struct fn_is_same_iter {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct fn_is_same_iter<_Tx, _Ty, enable_if<contains<_Tx, car<_Ty>>::value>> {
    using type = typename fn_is_same_iter<_Tx, cdr<_Ty>>::type;
};

template<typename _Tx>
struct fn_is_same_iter<_Tx, nil> {
    using type = true_type;
};

template<typename _Tx, typename _Ty>
using fn_is_same_iter_t = typename fn_is_same_iter<_Tx, _Ty>::type;

template<typename _Tx, typename _Ty, typename = void, typename = void> struct fn_is_same {
    using type = false_type;
};

template<typename _Tx, typename _Ty>
struct fn_is_same<_Tx, _Ty,
        enable_if<fn_is_same_iter_t<_Tx, _Ty>::value>,
        enable_if<fn_is_same_iter_t<_Ty, _Tx>::value>> {
    using type = true_type;
};

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `is_unit` metafunction
template<typename _Tx> struct fn_is_unit {
    using type = false_type;
};

template<typename _Tx, int _Nx, typename _Ty>
struct fn_is_unit<cons<unitbase<_Tx, _Nx>, _Ty>> {
    using type = typename fn_is_unit<_Ty>::type;
};

template<>
struct fn_is_unit<nil> {
    using type = true_type;
};

////////////////////////////////////////////////////////////////////////////////
//! Append a unitbase type onto a unit type and combine appropriately.
template<typename _Tx, typename _Ty, typename = void> struct fn_append {
    using type = cons<car<_Tx>, typename fn_append<cdr<_Tx>, _Ty>::type>;
};

template<typename _Tx, typename _Ty>
struct fn_append < _Tx, _Ty, enable_if < !contains<_Tx, _Ty, is_same_base>::value >> {
    using type = typename append<_Tx, _Ty>;
};

template<typename _Tbase, typename _Tlist, int _Nx, int _Ny>
struct fn_append<cons<unitbase<_Tbase, _Nx>, _Tlist>, unitbase<_Tbase, _Ny>> {
    using type = cons < unitbase < _Tbase, _Nx + _Ny >, _Tlist >;
};

////////////////////////////////////////////////////////////////////////////////
//! Combine a list of unit and unitbase types into a single unit type.
template<typename... _Targs> struct fn_combine_iter;

template<typename _Tx, typename _Ty, typename _Tz>
struct fn_combine_iter<_Tx, _Ty, _Tz> {
    using next = typename fn_append<_Tz, _Tx>::type;
    using type = typename fn_combine_iter<car<_Ty>, cdr<_Ty>, next>::type;
};

template<typename _Tx, typename _Tz>
struct fn_combine_iter<_Tx, nil, _Tz> {
    using type = typename fn_append<_Tz, _Tx>::type;
};

template<typename _Tx> struct fn_combine {
    using type = typename fn_combine_iter<car<_Tx>, cdr<_Tx>, nil>::type;
};

template<>
struct fn_combine<nil> {
    using type = nil;
};

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `unit` metaconstructor
template<typename _Tunit> struct fn_unit {
    using type = list<unitbase<_Tunit, 1>>;
};

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `product` metafunction
template<typename... _Targs> struct fn_product {
    using type = typename fn_combine<extend<_Targs...>>::type;
};

////////////////////////////////////////////////////////////////////////////////
// Implementation of `power` metafunction
template<typename _Tx, int _Ny> struct fn_power {
    using type = map<typename fn_raise<_Ny>::func, _Tx>;
};

} // namespace detail

////////////////////////////////////////////////////////////////////////////////
/**
 * product
 *
 * Metafunction which takes two unit metatypes and evaluates to their product.
 */
template<typename... _Targs> using product = typename detail::fn_product<_Targs...>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * quotient
 *
 * Metafunction which takes two unit metatypes and evaluates to their quotient.
 */
template<typename _Tx, typename _Ty> using quotient = typename detail::fn_product < _Tx, typename detail::fn_power < _Ty, -1 >::type >::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * power
 *
 * Metafunction which takes a unit metatype and evaluates to the unit raised
 * to the given power.
 */
template<typename _Tx, int _Ny> using power = typename detail::fn_power<_Tx, _Ny>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * reciprocal
 *
 * Metafunction which evaluates to the reciprocal of the given unit metatype.
 */
template<typename _Tx> using reciprocal = typename detail::fn_power < _Tx, -1 >::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * is_same
 *
 * Metafunction for determining whether two unit types are the same. Evaluates
 * to `true_type` if _Tx and _Ty represent the same dimensional units, otherwise
 * evaluates to `false_type`.
 */
template<typename _Tx, typename _Ty> using is_same = typename detail::fn_is_same<_Tx, _Ty>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * is_unit
 *
 * Metafunction for determining whether a type is a unit type.
 */
template<typename _Tx> using is_unit = typename detail::fn_is_unit<_Tx>::type;

////////////////////////////////////////////////////////////////////////////////
/**
 * unit
 *
 * Metatype for tracking dimensional units.
 */
template<typename _Tunit> using unit = typename detail::fn_unit<_Tunit>::type;

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

    //! Default construction
    value() {}

    //! Explicit construction from type
    explicit value(_Tx const& v)
        : _value(v) {}

    //! Explicit cast to type
    explicit operator _Tx() const {
        return _value;
    }

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
        return value<_Tx, product<_Ty, _Tz>>(_value * (_Tx)a);
    }

    //! Division
    template<typename _Tz>
    value<_Tx, quotient<_Ty, _Tz>> operator/(value<_Tx, _Tz> const& a) const {
        return value<_Tx, quotient<_Ty, _Tz>>(_value * (_Tx)a);
    }

    //! Division to scalar
    _Tx operator/(value<_Tx, _Ty> const& a) const {
        return _value / (_Tx)a;
    }
};

namespace si {

using seconds = unit<dimension::time>;
using amperes = unit<dimension::current>;
using kelvin = unit<dimension::temperature>;
using moles = unit<dimension::amount>;
using candelas = unit<dimension::intensity>;

namespace mks {

using meters = unit<dimension::length>;
using kilograms = unit<dimension::mass>;

using newtons = quotient<product<kilograms, meters>, power<seconds, 2>>;
using pascals = quotient<newtons, power<meters, 2>>;
using joules = product<newtons, meters>;
using watts = quotient<joules, seconds>;
using coulombs = product<seconds, amperes>;
using volts = quotient<watts, amperes>;
using farads = quotient<coulombs, volts>;
using ohms = quotient<volts, amperes>;
using siemens = reciprocal<ohms>;
using webers = quotient<joules, amperes>;
using teslas = quotient<product<volts, seconds>, power<meters, 2>>;
using henries = quotient<product<volts, seconds>, amperes>;

} // namespace mks

namespace cgs {

using centimeters = unit<dimension::length>;
using grams = unit<dimension::mass>;

} // namespace cgs

using namespace mks;

} // namespace si

} // namespace units

namespace detail {

////////////////////////////////////////////////////////////////////////////////
//! Specialization for `is_same`
template<typename _Tx, typename _Ty>
struct fn_is_same<_Tx, _Ty, enable_if<units::is_unit<_Tx>::value && units::is_unit<_Ty>::value>> {
    using type = typename units::detail::fn_is_same<_Tx, _Ty>::type;
};

} // namespace detail

} // namespace mpl

#endif _mpl_units_h_
