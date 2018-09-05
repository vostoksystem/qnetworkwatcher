
#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include<QCoreApplication>
#include <sailfishapp.h>
#include "qnetworkwatcher/qnetworkwatcher.h"

#include <qdebug.h>

int main(int argc, char *argv[])
{
    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    qnetworkwatcher::init(view->rootContext());

    // TIP : it's better to init qnetworkwatcher BEFORE adding the qml source,
    // which will tries to load data upon rendering.

    // this create the qml view
    view->setSource(SailfishApp::pathTo("qml/harbour-test_qnetworkwatcher.qml"));
    view->show();

    return app->exec();
}
