//
// Created by 李洪良 on 2022/10/10.
//

#ifndef DAILY_PRACTICE_MYTIME_H
#define DAILY_PRACTICE_MYTIME_H
#include <chrono>
#include <string>
#include <iostream>
#include <iomanip>
#include <random>


class myTime {
public:
    // 获取指定时间的时间点
    std::chrono::system_clock::time_point makeTimePoint(int year,int mon, int day,int hour, int min, int sec = 0);

    // 格式化时间点
    std::string asString(const std::chrono::system_clock::time_point & tp);

    // 获取当前时间的时间戳 （微秒）
    time_t getCurrentTimeStamp();

    // 获取指定时间点的时间戳 （微秒）
    time_t getTimePointStamp(int year,int mon, int day,int hour, int min, int sec = 0);

    // 获取一个真随机数
    template<typename T>
    T getRandNum(const T &min, const T &max);
};

inline
std::chrono::system_clock::time_point myTime::makeTimePoint(int year,int mon, int day,int hour, int min, int sec) {
    struct tm t;
    t.tm_sec = sec;
    t.tm_min = min;
    t.tm_hour = hour;
    t.tm_mday = day;
    t.tm_mon = mon -1;
    t.tm_year = year-1900;
    t.tm_isdst = -1;
    time_t tt = mktime(&t);
    if (tt == -1) {
        throw "no valid system time";
    }
    return std::chrono::system_clock::from_time_t(tt);
}

inline
std::string myTime::asString(const std::chrono::system_clock::time_point & tp) {
    time_t t = std::chrono::system_clock::to_time_t(tp);
    std::string ts = std::ctime(&t);
    ts.resize(ts.size()-1);
    return ts;
}

inline
time_t myTime::getCurrentTimeStamp() {
    // c 的时间戳获取接口 精确到秒
    // std::cout<< time(nullptr) <<std::endl;

    return std::chrono::system_clock::now().time_since_epoch().count();
}

time_t myTime::getTimePointStamp(int year, int mon, int day, int hour, int min, int sec) {
    auto timePoint = makeTimePoint(year,mon,day,min,sec);
    return timePoint.time_since_epoch().count();
}

template<typename T>
T myTime::getRandNum(const T &min, const T &max) {
    std::default_random_engine dre(getCurrentTimeStamp());

    if (is_same<T, int>::value) {
        std::uniform_int_distribution<T> di(min, max);
        return di(dre);
    } else if(is_same<T, double>::value) {
        std::uniform_real_distribution<T> di(min, max);
        return di(dre);
    }
    return 0;
}

int myTimeTest() {
    myTime timeTest;
    auto tp1 = timeTest.makeTimePoint(2010,01,01,00,00);
    std::cout<<timeTest.getCurrentTimeStamp()<<std::endl;
    cout<< timeTest.getRandNum(0.1, 0.8)<< endl;
}

#endif //DAILY_PRACTICE_MYTIME_H
