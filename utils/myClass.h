//
// Created by 李洪良 on 2023/2/10.
//

#ifndef DAILY_PRACTICE_MYCLASS_H
#define DAILY_PRACTICE_MYCLASS_H

#include <iostream>

class Pet {
public:
    virtual ~Pet() {};

    virtual void make_sound() const = 0;
};

class Dog : public Pet {
public:
    virtual void make_sound() const override {
        std::cout << "raf raf \n";
    }
};

class Cat : public Pet {
public:
    virtual void make_sound() const override {
        std::cout << "mewo \n";
    }
};

class PetFactory {
public:
    virtual ~PetFactory() {}

    virtual Pet *create() const = 0;
};

class DogFactory : public PetFactory {
public:
    virtual Dog *create() const override {
        return new Dog();
    }
};

class CatFactory : public PetFactory {
public:
    virtual Cat *create() const override {
        return new Cat;
    }
};


void myClassTest1() {
    Dog dog;
    Cat cat;
    std::vector<Pet *> pets = {&dog, &cat};
    for (auto pet: pets) {
        pet->make_sound();
    }

    pets.clear();
    DogFactory df;
    CatFactory cf;
    std::vector<PetFactory *> pf = {&df, &cf};

    for(auto pPet :  pf) {
        pets.push_back(pPet->create());
    }

    for (auto pet: pets) {
        pet->make_sound();
    }

}


#endif //DAILY_PRACTICE_MYCLASS_H
