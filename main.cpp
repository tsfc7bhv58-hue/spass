#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <algorithm>
#include <cctype>
#include <cstdlib>

void show_help(const char* prog_name) {
    std::cout << "Использование: " << prog_name << " [ДЛИНА] [ОПЦИИ]\n"
              << "Генератор надёжных паролей.\n\n"
              << "Опции:\n"
              << "  -s, --no-symbols      исключить спецсимволы\n"
              << "  -l, --no-letters      исключить все буквы (заглавные и строчные)\n"
              << "  -d, --no-digits       исключить цифры\n"
              << "  -u, --no-uppercase    исключить заглавные буквы\n"
              << "  -o, --no-lowercase    исключить строчные буквы\n"
              << "  -c N, --count=N       сгенерировать N паролей (по умолчанию: 1)\n"
              << "  -h, --help            показать эту справку\n\n"
              << "Примеры:\n"
              << "  " << prog_name << " 20\n"
              << "  " << prog_name << " 12 -s -u\n"
              << "  " << prog_name << " -c 5 16\n";
}

std::string generate_password(int length, const std::string& charset) {
    if (charset.empty() || length <= 0) return "";
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, static_cast<int>(charset.size()) - 1);

    std::string pwd;
    pwd.reserve(length);
    for (int i = 0; i < length; ++i) {
        pwd += charset[dis(gen)];
    }
    return pwd;
}

int main(int argc, char* argv[]) {
    bool use_upper = true;
    bool use_lower = true;
    bool use_digits = true;
    bool use_symbols = true;
    int length = 16;
    int count = 1;
    bool length_set = false;

    for (int i = 1; i < argc; ++i) {
        std::string arg = argv[i];

        if (arg.empty()) {
            std::cerr << "Ошибка: пустой аргумент\n";
            return 1;
        }

        if (arg == "-h" || arg == "--help") {
            show_help(argv[0]);
            return 0;
        }

        if (arg[0] == '-') {
            if (arg == "-s" || arg == "--no-symbols") {
                use_symbols = false;
            } else if (arg == "-l" || arg == "--no-letters") {
                use_upper = false;
                use_lower = false;
            } else if (arg == "-d" || arg == "--no-digits") {
                use_digits = false;
            } else if (arg == "-u" || arg == "--no-uppercase") {
                use_upper = false;
            } else if (arg == "-o" || arg == "--no-lowercase") {
                use_lower = false;
            } else if (arg == "-c" || arg == "--count") {
                if (i + 1 >= argc) {
                    std::cerr << "Ошибка: ожидается число после " << arg << "\n";
                    return 1;
                }
                std::string next = argv[++i];
                if (next.empty() || !std::all_of(next.begin(), next.end(), ::isdigit)) {
                    std::cerr << "Ошибка: '" << next << "' не является целым числом\n";
                    return 1;
                }
                count = std::atoi(next.c_str());
                if (count <= 0 || count > 100) {
                    std::cerr << "Ошибка: количество паролей должно быть от 1 до 100\n";
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
            if (!std::all_of(arg.begin(), arg.end(), ::isdigit)) {
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

    std::string charset = "";
    if (use_upper)    charset += "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    if (use_lower)    charset += "abcdefghijklmnopqrstuvwxyz";
    if (use_digits)   charset += "0123456789";
    if (use_symbols)  charset += "!@#$%^&*()_+-=[]{}|;:,.<>?~";

    if (charset.empty()) {
        std::cerr << "Ошибка: не выбрано ни одного типа символов!\n";
        return 1;
    }

    for (int i = 0; i < count; ++i) {
        std::string pwd = generate_password(length, charset);
        if (pwd.empty()) {
            std::cerr << "Ошибка генерации пароля\n";
            return 1;
        }
        std::cout << pwd << '\n';
    }

    return 0;
}