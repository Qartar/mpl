#include "mpl_test.h"

#include "mpl/logical.h"

///////////////////////////////////////////////////////////////////////////////
namespace and {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::and<mpl::true_type, mpl::true_type>;
using _B = mpl::and<mpl::true_type, mpl::false_type>;
using _C = mpl::and<mpl::false_type, mpl::true_type>;
using _D = mpl::and<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::and<mpl::true_type, mpl::true_type, mpl::true_type>;
using _B = mpl::and<mpl::true_type, mpl::true_type, mpl::false_type>;
using _C = mpl::and<mpl::true_type, mpl::false_type, mpl::true_type>;
using _D = mpl::and<mpl::true_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::and<mpl::true_type, mpl::true_type, mpl::true_type, mpl::true_type>;
using _B = mpl::and<mpl::true_type, mpl::true_type, mpl::true_type, mpl::false_type>;
using _C = mpl::and<mpl::true_type, mpl::true_type, mpl::false_type, mpl::true_type>;
using _D = mpl::and<mpl::true_type, mpl::true_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C
} // namespace and

///////////////////////////////////////////////////////////////////////////////
namespace or {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::or<mpl::true_type, mpl::true_type>;
using _B = mpl::or<mpl::true_type, mpl::false_type>;
using _C = mpl::or<mpl::false_type, mpl::true_type>;
using _D = mpl::or<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::or<mpl::false_type, mpl::true_type, mpl::true_type>;
using _B = mpl::or<mpl::false_type, mpl::true_type, mpl::false_type>;
using _C = mpl::or<mpl::false_type, mpl::false_type, mpl::true_type>;
using _D = mpl::or<mpl::false_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::or<mpl::false_type, mpl::false_type, mpl::true_type, mpl::true_type>;
using _B = mpl::or<mpl::false_type, mpl::false_type, mpl::true_type, mpl::false_type>;
using _C = mpl::or<mpl::false_type, mpl::false_type, mpl::false_type, mpl::true_type>;
using _D = mpl::or<mpl::false_type, mpl::false_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C
} // namespace or
