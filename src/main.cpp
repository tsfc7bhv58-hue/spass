#include <iostream>
#include <memory>
#include <string>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include "SimpleGenerator.hpp"
#include "PasswordPolicy.hpp"

void show_help(const char* prog_name) {
    std::cout << "Использование: " << prog_name << " [ДЛИНА] [ОПЦИИ]\n"
              << "Генератор надёжных паролей на основе /dev/urandom.\n\n"
              << "Опции:\n"
              << "  -s, --no-symbols      исключить спецсимволы\n"
              << "  -l, --no-letters      исключить все буквы\n"
              << "  -d, --no-digits       исключить цифры\n"
              << "  -u, --no-uppercase    исключить заглавные буквы\n"
              << "  -o, --no-lowercase    исключить строчные буквы\n"
              << "  -c N, --count=N       сгенерировать N паролей (по умолчанию: 1)\n"
              << "  -e, --enforce-policy  гарантировать наличие всех выбранных типов символов\n"
              << "  -h, --help            показать эту справку\n\n"
              << "Примеры:\n"
              << "  " << prog_name << " 20\n"
              << "  " << prog_name << " 12 -s -u\n"
              << "  " << prog_name << " -c 5 16 -e\n";
}

bool is_positive_integer(const std::string& s) {
    if (s.empty()) return false;
    for (char c : s) {
        if (!std::isdigit(static_cast<unsigned char>(c))) return false;
    }
    return true;
}

int main(int argc, char* argv[]) {
    bool use_upper = true;
    bool use_lower = true;
    bool use_digits = true;
    bool use_symbols = true;
    int length = 16;
    int count = 1;
    bool enforce_policy = false;
    bool length_set = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg == "-h" || arg == "--help") {
            show_help(argv[0]);
            return 0;
        }

        if (arg[0] == '-') {
            if (arg == "-s" || arg == "--no-symbols") {
                use_symbols = false;
            } else if (arg == "-l" || arg == "--no-letters") {
                use_upper = use_lower = false;
            } else if (arg == "-d" || arg == "--no-digits") {
                use_digits = false;
            } else if (arg == "-u" || arg == "--no-uppercase") {
                use_upper = false;
            } else if (arg == "-o" || arg == "--no-lowercase") {
                use_lower = false;
            } else if (arg == "-e" || arg == "--enforce-policy") {
                enforce_policy = true;
            } else if (arg == "-c" || arg == "--count") {
                if (i + 1 >= argc) {
                    std::cerr << "Ошибка: ожидается число после " << arg << "\n";
                    return 1;
                }
                std::string next = argv[++i];
                if (!is_positive_integer(next)) {
                    std::cerr << "Ошибка: '" << next << "' не является целым числом\n";
                    return 1;
                }
                count = std::atoi(next.c_str());
                if (count <= 0 || count > 100) {
                    std::cerr << "Ошибка: количество должно быть от 1 до 100\n";
                    return 1;
                }
            } else {
                std::cerr << "Неизвестный флаг: " << arg << "\n";
                std::cerr << "Используйте " << argv[0] << " --help для справки.\n";
                return 1;
            }
        } else {
            if (length_set) {
                std::cerr << "Ошибка: длина указана более одного раза\n";
                return 1;
            }
            if (!is_positive_integer(arg)) {
                std::cerr << "Ошибка: ожидалось число (длина), получено: " << arg << "\n";
                return 1;
            }
            length = std::atoi(arg.c_str());
            if (length <= 0 || length > 1000) {
                std::cerr << "Ошибка: длина должна быть от 1 до 1000\n";
                return 1;
            }
            length_set = true;
        }
    }
    if (!use_upper && !use_lower && (use_upper || use_lower)) {
    }

    try {
        auto generator = std::make_unique<SimpleGenerator>(use_upper, use_lower, use_digits, use_symbols);

        for (int i = 0; i < count; ++i) {
            std::string pwd;
            int attempts = 0;
            const int max_attempts = 1000;

            do {
                pwd = generator->generate(length);
                attempts++;
                if (attempts > max_attempts) {
                    std::cerr << "Не удалось сгенерировать пароль, удовлетворяющий политике\n";
                    return 1;
                }
            } while (enforce_policy && !PasswordPolicy::satisfies(pwd, use_upper, use_lower, use_digits, use_symbols));

            std::cout << pwd << '\n';
        }

    } catch (const std::exception& e) {
        std::cerr << "Ошибка: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}