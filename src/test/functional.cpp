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

template<typename _Tx, typename _Ty, typename = void, typename = void> struct fn_and {
    using type = std::false_type;
};

template<typename _Tx, typename _Ty>
struct fn_and<_Tx, _Ty, std::enable_if_t<_Tx::value>, std::enable_if_t<_Ty::value>> {
    using type = std::true_type;
};

template<typename _Tx, typename _Ty, typename = void, typename = void> struct fn_or {
    using type = std::true_type;
};

template<typename _Tx, typename _Ty>
struct fn_or < _Tx, _Ty, std::enable_if_t < !_Tx::value >, std::enable_if_t < !_Ty::value >> {
    using type = std::false_type;
};

template<typename _Tx, typename _Ty> using and = typename fn_and<_Tx, _Ty>::type;
template<typename _Tx, typename _Ty> using or = typename fn_or<_Tx, _Ty>::type;

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::list<int, bool, float, double>;
using _B = mpl::reduce<or, mpl::map<std::is_floating_point, _A>>;
using _C = mpl::reduce<and, mpl::map<std::is_floating_point, _A>>;
using _D = mpl::reduce<or, mpl::map<std::is_pointer, _A>>;
using _E = mpl::reduce<and, mpl::map<std::is_fundamental, _A>>;

ASSERT_SAME(_B, std::true_type);
ASSERT_SAME(_C, std::false_type);
ASSERT_SAME(_D, std::false_type);
ASSERT_SAME(_E, std::true_type);

} // namespace A
} // namespace reduce

} // anonymous namespace
