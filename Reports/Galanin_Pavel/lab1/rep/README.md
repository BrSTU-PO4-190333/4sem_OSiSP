# How to compile a project

The project is written in `TeX` markup language in `VS Code` notebook with `LaTeX Workshop` extension.

When any `*.tex` file changes, the `LaTeX Workshop` extension in the `VS Code` notebook will automatically compile `main.tex` into `main.pdf`.

For the `LaTeX Workshop` extension to work in the `VS Code` notepad, you need a compiler:
- on `Debian`-like systems:
     ```bash
     sudo apt update
     sudo apt install texlive-full
     ```
