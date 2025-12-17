#pragma once
#include "IGenerator.hpp"
#include "RandomReader.hpp"
#include <string>

class SimpleGenerator : public IGenerator {
private:
    std::string charset;

public:
    SimpleGenerator(bool upper, bool lower, bool digits, bool symbols) {
        if (upper)    charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        if (lower)    charset += "abcdefghijklmnopqrstuvwxyz";
        if (digits)   charset += "0123456789";
        if (symbols)  charset += "!@#$%^&*()_+-=[]{}|;:,.<>?~";
        if (charset.empty()) {
            throw std::invalid_argument("Набор символов пуст");
        }
    }

    std::string generate(int length) override {
        if (length <= 0) return "";
        std::string pwd;
        pwd.reserve(length);
        for (int i = 0; i < length; ++i) {
            pwd += charset[RandomReader::get_index(charset.size())];
        }
        return pwd;
    }
};