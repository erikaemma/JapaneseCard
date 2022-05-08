#include "ui_cardedit.h"

#include "../include/cardedit.h"
#include "../include/japanesecard.h"

#include <QDebug>

extern QString cardEditTitle;

CardEdit::CardEdit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CardEdit)
{
    ui->setupUi(this);

    ui->c1Label->adjustSize();
    ui->c2Label->adjustSize();
    ui->c3Label->adjustSize();
    ui->wordLabel->adjustSize();
    ui->kanaLabel->adjustSize();
    ui->tagLabel->adjustSize();
    ui->typeLabel->adjustSize();
    ui->partOfSpeechLabel->adjustSize();
    ui->paraphraseLabel->adjustSize();
    ui->noteLabel->adjustSize();
}

CardEdit::~CardEdit()
{
    delete ui;
}

void CardEdit::on_buttonBox_accepted()
{
    CardStruct cardStruct;
    cardStruct.m_c1 = ui->c1LineEdit->text();
    cardStruct.m_c2 = ui->c2LineEdit->text();
    cardStruct.m_c3 = ui->c2LineEdit->text();
    cardStruct.m_type = ui->typeLineEdit->text();
    cardStruct.m_tag = ui->tagLineEdit->text();
    cardStruct.m_word = ui->wordLineEdit->text();
    cardStruct.m_kana = ui->kanaLineEdit->text();
    cardStruct.m_partOfSpeech = ui->partOfSpeechLineEdit->text();
    cardStruct.m_paraphrase = ui->paraphraseTextEdit->document()->toPlainText();
    cardStruct.m_note = ui->noteTextEdit->document()->toPlainText();
    sendData(cardStruct);
}

void CardEdit::receiveDate(CardStruct cardStruct)
{
    ui->c1LineEdit->setText(cardStruct.m_c1);
    ui->c2LineEdit->setText(cardStruct.m_c2);
    ui->c3LineEdit->setText(cardStruct.m_c3);
    ui->typeLineEdit->setText(cardStruct.m_type);
    ui->tagLineEdit->setText(cardStruct.m_tag);
    ui->wordLineEdit->setText(cardStruct.m_word);
    ui->kanaLineEdit->setText(cardStruct.m_kana);
    ui->partOfSpeechLineEdit->setText(cardStruct.m_partOfSpeech);
    ui->paraphraseTextEdit->setText(cardStruct.m_paraphrase);
    ui->noteTextEdit->setText(cardStruct.m_note);

    this->setWindowTitle(cardEditTitle);
}
