//
// Created by 李洪良 on 2023/3/9.
//
#include <iostream>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <errno.h>
#include <unistd.h>

int socketServerMain() {
    char hello[] = "hello world";
    struct sockaddr_in sa;
    int SockerFD = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);

    if (-1 == SockerFD) {
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }
    memset(&sa, 0, sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(2222);
    sa.sin_addr.s_addr = htonl(INADDR_ANY);

    if (-1 == bind(SockerFD, (struct sockaddr *) &sa, sizeof sa)) {
        perror("bind fail");
        close(SockerFD);
        exit(EXIT_FAILURE);
    }
    if (-1 == listen(SockerFD, 10)) {
        perror("listen fail");
        close(SockerFD);
        exit(EXIT_FAILURE);
    }

    for (;;) {
        int ConnectFD = accept(SockerFD, NULL, NULL);
        std::cout << ConnectFD << std::endl;
        if (0 > ConnectFD) {
            perror("accept fail");
            close(SockerFD);
            exit(EXIT_FAILURE);
        }

        std::cout << "accept success" << std::endl;
        int writeSize = 0;
        size_t totalWrite = 0;
        while (totalWrite < sizeof(hello)) {
            writeSize = write(ConnectFD, hello + totalWrite, sizeof(hello) - totalWrite);
            std::cout << "-----" << errno << std::endl;

            if (-1 == writeSize) {
                perror("write fail");
                close(ConnectFD);
                close(SockerFD);
                exit(EXIT_FAILURE);
            }
            totalWrite += writeSize;
        }
        if (-1 == shutdown(ConnectFD, SHUT_RDWR)) {
            perror("shutdown fail");
            close(ConnectFD);
            close(SockerFD);
            exit(EXIT_FAILURE);
        }
        close(ConnectFD);
    }
    close(SockerFD);
    return EXIT_SUCCESS;
}

int main() {
    socketServerMain();
}