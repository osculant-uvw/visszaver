#include <iostream>
#include <string>
#include <pqxx/pqxx>

#include "app.hpp"

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

    try {
        pqxx::connection conn(connectionString);
        std::cout << "connected to database: " << conn.dbname() << "\n";

        std::string QUERY = "SELECT version();";
        pqxx::work txn(conn);
        pqxx::result result = txn.exec(QUERY);
        txn.commit();
        for (const auto& row : result) {
            std::cout << row[0].c_str() << "\n";
        }

        conn.disconnect();
    }
    catch (const std::exception& e) {
        std::cerr << "Failed to query database: " << e.what() << "\n";
    }

}

} // namespace app
