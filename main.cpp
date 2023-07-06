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
#include "practice3.h"
#include "singleton.h"
#include "my_order.h"
//#include "myBoost.h"
#include "select_poll_epoll.h"

// using namespace std;

void fn1() {
    cout << "calling fn1() ..." << endl;
}

void fn2() {
    cout << "calling fn2() ..." << endl;
}

class Empty {
public:
    int a;
};

#define gDynamicConfWarpper Singleton<Empty>::Instance()


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

    // cout<<sizeof(Empty)<<endl;
    //practice3();

/*
    {
        std::future<int> result = std::async([](int a,int b){
            std::cout<<"i am sum"<<endl;
            return a+b;
            }, 1, 2);
        std::cout << "Waiting for result..." << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(10));
        int sum = result.get();
        std::cout << "Sum is " << sum << std::endl;

        return 0;
    }
    */
    //gDynamicConfWarpper.a=10;
    //cout<<gDynamicConfWarpper.a<<endl;
    //order_test();
    // my_boost();
    /*
    std::atomic<int> or_num = 3;
    int expe = 2;
    if(or_num.compare_exchange_strong(expe,-1)) {
        std::cout<<"true"<<std::endl;
    }
    cout<<or_num.load()<<endl;
    cout<<expe<<endl;
    */
    // test_select();
    test_poll();
    return 0;
}