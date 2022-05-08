#ifndef JAPANESECARD_H
#define JAPANESECARD_H

#include <QWidget>

#include "cardedit.h"
#include "../../tools/include/cardstruct.h"
#include "../../tools/include/dbtool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class JapaneseCard; }
QT_END_NAMESPACE

class JapaneseCard : public QWidget
{
    Q_OBJECT

public:
    JapaneseCard(QWidget *parent = nullptr);
    ~JapaneseCard();

private:
    Ui::JapaneseCard *ui;

    CardEdit *cardEdit;

    DBTool *dbTool;
    CardStruct m_cardStruct;

private slots:
    void receiveDate(CardStruct cardStruct);

    void on_ExitPushButton_clicked();

    void on_addPushButton_clicked();

    void on_modifyPushButton_clicked();

    void on_deletePushButton_clicked();

    void on_AboutPushButton_clicked();

signals:
    void sendData(CardStruct);
};
#endif // JAPANESECARD_H
