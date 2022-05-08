#ifndef JAPANESECARDSTRUCT_H
#define JAPANESECARDSTRUCT_H

#include <QString>
#include <QFile>

typedef struct
{
    unsigned long int size_full;
    char *m_word;
    char *m_kana;
    char *m_partOfSpeech;
    char *m_paraphrase;
    char *m_classification;
    unsigned long int size_word;
    unsigned long int size_kana;
    unsigned long int size_partOfSpeech;
    unsigned long int size_paraphrase;
    unsigned long int size_classification;
} JCStruct;

class JapaneseCardStruct
{
public:
    JapaneseCardStruct(QString filename);

private:
    QFile *qfile;

public:
    bool readAll();
};

#endif // JAPANESECARDSTRUCT_H
