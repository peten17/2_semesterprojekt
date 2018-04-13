#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <wchar.h>

class Server
{
public:
    Server();
    Server(char *hello, const int port, const char ip);

    std::string serverListen();
    void serverBind();

private:
   int _server_fd, _new_socket, _valread;
   struct sockaddr_in _address;
   int _opt = 1;
   int _addrlen = sizeof(_address);
   char _buffer[1024] = {0};
   char *_hello;
};

#endif // SERVER_H
