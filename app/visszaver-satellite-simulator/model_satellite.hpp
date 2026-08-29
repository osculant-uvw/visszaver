#include <array>
#include <cmath>
#include <string>

using Vector3 = std::array<double, 3>;

class ModelSatellite {
public:

    ModelSatellite(const std::string& name, const double mu, const Vector3& position, const Vector3& velocity)
        : name(name), mu(mu), position(position), velocity(velocity)
        { acceleration = getAcceleration(); }


    /*
     * Updated frame moves the model forward using a component-wise Velocity Verlet Integrator
     */
    void updateFrame(double timestep_s) {
        position[0] += velocity[0] * timestep_s + 0.5 * acceleration[0] * std::pow(timestep_s, 2);
        position[1] += velocity[1] * timestep_s + 0.5 * acceleration[1] * std::pow(timestep_s, 2);
        position[2] += velocity[2] * timestep_s + 0.5 * acceleration[2] * std::pow(timestep_s, 2);

        Vector3 updatedAcceleration = getAcceleration();

        velocity[0] += 0.5 * (acceleration[0] + updatedAcceleration[0]) * timestep_s;
        velocity[1] += 0.5 * (acceleration[1] + updatedAcceleration[1]) * timestep_s;
        velocity[2] += 0.5 * (acceleration[2] + updatedAcceleration[2]) * timestep_s;

        acceleration = updatedAcceleration;
    }


    const std::string name;
    const double mu;

    Vector3 position;
    Vector3 velocity;
    Vector3 acceleration;

private:

    Vector3 getAcceleration() {
        double norm = std::sqrt(
                std::pow(position[0], 2) + std::pow(position[1], 2) + std::pow(position[2], 2)
        );

        double a1 = -mu * position[0] / std::pow(norm, 3);
        double a2 = -mu * position[1] / std::pow(norm, 3);
        double a3 = -mu * position[2] / std::pow(norm, 3);

        return Vector3 {a1, a2, a3};
    }

};
