#ifndef CARDEDIT_H
#define CARDEDIT_H

#include <QDialog>

#include "../../tools/include/cardstruct.h"

namespace Ui {
class CardEdit;
}

class CardEdit : public QDialog
{
    Q_OBJECT

public:
    explicit CardEdit(QWidget *parent = nullptr);
    ~CardEdit();

private slots:
    void on_buttonBox_accepted();
    void receiveDate(CardStruct cardStruct);

signals:
    void sendData(CardStruct);

private:
    Ui::CardEdit *ui;
};

#endif // CARDEDIT_H
