//
// Created by 李洪良 on 2023/1/18.
//

#ifndef DAILY_PRACTICE_STDEMPTYCLASS_H
#define DAILY_PRACTICE_STDEMPTYCLASS_H
#include <string>
#include <iostream>
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

class Person {
public:
    Person();    // 构造函数
    Person(const Person &);    //  复制构造函数
    Person(int age, std::string name, Person *parent= nullptr):age(age),name(name),parent(parent){

    }   //  带参数的构造函数
    Person(Person &&) noexcept;    //  移动构造函数
    ~Person(){
        delete parent;
    }   // 析构函数
    Person &operator=(const Person &); //赋值运算符
    Person *operator&(){
        return this;
    } //  取址运算符
    const Person *operator&() const {
        return this;
    } // 取址运算符const

    bool operator==(const Person &) const;
    bool operator>(const Person &) const;
private:
    std::string name{};
    int age{};
    Person *parent{nullptr};
};
Person::Person() {
    std::cout<<"i am 默认初始化构造函数\n";
}
Person::Person(const Person &person) {
    this->age=person.age;
    this->name=person.name;
    if (person.parent!= nullptr){
        this->parent=new Person(*person.parent);
    }
    std::cout<<"i am 拷贝构造函数\n";
}

Person &Person::operator=(const Person &person) {
    if (this != &person) {
        this->age=person.age;
        this->name=person.name;
        delete this->parent;
        if (person.parent != nullptr){
            this->parent=new Person(*person.parent);
        } else{
            this->parent= nullptr;
        }
        // this->parent = person.parent != nullptr ? new Person(*person.parent) : nullptr;
    }
    return *this;
}

Person::Person(Person &&person) noexcept {
    this->name=std::move(person.name);
    this->age=std::move(person.age);
    this->parent=person.parent;
    person.parent= nullptr;
}

bool Person::operator==(const Person &person) const {
    return this->age==person.age;
}

bool Person::operator>(const Person &person) const {
    return this->age>person.age;
}
#endif //DAILY_PRACTICE_STDEMPTYCLASS_H
