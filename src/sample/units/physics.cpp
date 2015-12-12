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

////////////////////////////////////////////////////////////////////////////////
/**
 * Exercise 2
 *
 * Using the configuration in Exercise 1, determine the acceleration of block B
 * when the force of tension on the string attached to block B is F. The 
 * coefficient of kinetic friction between block A and B is mu_1 and the between
 * block B and the ground is mu_2. Assume the blocks are already in motion (you
 * may skip any considerations for static friction).
 */
meters_per_second_squared<float> exercise_2(kilograms<float> m_a,
                                            kilograms<float> m_b,
                                            float mu_1,
                                            float mu_2,
                                            newtons<float> F) {

    // Check that the force of tension is sufficient to overcome friction.
    if (F < exercise_1(m_a, m_b, mu_1, mu_2)) {
        return meters_per_second_squared<float>(0.0f);
    }

    /**
     * System of equations:
     *
     * Fx_a :=  Fa_f - Fa_T  = -a * m_a
     * Fy_a :=  Fa_N - Fa_g  = 0
     *
     * Fx_b :=  F    - Fb_T - Fb_f - Fa_f = a * m_b
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

    /**
     * Solving for T (Fa_T and Fb_T):
     *
     *  a = ( T - Fa_f ) / m_a
     *  a = ( F - T - Fb_f - Fa_f ) / m_b
     *
     * ( T - Fa_f ) / m_a = ( F - T - Fb_f - Fa_f ) / m_b
     * ( T - Fa_f ) * m_b = ( F - T - Fb_f - Fa_f ) * m_a
     *
     * T * ( m_a + m_b ) = ( F - Fb_f - Fa_f ) * m_a + Fa_f * m_b
     *
     * K_a := m_a / ( m_a + m_b )
     * K_b := m_b / ( m_a + m_b )
     *
     * T = (F - Fb_f - Fa_f ) * K_a + Fa_f * K_b
     */

    //! Mass coefficient of block A
    auto K_a = m_a / ( m_a + m_b );
    //! Mass coefficient of block B
    auto K_b = m_b / ( m_a + m_b );
    //! Force of tension from pulley on blocks A and B
    auto T = ( F - Fb_f - Fa_f ) * K_a + Fa_f * K_b;

    //! Acceleration of block B
    return ( F - T - Fb_f - Fa_f ) / m_b;
}

} // namespace kinematics

} // namespace samples
