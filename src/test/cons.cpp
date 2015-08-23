#include "mpl_test.h"

#include "mpl/cons.h"

namespace {

namespace A {

using _A = mpl::cons<int, bool>;
using _B = mpl::car<_A>;
using _C = mpl::cdr<_A>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);

} // namespace A

namespace B {

using _A = mpl::cons<int, mpl::cons<bool, float>>;
using _B = mpl::car<_A>;
using _C = mpl::car<mpl::cdr<_A>>;
using _D = mpl::cdr<mpl::cdr<_A>>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);
ASSERT_SAME(_D, float);

} // namespace B

namespace C {

using _A = mpl::cons<mpl::cons<int, bool>, mpl::cons<float, double>>;
using _B = mpl::car<mpl::car<_A>>;
using _C = mpl::cdr<mpl::car<_A>>;
using _D = mpl::car<mpl::cdr<_A>>;
using _E = mpl::cdr<mpl::cdr<_A>>;

ASSERT_SAME(_B, int);
ASSERT_SAME(_C, bool);
ASSERT_SAME(_D, float);
ASSERT_SAME(_E, double);

} // namespace C

} // anonymous namespace
