#ifndef ENCRYPTOR_H
#define ENCRYPTOR_H

#include <QString>

class Encryptor {
public:
    Encryptor();

    QString encrypt(const QString &data);
    QString decrypt(const QString &data);

private:
    QByteArray key;
};

#endif // ENCRYPTOR_H
