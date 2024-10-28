### УСТАНОВКА И УДАЛЕНИЕ:

Чтобы установить библиотеку, надо скачать этот репозиторий в домашний каталог и запустить make / make install, произойдет следующее:
  1. Шаблоны и bash-скрипт из папки templates этого репозитория будут скопированны в папку \~/.local (если понадобиться она будет создана со всеми нужными вложениями), точнее в её поддиректории: templates и bin (\~/.local/bin добавляется в $PATH навсегда (команда закоментирована для того, чтобы установка не запрашивала права суперпользователя, так что в PATH сохранять нужно вручную));
  2. Создаётся папка \~/RecentCpp.

make uninstall:
  1. Удаляет скопированные шаблоны и скрипт из \~/.local, но не удаляет папки \~/.local/templates и \~/.local/bin, также не возращает $PATH;
  2. Удаляет папку \~/RecentCpp.


### ИСПОЛЬЗОВАНИЕ:

Команда crcpp {name} (расшифровка - create cpp {имя будующей программы}) создает шаблонную программу на языке C++, а также создает шаблонный ./buildCpp/MakefileCpp_{name} (для каждой программы свой!). Написанную программу в созданном файле можно собрать и запустить созданным вместе с ним Makefile-ом из папки сборки (./buildCpp), как make отработает, в папке сборки появится исполняемый файл этой программы и ещё один cpp исходник send_{name}, send_{name}.cpp - это программа {name}.cpp после частичного препроцессинга (исходная программа проходит полный препроцессинг, кроме расскрытия заголовочных файлов, которые находились в области системных хедеров, далее из полученного файла убераются все строки, начинающиеся со знака #), этот файл готов к отправке в тестирующую систему! Ссылка на send программу помещается в папку \~/RecentCpp для удобного доступа к программе (эту папку удобно закрепить в своем файловом менеджере). 
