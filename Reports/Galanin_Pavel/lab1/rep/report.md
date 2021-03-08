# Интерфейс. Файлы. Команды

---

## Часть 1.

1. Определить путевое имя рабочего каталога. Как обозначается корневой каталог? Какое путевое имя получили (относительное или абсолютное)?
2. Создать в начальном каталоге два подкаталога. Просмотреть содержимое рабочего каталога. Просмотреть содержимое родительского каталога, не переходя в него.
3. Перейти в системный каталог. Просмотреть его содержимое. Просмотреть содержимое начального каталога. Вернуться в начальный каталог.
4. Удалить созданные ранее подкаталоги.
5. Получить информацию по командам `ls` и `cd` с помощью утилиты `man`. Изучить структуру `man`-документа.
6. Получить краткую информацию по командам `ls` и `cd` с помощью команды `whatis` и `apropos`. В чем различие?
7. То же, что и в п.5, только с помощью команды `info`.

---

1. .
    ```bash
    $ pwd
    /home/pavel-innokentevich-galanin
    ```
2. .
    ```bash
    $ mkdir katalog1
    $ mkdir katalog2
    $ ls
    Apps     Documents  Music     Public     Videos    katalog2
    Desktop  Downloads  Pictures  Templates  katalog1  www
    $ ls ..
    pavel-innokentevich-galanin
    ```
3. .
    ```bash
    $ ls
    Apps     Documents  Music     Public     Videos    katalog2
    Desktop  Downloads  Pictures  Templates  katalog1  www
    $ cd /
    $ ls
    bin    dev   lib         media  proc  sbin      sys        usr
    boot   etc   lib64       mnt    root  srv       timeshift  var
    cdrom  home  lost+found  opt    run   swapfile  tmp
    $ cd
    $ ls
    Apps     Documents  Music     Public     Videos    katalog2
    Desktop  Downloads  Pictures  Templates  katalog1  www 
    ```
4. .
    ```bash
    $ ls
    Apps     Documents  Music     Public     Videos    katalog2
    Desktop  Downloads  Pictures  Templates  katalog1  www
    $ rmdir katalog1
    $ rmdir katalog2
    $ ls
    Apps     Documents  Music     Public     Videos
    Desktop  Downloads  Pictures  Templates  www
    ```
5. .
    ```bash
    $ man ls

    $ man cd
    No manual entry for cd
    ```
6. .
    ```bash
    $ whatis ls
    ls (1)               - list directory contents
    $ whatis cd
    cd: nothing appropriate.
    ```
7. .
    ```bash
    $ info ls

    $ info cd
    info: No menu item 'cd' in node '(dir)Top'
    ```

---

Часть 3.

1. Создайте в домашнем каталоге следующую структуру подкаталогов

    (существующие каталоги не удаляйте!)
    ```
    a.домашний каталог ----|
                1.|-ВашаФамилия-|
                        a. |-1-|
                        b. |   |-2
                        c. |   |-3
                        d. |
                        e. |-4
    ```
2. Скопируйте файл `/etc/group` в каталог `1` используя абсолютные имена копируемого файла и каталога назначения.
3. Скопируйте файл `/etc/group` в каталог `2` используя абсолютное  имя копируемого файла и относительное имя каталога назначения.
4. Скопируйте файл `/etc/group` в каталог `3` используя относительные имена копируемого файла и каталога назначения.
5. Скопируйте файл `/etc/group` в каталог `4` используя абсолютные имена копируемого файла и относительное имя каталога назначения с использованием специального символа `~`.
6. При помощи одной команды зайдите в каталог `3`.
7. Удалите файл `group` из  каталога `4` при помощи одной команды.
8. Перейдите в свой домашний каталог. Удалите каталоги `1` и `4`.
9. Выведите первые и последние 13 строк файла `/etc/group`.

---

1. .
    ```bash
    $ mkdir -p Galanin/1/2 Galanin/1/3 Galanin/4
    $ tree .. -d --charset anscii
    .
    |-- pavel-innokentevich-galanin
    |   |-- Galanin
    |   |   |-- 1
    |   |   |   |-- 2
    |   |   |   `-- 3
    |   |   `-- 4

    2562 directories
    ```
2. .
    ```bash
    $ cp /etc/group /home/pavel-innokentevich-galanin/Galanin/1
    $ ls ~/Galanin/1
    2  3  group
    ```
3. .
    ```bash
    $ cp /etc/group Galanin/1/2
    $ ls ~/Galanin/1/2
    group
    ```
4. .
    ```bash
    $ cp ../../etc/group Galanin/1/3
    $ ls ~/Galanin/1/3
    group
    ```
5. .
    ```
    $ cp /etc/group ~/Galanin/4
    $ ls ~/Galanin/4
    group
    ```
6. .
    ```bash
    $ pwd
    /home/pavel-innokentevich-galanin
    $ cd ~/Galanin/1/3
    $ pwd
    /home/pavel-innokentevich-galanin/Galanin/1/3
    ```
7. .
    ```bash
    $ ls ~/Galanin/4
    group
    $ rm -v ~/Galanin/4/group
    removed '/home/pavel-innokentevich-galanin/Galanin/4/group'
    $ ls ~/Galanin/4
    $ 
    ```
8. .
    ```bash
    $ rm -rv ~/Galanin/1
    removed '/home/pavel-innokentevich-galanin/Galanin/1/group'
    removed '/home/pavel-innokentevich-galanin/Galanin/1/3/group'
    removed directory '/home/pavel-innokentevich-galanin/Galanin/1/3'
    removed '/home/pavel-innokentevich-galanin/Galanin/1/2/group'
    removed directory '/home/pavel-innokentevich-galanin/Galanin/1/2'
    removed directory '/home/pavel-innokentevich-galanin/Galanin/1'
    $ rm -rv ~/Galanin/4
    removed directory '/home/pavel-innokentevich-galanin/Galanin/4'
    $ tree ~/Galanin --charset ascii
    /home/pavel-innokentevich-galanin/Galanin

    0 directories, 0 files
9. .
    ```bash
    $ head -n 13 /etc/group
    root:x:0:
    daemon:x:1:
    bin:x:2:
    sys:x:3:
    adm:x:4:syslog
    tty:x:5:syslog
    disk:x:6:
    lp:x:7:
    mail:x:8:
    news:x:9:
    uucp:x:10:
    man:x:12:
    proxy:x:13:
    $ tail -n 13 /etc/group
    scanner:x:125:saned
    _flatpak:x:126:
    avahi:x:127:
    saned:x:128:
    lightdm:x:129:
    nopasswdlogin:x:130:
    colord:x:131:
    pulse:x:132:
    pulse-access:x:133:
    nm-openvpn:x:134:
    sambashare:x:135:
    docker:x:136:
    pavel-innokentevich-galanin:x:1001:
    ```

---
