#include "mpl/units.h"

////////////////////////////////////////////////////////////////////////////////
namespace samples {

template<typename T> using kilograms = mpl::units::value<T, mpl::units::si::kilograms>;
template<typename T> using meters = mpl::units::value<T, mpl::units::si::meters>;
template<typename T> using seconds = mpl::units::value<T, mpl::units::si::seconds>;
template<typename T> using amperes = mpl::units::value<T, mpl::units::si::amperes>;
template<typename T> using kelvin = mpl::units::value<T, mpl::units::si::kelvin>;
template<typename T> using moles = mpl::units::value<T, mpl::units::si::moles>;
template<typename T> using newtons = mpl::units::value<T, mpl::units::si::newtons>;
template<typename T> using pascals = mpl::units::value<T, mpl::units::si::pascals>;
template<typename T> using joules = mpl::units::value<T, mpl::units::si::joules>;

//! Velocity
template<typename T> using meters_per_second = decltype(meters<T>{} / seconds<T>{});
//! Acceleration
template<typename T> using meters_per_second_squared = decltype(meters_per_second<T>{} / seconds<T>{});
//! Linear momentum
template<typename T> using kilogram_meters_per_second = decltype(kilograms<T>{} * meters_per_second<T>{});
//! Volume
template<typename T> using meters_cubed = decltype(meters<T>{} * meters<T>{} * meters<T>{});
//! Mass density
template<typename T> using kilograms_per_meter_cubed = decltype(kilograms<T>{} / meters_cubed<T>{});
//! Molar mass
template<typename T> using kilograms_per_mole = decltype(kilograms<T>{} / moles<T>{});

//! Gravitational constant
template<typename T> using meters_cubed_per_kilogram_seconds_squared = void;
//! Magnetic permeability
template<typename T> using newtons_per_ampere_squared = decltype(newtons<T>{} / amperes<T>{} / amperes<T>{});
//! Thermal capacity, entropy
template<typename T> using joules_per_kelvin = decltype(joules<T>{} / kelvin<T>{});
//! Specific heat
template<typename T> using joules_per_kilogram = decltype(joules<T>{} / kilograms<T>{});
//! Specific heat capacity
template<typename T> using joules_per_kilogram_kelvin = decltype(joules<T>{} / kilograms<T>{} / kelvin<T>{});
//! Specific heat capacity
template<typename T> using joules_per_mole_kelvin = decltype(joules<T>{} / moles<T>{} / kelvin<T>{}); 

} // namespace samples
