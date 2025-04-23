// backend.h - Заголовочный файл для класса Backend
#ifndef BACKEND_H
#define BACKEND_H

#include <QObject>
#include <QString>

// Класс, который будет доступен из JavaScript
class Backend : public QObject {
    Q_OBJECT
    
public:
    explicit Backend(QObject *parent = nullptr);
    
public slots:
    // Методы, которые будут вызываться из JavaScript
    QString getMessage();
    void processData(const QString &data);
    int calculate(int a, int b);
    
signals:
    // Сигналы, которые будут отправляться в JavaScript
    void dataChanged(const QString &newData);
    void progressUpdated(int progress);
    
private:
    QString m_message;
};

#endif // BACKEND_H