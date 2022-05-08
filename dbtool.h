#ifndef DBTOOL_H
#define DBTOOL_H

#include <QString>
#include <QSqlDatabase>
#include <QTableView>
#include <QSqlTableModel>
#include <QWidget>
#include <QSqlQuery>

#include "cardstruct.h"

class DBTool
{
public:
    DBTool(QString);
public:
    void bindTableView(QWidget*, QTableView*);
    void fillCardStruct(CardStruct&, int);
    bool update(CardStruct&, int);
    bool insert(CardStruct&);
    bool remove(int);
private:
    QString m_dbFile; //数据库文件路径+名称
    QString m_dbcn = "jc";
    QSqlDatabase m_sqliteDatabase; //数据库实例
    QSqlTableModel* m_sqlTableModel;
private:
    int getQuerySize(QSqlQuery&);
};

#endif // DBTOOL_H
