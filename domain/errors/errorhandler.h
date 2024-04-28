#ifndef ERRORHANDLER_H
#define ERRORHANDLER_H

#include <QObject>

class ErrorHandler : public QObject
{
    Q_OBJECT

public:
    ErrorHandler(QObject* parent = nullptr)
        : QObject(parent) {}

signals:
    void errorFromDataBase(const QString&);
    void userAlreadyExists();
    void emailAlreadyExists();
    void phoneNumberAlreadyExists();
    void unknowError();
};

#endif // ERRORHANDLER_H
