#ifndef DATABYTE_H
#define DATABYTE_H

typedef unsigned char byte;

class DataByte
{
public:

    static void CharToByte(char*, byte*, unsigned int);
    static void ByteToChar(byte*, char*, unsigned int);

    static void IntToByte(int, byte*);
    static int ByteToInt(byte*);

    static void LongLongToByte(long long, byte*);
    static long long ByteToLongLong(byte*);

    static void ShortToByte(short, byte*); //untest
    static short ByteToShort(byte*); //untest
};

#endif // DATABYTE_H
