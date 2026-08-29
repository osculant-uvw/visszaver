#pragma once

#include <array>
#include <chrono>
#include <string>

using Vector3 = std::array<double, 3>;

class SatelliteTelemetry {
public:
    SatelliteTelemetry(
        const std::chrono::system_clock::time_point& timestamp,
        const std::string& name,
        const Vector3& position,
        const Vector3& velocity,
        const Vector3& acceleration
    ) : timestamp(timestamp), name(name), position(position), velocity(velocity), acceleration(acceleration) {}

    const std::chrono::system_clock::time_point timestamp;
    const std::string name;
    const Vector3 position;
    const Vector3 velocity;
    const Vector3 acceleration;

};
