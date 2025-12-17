#pragma once
#include <string>
#include <cctype>

class PasswordPolicy {
public:
    static bool satisfies(const std::string& pwd, bool need_upper, bool need_lower,
                          bool need_digit, bool need_symbol) {
        bool has_upper = false, has_lower = false, has_digit = false, has_symbol = false;

        for (char c : pwd) {
            if (std::isupper(c)) has_upper = true;
            else if (std::islower(c)) has_lower = true;
            else if (std::isdigit(c)) has_digit = true;
            else has_symbol = true;
        }

        return (!need_upper || has_upper) &&
               (!need_lower || has_lower) &&
               (!need_digit || has_digit) &&
               (!need_symbol || has_symbol);
    }
};