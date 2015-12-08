#include "physics.h"

////////////////////////////////////////////////////////////////////////////////
namespace samples {

//------------------------------------------------------------------------------
namespace kinematics {

////////////////////////////////////////////////////////////////////////////////
/**
 * Exercise 1
 *
 * Block A of mass m_a rests on block B of mass m_b. They are both attached via
 * a pulley to one side, and block B is pulled in the opposite direction by a
 * string with force F. The coefficient of static friction between block A and B
 * is mu_1 and the coefficient of static friction between block B and the ground
 * is mu_2. What is the force required on the string to overcome static friction
 * on blocks A and B?
 *
 *             +-----+
 *             |  A  |---------/---\
 *          +--+-----+--+      | O |
 *  F <-----|     B     |------\---/
 *          +-----------+
 */
newtons<float> exercise_1(kilograms<float> m_a,
                          kilograms<float> m_b,
                          float mu_1,
                          float mu_2) {

    /**
     * Force diagram:
     *
     *      Fa_N ^                   Fb_N ^
     *           |                        |   
     *  Fa_f <---+---> Fa_T         F <---+---> Fb_T + Fb_f + Fa_f
     *           |                        |
     *           v Fa_g                   v Fb_g + Fa_N
     *
     * Fa_N     Normal force on A
     * Fa_g     Gravitational force on A
     * Fa_T     Force of tension on A from pulley
     * Fa_f     Force of friction on A from B
     *
     * Fb_N     Normal force on B
     * Fb_g     Gravitational force on B
     * Fb_T     Force of tension on B from pulley
     * Fb_f     Force of friction on B from ground
     * F        Force of tension on B from string
     */

    /**
     * System of equations:
     *
     * Fx_a :=  Fa_f - Fa_T  = 0
     * Fy_a :=  Fa_N - Fa_g  = 0
     *
     * Fx_b :=  F    - Fb_T - Fb_f - Fa_f = 0
     * Fy_b :=  Fb_N - Fb_g - Fa_N        = 0
     */

    //! Gravitational force on A
    auto Fa_g = m_a * g<float>();
    //! Normal force on A
    auto Fa_N = Fa_g;
    //! Force of friction on A from B
    auto Fa_f = mu_1 * Fa_N;

    //! Gravitational force on B
    auto Fb_g = m_b * g<float>();
    //! Normal force on B
    auto Fb_N = Fb_g + Fa_N;
    //! Force of friction on B from ground
    auto Fb_f = mu_2 * Fb_N;

    //! Force of tension on A from pulley
    auto Fa_T = Fa_f;
    //! Force of tension on B from pulley
    auto Fb_T = Fa_T;

    //! Force of tension on B from string
    return Fb_T + Fb_f + Fa_f;
}

} // namespace kinematics

} // namespace samples
