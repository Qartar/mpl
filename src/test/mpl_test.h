#include <type_traits>

#define ASSERT_SAME(x, y) static_assert(std::is_same<x, y>::value, "Expected same type for " #x " and " #y ".")
