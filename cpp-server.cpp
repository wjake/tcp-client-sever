#include <iostream>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    // Create a socket
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1)
    {
        std::cerr << "Socket creation failed." << '\n';
        return 1;
    }

    // Set server address
    sockaddr_in server_addr;
    std::memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(65432);

    // Bind the socket to the address
    if (bind(server_fd, (sockaddr*)&server_addr, sizeof(server_addr)) == -1)
    {
        std::cerr << "Binding failed." << '\n';
        close(server_fd);
        return 1;
    }

    // Listen for incoming connections
    if (listen(server_fd, 10) == -1)
    {
        std::cerr << "Listening failed." << '\n';
        close(server_fd);
        return 1;
    }
    std::cout << "Server is listening on port 65432..." << '\n';

    // Accept client connection
    sockaddr_in client_addr;
    socklen_t client_addr_len = sizeof(client_addr);
    int client_fd = accept(server_fd, (sockaddr*)&client_addr, &client_addr_len);
    if (client_fd == -1)
    {
        std::cerr << "Accepting connection failed." << '\n';
        close(server_fd);
        return 1;
    }
    std::cout << "Received connection from client: " << client_fd << '\n';

    // Receive message from the client
    char buffer[1024];
    std::memset(buffer, 0, sizeof(buffer));
    ssize_t bytes_received = recv(client_fd, buffer, sizeof(buffer) - 1, 0);
    if (bytes_received == -1)
    {
        std::cerr << "Receiving data failed." << '\n';
        close(client_fd);
        close(server_fd);
        return 1;
    }
    std::cout << "Received messages from client " << client_fd << ": " << buffer << '\n';

    // Send confirmation response to the client
    const char* response = "Message received.";
    send(client_fd, response, std::strlen(response), 0);

    // Close the sockets
    close(client_fd);
    close(server_fd);
    std::cout << "Closed port 65432." << '\n';

    return EXIT_SUCCESS;
}