1) Иерархия классов <br />
![Иерархия классов потоков](./IOSTREAM.png "Иерархия классов потоков") <br />
- iostream: определены стандартные потоки cin, cout, wcin, wcout и т.д., включен файл istream;
- istream: определены шаблоны basic_istream и basic_iostream, включен заголовочный файл ostream;
- ostream: определен шаблон basic_ostream, включен заголовочный файл ios;
- ios: определен шаблон basic_ios, включен заголовочный файл xlocnum, а через него — streambuf;
- streambuf: определен шаблон basic_streambuf, включен заголовочный файл xiosbase;
- xiosbase: определен класс ios_base. <br />
Видно, что всё организовано так, что для использования всех этих классов и шаблонов в программу достаточно включить заголовочный файл iostream.
- fstream: определены шаблоны basic_filebuf, basic_ifstream, basic_ofstream, basic_fstream.
- sstream: определены шаблоны basic_stringbuf, basic_istringstream, basic_ostringstream, basic_stringstream. <br />
2) Состояние потока определяется тремя элементами класса ios_base: eofbit, badbit, failbit. Значение каждого такого элемента может принимать значения 0 (сброшен) или 1 (установлен). 
- Так, когда cin достигает конца файла, eofbit устанавливается в значение 1. 
- Если cin не может прочитать ожидаемый формат данных (как в примерах выше) или производится попытка чтения недоступного файла, то failbit устанавливается в значение 1. - Элемент badbit устанавливается в 1, если происходит не поддающийся диагностике сбой, который может привести к повреждению потока.
- Имеется также элемент goodbit, который всегда равен нулю <br />
3) Разница между манипуляторами и флагами форматирования: <br />
Форматирование в языке программирования С+ реализуется посредством специальных функций – манипуляторов, 
а для задания видов форматирования используются флаги формата. Каждый поток, как и всякий объект, в любой момент 
времени характеризуется состоянием, определяющим свойства потока. Это состояние описывается при помощи флагов. 
Флаги форматирования позволяют задать установленные в потоке правила форматирования, действующие при выполнении операций ввода и вывода. 
Управлять флагами форматирования можно в том числе с помощью специальных функций – манипуляторов. Манипуляторы потоков используются в C++ 
при решении вопросов, связанных с форматированным вводом-выводом (например, задание точности, ширины полей, пропуск символов-разделителей 
во входном потоке, и т.д.) и находятся в пространстве имен std. <br />
4) Пути к файлам <br />
Пути - это наборы символов, показывающие расположение файла/каталога в файловой системе. 
Путь состоит из последовательности катлогов, разделенных символами "\\" или "/" в зависимости от системы. Например, в следующей записи адреса /home/user_viki/file.txt часть file.txt — это имя файла, а /home/user_viki — путь к нему. Путь может быть абсолютным и относительнм. Абсолютный путь - описывает расположение файла, начиная с корневого каталога, обозначаемого "/" в UNIX системах. Относительный путь представляет собой путь по отношению к текущему рабочему каталогу пользователя. Текущий каталог обозначается символом "."

