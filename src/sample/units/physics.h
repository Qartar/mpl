#include "mpl/units.h"

#include "types.h"

////////////////////////////////////////////////////////////////////////////////
namespace samples {

//! Acceleration due to gravity on Earth.
template<typename T> constexpr auto g = meters_per_second_squared<T>((T)9.80665);

//! Speed of light in vacuum.
template<typename T> constexpr auto c = meters_per_second<T>((T)2.99792458e8);

//! Gravitational constant
template<typename T> constexpr auto G = meters_cubed_per_kilogram_seconds_squared<T>((T)6.6740831e-11);

//! Magnetic permeability in vacuum.
template<typename T> constexpr auto mu0 = newtons_per_ampere_squared<T>((T)1.2566370614e-6);

//! Boltzmann constant
template<typename T> constexpr auto k_b = joules_per_kelvin<T>((T)1.3806485279e-23);

//! Ideal gas constant
template<typename T> constexpr auto R = joules_per_mole_kelvin<T>((T)8.3144598);

} // namespace samples
