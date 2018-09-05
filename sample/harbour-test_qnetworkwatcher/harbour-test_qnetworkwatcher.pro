
# The name of your application
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
    harbour-test_qnetworkwatcher.desktop \
    qml/pages/Status.qml \
    qml/pages/Main.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 256x256
