//
// Created by hongliang11 on 2023/3/8.
//

#ifndef DAILY_PRACTICE_MYSOCKETCLIENT_H
#define DAILY_PRACTICE_MYSOCKETCLIENT_H
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstring>
#include <unistd.h>

int socketClinetMain() {
    struct sockaddr_in sa;
    int res;
    int SocketFd = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (-1==SocketFd)
    {
        /* code */
        perror("cannot create socket");
        exit(EXIT_FAILURE);
    }

    memset(&sa,0,sizeof sa);

    sa.sin_family = AF_INET;
    sa.sin_port = htons(2222);
    
    res = inet_pton(AF_INET, "192.168.1.9", &sa.sin_addr);

    if (-1==connect(SocketFd, (struct sockaddr*)&sa, sizeof sa)) {
        /* code */
        perror("connect create socket");
        close(SocketFd);
        exit(EXIT_FAILURE);
    }

    char buffer[512];
    int totalRead = 0;
    for (;;)
    {
        /* code */
        int readsize =0;
        readsize = read(SocketFd, buffer+totalRead, sizeof(buffer)-totalRead);
        if (readsize == 0)
        {
            /* code */
            break;
        } else if(readsize==-1) {
            perror("read create socket");
            close(SocketFd);
            exit(EXIT_FAILURE);
        }
        totalRead += readsize;
    }
    buffer[totalRead] = 0;
    printf("get from server:%s\n", buffer);
    (void)shutdown(SocketFd, SHUT_RDWR);
    close(SocketFd);
    return EXIT_SUCCESS;
}





#endif //DAILY_PRACTICE_MYSOCKETCLIENT_H
