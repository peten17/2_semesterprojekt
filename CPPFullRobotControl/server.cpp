#include "server.h"

#define PORT 8080
Server::Server()
{
    std::string msg = "Hello from server you fucking cunt";
    _hello  = &msg[0u];
    //Standard for Linux:
    _address.sin_family = AF_INET;
    //Vælger porten. htons(),  converts the unsigned short integer hostshort from host byte order to network byte order.
    _address.sin_port = htons(PORT);
    //Sætter IP-adressen. INADDR_ANY = 0.0.0.0, alle adresser kan forbinde.
    _address.sin_addr.s_addr = INADDR_ANY;
}

Server::Server(char *hello, const int port, const char ip[15])
{
    _hello = hello;
    _address.sin_family = AF_INET;
    _address.sin_port = htons(port);
    inet_pton(_address.sin_family, ip, &(_address.sin_addr));
}

void Server::serverBind()
{
    // Creating socket file descriptor
    // socket(int DOMAIN, int TYPE, int PROTOCOL)
    // Domain: AF_INET = IPV4 internet protocols
    // Type: SOCK_STREAM = Provides sequenced, reliable,
    // two-way, connection-based byte streams.
    // Protocol: 0, standard
    if ((_server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    //Forcefully attaching socket to the port 8080
    //setsockopt(int socket, int level, int option_name, cont void*
    //option_value, socklen_t option length);
    //Socket: referencing earlier server which was setup
    //Level: defines where the function searches for the socket
    //Option_name: Socket option, SO_REUSEADDR = forcibly connect the socket to a port.
    //SO_REUSEPORT = Reuse a port.
    //option_value: 1, to open up for a boolean value
    if (setsockopt(_server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                   &_opt, sizeof(_opt)))
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    // Forcefully attaching socket to the port 8080
    // bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen)
    // Sockfd: choose the socket that should be binded.
    // *addr: choose the structure where the IP and port should be optained from
    // addrlen: the size of *addr in bytes.
    if (bind(_server_fd, (struct sockaddr *)&_address, sizeof(_address)) < 0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

std::string Server::serverListen()
{
    //Places the specified socket in lisetning mode
    //listen(int sockfd, int backLog)
    //sockfd = choose the socket to open lisetning for
    //backLog = how many pending connection requests that are allowed per time.
    if (listen(_server_fd, 3) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accepts a connection to the specified socket
    //accept(int sockfd, struckt sockaddr *addr, socklen_t *addrLen)
    //sockfd = choose the socket to accept a connection.
    //*addr = choose the structure where the IP and port should be optained from
    //addren = returns the size of *addr in bytes
    if ((_new_socket = accept(_server_fd, (struct sockaddr *)&_address, (socklen_t*)&_addrlen)) < 0)
    {
        perror("accept");
        exit(EXIT_FAILURE);
    }

    //Reads the data from a connected client
    //read(int socket, void *buf, ssize_t N)
    //socket: specifies the socket to read from.
    //*buf: pointer to buffer that receives the data
    //N: the length in bytes of the buffer pointed to by the *buf parameter
    _valread = read(_new_socket , _buffer, 1024);
    std::cout << "%s\n" << _buffer << std::endl;

    //Sends a message to the connected client
    //send(int socket, const void *buf, size_t length, flags)
    //socket: chooses the socket to send information on
    //*buf: pointer to the buffer which contains the send message
    //length: the length of the buffer.
    //flag: ??
    send(_new_socket , _hello , strlen(_hello) , 0);
    std::cout << "Hello message sent." << std::endl;

    return _buffer;
}
