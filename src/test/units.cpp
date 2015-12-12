#include "mpl_test.h"

#include <cstdint>

#include "mpl/units.h"
#include "mpl/list.h"

namespace {

////////////////////////////////////////////////////////////////////////////////
namespace is_same {

//------------------------------------------------------------------------------
namespace test_identity {

using _A = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::meters>;
using _B = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::seconds>;
using _C = mpl::units::is_same<mpl::units::si::meters, mpl::units::si::newtons>;
using _D = mpl::units::is_same<mpl::units::si::newtons, mpl::units::si::newtons>;

ASSERT_SAME(mpl::true_type, _A);
ASSERT_SAME(mpl::false_type, _B);
ASSERT_SAME(mpl::false_type, _C);
ASSERT_SAME(mpl::true_type, _D);

} // namespace test_identity

//------------------------------------------------------------------------------
namespace test_derived_identity {

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

#define ASSERT_SAME_UNIT(x, y)                                                  \
    using _B##x##y = mpl::is_same<x,y>;                                         \
    ASSERT_SAME(mpl::true_type, _B##x##y)

ASSERT_SAME_UNIT(pascals, _pascals);
ASSERT_SAME_UNIT(joules, _joules);
ASSERT_SAME_UNIT(watts, _watts);
ASSERT_SAME_UNIT(volts, _volts);
ASSERT_SAME_UNIT(farads, _farads);
ASSERT_SAME_UNIT(ohms, _ohms);
ASSERT_SAME_UNIT(siemens, _siemens);
ASSERT_SAME_UNIT(webers, _webers);
ASSERT_SAME_UNIT(teslas, _teslas);
ASSERT_SAME_UNIT(henries, _henries);

} // namespace test_derived_identity

//------------------------------------------------------------------------------
namespace test_derived_units {

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

} // namespace test_derived_units
} // namespace is_same

////////////////////////////////////////////////////////////////////////////////
namespace is_unit {

//------------------------------------------------------------------------------
namespace test_units {

template<typename T>
using is_unit = mpl::units::is_unit<T>;

ASSERT_SAME(mpl::false_type, is_unit<void>);
ASSERT_SAME(mpl::false_type, is_unit<mpl::units::dimension>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::unit<void>>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::si::meters>);
ASSERT_SAME(mpl::true_type, is_unit<mpl::units::si::newtons>);

} // namespace test_units
} // namespace is_unit

////////////////////////////////////////////////////////////////////////////////
namespace is_square {

using _A = mpl::units::si::meters;
using _B = mpl::units::si::sieverts;
using _C = mpl::units::product<mpl::units::si::kilograms, mpl::units::si::joules>;
using _D = mpl::units::power<mpl::units::si::meters, 2>;
using _E = mpl::units::power<mpl::units::si::teslas, 2>;
using _F = mpl::units::si::radians;

ASSERT_SAME(mpl::false_type, mpl::units::is_square<int>);
ASSERT_SAME(mpl::false_type, mpl::units::is_square<_A>);
ASSERT_SAME(mpl::true_type, mpl::units::is_square<_B>);
ASSERT_SAME(mpl::true_type, mpl::units::is_square<_C>);
ASSERT_SAME(mpl::true_type, mpl::units::is_square<_D>);
ASSERT_SAME(mpl::true_type, mpl::units::is_square<_E>);
ASSERT_SAME(mpl::true_type, mpl::units::is_square<_F>);

} // namespace is_square

////////////////////////////////////////////////////////////////////////////////
namespace is_cube {

using _A = mpl::units::si::meters;
using _B = mpl::units::si::sieverts;
using _C = mpl::units::product<mpl::units::si::pascals,
                               mpl::units::si::joules,
                               mpl::units::si::watts,
                               mpl::units::si::seconds>;
using _D = mpl::units::power<mpl::units::si::meters, 3>;
using _E = mpl::units::power<mpl::units::si::teslas, 3>;
using _F = mpl::units::si::radians;

ASSERT_SAME(mpl::false_type, mpl::units::is_cube<int>);
ASSERT_SAME(mpl::false_type, mpl::units::is_cube<_A>);
ASSERT_SAME(mpl::false_type, mpl::units::is_cube<_B>);
ASSERT_SAME(mpl::true_type, mpl::units::is_cube<_C>);
ASSERT_SAME(mpl::true_type, mpl::units::is_cube<_D>);
ASSERT_SAME(mpl::true_type, mpl::units::is_cube<_E>);
ASSERT_SAME(mpl::true_type, mpl::units::is_cube<_F>);

} // namespace is_cube

////////////////////////////////////////////////////////////////////////////////
namespace value {

//------------------------------------------------------------------------------
namespace test_no_conversion {

void test_operators(void) {
    auto x = mpl::units::value<int, mpl::units::si::meters>(1);
    auto y = mpl::units::value<int, mpl::units::si::meters>(2);

    ASSERT_SAME(decltype(x), decltype(y));

    auto a = x + y;
    auto b = x - y;
    auto c = x * 2;
    auto d = x / 2;

    auto e = x += y;
    auto f = x -= y;
    auto g = x *= 2;
    auto h = x /= 2;

    auto i = -x;
    auto j = x / y;

    ASSERT_SAME(decltype(x), decltype(a));
    ASSERT_SAME(decltype(x), decltype(b));
    ASSERT_SAME(decltype(x), decltype(c));
    ASSERT_SAME(decltype(x), decltype(d));

    ASSERT_SAME(decltype(x), decltype(e));
    ASSERT_SAME(decltype(x), decltype(f));
    ASSERT_SAME(decltype(x), decltype(g));
    ASSERT_SAME(decltype(x), decltype(h));

    ASSERT_SAME(decltype(x), decltype(i));
    ASSERT_SAME(decltype(x)::type, decltype(j));
}

void test_friend_operators(void) {
    auto a = mpl::units::value<int, mpl::units::si::meters>(1);

    auto b = 2 * a;
    auto c = 2 / a;

    ASSERT_SAME(decltype(a), decltype(b));
    ASSERT_SAME(decltype(a)::type, decltype(c)::type);
    ASSERT_SAME(mpl::units::reciprocal<typename decltype(a)::unit>, decltype(c)::unit);
}

void test_implicit_casts(void) {
    auto a = mpl::units::value<double, mpl::units::si::meters>(1.0);

    auto b = a * 2;
    auto c = a * 2.0f;

    ASSERT_SAME(decltype(a), decltype(b));
    ASSERT_SAME(decltype(a), decltype(c));

    auto d = a / 2;
    auto e = a / 2.0f;

    ASSERT_SAME(decltype(a), decltype(d));
    ASSERT_SAME(decltype(a), decltype(e));

    auto f = 2 * a;
    auto g = 2.0f * a;

    ASSERT_SAME(decltype(a), decltype(f));
    ASSERT_SAME(decltype(a), decltype(g));

    auto h = 2 / a;
    auto i = 2.0f / a;

    ASSERT_SAME(decltype(a)::type, decltype(h)::type);
    ASSERT_SAME(mpl::units::reciprocal<typename decltype(a)::unit>, decltype(h)::unit);

    ASSERT_SAME(decltype(a)::type, decltype(i)::type);
    ASSERT_SAME(mpl::units::reciprocal<typename decltype(a)::unit>, decltype(i)::unit);
}

void test_implicit_promotion_multiplication(void) {
    auto a = mpl::units::value<float, mpl::units::si::meters>(1.0f);
    auto b = mpl::units::value<int32_t, mpl::units::si::meters>(1);

    auto c = a * 2.0;
    auto d = b * 2.0;
    auto e = b * 2ll;

    ASSERT_SAME(double, decltype(c)::type);
    ASSERT_SAME(double, decltype(d)::type);
    ASSERT_SAME(int64_t, decltype(e)::type);

    auto f = 2.0 * a;
    auto g = 2.0 * b;
    auto h = 2ll * b;

    ASSERT_SAME(double, decltype(f)::type);
    ASSERT_SAME(double, decltype(g)::type);
    ASSERT_SAME(int64_t, decltype(h)::type);
}

void test_implicit_promotion_division(void) {
    auto a = mpl::units::value<float, mpl::units::si::meters>(1.0f);
    auto b = mpl::units::value<int32_t, mpl::units::si::meters>(1);

    auto c = a / 2.0;
    auto d = b / 2.0;
    auto e = b / 2ll;

    ASSERT_SAME(double, decltype(c)::type);
    ASSERT_SAME(double, decltype(d)::type);
    ASSERT_SAME(int64_t, decltype(e)::type);

    auto f = 2.0 / a;
    auto g = 2.0 / b;
    auto h = 2ll / b;

    ASSERT_SAME(double, decltype(f)::type);
    ASSERT_SAME(double, decltype(g)::type);
    ASSERT_SAME(int64_t, decltype(h)::type);
}

} // namespace test_no_conversion

//------------------------------------------------------------------------------
namespace test_conversion {

void test_units_multiplication(void) {
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

void test_units_division(void) {
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

} // namespace test_conversion

//------------------------------------------------------------------------------
namespace test_base_conversion {

struct X {};
struct Y {};
struct Z {};
struct W {};

Z operator*(X const&, Y const&) { return Z{}; }
W operator/(X const&, Y const&) { return W{}; }

void internal_test_operators(void) {
    auto x = X{};
    auto y = Y{};
    auto z = x * y;
    auto w = x / y;

    ASSERT_SAME(Z, decltype(z));
    ASSERT_SAME(W, decltype(w));
}

void test_multiplication_with_base_conversion(void) {
    auto x = mpl::units::value<X, mpl::units::si::newtons>{};
    auto y = mpl::units::value<Y, mpl::units::si::meters>{};
    auto z = x * y;

    ASSERT_SAME(Z, decltype(z)::type);
    ASSERT_SAME(mpl::units::si::joules, decltype(z)::unit);
}

void test_division_with_base_conversion(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::si::seconds>{};
    auto w = x / y;

    ASSERT_SAME(W, decltype(w)::type);
    ASSERT_SAME(mpl::units::si::watts, decltype(w)::unit);
}

void test_division_with_base_conversion_to_dimensionless(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::si::joules>{};
    auto w = x / y;

    ASSERT_SAME(W, decltype(w));
}

void test_division_with_equivalent_units(void) {
    auto x = mpl::units::value<int, mpl::units::si::joules>{};
    auto y = mpl::units::value<int, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};
    auto z = x / y;

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    ASSERT_SAME(int, decltype(z));
}

void test_division_with_base_conversion_and_equivalent_units(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};
    auto w = x / y;

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    ASSERT_SAME(W, decltype(w));
}

void test_implicit_conversion_with_equivalent_units(void) {
    auto x = mpl::units::value<int, mpl::units::si::joules>{};
    auto y = mpl::units::value<int, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};
    decltype(x) z = y;

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    ASSERT_SAME(decltype(x), decltype(z));
}

} // namespace test_base_conversion

//------------------------------------------------------------------------------
namespace relational {

struct X {};
struct Y {};
struct Z {};
struct W {};

bool operator==(X const&, Y const&) { return true; }
bool operator!=(X const&, Y const&) { return true; }
bool operator< (X const&, Y const&) { return true; }
bool operator<=(X const&, Y const&) { return true; }
bool operator> (X const&, Y const&) { return true; }
bool operator>=(X const&, Y const&) { return true; }

X operator==(Z const&, W const&) { return X{}; }
X operator!=(Z const&, W const&) { return X{}; }
X operator< (Z const&, W const&) { return X{}; }
X operator<=(Z const&, W const&) { return X{}; }
X operator> (Z const&, W const&) { return X{}; }
X operator>=(Z const&, W const&) { return X{}; }

void test_same_units(void) {
    auto x = mpl::units::value<int, mpl::units::si::meters>{};
    auto y = mpl::units::value<int, mpl::units::si::meters>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::true_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(bool, decltype(eq));
    ASSERT_SAME(bool, decltype(ne));
    ASSERT_SAME(bool, decltype(lt));
    ASSERT_SAME(bool, decltype(le));
    ASSERT_SAME(bool, decltype(gt));
    ASSERT_SAME(bool, decltype(ge));
}

void test_equivalent_units(void) {
    auto x = mpl::units::value<int, mpl::units::si::joules>{};
    auto y = mpl::units::value<int, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(bool, decltype(eq));
    ASSERT_SAME(bool, decltype(ne));
    ASSERT_SAME(bool, decltype(lt));
    ASSERT_SAME(bool, decltype(le));
    ASSERT_SAME(bool, decltype(gt));
    ASSERT_SAME(bool, decltype(ge));
}

void test_base_types_with_same_units(void) {
    auto x = mpl::units::value<X, mpl::units::si::meters>{};
    auto y = mpl::units::value<Y, mpl::units::si::meters>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::true_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(bool, decltype(eq));
    ASSERT_SAME(bool, decltype(ne));
    ASSERT_SAME(bool, decltype(lt));
    ASSERT_SAME(bool, decltype(le));
    ASSERT_SAME(bool, decltype(gt));
    ASSERT_SAME(bool, decltype(ge));
}

void test_base_types_with_equivalent_units(void) {
    auto x = mpl::units::value<X, mpl::units::si::joules>{};
    auto y = mpl::units::value<Y, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(bool, decltype(eq));
    ASSERT_SAME(bool, decltype(ne));
    ASSERT_SAME(bool, decltype(lt));
    ASSERT_SAME(bool, decltype(le));
    ASSERT_SAME(bool, decltype(gt));
    ASSERT_SAME(bool, decltype(ge));
}

void test_return_types_with_same_units(void) {
    auto x = mpl::units::value<Z, mpl::units::si::meters>{};
    auto y = mpl::units::value<W, mpl::units::si::meters>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::true_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(X, decltype(eq));
    ASSERT_SAME(X, decltype(ne));
    ASSERT_SAME(X, decltype(lt));
    ASSERT_SAME(X, decltype(le));
    ASSERT_SAME(X, decltype(gt));
    ASSERT_SAME(X, decltype(ge));
}

void test_return_types_with_equivalent_units(void) {
    auto x = mpl::units::value<Z, mpl::units::si::joules>{};
    auto y = mpl::units::value<W, mpl::units::product<mpl::units::si::meters, mpl::units::si::newtons>>{};

    using a = std::is_same<decltype(x)::unit, decltype(y)::unit>::type;
    using b = mpl::is_same<decltype(x)::unit, decltype(y)::unit>;
    ASSERT_SAME(std::false_type, a);
    ASSERT_SAME(mpl::true_type, b);

    auto eq = (x == y);
    auto ne = (x != y);
    auto lt = (x <  y);
    auto le = (x <= y);
    auto gt = (x >  y);
    auto ge = (x >= y);

    ASSERT_SAME(X, decltype(eq));
    ASSERT_SAME(X, decltype(ne));
    ASSERT_SAME(X, decltype(lt));
    ASSERT_SAME(X, decltype(le));
    ASSERT_SAME(X, decltype(gt));
    ASSERT_SAME(X, decltype(ge));
}

} // namespace relational
} // namespace value

} // anonymous namespace
