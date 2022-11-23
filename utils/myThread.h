//
// Created by 李洪良 on 2022/10/11.
//

#ifndef DAILY_PRACTICE_MYTHREAD_H
#define DAILY_PRACTICE_MYTHREAD_H

#include <mutex>
#include <thread>
#include <future>
#include <myTime.h>

class myThread {
public:
    static int v;
public:
    static void critical_section(int change_v) ;
    void threadDemo();
    static void print_int(std::future<int>& fut);
    void demo1();
};

int myThread::v = 1;

void myThread::critical_section(int change_v) {
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);

    v = change_v;
}

void myThread::print_int(std::future<int> &fut) {
    cout<<"wait...."<<endl;
    int x = fut.get(); // 获取共享状态的值.
    std::cout << "value: " << x << '\n'; // 打印 value: 10.
}

void myThread::demo1() {
    std::promise<int> prom; // 生成一个 std::promise<int> 对象.
    std::future<int> fut = prom.get_future(); // 和 future 关联.
    std::thread t1(print_int, std::ref(fut)); // 将 future 交给另外一个线程t.
    std::this_thread::sleep_for(std::chrono::seconds(5));
    prom.set_value(10); // 设置共享状态的值, 此处和线程t保持同步.
    t1.join();
}

void myThread::threadDemo() {
    std::thread t1(critical_section, 2), t2(critical_section, 3);
    t1.join();
    t2.join();
    cout<<v<<endl;
}



class packagedTask {
public:
    static int add2(int x, int y) {
        return x+y;
    }
    int demo();
};

int packagedTask::demo() {
    // std::packaged_task可以封装任何可以调用的目标
    //std::packaged_task<int(int,int)> task(add2(5,10));
    std::packaged_task<int()> task(std::bind(add2, 5,10));
    // 获取task的期物
    std::future<int> result = task.get_future();
    std::thread(std::move(task)).detach();
    std::cout<<"wait..."<<std::endl;
    // 阻塞到期物的完成
    result.wait();
    std::cout<<"done"<<std::endl
             <<"future result is " << result.get()
             <<std::endl;
}

class myFuture {
public:
    static int doSomething(char c);
    static int doSomething2(char c, shared_future<int> f);
    static int func1() {
        return doSomething('.');
    }
    int func2() {
        return doSomething('+');
    }
    int demo();
    int demo1();
    int demo2();
    static int queryNum() {
        myTime util;
        return util.getRandNum(1,10);
    }
};

int myFuture::doSomething(char c) {
    default_random_engine dre(c);
    uniform_int_distribution<int> id(10,1000);

    for (int i = 0; i < 10; ++i) {
        this_thread::sleep_for(chrono::milliseconds(id(dre)));
        cout.put(c).flush();
    }
    cout<<endl;
    return c;
}

int myFuture::doSomething2(char c, shared_future<int> f) {
    try {
        int  num = f.get();

        for (int i = 0; i < num; ++i) {
            this_thread::sleep_for(chrono::milliseconds(1000));
            cout.put(c).flush();
        }
        cout<<endl;
    }
    catch (const exception& e){
        cerr<<"exception in thread "<<this_thread::get_id() <<": "<<e.what()<<endl;
    }
}

int myFuture::demo() {
    std::future<int> result1(std::async(func1));
    // this_thread::sleep_for(chrono::seconds(5));
    int result2 = func2();
    // 只能调用get一次
    int result = result1.get() + result2;
    cout<<result<<endl;
}

int myFuture::demo1() {
    auto tp = chrono::system_clock::now() + chrono::minutes(1);
    char c = '@';
    future<int> f = async(launch::async, doSomething, ref(c));
    future_status s = f.wait_until(tp);
    if (s == future_status::ready) {
        cout<<"ready"<<endl;
    } else if(s == future_status::timeout) {
        cout<<"timeout"<<endl;
    }
}

int myFuture::demo2() {
    try {
        // get可被调用多次
        shared_future<int> f = async(queryNum);

        auto f1 = async(launch::async, doSomething2, '.', f);
        auto f2 = async(launch::async, doSomething2, '+', f);
        auto f3 = async(launch::async, doSomething2, '*', f);

        f1.get();
        f2.get();
        f3.get();
    }
    catch (const exception& e) {
        cout<<"\n exception: "<< e.what()<< endl;
    }
    cout<<"done"<<endl;

}

int threadTest() {
    myThread demo;
    demo.demo1();
}


#endif //DAILY_PRACTICE_MYTHREAD_H
