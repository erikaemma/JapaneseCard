#include "exception.h"

Exception::Exception(QString message, QString error)
{
    m_message = message;
    m_error = error;
}

QString Exception::getMessage()
{
    return m_message;
}

QString Exception::getError()
{
    return m_error;
}

QString Exception::toString()
{
    return m_message + "----------" + m_error;
}
