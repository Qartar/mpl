#include "mpl_test.h"

#include "mpl/list.h"

namespace {

///////////////////////////////////////////////////////////////////////////////
namespace list {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int>;
using _B = mpl::car<_A>;
using _C = mpl::cdr<_A>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, mpl::nil);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<int, bool>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::cdr<mpl::cdr<_A>>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);
ASSERT_SAME(_D, mpl::nil);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::list<int, bool, float>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::car<mpl::cdr<mpl::cdr<_A>>>;
using _E = mpl::cdr<mpl::cdr<mpl::cdr<_A>>>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);
ASSERT_SAME(_D, float);
ASSERT_SAME(_E, mpl::nil);

} // namespace C
} // namespace list

///////////////////////////////////////////////////////////////////////////////
namespace extend {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int>;
using _B = mpl::list<bool>;
using _C = mpl::extend<_A, _B>;
using _D = mpl::car<_C>;
using _E = mpl::car<mpl::cdr<_C>>;
using _F = mpl::cdr<mpl::cdr<_C>>;

ASSERT_SAME(_D, int);
ASSERT_SAME(_E, bool);
ASSERT_SAME(_F, mpl::nil);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<int>;
using _B = mpl::list<bool>;
using _C = mpl::list<float>;
using _D = mpl::extend<_A, _B, _C>;
using _E = mpl::car<_D>;
using _F = mpl::car<mpl::cdr<_D>>;
using _G = mpl::car<mpl::cdr<mpl::cdr<_D>>>;
using _H = mpl::cdr<mpl::cdr<mpl::cdr<_D>>>;

ASSERT_SAME(_E, int);
ASSERT_SAME(_F, bool);
ASSERT_SAME(_G, float);
ASSERT_SAME(_H, mpl::nil);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::list<int, bool>;
using _B = mpl::list<float, double>;
using _C = mpl::extend<_A, _B>;
using _D = mpl::car<_C>;
using _E = mpl::car<mpl::cdr<_C>>;
using _F = mpl::car<mpl::cdr<mpl::cdr<_C>>>;
using _G = mpl::car<mpl::cdr<mpl::cdr<mpl::cdr<_C>>>>;
using _H = mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<_C>>>>;

ASSERT_SAME(_D, int);
ASSERT_SAME(_E, bool);
ASSERT_SAME(_F, float);
ASSERT_SAME(_G, double);
ASSERT_SAME(_H, mpl::nil);

} // namespace C

//-----------------------------------------------------------------------------
namespace D {

using _A = mpl::list<int, bool>;
using _B = mpl::list<float, double>;
using _C = mpl::list<wchar_t, unsigned>;
using _D = mpl::extend<_A, _B, _C>;
using _E = mpl::car<_D>;
using _F = mpl::car<mpl::cdr<_D>>;
using _G = mpl::car<mpl::cdr<mpl::cdr<_D>>>;
using _H = mpl::car<mpl::cdr<mpl::cdr<mpl::cdr<_D>>>>;
using _I = mpl::car<mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<_D>>>>>;
using _J = mpl::car<mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<_D>>>>>>;
using _K = mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<mpl::cdr<_D>>>>>>;

ASSERT_SAME(_E, int);
ASSERT_SAME(_F, bool);
ASSERT_SAME(_G, float);
ASSERT_SAME(_H, double);
ASSERT_SAME(_I, wchar_t);
ASSERT_SAME(_J, unsigned);
ASSERT_SAME(_K, mpl::nil);

} // namespace D
} // namespace extend

///////////////////////////////////////////////////////////////////////////////
namespace append {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int>;
using _B = mpl::append<_A, bool>;
using _C = mpl::car<_B>;
using _D = mpl::car<mpl::cdr<_B>>;

ASSERT_SAME(_C, int);
ASSERT_SAME(_D, bool);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::list<int>;
using _B = mpl::append<_A, bool, float>;
using _C = mpl::car<_B>;
using _D = mpl::car<mpl::cdr<_B>>;
using _E = mpl::car<mpl::cdr<mpl::cdr<_B>>>;

ASSERT_SAME(_C, int);
ASSERT_SAME(_D, bool);
ASSERT_SAME(_E, float);

} // namespace B
} // namespace append

///////////////////////////////////////////////////////////////////////////////
namespace index {

//-----------------------------------------------------------------------------
namespace A {

using _E = mpl::index<extend::D::_D, 0>;
using _F = mpl::index<extend::D::_D, 1>;
using _G = mpl::index<extend::D::_D, 2>;
using _H = mpl::index<extend::D::_D, 3>;
using _I = mpl::index<extend::D::_D, 4>;
using _J = mpl::index<extend::D::_D, 5>;

ASSERT_SAME(_E, extend::D::_E);
ASSERT_SAME(_F, extend::D::_F);
ASSERT_SAME(_G, extend::D::_G);
ASSERT_SAME(_H, extend::D::_H);
ASSERT_SAME(_I, extend::D::_I);
ASSERT_SAME(_J, extend::D::_J);

} // namespace A
} // namespace index

} // anonymous namespace
