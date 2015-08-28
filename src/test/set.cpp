#include "mpl_test.h"

#include "mpl/set.h"

namespace {

///////////////////////////////////////////////////////////////////////////////
namespace is_same {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::is_same<int, int>;
using _B = mpl::is_same<int, bool>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);

} // namespace A
} // namespace is_same

///////////////////////////////////////////////////////////////////////////////
namespace contains {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<>;
using _B = mpl::contains<_A, int>;
using _C = mpl::contains<_A, mpl::nil>;

ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<mpl::nil>;
using _B = mpl::contains<_A, mpl::nil>;

ASSERT_SAME(_B, mpl::true_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::list<int, bool, float>;
using _B = mpl::contains<_A, int>;
using _C = mpl::contains<_A, bool>;
using _D = mpl::contains<_A, float>;
using _E = mpl::contains<_A, double>;

ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::true_type);
ASSERT_SAME(_E, mpl::false_type);

} // namespace C
} // namespace contains

} // anonymous namespace
