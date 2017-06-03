import QtQuick 2.7
import QtQuick.Controls 2.0
import QtQuick.Layouts 1.0

ApplicationWindow {
    property alias general: general
    property alias moreOptions: moreOptions

    id: applicationWindow
    visible: true
    width: 640
    height: 480
    minimumWidth: 640
    minimumHeight: 480
    maximumWidth: 640
    maximumHeight: 480
    title: qsTr("Print Document")

    General {
        id: general
        visible: true
    }

    MoreOptions {
        id: moreOptions
        visible: false
    }
}
