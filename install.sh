#!/bin/bash

set -e

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
BUILD_DIR="$SCRIPT_DIR/build"
BIN_NAME="spass"
INSTALL_DIR="$HOME/.local/bin"
TARGET_PATH="$INSTALL_DIR/$BIN_NAME"

echo "Проверка: сборка выполнена в '$BUILD_DIR'..."
sleep 0.5

if [ ! -f "$BUILD_DIR/$BIN_NAME" ]; then
    echo "Ошибка: исполняемый файл '$BIN_NAME' не найден в '$BUILD_DIR'."
    echo "Выполните сначала:"
    echo "  mkdir build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Release && make"
    exit 1
fi

echo "Проверка существования директории '$INSTALL_DIR'..."
sleep 0.5

if [ ! -d "$INSTALL_DIR" ]; then
    echo "Директория не найдена. Создаём '$INSTALL_DIR'..."
    mkdir -p "$INSTALL_DIR"
    echo "Директория успешно создана."
else
    echo "Директория '$INSTALL_DIR' уже существует."
fi

sleep 0.5
echo "Копирование исполняемого файла в '$INSTALL_DIR'..."
cp "$BUILD_DIR/$BIN_NAME" "$INSTALL_DIR/"
echo "Файл успешно скопирован."

sleep 0.5
echo "Установка завершена успешно!"

if command -v spass &> /dev/null; then
    echo "Готово! Используйте 'spass --help' для справки."
else
    echo "Внимание: '$INSTALL_DIR' не в вашем PATH."
    echo "Чтобы использовать 'spass' из любого места, добавьте в ~/.bashrc или ~/.zshrc:"
    echo "  export PATH=\"\$HOME/.local/bin:\$PATH\""
fi

sleep 0.3