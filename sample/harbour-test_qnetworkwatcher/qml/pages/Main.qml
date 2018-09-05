import QtQuick 2.0
import Sailfish.Silica 1.0
import Nemo.Notifications 1.0
import org.vostok.qnetworkwatcher 1.0

Page {
    id: page
    property bool active: status===PageStatus.Active

    Grid{
        columns: 1
        anchors.fill: parent

        Item {
            width: parent.width
            height: parent.height / 3
            Image {
                width: Theme.iconSizeExtraLarge
                height: width
                anchors.centerIn: parent
                opacity:  ( networkwatcher.wifi ? 1.0 : 0.5 )
                source: "image://theme/icon-m-wlan-4?" + Theme.primaryColor
            }
        }

        Item {
            width: parent.width
            height: parent.height / 3
            Image {
                width: Theme.iconSizeExtraLarge
                height: width
                anchors.centerIn: parent
                opacity: ( networkwatcher.wcdma ? 1.0 : 0.5 )
                source: "image://theme/icon-m-mobile-network?" + Theme.primaryColor
            }
        }

        Item {
            width: parent.width
            height: parent.height / 3
            Image {
                width: Theme.iconSizeExtraLarge
                height: width
                anchors.centerIn: parent
                source: ( networkwatcher.connected ?
                             "image://theme/icon-l-check?" : "image://theme/icon-l-dismiss?" )  + Theme.primaryColor
            }
        }
    }

    onStatusChanged: {
        // The only purpose of this code is to show how to use enum in qml + js
        if (status===PageStatus.Active ) {
            var str = "unknow";
            switch(networkwatcher.network) {
            case NetworkType.WIFI :
                str = "Wifi";
                break;
            case NetworkType.WCDMA :
                str = "3G/4G";
                break;
            }

            console.log("page activated, network is : " + str);
        }
    }

    Notification {
        id: notification
        category: "x-nemo.example"
        summary: "Network"
        body: "Network status changed"
        previewSummary: summary
        previewBody: body
    }

    Connections {
        target: networkwatcher
        onNetworkChanged : {
            console.log("Network status changed")
            notification.publish();
        }
    }
}
