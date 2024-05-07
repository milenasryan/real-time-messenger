#include "encryptor.h"

Encryptor::Encryptor() {
    key = "mysecretkey";
}

QString Encryptor::encrypt(const QString &data) {
    QByteArray rawData = data.toUtf8();
    QByteArray encrypted;
    for (int i = 0; i < rawData.size(); ++i) {
        encrypted.append(rawData[i] ^ key[i % key.size()]);
    }
    return QString(encrypted.toHex());
}

QString Encryptor::decrypt(const QString &data) {
    QByteArray encryptedData = QByteArray::fromHex(data.toUtf8());
    QByteArray decrypted;
    for (int i = 0; i < encryptedData.size(); ++i) {
        decrypted.append(encryptedData[i] ^ key[i % key.size()]);
    }
    return QString::fromUtf8(decrypted);
}
