#include "mpl_test.h"

#include "mpl/units.h"

namespace {

////////////////////////////////////////////////////////////////////////////////
namespace value {

//------------------------------------------------------------------------------
namespace A {

using _A = mpl::units::value<int, void>;

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
