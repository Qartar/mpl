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

///////////////////////////////////////////////////////////////////////////////
namespace set {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::set<>;
using _B = mpl::contains<_A, int>;

ASSERT_SAME(_A, mpl::nil);
ASSERT_SAME(_B, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::set<int, bool, float>;
using _B = mpl::contains<_A, int>;
using _C = mpl::contains<_A, bool>;
using _D = mpl::contains<_A, float>;
using _E = mpl::contains<_A, double>;

ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::true_type);
ASSERT_SAME(_E, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::set<int, int, bool, bool>;
using _B = mpl::index<_A, 0>;
using _C = mpl::index<_A, 1>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);

} // namespace C
} // namespace set

///////////////////////////////////////////////////////////////////////////////
namespace join {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::join<>;

ASSERT_SAME(_A, mpl::nil);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::set<int, bool>;
using _B = mpl::join<_A>;

ASSERT_SAME(_A, _B);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::set<int, bool>;
using _B = mpl::set<float, double>;
using _C = mpl::join<_A, _B>;

using _D = mpl::contains<_C, int>;
using _E = mpl::contains<_C, bool>;
using _F = mpl::contains<_C, float>;
using _G = mpl::contains<_C, double>;

ASSERT_SAME(_D, mpl::true_type);
ASSERT_SAME(_E, mpl::true_type);
ASSERT_SAME(_F, mpl::true_type);
ASSERT_SAME(_G, mpl::true_type);

} // namespace C

//-----------------------------------------------------------------------------
namespace D {

using _A = mpl::set<int, bool>;
using _B = mpl::set<float, double>;
using _C = mpl::set<wchar_t, unsigned>;
using _D = mpl::join<_A, _B, _C>;

using _E = mpl::contains<_D, int>;
using _F = mpl::contains<_D, bool>;
using _G = mpl::contains<_D, float>;
using _H = mpl::contains<_D, double>;
using _I = mpl::contains<_D, wchar_t>;
using _J = mpl::contains<_D, unsigned>;

ASSERT_SAME(_E, mpl::true_type);
ASSERT_SAME(_F, mpl::true_type);
ASSERT_SAME(_G, mpl::true_type);
ASSERT_SAME(_H, mpl::true_type);
ASSERT_SAME(_I, mpl::true_type);
ASSERT_SAME(_J, mpl::true_type);

} // namespace D
} // namespace join

///////////////////////////////////////////////////////////////////////////////
namespace meet {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::meet<>;
using _B = mpl::meet<mpl::nil>;
using _C = mpl::meet<mpl::nil, mpl::nil>;

ASSERT_SAME(_A, mpl::nil);
ASSERT_SAME(_B, mpl::nil);
ASSERT_SAME(_C, mpl::nil);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::set<int, bool, float>;
using _B = mpl::set<bool, float, double>;
using _C = mpl::meet<_A, _B>;

using _D = mpl::contains<_C, int>;
using _E = mpl::contains<_C, bool>;
using _F = mpl::contains<_C, float>;
using _G = mpl::contains<_C, double>;

ASSERT_SAME(_D, mpl::false_type);
ASSERT_SAME(_E, mpl::true_type);
ASSERT_SAME(_F, mpl::true_type);
ASSERT_SAME(_G, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::set<int, bool, float>;
using _B = mpl::set<bool, float, double>;
using _C = mpl::set<float, double, wchar_t>;
using _D = mpl::meet<_A, _B, _C>;

using _E = mpl::contains<_D, int>;
using _F = mpl::contains<_D, bool>;
using _G = mpl::contains<_D, float>;
using _H = mpl::contains<_D, double>;
using _I = mpl::contains<_D, wchar_t>;

ASSERT_SAME(_E, mpl::false_type);
ASSERT_SAME(_F, mpl::false_type);
ASSERT_SAME(_G, mpl::true_type);
ASSERT_SAME(_H, mpl::false_type);
ASSERT_SAME(_I, mpl::false_type);

} // namespace C
} // namespace meet

} // anonymous namespace
