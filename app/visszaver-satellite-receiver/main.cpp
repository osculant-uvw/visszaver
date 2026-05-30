#include <array>
#include <iostream>
#include <string>

#include <asio.hpp>

namespace app {

const uint LISTENER_PORT = 7777;
const uint BUFFER_SIZE_BYTES = 4096

void run() {
    try {
        asio::io_context ioContext;
        asio::ip::udp::socket socket(ioContext, asio::ip::udp::endpoint(asio::ip::udp::v4(), LISTENER_PORT));

        while (true) {
            std::array<char, BUFFER_SIZE_BYTES> recvBuf{};
            asio::ip::udp::endpoint remoteEndpoint;

            std::size_t bytesReceived = socket.receive_from(
                    asio::buffer(recvBuf),
                    remoteEndpoint
            );

            std::cout << bytesReceived << " bytes from "
                      << remoteEndpoint.address().to_string()
                      << ":" << remoteEndpoint.port() << "\n";

            std::cout.write(recvBuf.data(), bytesReceived);
            std::cout << "\n";

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
