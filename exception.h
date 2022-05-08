#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <QString>
#include <QSqlError>

class Exception
{
public:
    Exception(QString, QString);
    QString getMessage();
    QString getError();
    QString toString();
protected:
    QString m_message;
    QString m_error;
};

class DbException : public Exception
{
public:
    DbException(QString message, QSqlError error) : Exception(message, error.text()) {}
    DbException(QString message, QString error) : Exception(message, error) {}
};

class FileException : public Exception
{
public:
    FileException(QString message, QString error) : Exception(message, error) {}
};

#endif // EXCEPTION_H
