#include "qnetworkwatcher.h"
#include <QtQml>
#include <QMetaType>
#include <QDebug>

qnetworkwatcher::qnetworkwatcher(QObject *parent) : QObject(parent), network(NetworkType::NONE) {
    connect(&net, SIGNAL(configurationChanged(QNetworkConfiguration)),
            this, SLOT(configurationChanged(QNetworkConfiguration)));

    connect(&net, SIGNAL(onlineStateChanged(bool)),
            this, SLOT(onlineStateChanged(bool)));

    checkNetwork();
}

/**
 * @brief getInstance
 * @return
 */
qnetworkwatcher& qnetworkwatcher::getInstance() {
    static qnetworkwatcher instance;
    return instance;
}

/**
 * @brief IMPORTANT ! you must register this objet into qml, this method do it for you.
 * Service will be available on the name "qnetworkwatcher" (else define in QNETWORKWATCHER_QML_NAME).
 * You can also register service by yourself (or not, if you don't need it in qml)
 * @param context
     * @param name : register service on this name, default to QNETWORKWATCHER_QML_NAME
 */
void qnetworkwatcher::init(QQmlContext *context, QString name) {
#ifdef QT_DEBUG
    qDebug() << "qnetworkwatcher, registering qml service as : " << name;
#endif
    context->setContextProperty(name, &qnetworkwatcher::getInstance());

    qmlRegisterUncreatableType<NetworkType>("org.vostok.qnetworkwatcher", 1, 0, "NetworkType","");
}

/**
 * @brief qnetworkwatcher::configurationChanged
 * @param c
 */
void qnetworkwatcher::configurationChanged(const QNetworkConfiguration& c) {
    checkNetwork();
}

/**
 * @brief qnetworkwatcher::onlineStateChanged
 */
void qnetworkwatcher::onlineStateChanged(bool) {
    checkNetwork();
}

/**
 * @brief qnetworkwatcher::checkReseauValide
 */
void qnetworkwatcher::checkNetwork() {
    //   qDebug() << "check net : " << net.isOnline();
    NetworkType::Type n=network; // save old type
    bool oldStatus = network != NetworkType::NONE;

    network = NetworkType::NONE;
    if(net.isOnline()) {
        // net up
        switch (net.defaultConfiguration().bearerType()) {
        case QNetworkConfiguration::BearerWLAN:
            network=NetworkType::WIFI;
            break;
        case QNetworkConfiguration::BearerEthernet:
            network=NetworkType::ETH;
            break;
        case QNetworkConfiguration::BearerUnknown:
            break;
        default : // 3g edge etc...
            network=NetworkType::WCDMA;
            break;
        }
    }

    if(network==n) {
        // same type of connection, nothing to do
        return;
    }

#ifdef QT_DEBUG
    qDebug() << "qnetworkwatcher, changed : " << network;
#endif

    emit networkChanged();

    bool currentStatus = network != NetworkType::NONE;
    if( oldStatus != currentStatus) {
        emit connectedChanged();
    }

    if(network == NetworkType::WIFI || n == NetworkType::WIFI ) {
        emit wifiOn();
    }

    if(network == NetworkType::WCDMA || n == NetworkType::WCDMA ) {
        emit wcdmaOn();
    }

    if(network == NetworkType::ETH || n == NetworkType::ETH ) {
        emit ethOn();
    }
}
