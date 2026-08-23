#include <array>
#include <chrono>
#include <iostream>
#include <string>

#include <asio.hpp>

#include "app/common/time_helpers.hpp"
#include "model_satellite.hpp"

namespace app {

const std::string LOCALHOST = "127.0.0.1";
const uint SERVER_PORT = 7777;

std::string satelliteMessage(const ModelSatellite& satellite, const std::chrono::system_clock::time_point& timestamp) {
    std::ostringstream message{};
    message << common::TIMEPOINT_TO_STRING(timestamp) << ","
            << satellite.name << ","
            << satellite.position[0] << "," << satellite.position[1] << "," << satellite.position[2] << ","
            << satellite.velocity[0] << "," << satellite.velocity[1] << "," << satellite.velocity[2] << ","
            << satellite.acceleration[0] << "," << satellite.acceleration[1] << "," << satellite.acceleration[2]
            << "\n";

    return message.str();
}

void run(ModelSatellite& satellite) {
    try {
        asio::io_context ioContext;
        asio::ip::udp::socket socket(ioContext);
        socket.open(asio::ip::udp::v4());

        asio::ip::udp::endpoint server(asio::ip::make_address(LOCALHOST), SERVER_PORT);

        uint64_t count = 0;
        while (true) {
            if (count % 60 == 0) {
                std::string message = satelliteMessage(satellite, std::chrono::system_clock::now());
                socket.send_to(asio::buffer(message), server);
            }
            std::this_thread::sleep_for(std::chrono::seconds(1));
            satellite.updateFrame(1);
            ++count;
        }

    }
    catch (std::exception& error) {
        std::cerr << error.what() << "\n";
    }

}

} // namespace app


const double G = 6.67430e-11;
const double M_EARTH = 5.97220e24;
const double MU_EARTH = G * M_EARTH;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "usage: requires a satellite id as argument \n";
        return 1;
    }
    std::string satelliteId = argv[1];

    ModelSatellite* satellite = nullptr;
    if (satelliteId == "geostationary") {
        satellite = new ModelSatellite(satelliteId, MU_EARTH, {4.215700e+07, 0, 0}, {0,  3.074930e+03, 0});
    } else if (satelliteId == "iss") {
        satellite = new ModelSatellite(satelliteId, MU_EARTH, {6.771000e+06, 0, 0}, {0,  4.765830e+03, 6.012981e+03});
    } else if (satelliteId == "polar") {
        satellite = new ModelSatellite(satelliteId, MU_EARTH, {6.971000e+06, 0, 0}, {0,  4.630238e-13, 7.561753e+03});
    } else if (satelliteId == "retrograde-equatorial") {
        satellite = new ModelSatellite(satelliteId, MU_EARTH, {6.771000e+06, 0, 0}, {0, -7.672619e+03, 9.396248e-13});
    } else if (satelliteId == "sun-synchronous") {
        satellite = new ModelSatellite(satelliteId, MU_EARTH, {6.971000e+06, 0, 0}, {0, -1.078525e+03, 7.484443e+03});
    }  else {
        std::cout << "error: satellite id " << satelliteId << " isn't supported \n";
        return 1;
    }

    app::run(*satellite);
}
