#include "mpl_test.h"

#include "mpl/logical.h"

namespace {

///////////////////////////////////////////////////////////////////////////////
namespace not_ {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::not_<mpl::true_type>;
using _B = mpl::not_<mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);

} // namespace A
} // namespace not_

///////////////////////////////////////////////////////////////////////////////
namespace and_ {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::and_<mpl::true_type, mpl::true_type>;
using _B = mpl::and_<mpl::true_type, mpl::false_type>;
using _C = mpl::and_<mpl::false_type, mpl::true_type>;
using _D = mpl::and_<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::and_<std::true_type, std::true_type>;
using _B = mpl::and_<std::true_type, std::false_type>;
using _C = mpl::and_<std::false_type, std::true_type>;
using _D = mpl::and_<std::false_type, std::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::and_<std::true_type, mpl::true_type>;
using _B = mpl::and_<std::true_type, mpl::false_type>;
using _C = mpl::and_<std::false_type, mpl::true_type>;
using _D = mpl::and_<std::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C
} // namespace and_

///////////////////////////////////////////////////////////////////////////////
namespace or_ {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::or_<mpl::true_type, mpl::true_type>;
using _B = mpl::or_<mpl::true_type, mpl::false_type>;
using _C = mpl::or_<mpl::false_type, mpl::true_type>;
using _D = mpl::or_<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A

//-----------------------------------------------------------------------------
namespace B {

using _A = mpl::or_<std::true_type, std::true_type>;
using _B = mpl::or_<std::true_type, std::false_type>;
using _C = mpl::or_<std::false_type, std::true_type>;
using _D = mpl::or_<std::false_type, std::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace B

//-----------------------------------------------------------------------------
namespace C {

using _A = mpl::or_<std::true_type, mpl::true_type>;
using _B = mpl::or_<std::true_type, mpl::false_type>;
using _C = mpl::or_<std::false_type, mpl::true_type>;
using _D = mpl::or_<std::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace C
} // namespace or_

///////////////////////////////////////////////////////////////////////////////
namespace nand {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::nand<mpl::true_type, mpl::true_type>;
using _B = mpl::nand<mpl::true_type, mpl::false_type>;
using _C = mpl::nand<mpl::false_type, mpl::true_type>;
using _D = mpl::nand<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::true_type);

} // namespace A
} // namespace nand

///////////////////////////////////////////////////////////////////////////////
namespace nor {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::nor<mpl::true_type, mpl::true_type>;
using _B = mpl::nor<mpl::true_type, mpl::false_type>;
using _C = mpl::nor<mpl::false_type, mpl::true_type>;
using _D = mpl::nor<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::true_type);

} // namespace A
} // namespace nor

///////////////////////////////////////////////////////////////////////////////
namespace xor_ {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::xor_<mpl::true_type, mpl::true_type>;
using _B = mpl::xor_<mpl::true_type, mpl::false_type>;
using _C = mpl::xor_<mpl::false_type, mpl::true_type>;
using _D = mpl::xor_<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::false_type);
ASSERT_SAME(_B, mpl::true_type);
ASSERT_SAME(_C, mpl::true_type);
ASSERT_SAME(_D, mpl::false_type);

} // namespace A
} // namespace xor_

///////////////////////////////////////////////////////////////////////////////
namespace xnor {

//-----------------------------------------------------------------------------
namespace A {

using _A = mpl::xnor<mpl::true_type, mpl::true_type>;
using _B = mpl::xnor<mpl::true_type, mpl::false_type>;
using _C = mpl::xnor<mpl::false_type, mpl::true_type>;
using _D = mpl::xnor<mpl::false_type, mpl::false_type>;

ASSERT_SAME(_A, mpl::true_type);
ASSERT_SAME(_B, mpl::false_type);
ASSERT_SAME(_C, mpl::false_type);
ASSERT_SAME(_D, mpl::true_type);

} // namespace A
} // namespace xnor

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
