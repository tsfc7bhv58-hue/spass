#pragma once
#include <string>
#include <fstream>
#include <stdexcept>

class RandomReader {
public:
    static unsigned char get_byte() {
        static std::ifstream urandom("/dev/urandom", std::ios::in | std::ios::binary);
        if (!urandom.is_open()) {
            throw std::runtime_error("Не удалось открыть /dev/urandom");
        }
        unsigned char byte;
        urandom.read(reinterpret_cast<char*>(&byte), sizeof(byte));
        if (!urandom) {
            throw std::runtime_error("Ошибка чтения из /dev/urandom");
        }
        return byte;
    }

    static size_t get_index(size_t max) {
        if (max == 0) return 0;
        return get_byte() % max;
    }
};