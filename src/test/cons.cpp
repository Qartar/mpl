#include "mpl/cons.h"

#include <type_traits>

namespace {

namespace A {

using _A = mpl::cons<int, bool>;
using _B = mpl::car<_A>;
using _C = mpl::cdr<_A>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<bool, _C>::value, "");

} // namespace A

namespace B {

using _A = mpl::cons<int, mpl::cons<bool, float>>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::cdr<mpl::cdr<_A>>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<bool, _C>::value, "");
static_assert(std::is_same<float, _D>::value, "");

} // namespace B

namespace C {

using _A = mpl::cons<mpl::cons<int, bool>, mpl::cons<float, double>>;
using _B = mpl::car<mpl::car<_A>>;
using _C = mpl::cdr<mpl::car<_A>>;
using _D = mpl::car<mpl::cdr<_A>>;
using _E = mpl::cdr<mpl::cdr<_A>>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<bool, _C>::value, "");
static_assert(std::is_same<float, _D>::value, "");
static_assert(std::is_same<double, _E>::value, "");

} // namespace C

} // anonymous namespace
