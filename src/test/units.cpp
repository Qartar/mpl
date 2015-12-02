#include "mpl_test.h"

#include "mpl/units.h"
#include "mpl/list.h"

namespace {

////////////////////////////////////////////////////////////////////////////////
namespace is_same {

//------------------------------------------------------------------------------
namespace A {

using _A = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::meters>;
using _B = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::seconds>;
using _C = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::newtons>;
using _D = mpl::units::is_same<mpl::units::si::newtons, mpl::units::si::newtons>;

ASSERT_SAME(mpl::true_type, _A);
ASSERT_SAME(mpl::false_type, _B);
ASSERT_SAME(mpl::false_type, _C);
ASSERT_SAME(mpl::true_type, _D);

} // namespace A

//------------------------------------------------------------------------------
namespace B {

using namespace mpl::units;
using namespace mpl::units::si;

using _pascals = product<kilograms, power<meters, -1>, power<seconds, -2>>;
using _joules = product<kilograms, power<meters, 2>, power<seconds, -2>>;
using _watts = product<kilograms, power<meters, 2>, power<seconds, -3>>;
using _volts = product<kilograms, power<meters, 2>, power<seconds, -3>, power<amperes, -1>>;
using _farads = product<power<kilograms, -1>, power<meters, -2>, power<seconds, 4>, power<amperes, 2>>;
using _ohms = product<kilograms, power<meters, 2>, power<seconds, -3>, power<amperes, -2>>;
using _siemens = product<power<kilograms, -1>, power<meters, -2>, power<seconds, 3>, power<amperes, 2>>;
using _webers = product<kilograms, power<meters, 2>, power<seconds, -2>, power<amperes, -1>>;
using _teslas = product<kilograms, power<seconds, -2>, power<amperes, -1>>;
using _henries = product<kilograms, power<meters, 2>, power<seconds, -2>, power<amperes, -2>>;

ASSERT_SAME(pascals, _pascals);
ASSERT_SAME(joules, _joules);
ASSERT_SAME(watts, _watts);
ASSERT_SAME(volts, _volts);
//ASSERT_SAME(farads, _farads); // FIXME
ASSERT_SAME(ohms, _ohms);
ASSERT_SAME(siemens, _siemens);
ASSERT_SAME(webers, _webers);
ASSERT_SAME(teslas, _teslas);
ASSERT_SAME(henries, _henries);

} // namespace B

//------------------------------------------------------------------------------
namespace C {

using namespace mpl::units::si;

//! Helper metafunction for retrieving a given base unit.
template<typename _Tx> struct dim {
    template<typename _Ty> struct fn_pred {
        using type = mpl::false_type;
    };

    template<int _Ny> struct fn_pred<mpl::units::detail::unitbase<_Tx, _Ny>> {
        using type = mpl::true_type;
    };

    template<typename _Ty> using pred = typename fn_pred<_Ty>::type;
};

template<typename _Tx> using length = mpl::find<_Tx, dim<mpl::units::dimension::length>::pred>;
template<typename _Tx> using mass = mpl::find<_Tx, dim<mpl::units::dimension::mass>::pred>;
template<typename _Tx> using time = mpl::find<_Tx, dim<mpl::units::dimension::time>::pred>;
template<typename _Tx> using current = mpl::find<_Tx, dim<mpl::units::dimension::current>::pred>;
template<typename _Tx> using amount = mpl::find<_Tx, dim<mpl::units::dimension::amount>::pred>;
template<typename _Tx> using intensity = mpl::find<_Tx, dim<mpl::units::dimension::intensity>::pred>;

ASSERT_SAME(mpl::nil, mass<hertz>);
ASSERT_SAME(mpl::nil, length<hertz>);
ASSERT_EQUAL(-1, time<hertz>::power);
ASSERT_SAME(mpl::nil, current<hertz>);
ASSERT_SAME(mpl::nil, amount<hertz>);
ASSERT_SAME(mpl::nil, intensity<hertz>);

ASSERT_SAME(mpl::nil, mass<radians>);
ASSERT_SAME(mpl::nil, length<radians>);
ASSERT_SAME(mpl::nil, time<radians>);
ASSERT_SAME(mpl::nil, current<radians>);
ASSERT_SAME(mpl::nil, amount<radians>);
ASSERT_SAME(mpl::nil, intensity<radians>);

ASSERT_SAME(mpl::nil, mass<steradians>);
ASSERT_SAME(mpl::nil, length<steradians>);
ASSERT_SAME(mpl::nil, time<steradians>);
ASSERT_SAME(mpl::nil, current<steradians>);
ASSERT_SAME(mpl::nil, amount<steradians>);
ASSERT_SAME(mpl::nil, intensity<steradians>);

ASSERT_EQUAL(1, mass<newtons>::power);
ASSERT_EQUAL(1, length<newtons>::power);
ASSERT_EQUAL(-2, time<newtons>::power);
ASSERT_SAME(mpl::nil, current<newtons>);
ASSERT_SAME(mpl::nil, amount<newtons>);
ASSERT_SAME(mpl::nil, intensity<newtons>);

ASSERT_EQUAL(1, mass<pascals>::power);
ASSERT_EQUAL(-1, length<pascals>::power);
ASSERT_EQUAL(-2, time<pascals>::power);
ASSERT_SAME(mpl::nil, current<pascals>);
ASSERT_SAME(mpl::nil, amount<pascals>);
ASSERT_SAME(mpl::nil, intensity<pascals>);

ASSERT_EQUAL(1, mass<joules>::power);
ASSERT_EQUAL(2, length<joules>::power);
ASSERT_EQUAL(-2, time<joules>::power);
ASSERT_SAME(mpl::nil, current<joules>);
ASSERT_SAME(mpl::nil, amount<joules>);
ASSERT_SAME(mpl::nil, intensity<joules>);

ASSERT_EQUAL(1, mass<watts>::power);
ASSERT_EQUAL(2, length<watts>::power);
ASSERT_EQUAL(-3, time<watts>::power);
ASSERT_SAME(mpl::nil, current<watts>);
ASSERT_SAME(mpl::nil, amount<watts>);
ASSERT_SAME(mpl::nil, intensity<watts>);

ASSERT_SAME(mpl::nil, mass<coulombs>);
ASSERT_SAME(mpl::nil, length<coulombs>);
ASSERT_EQUAL(1, time<coulombs>::power);
ASSERT_EQUAL(1, current<coulombs>::power);
ASSERT_SAME(mpl::nil, amount<coulombs>);
ASSERT_SAME(mpl::nil, intensity<coulombs>);

ASSERT_EQUAL(1, mass<volts>::power);
ASSERT_EQUAL(2, length<volts>::power);
ASSERT_EQUAL(-3, time<volts>::power);
ASSERT_EQUAL(-1, current<volts>::power);
ASSERT_SAME(mpl::nil, amount<volts>);
ASSERT_SAME(mpl::nil, intensity<volts>);

ASSERT_EQUAL(-1, mass<farads>::power);
ASSERT_EQUAL(-2, length<farads>::power);
ASSERT_EQUAL(4, time<farads>::power);
ASSERT_EQUAL(2, current<farads>::power);
ASSERT_SAME(mpl::nil, amount<farads>);
ASSERT_SAME(mpl::nil, intensity<farads>);

ASSERT_EQUAL(1, mass<ohms>::power);
ASSERT_EQUAL(2, length<ohms>::power);
ASSERT_EQUAL(-3, time<ohms>::power);
ASSERT_EQUAL(-2, current<ohms>::power);
ASSERT_SAME(mpl::nil, amount<ohms>);
ASSERT_SAME(mpl::nil, intensity<ohms>);

ASSERT_EQUAL(-1, mass<siemens>::power);
ASSERT_EQUAL(-2, length<siemens>::power);
ASSERT_EQUAL(3, time<siemens>::power);
ASSERT_EQUAL(2, current<siemens>::power);
ASSERT_SAME(mpl::nil, amount<siemens>);
ASSERT_SAME(mpl::nil, intensity<siemens>);

ASSERT_EQUAL(1, mass<webers>::power);
ASSERT_EQUAL(2, length<webers>::power);
ASSERT_EQUAL(-2, time<webers>::power);
ASSERT_EQUAL(-1, current<webers>::power);
ASSERT_SAME(mpl::nil, amount<webers>);
ASSERT_SAME(mpl::nil, intensity<webers>);

ASSERT_EQUAL(1, mass<teslas>::power);
ASSERT_SAME(mpl::nil, length<teslas>);
ASSERT_EQUAL(-2, time<teslas>::power);
ASSERT_EQUAL(-1, current<teslas>::power);
ASSERT_SAME(mpl::nil, amount<teslas>);
ASSERT_SAME(mpl::nil, intensity<teslas>);

ASSERT_EQUAL(1, mass<henries>::power);
ASSERT_EQUAL(2, length<henries>::power);
ASSERT_EQUAL(-2, time<henries>::power);
ASSERT_EQUAL(-2, current<henries>::power);
ASSERT_SAME(mpl::nil, amount<henries>);
ASSERT_SAME(mpl::nil, intensity<henries>);

ASSERT_SAME(mpl::nil, mass<lumens>);
ASSERT_SAME(mpl::nil, length<lumens>);
ASSERT_SAME(mpl::nil, time<lumens>);
ASSERT_SAME(mpl::nil, current<lumens>);
ASSERT_SAME(mpl::nil, amount<lumens>);
ASSERT_EQUAL(1, intensity<lumens>::power);

ASSERT_SAME(mpl::nil, mass<lux>);
ASSERT_EQUAL(-2, length<lux>::power);
ASSERT_SAME(mpl::nil, time<lux>);
ASSERT_SAME(mpl::nil, current<lux>);
ASSERT_SAME(mpl::nil, amount<lux>);
ASSERT_EQUAL(1, intensity<lux>::power);

ASSERT_SAME(mpl::nil, mass<becquerels>);
ASSERT_SAME(mpl::nil, length<becquerels>);
ASSERT_EQUAL(-1, time<becquerels>::power);
ASSERT_SAME(mpl::nil, current<becquerels>);
ASSERT_SAME(mpl::nil, amount<becquerels>);
ASSERT_SAME(mpl::nil, intensity<becquerels>);

ASSERT_SAME(mpl::nil, mass<grays>);
ASSERT_EQUAL(2, length<grays>::power);
ASSERT_EQUAL(-2, time<grays>::power);
ASSERT_SAME(mpl::nil, current<grays>);
ASSERT_SAME(mpl::nil, amount<grays>);
ASSERT_SAME(mpl::nil, intensity<grays>);

ASSERT_SAME(mpl::nil, mass<sieverts>);
ASSERT_EQUAL(2, length<sieverts>::power);
ASSERT_EQUAL(-2, time<sieverts>::power);
ASSERT_SAME(mpl::nil, current<sieverts>);
ASSERT_SAME(mpl::nil, amount<sieverts>);
ASSERT_SAME(mpl::nil, intensity<sieverts>);

ASSERT_SAME(mpl::nil, mass<katals>);
ASSERT_SAME(mpl::nil, length<katals>);
ASSERT_EQUAL(-1, time<katals>::power);
ASSERT_SAME(mpl::nil, current<katals>);
ASSERT_EQUAL(1, amount<katals>::power);
ASSERT_SAME(mpl::nil, intensity<katals>);

} // namespace C
} // namespace is_same

////////////////////////////////////////////////////////////////////////////////
namespace is_unit {

//------------------------------------------------------------------------------
namespace A {

template<typename T>
using is_unit = mpl::units::is_unit<T>;

ASSERT_SAME(mpl::false_type, is_unit<void>);
ASSERT_SAME(mpl::false_type, is_unit<mpl::units::dimension>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::unit<void>>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::si::meters>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::si::newtons>);

} // namespace A
} // namespace is_unit

////////////////////////////////////////////////////////////////////////////////
namespace value {

//------------------------------------------------------------------------------
namespace A {

using _A = mpl::units::value<int, mpl::nil>;

void _fA(_A x, _A y) {
    _A _a = x + y;
    _A _b = x - y;
    _A _c = x * 2;
    _A _d = x / 2;

    _A _e = x += y;
    _A _f = x -= y;
    _A _g = x *= 2;
    _A _h = x /= 2;

    _A _i = -x;
    int _j = x / y;
}

} // namespace A

//------------------------------------------------------------------------------
namespace B {

void _A(void) {
    auto a = mpl::units::value<double, mpl::units::si::newtons>(1.0);
    auto b = mpl::units::value<double, mpl::units::si::meters>(2.0);
    auto c = mpl::units::value<double, mpl::units::si::joules>(3.0);
    auto d = a * b;
    auto e = c / d;
    auto f = c + d;
    auto g = c - d;

    ASSERT_SAME(mpl::units::si::joules, decltype(d)::unit);
    ASSERT_SAME(mpl::units::si::joules, decltype(f)::unit);
    ASSERT_SAME(mpl::units::si::joules, decltype(g)::unit);

    ASSERT_SAME(double, decltype(d)::type);
    ASSERT_SAME(double, decltype(e));
    ASSERT_SAME(double, decltype(f)::type);
    ASSERT_SAME(double, decltype(g)::type);
}

void _B(void) {
    auto a = mpl::units::value<double, mpl::units::si::joules>(4.0);
    auto b = mpl::units::value<double, mpl::units::si::seconds>(5.0);
    auto c = mpl::units::value<double, mpl::units::si::watts>(6.0);
    auto d = a / b;
    auto e = c / d;
    auto f = c + d;
    auto g = c - d;

    ASSERT_SAME(mpl::units::si::watts, decltype(d)::unit);
    ASSERT_SAME(mpl::units::si::watts, decltype(f)::unit);
    ASSERT_SAME(mpl::units::si::watts, decltype(g)::unit);

    ASSERT_SAME(double, decltype(d)::type);
    ASSERT_SAME(double, decltype(e));
    ASSERT_SAME(double, decltype(f)::type);
    ASSERT_SAME(double, decltype(g)::type);
}

} // namespace B

//------------------------------------------------------------------------------
namespace C {

struct X {};
struct Y {};
struct Z {};
struct W {};

Z operator*(X const&, Y const&) { return Z{}; }
W operator/(X const&, Y const&) { return W{}; }

void _A(void) {
    auto x = X{};
    auto y = Y{};
    auto z = x * y;
    auto w = x / y;

    ASSERT_SAME(Z, decltype(z));
    ASSERT_SAME(W, decltype(w));
}

void _B(void) {
    auto x = mpl::units::value<X, mpl::units::si::newtons>{};
    auto y = mpl::units::value<Y, mpl::units::si::meters>{};
    auto z = x * y;

    ASSERT_SAME(Z, decltype(z)::type);
    ASSERT_SAME(mpl::units::si::joules, decltype(z)::unit);
}

void _C(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::si::seconds>{};
    auto w = x / y;

    ASSERT_SAME(W, decltype(w)::type);
    ASSERT_SAME(mpl::units::si::watts, decltype(w)::unit);
}

void _D(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::si::joules>{};
    auto w = x / y;

    ASSERT_SAME(W, decltype(w));
}

void _E(void) {
    auto x = mpl::units::value<int, mpl::units::si::joules>{};
    auto y = mpl::units::value<int, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};
    auto z = x / y;

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    ASSERT_SAME(decltype(z), int);
}

void _F(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};
    auto w = x / y;

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    ASSERT_SAME(W, decltype(w));
}

} // namespace C
} // namespace value

} // anonymous namespace
