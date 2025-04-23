// mainwindow.cpp - реализация класса главного окна
#include "mainwindow.h"    // Включаем заголовочный файл
#include <QVBoxLayout>     // Для вертикального размещения элементов
#include <QIcon>           // Для работы с иконками

// Конструктор класса MainWindow
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    // Настраиваем заголовок окна
    setWindowTitle("Многостраничное приложение Qt");
    
    // Устанавливаем минимальный размер окна
    setMinimumSize(600, 400);
    
    // Вызываем методы настройки интерфейса и действий
    setupUI();
    setupActions();
    
    // По умолчанию показываем первую страницу при запуске
    showFirstPage();
}

// Метод для создания и настройки пользовательского интерфейса
void MainWindow::setupUI() {
    // Создаем стек виджетов - контейнер, позволяющий отображать только один виджет одновременно
    m_stackedWidget = new QStackedWidget(this);
    
    // Создаем экземпляры наших страниц
    m_firstPage = new FirstPage(this);       // Первая страница с формой ввода
    m_secondPage = new SecondPage(this);     // Вторая страница с дополнительными элементами
    
    // Добавляем страницы в стек виджетов
    m_stackedWidget->addWidget(m_firstPage);     // Индекс 0
    m_stackedWidget->addWidget(m_secondPage);    // Индекс 1
    
    // Устанавливаем стек виджетов как центральный виджет главного окна
    setCentralWidget(m_stackedWidget);
    
    // Создаем панель инструментов для навигации
    m_navigationToolbar = new QToolBar("Навигация", this);
    m_navigationToolbar->setMovable(false);              // Запрещаем перемещение панели
    m_navigationToolbar->setIconSize(QSize(32, 32));     // Размер иконок
    
    // Добавляем панель навигации слева
    addToolBar(Qt::LeftToolBarArea, m_navigationToolbar);
}

// Метод для настройки действий и их соединений
void MainWindow::setupActions() {
    // Создаем действие для перехода на первую страницу
    m_firstPageAction = new QAction("Главная", this);
    // Устанавливаем иконку из системной темы или из ресурсов
    m_firstPageAction->setIcon(QIcon::fromTheme("go-home", QIcon(":/icons/home.png")));
    m_firstPageAction->setCheckable(true);  // Делаем действие отмечаемым
    
    // Создаем действие для перехода на вторую страницу
    m_secondPageAction = new QAction("Вторая страница", this);
    m_secondPageAction->setIcon(QIcon::fromTheme("document-new", QIcon(":/icons/page.png")));
    m_secondPageAction->setCheckable(true);  // Делаем действие отмечаемым
    
    // Добавляем действия на панель инструментов
    m_navigationToolbar->addAction(m_firstPageAction);   // Добавляем действие главной страницы
    m_navigationToolbar->addAction(m_secondPageAction);  // Добавляем действие второй страницы
    
    // Соединяем сигналы и слоты для обработки нажатий
    // При активации действия вызываем соответствующий метод
    connect(m_firstPageAction, &QAction::triggered, this, &MainWindow::showFirstPage);
    connect(m_secondPageAction, &QAction::triggered, this, &MainWindow::showSecondPage);
}

// Слот для отображения второй страницы
void MainWindow::showSecondPage() {
    // Устанавливаем текущим виджетом в стеке вторую страницу
    m_stackedWidget->setCurrentWidget(m_secondPage);
    
    // Обновляем состояние кнопок (активна только кнопка второй страницы)
    m_firstPageAction->setChecked(false);    // Снимаем отметку
    m_secondPageAction->setChecked(true);    // Отмечаем как активную
}

// Слот для отображения первой страницы
void MainWindow::showFirstPage() {
    // Устанавливаем текущим виджетом в стеке первую страницу
    m_stackedWidget->setCurrentWidget(m_firstPage);
    
    // Обновляем состояние кнопок (активна только кнопка первой страницы)
    m_firstPageAction->setChecked(true);    // Отмечаем как активную
    m_secondPageAction->setChecked(false);  // Снимаем отметку
}