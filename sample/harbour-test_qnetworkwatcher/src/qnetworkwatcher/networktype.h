#ifndef NETWORKTYPE_H
#define NETWORKTYPE_H

#include <QObject>

/**
 * @brief The type of network;
 * only purpose of this class is to be able to have enum in qml
 */
class NetworkType : public QObject {
    Q_OBJECT

public:
    explicit NetworkType(QObject *parent = 0);

    enum Type {
        NONE = 0,
        WCDMA = 1,
        WIFI = 2,
        ETH = 3
    };
    Q_ENUM(Type)

private:
    Q_DISABLE_COPY(NetworkType)
};

#endif // NETWORKTYPE_H
