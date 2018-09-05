/*
 * an helper class/service which monitor the network status, with signa for up, wifi and 3g/4g
 */
#ifndef QNETWORKWATCHER_H
#define QNETWORKWATCHER_H

#include <QObject>
#include <QString>
#include <QQmlContext>
#include <QNetworkConfigurationManager>
#include <QDebug>
#include "networktype.h"

using namespace std;

#define QNETWORKWATCHER_QML_NAME "networkwatcher"

#define QNWI qnetworkwatcher::getInstance()

/**
 * @brief this service report status of network connection
 * @version 1.2
 */
class qnetworkwatcher : public QObject {
    Q_OBJECT

    Q_PROPERTY(NetworkType::Type network READ getNetwork NOTIFY networkChanged)
    // is wifi up ?
    Q_PROPERTY(bool wifi READ getWifi NOTIFY wifiOn)
    // is 3g/4g up ?
    Q_PROPERTY(bool wcdma READ getWcdma NOTIFY wcdmaOn)
    // is ethernet up ?
    Q_PROPERTY(bool eth READ getEthernet NOTIFY ethOn)
    // is network down ?
    Q_PROPERTY(bool connected READ getConnected NOTIFY connectedChanged)

    friend class QNetworkConfiguration;

public:

    static qnetworkwatcher& getInstance();

    /**
     * @brief IMPORTANT ! you must register this objet into qml, this method do it for you.
     * Service will be available on the name "qnetworkwatcher" (else define in QNETWORKWATCHER_QML_NAME).
     * You can also register service by yourself (or not, if you don't need it in qml)
     * @param context
     * @param name : register service on this name, default to QNETWORKWATCHER_QML_NAME
     */
    static void init(QQmlContext *context, QString name=QNETWORKWATCHER_QML_NAME);

    /**
      * @brief return current state of network connection : 0 none, 1 has 3g/4g, 2 wifi on
      * @return
      */
    Q_INVOKABLE NetworkType::Type getNetwork() const {
        return network;
    }

    /**
      * @brief is wifi up ?
      * @return true if has wifi
      */
    Q_INVOKABLE bool getWifi() const {
        return network == NetworkType::WIFI;
    }

    /**
      * @brief is wcdma up ?
      * @return true if has 3g/4g
      */
    Q_INVOKABLE bool getWcdma() const {
        return network == NetworkType::WCDMA;
    }

    /**
      * @brief is eth up ?
      * @return true if connected through ethernet
      */
    Q_INVOKABLE bool getEthernet() const {
        return network == NetworkType::ETH;
    }

    /**
      * @brief is network down (no connection) ?
      * @return true if network, else false (down)
      */
    Q_INVOKABLE bool getConnected() const {
        return network != NetworkType::NONE;
    }

private :
    explicit qnetworkwatcher(QObject *parent = 0);

    QNetworkConfigurationManager net;
    NetworkType::Type network;

    void checkNetwork();

private slots:
    void configurationChanged(const QNetworkConfiguration&);
    void onlineStateChanged(bool);

signals:
    /**
     * @brief when type of network changed
     * this signal emit on change only, not on startup
     */
    void networkChanged();

    /**
     * @brief emited if connection status between online/offline changed
     * this signal emit on change only, not on startup
     */
    void connectedChanged();

    /**
     * @brief switched to wifi
     * this signal emit on change only, not on startup
     */
    void wifiOn();

    /**
     * @brief switched to wcdma (3g/4g/5g)
     * this signal emit on change only, not on startup
     */
    void wcdmaOn();

    /**
     * @brief switcher to ethernet
     * this signal emit on change only, not on startup
     */
    void ethOn();
};

#endif // QNETWORKWATCHER_H
