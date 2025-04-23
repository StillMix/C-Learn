// firstpage.cpp - реализация первой страницы приложения
#include "firstpage.h"  // Включаем заголовочный файл

// Включаем необходимые компоненты Qt
#include <QLabel>           // Для отображения текста
#include <QPushButton>      // Для создания кнопок
#include <QVBoxLayout>      // Вертикальный контейнер
#include <QHBoxLayout>      // Горизонтальный контейнер
#include <QMessageBox>      // Для отображения сообщений
#include <QFont>            // Для форматирования шрифта

// Конструктор класса FirstPage
FirstPage::FirstPage(QWidget *parent) : QWidget(parent) {
    // Вызываем методы настройки интерфейса и соединений
    setupUI();
    setupConnections();
}

// Метод для создания и настройки пользовательского интерфейса
void FirstPage::setupUI() {
    // Создаем заголовок страницы
    QLabel *headerLabel = new QLabel("Главная страница");
    
    // Настраиваем шрифт заголовка
    QFont headerFont;
    headerFont.setPointSize(18);  // Размер шрифта
    headerFont.setBold(true);     // Жирный шрифт
    headerLabel->setFont(headerFont);
    
    // Выравнивание заголовка по центру
    headerLabel->setAlignment(Qt::AlignCenter);
    
    // Создаем подпись и поле для ввода текста
    QLabel *inputLabel = new QLabel("Введите текст:");
    m_inputField = new QLineEdit();
    
    // Устанавливаем подсказку в поле ввода (placeholder)
    m_inputField->setPlaceholderText("Текст для отправки");
    
    // Создаем горизонтальный контейнер для размещения подписи и поля ввода
    QHBoxLayout *inputLayout = new QHBoxLayout();
    inputLayout->addWidget(inputLabel);
    inputLayout->addWidget(m_inputField, 1);  // 1 - коэффициент растяжения
    
    // Создаем кнопку отправки
    QPushButton *submitButton = new QPushButton("Отправить");
    
    // Настраиваем вид курсора при наведении на кнопку
    submitButton->setCursor(Qt::PointingHandCursor);
    
    // Устанавливаем минимальную высоту кнопки
    submitButton->setMinimumHeight(30);
    
    // Создаем главный вертикальный контейнер
    // this в качестве родителя означает, что этот макет будет управлять данным виджетом
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Добавляем компоненты в главный контейнер
    mainLayout->addWidget(headerLabel);           // Заголовок
    mainLayout->addSpacing(20);                   // Отступ 20 пикселей
    mainLayout->addLayout(inputLayout);           // Контейнер с полем ввода
    mainLayout->addSpacing(10);                   // Отступ 10 пикселей
    mainLayout->addWidget(submitButton);          // Кнопка
    mainLayout->addStretch(1);                    // Растягиваемый пустой элемент
    
    // Настраиваем отступы контейнера от краев виджета
    mainLayout->setContentsMargins(30, 30, 30, 30);
}

// Метод для настройки сигналов и слотов
void FirstPage::setupConnections() {
    // Находим кнопку на форме
    QPushButton *submitButton = findChild<QPushButton*>();
    
    // Подключаем сигнал clicked к слоту onButtonClicked
    connect(submitButton, &QPushButton::clicked, this, &FirstPage::onButtonClicked);
    
    // Подключаем сигнал нажатия Enter в поле ввода к тому же слоту
    connect(m_inputField, &QLineEdit::returnPressed, this, &FirstPage::onButtonClicked);
}

// Слот, вызываемый при нажатии кнопки или Enter в поле ввода
void FirstPage::onButtonClicked() {
    // Получаем текст из поля ввода
    QString inputText = m_inputField->text();
    
    // Проверяем, не пустой ли текст
    if (inputText.isEmpty()) {
        // Отображаем предупреждение, если поле пустое
        QMessageBox::warning(
            this,                           // Родительский виджет
            "Внимание",                     // Заголовок окна
            "Пожалуйста, введите текст!"    // Текст сообщения
        );
    } else {
        // Отображаем информационное сообщение с введенным текстом
        QMessageBox::information(
            this,                       // Родительский виджет
            "Сообщение",                // Заголовок окна
            "Вы ввели: " + inputText    // Текст сообщения
        );
        
        // Очищаем поле ввода
        m_inputField->clear();
        
        // Устанавливаем фокус обратно на поле ввода
        m_inputField->setFocus();
    }
}