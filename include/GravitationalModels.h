/*
 * ---------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [GravitationalModels.h]
 * Author:      Prof.Dr. Onur Tuncer
 * Email:       onur.tuncer@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronuatics and Astronautics
 * 
 * Date:        2024
 * 
 * Description:
 * [Routines to perform gravitational model calculations]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * -----------------------------------------------------------------------------------
 */

#ifndef GRAVITATIONAL_MODELS_H
#define GRAVITATIONAL_MODELS_H

#include <iostream>
#include <cmath>
#include <array>
#include <concepts>

namespace J2 {

// Constants for the J2 gravitational model
constexpr double GM = 3.986004418e14; // Gravitational constant * Earth mass [m^3/s^2]
constexpr double Re = 6378137.0; // Earth's equatorial radius [m]
constexpr double J2 = 1.08262668e-3; // Earth's second zonal harmonic

// Concept to ensure position coordinates are floating-point numbers
template<typename T>
concept ValidPosition = std::floating_point<T>;

template<ValidPosition T>
constexpr std::array<T, 3> calculateGravitationalAcceleration(T x, T y, T z) {
    // Calculate the square of the distance from the Earth's center
    T r2 = x * x + y * y + z * z;
    T r = std::sqrt(r2); // Distance from the Earth's center

    // Gravitational acceleration factor
    T factor = GM / (r2 * r);

    // J2 correction factor
    T factorJ2 = 1.5 * J2 * GM * Re * Re / (r2 * r * r);

    // Gravitational acceleration in x, y, and z directions
    T ax = -factor * x * (1 - factorJ2 * (5 * z * z / r2 - 1));
    T ay = -factor * y * (1 - factorJ2 * (5 * z * z / r2 - 1));
    T az = -factor * z * (1 - factorJ2 * (5 * z * z / r2 - 3));

    return {ax, ay, az};
}

} // namespace J2

#endif // GRAVITATIONAL_MODELS_H


#endif // GRAVITATIONAL_MODELS_H