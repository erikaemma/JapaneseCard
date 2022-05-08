#ifndef CARDSTRUCT_H
#define CARDSTRUCT_H

#include <QString>

typedef struct
{
    QString m_c1; //分类1（书籍，如“标准日本语上册”）
    QString m_c2; //分类2（单元，如“Unit 1”）
    QString m_c3; //分类3（课程，如“course 1”）
    QString m_type; //种类，如“单词”、“敬语”、“寒暄语”、“语法”等
    QString m_tag; //分类，如“数字”、“国家”
    QString m_word; //日语单词（含中文）
    QString m_kana; //假名版本
    QString m_partOfSpeech; //词性
    QString m_paraphrase; //释义，json数据
    QString m_note; //笔记
} CardStruct;

#endif // CARDSTRUCT_H
