#pragma once

#include <string>
#include <chrono>
#include <stdexcept>

class SatelliteTelemetry {
public:
    SatelliteTelemetry(
            const std::string satelliteId,
            const std::chrono::system_clock::time_point timeReceived,
            const double latitude_deg,
            const double longitude_deg,
            const double altitude_m,
            const double speed_m_s,
            const double temperature_K
    ):
            satelliteId(satelliteId),
            timeReceived(timeReceived),
            latitude(latitude_deg),
            longitude(longitude_deg),
            altitude(altitude_m),
            speed(speed_m_s),
            temperature(temperature_K)
    {
        if (latitude < -90.0 || latitude > 90.0) {
            throw std::invalid_argument(
                    "Latitude must be between [-90, 90] degrees, received: " + std::to_string(latitude)
            );
        }

        if (longitude < -180.0 || longitude > 180.0) {
            throw std::invalid_argument(
                    "Longitude must be between [-180, 180] degrees, received: " + std::to_string(longitude)
            );
        }
    }

    const std::string satelliteId;
    const std::chrono::system_clock::time_point timeReceived;
    const double latitude;
    const double longitude;
    const double altitude;
    const double speed;
    const double temperature;
};
