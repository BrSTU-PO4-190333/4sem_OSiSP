# Как скомпилировать проект

Проект написан на языке разметки `TeX` в блокноте `VS Code` с расширением `LaTeX Workshop`.

Когда изменяеться какой-нибудь файл `*.tex`, то в блокноте `VS Code` расширение `LaTeX Workshop` автоматически компилирует `main.tex` в `main.pdf`.

Для работа расширения `LaTeX Workshop` в блокноте `VS Code` нужен компилятор:
- на `Debian`-подобных системах:
    ```bash
    sudo apt update
    sudo apt install texlive-full
    ```
