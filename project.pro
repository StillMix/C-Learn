# project.pro - файл описания проекта для системы сборки qmake

# Указываем необходимые модули Qt
QT += core gui widgets    # core - основной функционал, gui - графический интерфейс, widgets - виджеты

# Имя целевого файла (исполняемого)
TARGET = MultiPageApp     # Имя приложения

# Тип проекта
TEMPLATE = app            # app - обычное приложение (не библиотека)

# Добавляем все директории в путь поиска исходников
INCLUDEPATH += mainwindow \
               firstpage \
               secondpage

# Настройка директорий сборки
# Директория для объектных файлов (.o)
OBJECTS_DIR = build/obj

# Директория для moc-файлов (файлы, создаваемые Meta-Object Compiler)
MOC_DIR = build/moc

# Директория для ui-файлов (если используете .ui файлы)
UI_DIR = build/ui

# Директория для rcc-файлов (если используете ресурсы Qt)
RCC_DIR = build/rcc

# Установка выходной директории для исполняемого файла
CONFIG(debug, debug|release) {
    # Для отладочной сборки
    DESTDIR = bin/debug
} else {
    # Для релизной сборки
    DESTDIR = bin/release
}

# Список исходных файлов C++
SOURCES += \
    main.cpp \            # Точка входа в программу
    mainwindow/mainwindow.cpp \      # Реализация главного окна
    firstpage/firstpage.cpp \       # Реализация первой страницы
    secondpage/hello2.cpp            # Реализация второй страницы (не соответствует имени класса)

# Список заголовочных файлов
HEADERS += \
    mainwindow/mainwindow.h \        # Заголовочный файл главного окна
    firstpage/firstpage.h \         # Заголовочный файл первой страницы
    secondpage/secondpage.h          # Заголовочный файл второй страницы