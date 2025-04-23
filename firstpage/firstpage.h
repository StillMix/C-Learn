// firstpage.h - объявление класса первой страницы
#ifndef FIRSTPAGE_H  // Защита от повторного включения файла
#define FIRSTPAGE_H

#include <QWidget>     // Базовый класс для всех виджетов в Qt
#include <QLineEdit>   // Виджет для ввода текста

// Определяем класс FirstPage, наследующийся от QWidget
class FirstPage : public QWidget {
    Q_OBJECT  // Макрос для поддержки сигналов/слотов и других возможностей Qt
    
public:
    // Конструктор класса, parent по умолчанию nullptr
    FirstPage(QWidget *parent = nullptr);
    
private slots:  // Приватные слоты (обработчики событий)
    void onButtonClicked();  // Метод, вызываемый при нажатии кнопки
    
private:  // Приватные члены класса
    QLineEdit *m_inputField;  // Поле для ввода текста
    
    // Методы для настройки интерфейса и соединений
    void setupUI();           // Метод для создания и настройки UI компонентов
    void setupConnections();  // Метод для настройки сигналов и слотов
};

#endif // FIRSTPAGE_H  // Закрытие защиты от повторного включения