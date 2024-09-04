/*
 * -----------------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [AtmoshpericModels.h]
 * Author:      Onur Tuncer, PhD
 * Email:       onur.tuncer@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronuatics and Astronautics
 *
 * Description:
 * [Routines to perform atmospheric model calculations]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * ----------------------------------------------------------------------------------- 
 */

#ifndef ATMOSPHERIC_MODELS_H
#define ATMOSPHERIC_MODELS_H

#include <iostream>
#include <cmath>
#include <array>
#include <ranges>
#include <concepts>
#include <limits> // For std::numeric_limits<double>::quiet_NaN()

namespace US1976{

// Constants for the US1976 model
constexpr double R = 287.05;  // Specific gas constant for dry air [J/(kg·K)]
constexpr double g0 = 9.80665; // Standard acceleration of gravity [m/s²]

// Layer definitions for the US1976 model
struct Layer {
    double altitude_min; // Minimum altitude for the layer [m]
    double altitude_max; // Maximum altitude for the layer [m]
    double temperature_base; // Base temperature of the layer [K]
    double temperature_gradient; // Temperature gradient of the layer [K/m]
    double pressure_base; // Base pressure of the layer [Pa]
};

// Define the layers of the US1976 atmosphere
constexpr std::array<Layer, 6> layers = {{
    {0, 11000, 288.15, -0.00649, 101325}, // Troposphere
    {11000, 20000, 216.65, 0.001, 22632.06}, // Stratosphere
    {20000, 32000, 216.65, 0.0028, 5474.89}, // Upper Stratosphere
    {32000, 47000, 228.65, 0.0000, 868.02}, // Mesosphere
    {47000, 51000, 270.65, 0.0028, 110.91}, // Upper Mesosphere
    {51000, 71000, 270.65, 0.0, 66.94} // Thermosphere
}};

// template<typename T>
// concept ValidAltitude = std::floating_point<T>;

template<typename T>
constexpr T Temperature(T altitude) {
    for (const auto& layer : layers) {
        if (altitude >= layer.altitude_min && altitude <= layer.altitude_max) {
            return layer.temperature_base + layer.temperature_gradient * (altitude - layer.altitude_min);
        }
    }
     return std::numeric_limits<T>::quiet_NaN(); // Return NaN if altitude is out of range
}

template<typename T>
constexpr T Pressure(T altitude) {
    for (const auto& layer : layers) {
        if (altitude >= layer.altitude_min && altitude <= layer.altitude_max) {
            T T0 = layer.temperature_base;
            T P0 = layer.pressure_base;
            T L = layer.temperature_gradient;
            T Te = Temperature(altitude);
            
            // Calculate pressure using the barometric formula
            if (L != 0) {
                return P0 * std::pow((Te / T0), (g0 / (R * L)));
            } else {
                return P0 * std::exp(-g0 * (altitude - layer.altitude_min) / (R * T0));
            }
        }
    }
    return std::numeric_limits<T>::quiet_NaN(); // Return NaN if altitude is out of range
}

template<typename T>
constexpr T Density(T altitude) {
    T Te = Temperature(altitude);
    T P = Pressure(altitude);
    return P / (R * Te);
}

}//namespace US1976

#endif // ATMOSPHERIC_MODELS_H