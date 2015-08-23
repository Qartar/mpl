#include "mpl_test.h"

#include "mpl/list.h"

namespace {

namespace A {

using _A = mpl::list<int>;
using _B = mpl::car<_A>;
using _C = mpl::cdr<_A>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, mpl::nil);

} // namespace A

namespace B {

using _A = mpl::list<int, bool>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::cdr<mpl::cdr<_A>>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);
ASSERT_SAME(_D, mpl::nil);

} // namespace B

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

namespace D {

using _A = mpl::list<int>;
using _B = mpl::list<bool>;
using _C = mpl::extend<_A, _B>;
using _D = mpl::car<_C>;
using _E = mpl::car<mpl::cdr<_C>>;
using _F = mpl::cdr<mpl::cdr<_C>>;

ASSERT_SAME(_D, int);
ASSERT_SAME(_E, bool);
ASSERT_SAME(_F, mpl::nil);

} // namespace D

namespace E {

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

} // namespace E

namespace F {

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

} // namespace F

namespace G {

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

} // namespace G

namespace H {

using _E = mpl::index<0, G::_D>;
using _F = mpl::index<1, G::_D>;
using _G = mpl::index<2, G::_D>;
using _H = mpl::index<3, G::_D>;
using _I = mpl::index<4, G::_D>;
using _J = mpl::index<5, G::_D>;

ASSERT_SAME(_E, G::_E);
ASSERT_SAME(_F, G::_F);
ASSERT_SAME(_G, G::_G);
ASSERT_SAME(_H, G::_H);
ASSERT_SAME(_I, G::_I);
ASSERT_SAME(_J, G::_J);

} // namespace H

} // anonymous namespace
