echo "Проверка существования директории ~/.local/bin..."

if [ ! -d "$HOME/.local/bin" ]; then
    echo "Директория не найдена. Создаём ~/.local/bin..."
    mkdir -p "$HOME/.local/bin"
    if [ $? -eq 0 ]; then
        echo "Директория успешно создана"
    else
        echo "Ошибка при создании директории"
        exit 1
    fi
else
    echo "Директория ~/.local/bin уже существует."
fi

echo "Копирование исполняемого файла в ~/.local/bin..."
cp ./spass "$HOME/.local/bin/"

if [ $? -eq 0 ]; then
    echo "Файл успешно скопирован"
    echo "Установка завершена успешно! Для использования программы используйте "spass""
else
    echo "Ошибка при копировании файла"
    exit 1
fi