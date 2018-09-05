# qnetworkwatcher
qnetworkwatcher is a qt/qml service that listen to the network status and inform for any changes.

It give you a simple access to the network state (up/down) which adaptater is up and shortcut for wifi, eth and wcdma in both cpp and qml code.

* simple, only add the directory and pri file to your project
* easy to use, only one class as a service (singleton)
* give you the network status live
* shortcut for the main interface
* fully integrated with qml

Install
==================

1. Copy the src/qnetworkwatcher file to your src project directory.
2. Now edit the pro file to include the pri

Have a look at the sample project

Sample .pro file
------------------
Assuming you use the default name and location, for the project harbour-test_qnetworkwatcher :

```pro
TARGET = harbour-test_qnetworkwatcher

CONFIG += sailfishapp

include(src/qnetworkwatcher/qnetworkwatcher.pri)

SOURCES += src/harbour-test_qnetworkwatcher.cpp

DISTFILES += qml/harbour-test_qnetworkwatcher.qml \
    qml/cover/*.qml \
    qml/pages/*.qml \
    rpm/harbour-test_qnetworkwatcher.changes \
    rpm/harbour-test_qnetworkwatcher.spec \
    rpm/harbour-test_qnetworkwatcher.yaml \
    harbour-test_qnetworkwatcher.desktop 

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256
```
