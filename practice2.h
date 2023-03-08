//
// Created by 李洪良 on 2023/1/18.
//

// 防止头文件被重复引用
#ifndef DAILY_PRACTICE_PRACTICE2_H
#define DAILY_PRACTICE_PRACTICE2_H

#include <iostream>
#include <cstddef>

// #pragma pack(1)
using namespace std;
typedef unsigned short word;

#define debugSwitch
// 宏是简单的文本替换
#define MAX(x, y) ((x) >(y) ? (x):(y))
#define SQR(x) (x*x)
// #使参数成为字符串
#define STR(s) #s
// ##拼接宏参数
#define CONS(a, b) (int)(a##e##b)
// 获取数组元素个数
#define ARR_SIZE(a) (sizeof(a)/sizeof(a[0]))

typedef int (*pfun)(int x, int y);

int value = 0;

void printValue() {
    cout << value << endl;
}

void setValue() {
    int value = 1;
    cout << value << endl;
    // 全局变量
    ::value = 2;
    printValue();
}

char getChar(int x, int y) {
    char c;
    unsigned int a = x;
    // 表达式存在有符号类型和无符号类型时，所有的操作数转为无符号类型相加
    (a + y > 10) ? (c = 1) : (c = 2);
    cout << (a + y) << endl;
    return c;
}

void swap2(int &a, int &b) {
    a = a + b;
    b = a - b;
    a = a - b;
}

// 异或位
void swap3(int &a, int &b) {
    a ^= b;
    b ^= a;
    a ^= b;
}


void unsignedTest() {
    char c1 = getChar(7, 4);
    char c2 = getChar(7, 3);
    char c3 = getChar(7, -7);
    char c4 = getChar(7, -8);

    cout << (int) c1 << "  " << (int) c2 << "   " << (int) c3 << "   " << (int) c4 << endl;
}

void constTest() {
    const int x = 1;
    int b = 10, c = 20;
    const int *a1 = &b;
    int *const a2 = &b;
    const int *const a3 = &b;

    // x = 2;
    a1 = &c;
    // *a1 = 1;
    // a2 = &c;
    *a2 = 1;

    // a3 = &c;
    // *a3 = 1;
}


class widget {
public:
    widget() {
        count++;
    }

    ~widget() {
        --count;
    }

    static int num() {
        return count;
    }

private:
    static int count;
};

int widget::count = 0;

void widgetTest() {
    widget x, y;
    {
        cout << "the num is " << widget::num() << endl;
        widget z;
        cout << "the num is " << widget::num() << endl;
    }
    cout << "the num is " << widget::num() << endl;

}

struct s {
    char c1;
    int i;
    char c2;
};

class Base {
public:
    Base(int x) : a(x) {

    }

    void print() {
        cout << "base" << endl;
    }

private:
    int a;
};

class Derived : public Base {
public:
    Derived(int x) : Base(x - 1), b(x) {

    }

    void print() {
        cout << "derived" << endl;
    }

private:
    int b;
};

union u {
    double a;
    int b;
};

// 联合体大小取决于 所有成员中占用空间最大的一个成员的大小
union u2 {
    char a[13];
    int b;
};

class MyClass {
public:
    int data;

    MyClass(int data) {
        this->data = data;
    }

    void print() {
        cout << data << endl;
        cout << "hello" << endl;
    }
};

void myClassTest() {
    MyClass *pmyClass = new MyClass(1);
    pmyClass->print();
    pmyClass[0].print();
    pmyClass[10000].print();

}

int max(int x, int y) {
    return x > y ? x : y;
}

void pointerTest() {
    int (*p)(int, int);
    int max(int, int);
    p = &max;
    cout << (*p)(5, 7) << endl;
    pfun z = max;
    cout << z(1, 9) << endl;
}

// 联合体的 存放顺序是所有成员从低地址开始存放
int checkCPU() {
    union w {
        int a;
        char b;
    } c;
    c.a = 1;    //0x0001
    return c.b == 1;
}

template<typename T>
void print(T &t) {
    cout << "lvalue" << endl;
}

template<typename T>
void print(T &&t) {
    cout << "rvalue" << endl;
}

static bool isLittleEndianOs() {
    cout<<"--------------"<<endl;
    cout << __BYTE_ORDER__<<endl;
    cout << __LITTLE_ENDIAN__<<endl;

    return __BYTE_ORDER__ == __LITTLE_ENDIAN__;
}

void myRvalue() {
    std::string num = "20";
    string moveNum = std::move(num);
    cout << moveNum << endl;
    cout << num.size() << endl;

    std::string num2 = "210";
    std::string num3 = num2;
    print(std::forward<string>(num3));
    print(std::move(num3));

    cout << num2 << endl;
}

void practiceTest2() {
#ifdef debugSwitch
    unsignedTest();
#endif
    cout << "practiceTest2" << endl;
    cout << MAX(2, 3) << endl;
    cout << SQR(5 + 2) << endl;
    cout << STR(vck) << endl;
    cout << CONS(2, 3) << endl;
    int num[100];
    cout << ARR_SIZE(num) << endl;
    widgetTest();
    cout << sizeof(s) << endl;
    cout << sizeof(widget) << endl;
    cout << sizeof(Base) << endl;
    cout << sizeof(Derived) << endl;
    cout << sizeof(u2) << endl;
    char *str7 = "abc";
    char *str8 = "abc";
    cout << (str7 == str8) << endl;
    cout << str8 << "   " << str7 << endl;
    //printf("%p", str7);
    myClassTest();
    pointerTest();
    //cout << checkCPU() << endl;
    if (isLittleEndianOs()) {
        cout << "little" << endl;
    } else {
        cout << "big" << endl;
    }
    int a = 1, b = 2;
    function<int(int)> fun2 = [=, &b](int c) -> int { return b += a + c; };
}


#endif //DAILY_PRACTICE_PRACTICE2_H
