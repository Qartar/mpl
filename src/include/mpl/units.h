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
    template<typename _Ty> struct func;

    template<typename _Tbase, int _Npower>
    struct func<unitbase<_Tbase, _Npower>> {
        using type = unitbase<_Tbase, _Npower* _Nx>;
    };
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
//! Append a unitbase type onto a unit type and combine appropriately.
template<typename _Tx, typename _Ty, typename = void> struct fn_append;

template<typename _Tx, typename _Ty>
struct fn_append < _Tx, _Ty, enable_if < !contains<_Tx, _Ty, is_same_base>::value >> {
    using type = typename append<_Tx, _Ty>;
};

template<typename _Tx, typename _Ty>
struct fn_append<_Tx, _Ty, enable_if<contains<_Tx, _Ty, is_same_base>::value>> {
    using type = cons<car<_Tx>, typename fn_append<cdr<_Tx>, _Ty>::type>;
};

template<typename _Tbase, typename _Tlist, int _Nx, int _Ny>
struct fn_append<cons<unitbase<_Tbase, _Nx>, _Tlist>, unitbase<_Tbase, _Ny>> {
    using type = cons < unitbase < _Tbase, _Nx + _Ny >, _Tlist >;
};

////////////////////////////////////////////////////////////////////////////////
//! Extend a list of unit and unitbase types into a list of only unitbase types.
template<typename... _Targs> struct fn_extend_iter;

//!
template<typename _Tx, typename _Ty, typename _Tz>
struct fn_extend_iter<cons<_Tx, _Ty>, _Tz> {
    using type = typename fn_extend_iter<_Tx, _Ty, _Tz>::type;
};

//!
template<typename _Tz>
struct fn_extend_iter<nil, _Tz> {
    using type = _Tz;
};

//! Extend a unit type
template<typename _Tx, typename _Tlist, typename _Ty, typename _Tz>
struct fn_extend_iter<cons<cons<_Tx, _Tlist>, _Ty>, _Tz> {
    using type = typename fn_extend_iter<_Tx, extend<_Tlist, _Ty>, _Tz>::type;
};

//! Extend a unitbase type
template<typename _Tx, int _Nx, typename _Ty, typename _Tz>
struct fn_extend_iter<unitbase<_Tx, _Nx>, _Ty, _Tz> {
    using unit = unitbase<_Tx, _Nx>;
    using type = typename fn_extend_iter<_Ty, append<_Tz, unit>>::type;
};

//! Extend a fundamental unit type
template<typename _Tx, typename _Ty, typename _Tz>
struct fn_extend_iter<_Tx, _Ty, _Tz> {
    using unit = unitbase<_Tx>;
    using type = typename fn_extend_iter<_Ty, append<_Tz, unit>>::type;
};

template<typename _Tx> struct fn_extend {
    using type = typename fn_extend_iter<car<_Tx>, cdr<_Tx>, nil>::type;
};

template<> struct fn_extend<nil> {
    using type = nil;
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
template<typename... _Tunits> struct fn_unit {
    using type = typename fn_combine<typename fn_extend<list<_Tunits...>>::type>::type;
};

////////////////////////////////////////////////////////////////////////////////
//! Implementation of `product` metafunction
template<typename _Tx, typename _Ty> struct fn_product {
    using type = typename fn_combine<list<_Tx, _Ty>>::type;
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
template<typename _Tx, typename _Ty> using product = typename detail::fn_product<_Tx, _Ty>::type;

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
 * unit
 *
 * Metatype for tracking dimensional units.
 */
template<typename... _Tunits> using unit = typename detail::fn_unit<_Tunits...>::type;

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

namespace si {

using seconds = unit<dimension::time>;
using amperes = unit<dimension::current>;
using kelvin = unit<dimension::temperature>;
using moles = unit<dimension::amount>;
using candelas = unit<dimension::intensity>;

namespace mks {

using meters = unit<dimension::length>;
using kilograms = unit<dimension::mass>;

using newtons = unit<quotient<product<kilograms, meters>, power<seconds, 2>>>;
using pascals = unit<quotient<newtons, power<meters, 2>>>;
using joules = unit<newtons, meters>;
using watts = unit<quotient<joules, seconds>>;
using coulombs = unit<seconds, amperes>;
using volts = unit<quotient<watts, amperes>>;
using farads = unit<quotient<coulombs, volts>>;
using ohms = unit<quotient<volts, amperes>>;
using siemens = unit<reciprocal<ohms>>;
using webers = unit<quotient<joules, amperes>>;
using teslas = unit<quotient<product<volts, seconds>, power<meters, 2>>>;
using henries = unit<quotient<product<volts, seconds>, amperes>>;

} // namespace mks

namespace cgs {

using centimeters = unit<dimension::length>;
using grams = unit<dimension::mass>;

} // namespace cgs

using namespace mks;

} // namespace si

} // namespace units
} // namespace mpl

#endif _mpl_units_h_
