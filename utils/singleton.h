//
// Created by 李洪良 on 2023/4/24.
//

#ifndef DAILY_PRACTICE_SINGLETON_H
#define DAILY_PRACTICE_SINGLETON_H
//禁用复制构造和移动构造 赋值
class noncopyabel {
public:
    noncopyabel(const noncopyabel &) = delete;

    noncopyabel(const noncopyabel &&) = delete;

    noncopyabel& operator=(const noncopyabel &) = delete;

    noncopyabel& operator=(const noncopyabel &&) = delete;

protected:
    noncopyabel() = default;

    ~noncopyabel() = default;
};

template<class T>
class Singleton : noncopyabel {
public:
    static T &Instance() {
        static T t;
        return t;
    }
};

void singletonTest() {

}


#endif //DAILY_PRACTICE_SINGLETON_H
