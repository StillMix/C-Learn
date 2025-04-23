// hello2.cpp - реализация второй страницы приложения
// Обратите внимание, что имя файла отличается от имени класса SecondPage
#include "secondpage/secondpage.h"  // Включаем заголовочный файл

// Включаем необходимые компоненты Qt
#include <QVBoxLayout>      // Вертикальный контейнер
#include <QLabel>           // Для отображения текста
#include <QPushButton>      // Для создания кнопок
#include <QFont>            // Для форматирования шрифта
#include <QComboBox>        // Выпадающий список
#include <QGroupBox>        // Группа элементов с рамкой и заголовком
#include <QRadioButton>     // Переключатели (радиокнопки)
#include <QMessageBox>      // Для отображения сообщений

// Конструктор класса SecondPage
SecondPage::SecondPage(QWidget *parent) : QWidget(parent) {
    // Вызываем методы настройки интерфейса и соединений
    setupUI();
    setupConnections();
}

// Метод для создания и настройки пользовательского интерфейса
void SecondPage::setupUI() {
    // Создаем заголовок страницы
    QLabel *headerLabel = new QLabel("Вторая страница");
    
    // Настраиваем шрифт заголовка
    QFont headerFont;
    headerFont.setPointSize(18);  // Размер шрифта
    headerFont.setBold(true);     // Жирный шрифт
    headerLabel->setFont(headerFont);
    
    // Выравнивание заголовка по центру
    headerLabel->setAlignment(Qt::AlignCenter);
    
    // Создаем текст с описанием страницы
    QLabel *descriptionLabel = new QLabel(
        "Это вторая страница нашего приложения. "
        "Здесь вы можете изучать новые компоненты Qt."
    );
    
    // Включаем перенос строк для длинного текста
    descriptionLabel->setWordWrap(true);
    
    // Выравнивание описания по центру
    descriptionLabel->setAlignment(Qt::AlignCenter);
    
    // Создаем подпись и выпадающий список
    QLabel *comboLabel = new QLabel("Выберите вариант:");
    m_comboBox = new QComboBox();
    
    // Добавляем элементы в выпадающий список
    m_comboBox->addItem("Вариант 1");
    m_comboBox->addItem("Вариант 2");
    m_comboBox->addItem("Вариант 3");
    
    // Создаем группу для радиокнопок с рамкой и заголовком
    QGroupBox *radioGroup = new QGroupBox("Выберите опцию:");
    
    // Создаем вертикальный контейнер для радиокнопок
    QVBoxLayout *radioLayout = new QVBoxLayout();
    
    // Создаем радиокнопки
    m_option1 = new QRadioButton("Опция 1");
    m_option2 = new QRadioButton("Опция 2");
    m_option3 = new QRadioButton("Опция 3");
    
    // По умолчанию выбираем первую опцию
    m_option1->setChecked(true);
    
    // Добавляем радиокнопки в контейнер
    radioLayout->addWidget(m_option1);
    radioLayout->addWidget(m_option2);
    radioLayout->addWidget(m_option3);
    
    // Устанавливаем контейнер для группы радиокнопок
    radioGroup->setLayout(radioLayout);
    
    // Создаем кнопку проверки
    QPushButton *checkButton = new QPushButton("Проверить выбор");
    
    // Настраиваем вид курсора при наведении на кнопку
    checkButton->setCursor(Qt::PointingHandCursor);
    
    // Устанавливаем минимальную высоту кнопки
    checkButton->setMinimumHeight(30);
    
    // Создаем главный вертикальный контейнер
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    
    // Добавляем компоненты в главный контейнер
    mainLayout->addWidget(headerLabel);          // Заголовок
    mainLayout->addSpacing(10);                  // Отступ 10 пикселей
    mainLayout->addWidget(descriptionLabel);     // Описание
    mainLayout->addSpacing(20);                  // Отступ 20 пикселей
    
    // Создаем горизонтальный контейнер для комбобокса и его подписи
    QHBoxLayout *comboLayout = new QHBoxLayout();
    comboLayout->addWidget(comboLabel);
    comboLayout->addWidget(m_comboBox, 1);       // 1 - коэффициент растяжения
    
    // Добавляем горизонтальный контейнер в главный
    mainLayout->addLayout(comboLayout);
    
    mainLayout->addSpacing(15);                  // Отступ 15 пикселей
    mainLayout->addWidget(radioGroup);           // Группа радиокнопок
    mainLayout->addSpacing(15);                  // Отступ 15 пикселей
    mainLayout->addWidget(checkButton);          // Кнопка проверки
    mainLayout->addStretch(1);                   // Растягиваемый пустой элемент
    
    // Настраиваем отступы контейнера от краев виджета
    mainLayout->setContentsMargins(30, 30, 30, 30);
}

// Метод для настройки сигналов и слотов
void SecondPage::setupConnections() {
    // Находим кнопку проверки на форме, используя рекурсивный поиск
    QPushButton *checkButton = findChild<QPushButton*>("", Qt::FindChildrenRecursively);
    
    // Подключаем сигнал clicked к слоту onCheckButtonClicked
    connect(checkButton, &QPushButton::clicked, this, &SecondPage::onCheckButtonClicked);
}

// Слот, вызываемый при нажатии кнопки проверки
void SecondPage::onCheckButtonClicked() {
    // Переменная для хранения выбранной радио-опции
    QString selectedOption;
    
    // Получаем текст выбранного элемента из выпадающего списка
    QString comboSelection = m_comboBox->currentText();
    
    // Определяем, какая радио-опция выбрана
    if (m_option1->isChecked()) {
        selectedOption = "Опция 1";
    } else if (m_option2->isChecked()) {
        selectedOption = "Опция 2";
    } else if (m_option3->isChecked()) {
        selectedOption = "Опция 3";
    }
    
    // Отображаем информационное сообщение с выбранными элементами
    QMessageBox::information(
        this,                                           // Родительский виджет
        "Ваш выбор",                                    // Заголовок окна
        "Вы выбрали: " + comboSelection + "\n" +       // Выбор из комбобокса
        "Выбранная опция: " + selectedOption           // Выбранная радио-опция
    );
}