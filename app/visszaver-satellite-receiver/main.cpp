#include <array>
#include <iostream>
#include <string>

#include <asio.hpp>
#include <pqxx/pqxx>

#include "app/common/time_helpers.hpp"
#include "app/visszaver-api/satellite_telemetry.hpp"

namespace app {

const uint LISTENER_PORT = 7777;
const uint BUFFER_SIZE_BYTES = 4096;
const char* DB_HOST = "localhost";
const char* DB_PORT = "5432";

SatelliteTelemetry satelliteMessageParser(const std::string& message) {
    std::array<std::string, 11> fields;

    size_t count = 0;
    std::string temp;
    for (size_t i = 0; i < message.size(); ++i) {
        if (message[i] != ',') {
            temp.push_back(message[i]);
        } else {
            fields[count] = temp;
            temp = "";
            ++count;
        }
    }
    fields[10] = temp;

    double x = std::stod(fields[2]);
    double y = std::stod(fields[3]);
    double z = std::stod(fields[4]);
    double vx = std::stod(fields[5]);
    double vy = std::stod(fields[6]);
    double vz = std::stod(fields[7]);
    double ax = std::stod(fields[8]);
    double ay = std::stod(fields[9]);
    double az = std::stod(fields[10]);

    return SatelliteTelemetry(
            common::STRING_TO_TIMEPOINT(fields[0]),
            fields[1],
            {x, y, z},
            {vx, vy, vz},
            {ax, ay, az}
    );
}

void run() {

    const char* dbName = std::getenv("POSTGRES_DB");
    if (!dbName) {
        throw std::runtime_error(std::string("Missing env var: POSTGRES_DB"));
    }

    const char* dbUser = std::getenv("POSTGRES_USER");
    if (!dbUser) {
        throw std::runtime_error(std::string("Missing env var: POSTGRES_USER"));
    }

    const char* dbPassword = std::getenv("POSTGRES_PASSWORD");
    if (!dbPassword) {
        throw std::runtime_error(std::string("Missing env var: POSTGRES_PASSWORD"));
    }

    std::string connectionString =
            std::string("host=") + DB_HOST +
            " port=" + DB_PORT +
            " dbname=" + dbName +
            " user=" + dbUser +
            " password=" + dbPassword;

    try {
        pqxx::connection conn(connectionString);
        std::cout << "connected to database: " << conn.dbname() << "\n";

        asio::io_context ioContext;
        asio::ip::udp::socket socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), LISTENER_PORT));

        while (true) {
            std::array<char, BUFFER_SIZE_BYTES> recvBuf{};
            asio::ip::udp::endpoint remoteEndpoint;

            std::size_t bytesReceived = socket.receive_from(
                    asio::buffer(recvBuf),
                    remoteEndpoint
            );

            std::string message(recvBuf.data(), bytesReceived);

            std::cout << bytesReceived << " bytes from " << remoteEndpoint.address().to_string()
                      << ":" << remoteEndpoint.port() << " -- " << message;

            SatelliteTelemetry satellite = satelliteMessageParser(message);

            pqxx::work txn(conn);
            txn.exec_params(R"(
                INSERT INTO satellite_telemetry_timeseries (
                    timestamp, name,
                    pos_x, pos_y, pos_z,
                    vel_x, vel_y, vel_z,
                    acc_x, acc_y, acc_z
                )
                VALUES (
                    $1, $2,
                    $3, $4, $5,
                    $6, $7, $8,
                    $9, $10, $11
                ))",
                common::TIMEPOINT_TO_STRING(satellite.timestamp),
                satellite.name,
                satellite.position[0], satellite.position[1], satellite.position[2],
                satellite.velocity[0], satellite.velocity[1], satellite.velocity[2],
                satellite.acceleration[0], satellite.acceleration[1], satellite.acceleration[2]
            );

            txn.commit();

        }
    }
    catch (std::exception& error) {
        std::cerr << error.what() << "\n";
    }
}

} // namespace app


int main() {
    app::run();
}
