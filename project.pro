// project.pro - Файл проекта для qmake (альтернатива CMakeLists.txt)
QT += core gui widgets webengine webenginewidgets

CONFIG += c++17

SOURCES += \
    main.cpp \
    backend.cpp

HEADERS += \
    backend.h

RESOURCES += \
    resources.qrc

# Правила для копирования файлов Vue.js
win32 {
    QMAKE_POST_LINK += xcopy /E /I /Y $$shell_path($$PWD/frontend/dist) $$shell_path($$OUT_PWD/frontend/dist)
} else {
    QMAKE_POST_LINK += mkdir -p $$shell_path($$OUT_PWD/frontend/dist) && \
                      cp -r $$shell_path($$PWD/frontend/dist) $$shell_path($$OUT_PWD/frontend)
}