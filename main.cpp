//
// Created by 李洪良 on 2022/10/10.
//

#include <version.h>
#include <ThreadPool.h>
#include <myTime.h>
#include "practice.h"
#include "practice2.h"
#include <myThread.h>
#include <myAlgorithms.h>
#include <iostream>
#include "myAsio.h"
#include "mySpdlog.h"
#include "myClass.h"

// using namespace std;

void fn1() {
    cout << "calling fn1() ..." << endl;
}

void fn2() {
    cout << "calling fn2() ..." << endl;
}


int main() {
    // main 函数执行完还可以执行atexit注册的函数 执行顺序与注册顺序相反
    // atexit(fn1);
    // atexit(fn2);
    // getCPPVersion();
    // myThreadPoolTest();
    // myTimeTest();
    // practiceTest();
    // threadTest();
    // Solution myAlgorithms;
    // myAlgorithms.myTest();
    // practiceTest2();
    // test();
    // spdlogTest();
    // myClassTest1();

    return 0;
}