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
//ASSERT_SAME(teslas, _teslas); // FIXME
ASSERT_SAME(henries, _henries);

} // namespace B
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
} // namespace value

} // anonymous namespace
