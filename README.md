# spass — Secure Terminal Password Generator  
# spass — Безопасный генератор паролей для терминала

> A minimal, secure, dependency-free password generator for Linux, written in modern C++.  
> Минималистичный, безопасный генератор паролей без зависимостей для Linux, написанный на современном C++.

---

## English

### Features
- **Cryptographically secure**: reads entropy directly from `/dev/urandom`.
- **Modular architecture**: abstract generator interface, easy to extend.
- **No external dependencies**: compiles with standard C++17 and CMake.
- **Flexible policies**: enforce presence of uppercase, lowercase, digits, symbols.
- **CLI-friendly**: intuitive flags, batch generation, help output.

### Build & Install

```bash
git clone https://github.com/tsfc7bhv58-hue/spass.git
cd spass

# Build
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Install to ~/.local/bin
./install.sh

Make sure ~/.local/bin is in your PATH. If not, add this to ~/.bashrc or ~/.zshrc:
export PATH="$HOME/.local/bin:$PATH"

Usage Examples


spass 20                    # Generate 1 password, 20 chars
spass 16 -c 5 -e            # Generate 5 passwords, enforce all symbol types
spass -s -u -o 12           # Only lowercase + digits, length 12
spass --help                # Show full help
```
--

## Русский
### Возможности
    - **Криптографическая безопасность**: энтропия читается напрямую из /dev/urandom.
    - **Модульная архитектура**: абстрактный интерфейс генератора, легко расширять.
    - **Без зависимостей**: собирается с C++17 и CMake, ничего дополнительно не нужно.
    - **Гибкие правила**: можно гарантировать наличие заглавных, строчных, цифр и спецсимволов.
    - **Удобный CLI**: понятные флаги, генерация нескольких паролей, справка.

### Сборка и установка

git clone https://github.com/tsfc7bhv58-hue/spass.git
cd spass

# Сборка
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make

# Установка в ~/.local/bin
./install.sh

Убедитесь, что ~/.local/bin есть в вашем PATH. Если нет, добавьте в ~/.bashrc или ~/.zshrc:

export PATH="$HOME/.local/bin:$PATH"

Примеры использования

spass 20                    # Сгенерировать 1 пароль длиной 20
spass 16 -c 5 -e            # Сгенерировать 5 паролей с обязательными всеми типами символов
spass -s -u -o 12           # Только строчные буквы + цифры, длина 12
spass --help                # Показать справку
