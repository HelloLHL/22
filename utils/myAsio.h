//
// Created by 李洪良 on 2023/2/3.
//

#ifndef DAILY_PRACTICE_MYASIO_H
#define DAILY_PRACTICE_MYASIO_H

#include <boost/asio.hpp>
#include <iostream>
#include <boost/thread.hpp>

void handler(const boost::system::error_code &ec) {
    std::cout << " 5 s . " << std::endl;
}

void handler2(const boost::system::error_code &ec) {
    std::cout << " 10 s . " << std::endl;
}

void io1() {
    boost::asio::io_service io_service;
    boost::asio::deadline_timer timer(io_service, boost::posix_time::seconds(5));
    timer.async_wait(handler);
    boost::asio::deadline_timer timer2(io_service, boost::posix_time::seconds(10));
    timer2.async_wait(handler2);
    io_service.run();
}

boost::asio::io_service a_io_service;

void run() {
    a_io_service.run();
}

void io2() {
    boost::asio::deadline_timer timer(a_io_service, boost::posix_time::seconds(5));
    timer.async_wait(handler);
    boost::asio::deadline_timer timer2(a_io_service, boost::posix_time::seconds(5));
    timer2.async_wait(handler2);
    boost::thread thread1(run);
    boost::thread thread2(run);
    thread1.join();
    thread2.join();
}

void callback(const boost::system::error_code &e) {
    cout << "hello world" << endl;
}

void print1(const boost::system::error_code &e,
           boost::asio::deadline_timer *t, int *count) {
    if (*count < 5) {
        cout << *count << endl;
        ++(*count);

        t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
        t->async_wait(
                [t, count](const auto &error) { print1(error, t, count); }
        );
    }
}

void test() {
    boost::asio::io_service io;

    int count = 0;
    auto t = make_shared<boost::asio::deadline_timer>(
            io, boost::posix_time::seconds(1)
    );
    auto pt = t.get();
    t->async_wait(callback);
    t->async_wait(
            boost::bind(print1, boost::asio::placeholders::error, pt, &count)
    );
    t->async_wait([pt, &count](const auto &error) {
        print1(error, pt, &count);
    });
    io.run();


}

#endif //DAILY_PRACTICE_MYASIO_H
