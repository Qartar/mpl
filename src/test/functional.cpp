#include "mpl_test.h"

#include "mpl/functional.h"

namespace {

///////////////////////////////////////////////////////////////////////////////
namespace map {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int>;
using _B = mpl::map<std::add_pointer_t, _A>;
using _C = mpl::index<_B, 0>;

ASSERT_SAME(_C, int*);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<int, bool, float>;
using _B = mpl::map<std::add_const_t, _A>;
using _C = mpl::index<_B, 0>;
using _D = mpl::index<_B, 1>;
using _E = mpl::index<_B, 2>;

ASSERT_SAME(_C, int const);
ASSERT_SAME(_D, bool const);
ASSERT_SAME(_E, float const);

} // namespace B
} // namespace map

} // anonymous namespace
