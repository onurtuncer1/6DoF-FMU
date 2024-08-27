


#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>
#include "gravitational_models.h"

namespace J2 = J2; // Alias for convenience

// Helper function to check if two arrays are approximately equal
template<typename T, size_t N>
bool approxEqual(const std::array<T, N>& a, const std::array<T, N>& b, T epsilon = 1e-6) {
    for (size_t i = 0; i < N; ++i) {
        if (std::abs(a[i] - b[i]) > epsilon) {
            return false;
        }
    }
    return true;
}

TEST_CASE("J2 Gravitational Model - calculateGravitationalAcceleration") {
    // Example position at Earth's equatorial surface
    const double x = J2::Re;
    const double y = 0.0;
    const double z = 0.0;

    // Calculate gravitational acceleration at the example position
    auto result = J2::calculateGravitationalAcceleration(x, y, z);

    // Expected results based on known values or theoretical calculations
    std::array<double, 3> expected = {-9.8196, 0.0, 0.0}; // Example expected values

    REQUIRE(approxEqual(result, expected, 1e-4));
}

TEST_CASE("J2 Gravitational Model - calculateGravitationalAcceleration with non-zero z") {
    // Example position at Earth's surface but with a non-zero z
    const double x = J2::Re;
    const double y = 0.0;
    const double z = 1000.0; // 1 km above the equator

    // Calculate gravitational acceleration at the example position
    auto result = J2::calculateGravitationalAcceleration(x, y, z);

    // Expected results based on known values or theoretical calculations
    std::array<double, 3> expected = {-9.8194, 0.0, -0.0132}; // Example expected values

    REQUIRE(approxEqual(result, expected, 1e-4));
}

TEST_CASE("J2 Gravitational Model - calculateGravitationalAcceleration with general position") {
    // Example position with non-zero x, y, and z
    const double x = 7000000.0; // 7000 km from Earth's center
    const double y = 3000000.0; // 3000 km from Earth's center
    const double z = 2000000.0; // 2000 km from Earth's center

    // Calculate gravitational acceleration at the example position
    auto result = J2::calculateGravitationalAcceleration(x, y, z);

    // Expected results based on known values or theoretical calculations
    std::array<double, 3> expected = {
        -9.1974, // Example expected values
        -4.6987,
        -1.1823
    };

    REQUIRE(approxEqual(result, expected, 1e-4));
}
