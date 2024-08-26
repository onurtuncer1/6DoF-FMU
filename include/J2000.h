/*
 * ----------------------------------------------------------------------------
 * Project:     [6DoF]
 * File:        [J2000.h]
 * Author:      Onur Tuncer, PhD
 * Email:       tuncero@itu.edu.tr
 * Institution: Istanbul Technical University
 *
 * Description:
 * [Brief description of the file's purpose and functionality]
 *
 * License:
 * [Specify the license under which this code is distributed, if applicable]
 *
 * ----------------------------------------------------------------------------
 * /

#ifndef J2000_H
#define J2000_H

#include <iostream>
#include <cmath>
#include <ctime>

// Julian Date for J2000 epoch
constexpr double J2000_JULIAN_DATE = 2451545.0;

// Function to calculate Julian Date from a given date
double dateToJulianDate(int year, int month, int day, int hour, int minute, int second) {

    // Adjust months and year for Gregorian calendar
    if (month <= 2) {
        month += 12;
        year -= 1;
    }
    
    int A = year / 100;
    int B = 2 - A + (A / 4);
    
    double julianDate = std::floor(365.25 * (year + 4716)) +
                        std::floor(30.6001 * (month + 1)) +
                        day + B - 1524.5 +
                        (hour / 24.0) + (minute / 1440.0) + (second / 86400.0);
    
    return julianDate;
}

// Function to calculate time since J2000 epoch in seconds
double timeSinceJ2000(int year, int month, int day, int hour, int minute, int second) {

    double julianDate = dateToJulianDate(year, month, day, hour, minute, second);
    double timeSinceEpoch = (julianDate - J2000_JULIAN_DATE) * 86400.0; // Convert days to seconds
    return timeSinceEpoch;
}

#endif // J2000_H