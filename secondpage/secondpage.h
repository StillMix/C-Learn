// secondpage.h - объявление класса второй страницы
#ifndef SECONDPAGE_H  // Защита от повторного включения файла
#define SECONDPAGE_H

#include <QWidget>       // Базовый класс для всех виджетов в Qt
#include <QComboBox>     // Выпадающий список
#include <QRadioButton>  // Переключатель (радиокнопка)

// Определяем класс SecondPage, наследующийся от QWidget
class SecondPage : public QWidget {
    Q_OBJECT  // Макрос для поддержки сигналов/слотов и других возможностей Qt
    
public:
    // Конструктор класса, parent по умолчанию nullptr
    SecondPage(QWidget *parent = nullptr);
    
private slots:  // Приватные слоты (обработчики событий)
    void onCheckButtonClicked();  // Метод, вызываемый при нажатии кнопки проверки
    
private:  // Приватные члены класса
    QComboBox *m_comboBox;    // Выпадающий список
    
    // Группа радиокнопок
    QRadioButton *m_option1;  // Первая опция
    QRadioButton *m_option2;  // Вторая опция
    QRadioButton *m_option3;  // Третья опция
    
    // Методы для настройки интерфейса и соединений
    void setupUI();           // Метод для создания и настройки UI компонентов
    void setupConnections();  // Метод для настройки сигналов и слотов
};

#endif // SECONDPAGE_H  // Закрытие защиты от повторного включения