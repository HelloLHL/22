//
// Created by 李洪良 on 2022/10/11.
//

#ifndef DAILY_PRACTICE_PRACTICE_H
#define DAILY_PRACTICE_PRACTICE_H
#include <iostream>
#include <cxxabi.h>
#include <mutex>


void lambda_expression_capture() {
    auto important = std::make_unique<int>(1);
    auto add = [v1 = 1, v2 = std::move(important)](int x, int y) -> int {
        return x+y+v1+(*v2);
    };

    std::cout<<
             abi::__cxa_demangle(typeid(add).name(),0,0,0)<<std::endl;
    std::cout << add(3,4) <<std::endl;
}


int producerAndConsumer() {
    std::queue<int> produced_nums;
    std::mutex mtx;
    std::condition_variable cv;
    bool notified = false;

    auto producer = [&]() {
        for (int i= 0; ; i++) {
            std::this_thread::sleep_for(std::chrono::milliseconds(900));
            std::unique_lock<std::mutex> lock(mtx);
            std::cout << "producting " << i<<std::endl;
            produced_nums.push(i);
            notified = true;
            cv.notify_all();
        }
    };

    auto consumer = [&]() {
        while (true) {
            std::unique_lock<std::mutex> lock(mtx);
            // 避免虚假唤醒
            while (!notified) {
                cv.wait(lock);
            }
            lock.unlock();
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            lock.lock();
            while (!produced_nums.empty()) {
                std::cout<<this_thread::get_id()<<"  consuming "<<produced_nums.front()<<std::endl;
                produced_nums.pop();
            }
            notified= false;
        }
    };


    std::thread p(producer);
    std::thread cs[2];
    for (int i=0; i<2; ++i) {
        cs[i] = std::thread(consumer);
        cout<<cs[i].get_id()<<endl;
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
}


int producerAndConsumer1() {
    std::queue<int> queue;
    mutex queueMutex;
    condition_variable queueCondVar;

    auto provider = [&] () {
        for (int i = 0; ; ++i) {
            {
                lock_guard<mutex> lg(queueMutex);
                queue.push(i);
                cout<<"provider  "<<i<<endl;
            }
            queueCondVar.notify_all();
            this_thread::sleep_for(chrono::milliseconds(1000));
        }
    };

    auto consumer = [&] () {
        while (true) {
            int val = int ();
            {
                unique_lock<mutex> ul(queueMutex);
                queueCondVar.wait(ul, [=]{return !queue.empty();});
                val = queue.front();
                queue.pop();
            }
            cout<<this_thread::get_id()<<"  consumer  "<<val<<endl;
            this_thread::sleep_for(chrono::milliseconds(2000));
        }
    };


    std::thread p(provider);
    std::thread cs[2];
    for (int i=0; i<2; ++i) {
        cs[i] = std::thread(consumer);
        cout<<cs[i].get_id()<<endl;
    }
    p.join();
    for (int i = 0; i < 2; ++i) {
        cs[i].join();
    }
}




int practiceTest() {
    setValue();
    // lambda_expression_capture();
    // producerAndConsumer();
}

#endif //DAILY_PRACTICE_PRACTICE_H
