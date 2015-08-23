#include "mpl/list.h"

#include <type_traits>

namespace {

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

namespace D {

using _A = mpl::list<int>;
using _B = mpl::list<bool>;
using _C = mpl::extend<_A, _B>;
using _D = mpl::car<_C>;
using _E = mpl::car<mpl::cdr<_C>>;
using _F = mpl::cdr<mpl::cdr<_C>>;

static_assert(std::is_same<int, _D>::value, "");
static_assert(std::is_same<bool, _E>::value, "");
static_assert(std::is_same<mpl::nil, _F>::value, "");

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

static_assert(std::is_same<int, _E>::value, "");
static_assert(std::is_same<bool, _F>::value, "");
static_assert(std::is_same<float, _G>::value, "");
static_assert(std::is_same<mpl::nil, _H>::value, "");

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

static_assert(std::is_same<int, _D>::value, "");
static_assert(std::is_same<bool, _E>::value, "");
static_assert(std::is_same<float, _F>::value, "");
static_assert(std::is_same<double, _G>::value, "");
static_assert(std::is_same<mpl::nil, _H>::value, "");

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

static_assert(std::is_same<int, _E>::value, "");
static_assert(std::is_same<bool, _F>::value, "");
static_assert(std::is_same<float, _G>::value, "");
static_assert(std::is_same<double, _H>::value, "");
static_assert(std::is_same<wchar_t, _I>::value, "");
static_assert(std::is_same<unsigned, _J>::value, "");
static_assert(std::is_same<mpl::nil, _K>::value, "");

} // namespace G

} // anonymous namespace
