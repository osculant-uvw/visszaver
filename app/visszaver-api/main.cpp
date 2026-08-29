#include <iostream>
#include <string>
#include <vector>

#include <pqxx/pqxx>

#include "app/common/time_helpers.hpp"
#include "satellite_telemetry.hpp"


namespace app {

const char* DB_HOST = "localhost";
const char* DB_PORT = "5432";


void run() {

    std::cout << "libpqxx version: "
              << PQXX_VERSION_MAJOR << "."
              << PQXX_VERSION_MINOR << "\n";

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

    std::vector<SatelliteTelemetry> top10;

    try {
        pqxx::connection conn(connectionString);
        std::cout << "connected to database: " << conn.dbname() << "\n";

        std::string QUERY = R"(
            SELECT
                timestamp,
                name,
                pos_x, pos_y, pos_z,
                vel_x, vel_y, vel_z,
                acc_x, acc_y, acc_z
            FROM satellite_telemetry_timeseries
            ORDER BY (timestamp)
            DESC LIMIT 10;
        )";
        pqxx::work txn(conn);
        pqxx::result result = txn.exec(QUERY);
        txn.commit();

        for (const auto& row : result) {
            top10.push_back({
                common::STRING_TO_TIMEPOINT(row[0].as<std::string>()),
                row[1].as<std::string>(),
                {row[2].as<double>(), row[3].as<double>(), row[4].as<double>()},
                {row[5].as<double>(), row[6].as<double>(), row[7].as<double>()},
                {row[8].as<double>(), row[9].as<double>(), row[10].as<double>()}
            });
        }

        conn.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to query database: " << e.what() << "\n";
    }

    std::cout << "last 10 rows from satellite_telemetry_timeseries in descending order \n";
    for (const auto& satellite: top10) {

        std::ostringstream message{};
        message << common::TIMEPOINT_TO_STRING(satellite.timestamp) << ","
                << satellite.name << ","
                << satellite.position[0] << "," << satellite.position[1] << "," << satellite.position[2] << ","
                << satellite.velocity[0] << "," << satellite.velocity[1] << "," << satellite.velocity[2] << ","
                << satellite.acceleration[0] << "," << satellite.acceleration[1] << "," << satellite.acceleration[2]
                << "\n";

        std::cout << message.str();
    }

}

} // namespace app


int main() {
    app::run();
}
