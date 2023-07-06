//
// Created by 李洪良 on 2023/3/13.
//

#ifndef DAILY_PRACTICE_PRACTICE3_H
#define DAILY_PRACTICE_PRACTICE3_H

#include <iostream>

struct alignas(8) S {

};

struct Obj {
    char a;
    int b;
};

template<typename T, typename U>
auto add(T a, U b) -> decltype(a + b) {
    return a + b;
}

struct  Example {
    char c;
    int i;
    short s;
};

class LRUCache {
public:
    LRUCache(int capacity):cap(capacity) {
    }

    int get(int key) {
        auto it = m.find(key);
        if (it == m.end()) {
            return -1;
        }
        // 将节点移到链表头部
        l.splice(l.begin(), l, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = m.find(key);
        if (it != m.end()) {
            // 节点已存在，更新值，将节点移到链表头部
            it->second->second = value;
            l.splice(l.begin(), l, it->second);
            return;
        }
        if (l.size() == cap) {
            // 移除链表末尾节点
            int k = l.back().first;
            m.erase(k);
            l.pop_back();
        }
        // 插入新节点，并将节点移到链表头部
        l.push_front({key, value});
        m[key] = l.begin();
    }

private:
    int cap{};
    list<pair<int, int>> l; // key和value
    unordered_map<int, list<pair<int, int>>::iterator> m; // key 和 位置指针
};

#include <iostream>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

class ThreadPool2 {
public:
    explicit ThreadPool2(size_t thread_count)
            : stop_(false)
    {
        for (size_t i = 0; i < thread_count; ++i)
            threads_.emplace_back(
                    [this]
                    {
                        for (;;)
                        {
                            std::function<void()> task;

                            {
                                std::unique_lock<std::mutex> lock(this->queue_mutex_);
                                this->condition_.wait(lock,
                                                      [this] { return this->stop_ || !this->tasks_.empty(); });
                                if (this->stop_ && this->tasks_.empty())
                                    return;
                                task = std::move(this->tasks_.front());
                                this->tasks_.pop();
                            }

                            task();
                        }
                    });
    }

    template<class F>
    void enqueue(F&& f)
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            tasks_.emplace(std::forward<F>(f));
        }
        condition_.notify_one();
    }

    ~ThreadPool2()
    {
        {
            std::unique_lock<std::mutex> lock(queue_mutex_);
            stop_ = true;
        }
        condition_.notify_all();
        for (std::thread& thread : threads_)
            thread.join();
    }

private:
    std::vector<std::thread> threads_;
    std::queue<std::function<void()>> tasks_;

    std::mutex queue_mutex_;
    std::condition_variable condition_;
    bool stop_;
};
void task(int i)
{
    std::cout << "hello " << i << std::endl;

    std::this_thread::sleep_for(std::chrono::seconds(1));
}

template <typename T>
class shared_ptr {
private:
    int* count;
    T* ptr;

public:
    shared_ptr(T* ptr = nullptr) : ptr(ptr) {
        count = new int(1);
    }

    shared_ptr(const shared_ptr<T>& other) {
        ptr = other.ptr;
        count = other.count;
        (*count)++;
    }

    ~shared_ptr() {
        (*count)--;
        if (*count == 0) {
            delete count;
            delete ptr;
        }
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }

    shared_ptr<T>& operator=(const shared_ptr<T>& other) {
        if (this != &other) {
            (*count)--;
            if (*count == 0) {
                delete count;
                delete ptr;
            }

            count = other.count;
            ptr = other.ptr;
            (*count)++;
        }

        return *this;
    }
};



int practice3() {
    std::cout << sizeof(Obj) << std::endl;
    std::cout << sizeof(float) << std::endl;
    auto a = 1 + 2;
    cout << typeid(a).name() << endl;
    const int j = 3;
    int *pj = const_cast<int *>(&j);
    *pj = 4;
    cout << &j << "    " << pj << endl;
    cout << j << "      " << *pj << endl;
    cout << &j << "    " << pj << endl;
    cout << add(1, 2.1) << endl;

    ThreadPool2 pool(4);
    std::shared_ptr<int> ss(new int(1));

    for (int i = 0; i < 8; ++i)
        pool.enqueue([i] { task(i); });

}

#endif //DAILY_PRACTICE_PRACTICE3_H
