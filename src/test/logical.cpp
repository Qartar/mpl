#include "mpl_test.h"

#include "mpl/logical.h"

namespace {

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

using _A = mpl::and<std::true_type, std::true_type>;
using _B = mpl::and<std::true_type, std::false_type>;
using _C = mpl::and<std::false_type, std::true_type>;
using _D = mpl::and<std::false_type, std::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::and<std::true_type, mpl::true_type>;
using _B = mpl::and<std::true_type, mpl::false_type>;
using _C = mpl::and<std::false_type, mpl::true_type>;
using _D = mpl::and<std::false_type, mpl::false_type>;

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

using _A = mpl::or<std::true_type, std::true_type>;
using _B = mpl::or<std::true_type, std::false_type>;
using _C = mpl::or<std::false_type, std::true_type>;
using _D = mpl::or<std::false_type, std::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::or<std::true_type, mpl::true_type>;
using _B = mpl::or<std::true_type, mpl::false_type>;
using _C = mpl::or<std::false_type, mpl::true_type>;
using _D = mpl::or<std::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C
} // namespace or

///////////////////////////////////////////////////////////////////////////////
namespace not {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::not<mpl::true_type>;
using _B = mpl::not<mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);

} // namespace A
} // namespace not

///////////////////////////////////////////////////////////////////////////////
namespace all {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::all<mpl::true_type, mpl::true_type>;
using _B = mpl::all<mpl::true_type, mpl::false_type>;
using _C = mpl::all<mpl::false_type, mpl::true_type>;
using _D = mpl::all<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::all<mpl::true_type, mpl::true_type, mpl::true_type>;
using _B = mpl::all<mpl::true_type, mpl::true_type, mpl::false_type>;
using _C = mpl::all<mpl::true_type, mpl::false_type, mpl::true_type>;
using _D = mpl::all<mpl::true_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::all<mpl::true_type, mpl::true_type, mpl::true_type, mpl::true_type>;
using _B = mpl::all<mpl::true_type, mpl::true_type, mpl::true_type, mpl::false_type>;
using _C = mpl::all<mpl::true_type, mpl::true_type, mpl::false_type, mpl::true_type>;
using _D = mpl::all<mpl::true_type, mpl::true_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C

//-----------------------------------------------------------------------------
namespace D {

using _A = mpl::all<>;
using _B = mpl::all<mpl::true_type>;
using _C = mpl::all<mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::false_type);

} // namespace D
} // namespace all

///////////////////////////////////////////////////////////////////////////////
namespace any {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::any<mpl::true_type, mpl::true_type>;
using _B = mpl::any<mpl::true_type, mpl::false_type>;
using _C = mpl::any<mpl::false_type, mpl::true_type>;
using _D = mpl::any<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::any<mpl::false_type, mpl::true_type, mpl::true_type>;
using _B = mpl::any<mpl::false_type, mpl::true_type, mpl::false_type>;
using _C = mpl::any<mpl::false_type, mpl::false_type, mpl::true_type>;
using _D = mpl::any<mpl::false_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::any<mpl::false_type, mpl::false_type, mpl::true_type, mpl::true_type>;
using _B = mpl::any<mpl::false_type, mpl::false_type, mpl::true_type, mpl::false_type>;
using _C = mpl::any<mpl::false_type, mpl::false_type, mpl::false_type, mpl::true_type>;
using _D = mpl::any<mpl::false_type, mpl::false_type, mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C

//-----------------------------------------------------------------------------
namespace D {

using _A = mpl::any<>;
using _B = mpl::any<mpl::true_type>;
using _C = mpl::any<mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::false_type);

} // namespace D
} // namespace any

} // anonymous namespace
