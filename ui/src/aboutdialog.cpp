#include "ui_aboutdialog.h"

#include "../include/aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutDialog)
{
    ui->setupUi(this);
    ui->textEdit->setReadOnly(true);
}

AboutDialog::~AboutDialog()
{
    delete ui;
}
