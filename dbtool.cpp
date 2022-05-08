#include "dbtool.h"

#include <QFileInfo>
#include <QSqlError>
#include "exception.h"
#include "readonlydelegate.h"

#include <QDebug>

DBTool::DBTool(QString dbFile) : m_dbFile(dbFile)
{
    if(QSqlDatabase::contains(m_dbcn))
    {
        m_sqliteDatabase = QSqlDatabase::database(m_dbcn);
    }
    else
    {
        m_sqliteDatabase = QSqlDatabase::addDatabase("QSQLITE", m_dbcn);
    }
    m_sqliteDatabase.setDatabaseName(dbFile);

    if(!(new QFileInfo(dbFile))->exists())
    {
        if(!m_sqliteDatabase.open())
        {
            throw DbException("Open SQLite .db file (for create) failed.", m_sqliteDatabase.lastError());
        }
        QSqlQuery sqlQuery(m_sqliteDatabase);
        if(!sqlQuery.exec("create table jwords(id integer primary key autoincrement,c1 text,c2 text,c3 text,type text,tag text,word text,kana text,part_of_speech text,paraphrase text,note text);"))
        {
            throw DbException("Create table failed.", m_sqliteDatabase.lastError());
        }
    }
    else if(!(new QFileInfo(dbFile))->isFile())
    {
        throw FileException("DB file is not a file", dbFile);
    }

    if(!m_sqliteDatabase.isOpen())
    {
        if(!m_sqliteDatabase.open())
        {
            throw DbException("Open SQLite .db file failed.", m_sqliteDatabase.lastError());
        }
    }
}

void DBTool::bindTableView(QWidget* widget, QTableView* tableView)
{
    m_sqlTableModel = new QSqlTableModel(widget, m_sqliteDatabase);
    m_sqlTableModel->setTable("jwords");
    m_sqlTableModel->setEditStrategy(QSqlTableModel::OnFieldChange);

    m_sqlTableModel->setHeaderData(0, Qt::Orientation::Horizontal, "序号");
    m_sqlTableModel->setHeaderData(1, Qt::Orientation::Horizontal, "一级分类");
    m_sqlTableModel->setHeaderData(2, Qt::Orientation::Horizontal, "二级分类");
    m_sqlTableModel->setHeaderData(3, Qt::Orientation::Horizontal, "三级分类");
    m_sqlTableModel->setHeaderData(4, Qt::Orientation::Horizontal, "种类");
    m_sqlTableModel->setHeaderData(5, Qt::Orientation::Horizontal, "标签/分类");
    m_sqlTableModel->setHeaderData(6, Qt::Orientation::Horizontal, "单词/词语/语法");
    m_sqlTableModel->setHeaderData(7, Qt::Orientation::Horizontal, "假名");
    m_sqlTableModel->setHeaderData(8, Qt::Orientation::Horizontal, "词性");
    m_sqlTableModel->setHeaderData(9, Qt::Orientation::Horizontal, "释义");
    m_sqlTableModel->setHeaderData(10, Qt::Orientation::Horizontal, "笔记");
    m_sqlTableModel->select();

    tableView->setModel(m_sqlTableModel);
    tableView->setItemDelegateForColumn(0, new ReadOnlyDelegate());
    tableView->setColumnHidden(0, true);
}

void DBTool::fillCardStruct(CardStruct& cardStruct, int id)
{
    QSqlQuery sqlQuery(m_sqliteDatabase);
    sqlQuery.prepare("select * from jwords where id=:id;");
    sqlQuery.bindValue(":id", id);
    if(sqlQuery.exec())
    {
        int resultSize = getQuerySize(sqlQuery);
        if(resultSize != 1)
        {
            throw DbException("fillCardStruct() query error.", "find " + QString(resultSize));
        }
        cardStruct.m_c1 = sqlQuery.value(1).toString();
        cardStruct.m_c2 = sqlQuery.value(2).toString();
        cardStruct.m_c3 = sqlQuery.value(3).toString();
        cardStruct.m_type = sqlQuery.value(4).toString();
        cardStruct.m_tag = sqlQuery.value(5).toString();
        cardStruct.m_word = sqlQuery.value(6).toString();
        cardStruct.m_kana = sqlQuery.value(7).toString();
        cardStruct.m_partOfSpeech = sqlQuery.value(8).toString();
        cardStruct.m_paraphrase = sqlQuery.value(9).toString();
        cardStruct.m_note = sqlQuery.value(10).toString();
    }
    else
    {
        throw DbException("fillCardStruct() query failed.", sqlQuery.lastError());
    }
}

int DBTool::getQuerySize(QSqlQuery& sqlQuery)
{
    int size = -1;

    if(sqlQuery.last())
    {
        size = sqlQuery.at() + 1;
    }
    sqlQuery.first();
    return size;
}

bool DBTool::update(CardStruct& cardStruct, int id)
{
    QSqlQuery sqlQuery(m_sqliteDatabase);
    sqlQuery.prepare("update jwords set c1=:c1,c2=:c2,c3=:c3,type=:type,tag=:tag,word=:word,kana=:kana,part_of_speech=:pos,paraphrase=:paraphrase,note=:note where id=:id;");
    sqlQuery.bindValue(":c1", cardStruct.m_c1);
    sqlQuery.bindValue(":c2", cardStruct.m_c2);
    sqlQuery.bindValue(":c3", cardStruct.m_c3);
    sqlQuery.bindValue(":type", cardStruct.m_type);
    sqlQuery.bindValue(":tag", cardStruct.m_tag);
    sqlQuery.bindValue(":word", cardStruct.m_word);
    sqlQuery.bindValue(":kana", cardStruct.m_kana);
    sqlQuery.bindValue(":pos", cardStruct.m_partOfSpeech);
    sqlQuery.bindValue(":paraphrase", cardStruct.m_paraphrase);
    sqlQuery.bindValue(":note", cardStruct.m_note);
    sqlQuery.bindValue(":id", id);
    bool result = sqlQuery.exec();
    m_sqlTableModel->select();
    return result;
}

bool DBTool::insert(CardStruct& cardStruct)
{
    QSqlQuery sqlQuery(m_sqliteDatabase);
    sqlQuery.prepare("insert into jwords (c1,c2,c3,type,tag,word,kana,part_of_speech,paraphrase,note) values (:c1,:c2,:c3,:type,:tag,:word,:kana,:pos,:paraphrase,:note);");
    sqlQuery.bindValue(":c1", cardStruct.m_c1);
    sqlQuery.bindValue(":c2", cardStruct.m_c2);
    sqlQuery.bindValue(":c3", cardStruct.m_c3);
    sqlQuery.bindValue(":type", cardStruct.m_type);
    sqlQuery.bindValue(":tag", cardStruct.m_tag);
    sqlQuery.bindValue(":word", cardStruct.m_word);
    sqlQuery.bindValue(":kana", cardStruct.m_kana);
    sqlQuery.bindValue(":pos", cardStruct.m_partOfSpeech);
    sqlQuery.bindValue(":paraphrase", cardStruct.m_paraphrase);
    sqlQuery.bindValue(":note", cardStruct.m_note);
    bool result = sqlQuery.exec();
    m_sqlTableModel->select();
    return result;
}

bool DBTool::remove(int row)
{
    if(row == -1)
    {
        return false;
    }
    m_sqlTableModel->removeRow(row);
    bool result = m_sqlTableModel->submitAll();
    m_sqlTableModel->select();
    return result;
}
