/*
 * ----------------------------------------------------------------------------
 * Project:     [EBEK]
 * File:        [testJ2000Timing.cpp]
 * Author:      Onur Tuncer, PhD
 * Email:       tuncero@itu.edu.tr
 * Institution: Istanbul Technical University
 *              Faculty of Aeronautics and Astronuatics
 * 
 * Date:        2024
 *
 * Description:
 * [Routines to aid with calculations with J2000 epoch]
 *
 * License:
 * [See License.txt in the top level directory for licence and copyright information]
 *
 * ----------------------------------------------------------------------------
 */

#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "J2000.h"

TEST_CASE("Julian Date Calculation") {
    // Test cases for Julian Date calculation
    REQUIRE(dateToJulianDate(2000, 1, 1, 12, 0, 0) == Approx(J2000_JULIAN_DATE).epsilon(1e-10));
    
    // Test cases for dates that are known
    // January 1, 2000, 00:00:00 UTC
    REQUIRE(dateToJulianDate(2000, 1, 1, 0, 0, 0) == Approx(J2000_JULIAN_DATE - 0.5).epsilon(1e-10));
    
    // Example known date for testing
    // July 20, 1969, 20:17:40 UTC (Apollo 11 Moon Landing)
    REQUIRE(dateToJulianDate(1969, 7, 20, 20, 17, 40) == Approx(2438566.344444444).epsilon(1e-10));
}

TEST_CASE("Time Since J2000 Calculation") {
    // Test cases for time since J2000 epoch
    REQUIRE(timeSinceJ2000(2000, 1, 1, 12, 0, 0) == Approx(0.0).epsilon(1e-10));
    
    // Test cases for known time intervals
    // January 1, 2000, 00:00:00 UTC
    // Time since J2000 in seconds: (0.5 days * 86400 seconds/day)
    REQUIRE(timeSinceJ2000(2000, 1, 1, 0, 0, 0) == Approx(-43200.0).epsilon(1e-10));
    
    // July 20, 1969, 20:17:40 UTC
    // Known Julian Date for testing: 2438566.344444444
    // Time since J2000 in seconds: (2438566.344444444 - 2451545.0) * 86400
    REQUIRE(timeSinceJ2000(1969, 7, 20, 20, 17, 40) == Approx(-2411927040.0).epsilon(1e-10));
}
