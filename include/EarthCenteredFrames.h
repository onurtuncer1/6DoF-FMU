

#include <cmath>
#include <iostream>

constexpr double PI = 3.141592653589793;
constexpr double DEG_TO_RAD = PI / 180.0;
constexpr double EARTH_SEMI_MAJOR_AXIS = 6378137.0; // WGS84 (meters)
constexpr double EARTH_ECCENTRICITY = 0.081819190842622; // WGS84

// Convert latitude, longitude, and altitude to ECEF coordinates
void latLonAltToEcef(double lat, double lon, double alt, double& x, double& y, double& z) {
    double lat_rad = lat * DEG_TO_RAD;
    double lon_rad = lon * DEG_TO_RAD;

    double N = EARTH_SEMI_MAJOR_AXIS / std::sqrt(1 - EARTH_ECCENTRICITY * EARTH_ECCENTRICITY * std::sin(lat_rad) * std::sin(lat_rad));

    x = (N + alt) * std::cos(lat_rad) * std::cos(lon_rad);
    y = (N + alt) * std::cos(lat_rad) * std::sin(lon_rad);
    z = ((1 - EARTH_ECCENTRICITY * EARTH_ECCENTRICITY) * N + alt) * std::sin(lat_rad);
}

// Convert ECEF coordinates to ECI coordinates
std::array<double, 3> ecefToEci(double x, double y, double z, double time_since_epoch) {
    // Calculate the Earth's rotation angle in radians
    double earth_rotation_rate = 2 * PI / 86400.0; // radians per second
    double theta = earth_rotation_rate * time_since_epoch;
    
    // Rotation matrix components
    double cos_theta = std::cos(theta);
    double sin_theta = std::sin(theta);
    
    // Perform the rotation
    double x_eci =  cos_theta * x + sin_theta * y;
    double y_eci = -sin_theta * x + cos_theta * y;
    double z_eci = z; // Z-coordinate is unchanged

    return {x_eci, y_eci, z_eci};
}
