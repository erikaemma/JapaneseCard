#include "japanesecard.h"
#include "ui_japanesecard.h"
#include "exception.h"
#include "aboutdialog.h"

#include <QFileInfo>
#include <QAbstractItemModel>
#include <QModelIndex>
#include <QMessageBox>

#include <QDebug>

QString cardEditTitle;

JapaneseCard::JapaneseCard(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::JapaneseCard)
{
    ui->setupUi(this);

    cardEdit = new CardEdit(this);
    cardEdit->setModal(true);

    connect(cardEdit, SIGNAL(sendData(CardStruct)), this, SLOT(receiveDate(CardStruct)));
    connect(this, SIGNAL(sendData(CardStruct)), cardEdit, SLOT(receiveDate(CardStruct)));

    QString dbFilename = qApp->applicationDirPath() + "/japanese_card.db";
    try {
        dbTool = new DBTool(dbFilename);
        dbTool->bindTableView(this, ui->tableView);
    } catch (DbException e) {
        qDebug() << e.toString();
    } catch (FileException e) {
        qDebug() << e.toString();
    }
}

JapaneseCard::~JapaneseCard()
{
    delete ui;
}

void JapaneseCard::receiveDate(CardStruct cardStruct)
{
    m_cardStruct = cardStruct;
}

void JapaneseCard::on_ExitPushButton_clicked()
{
    qApp->exit();
}

void JapaneseCard::on_addPushButton_clicked()
{
    cardEditTitle = "添加";
    CardStruct cardStruct;
    sendData(cardStruct);

    if(cardEdit->exec() == QDialog::Accepted) {
        if(dbTool->insert(m_cardStruct))
        {
            qDebug() << "添加成功！";
        }
        else
        {
            qDebug() << "添加失败";
        }
    }
}

void JapaneseCard::on_modifyPushButton_clicked()
{
    cardEditTitle = "修改";
    QAbstractItemModel* model = ui->tableView->model();
    QModelIndex index = model->index(ui->tableView->currentIndex().row(), 0);
    int id = model->data(index).toInt();

    CardStruct cardStruct;
    try {
        dbTool->fillCardStruct(cardStruct, id);
        sendData(cardStruct);
        if(cardEdit->exec() == QDialog::Accepted) {
            if(dbTool->update(m_cardStruct, id))
            {
                qDebug() << "修改成功！";
            }
            else
            {
                //修改失败
                qDebug() << "修改失败！";
            }
        }
    } catch (DbException e) {
        qDebug() << e.toString();
    }
}

void JapaneseCard::on_deletePushButton_clicked()
{
    QMessageBox::StandardButtons buttons = QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel;
    QMessageBox::StandardButton defaultBtn = QMessageBox::NoButton;
    QMessageBox::StandardButton result = QMessageBox::question(this, "删除确认", "确定删除？", buttons, defaultBtn);
    if(result == QMessageBox::No || result == QMessageBox::Cancel)
    {
        return;
    }

    if(dbTool->remove(ui->tableView->currentIndex().row()))
    {
        qDebug() << "删除成功！";
    }
}

void JapaneseCard::on_AboutPushButton_clicked()
{
    AboutDialog *aboutDialog = new AboutDialog(this);
    aboutDialog->setModal(true);
    aboutDialog->show();
}
