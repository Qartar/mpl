#include "mpl/units.h"

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
namespace samples {

//! Acceleration due to gravity on Earth.
template<typename T> constexpr meters_per_second_squared<T> g() {
    return meters_per_second_squared<T>((T)9.80665);
}

//! Speed of light in vacuum.
template<typename T> constexpr meters_per_second<T> c() {
    return meters_per_second<T>((T)2.99792458e8);
}

//! Gravitational constant
template<typename T> constexpr meters_cubed_per_kilogram_seconds_squared<T> G() {
    return meters_cubed_per_kilogram_seconds_squared<T>((T)6.6740831e-11);
}

//! Magnetic permeability in vacuum.
template<typename T> constexpr newtons_per_ampere_squared<T> mu0() {
    return newtons_per_ampere_squared<T>((T)1.2566370614e-6);
}

//! Boltzmann constant
template<typename T> constexpr joules_per_kelvin<T> k_b() {
    return joules_per_kelvin<T>((T)1.3806485279e-23);
}

} // namespace samples
