//
// Created by 李洪良 on 2023/2/7.
//

#ifndef DAILY_PRACTICE_MYSPDLOG_H
#define DAILY_PRACTICE_MYSPDLOG_H
#include <iostream>
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/sinks/rotating_file_sink.h"


void spdlogTest() {
    try {
        /*
        auto max_size = 25600;
        auto max_files = 3;
        auto logger = spdlog::rotating_logger_mt("some_logger_name", "logs/rotating.txt", max_size, max_files);
        for (int i=0; i<10000; i++) {
            logger->info("{} * {} equals {:>10}",i, i, i*i);
        }
         */

        auto my_logger = spdlog::basic_logger_mt("file_logger", "logs/basic-log.txt");
        my_logger->set_level(spdlog::level::trace);
        my_logger->info("hello,{}!", "world");
        my_logger->info("hello,rizhi!");

    } catch (const spdlog::spdlog_ex &ex) {
        std::cout << "error" << std::endl;
        std::cout << "Log init failed: " << ex.what() << std::endl;
    }
    // spdlog::error("hello,{}!", "world");
}


#endif //DAILY_PRACTICE_MYSPDLOG_H
