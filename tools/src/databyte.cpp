#include "databyte.h"

#include <string.h>

/*
 * char数组转byte数组
 * 若char为字符串数组（结尾为“\0”），则使用sizeof()获得
 */
void DataByte::CharToByte(char* chars, byte* bytes, unsigned int count)
{
    memcpy(bytes, chars, count);
}

/*
 * byte数组转char数组
 */
void DataByte::ByteToChar(byte* bytes, char* chars, unsigned int count)
{
    memcpy(chars, bytes, count);
}

/*
 * 将int32/long转为byte数组
 * 默认int32为4字节(sizeof(data)=4或sizeof(int)=4)
 */
void DataByte::IntToByte(int data, byte* bytes)
{
    //byte* bytes = new byte[4];
    memset(bytes, 0, sizeof(byte) * 4);
    bytes[0] = (byte)(0xFF & data);
    bytes[1] = (byte)((0xFF00 & data) >> 8);
    bytes[2] = (byte)((0xFF0000 & data) >> 16);
    bytes[3] = (byte)((0xFF000000 & data) >> 24);
}

/*
 * 将byte数组转为int32/long
 * 默认int32为4字节
 */
int DataByte::ByteToInt(byte* bytes)
{
    int result = bytes[0] & 0xFF;
    result |= ((bytes[1] << 8) & 0xFF00);
    result |= ((bytes[2] << 16) & 0xFF0000);
    result |= ((bytes[3] << 24) & 0xFF000000);
    return result;
}

/*
 * 将long long转为byte数组
 * 默认long long为8字节
 */
void DataByte::LongLongToByte(long long data, byte* bytes)
{
    memset(bytes, 0, sizeof(byte) * 8);
    bytes[0] = (byte)(0xFF & data);
    bytes[1] = (byte)((0xFF00 & data) >> 8);
    bytes[2] = (byte)((0xFF0000 & data) >> 16);
    bytes[3] = (byte)((0xFF000000 & data) >> 24);
    bytes[4] = (byte)((0xFF00000000 & data) >> 32);
    bytes[5] = (byte)((0xFF0000000000 & data) >> 40);
    bytes[6] = (byte)((0xFF000000000000 & data) >> 48);
    bytes[7] = (byte)((0xFF00000000000000 & data) >> 56);
}

/*
 * 将byte数组转为long long
 * 默认long long为8字节
 */
long long DataByte::ByteToLongLong(byte* bytes)
{
    long long result = bytes[0] & 0xFF;
    result |= ((bytes[1] << 8) & 0xFF00);
    result |= ((bytes[2] << 16) & 0xFF0000);
    result |= ((bytes[3] << 24) & 0xFF000000);
    result |= ((((long long)bytes[4]) << 32) & 0xFF00000000);
    result |= ((((long long)bytes[5]) << 40) & 0xFF0000000000);
    result |= ((((long long)bytes[6]) << 48) & 0xFF000000000000);
    result |= ((((long long)bytes[7]) << 56) & 0xFF00000000000000);
    return result;
}

/*
 * 将short转为byte数组
 * 默认short为2字节
 */
void DataByte::ShortToByte(short data, byte* bytes)
{
    memset(bytes, 0, sizeof(byte) * 2);
    bytes[0] = (byte)(0xFF & data);
    bytes[1] = (byte)((0xFF00 & data) >> 8);
}

/*
 * 将byte数组转为short
 * 默认short为2字节
 */
short DataByte::ByteToShort(byte* bytes)
{
    short result = bytes[0] & 0xFF;
    result |= ((bytes[1] << 8) & 0xFF00);
    return result;
}
