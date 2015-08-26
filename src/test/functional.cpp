#include "mpl_test.h"

#include "mpl/functional.h"
#include "mpl/logical.h"

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

///////////////////////////////////////////////////////////////////////////////
namespace filter {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int, bool, float, double>;
using _B = mpl::filter<std::is_floating_point, _A>;
using _C = mpl::index<_B, 0>;
using _D = mpl::index<_B, 1>;

ASSERT_SAME(_C, float);
ASSERT_SAME(_D, double);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<int, bool>;
using _B = mpl::filter<std::is_floating_point, _A>;

ASSERT_SAME(_B, mpl::nil);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::filter<std::is_floating_point, mpl::nil>;

ASSERT_SAME(_A, mpl::nil);

} // namespace C

//-----------------------------------------------------------------------------
namespace D {

using _A = mpl::list<int, bool, float, double>;
using _B = mpl::filter<std::is_fundamental, _A>;

ASSERT_SAME(_A, _B);

} // namespace D
} // namespace filter

///////////////////////////////////////////////////////////////////////////////
namespace reduce {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int, bool, float, double>;
using _B = mpl::reduce<mpl::or, mpl::map<std::is_floating_point, _A>>;
using _C = mpl::reduce<mpl::and, mpl::map<std::is_floating_point, _A>>;
using _D = mpl::reduce<mpl::or, mpl::map<std::is_pointer, _A>>;
using _E = mpl::reduce<mpl::and, mpl::map<std::is_fundamental, _A>>;

ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);
ASSERT_SAME(_E, mpl::true_type);

} // namespace A
} // namespace reduce

} // anonymous namespace
