//
// Created by 李洪良 on 2023/1/18.
//

#ifndef DAILY_PRACTICE_STDEMPTYCLASS_H
#define DAILY_PRACTICE_STDEMPTYCLASS_H

class Empty {
public:
    Empty();    // 构造函数
    Empty(const Empty &);    //  复制构造函数
    ~Empty();   // 析构函数
    Empty &operator=(const Empty &); //赋值运算符
    Empty *operator&(); //  取址运算符
    const Empty *operator&() const; // 取址运算符const
    Empty(Empty &&);    //  移动构造函数
};


#endif //DAILY_PRACTICE_STDEMPTYCLASS_H
