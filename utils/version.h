//
// Created by 李洪良 on 2022/10/10.
//

#ifndef UNTITLED_VERSION_H
#define UNTITLED_VERSION_H
#include <version>
#include <iostream>
using namespace std;

#define COMPILER_FEATURE_VALUE(value) #value
#define COMPILER_FEATURE_ENTRY(name) { #name, COMPILER_FEATURE_VALUE(name) }

struct CompilerFeature {
    CompilerFeature(const char* name = nullptr, const char* value = nullptr)
            : name(name), value(value) {}

    const char* name;
    const char* value;
};

int getCPPVersion()
{
    CompilerFeature x = COMPILER_FEATURE_ENTRY(__cplusplus);
    cout << "name:" << x.name << endl;
    cout << "value:" << x.value << endl;
    return 0;
}
#endif //UNTITLED_VERSION_H
