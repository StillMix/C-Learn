// main.cpp - Главный файл приложения
#include <QApplication>
#include <QWebEngineView>
#include <QWebChannel>
#include <QFile>
#include <QDir>
#include <QDebug>
#include "backend.h"

int main(int argc, char *argv[]) {
    // Для работы с Qt WebEngine необходимы эти параметры
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    
    // Инициализация приложения Qt
    QApplication app(argc, argv);
    
    // Создаем экземпляр WebEngineView - компонент для отображения веб-содержимого
    QWebEngineView view;
    
    // Создаем экземпляр нашего бэкенда
    Backend *backend = new Backend();
    
    // Создаем канал для общения между C++ и JavaScript
    QWebChannel *channel = new QWebChannel();
    
    // Регистрируем объект backend для доступа из JavaScript
    channel->registerObject("backend", backend);
    
    // Устанавливаем канал для веб-страницы
    view.page()->setWebChannel(channel);
    
    // Определяем путь до нашего Vue.js приложения
    QString path;
    
#ifdef QT_DEBUG
    // В режиме отладки используем локальный сервер разработки Vue.js
    path = "http://localhost:8080";
#else
    // В релизном режиме используем собранные файлы Vue.js из директории dist
    path = QDir::current().filePath("frontend/dist/index.html");
    QFile file(path);
    if (!file.exists()) {
        qWarning() << "Файл не найден:" << path;
        path = "qrc:/frontend/dist/index.html";
    } else {
        path = QUrl::fromLocalFile(path).toString();
    }
#endif
    
    // Загружаем Vue.js приложение
    view.load(QUrl(path));
    
    // Устанавливаем размеры окна
    view.resize(1024, 768);
    view.show();
    
    return app.exec();
}
