// mainwindow.h - объявление класса главного окна приложения
#ifndef MAINWINDOW_H  // Защита от повторного включения файла
#define MAINWINDOW_H

// Включаем необходимые заголовочные файлы из Qt
#include <QMainWindow>       // Базовый класс для главного окна приложения
#include <QStackedWidget>    // Виджет для переключения между страницами
#include <QToolBar>          // Панель инструментов
#include <QAction>           // Действия для меню и панелей инструментов

// Включаем заголовочные файлы наших страниц
#include "firstpage/firstpage.h"       // Первая страница
#include "secondpage/secondpage.h"      // Вторая страница

// Определяем класс MainWindow, наследующийся от QMainWindow
class MainWindow : public QMainWindow {
    Q_OBJECT  // Макрос для поддержки сигналов/слотов и других возможностей Qt
    
public:
    // Конструктор класса, parent по умолчанию nullptr (окно верхнего уровня)
    MainWindow(QWidget *parent = nullptr);
    
private slots:  // Приватные слоты (обработчики событий)
    void showFirstPage();    // Метод для отображения первой страницы
    void showSecondPage();   // Метод для отображения второй страницы
    
private:  // Приватные члены класса и методы
    // Стек виджетов для хранения и переключения между страницами
    QStackedWidget *m_stackedWidget;
    
    // Указатели на страницы нашего приложения
    FirstPage *m_firstPage;      // Первая страница
    SecondPage *m_secondPage;    // Вторая страница
    
    // Элементы навигации
    QToolBar *m_navigationToolbar;   // Панель навигации
    QAction *m_firstPageAction;      // Действие для перехода на первую страницу
    QAction *m_secondPageAction;     // Действие для перехода на вторую страницу
    
    // Приватные методы для настройки интерфейса
    void setupUI();       // Метод для создания и настройки UI компонентов
    void setupActions();  // Метод для настройки действий и их соединений
};

#endif // MAINWINDOW_H  // Закрытие защиты от повторного включения