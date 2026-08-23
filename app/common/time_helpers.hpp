#include <chrono>
#include <iomanip>
#include <string>

namespace common {

const auto STRING_TO_TIMEPOINT = [](const std::string &timestamp) {
    std::istringstream stream(timestamp);
    std::tm tm{};
    stream >> std::get_time(&tm, "%Y-%m-%d %H:%M:%S");
    return std::chrono::system_clock::from_time_t(timegm(&tm));
};

const auto TIMEPOINT_TO_STRING = [](const std::chrono::system_clock::time_point &timestamp) {
    std::time_t time = std::chrono::system_clock::to_time_t(timestamp);
    std::ostringstream stream{};
    stream << std::put_time(gmtime(&time), "%Y-%m-%d %H:%M:%S");
    return stream.str();
};

} // namespace common
