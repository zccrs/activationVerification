#ifndef AESTOOLS_H
#define AESTOOLS_H
#include <QByteArray>

#include "Rijndael.h"

/**
 *该类实现加密解密
 */
class AESTools
{
private:
    CRijndael crijndael;
public:
    /**
     * @brief AESTools
     * @param key
     * 如果密匙长度不是16，自动纠正
     */
    AESTools(const QByteArray &key);

    /**
     * @brief Encrypt
     * @param data
     * @return
     * 将UTF-8字符串加密成HEX串
     */
    QByteArray Encrypt(const QByteArray& data);

    /**
     * @brief Decrypt
     * @param hexData
     * @return
     * 将HEX串解密为UTF-8字符串
     */
    QByteArray Decrypt(const QByteArray& hexData);
};

#endif // AESTOOLS_H
