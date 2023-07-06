//
// Created by 李洪良 on 2023/7/5.
//

#ifndef DAILY_PRACTICE_SELECT_POLL_EPOLL_H
#define DAILY_PRACTICE_SELECT_POLL_EPOLL_H

#include <iostream>
#include <cstdlib>
#include <unistd.h>
#include <sys/select.h>
#include <sys/poll.h>
//#include <sys/epoll.h>


int test_select() {
    fd_set read_fds;

    timeval timeout;
    timeout.tv_sec = 5;
    timeout.tv_usec = 0;

    std::cout << "等待输入....\n";

    while (true) {
        FD_ZERO(&read_fds);
        FD_SET(STDIN_FILENO, &read_fds);

        int activity = select(STDIN_FILENO + 1, &read_fds, nullptr, nullptr, &timeout);
        if (activity == -1) {
            std::cerr << "select error\n";
            exit(EXIT_FAILURE);
        } else if (activity == 0) {
            std::cout << "timeout\n";
            continue;
        }

        if (FD_ISSET(STDIN_FILENO, &read_fds)) {
            char input[1024];

            std::cin.getline(input, sizeof input);

            std::cout << "input:" << input << "\n";
            if (strcmp(input, "exit") == 0) {
                break;
            }
        }
    }

    std::cout << "end\n";
    return 0;
}


int test_poll() {
    const int MAX_EVENTS=2;
    const int TIMEOUT=5000;
    struct pollfd fds[MAX_EVENTS];

    fds[0].fd=STDIN_FILENO;
    fds[0].events=POLLIN;

    fds[1].fd=STDOUT_FILENO;
    fds[1].events = POLLOUT;

    std::cout<<"等待IO操作。。。。"<<std::endl;

    int ret = poll(fds, MAX_EVENTS, TIMEOUT);

    if(ret==-1) {
        std::cerr<<"poll()失败"<<std::endl;
        return 1;
    }

    if(ret==0) {
        std::cout<<"超时，无IO事件发生"<<std::endl;
    } else{
        if(fds[0].revents & POLLIN) {
            std::cout<<"标准输入可读"<<std::endl;
        }
        if(fds[1].revents & POLLOUT) {
            std::cout<<"标准输入可写"<<std::endl;
        }
    }
#ifdef __APPLE__
    std::cout<<"apple系统"<<std::endl;
#endif

    return 0;
}


int test_epoll() {
#define MAX_EVENTS 10
#ifdef __linux__
    int epoll_fd, num_events;
    struct epoll_event event, events[MAX_EVENTS];

    // 创建epoll实例
    epoll_fd = epoll_create1(0);
    if (epoll_fd == -1) {
        std::cerr << "Failed to create epoll instance" << std::endl;
        return 1;
    }

    // 设置监听的文件描述符
    event.data.fd = STDIN_FILENO;  // 监听标准输入
    event.events = EPOLLIN;

    // 将标准输入文件描述符添加到epoll实例中
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, STDIN_FILENO, &event) == -1) {
        std::cerr << "Failed to add file descriptor to epoll instance" << std::endl;
        close(epoll_fd);
        return 1;
    }

    while (true) {
        // 等待事件发生
        num_events = epoll_wait(epoll_fd, events, MAX_EVENTS, -1);
        if (num_events == -1) {
            std::cerr << "epoll_wait failed" << std::endl;
            close(epoll_fd);
            return 1;
        }

        // 处理事件
        for (int i = 0; i < num_events; ++i) {
            if (events[i].data.fd == STDIN_FILENO) {
                // 读取输入
                std::string input;
                std::getline(std::cin, input);

                // 输出输入内容
                std::cout << "Input: " << input << std::endl;

                // 如果输入为"quit"，退出程序
                if (input == "quit") {
                    close(epoll_fd);
                    return 0;
                }
            }
        }
    }
#endif
    return 0;

}

#endif //DAILY_PRACTICE_SELECT_POLL_EPOLL_H
