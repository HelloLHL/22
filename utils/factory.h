//
// Created by 李洪良 on 2023/5/30.
//

#ifndef DAILY_PRACTICE_FACTORY_H
#define DAILY_PRACTICE_FACTORY_H
#include <iostream>
#include <string>

using namespace std;

// 抽象产品类
class Product{
public:
    virtual void use() = 0;
};

// 具体产品类A
class ProductA : public Product{
public:
    void use(){
        cout << "Product A" << endl;
    }
};

// 具体产品类B
class ProductB : public Product{
public:
    void use(){
        cout << "Product B" << endl;
    }
};

// 抽象工厂类
class Factory{
public:
    virtual Product* createProduct() = 0;
};

// 具体工厂类A
class FactoryA : public Factory{
public:
    Product* createProduct(){
        return new ProductA();
    }
};

// 具体工厂类B
class FactoryB : public Factory{
public:
    Product* createProduct(){
        return new ProductB();
    }
};

int main(){
    // 使用工厂A创建产品A
    Factory* factoryA = new FactoryA();
    Product* productA = factoryA->createProduct();
    productA->use();

    // 使用工厂B创建产品B
    Factory* factoryB = new FactoryB();
    Product* productB = factoryB->createProduct();
    productB->use();

    // 释放资源
    delete productA;
    delete productB;
    delete factoryA;
    delete factoryB;

    return 0;
}

#endif //DAILY_PRACTICE_FACTORY_H
