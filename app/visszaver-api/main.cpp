#include <iostream>
#include <string>
#include <vector>

#include <pqxx/pqxx>

#include "app/common/time_helpers.hpp"
#include "domain/telemetry.hpp"


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
                satellite_id,
                received_at,
                latitude_degrees,
                longitude_degrees,
                altitude_metres,
                speed_metres_per_second,
                temperature_kelvin
            FROM telemetry_timeseries
            ORDER BY (received_at)
            DESC LIMIT 10;
        )";
        pqxx::work txn(conn);
        pqxx::result result = txn.exec(QUERY);
        txn.commit();

        for (const auto& row : result) {
            top10.emplace_back(
                    row[0].as<std::string>(),
                    common::STRING_TO_TIMEPOINT(row[1].as<std::string>()),
                    row[2].as<double>(),
                    row[3].as<double>(),
                    row[4].as<double>(),
                    row[5].as<double>(),
                    row[6].as<double>()
            );
        }

        conn.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to query database: " << e.what() << "\n";
    }

    std::cout << "last 10 rows from telemetry_timeseries in descending order \n";
    for (const auto& item: top10) {
        std::cout << item.satelliteId << " "
                  << common::TIMEPOINT_TO_STRING(item.timeReceived) << " "
                  << item.latitude << " "
                  << item.longitude << " "
                  << item.altitude << " "
                  << item.speed << " "
                  << item.temperature << "\n";
    }

}

} // namespace app


int main() {
    app::run();
}
