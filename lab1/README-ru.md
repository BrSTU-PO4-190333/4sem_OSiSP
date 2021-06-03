## README

- [English](README.md)
- [Русский](README-ru.md)

## Дерево проекта

```bash
tree --charset ascii
.
|-- README**            // Информация репозитория
|-- docker-compose.yml  // Docker конфигурация
|-- rep
|   `-- main
|       `-- main.pdf    // Скомпилированный PDF
`-- src                 // Исходный код
```

## Компиляция PDF

Должен быть установлен Docker.

Запускаем виртуальную машину Docker через `docker-compose.yml`.

```bash
sudo docker-compose run latex /bin/bash
```

Как запустилась виртуальная машина, переходим в директорию с `main.tex` файлом.

```bash
cd /content/rep/main
```

Компилируем файл `main.tex`.

```bash
pdflatex main.tex
```

Второй раз компилируем файл `main.tex`, чтобы корректно работали ссылки в документе.

```bash
pdflatex main.tex
```

Скомпилированный файл `main.pdf` в папке `rep/main` вместе с `main.tex` файлом.
