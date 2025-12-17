#pragma once
#include <string>

class IGenerator {
public:
    virtual ~IGenerator() = default;
    virtual std::string generate(int length) = 0;
};