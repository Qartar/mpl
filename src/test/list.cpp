#include "mpl/list.h"

#include <type_traits>

namespace A {

using _A = mpl::list<int>;
using _B = mpl::car<_A>;
using _C = mpl::cdr<_A>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<mpl::nil, _C>::value, "");

} // namespace A

namespace B {

using _A = mpl::list<int, bool>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::cdr<mpl::cdr<_A>>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<bool, _C>::value, "");
static_assert(std::is_same<mpl::nil, _D>::value, "");

} // namespace B

namespace C {

using _A = mpl::list<int, bool, float>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::car<mpl::cdr<mpl::cdr<_A>>>;
using _E = mpl::cdr<mpl::cdr<mpl::cdr<_A>>>;

static_assert(std::is_same<int, _B>::value, "");
static_assert(std::is_same<bool, _C>::value, "");
static_assert(std::is_same<float, _D>::value, "");
static_assert(std::is_same<mpl::nil, _E>::value, "");

} // namespace C
