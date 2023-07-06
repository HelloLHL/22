//
// Created by 李洪良 on 2022/10/10.
//

#ifndef DAILY_PRACTICE_THREADPOOL_H
#define DAILY_PRACTICE_THREADPOOL_H

#include <vector>
#include <queue>
#include <memory>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <future>
#include <functional>
#include <stdexcept>
#include <iostream>

class ThreadPool {
public:
    explicit ThreadPool(size_t);

    template<class F, class... Args>
    auto enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type>;

    ~ThreadPool();

private:
    std::vector<std::thread> workers;   //  线程集合
    std::queue<std::function<void()> > tasks;  //  任务队列

    std::mutex queue_mutex;
    std::condition_variable condition;
    std::atomic<bool> stop;
};


inline ThreadPool::ThreadPool(size_t threads) : stop(false) {
    if (threads == 0) {
        threads = std::thread::hardware_concurrency();
        threads = threads == 0 ? 2 : threads;
    }
    for (size_t i = 0; i < threads; ++i) {
        workers.emplace_back(
                [this] {
                    for (;;) {
                        std::function<void()> task;
                        {
                            std::unique_lock<std::mutex> lock(this->queue_mutex);

                            this->condition.wait(lock, [this] {
                                                     return this->stop.load() || !this->tasks.empty();
                                                 }
                            );

                            if (this->stop.load() && this->tasks.empty())
                                return;

                            task = std::move(this->tasks.front());
                            this->tasks.pop();
                        }
                        task();
                    }
                }
        );
    }
}

template<class F, class... Args>
auto ThreadPool::enqueue(F &&f, Args &&... args) -> std::future<typename std::result_of<F(Args...)>::type> {
    using return_type = typename std::result_of<F(Args...)>::type;

    auto task = std::make_shared<std::packaged_task<return_type()>>([this, f, args...]() {
        return f(args...);
    });

    std::future<return_type> res = task->get_future();
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        if (stop.load()) {
            throw std::runtime_error("enqueue on stopped ThreadPool!");
        }
        tasks.emplace(
                [task]() {
                    (*task)();
                }
        );
    }
    condition.notify_one();
    std::cout << "i am here    " << std::endl;
    return res;
}

inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        stop.store(true);
    }
    condition.notify_all();
    for (std::thread &worker: workers) {
        if (worker.joinable()) {
            worker.join();
        }
    }
}

int myThreadPoolTest() {
    ThreadPool pool(4);
/*
    auto result = pool.enqueue(
            [](int answer) {
                return answer;
            },
            42
    );
    std::cout << "box    " <<result.get()<<std::endl;
*/
    std::vector<std::future<int>> results;
    results.reserve(8);
    for (int i = 0; i < 8; ++i) {
        results.emplace_back(
                pool.enqueue([i] {
                    std::cout << "hello " << i << std::endl;
                    std::this_thread::sleep_for(std::chrono::seconds(1));
                    std::cout << "world " << i << std::endl;
                    return i * i;
                })
        );
    }
    for (auto &&result: results) {
        std::cout << result.get() << ' ';
    }
    std::cout << std::endl;

}

#endif //DAILY_PRACTICE_THREADPOOL_H
