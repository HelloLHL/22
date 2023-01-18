//
// Created by 李洪良 on 2023/1/18.
//

#ifndef DAILY_PRACTICE_PRACTICE2_H
#define DAILY_PRACTICE_PRACTICE2_H
#include <iostream>

using namespace std;


int value = 0;

void printValue() {
    cout<<value<<endl;
}

void setValue() {
    int value = 1;
    cout<<value<<endl;
    // 全局变量
    ::value = 2;
    printValue();
}

void practiceTest2() {

}


#endif //DAILY_PRACTICE_PRACTICE2_H
